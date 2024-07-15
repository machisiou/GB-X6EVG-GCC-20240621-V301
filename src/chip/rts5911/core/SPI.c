#include "system/Type.h"
#include "hal/SPI.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/* Set HSPI R/W data buffer address
 * Tx_StartAddr - mapping to RAM address for HSPI Tx buffer
 * Tx_Length - HSPI Tx buffer length
 * Rx_StartAddr - mapping to RAM address for HSPI Rx buffer
 * Rx_Length - HSPI Rx buffer length
 * return None
*******************************************************************************/

void HSPI_BufCfg(uint32_t Tx_StartAddr, uint32_t Tx_Length, uint32_t Rx_StartAddr, uint32_t Rx_Length)
{
	SPISLV->TXSTRADDR = Tx_StartAddr;
	SPISLV->TXENDADDR = Tx_StartAddr + Tx_Length;
	SPISLV->RXSTRADDR = Rx_StartAddr;
	SPISLV->RXENDADDR = Rx_StartAddr + Rx_Length;
}

/******************************************************************************/
/* Set MSPI Cmd phase data and length
 * CmdData0 - Cmd byte 0~3
 * CmdData1 - Cmd byte 4
 * DataLength - Cmd data length bit number with 0-based
 * return FAIL if DataLength out of range
*******************************************************************************/
uint8_t MSPI_Set_CmdData(uint32_t CmdData0, uint32_t CmdData1,uint8_t DataLength)
{
	uint8_t result;
	if(DataLength>39)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		MSPI->CMDL = CmdData0;
		MSPI->CMDH_b.CMD4 = CmdData1 & 0xFF;
		MSPI->CMDNUM = DataLength;
	}
	return result;
}

/******************************************************************************/
/* Set MSPI Address phase data and length
 * AddrData - Address byte 0~2
 * DataLength - Address data length bit number with 0-based
 * return FAIL if DataLength out of range
*******************************************************************************/
uint8_t MSPI_Set_AddrData(uint32_t AddrData, uint8_t DataLength)
{
	uint8_t result;
	if(DataLength>31)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		MSPI->ADDR = AddrData;
		MSPI->ADDRNUM = DataLength;
	}
	return result;
}

/******************************************************************************/
/* Set MSPI Auto Mode
 * 0x0 = Command mode
 * 0x1 = Command & Address mode
 * 0x2 = Command & Data out mode
 * 0x3 = Command & Data in mode
 * 0x4 = Command & Address & Data out mode
 * 0x5 = Command & Address & Data in mode
 * 0x6 = Polling status
 * 0x7 = Fast read mode (SPI command = 0x0B)
 * 0x8 = Fast read dual out mode (SPI command = 0x03B)
 * 0x9 = Fast read dual in-out mode (SPI command = 0x0BB)
 * return FAIL if Mode is an illegal value
*******************************************************************************/
uint8_t MSPI_AutoModeSel(uint8_t Mode)
{
	uint8_t result;
	if(Mode>0x9)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		MSPI->TRCTRL_b.MODE = Mode;
	}
	return result;
}

/******************************************************************************/
/* Set MSPI Configuration
 * CS_IdleStatus: 0 = Low level, 1 = High level
 * LSBFirst: 0 = MSB first, 1 = LSB first
 * SampleTiming:
 * 0x0: Sample MISO at the rising edge of SCK.
 * 0x1: delay half SCK clock cycle to sample.
 * 0x2: delay one SCK clock cycle
 * 0x3: delay one and a half SCK clock cycle
 * return FAIL if Mode is an illegal value
*******************************************************************************/
uint8_t MSPI_Config(uint8_t CS_IdleStatus, uint8_t LSBFirst, uint8_t SampleTiming)
{
	uint8_t result;
	if(CS_IdleStatus>1 || LSBFirst>1 || SampleTiming>3)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		MSPI->CTRL_b.CSPOR = CS_IdleStatus;
		MSPI->CTRL_b.LSBFST = LSBFirst;
		MSPI->CFG_b.EDO =  SampleTiming;
	}
	return result;
}

/******************************************************************************/
/* MSPI Reset
 * return none
*******************************************************************************/
void MSPI_Reset(void)
{
	MSPI->CTRL_b.RST = 1;
}

/******************************************************************************/
/* MSPI Start
 * return none
*******************************************************************************/
void MSPI_Start(void)
{
	MSPI->TRCTRL_b.START = 1;
}

/******************************************************************************/
/* MSPI Data Length
 * return none
*******************************************************************************/
void MSPI_Length(uint8_t Length)
{
	MSPI->TRLEN = Length;
}

/******************************************************************************/
/* MSPI Clk divider
 * SCK frequency is MCU clock divided by SPI clock divider.
 * The actual SPI clock divider value is (CLK_DIVIDER +1) * 2.
 * return none
*******************************************************************************/
void MSPI_Divider(uint16_t DivValue)
{
	MSPI->CLKDIV = DivValue;
}

/******************************************************************************/
/* MSPI Auto write
 * Data length is 0-based
 * return none
*******************************************************************************/
uint8_t MSPI_Write_Data(uint32_t *TxBufAddr, uint8_t DataLenght)
{
	uint16_t i;
	uint8_t result;
	if((MSPI->TRCTRL_b.MODE != 2) || (MSPI->TRCTRL_b.MODE != 4))
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		for(i=0 ; i<=DataLenght ; i++)
		{
			MSPI->TX = (uint8_t)(*(TxBufAddr+i));
		}
		MSPI->TRLEN = DataLenght;
		MSPI_Start();
	}
	return result;
}

/******************************************************************************/
/* MSPI Auto read
 * Data length is 0-based
 * return none
*******************************************************************************/
uint8_t MSPI_Read_Data(uint32_t *RxBufAddr, uint8_t DataLenght)
{
	uint16_t i;
	uint8_t result;
	if((MSPI->TRCTRL_b.MODE != 3)  ||  (MSPI->TRCTRL_b.MODE != 5) ||  (MSPI->TRCTRL_b.MODE != 7))
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		MSPI->TRLEN = DataLenght;
		MSPI_Start();
		for(i=0 ; i<=DataLenght ; i++)
		{
			(*(RxBufAddr+i)) = MSPI->RX;
		}
	}
	return result;
}
