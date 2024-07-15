#include "system/Memory.h"
#include "system/ACPI_Command.h"
#include "armv8m/cmsis_gcc.h"
#include "system/peripheral.h"
#include "hal/ACPI.h"
#include "hal/TIMER.h"
#include "hal/SYSTEM.h"
#include "hal/PerVW.h"
#include "oem/crb/Oem_timer.h"
#include "chip/rts5911/RTS5911.h"

#ifdef SupportMTLCRB
#include "oem/crb/CRB.h"
#endif

/******************************************************************************/
/** Service ACPI command
 * input: service bit
*******************************************************************************/
void ACPI_Process(void)
{
	__disable_irq();
	BurstMode_touch();
	do {
		if(ACPI_Is_CMD())	//Command
		{
			AcpiCmd = ACPI_Read();
			AcpiDLen = 0;
			ACPI_66PORT();
		}
		else	// Data
		{
			AcpiData = ACPI_Read();
			if(AcpiDLen) {
				AcpiDLen--;
				ACPI_62PORT();
			}else {
				RAM_debug(0x6D);
				RAM_debug(AcpiData);
			}
		}
	}while((IS_BIT_SET(CustomFlags,ECCheckBurstMode)||ACPI_Is_BURST())&&ACPI_Burst_wait());
	TIMER32_Enable(TIMER3, disable);
	NVIC_EnableIRQ(ACPI_IB_IRQn);
	__enable_irq();
	ACPI_SMBusCmd();
}

// check Burst time-out or data in
uint8_t ACPI_Burst_wait(void)
{
	while(!ACPI_Is_IBF()) {
		if(BurstMode_check()) {
			ACPI_BURST_Clr();
			ACPI_SCI_OUT(ACPISCI);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			return FAIL;
		}
	}
	return SUCCESS;
}

void ACPI_66PORT(void)
{
	switch(AcpiCmd)
	{
		case 0x80:
			ACPI_80CMD();
			break;
		case 0x81:
			ACPI_81CMD();
			break;
		case 0x82:
			ACPI_82CMD();
			break;
		case 0x83:
			ACPI_83CMD();
			break;
		case 0x84:
			ACPI_84CMD();
			break;
		default:
#ifdef SupportMTLCRB
			HookHandle66Port();
#endif
			RAM_debug(0x66);
			RAM_debug(AcpiData);
	}
}

// Read Embedded Controller
void ACPI_80CMD(void)
{
	ACPI_SCI_OUT(ACPISCI);
	AcpiDLen =0x01;

	if(IS_BIT_SET(CustomFlags,ACPI_Mode)) {	// ACPI mode
		if(!ACPI_Is_BURST()) {
			BIT_SET(CustomFlags,ECCheckBurstMode);
		}
	}
}

// Write Embedded Controller
void ACPI_81CMD(void)
{
	ACPI_SCI_OUT(ACPISCI);
	AcpiDLen =0x02;

	if(IS_BIT_SET(CustomFlags,ACPI_Mode)) {	// ACPI mode
		if(!ACPI_Is_BURST()) {
			BIT_SET(CustomFlags,ECCheckBurstMode);
		}
	}
}

// Burst Enable Embedded Controller
void ACPI_82CMD(void)
{
	ACPI_BURST_Set();
	BIT_SET(CustomFlags,ECCheckBurstMode);
	ACPI2HOST(0x90);
}

// Burst Disable Embedded Controller
void ACPI_83CMD(void)
{
	ACPI_BURST_Clr();
	BIT_CLR(CustomFlags,ECCheckBurstMode);
	ACPI_SCI_OUT(ACPISCI);
}

// Query Embedded Controller
void ACPI_84CMD(void)
{
	uint8_t tempNum=0;
	if(SCIDataQueueHead != SCIDataQueueTail) {
		tempNum = SCIDataQueue[SCIDataQueueTail];
		SCIDataQueueTail++;
		if (SCIDataQueueTail >= SCIDQLEN)
		{
			SCIDataQueueTail = 0;
		}
		if (SCIDataQueueTail == SCIDataQueueHead)
			ACPI_Set_Status(SCIEVT,0);

		ACPI2HOST(tempNum);
	}
	else
	{
		ACPI_Set_Status(SCIEVT,0);
	}
}

void ACPI_62PORT(void)
{
	switch(AcpiCmd)
	{
		case 0x80:
			ACPI_80DATA();
			break;
		case 0x81:
			ACPI_81DATA();
			break;
		case 0x82:
			ACPI_82DATA();
			break;
		case 0x83:
			ACPI_83DATA();
			break;
		case 0x84:
			ACPI_84DATA();
			break;
		default:
			RAM_debug(0x62);
			RAM_debug(AcpiCmd);
			break;
	}
}

void ACPI_80DATA(void)
{
	if(AcpiDLen == 0) {
#ifdef SupportMTLCRB
		uint8_t value1;
		value1 = HandleACPI80Data();
		if(value1 != 0xFF)
			ACPI2HOST(value1);
		else
			ACPI2HOST(ECSpace_Read(AcpiData));
		
		BIT_CLR(CustomFlags,ECCheckBurstMode);
#else
		ACPI2HOST(ECSpace_Read(AcpiData));
		BIT_CLR(CustomFlags,ECCheckBurstMode);
#endif
	}
}

void ACPI_81DATA(void)
{
	ACPI_SCI_OUT(ACPISCI);
	if(AcpiDLen == 1) {
		AcpiData2 = AcpiData;
	}else if(AcpiDLen == 0) {
		ECSpace_Write(AcpiData2, AcpiData);
		BIT_CLR(CustomFlags,ECCheckBurstMode);
	}
}

void ACPI_82DATA(void)
{
}

void ACPI_83DATA(void)
{
}

void ACPI_84DATA(void)
{
}

void ACPI2HOST(uint8_t acpiData)
{
	ACPI_Write(acpiData);
	ACPI_SCI_OUT(ACPISCI);
}

// Push event number to SCI data queue
void QeventSend(uint8_t Qnumber)
{
	uint8_t tempNum=0;
	tempNum = SCIDataQueueHead;
	SCI_NUM = Qnumber;
	SCIDataQueue[tempNum] = Qnumber;
	tempNum++;
	if(tempNum >= SCIDQLEN) {
		tempNum = 0;
 	}
	if(tempNum!=SCIDataQueueTail)
		SCIDataQueueHead = tempNum;
	
	if(GetSlp_S3)
	{
		ACPI_Set_Status(SCIEVT,1);
		ACPI_SCI_OUT(ACPISCI);
	}

}

// Generate SCI pulse
void ACPI_SCI_OUT(uint8_t Qevent)
{
	if(Qevent == QeventSCI)
		__disable_irq();
	SCI_ON();
	Delay15us
	SCI_OFF();
	if(Qevent == QeventSCI)
		__enable_irq();
}

void SCI_ON()
{
	SetSCILow;
}

void SCI_OFF()
{
	SetSCIHigh;
}

void ECSpace_Write(uint8_t offset, uint8_t data)
{
	uint8_t* ECPACEP;
	ECPACEP = &BAT_STATUS;
	*(ECPACEP+offset) = data;
}

uint8_t ECSpace_Read(uint8_t offset)
{
	uint8_t* ECPACEP;
	ECPACEP = &BAT_STATUS;
	return *(ECPACEP+offset);
}

void oem_set_acpi_event_pending(void)
{
	ACPI_Set_Status(SCIEVT,1);
}

void oem_clr_acpi_event_pending(void)
{
	ACPI_Set_Status(SCIEVT,0);
}

// service SCPISMBus command
void ACPI_SMBusCmd(void)
{
}
