#include "system/Memory.h"
#include "system/Type.h"
#include "system/KBC_Command.h"
#include "system/interrupt.h"
#include "system/peripheral.h"
#include "hal/SPIC.h"
#include "hal/KBC.h"

/******************************************************************************/
/** Service KBC command
 * input: service bit
*******************************************************************************/
void KBC_Process(void)
{
	if(KBC_Is_CMD())	//Command
	{
		KbcCmd = KBC_Read();
		KbcDLen = 0;
		KBC_64PORT();
		HOOK_64PORT();
	}
	else	// Data
	{
		KbcData = KBC_Read();
		if(KbcDLen!=0)
		{
			KbcDLen--;
			KBC_60PORT();
			HOOK_60PORT();
		}
		else
		{
			//KB command
			KBD_Process();
		}
	}
	NVIC_EnableIRQ(KBC_IB_IRQn);
}

/******************************************************************************/
/** Service multi bytes send to host
 * input: 
*******************************************************************************/
void Service_KBC_OBF(void)
{
	if(KBC_Is_IBF() || KBC_Is_OBF()) {
		BIT_SET(SERVICEflag,SERVICE_F_SENDKEY);		// set service bit
		return;
	}
	if(KBDataQueueTail != KBDataQueueHead) {
		Data2Host(Get_KBData_From_Queue());
	}
}

/******************************************************************************/
/** Write EC KBC data
 * input: The data want to send the host 
*******************************************************************************/
void Kbcwritedata(uint8_t Value)
{
	if(KBC_Is_IBF() || KBC_Is_OBF())
	{
		KBC_DataQueuing(Value);
	}
	else
	{
		Data2Host(Value);						// Send data to host.
	}
}

/******************************************************************************/
/** Send data to output buffer
 * input: 
*******************************************************************************/
void Data2Host(uint8_t data_byte)
{
	KBC_Set_Status(KEYL, 1);
	KBC_Set_Status(AOBF, 0);
	KBC_Set_Status(BIT6, 0);
	KBC_Set_Status(BIT7, 0);

	KBC_Write(data_byte);
}

/******************************************************************************/
/** Push data to data queue
 * input: data to queue 
*******************************************************************************/
void KBC_DataQueuing(uint8_t nQueuing)
{
	if(KBDataQueueHead > 16) return;

	KBDataQueue[(KBDataQueueHead)&0x0f] = nQueuing;
	KBDataQueueHead++;
	BIT_SET(SERVICEflag,SERVICE_F_SENDKEY);			// set service bit

	#if 0
	uint8_t QueHeadtemp, QueTailtemp;

	// check queue is full
	QueHeadtemp = KBDataQueueHead+1;
	QueTailtemp = KBDataQueueTail;
	QueHeadtemp &= 0x0F;
	QueTailtemp &= 0x0F;
	if(QueHeadtemp == QueTailtemp) return;

	KBDataQueue[(KBDataQueueHead++&0x0F)] = nQueuing;
	BIT_SET(SERVICEflag,SERVICE_F_SENDKEY);			// set service bit
	#endif
}

/******************************************************************************/
/** Get KBC data from queue
 * return: data from queue 
*******************************************************************************/
uint8_t Get_KBData_From_Queue(void)
{
	uint8_t ret;
	ret = KBDataQueue[KBDataQueueTail&0x0F];
	KBDataQueueTail++;
	if(KBDataQueueHead >= KBDataQueueTail)
	{
		KBDataQueueHead = 0;
		KBDataQueueTail = 0;
	}
	return ret;
	#if 0
	uint8_t ret;
	if(KBDataQueueTail == KBDataQueueHead) return ERROR;
	ret = KBDataQueue[KBDataQueueTail&0x0F];
	KBDataQueueTail++;

	// check again need send next
	if(KBDataQueueTail != KBDataQueueHead)
		BIT_SET(SERVICEflag,SERVICE_F_SENDKEY);			// set service bit
	return ret;
	#endif
}

void KBD_Process(void)
{
	uint8_t ret;

	// Second round parameters in
	if(KbdCmd) {
		ret = 0xFE;
		// Update LEDs command
		if(KbdCmd == 0xED) {
			Led_Datas = KbcData;
			//OEM_Write_Leds(Led_Datas);	// update LED
			ret = 0xFA;
		}
		// Set alternate scan codes
		if(KbdCmd == 0xF0) {
			KBCodeSet = KbcData;
			ret = 0xFA;
		}
		// Set typematic rate/delay
		if(KbdCmd == 0xF3) {
			KBTypematic = KbcData;
			ret = 0xFA;
		}
		KbdCmd=0;
		Kbcwritedata(ret);
		return;
	}

	// First round KBD command in
	KbdCmd = KbcData;

	switch(KbcData)
	{
		case 0xED:					// Update LEDs command
		case 0xEC:
			ret = 0xFA;
			break;
		case 0xEE:					// ECHO command
			ret = 0xEE;
			break;
		case 0xF0:					// Set alternate scan codes
			ret = 0xFA;
			break;
		case 0xF2:					// Read manufacturers ID
			Kbcwritedata(0xFA);
			Kbcwritedata(0xAB);

			if(IS_BIT_SET(KCCB42,Ccb42_XLATE_PC)) {
				ret = 0x83;
			}else {
				ret = 0x41;
			}
			break;
		case 0xF3:					// Set typematic rate/delay
			ret = 0xFA;
			break;
		case 0xF4:					// Enable scanning
			//Clear_Key();			// clear key buffer
			ret = 0xFA;
			break;
		case 0xF5:					// Default disable
			//Clear_Key();			// clear key buffer
			//Clear_Typematic();	// clear typematic
			ret = 0xFA;
			break;
		case 0xF6:					// Set defaults
			//Clear_Key();			// clear key buffer
			//Clear_Typematic();	// clear typematic
			ret = 0xFA;
			break;
		case 0xF7:
		case 0xF8:
		case 0xF9:
		case 0xFA:
		case 0xFB:
			ret = 0xFA;
			break;
		case 0xFF:					// Reset keyboard
			//Clear_Key();			// clear key buffer
			//Clear_Typematic();	// clear typematic
			Kbcwritedata(0xFA);
			ret = 0xAA;
			break;
		default:
			RAM_debug(0x6D);
			RAM_debug(KbcData);
			ret = 0xFE;
	}
	Kbcwritedata(ret);
}

void KBC_64PORT(void)
{
	switch(KbcCmd)
	{
		case 0x20:
			KBC_20CMD();
			break;

		case 0x60:
			KBC_60CMD();
			break;

		case 0xA4:
			KBC_A4CMD();
			break;

		case 0xA5:
			KBC_A5CMD();
			break;

		case 0xA6:
			KBC_A6CMD();
			break;

		case 0xA7:
			KBC_A7CMD();
			break;

		case 0xA8:
			KBC_A8CMD();
			break;

		case 0xA9:
			KBC_A9CMD();
			break;

		case 0xAA:
			KBC_AACMD();
			break;

		case 0xAB:
			KBC_ABCMD();
			break;

		case 0xAC:
			KBC_ACCMD();
			break;

		case 0xAD:
			KBC_ADCMD();
			break;

		case 0xAE:
			KBC_AECMD();
			break;
		
		case 0xC0:
			KBC_C0CMD();
			break;

		case 0xD0:
			KBC_D0CMD();
			break;

		case 0xD1:
			KBC_D1CMD();
			break;

		case 0xD2:
			KBC_D2CMD();
			break;

		case 0xD3:
			KBC_D3CMD();
			break;

		case 0xD4:
			KBC_D4CMD();
			break;

		case 0xE0:
			KBC_E0CMD();
			break;

		case 0xF0:
		case 0xF1:
		case 0xF2:
		case 0xF3:
		case 0xF4:
		case 0xF5:
		case 0xF6:
		case 0xF7:
		case 0xF8:
		case 0xF9:
		case 0xFA:
		case 0xFB:
		case 0xFC:
		case 0xFD:
		case 0xFE:
		case 0xFF:
			KBC_FXCMD();
			break;

		default:
			RAM_debug(0x64);
			RAM_debug(KbcCmd);
		break;
	}
}

/******************************************************************************/
/** KBC command 0x20, read the data from output port.
 * None
*******************************************************************************/
void KBC_20CMD(void)
{
	Kbcwritedata(KCCB42);
}

/******************************************************************************/
/** KBC command 0x60, Write the command byte command, next command byte will 
/   be written to the 0x60 port.
 * None
*******************************************************************************/
void KBC_60CMD(void)
{
	KbcDLen = 1;
}

/******************************************************************************/
/** KBC command 0xA4, Test KB Password, if ready return 0xFA, otherwise return
// 0xF1.
 * None
*******************************************************************************/
void KBC_A4CMD(void)
{
	if (IS_BIT_SET(KBFlag,PASS_READY))
	{
		Kbcwritedata(0xFA);	// Return FA if password is loaded
	}
	else
	{
		Kbcwritedata(0xF1);	// Return F1 if password not loaded
	}
}

/******************************************************************************/
/** KBC command 0xA5, Set KB Password
 * None
*******************************************************************************/
void KBC_A5CMD(void)
{
}

/******************************************************************************/
/** KBC command 0xA6, Check Password
 * None
*******************************************************************************/
void KBC_A6CMD(void)
{
	//Check Password
	if (IS_BIT_SET(KBFlag,PASS_READY))						// At this point, a password is loaded.
	{														// Enable inhibit switch
		BIT_SET(Gen_Info,Gen_Info_PASS_ENABLE); 			// Enable password
		Pass_Buff_Idx = 0;									// Clear password buffer index
		BIT_CLR(KBFlag,SCAN_INH);							// Clear internal keyboard inhibit
		Kbcwritedata(Pass_On);
	}
	else													// At this point, a password is not loaded.
	{
		Kbcwritedata(0x00);
	}
}

/******************************************************************************/
/** Handle command A7 - Disable Aux Device Interface
 * None 
 * None
*******************************************************************************/
void KBC_A7CMD(void)
{
	BIT_SET(KCCB42,Ccb42_DISAB_AUX);
}

/******************************************************************************/
/** Handle command A8 - Enable Aux Device Interface
 * None 
 * None
*******************************************************************************/
void KBC_A8CMD(void)
{
	BIT_SET(KCCB42,Ccb42_DISAB_AUX);
}

void KBC_A9CMD(void)
{
	BIT_SET(MULPX,MULPX_Multiplex);
	Kbcwritedata(0x00);
}

void KBC_AACMD(void)
{
	//BIT_SET(MULPX,MULPX_Multiplex);
	Kbcwritedata(0x55);
}

void KBC_ABCMD(void)
{
	Kbcwritedata(0x00);
}

void KBC_ACCMD(void)
{

}

void KBC_ADCMD(void)
{
	BIT_SET(KCCB42,Ccb42_DISAB_KEY);	// Disable auxiliary keyboard.
	BIT_SET(KBFlag,SCAN_INH);			// Inhibit scanner (internal keyboard).	
	// !!to do!!	//stop key scan
}

void KBC_AECMD(void)
{
	BIT_CLR(KCCB42,Ccb42_DISAB_KEY);	// Enable auxiliary keyboard.
	BIT_CLR(KBFlag,SCAN_INH);			// Enable scanner (internal keyboard).
}

void KBC_C0CMD(void)
{
	Kbcwritedata(0xBF);
}

void KBC_C1CMD(void)
{

}

void KBC_C2CMD(void)
{

}

void KBC_D0CMD(void)
{
	Kbcwritedata((1<<3)|(1<<2)|(1<<0));
}

void KBC_D1CMD(void)
{
	BIT_SET(CustomFlags,FastA20);
}

void KBC_D2CMD(void)
{

}

void KBC_D3CMD(void)
{

}

void KBC_D4CMD(void)
{

}

void KBC_E0CMD(void)
{
	Kbcwritedata(0x00);
}

void KBC_FXCMD(void)
{
	uint8_t i;
	if(IS_BIT_SET(KbcCmd, BIT0)) {
		i=5;
		while(--i);
		i=6;
		while(--i);
		i=6;
		while(--i);
	}
	KbcDLen = 0;
	KBC_ForceClr_Status(_OBF);
	KBC_ForceClr_Status(_IBF);
		//VW idx6 RCIN# low for 6us
		//	SetRCINLow;
		//	Delayus7us
		//	SetRCINHigh;
}

void KBC_60PORT(void)
{
	switch(KbcCmd)
	{
		case 0x60:
			KBC_60DATA();
			break;
		case 0xA5:
			KBC_A5DATA();
			break;

		case 0xD1:
			KBC_D1DATA();
			break;

		case 0xD2:
			KBC_D2DATA();
			break;

		case 0xD3:
			KBC_D3DATA();
			break;

		case 0xD4:
			KBC_D4DATA();
			break;

		default:
			RAM_debug(0x60);
			RAM_debug(KbcCmd);
			break;
	}
}

void KBC_60DATA(void)
{
	KCCB42 = KbcData;   // Write the data.
	if(IS_BIT_SET(KCCB42,Ccb42_DISAB_KEY)) {
		KBC_ADCMD();
	}else {
		KBC_AECMD();
	}
	if(IS_BIT_SET(KCCB42,Ccb42_SYS_FLAG)) {
		KBC_Set_Status(SYSF,1);
	}else {
		KBC_Set_Status(SYSF,0);
	}
}

void KBC_A5DATA(void)
{
	if ((Temp_Load == 0) && (KbcData == 0))	// The first byte is NULL
	{
		BIT_CLR(KBFlag,PASS_READY);			// clear password ready flag and exit
											// Cmd_Byte has already been set to 0.  So the code will
											// NOT wait for next byte
	}
	else
	{
		if (Temp_Load < 8)					// PASS_SIZE = 8
		{									// If there is room in the buffer
			Pass_Buff[Temp_Load] = KbcData;	// Store scan code
			Temp_Load++;					// Increment password buffer index
		}
		//Cmd_Byte = 0xA5;					// Set to keep waiting for next byte
		if (KbcData == 0)					// The last byte (null terminated string) has been stored
		{
			//Cmd_Byte = 0;					// Clear out the command byte.
			BIT_SET(KBFlag,PASS_READY);		// Set password ready bit.
		}
	}
}

void KBC_D1DATA(void)
{

}

void KBC_D2DATA(void)
{
	Kbcwritedata(KbcData);
}

void KBC_D3DATA(void)
{
	Aux_Data_To_Host(KbcData);
}

void KBC_D4DATA(void)
{
	if(KbcData==0xFF)						// if is reset command
	{
		SendFromAux(0xFA);
		SendFromAux(0xAA);
		SendFromAux(0x00);
	}

	//SendFromAux(0xFC);
	SendFromAux(0xFA);
}

void Aux_Data_To_Host(uint8_t data_byte)
{
	uint32_t data;

	//KBC->Status.BYTE &= 0x0F;
	KBC->STS &= 0x0F; 
	//KBC->Status.BITS.Kbc_ST1 = 1;
	KBC->STS_b.STS1 = 1;

	if (IS_BIT_SET(KCCB42,Ccb42_INTR_AUX))
	{
		Manual = 4;
		// printf("MS Auto IRQ E\n");
		// IRQ Number =12
		//KBC->KbcVwCtrl2.BITS.Kbc_irq_num = 0x0C;
		KBC->VWCTRL1_b.IRQNUM = 0x0C;
		//KBC->KbcVwCtrl1.BITS.Kbc_irq_trig_sel =1;
		KBC->VWCTRL0_b.TGLV = 1;
		// Enable auto irq
		//KBC->KbcVwCtrl1.BITS.Kbc_auto_irq_en =1;
		KBC->VWCTRL0_b.IRQEN = 1;
	}
	else
	{
		//KBC->KbcVwCtrl1.BITS.Kbc_auto_irq_en =0;
		KBC->VWCTRL0_b.IRQEN = 0;
	}

	data = (0x000000FF & (uint32_t)data_byte);
	//KBC->Kbc_output_data.DWORD = data;
	KBC->OB_b.OBDAT = data;
	//printf("MS TO HOST DATA =  %x\n", data_byte);

}
//-----------------------------------------------------------------
// Send data from aux mouse
//-----------------------------------------------------------------
void SendFromAux(uint8_t auxdata)
{
	//KBC->Status.BYTE &= 0x0F;
	KBC->STS &= 0x0F;

	//KBC->Status.BITS.Kbc_ST1 = 1;	// set AUX bit
	KBC->STS_b.STS1 = 1;
	Aux_Data_To_Host(auxdata);
}

//-----------------------------------------------------------------
// Process AUX command
//-----------------------------------------------------------------
void SendCmdtoMouse(uint8_t PortNum)
{
	uint8_t index;
	PortNum =0;
	KBC_A8CMD();
	ResetMSPendingData();
	SetPS2CmdACKCounter(0);
	MS_ID_CUNT = 0x00;

	if(BIT_SET(AuxTestFlagS,AUX2ByteCommand))
	{
		SetPS2CmdACKCounter(1);
		if(TPResolution == 0xFF)
		{
			TPResolution = KbcData;
		}
		else if(TPSamplingRate == 0xFF)
		{
			TPSamplingRate = KbcData;
		}
		SendFromAux(0xFA);

		//Send2Port(PortNum, KBHIData, SendCmdToMS);
		BIT_CLR(AuxTestFlagS,AUX2ByteCommand);
		return;
	}

	switch(KbcData)
	{
		case 0xE8:				// Set Resolution (2 byte)
			TPResolution = 0xFF;
			BIT_SET(AuxTestFlagS,AUX2ByteCommand);
			break;

		case 0xF3:				// Set Sampling Rate (2 byte)
			TPSamplingRate = 0xFF;
			BIT_SET(AuxTestFlagS,AUX2ByteCommand);
			break;

		case 0xF4:
			BIT_SET(MULPX,EnableTP);
			BIT_SET(AuxTestFlagS,MouseDriverIn);
			break;

		case 0xF5:
			BIT_CLR(AuxTestFlagS,MouseDriverIn);
			break;

		case 0xE6:
			break;

		case 0xE7:
			break;

		case 0xEA:
			break;

		case 0xEC:
			break;

		case 0xEE:
			break;

		case 0xF0:
			break;

		case 0xF6:
			break;

		case 0xE9:
			break;

		case 0xF2:
			MS_ID_CUNT = 2;
			break;

		case 0xEB:
		case 0xFE:
			break;

		case 0xFF:
			BIT_CLR(AuxTestFlagS,MouseDriverIn);
			BIT_CLR(MULPX,MULPX_Multiplex);	    // Disable Activate Multiplex mode

			for(index=0x00; index<3; index++)
			{
				if((Main_MOUSE_CHN-1)!=index)
				{
					if(IS_BIT_SET(AuxFlags[index],DEVICE_IS_MOUSE))
					{
						//AuxFlagss[index].AuxFlags.byte = 0x00;
						AuxFlags[index] = 0;
					}
				}
			}
			break;

		default:						// Invalid command
			break;
	}

	if(KbcData==0xFF)		// Reset command
	{
		SetPS2CmdACKCounter(3);
	}
	else if(KbcData==0xF2) // Read ID command
	{
		SetPS2CmdACKCounter(2);
		SendFromAux(0xFA);
		SendFromAux(0x00);
		return;
	}
	else if(KbcData==0xE9)	// Read status cmmand
	{
		SetPS2CmdACKCounter(4);
	}
	else					// Other commands
	{
		SetPS2CmdACKCounter(1);
	}

	SendFromAux(0xFA);

	//Send2Port(PortNum, KBHIData, SendCmdToMS);
}

void ResetMSPendingData(void)
{
	MSPending = 0x88;
	//F_Service_Send_PS2 = 0;
}

void SetPS2CmdACKCounter(uint8_t ackcunt)
{
	TPACKCounter = ackcunt;
}
