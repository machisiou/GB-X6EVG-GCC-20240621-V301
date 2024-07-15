#include "hal/I2C.h"
#include "chip/rts5911/RTS5911.h"
#include "system/memory.h"
uint32_t g_i2c_slave_0_byte_write_index;
uint32_t g_i2c_slave_1_byte_write_index;
uint32_t g_i2c_slave_2_byte_write_index;
uint32_t g_i2c_slave_0_byte_read_index;
uint32_t g_i2c_slave_1_byte_read_index;
uint32_t g_i2c_slave_2_byte_read_index;

uint8_t *g_i2c_slave_2_byte_write_buffer_pointer;

/******************************************************************************/
/** I2C Initial
 * Channel - I2C Channel 0~7
 * Frequency - 0:100KHz, 1:400KHz, 2: 1MHz
 * Mode - 0:Master, 1:Slave
 * SlvAddr - Slave address(Only used for Slave mode)
 * return None
*******************************************************************************/
void I2C_Initial(uint8_t Channel, uint8_t Frequency, uint8_t Mode, uint8_t SlvAddr)
{
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));
	if (Mode == 0) {
		Ptr->ENABLE = 0;
		Ptr->CON_b.SLVDISABLE = 1;
		Ptr->CON_b.RESTREN = 1;
		Ptr->CON_b.MST10BIT = 0;
		Ptr->CON_b.SLV10BIT = 0;
		Ptr->CON_b.MATSER = 1;
		Ptr->CON_b.BUSCLRCTRL = 1;				/* Enable Bus clear feature */
		Ptr->SCLLOWTO = 0x0016E360;				/* Set time out as 30ms(IC_CLK =50MHz) */
		Ptr->SDALOWTO = 0x0016E360;				/* Set time out as 30ms */
		if (Frequency == _100KHz) {				/* 100KHz */
			Ptr->CON_b.SPEED = 1;
			Ptr->SCLHCNT = 0x000000DA;
			Ptr->SCLLCNT = 0x000000FE;
			Ptr->SPKLEN = 0x00000003;
			Ptr->SDAHOLD = 0x00090009;
//			Ptr->SCLHCNT = 0x000001D5;
//			Ptr->SCLLCNT = 0x000001D0;
//			Ptr->SPKLEN = 0x00000003;
//			Ptr->SDAHOLD = 0x00050000;
		}
		else if (Frequency == _400KHz) {		/* 400KHz */
			Ptr->CON_b.SPEED = 2;
			Ptr->FSSCLHCNT = 0x00000020;
			Ptr->FSSCLLCNT = 0x00000044;
			Ptr->SPKLEN = 0x00000002;
			Ptr->SDAHOLD = 0x00090009;
		}
		else if (Frequency == _1MHz) {			/* 1MHz */
			Ptr->CON_b.SPEED = 2;
			Ptr->FSSCLHCNT = 0x00000009;
			Ptr->FSSCLLCNT = 0x0000001A;
			Ptr->SPKLEN = 0x00000003;
			Ptr->SDAHOLD = 0x00050005;
		}
		Ptr->RXTL = 0;
		Ptr->TXTL = 0;
	}
	else if (Mode == 1) {
		Ptr->ENABLE = 0x00000000;
		Ptr->SAR = (uint32_t)SlvAddr >> 1;
		Ptr->CON_b.SLVDISABLE = 0;
		Ptr->CON_b.RESTREN = 1;
		Ptr->CON_b.MST10BIT = 0;
		Ptr->CON_b.SLV10BIT = 0;
		Ptr->CON_b.SPEED = 1;
		Ptr->CON_b.MATSER = 0;
		Ptr->CON_b.STPDET = 1;
		if (Frequency == _100KHz) {				/* 100KHz */
			Ptr->SCLHCNT = 0x00000071;
			Ptr->SCLLCNT = 0x0000007E;
		}
		else if (Frequency == _400KHz) {		/* 400KHz */
			Ptr->SCLHCNT = 0x00000010;
			Ptr->SCLLCNT = 0x00000026;
		}
		else if (Frequency == _1MHz) {			/* 1MHz */
			Ptr->SCLHCNT = 0x00000001;
			Ptr->SCLLCNT = 0x0000000F;
		}
		Ptr->SDAHOLD = 5;
		Ptr->INTMASK = 0x0000FFFF;
		Ptr->RXTL = 0;
		Ptr->TXTL = 0;
		Ptr->ENABLE = 0x00000001;
	}
}

/******************************************************************************/
/** I2C SMBus protocol
 * Channel - I2C Channel 0~7
 * Protocol -
 * 0:Quick Command Write, 
 * 1:Quick Command Read, 
 * 2:Send Byte, 
 * 3:Receive Byte, 
 * 4:Write Byte, 
 * 5:Read Byte, 
 * 6:Write Word, 
 * 7:Read Word, 
 * 8:Write Block, 
 * 9:Read Block 
 * Addr - SMBus Device Address(8 bits)
 * DatCnt - Data Count (Only used for Write Block)
 * WDatBuf - The Data write to Slave device
 * RDatBuf - The Data read from Slave device
 * return None
*******************************************************************************/
uint8_t I2C_SMBusModProtocol(uint8_t Channel, uint8_t Protocol, uint8_t Addr, uint8_t DatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf)
{
	uint8_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));
	if(Protocol == QuickCommandWr) {
		Ptr->TAR = ((uint32_t)Addr >> 1
		| ((uint32_t) 0x08 << 8)
		| ((uint32_t) 0x01 << 8));								/* Address Set BIT 11 & 16 */

		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1; */
		Ptr->DATACMD = 0x00000200;								/* with stop bit */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == QuickCommandRd) {
		Ptr->TAR = ((uint32_t)Addr >> 1
		| ((uint32_t) 0x08 << 8)
		| ((uint32_t) 0x01 << 8));								/* Address Set BIT 11 & 16 */

		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1; */
		Ptr->DATACMD = 0x00000300;								/* with stop bit */
		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == SendByte) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1; */
		Ptr->DATACMD = ((uint32_t) *(WDatBuf)					/* Byte */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		while((Ptr->STATUS & 0x00000020) != 0);	
		Ptr->ENABLE = 0x00000000;   							/* ic_enable = 0 */
	}
	else if(Protocol == ReceiveByte) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1; */
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop */

		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}
		*(RDatBuf) = Ptr->DATACMD_b.DATA;
		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;   							/* ic_enable = 0 */
	}
	else if(Protocol == WriteByte) {
		Ptr->TAR = (uint32_t)Addr>> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+1)					/* Byte1 */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0; */
	}
	else if(Protocol == ReadByte) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}

		}

		*(RDatBuf) = Ptr->DATACMD_b.DATA;
		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == WriteWord) {
		Ptr->TAR = (uint32_t)Addr >> 1; 						/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+1) & 0x000000FF);	/* Byte1 */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+2)					/* Byte2 */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == ReadWord) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */

		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

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

		*RDatBuf = Ptr->DATACMD_b.DATA;
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop */

		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		*(RDatBuf+1) = Ptr->DATACMD_b.DATA;
		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == WriteBlock) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		Ptr->DATACMD = (uint32_t) DatCnt;						/* Data Count */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		for(i=0;i<(DatCnt-1);i++) {
			Ptr->DATACMD = ((uint32_t) *(WDatBuf+1+i) & 0x000000FF);	/* N-1 Bytes */
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					return FAIL;
				}
			}
		}

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+1+i)				/* Byte N */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == ReadBlock) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				return FAIL;
			}
		}

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

		*RDatBuf = Ptr->DATACMD_b.DATA;

		for(i=0;i<*(RDatBuf)-1;i++) {
			Ptr->DATACMD_b.CMD = 1;								/* read */
			while(1) {											/* Check if IC_RX_FULL */
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
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop (Byte N) */

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
		while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}

	return SUCCESS;
}

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
uint8_t I2C_Protocol(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf)
{
	uint8_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

	Ptr->TAR = (uint8_t)(Addr >> 1);								/* Setup target address */
	Ptr->ENABLE = 0x00000001;										/* Enable I2C engine */
	if(WDatCnt != 0) {
		for (i = 0; i < (WDatCnt - 1); i++) {						/* Push data */
			Ptr->DATACMD = ((uint32_t)WDatBuf[i] & 0x000000FF);
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
			Ptr->DATACMD = ((uint32_t)WDatBuf[i] & 0x000000FF);
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
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);						/* Read+Stop (Byte N) */

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

/******************************************************************************/
/** I2C_Slave_ByteRead
 * Channel - I2C Channel 0~7
 * RDatBuf - The Data read from Master
 * return None
*******************************************************************************/
uint8_t I2C_Slave_ByteRead (uint8_t Channel, uint8_t *RDatBuf)
{
	uint32_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

	if(Ptr->INTSTAT == 0X00000004) {								/* Check if RX Full */
		i = Ptr->CLRINT;											/* Interrupt Read Clear */
		*RDatBuf = Ptr->DATACMD_b.DATA;
		return SUCCESS;
	}
	return FAIL;
}

/******************************************************************************/
/** I2C_Slave_ByteWrite
 * Channel - I2C Channel 0~7
 * WDatBuf - The Data write to Master
 * return None
*******************************************************************************/
uint8_t I2C_Slave_ByteWrite (uint8_t Channel, uint8_t *WDatBuf)
{
	uint32_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

	if(Ptr->INTSTAT == 0X00000020) {								/* Check if RD_REQ */
		if((Ptr->INTSTAT & 0x00000040) != 0)
			i = Ptr->CLRTXABRT;										/* Interrupt Read Clear */
		Ptr->DATACMD = ((uint32_t) *WDatBuf
		| ((uint32_t) 0x00 << 8));
		i = Ptr->CLRRDREQ;											/* Interrupt Read Clear */
		return SUCCESS;
	}
	return FAIL;
}

 /******************************************************************************/
 /** I2C channel 2 Slave Variables reset
  * return None
 *******************************************************************************/
void I2C_Slave_2_Variables_Reset(void)
{
	/* reset byte write index for slave c. */
	g_i2c_slave_2_byte_write_index = 0x00;

	/* reset byte read index for slave c. */
	g_i2c_slave_2_byte_read_index = 0x00;
}

void I2C_Reset_Handler_Isr(uint8_t Channel)
{
	uint32_t i;
	I2C_Type* Ptr;
	// Timeout process
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));
	if(Ptr->TXABRTSRC_b.SDASTUCKLOW) {								/* Check if SMBus DAT time out occur */
		Ptr->ENABLE_b.SMBCLKRST = 1;								/* Reset SMBClk to reset device */
		while(Ptr->ENABLE_b.SMBCLKRST);								/* Finish Reset will clear */
		i = Ptr->CLRTXABRT;
	}
	else if(Ptr->INTSTAT_b.SCLSTUCKLOW) {
		Ptr->ENABLE_b.ABORT = 1;									/* Abort Tranfer */
		while(Ptr->ENABLE_b.ABORT);									/* Finish Abort will clear */
	}
}

uint8_t I2C_Timeout_Handler(I2C_Type* Ptr)
{
	uint32_t i;
	if(Ptr->TXABRTSRC_b.SDASTUCKLOW) {								/* Check if SMBus DAT time out occur */
		Ptr->ENABLE_b.SMBCLKRST = 1;								/* Reset SMBClk to reset device */
		while(Ptr->ENABLE_b.SMBCLKRST);								/* Finish Reset will clear */
		i = Ptr->CLRTXABRT;											/* Read to clear TX ABORT*/
		return 1;
	}
	else if(Ptr->RAWINTSTAT_b.SCLSTUCKLOW) {
		Ptr->ENABLE_b.ABORT = 1;									/* Abort Tranfer */
		while(Ptr->ENABLE_b.ABORT);									/* Finish Abort will clear */
		return 1;
	}
	else if(Ptr->TXABRTSRC_b.ADDR7BNACK) {
		i = Ptr->CLRTXABRT;										/* Read to clear TX ABORT*/
		return 1;
	}
	else if((Ptr->RAWINTSTAT & 0x00000240) == 0x00000240) {		/* Check if TX ABORT and Detect stop */
		return 1;
	}
	//else if(SMBus26ms_check()){
	//	return 0;
	//}
	else{
		//printf(" Waiting time\n");
		return 0;
	}	
}

/******************************************************************************/
/** I2C protocol W
 * Channel - I2C Channel 0~7
 * Addr - SMBus Device Address(8 bits)
 * WDatCnt - Write Data Count
 * WDatBuf - The Data write to Slave device
 * return None
*******************************************************************************/
uint8_t I2C_ProtocolFIFO_W(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t *WDatBuf)
{
	uint8_t i;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

	Ptr->TXTL = (WDatCnt -1);
	Ptr->TAR = (uint8_t)(Addr >> 1);								/* Setup target address */
	Ptr->ENABLE = 0x00000001;										/* Enable I2C engine */

	for (i = 0; i < (WDatCnt - 1); i++) {							/* Push data */
			Ptr->DATACMD = (uint32_t)WDatBuf[i];
		}

	while(1) {
		if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
			break;
		else if(I2C_Timeout_Handler(Ptr)) {
			Ptr->ENABLE = 0x00000000;
			return FAIL;
			}
		}

	Ptr->DATACMD = (uint32_t)(WDatBuf[i] | (0x01 << 9));	/* Push last data with stop */
	while(1) {
		volatile uint32_t interr = Ptr->RAWINTSTAT;
		if((interr & 0x00000050) == 0x00000010)
			break;
		else if(I2C_Timeout_Handler(Ptr)) {
			Ptr->ENABLE = 0x00000000;
			return FAIL;
		}
	}
	while((Ptr->STATUS & 0x00000020) != 0);					/* Wait until idle */

	Ptr->ENABLE = 0x00000000;									/* Disable I2C engine */
	return SUCCESS;
}

uint8_t I2C_ProtocolFIFO_R(uint8_t Channel, uint8_t Addr, uint8_t RDatCnt, uint8_t *RDatBuf)
{
	uint8_t i = 0;
	I2C_Type* Ptr;
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));
	Ptr->RXTL = (RDatCnt -1);
	Ptr->TAR = (uint8_t)(Addr >> 1);
	Ptr->ENABLE = 0x00000001;

	for (i = 0; i < (RDatCnt - 1); i++) {	/* Push read command */
		Ptr->DATACMD_b.CMD = 1;
	}

	while(1) {
		if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
			break;
		else if(I2C_Timeout_Handler(Ptr)) {
			Ptr->ENABLE = 0x00000000;
			return FAIL;
			}
	}

	Ptr->DATACMD = ((uint32_t) 0x03 << 8);

	while(1) {
		volatile uint32_t interr = Ptr->RAWINTSTAT;
		if((interr & 0x00000050) == 0x00000010)
			break;
		else if(I2C_Timeout_Handler(Ptr)) {
			Ptr->ENABLE = 0x00000000;
			return FAIL;
		}
	}
	
	while((Ptr->STATUS & 0x00000020) != 0);					/* Wait until idle */
	
	while(1) {												/* Check if IC_RX_FULL */
		if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
			break;
		}
		else if(I2C_Timeout_Handler(Ptr)) {
			Ptr->ENABLE = 0x00000000;
			return FAIL;
		}
	}

	for(i = 0; i < RDatCnt; i++)	/* Read data */
	{
		*(RDatBuf + i) = (uint8_t)Ptr->DATACMD_b.DATA;
	}

	Ptr->ENABLE = 0x00000000;
	return SUCCESS;
}

uint8_t SMBUS_RW_BLK(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint32_t *var)
{
	uint8_t test_tx_buf[5];
	uint8_t test_rx_buf[5];
	if(Protocol == WriteBlock)
	{
		test_tx_buf[0] = Cmd;
		test_tx_buf[1] = (uint8_t)*var;
		test_tx_buf[2] = (uint8_t)*var>>8;
		test_tx_buf[3] = (uint8_t)*var>>16;
		test_tx_buf[4] = *var>>24;

		
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,NULL))
		{
			return SUCCESS;
		}
			return FAIL;
	}
	else if(Protocol == ReadBlock)
	{
		test_tx_buf[0] = Cmd;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,test_rx_buf))
		{
			*var = (uint32_t)((test_rx_buf[4]<<24)+(test_rx_buf[3]<<16)+(test_rx_buf[2]<<8)+test_rx_buf[1]);
			BAT_DEVNAME = (uint32_t)*var;
			//BAT_DEVNAME2 = (uint16_t)(*var>>16);
			return SUCCESS;
		}
		return FAIL;
		
	}
	return SUCCESS;
}

uint8_t SMBUS_RW_W(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint16_t *var)
{
	uint8_t test_tx_buf[3];
	uint8_t test_rx_buf[3];
	if(Protocol == WriteWord)
	{
		test_tx_buf[0] = Cmd;
		test_tx_buf[1] = *var>>8;
		test_tx_buf[2] = (uint8_t)*var;
		
		
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,NULL))
		{
			return SUCCESS;
		}
			return FAIL;
	}
	else if(Protocol == ReadWord)
	{
		test_tx_buf[0] = Cmd;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,test_rx_buf))
		{
			*var = (uint16_t)((test_rx_buf[1]<<8)+test_rx_buf[0]);
			return SUCCESS;
		}
		return FAIL;
		
	}
	return SUCCESS;
}

uint8_t SMBUS_RW_B(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var)
{
	uint8_t test_tx_buf[3];
	uint8_t test_rx_buf[3];
	if(Protocol == WriteByte)
	{
		test_tx_buf[0] = Cmd;
		test_tx_buf[1] = *var;

		
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,NULL))
		{
			return SUCCESS;
		}
			return FAIL;
	}
	else if(Protocol == ReadByte)
	{
		test_tx_buf[0] = Cmd;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,test_rx_buf))
		{
			*var = test_rx_buf[0];
			return SUCCESS;
		}
		return FAIL;
		
	}
	return SUCCESS;
}