#ifndef __PECI_H__
#define __PECI_H__

//-----------------------------------------------------------------
// PECI command set-specific definitions

#define PECI_LENGTH								3									// Client Address + Write Length + Read Length
#define FCSPING									1									// Ping command only has 1 Write Data FCS 
#define FCSLENGTH								2									// Write data FCS and Read Data FCS

//
// Ping()
//
#define PECI_PING_WRITE_DATA_LENGTH				0									// Only single command code byte written
#define PECI_PING_READ_DATA_LENGTH				0									// 8 Bytes returned
#define PECI_PING_READ_ARRAY_LENGTH				(PECI_PING_READ_DATA_LENGTH + FCSPING)	// FCS + return data + FCS
#define PECI_PING_WRITE_ARRAY_LENGTH			(PECI_LENGTH + PECI_PING_WRITE_DATA_LENGTH)		// Total write array size
//
// GetDIB()
//
#define PECI_GETDIB_WRITE_DATA_LENGTH			1									// Only single command code byte written
#define PECI_GETDIB_READ_DATA_LENGTH			8									// 8 Bytes returned
#define PECI_GETDIB_READ_ARRAY_LENGTH			(PECI_GETDIB_READ_DATA_LENGTH + FCSLENGTH)	// FCS + return data + FCS
#define PECI_GETDIB_CMD							0xF7								// Command
#define PECI_GETDIB_WRITE_ARRAY_LENGTH			(PECI_LENGTH + PECI_GETDIB_WRITE_DATA_LENGTH)		// Total write array size
#define PECI_GET_REVISION						1									// Offset in return data of revision

//
// GetTemp()
//

#define PECI_GETTEMP_WRITE_DATA_LENGTH			1									// Only single command code byte written
#define PECI_GETTEMP_READ_DATA_LENGTH			2									// 16-bit signed temperature returned
#define PECI_GETTEMP_READ_ARRAY_LENGTH			(PECI_GETTEMP_READ_DATA_LENGTH + FCSLENGTH)	// FCS + return data + FCS
#define PECI_GETTEMP_CMD						0x01								// Command
#define PECI_GETTEMP_WRITE_ARRAY_LENGTH			(PECI_LENGTH + PECI_GETTEMP_WRITE_DATA_LENGTH)	// Total write array size
#define PECI_GETTEMP_LSB						1
#define PECI_GETTEMP_MSB						2
#define PECI_GETTEMP_ERR_MSB					0x80

//
// RdPkgConfig()
//

#define PECI_RDPKGCONFIG_WRITE_DATA_LENGTH		5
#define PECI_RDPKGCONFIG_READ_DATA_LENGTH		5
#define PECI_RDPKGCONFIG_READ_ARRAY_LENGTH		(PECI_RDPKGCONFIG_READ_DATA_LENGTH + FCSLENGTH)	// FCS + return data + FCS
#define PECI_RDPKGCONFIG_CMD					0xA1
#define PECI_RDPKGCONFIG_WRITE_ARRAY_LENGTH		(PECI_LENGTH+PECI_RDPKGCONFIG_WRITE_DATA_LENGTH)
#define PECI_RDPKGCONFIG_RETRY					1
#define PECI_RDPKGCONFIG_CC						1
#define PECI_RDPKGCONFIG_DATA					1
#define PECI_RDPKGCONFIG_CC_SUCCESS				0x40
#define PECI_RDPKGCONFIG_CC_TIMEOUT				0x80
#define PECI_RDPKGCONFIG_CC_ILLEGAL				0x90

//
// WrPkgConfig()
//

#define PECI_WRPKGCONFIG_WRITE_DATA_LENGTH		10
#define PECI_WRPKGCONFIG_READ_DATA_LENGTH		1
#define PECI_WRPKGCONFIG_READ_ARRAY_LENGTH		(PECI_WRPKGCONFIG_READ_DATA_LENGTH + FCSLENGTH)	// FCS + return data + FCS
#define PECI_WRPKGCONFIG_CMD					0xA5
#define PECI_WRPKGCONFIG_WRITE_ARRAY_LENGTH		(PECI_LENGTH+PECI_WRPKGCONFIG_WRITE_DATA_LENGTH)
#define PECI_WRPKGCONFIG_RETRY					1
#define PECI_WRPKGCONFIG_CC						0
#define PECI_WRPKGCONFIG_CC_SUCCESS				0x40
#define PECI_WRPKGCONFIG_CC_TIMEOUT				0x80
#define PECI_WRPKGCONFIG_CC_ILLEGAL				0x90



typedef unsigned short us_time_t;

#define PECI_MODULE_INPUT_CLOCK_HZ	  			8000000
#define PECI_BUS_SPEED_HZ						400000  // OBT=0x14

#define MAX_RETRIES								10
#define OBT_LO ((PECI_MODULE_INPUT_CLOCK_HZ/PECI_BUS_SPEED_HZ) & 0xff)
#define OBT_HI ((((PECI_MODULE_INPUT_CLOCK_HZ/PECI_BUS_SPEED_HZ)) & 0xff00) >> 8)

#define CPU_TJMAX_INDEX							16
#define POWERLIMIT1_INDEX						26
#define POWERLIMIT2_INDEX						27
#define POWERLIMIT4_INDEX						60

#define CHECK_PECI_BUSY()						(PECI->STS1_b.BUSY)
#define CHECK_PECI_ERROR()						(PECI->STS0_b.ERRSTS)
#define CHECK_PECI_FCS_ERROR()					(PECI->ERR_b.FCSERR)
#define CHECK_PECI_FIFO_EMPTY()					(PECI->STS1_b.RXEMPTY)
#define PECI_FIFO_RESET_SET()					(PECI->CTRL_b.FIFORST = 1)
#define PECI_FIFO_RESET_CLEAR()					(PECI->CTRL_b.FIFORST = 0)

extern uint8_t CheckForTimeout(void);
extern int8_t TempConvert(uint8_t bLSB, uint8_t bMSB);

extern void	PECI_Reset(void);
extern void	PECI_Read_Bytes ( uint8_t read_data[], uint8_t num_bytes );
extern uint8_t	PECI_Write_Command(uint8_t cmd_fifo[], uint8_t cmd_length);
extern uint8_t	PECI_Wait_Idle(void);
extern uint8_t	PECI_Fcs_Check(uint8_t crc, uint8_t *data_blk_ptr, uint32_t length );
extern int	PECI_Command(uint8_t header[], uint8_t headerLen, uint8_t readBuf[], uint8_t readLen);

extern uint8_t	PECI_Ping(uint8_t Peciaddr, uint8_t Numretries);
extern uint8_t	PECI_Get_Temp(uint8_t Peciaddr, int16_t* Temp);
extern uint8_t	PECI_Get_DIB(uint8_t Peciaddr,uint8_t Numretries, uint8_t *Version);
extern uint8_t	PECI_Read_Pkg_Config(uint8_t Peciaddr,uint8_t Numretries,uint8_t Index, uint16_t Parameter, uint8_t *Value);
extern uint8_t	PECI_Write_Pkg_Config(uint8_t Peciaddr,uint8_t Numretries,uint8_t Index, uint16_t Parameter, uint8_t *Value);
extern uint8_t	PECI_Read_IA_MSR(uint8_t Peciaddr,uint8_t Numretries);

extern uint8_t	PECI_Enable_Interrupt(void);
extern uint8_t	PECI_Disable_Interrupt(void);


#endif
