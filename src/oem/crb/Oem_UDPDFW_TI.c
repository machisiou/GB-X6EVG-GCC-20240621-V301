#include "RTK_Include.h"

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
/* TI PD */
#define TI6599x_ADDR1                       0x40
#define UCSI_SUPPORT						1
#define SUPPORT_TI_FW_UPD  			 		1
#define SUPPORT_TI_PD_APP_UPDATE			1 //981004-220208-A

#define _TISMAMP_ADDR        0x98    //8Bit = 0x98 //0X4C //981004-231103-A
#define CFG_META_SWITCH 	(255)
#define CFG_META_DELAY  	(254)
#define CFG_META_BURST  	(253)
/*-----------------------------------------------------------------------------
 * Local default control table
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#define TI_RamDebug(x)   RamDebug(x)
//-----------------------------------------------------------------------------

//*****************************************************************************
// CODE START
//*****************************************************************************
const sTi4ccStruct _TI_PD_4CC_TBLs[] =
{
    { 0x08, 0x04, 'U', 'C', 'S', 'I' }, //_4CC_UCSI
    { 0x08, 0x04, 'G', 'a', 'i', 'd' }, //_4CC_Gaid
    { 0x08, 0x04, 'G', 'A', 'I', 'D' }, //_4CC_GAID
    { 0x08, 0x04, 'P', 'B', 'M', 's' }, //_4CC_PBMs
    { 0x08, 0x04, 'P', 'B', 'M', 'c' }, //_4CC_PBMc
    { 0x08, 0x04, 'P', 'B', 'M', 'e' }, //_4CC_PBMe
	{ 0x08, 0x04, 'S', 'R', 'D', 'Y' }, //_4CC_SRDY
	{ 0x08, 0x04, 'S', 'R', 'Y', 'R' }, //_4CC_SRYR
    { 0x08, 0x04, 'F', 'L', 'r', 'd' }, //_4CC_FLrd //981004-220208-A
    { 0x08, 0x04, 'F', 'L', 'a', 'd' }, //_4CC_FLad //981004-220208-A
    { 0x08, 0x04, 'F', 'L', 'w', 'd' }, //_4CC_FLwd //981004-220208-A
    { 0x08, 0x04, 'F', 'L', 'v', 'y' }, //_4CC_FLvy //981004-220208-A
};

/******************************************************************************/
/** I2C protocol
 * Channel - I2C Channel 0~7
 * Addr - SMBus Device Address(8 bits)
 * WDatCnt - Write Data Count
 * RDatCnt - Write Data Count
 * WDatBuf - The Data write to Slave device
 * RDatBuf - The Data read from Slave device
 * return None
*******************************************************************************/
uint8_t I2C_Protocol_PD(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf)
{
	uint8_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

	Ptr->TAR = (uint8_t)(Addr >> 1);								/* Setup target address */
	Ptr->ENABLE = 0x00000001;										/* Enable I2C engine */
	if(WDatCnt != 0) {
		for (i = 0; i < (WDatCnt - 1); i++) {						/* Push data */
			Ptr->DATACMD = (uint32_t)WDatBuf[i];
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
		}

		if(RDatCnt == 0) {
			Ptr->DATACMD = (uint32_t)(WDatBuf[i] | (0x01 << 9));	/* Push last data with stop */
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
			while((Ptr->STATUS & 0x00000020) != 0);					/* Wait until idle */
		}
		else {
			Ptr->DATACMD = (uint32_t)WDatBuf[i];
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
		}
	}

	if(RDatCnt == 0) {
		Ptr->ENABLE = 0x00000000;									/* Disable I2C engine */
		}
	else {
		//Ptr->DATACMD_b.CMD = 1;									/* read */
		if(RDatCnt == 0xFF)
		{
			*RDatBuf = Ptr->DATACMD_b.DATA;
			for(i=0;i<*RDatBuf-1;i++) {
			Ptr->DATACMD_b.CMD = 1;									/* read */

			while(1) {												/* Check if IC_RX_FULL */
				if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
					break;
				}
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}

			*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		}	
		}
		else
		{
			for(i=0;i<RDatCnt-1;i++) {
			Ptr->DATACMD_b.CMD = 1;									/* read */

			while(1) {												/* Check if IC_RX_FULL */
				if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
					break;
				}
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}

			*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		}	
		}

		
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);						/* Read+Stop (uint8_t N) */

		while(1) {													/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		while((Ptr->STATUS & 0x00000020) != 0);	
		Ptr->ENABLE = 0x00000000;									/* ic_enable = 0 */
	}
	return SUCCESS;
}

uint8_t I2C_Protocol_SMART_AMP(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf)
{
	uint8_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

	Ptr->TAR = (uint8_t)(Addr >> 1);								/* Setup target address */
	Ptr->ENABLE = 0x00000001;										/* Enable I2C engine */
	if(WDatCnt != 0) {
		for (i = 0; i < (WDatCnt - 1); i++) {						/* Push data */
			Ptr->DATACMD = (uint32_t)WDatBuf[i];
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
		}

		if(RDatCnt == 0) {
			Ptr->DATACMD = (uint32_t)(WDatBuf[i] | (0x01 << 9));	/* Push last data with stop */
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
			while((Ptr->STATUS & 0x00000020) != 0);					/* Wait until idle */
		}
		else {
			Ptr->DATACMD = (uint32_t)WDatBuf[i];
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
		}
	}

	if(RDatCnt == 0) {
		Ptr->ENABLE = 0x00000000;									/* Disable I2C engine */
		}
	else {
		//Ptr->DATACMD_b.CMD = 1;									/* read */
		if(RDatCnt == 0xFF)
		{
			*RDatBuf = Ptr->DATACMD_b.DATA;
			for(i=0;i<*RDatBuf-1;i++) {
			Ptr->DATACMD_b.CMD = 1;									/* read */

			while(1) {												/* Check if IC_RX_FULL */
				if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
					break;
				}
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}

			*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		}	
		}
		else
		{
			for(i=0;i<RDatCnt-1;i++) {
			Ptr->DATACMD_b.CMD = 1;									/* read */

			while(1) {												/* Check if IC_RX_FULL */
				if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
					break;
				}
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}

			*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		}	
		}

		
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);						/* Read+Stop (uint8_t N) */

		while(1) {													/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		while((Ptr->STATUS & 0x00000020) != 0);	
		Ptr->ENABLE = 0x00000000;									/* ic_enable = 0 */
	}
	return SUCCESS;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_send_4cc
 * @function - pd_ti_send_4cc
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd_ti_send_4cc(uint8_t Index4cc)
{
    /* Set Host Block Data uint8_t Register by Write uint8_tcnt. */
    xUCSI_I2C_WR_BUFF[0] = _TI_PD_4CC_TBLs[Index4cc].ccmd;
    xUCSI_I2C_WR_BUFF[1] = _TI_PD_4CC_TBLs[Index4cc].bcnt;
    xUCSI_I2C_WR_BUFF[2] = _TI_PD_4CC_TBLs[Index4cc].cch1;
    xUCSI_I2C_WR_BUFF[3] = _TI_PD_4CC_TBLs[Index4cc].cch2;
    xUCSI_I2C_WR_BUFF[4] = _TI_PD_4CC_TBLs[Index4cc].cch3;
    xUCSI_I2C_WR_BUFF[5] = _TI_PD_4CC_TBLs[Index4cc].cch4;
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        6,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        0))

    if(I2C_Protocol(3,TI6599x_ADDR1,6,0,xUCSI_I2C_WR_BUFF,NULL))    
    {
        return SUCCESS;
    }
    return FAIL;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd_i2c_buffer_clear
 * @function - pd_i2c_buffer_clear
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void pd_i2c_buffer_clear(void)
{
    for (uint8_t i = 0; i < 32; i++)
    {
        xUCSI_I2C_WR_BUFF[i] = 0;
        xUCSI_I2C_RD_BUFF[i] = 0;
    }
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_HandleErroe
 * @function - pd1_ti_HandleErroe
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void pd1_ti_HandleErroe(void)
{
    xTIFW_Step = 0;
	ENABLE_PD_Step = 0;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_clear_event
 * @function - pd_ti_clear_event
 * @Upstream - By Call
 * @input    - xINT4,xINT3,xINT2,xINT1
 * @return   - none
 * @note     - none
 */
void pd_ti_clear_event(uint8_t *Var)
{
	uint8_t Count;
    pd_i2c_buffer_clear();
    xUCSI_I2C_WR_BUFF[0] = 0x18;  //INT_CLEAR1
    xUCSI_I2C_WR_BUFF[1] = 0x0B;  //uint8_t count = 11
   	for (Count = 0; Count < 11; Count++ )
   	{
   		xUCSI_I2C_WR_BUFF[Count+2] = *Var;
   		Var++;
   	}

    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        13,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        0))
    if(I2C_Protocol(3,TI6599x_ADDR1,13,0,xUCSI_I2C_WR_BUFF,NULL))
    {
        
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_check_Cmd1Complete
 * @function - pd_ti_check_Cmd1Complete
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd_ti_check_Cmd1Complete(void)
{
	uint8_t Count;
    xUCSI_I2C_RD_BUFF[4] = 0x00;
    xUCSI_I2C_WR_BUFF[0] = _TIPD_INT_EVENT1;    //0x14
    //if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                       &xUCSI_I2C_WR_BUFF[0],
    //                       1,
    //                       0,
    //                       &xUCSI_I2C_RD_BUFF[0],
    //                       0xFF))
	if(I2C_Protocol(3,TI6599x_ADDR1,1,0,xUCSI_I2C_WR_BUFF,NULL))
    {
    	for (Count = 0; Count<11 ; Count++)
    	{
    		xTIPD1_EVENT[Count] = xUCSI_I2C_RD_BUFF[Count+1];
    	}

        pd_ti_clear_event(&xTIPD1_EVENT[0]);

        if (xTIPD1_EVENT[3] & F_Cmd1Complete)  //uint8_t#4.6-Cmd1Complete
        {
            return SUCCESS;
        }
    }
    return FAIL;
}

/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_check_readyforpatch
 * @function - pd_ti_check_readyforpatch
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd_ti_check_readyforpatch(void)
{
	uint8_t Count;
//	SCLKTS_D = 0x13;							//SMBUS 0x12:100KHz,0x13:400KHz //981004-220615-R
    xUCSI_I2C_RD_BUFF[4] = 0x00;
    xUCSI_I2C_WR_BUFF[0] = _TIPD_INT_EVENT1;    //0x14
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        0xFF))
    if(I2C_Protocol(3,TI6599x_ADDR1,1,0xFF,xUCSI_I2C_WR_BUFF,xUCSI_I2C_RD_BUFF))
    {
    	for (Count = 0; Count<11 ; Count++)
    	{
    		xTIPD1_EVENT[Count] = xUCSI_I2C_RD_BUFF[Count+1];
    	}

        //pd_ti_clear_event(&xTIPD1_EVENT[0]);

        if (xTIPD1_EVENT[10] & F_ReadyForPatch)  //uint8_t#11.1-ReadyForPatch
        {
            return SUCCESS;
        }
    }
    return FAIL;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_check_readyforpatch
 * @function - pd_ti_check_readyforpatch
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd_ti_check_patchloaded(void)
{
	uint8_t Count;
    xUCSI_I2C_RD_BUFF[4] = 0x00;
    xUCSI_I2C_WR_BUFF[0] = _TIPD_INT_EVENT1;    //0x14
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        0xFF))
    if(I2C_Protocol(3,TI6599x_ADDR1,1,0xFF,xUCSI_I2C_WR_BUFF,xUCSI_I2C_RD_BUFF))
    {
    	for (Count = 0; Count<11 ; Count++)
    	{
    		xTIPD1_EVENT[Count] = xUCSI_I2C_RD_BUFF[Count+1];
    	}

        //pd_ti_clear_event(&xTIPD1_EVENT[0]);

        if (xTIPD1_EVENT[10] & F_PatchLoaded)  //uint8_t#11.0-PatchLoaded
        {
            return SUCCESS;
        }
    }
    return FAIL;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_check_ptch_mode
 * @function - pd1_ti_check_ptch_mode
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd1_ti_check_ptch_mode(void)
{
    xUCSI_I2C_WR_BUFF[0] = _TIPD_MODE;
    if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           5))
    {
        //xTIPD1_i2c_error = 0;
        if (xUCSI_I2C_RD_BUFF[1] == 'P')
        {
            return SUCCESS;
        }
    }
    else
    {
    	return FAIL;
        //xTIPD1_i2c_error++;
        //xTIPD1_service_delay = 100;
    }
    return SUCCESS;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_check_ptch_mode
 * @function - pd1_ti_check_ptch_mode
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd1_ti_check_app_mode(void)
{
    xUCSI_I2C_WR_BUFF[0] = _TIPD_MODE;
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        5))
    if(I2C_Protocol(3,TI6599x_ADDR1,1,5,xUCSI_I2C_WR_BUFF,xUCSI_I2C_RD_BUFF))
    {
        //xTIPD1_i2c_error = 0;
        if (xUCSI_I2C_RD_BUFF[1] == 'A')
        {
            return SUCCESS;
        }
    }
    else
    {
    	return FAIL;

    }
    return FAIL;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_check_CMD1
 * @function - pd_ti_check_CMD1
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd_ti_check_CMD1(void)
{
	xUCSI_I2C_WR_BUFF[0] = 0x08;	//CMD1
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        5))
    if(I2C_Protocol(3,TI6599x_ADDR1,1,5,xUCSI_I2C_WR_BUFF,xUCSI_I2C_RD_BUFF))
    {
        //xTIPD1_i2c_error = 0;
        if (xUCSI_I2C_RD_BUFF[1] == '!')
        {
        	if (xTIFW_Step == 0x02)		// Handling "pbms"
        	{
        		pd1_ti_HandleErroe();
        	}
        	else if (xTIFW_Step == 0x04)		// Handling "pbmc"
        	{
        		xTIFW_Step = 0xFF;		// Go to write "pbme"
				ENABLE_PD_Step = 0;
        	}
            return FAIL;
        }
        if (xUCSI_I2C_RD_BUFF[1] == 0)
        {
        	return SUCCESS;
        }
        return FAIL;
    }
    else
    	return FAIL;
        //xTIPD1_i2c_error++;
        //xTIPD1_service_delay = 100;
   // return FAIL;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_Write_pbms
 * @function - pd1_ti_Write_pbms
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
void pd1_ti_Write_pbms(void)
{
	if (ENABLE_PD_Step == 0)
    {
		pd_i2c_buffer_clear();
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		xUCSI_I2C_WR_BUFF[1] = 0x06;  //uint8_t count
		xUCSI_I2C_WR_BUFF[2] = xTIFW_Bin_Size;  
		xUCSI_I2C_WR_BUFF[3] = xTIFW_Bin_Size>>8;
		xUCSI_I2C_WR_BUFF[4] = 0x00;  
		xUCSI_I2C_WR_BUFF[5] = 0x00;
		xUCSI_I2C_WR_BUFF[6] = 0x08;  //Address
		xUCSI_I2C_WR_BUFF[7] = 0x1E;  //Timeout value 30*100ms=3sec
        if(I2C_Protocol(3,TI6599x_ADDR1,8,0,xUCSI_I2C_WR_BUFF,NULL))
		// if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		// 						&xUCSI_I2C_WR_BUFF[0],
	    //                     	8,
	    //                     	0,
	    //                     	&xUCSI_I2C_RD_BUFF[0],
	    //                   		0))
		{
			ENABLE_PD_Step++;
		}
	    return;
	}
	if (ENABLE_PD_Step == 1)
    {
		pd_ti_send_4cc(_4CC_PBMs);
		ENABLE_PD_Step++;
		return;
	}
	if (ENABLE_PD_Step == 2)
    {
	  	if ( pd_ti_check_CMD1())
	 	{
	 		ENABLE_PD_Step++;
	 		return;
		}
	}
	if (ENABLE_PD_Step == 3)
    {
        // Raymond need to guess uint8_t count val
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
//		if (TI_PD_WrToRdStream(TI6599x_ADDR1,
//								&xUCSI_I2C_WR_BUFF[0],
//	                        	1,
//	                         	0,
//	                         	&xUCSI_I2C_RD_BUFF[0],
//	                          	0xFF))
		if(I2C_Protocol(3,TI6599x_ADDR1,1,0,xUCSI_I2C_WR_BUFF,NULL))
		{
			;
		}
		ENABLE_PD_Step++;
		return;
	}
	if (ENABLE_PD_Step == 4)
    {
	    if (xUCSI_I2C_RD_BUFF[1] == 0)	// only check the first uint8_t
	    {
			xTIFW_Step++;
			ENABLE_PD_Step = 0;
			return;
		}
		pd1_ti_HandleErroe();
		return;
	}
}

/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_flash_patch_data
 * @function - pd1_ti_flash_patch_data
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
uint8_t pd1_ti_flash_patch_data(void)
{
    uint16_t addrcnt;
    uint16_t Bin_Cnt;
    uint8_t _TIPD_ADDH = 0x01;
    uint8_t _TIPD_ADDM = 0xC0;
    uint8_t _TIPD_ADDL = 0x00;
    Bin_Cnt = xTIFW_Bin_Size /32;
    for (addrcnt = 0; addrcnt<Bin_Cnt; addrcnt++) 
    {
        ///(_TIPD_ADDH, _TIPD_ADDM, _TIPD_ADDL, SPI_selection_internal, 32, &xUCSI_I2C_WR_BUFF[0]);
	
        if (TI_PD_WrToRdStream(0x10,
								&xUCSI_I2C_WR_BUFF[0],
	                        	32,
	                         	0,
	                         	&xUCSI_I2C_RD_BUFF[0],
	                          	0))
	    {
	    	_TIPD_ADDL += 32;
	    	if(_TIPD_ADDL == 0x00)
	    	{
	    		_TIPD_ADDM++;
	    	}
	    }
        //Delay1MS(5);
    }
    xTIFW_Step++;
    return SUCCESS;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_Write_pbmc
 * @function - pd1_ti_Write_pbmc
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
void pd1_ti_Write_pbmc(void)
{
	uint8_t Count;
	if (ENABLE_PD_Step == 0)
    {
		pd_ti_send_4cc(_4CC_PBMc);
		ENABLE_PD_Step++;
		return;
	}
	if (ENABLE_PD_Step == 1)
    {
		if ( pd_ti_check_CMD1())
	 	{
	 		ENABLE_PD_Step++;
	 		return;
		}
	}
	if (ENABLE_PD_Step == 2)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		if (TI_PD_WrToRdStream(TI6599x_ADDR1,
								&xUCSI_I2C_WR_BUFF[0],
	                        	1,
	                         	0,
	                         	&xUCSI_I2C_RD_BUFF[0],
	                          	0xFF))
		{
			;
		}
		ENABLE_PD_Step++;
		return;
	}
	if (ENABLE_PD_Step == 3)
    {
    	if (xUCSI_I2C_RD_BUFF[1] == 0)	// only check the first uint8_t
	    {
			xTIFW_Step++;
			ENABLE_PD_Step = 0;
			return;
		}
		xTIFW_Step = 0;
		ENABLE_PD_Step = 0;
		return;
	}
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_Write_pbme
 * @function - pd1_ti_Write_pbmc
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
void pd1_ti_Write_pbme(void)
{
	uint8_t Count;
	if (ENABLE_PD_Step == 0)
    {
		pd_ti_send_4cc(_4CC_PBMe);
		ENABLE_PD_Step++;
		return;
	}
	if (ENABLE_PD_Step == 1)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		if (TI_PD_WrToRdStream(TI6599x_ADDR1,
								&xUCSI_I2C_WR_BUFF[0],
	                        	1,
	                         	0,
	                         	&xUCSI_I2C_RD_BUFF[0],
	                          	0xFF))
		{
			;
		}
		ENABLE_PD_Step++;
		return;
	}
	if (ENABLE_PD_Step == 2)
    {
    	pd1_ti_HandleErroe();
		return;
	}
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_check_version
 * @function - pd1_ti_check_version
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd1_ti_check_version(void)
{
	uint8_t Count;
	//981004-220310-R-S for not reading TI chip correctly
	#if 0
	uint8_t Version[8];
	
	ECIndirectFastRead(0x01, 0xC0, 0xA6, SPI_selection_internal, 8, &Version[0]);    
	
    xUCSI_I2C_WR_BUFF[0] = _TIPD_OUID; //981004-220208-M
    if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           9))
    {
        for (Count = 0; Count<8 ; Count++)
    	{
    		xTIFW_Custuse[Count] = xUCSI_I2C_RD_BUFF[Count+1];
    		if(xTIFW_Custuse[Count] != Version[Count] )
    		{
    			xTIFW_Step = 0;
				ENABLE_PD_Step = 0;
				return FAIL;
    		}
    	}
    }
    else
    {
    	return FAIL;
    }
	#endif
	//981004-220310-R-E
	
    xUCSI_I2C_WR_BUFF[0] = _TIPD_VERSION;
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        5))
	if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,5,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
    {
        for (Count = 0; Count<4 ; Count++)
    	{
    		xTIFW_Version[Count] = xUCSI_I2C_RD_BUFF[Count+1];			
			PD_FW_Ver = xUCSI_I2C_RD_BUFF[2]; //981004-211206-A //0X2B9 , 02 =>AC , 04 =>AD , 06 =>AE			
    	}
    }
    else
    {		
    	return FAIL; //981004-210524-R
    }
    //981004-211206-A-S
	#if 1
	pd_i2c_buffer_clear();
    xUCSI_I2C_WR_BUFF[0] = 0x0D;
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0],
    //                        5))
	if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,5,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
    {
        for (Count = 0; Count<4 ; Count++)
    	{
    		xTIFW_Version[Count] = xUCSI_I2C_RD_BUFF[Count+1];			
			PD_FW_Ver2 = xUCSI_I2C_RD_BUFF[1]; //0X2BA(BIT4) , 00 =>65994 , 10=>65993			
    	}
    }
    else
    {
    	//return FAIL;
    }
    #endif	
    //981004-211206-A-E	
    return SUCCESS;
}
#if SUPPORT_TI_FW_UPD
/*-----------------------------------------------------------------------------
 * @subroutine - TI_FirmwareUpdate
 * @function - Service Cypress TI firmware update (Bin file in BIOS ROM)
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void TI_FirmwareUpdate(void)
{
	switch(xTIFW_Step)
	{
		case 0:
			if (pd_ti_check_readyforpatch())
			{
				Get_Bin_Size();
				xTIFW_Step++;
			}
			break;
		case 1:
			if(pd1_ti_check_ptch_mode())
			{
				xTIFW_Step++;				
			}
			break;
		case 2:
			pd1_ti_Write_pbms();
			break;
		case 3:
			pd1_ti_flash_patch_data();
			break;
		case 4:
			pd1_ti_Write_pbmc();
			break;
		case 5:
			if (pd1_ti_check_version())
			{
				xTIFW_Step++;
			}
			break;
		case 6:
			if(pd1_ti_check_app_mode())
			{
				xTIFW_Step++;
			}
			else
			{
				xTIFW_Step = 0;
				ENABLE_PD_Step = 0;
			}
			break;
		case 0xFF:
			pd1_ti_Write_pbme();
			break;
		default:
			BIT_SET(xTIFW_States,F_TIFW_Finish);
			xAPP_PD_UpdStepFinish = 0xA1;			// For app use //981004-220208-A
			xTIFW_Step = 0; //981004-220615-A
			ENABLE_PD_Step = 0; //981004-220615-A
//			SCLKTS_D = 0x12;		//SMBUS 0x12:100KHz,0x13:400KHz            			
			break;
	}
}
#endif // SUPPORT_TI_FW_UPD

//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - pd_ti_get_active_PDO
 * @function - pd_ti_get_active_PDO
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void pd_ti_get_active_PDO(void)
{
	 //uint16_t ITempW02; 	 
    /* Check AC_IN(AC_OK) make sure PD power or AC in system */
	#if 0
    if (IL_AC_IN)   /* [0]:AC_IN or PD_IN  [1]: No AC & No PD */
    {
        xTIPD1_pd_mV = 0;
        xTIPD1_pd_mA = 0;
        xTIPD1_pd_watt = 0;
        xTIPD1_poll_pdo_delay = 2;   /* Quick Polling */
        return;
    }
	#endif
	
    xUCSI_I2C_WR_BUFF[0] = _TIPD_ACTIVE_CONTRACT_PDO; //0x34	
    // if (TI_PD_WrToRdStream(TI6599x_ADDR1,             //Address 0x40
    //                        &xUCSI_I2C_WR_BUFF[0],
    //                        1,
    //                        0,
    //                        &xUCSI_I2C_RD_BUFF[0x10],
    //                        7))
    if(I2C_Protocol(3,TI6599x_ADDR1,6,0,xUCSI_I2C_WR_BUFF,NULL))
    {
        //xTIPD1_i2c_error = 0;		
        ITempW01 = ((xUCSI_I2C_RD_BUFF[0x12] & 0x03) * 256) +
                   xUCSI_I2C_RD_BUFF[0x11];
        xTIPD1_pd_mA = (uint8_t)(ITempW01 * 10);

        ITempB04 = (xUCSI_I2C_RD_BUFF[0x13] >> 2) & 0x03;
        ITempB05 = (uint8_t)((xUCSI_I2C_RD_BUFF[0x12] >> 2) +
                   (xUCSI_I2C_RD_BUFF[0x13] << 6));
        ITempW02 = ((ITempB04 * 256) + ITempB05) & 0x03FF;
        xTIPD1_pd_mV = (uint8_t)(ITempW02 * 50);
        ITempW02 = ITempW02 / 10;
        xTIPD1_pd_watt = (uint8_t)((ITempW01 * ITempW02) / 200);
        //xTIPD1_poll_pdo_delay = 20;  /* Slowdown polling speed */
    }
	else
	{
       ;
    }
	

}
//-----------------------------------------------------------------------------

void Enable_pd_adapter(void)
{
	
    #if 1	
    if (ENABLE_PD_Step == 0)
    {
        pd_i2c_buffer_clear();
        xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
        xUCSI_I2C_WR_BUFF[1] = 0x01;  //uint8_t count
        xUCSI_I2C_WR_BUFF[2] = 0x02;  //PP3 (PP_EXT1)		

//        if (TI_PD_WrToRdStream(TI6599x_ADDR1,
//                               &xUCSI_I2C_WR_BUFF[0],
//                               3,
//                               0,
//                               &xUCSI_I2C_RD_BUFF[0],
//                               0))
		if(I2C_Protocol(3,TI6599x_ADDR1,3,0,xUCSI_I2C_WR_BUFF,NULL))
        {
			;
        }
        ENABLE_PD_Step++;
        //return;
         _Delay_1ms(50);		
    }
    if (ENABLE_PD_Step == 1)
    {
        pd_ti_send_4cc(_4CC_SRDY);
        ENABLE_PD_Step++;		
		//return;
        _Delay_1ms(50);
    }
    if (ENABLE_PD_Step == 2)
    {
        if (pd_ti_check_Cmd1Complete())
        {
            ENABLE_PD_Step++;            			
        }		
        //if (ucsi_cmd_ppm_timeout())
        //{
            //ENABLE_PD_Step = 99;
        //}
        //return;
		 _Delay_1ms(50);
    }
    if (ENABLE_PD_Step == 3)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x08;  //CMD1
//        if (TI_PD_WrToRdStream(TI6599x_ADDR1,
//                               &xUCSI_I2C_WR_BUFF[0],
//                               1,
//                               0,
//                               &xUCSI_I2C_RD_BUFF[0],
//                               2))
		if(I2C_Protocol(3,TI6599x_ADDR1,3,0,xUCSI_I2C_WR_BUFF,NULL))
        {
			;
        }
				
		_Delay_1ms(50);
        xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
//        if (TI_PD_WrToRdStream(TI6599x_ADDR1,
//                               &xUCSI_I2C_WR_BUFF[0],
//                               1,
//                               0,
//                               &xUCSI_I2C_RD_BUFF[0],
//                               2))
		if(I2C_Protocol(3,TI6599x_ADDR1,1,2,xUCSI_I2C_WR_BUFF,xUCSI_I2C_RD_BUFF))
        {
			;
        }
		else
		{
           ; 
        }	
		//test0A = xUCSI_I2C_RD_BUFF[1];
        ENABLE_PD_Step++;
        //return;
    }    
    ENABLE_PD_Step = 0;
	//while(1);
    #endif    
}
void Disable_pd_adapter(void)
{	 
     pd_ti_send_4cc(_4CC_SRYR);
	 _Delay_1ms(20);	 
	 if (pd_ti_check_Cmd1Complete())
     {
		; 
     }     
}	

//981004-211102-A-S
void TI_PD_Warm_reset(void)
{	 
     pd_ti_send_4cc(_4CC_Gaid);	 
}
//981004-211102-A-E		

#if 0
void TBT_Reconnet(void)
{
    uint8_t Count;

    if (ENABLE_PD_Step == 0)
    {
	  pd_i2c_buffer_clear(); 	
      xUCSI_I2C_WR_BUFF[0] = _TIPD_SYSTEM_CONFIG; //0x28
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           5))
      {
        for (Count = 0; Count< 4 ; Count++)
    	{
    		xPORT_Config[Count] = xUCSI_I2C_RD_BUFF[Count+1];
           			
    	}
      }
      else
      {		
    	  ;
      }
      _Delay_1ms(50);
	  xUCSI_I2C_WR_BUFF[0] = _TIPD_SYSTEM_CONFIG; //0x28
      xUCSI_I2C_WR_BUFF[1] = 0x04;  //uint8_t count
      xUCSI_I2C_WR_BUFF[2] = xPORT_Config[0]; //uint8_t 1 	
      xUCSI_I2C_WR_BUFF[3] = xPORT_Config[1]; //uint8_t 2 
      xUCSI_I2C_WR_BUFF[4] = xPORT_Config[2]; //uint8_t 3
      xUCSI_I2C_WR_BUFF[5] = xPORT_Config[3]; //uint8_t 4	
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                               &xUCSI_I2C_WR_BUFF[0],
                               6,
                               0,
                               &xUCSI_I2C_RD_BUFF[0],
                               0))
        {
			;
        }
	  _Delay_1ms(50);
	  xUCSI_I2C_WR_BUFF[0] = _TIPD_SYSTEM_CONFIG; //0x28
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           5))
      {
        for (Count = 0; Count< 4 ; Count++)
    	{
    		xPORT_Config[Count] = xUCSI_I2C_RD_BUFF[Count+1];
            ;			
    	}
      }
      else
      {		
    	  ;
      }
	}	
    ENABLE_PD_Step = 0;	
}

void TBT_Reconnet2(void)
{
    uint8_t Count;

    if (ENABLE_PD_Step == 0)
    {
	  pd_i2c_buffer_clear(); 	
      xUCSI_I2C_WR_BUFF[0] = _TIPD_SYSTEM_CONFIG; //0x28
      if (TI_PD_WrToRdStream(TI6599x_ADDR2,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           5))
      {
        for (Count = 0; Count< 4 ; Count++)
    	{
    		xPORT_Config2[Count] = xUCSI_I2C_RD_BUFF[Count+1];            			
    	}
      }
      else
      {		
    	   ;
      }
      _Delay_1ms(50);
	  xUCSI_I2C_WR_BUFF[0] = _TIPD_SYSTEM_CONFIG; //0x28
      xUCSI_I2C_WR_BUFF[1] = 0x04;  //uint8_t count
      xUCSI_I2C_WR_BUFF[2] = xPORT_Config2[0]; //uint8_t 1 	
      xUCSI_I2C_WR_BUFF[3] = xPORT_Config2[1]; //uint8_t 2 
      xUCSI_I2C_WR_BUFF[4] = xPORT_Config2[2]; //uint8_t 3
      xUCSI_I2C_WR_BUFF[5] = xPORT_Config2[3]; //uint8_t 4	
      if (TI_PD_WrToRdStream(TI6599x_ADDR2,
                               &xUCSI_I2C_WR_BUFF[0],
                               6,
                               0,
                               &xUCSI_I2C_RD_BUFF[0],
                               0))
      {
			;
      }
	  else
	  {
		    ;
	  }	    
	  _Delay_1ms(50);
	  xUCSI_I2C_WR_BUFF[0] = _TIPD_SYSTEM_CONFIG; //0x28
      if (TI_PD_WrToRdStream(TI6599x_ADDR2,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           5))
      {
        for (Count = 0; Count< 4 ; Count++)
    	{
    		xPORT_Config2[Count] = xUCSI_I2C_RD_BUFF[Count+1];
            ;			
    	}
      }
      else
      {		
    	   ;
      }
	}	
    ENABLE_PD_Step = 0;	
}
#endif
void TI_FW_CHECK(void)
{
    uint8_t Count;
   
	pd_i2c_buffer_clear(); 	
    xUCSI_I2C_WR_BUFF[0] = _TIPD_OUID; //0x06 //981004-220208-M
    //if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                       &xUCSI_I2C_WR_BUFF[0],
    //                       1,
    //                       0,
    //                       &xUCSI_I2C_RD_BUFF[0],
    //                       9))
	if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,9,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
    {
        for (Count = 0; Count< 8 ; Count++)
    	{
    		xPORT_FW_VER[Count] = xUCSI_I2C_RD_BUFF[Count+1];           		
    	}
    }    
	TI_FW_Ver = xPORT_FW_VER[0];
    TI_FW_Model = xPORT_FW_VER[1];    	
}

//981004-211215-A-S
#if 0
void S0_STATUS(void)
{
    uint8_t Count;

    if (ENABLE_PD_Step == 0)
    {
	  pd_i2c_buffer_clear(); 	
      xUCSI_I2C_WR_BUFF[0] = _POWER_STATUS; //0x20 //2 uint8_t
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           3))
      {
        for (Count = 0; Count< 2 ; Count++)
    	{
    		xPOWER_STS[Count] = xUCSI_I2C_RD_BUFF[Count+1];           		
    	}
      }
      else
      {		
    	   ;
      }
      Delay1MS(50);
	  xUCSI_I2C_WR_BUFF[0] = _POWER_STATUS; //0x20 //2 uint8_t
      xUCSI_I2C_WR_BUFF[1] = 0x02;  //uint8_t count
      xUCSI_I2C_WR_BUFF[2] = xPOWER_STS[0] & 0xF8 ; //uint8_t 1 bit0/bit1/bit2 is 0 => 0x000 	
      xUCSI_I2C_WR_BUFF[3] = xPOWER_STS[1]; //uint8_t 2 
      
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                               &xUCSI_I2C_WR_BUFF[0],
                               4,
                               0,
                               &xUCSI_I2C_RD_BUFF[0],
                               0))
     {
		;
     }
	 else
	 {
		;
	 }	 
	  Delay1MS(50);
	  xUCSI_I2C_WR_BUFF[0] = _POWER_STATUS; //0x20 //2 uint8_t
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           3))
      {
        for (Count = 0; Count< 2 ; Count++)
    	{
    		xPOWER_STS[Count] = xUCSI_I2C_RD_BUFF[Count+1];           	
    	}
      }
      else
      {		
    	   ;
      }
	}	
    ENABLE_PD_Step = 0;	
}
//981004-211215-A-E

//981004-211215-A-S
void S4_STATUS(void)
{
    uint8_t Count;

    if (ENABLE_PD_Step == 0)
    {
	  pd_i2c_buffer_clear(); 
      #if 0	  
      xUCSI_I2C_WR_BUFF[0] = _POWER_STATUS; //0x20 //2 uint8_t
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           3))
      {
        for (Count = 0; Count< 2 ; Count++)
    	{
    		xPOWER_STS[Count] = xUCSI_I2C_RD_BUFF[Count+1];           			
    	}
      }
      else
      {		
    	   ;
      }
      Delay1MS(50);
	  #endif
	  xUCSI_I2C_WR_BUFF[0] = _POWER_STATUS; //0x20 //2 uint8_t
      xUCSI_I2C_WR_BUFF[1] = 0x02;  //uint8_t count
      //xUCSI_I2C_WR_BUFF[2] = ((xPOWER_STS[0]) | BIT1) ; //uint8_t 1 bit0/bit2 is 0 BIT1 is 1 => 0x010 
	  //xUCSI_I2C_WR_BUFF[3] = xPOWER_STS[1]; //uint8_t 2 
      xUCSI_I2C_WR_BUFF[2] = 0x02; //uint8_t 1	  
      xUCSI_I2C_WR_BUFF[3] = 0x00; //uint8_t 2 
      
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                               &xUCSI_I2C_WR_BUFF[0],
                               4,
                               0,
                               &xUCSI_I2C_RD_BUFF[0],
                               0))
     {
		;
     }
	 else
	 {
		;
	 }	 
	  Delay1MS(50);
	  xUCSI_I2C_WR_BUFF[0] = _POWER_STATUS; //0x20 //2 uint8_t
      if (TI_PD_WrToRdStream(TI6599x_ADDR1,
                           &xUCSI_I2C_WR_BUFF[0],
                           1,
                           0,
                           &xUCSI_I2C_RD_BUFF[0],
                           3))
      {
        for (Count = 0; Count< 2 ; Count++)
    	{
    		xPOWER_STS[Count] = xUCSI_I2C_RD_BUFF[Count+1];           		
    	}
      }
      else
      {		
    	   ;
      }
	}	
    ENABLE_PD_Step = 0;	
}
//981004-211215-A-E
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_read_Ouid 
 * @function - pd1_ti_read_Ouid
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd1_ti_read_Ouid(void)
{
	uint8_t Count;
    xUCSI_I2C_WR_BUFF[0] = _TIPD_OUID;
    //if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                       &xUCSI_I2C_WR_BUFF[0],
    //                       1,
    //                       0,
    //                       &xUCSI_I2C_RD_BUFF[0],
    //                       9))
	if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,9,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
    {
    	for (Count = 0; Count<8 ; Count++)
    	{
    		xTIFW_OUID[Count] = xUCSI_I2C_RD_BUFF[Count+1];
    		xAPP_PD_UpdStepFinish = 0xA1;
    	}
        
    }
    else
    {
    	return FAIL;
    }
    return SUCCESS;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_boot_status
 * @function - pd1_ti_boot_status
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
uint8_t pd1_ti_boot_status(void)
{
	uint8_t Count;
    xUCSI_I2C_WR_BUFF[0] = _TIPD_BOOT_STATUS;
    //if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                       &xUCSI_I2C_WR_BUFF[0],
    //                       1,
    //                       0,
    //                       &xUCSI_I2C_RD_BUFF[0],
    //                       5))
	if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,5,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
    {
		if((xUCSI_I2C_RD_BUFF[1] & 0x40) || (xUCSI_I2C_RD_BUFF[2] & 0x01))	// region0invalid(bit6) & region0eepromerr(bit8)
        {
        	xNewRegPointer = 0;
        	xNewRegStart = 0x0800;
        	xOldRegPointer = 0x0400;
        	xOldRegStart = 0x4400;
        	xAppConfigOffset = LowAppConfigOffset;
        }
        else
        {
        	xNewRegPointer = 0x0400;
        	xNewRegStart = 0x4400;
        	xOldRegPointer = 0;
        	xOldRegStart = 0x0800;
        	xAppConfigOffset = HighAppConfigOffset;
        }
        xAPP_PD_UpdStepFinish = 0xA1;
    }
    else
    {
    	return FAIL;
    }
    return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_Write_FLrd
 * @function - pd1_ti_all_app_Write_FLem
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
uint8_t pd1_ti_app_Write_FLrd(uint16_t point,uint16_t value)
{
	if (xTIFW_CMD_Step == 0)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		xUCSI_I2C_WR_BUFF[1] = 0x04;  //uint8_t count
		xUCSI_I2C_WR_BUFF[2] = (point&0xFF);  
		xUCSI_I2C_WR_BUFF[3] = (point>>8);
		xUCSI_I2C_WR_BUFF[4] = 0x00;  
		xUCSI_I2C_WR_BUFF[5] = 0x00;
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	6,
	    //                    	0,
	    //                    	&xUCSI_I2C_RD_BUFF[0],
	    //                  		0))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,6,0,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			xTIFW_CMD_Step++;
		}
	    return 0;
	}
	if (xTIFW_CMD_Step == 1)
    {
		if (pd_ti_send_4cc(_4CC_FLrd))
		{
			xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 2)
    {
	  	if ( pd_ti_check_CMD1())
	 	{
	 		xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 3)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	1,
	    //                     	0,
	    //                     	&xUCSI_I2C_RD_BUFF[0],
	    //                      	5))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,5,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			;
		}
		xTIFW_CMD_Step++;
		return 0;
	}
	if (xTIFW_CMD_Step == 4)
    {
	    if (xUCSI_I2C_RD_BUFF[2] == (value>>8))	// only check the first uint8_t
	    {
			xTIFW_CMD_Step = 0;
			return 1;
		}
		xTIFW_CMD_Step = 0;
		return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_all_app_Write_FLad
 * @function - pd1_ti_all_Write_FLad
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
uint8_t pd1_ti_app_Write_FLad(uint16_t point)
{
	if (xTIFW_CMD_Step == 0)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		xUCSI_I2C_WR_BUFF[1] = 0x04;  //uint8_t count
		xUCSI_I2C_WR_BUFF[2] = (point&0xFF);  
		xUCSI_I2C_WR_BUFF[3] = (point>>8);
		xUCSI_I2C_WR_BUFF[4] = 0x00;  
		xUCSI_I2C_WR_BUFF[5] = 0x00;
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	6,
	    //                    	0,
	    //                    	&xUCSI_I2C_RD_BUFF[0],
	    //                  		0))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,6,0,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			xTIFW_CMD_Step++;
		}
	    return 0;
	}
	if (xTIFW_CMD_Step == 1)
    {
		if (pd_ti_send_4cc(_4CC_FLad))
		{
			xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 2)
    {
	  	if ( pd_ti_check_CMD1())
	 	{
	 		xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 3)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	1,
	    //                     	0,
	    //                     	&xUCSI_I2C_RD_BUFF[0],
	    //                      	2))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,2,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			;
		}
		xTIFW_CMD_Step++;
		return 0;
	}
	if (xTIFW_CMD_Step == 4)
    {
	    if (xUCSI_I2C_RD_BUFF[1] == 0)	// only check the first uint8_t
	    {
			xTIFW_CMD_Step = 0;
			return 1;
		}
		xTIFW_CMD_Step = 0;
		return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_Write_FLwd
 * @function - pd1_ti_app_Write_FLwd
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
uint8_t pd1_ti_app_Write_FLwd(uint16_t value)
{
	if (xTIFW_CMD_Step == 0)
    {
    	xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
    	xUCSI_I2C_WR_BUFF[1] = 0x04;  //uint8_t count
    	xUCSI_I2C_WR_BUFF[2] = (value & 0xFF);
    	xUCSI_I2C_WR_BUFF[3] = (value>>8);
    	xUCSI_I2C_WR_BUFF[4] = 0x00;
    	xUCSI_I2C_WR_BUFF[5] = 0x00;
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	6,
	    //                    	0,
	    //                    	&xUCSI_I2C_RD_BUFF[0],
	    //                  		0))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,6,0,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			xTIFW_CMD_Step++;
		}
	    return 0;
	}
	if (xTIFW_CMD_Step == 1)
    {
		if (pd_ti_send_4cc(_4CC_FLwd))
		{
			xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 2)
    {
	  	if ( pd_ti_check_CMD1())
	 	{
	 		xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 3)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	1,
	    //                     	0,
	    //                     	&xUCSI_I2C_RD_BUFF[0],
	    //                      	2))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,2,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			;
		}
		xTIFW_CMD_Step++;
		return 0;
	}
	if (xTIFW_CMD_Step == 4)
    {
	    if (xUCSI_I2C_RD_BUFF[1] == 0)	// only check the first uint8_t
	    {
			xTIFW_CMD_Step = 0;
			return 1;
		}
		xTIFW_CMD_Step = 0;
		return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_Write_FLvy
 * @function - pd1_ti_app_Write_FLwd
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     - 
 */
uint8_t pd1_ti_app_Write_FLvy(uint16_t point)
{
	if (xTIFW_CMD_Step == 0)
    {
    	xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
    	xUCSI_I2C_WR_BUFF[1] = 0x04;  //uint8_t count
    	xUCSI_I2C_WR_BUFF[2] = (point&0xFF);  
		xUCSI_I2C_WR_BUFF[3] = (point>>8);
		xUCSI_I2C_WR_BUFF[4] = 0x00;  
		xUCSI_I2C_WR_BUFF[5] = 0x00;
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						xUCSI_I2C_WR_BUFF,
	    //                    	6,
	    //                    	0,
	    //                    	&xUCSI_I2C_RD_BUFF[0],
	    //                  		0))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,6,0,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			xTIFW_CMD_Step++;
		}
	    return 0;
	}
	if (xTIFW_CMD_Step == 1)
    {
		if (pd_ti_send_4cc(_4CC_FLvy))
		{
			xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 2)
    {
	  	if ( pd_ti_check_CMD1())
	 	{
	 		xTIFW_CMD_Step++;
		}
		return 0;
	}
	if (xTIFW_CMD_Step == 3)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	1,
	    //                     	0,
	    //                     	&xUCSI_I2C_RD_BUFF[0],
	    //                      	2))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,2,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			;
		}
		xTIFW_CMD_Step++;
		return 0;
	}
	if (xTIFW_CMD_Step == 4)
    {
	    if (xUCSI_I2C_RD_BUFF[1] == 0)	// only check the first uint8_t
	    {
			xTIFW_CMD_Step = 0;
			xAPP_PD_UpdStepFinish = 0xA1;
			return 1;
		}
		xTIFW_CMD_Step = 0;
		return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_WriteRegionPointer
 * @function - pd1_ti_app_WriteRegionPointer
 * @Upstream - By Call
 * @input    -
 * @return   -
 * @note     -
 */
void pd1_ti_app_WriteRegionPointer(uint16_t point, uint16_t value)
{
	switch(xTIFW_Erase_Step)
	{
		case 0:
			if (pd1_ti_app_Write_FLad(point))
		    {
				xTIFW_Erase_Step++;
			    return;
			}
			break;
		case 1:
			if (pd1_ti_app_Write_FLwd(value))
		    {
		    	xTIFW_Erase_Step++;
				return;
			}
			break;
		case 2:
			if (pd1_ti_app_Write_FLrd(point,value))
		    {
			  	xAPP_PD_UpdStepFinish = 0xA1;
			  	xTIFW_Erase_Step = 0;
				return;
			}
			break;
		default:
			break;
	}
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_erase_new_point
 * @function - pd1_ti_app_erase_new_point
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_erase_new_point(void)
{
	pd1_ti_app_WriteRegionPointer(xNewRegPointer,0);
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_erase_new_offset
 * @function - pd1_ti_app_erase_new_offset
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_erase_new_offset(void)
{
	pd1_ti_app_WriteRegionPointer(xAppConfigOffset,0);
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_set_address
 * @function - pd1_ti_app_set_address
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_set_address(void)
{
	if(pd1_ti_app_Write_FLad(xNewRegStart))
	{
		xAPP_PD_UpdStepFinish = 0xA1;
	}
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_write_bin
 * @function - pd1_ti_app_write_bin
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_write_bin(void)
{
	if (xTIFW_CMD_Step == 0)
    {
    	xAPP_BIN_Buffer[0] = 0x09;  //DATA1
    	xAPP_BIN_Buffer[1] = 0x20;  //uint8_t count
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xAPP_BIN_Buffer[0],
	    //                    	34,
	    //                    	0,
	    //                    	&xUCSI_I2C_RD_BUFF[0],
	    //                  		0))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,34,0,&xAPP_BIN_Buffer[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			xTIFW_CMD_Step++;
		}
	    return;
	}
	if (xTIFW_CMD_Step == 1)
    {
		if (pd_ti_send_4cc(_4CC_FLwd))
		{
			xTIFW_CMD_Step++;
		}
		return;
	}
	if (xTIFW_CMD_Step == 2)
    {
	  	if ( pd_ti_check_CMD1())
	 	{
	 		xTIFW_CMD_Step++;
		}
		return;
	}
	if (xTIFW_CMD_Step == 3)
    {
		xUCSI_I2C_WR_BUFF[0] = 0x09;  //DATA1
		//if (TI_PD_WrToRdStream(TI6599x_ADDR1,
		//						&xUCSI_I2C_WR_BUFF[0],
	    //                    	1,
	    //                     	0,
	    //                     	&xUCSI_I2C_RD_BUFF[0],
	    //                      	2))
		if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,2,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
		{
			;
		}
		xTIFW_CMD_Step++;
		return;
	}
	if (xTIFW_CMD_Step == 4)
    {
	    if (xUCSI_I2C_RD_BUFF[1] == 0)	// only check the first uint8_t
	    {
			xTIFW_CMD_Step = 0;
			xAPP_PD_UpdStepFinish = 0xA1;
			return;
		}
		xTIFW_CMD_Step = 0;
		return;
	}
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_verify
 * @function - pd1_ti_app_verify
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_verify(void)
{
	if(pd1_ti_app_Write_FLvy(xNewRegStart))
	{
		xAPP_PD_UpdStepFinish = 0xA1;
	}
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_restore_new_point
 * @function - pd1_ti_app_restore_new_point
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_restore_new_point(void)
{
	pd1_ti_app_WriteRegionPointer(xNewRegPointer,xNewRegStart);
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_erase_old_point
 * @function - pd1_ti_app_erase_old_point
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_erase_old_point(void)
{
	pd1_ti_app_WriteRegionPointer(xOldRegPointer,0);
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_recovery
 * @function - pd1_ti_app_recovery
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_recovery(void)
{
	TI_FirmwareUpdate();
}
/*-----------------------------------------------------------------------------
 * @subroutine - pd1_ti_app_reboot
 * @function - pd1_ti_app_reboot
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void pd1_ti_app_reboot(void)
{
    if (pd_ti_send_4cc(_4CC_GAID))	// Reset
	{
		//DelayXms(250);
		_Delay_1ms(250);
		xAPP_PD_UpdStepFinish = 0xA1;
		//CLEAR_MASK(EC_Flag5, TI_PD_Flash); //981004-220208-A
	}
}

#if SUPPORT_TI_PD_APP_UPDATE
/*-----------------------------------------------------------------------------
 * @subroutine - service_ti_pd
 * @function - service_ti_pd
 * @upstream - ...
 * @input    - ...
 * @return   - ...
 * @note     - ...
 */
void service_app_update_ti_pd(void)
{
    switch(xAPP_PD_UpdStep)
    {
        case 0:
            xAPP_PD_EnterUpdate = 0xA0; //Ack tp App
            xAPP_PD_UpdStepFinish = 0xA1;
            xTIFW_Step = 0; //981004-220615-A
			ENABLE_PD_Step = 0; //981004-220615-A
            xTIFW_Erase_Step = 0;
            xTIFW_CMD_Step = 0;
            break;
        case 1:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_read_Ouid();
            }
            break;
        case 2:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_boot_status();
            }
            break;
        case 3:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_erase_new_point();
            }
            break;
        case 4:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_set_address();
            }
            break;
        case 5:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_write_bin();
            }
            break;
        case 6:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_verify();
            }
            break;
        case 7:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_restore_new_point();
            }
            break;
        case 8:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_erase_old_point();
            }
            break;
        case 9:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_reboot();
            }
            break;
        case 10:
            if (xAPP_PD_UpdStepFinish == 0)
            {
                pd1_ti_app_erase_new_offset();
            }
			break;
        case 11:
        	if (xAPP_PD_UpdStepFinish == 0)
            {
            	pd1_ti_app_recovery();
            }
			break;
        default:
            break;
    }
}
#endif // SUPPORT_TI_PD_APP_UPDATE
//981004-220208-A-E

//-----------------------------------------------------------------------------
// Init_Ti_SmartAmp: transmit_registers
//-----------------------------------------------------------------------------
void Init_Ti_SmartAmp(void)
{
	uint16_t	windex = 0x20;
    uint8_t 	i, command, param, length;
	uint8_t _TIAmp_ADDH = 0x01;
    uint8_t _TIAmp_ADDM = 0x81;
    uint8_t _TIAmp_ADDL = 0x00;
    
   /// SCLKTS_E = 0x12;   /* 0x11:50KHz,0x12:100KHz,0x13:400KHz */	
	while(1)
	{
		if (windex == 0x20)
		{
			///ECIndirectFastRead(_TIAmp_ADDH, _TIAmp_ADDM, _TIAmp_ADDL, SPI_selection_internal, 32, &xUCSI_I2C_WR_BUFF[0]);
			_TIAmp_ADDL += 32;
	    	if(_TIAmp_ADDL == 0x00)
	    	{
	    		_TIAmp_ADDM++;				
	    	}			
			windex = 0;
		}
		command = xUCSI_I2C_WR_BUFF[windex];
		param = xUCSI_I2C_WR_BUFF[windex+1];	
		windex += 2;        		
		/* check 0xfe,0xfe End Mark*/	
		if ((command == 0xfe) && (param == 0xfe))
		{			
			break;
		}
		if (command == CFG_META_SWITCH)
		{
			// Used in legacy applications. Ignored here.
		}		
		else if (command == CFG_META_DELAY)
		{
			//delay(r[i].param);
			//Delay1MS(param);
			_Delay_1ms(param);			
		}

		else if (command == CFG_META_BURST)
		{
			//i2c_write((unsigned char *)&r[i+1], r[i].param);
            //i += (r[i].param / 2) + 1;
            length = param;
            for (i = 0; i < param; i+=2)
            { 
		        SPIBuffer[i] = xUCSI_I2C_WR_BUFF[windex];
		        SPIBuffer[i+1] = xUCSI_I2C_WR_BUFF[windex+1];
                windex += 2;			
            }
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[0],
            //                      length,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,length,0,SPIBuffer,SPIBuffer))
			{
				;
			}
            else
            {
				;
			}				
		}	
		else
		{
			//i2c_write((unsigned char *)&r[i], 2);
            SPIBuffer[0] = command;
            SPIBuffer[1] = param;
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[0],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,length,0,SPIBuffer,&SPIBuffer[80]))
								  {
									  ;
								  }	
            else
            {
				;
			}				
		}	
	}
}

void Read_Ti_SmartAmp(void)
{
	        SPIBuffer[0] = 0x00;
			SPIBuffer[1] = 0x00;
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[0],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,2,0,SPIBuffer,&SPIBuffer[80]))
								  {
									  ;
								  }
		    _Delay_1ms(10);//Delay1MS(10);						   
			SPIBuffer[2] = 0x7F;
			SPIBuffer[3] = 0x8C;					  
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[2],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,2,0,&SPIBuffer[2],&SPIBuffer[80]))
								  {
									  ;
								  }	
            _Delay_1ms(10);//Delay1MS(10);								  
            SPIBuffer[4] = 0x7D;           
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[4],
            //                      1,
            //                      0,
            //                      &SPIBuffer[5], //XOR => 0XB2
            //                      1))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,1,1,&SPIBuffer[4],&SPIBuffer[5]))
								  {
									 ;
								  }	
            else
            {
				;
			}
			_Delay_1ms(10);//Delay1MS(10);
			SPIBuffer[6] = 0x7E;           
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[6],
            //                      1,
            //                      0,
            //                      &SPIBuffer[7], //CRC => 0X1E
            //                      1))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,1,1,&SPIBuffer[6],&SPIBuffer[7]))
								  {
									;
								  } 
#if 0								  
			Delay1MS(10);
			SPIBuffer[4] = 0x71;           
            if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
                                  &SPIBuffer[4],
                                  1,
                                  0,
                                  &SPIBuffer[5],
                                  1))
								  {
									  ;
								  }
            Delay1MS(10);
			SPIBuffer[6] = 0x72;           
            if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
                                  &SPIBuffer[6],
                                  1,
                                  0,
                                  &SPIBuffer[7],
                                  1))
								  {
									  ;
								  }
			Delay1MS(10);
			SPIBuffer[8] = 0x73;           
            if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
                                  &SPIBuffer[8],
                                  1,
                                  0,
                                  &SPIBuffer[9],
                                  1))
								  {
									  ;
								  }					   
 #endif           					  
}

void Clear_Ti_SmartAmp(void)
{
	        SPIBuffer[0] = 0x00;
			SPIBuffer[1] = 0x00;
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[0],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,2,0,&SPIBuffer[0],&SPIBuffer[80]))
								  {
									  ;
								  }
		    _Delay_1ms(10);//Delay1MS(10);						   
			SPIBuffer[2] = 0x7F;
			SPIBuffer[3] = 0x8C;					  
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[2],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,2,0,&SPIBuffer[2],&SPIBuffer[80]))
								  {
									  ;
								  }	
            _Delay_1ms(10);//Delay1MS(10);								  
            SPIBuffer[4] = 0x7D;
            SPIBuffer[5] = 0x00; 			
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[4],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,2,0,&SPIBuffer[4],&SPIBuffer[80]))
								  {
									 ;
								  }	
            else
            {
				;
			}
			_Delay_1ms(10);//Delay1MS(10);	
			SPIBuffer[6] = 0x7E; 
            SPIBuffer[7] = 0x00; 			
            //if (I2C_CH5_WrToRdStream(_TISMAMP_ADDR,
            //                      &SPIBuffer[6],
            //                      2,
            //                      0,
            //                      &SPIBuffer[0x80],
            //                      0))
			if(I2C_Protocol_SMART_AMP(3,_TISMAMP_ADDR,2,0,&SPIBuffer[6],&SPIBuffer[80]))
								  {
									 ;
								  } 
}
void Display_Mode(void)
{
    uint8_t Count;
   
	pd_i2c_buffer_clear(); 	
    xUCSI_I2C_WR_BUFF[0] = _TIPD_DATA_STATUS; //0x5F //Read 5 uint8_ts
    //if (TI_PD_WrToRdStream(TI6599x_ADDR1,
    //                       &xUCSI_I2C_WR_BUFF[0],
    //                       1,
    //                       0,
    //                       &xUCSI_I2C_RD_BUFF[0],
    //                       6))
	if(I2C_Protocol_PD(3,TI6599x_ADDR1,1,6,&xUCSI_I2C_WR_BUFF[0],&xUCSI_I2C_RD_BUFF[0]))
    {
        for (Count = 0; Count< 5 ; Count++)
    	{
    		xDATA_STS[Count] = xUCSI_I2C_RD_BUFF[Count+1];           			
    	}
    }
    else
    {		
    	;
    }
	if ((xDATA_STS[1] & 0x01) != 0x00 ) //uint8_t2 bit0
	{
		BIT_SET(POWER_FLAG1, dp_attached); //0X201 BIT5		
	}
    else
	{
		BIT_CLR(POWER_FLAG1, dp_attached); //0X201 BIT5		
	}	     		
}