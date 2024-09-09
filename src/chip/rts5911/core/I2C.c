#include "hal/I2C.h"
#include "chip/rts5911/RTS5911.h"
#include "oem/crb/Oem_timer.h"
#include "system/Memory.h"
#include "oem/crb/RTK_I2C.h"
uint32_t g_i2c_slave_2_byte_write_index;
uint32_t g_i2c_slave_2_byte_read_index;

uint8_t *g_i2c_slave_2_byte_write_buffer_pointer;
uint8_t *g_i2c_slave_2_byte_read_buffer_pointer;

FUNCT_PTR_V_V g_i2c_slave_2_stop_condition_hook_func;
FUNCT_PTR_V_V g_i2c_slave_2_stop_condition_hook_func_addr2;
FUNCT_PTR_V_V g_i2c_slave_2_timeout_hook_func;

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

/**
 * ****************************************************************************
 * oem init function for I2C slave 2.
 *
 * @return
 *
 * @parameter
 * p_byte_write_buffer, pointer for write buffer
 * p_byte_read_buffer, pointer for read buffer
 * p_stop_condition_func, function pointer for stop condition
 * p_stop_condition_func_addr2, function pointer for stop condition
 *     (address 2 match)
 * p_timeout_func, function pointer for timeout condition
 *
 * @note,
 * 1. To ready all pointer before enable slave channel.
 * 2. all hook function are executed in isr,
 *    please consider the content of oem hook function.
 *
 * ****************************************************************************
 */
void I2C_Slave_2_OEM_Init(uint8_t *p_byte_write_buffer,
			  uint8_t *p_byte_read_buffer,
			  FUNCT_PTR_V_V p_stop_condition_func,
			  FUNCT_PTR_V_V p_stop_condition_func_addr2,
			  FUNCT_PTR_V_V p_timeout_func)
{
	/* to store the address of oem byte write buffer */
	g_i2c_slave_2_byte_write_buffer_pointer = p_byte_write_buffer;

	/* to store the address of oem byte read buffer */
	g_i2c_slave_2_byte_read_buffer_pointer = p_byte_read_buffer;

	/* to store the address of oem hook function for stop condition occurs */
	g_i2c_slave_2_stop_condition_hook_func = p_stop_condition_func;

	/*
	 * to store the address of oem hook function for stop condition occurs
	 * (address 2 match)
	 */
	g_i2c_slave_2_stop_condition_hook_func_addr2 = p_stop_condition_func_addr2;

	/* to store the address of oem hook function for timeout occurs */
	g_i2c_slave_2_timeout_hook_func = p_timeout_func;
}

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
	// puts(__FUNCTION__);
	//uart_write16(UART_I2C_Initial);

	I2C_Type* Ptr;
	UINT32 i;
	if(Channel > 7) {
		//Fault_Record(0x00010100ul);
		//return 0;
	}
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
//			Ptr->SCLHCNT = 0x000000DA;
//			Ptr->SCLLCNT = 0x000000FE;
//			Ptr->SPKLEN = 0x00000003;
//			Ptr->SDAHOLD = 0x00090009;
			Ptr->SCLHCNT = 0x000000D5;
			Ptr->SCLLCNT = 0x00000100;
			Ptr->SPKLEN = 0x00000003;
			Ptr->SDAHOLD = 0x00070005;
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
			Ptr->SCLHCNT = 0x000000DA;
			Ptr->SCLLCNT = 0x000000FE;
			Ptr->SPKLEN = 0x00000003;
			Ptr->SDAHOLD = 0x00090009;
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
		Ptr->CON_b.BUSCLRCTRL = 1;				/* Enable Bus clear feature */
		Ptr->SCLLOWTO = 0x0016E360;				/* Set time out as 30ms(IC_CLK =50MHz) */
		Ptr->SDALOWTO = 0x0016E360;				/* Set time out as 30ms */
		Ptr->INTMASK = 0x00005EEE;
		Ptr->RXTL = 0;
		Ptr->TXTL = 0;
		Ptr->ENABLE = 0x00000001;
		i = I2C2->CLRINT;
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
	// puts(__FUNCTION__);
	//uart_write16(UART_I2C_SMBusModProtocol);

	uint8_t i;
	I2C_Type* Ptr;
	if(Channel > 7) {
		//Fault_Record(0x00010200ul);
		return FAIL;
	}
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

    Ptr->ENABLE = 0x00000000;
	if(Protocol == QuickCommandWr) {
		Ptr->TAR = ((uint32_t)Addr >> 1
		| ((uint32_t) 0x08 << 8)
		| ((uint32_t) 0x01 << 8));								/* Address Set BIT 11 & 16 */

		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1; */
		Ptr->DATACMD = 0x00000200;								/* with stop bit */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010201ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010202ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
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

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010203ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010204ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;   							/* ic_enable = 0 */
	}
	else if(Protocol == ReceiveByte) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1; */
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop */

		SMBus26ms_touch();
		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010205ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		*(RDatBuf) = Ptr->DATACMD_b.DATA;
		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010206ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;   							/* ic_enable = 0 */
	}
	else if(Protocol == WriteByte) {
		Ptr->TAR = (uint32_t)Addr>> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010207ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+1)					/* Byte1 */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010208ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010209ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0; */
	}
	else if(Protocol == ReadByte) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001020Aul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514){
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001020Bul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		*(RDatBuf) = Ptr->DATACMD_b.DATA;
		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001020Cul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == WriteWord) {
		Ptr->TAR = (uint32_t)Addr >> 1; 						/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001020Dul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+1) & 0x000000FF);	/* Byte1 */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001020Eul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+2)					/* Byte2 */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001020Ful);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010210ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == ReadWord) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */

		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		//SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010211ul);
		//		timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		//timer324_SMBus26ms_Setting();

		Ptr->DATACMD_b.CMD = 1;									/* read */

		//SMBus26ms_touch();
		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010212ul);
		//		timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		//timer324_SMBus26ms_Setting();

		*RDatBuf = Ptr->DATACMD_b.DATA;
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop */

		//SMBus26ms_touch();
		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010213ul);
		//		timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		*(RDatBuf+1) = Ptr->DATACMD_b.DATA;
		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010214ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == WriteBlock) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010215ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		Ptr->DATACMD = (uint32_t) DatCnt;						/* Data Count */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010216ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		for(i=0;i<(DatCnt-1);i++) {
			Ptr->DATACMD = ((uint32_t) *(WDatBuf+1+i) & 0x000000FF);	/* N-1 Bytes */
			SMBus26ms_touch();
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x00010217ul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
			}
			timer324_SMBus26ms_Setting();
		}

		Ptr->DATACMD = ((uint32_t) *(WDatBuf+1+i)				/* Byte N */
			| ((uint32_t) 0x02 << 8));							/* with stop bit */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010218ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}

		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010219ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;								/* ic_enable = 0 */
	}
	else if(Protocol == ReadBlock) {
		Ptr->TAR = (uint32_t)Addr >> 1;							/* Address */
		Ptr->ENABLE = 0x00000001;								/* ic_enable = 1 */
		Ptr->DATACMD = ((uint32_t) *WDatBuf & 0x000000FF);		/* Command */

		SMBus26ms_touch();
		while(1) {
			if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
				break;
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001021Aul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		Ptr->DATACMD_b.CMD = 1;									/* read */

		SMBus26ms_touch();
		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001021Bul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
		}
		timer324_SMBus26ms_Setting();

		*RDatBuf = Ptr->DATACMD_b.DATA;

		for(i=0;i<*(RDatBuf)-1;i++) {
			Ptr->DATACMD_b.CMD = 1;								/* read */
			SMBus26ms_touch();
			while(1) {											/* Check if IC_RX_FULL */
				if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
					break;
				}
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x0001021Cul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
			}
			timer324_SMBus26ms_Setting();
			*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		}
		Ptr->DATACMD = ((uint32_t) 0x03 << 8);					/* Read+Stop (Byte N) */

		SMBus26ms_touch();
		while(1) {												/* Check if IC_RX_FULL */
			if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514){
				break;
			}
			else if(I2C_Timeout_Handler(Ptr)) {
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001021Dul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}

		}

		*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x0001021Eul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
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
	// puts(__FUNCTION__);
	//uart_write16(UART_I2C_Protocol);

	uint8_t i;
	I2C_Type* Ptr;
	if(Channel > 7) {
		//Fault_Record(0x00010300ul);
		return FAIL;
	}
	Ptr = (I2C_Type*)((uint32_t)I2C0_BASE + (uint32_t)(Channel * 0x200UL));

    Ptr->ENABLE = 0x00000000;
	Ptr->TAR = (uint8_t)(Addr >> 1);								/* Setup target address */
	Ptr->ENABLE = 0x00000001;										/* Enable I2C engine */
	if(WDatCnt != 0) {
		for (i = 0; i < (WDatCnt - 1); i++) {						/* Push data */
			Ptr->DATACMD = ((uint32_t)WDatBuf[i] & 0x000000FF);
			SMBus26ms_touch();
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x00010301ul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
			}
			timer324_SMBus26ms_Setting();
		}

		if(RDatCnt == 0) {
			Ptr->DATACMD = (uint32_t)(WDatBuf[i] | (0x01 << 9));	/* Push last data with stop */
			SMBus26ms_touch();
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x00010302ul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
			}
			while (1)
			{
				if(SMBus26ms_check()){
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x00010303ul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
				if (((Ptr->STATUS & 0x00000020) == 0))
					break;
			}
			// while((Ptr->STATUS & 0x00000020) != 0);
		}
		else {
			Ptr->DATACMD = ((uint32_t)WDatBuf[i] & 0x000000FF);
			SMBus26ms_touch();
			while(1) {
				if((Ptr->RAWINTSTAT & 0x00000050) == 0x00000010)
					break;
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x00010304ul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
			}
		}
		timer324_SMBus26ms_Setting();
	}

	if(RDatCnt == 0) {
		Ptr->ENABLE = 0x00000000;									/* Disable I2C engine */
	}else {
		//Ptr->DATACMD_b.CMD = 1;									/* read */

		// for(i=0;i<RDatCnt-1;i++) {
		for(i=0;i<RDatCnt;i++) {
			if(i == (RDatCnt-1))
				Ptr->DATACMD = ((uint32_t) 0x03 << 8);				/* Read+Stop (Byte N) */
			else
				Ptr->DATACMD_b.CMD = 1;								/* read */

			SMBus26ms_touch();
			while(1) {												/* Check if IC_RX_FULL */
				if((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) {
					break;
				}
				else if(I2C_Timeout_Handler(Ptr)) {
					Ptr->ENABLE = 0x00000000;
					//Fault_Record(0x00010305ul);
					timer324_SMBus26ms_Setting();
					return FAIL;
				}
			}
			timer324_SMBus26ms_Setting();

			*(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		}

		// Ptr->DATACMD = ((uint32_t) 0x03 << 8);						/* Read+Stop (Byte N) */

		// SMBus26ms_touch();
		// while(1) {													/* Check if IC_RX_FULL */
		// 	if(((Ptr->RAWINTSTAT & 0x00000514) == 0x00000514) && ((Ptr->STATUS & 0x00000020) != 0)) {
		// 		break;
		// 	}
		// 	else if(I2C_Timeout_Handler(Ptr)) {
		// 		Ptr->ENABLE = 0x00000000;
		// 		Fault_Record(0x00010305ul);
		// 		timer324_SMBus26ms_Setting();
		// 		return FAIL;
		// 	}
		// }
		// timer324_SMBus26ms_Setting();

		// *(RDatBuf+i+1) = Ptr->DATACMD_b.DATA;
		while (1)
		{
			if(SMBus26ms_check()){
				Ptr->ENABLE = 0x00000000;
				//Fault_Record(0x00010306ul);
				timer324_SMBus26ms_Setting();
				return FAIL;
			}
			if (((Ptr->STATUS & 0x00000020) == 0))
				break;
		}
		// while((Ptr->STATUS & 0x00000020) != 0);
		Ptr->ENABLE = 0x00000000;									/* ic_enable = 0 */
	}
	timer324_SMBus26ms_Setting();
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
		// while(Ptr->ENABLE_b.SMBCLKRST);								/* Finish Reset will clear */
		i = Ptr->CLRTXABRT;											/* Read to clear TX ABORT*/
		return 1;
	}
	else if(Ptr->RAWINTSTAT_b.SCLSTUCKLOW) {
		Ptr->ENABLE_b.ABORT = 1;									/* Abort Tranfer */
		// while(Ptr->ENABLE_b.ABORT);									/* Finish Abort will clear */
		return 1;
	}
	else if(Ptr->TXABRTSRC_b.ADDR7BNACK) {
		i = Ptr->CLRTXABRT;										/* Read to clear TX ABORT*/
		return 1;
	}
	else if((Ptr->RAWINTSTAT & 0x00000240) == 0x00000240) {		/* Check if TX ABORT and Detect stop */
		return 1;
	}
	else if(!(Ptr->STATUS_b.MSTACTIVITY) && !(Ptr->RAWINTSTAT_b.TXEMPTY)) {
		return 1;
	}
	else if(SMBus26ms_check()){
		Ptr->ENABLE_b.ABORT = 1;
		_Delay_1ms(1);
		return 1;
	}
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

uint8_t bRWSMBus(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var, uint8_t PECSupport)
{
	(void)PECSupport;
	uint8_t test_tx_buf[3];
	uint8_t test_rx_buf[3];
	if(Protocol == SendByte || Protocol == SMbusSBC)
	{
		test_tx_buf[0] = Cmd;
		test_tx_buf[1] = *var;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,NULL))
		{
			return SUCCESS;
		}
			return FAIL;

	}
	else if(Protocol == ReceiveByte || Protocol == SMbusRBC)
	{
		test_tx_buf[0] = Cmd;
		test_tx_buf[1] = *var;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,NULL))
		{
			return SUCCESS;
		}
			return FAIL;

	}
	else if(Protocol == WriteByte || Protocol == SMbusWB)
	{
		test_tx_buf[0] = Cmd;
		test_tx_buf[1] = *var;

		
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,NULL))
		{
			return SUCCESS;
		}
			return FAIL;
	}
	else if(Protocol == ReadByte || Protocol == SMbusRB)
	{
		test_tx_buf[0] = Cmd;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,test_rx_buf))
		{
			*var = test_rx_buf[0];
			return SUCCESS;
		}
		return FAIL;
		
	}
	else if(Protocol == WriteWord || Protocol == SMbusWW)
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
	else if(Protocol == ReadWord || Protocol == SMbusRW)
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

uint8_t bWSMBusBlock(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var, uint8_t PECSupport)
{
uint8_t test_tx_buf[5];
	uint8_t test_rx_buf[5];
	if(Protocol == WriteBlock || Protocol == SMbusWBK)
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
	else if(Protocol == ReadBlock || Protocol == SMbusRBK)
	{
		test_tx_buf[0] = Cmd;
		if(I2C_SMBusModProtocol(Channel, Protocol, Addr,0,test_tx_buf,test_rx_buf))
		{
			*var = (uint32_t)((test_rx_buf[4]<<24)+(test_rx_buf[3]<<16)+(test_rx_buf[2]<<8)+test_rx_buf[1]);
			//BAT_DEVNAME = (uint32_t)*var;
			//BAT_DEVNAME2 = (uint16_t)(*var>>16);
			return SUCCESS;
		}
		return FAIL;
		
	}
	return SUCCESS;	
}