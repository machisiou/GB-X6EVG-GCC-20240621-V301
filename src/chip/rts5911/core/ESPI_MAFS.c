#include "system/Type.h"
#include "hal/ESPI_MAFS.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Send data to flash part via eSPI Flash Channel
 * Parameters:
 * FlashAddr: External Flash part Address
 * WriteBuffer: Output Write Buffer data to Slave Device
 * WriteLength 
 * return Success or Fail
*******************************************************************************/
void MAFS_SendDatatoFlash(uint32_t FlashAddr, uint8_t* WriteBuffer, uint32_t WriteLength)
{
	ESPI->EMADR = FlashAddr;
	ESPI->EMBUF = (volatile uint32_t)WriteBuffer;
	//Flash Wr
//	Buf[0] = 0x55;			//desination Slave Address
//	Buf[1] = 0xAA;			//Command Code
//	Buf[2] = 0x5A;			//Byte Count
//	Buf[3] = 0xA5;			//Source Slave Address
	ESPI->EMTRLEN_b.TRLEN = WriteLength;					//TX Length 4Byte[0x400A0688]
	ESPI->EMCTRL_b.MDSEL |= 1;								//Start MAFS write master flash
	ESPI->EMCTRL_b.START |= 1;

	// printf("--START FLASH CH MAFS Read--\n");
	while(ESPI->EFSTS_b.MAFTXDN == 0);						//Check MAFS Transaction done
	// printf("--FLASH Read DONE--\n");
	ESPI->EFSTS_b.MAFTXDN |= 1;
}

/******************************************************************************/
/** Get data from flash part via eSPI Flash Channel
 * Parameters:
 * FlashAddr: External Flash part Address
 * ReadBuffer: Save Slave Device data to Read Buffer
 * ReadLength
 * return Success or Fail
*******************************************************************************/
void MAFS_GetDataFromFlash(uint32_t FlashAddr, uint8_t* ReadBuffer, uint32_t ReadLength)
{
	uint8_t FlashCnt=0, FlashBase = 0;

	ESPI->EMADR = FlashAddr;
	ESPI->EMBUF = (volatile uint32_t)ReadBuffer;						//FLASH_BUFFER_ADDR: 0x400A06B0 = 0x20058010

	//Flash Rd
	ESPI->EMTRLEN_b.TRLEN = ReadLength;						//TX Length 4Byte//FLASH_TRANS_LENGTH: 0x400A06AC = 32
	// printf("--START FLASH CH - MAFS READ--\n");
	// printf("--FlashAddr: 0x%hhx--\n", (uint8_t)FlashAddr);
	// printf("--ReadLen: %d--\n", (uint8_t)ReadLength);

	ESPI->EMCTRL_b.MDSEL |= 0;								//Start MAFS read master flash//FLASH_MAFS_CTRL: 0x400A06B4 |= BIT0
	ESPI->EMCTRL_b.START |= 1;
	while(ESPI->EFSTS_b.MAFTXDN == 0);						//Check MAFS Transaction done//Check FLASH_STS: 0x400A06A0 BIT0 = 0
	// printf("--------FLASH READ DONE--------\n");
	ESPI->EFSTS_b.MAFTXDN |= 1;								//FLASH_STS: 0x400A06A0 = BIT0

	for(FlashCnt=0; FlashCnt<ReadLength; FlashCnt++)
	{
		// printf("FLASH BUF[0x%x]: %x\n", (uint8_t)((FlashBase*32)+FlashCnt), ReadBuffer[FlashCnt]);
	}
}

/******************************************************************************/
/** Erase flash part via eSPI Flash Channel
 * Parameters:
 * FlashAddr: External Flash part Address
 * return Success or Fail
*******************************************************************************/
void MAFS_EraseFlash(uint32_t FlashAddr)
{
	ESPI->EMADR = FlashAddr;

	// printf("--START FLASH CH - MAFS ERASE--\n");
	// printf("--FlashAddr: 0x%hhx--\n", (uint8_t)FlashAddr);

	ESPI->EMCTRL_b.MDSEL |= 2;								//Start MAFS erase master flash//FLASH_MAFS_CTRL: 0x400A06B4 |= BIT0+BIT2
	ESPI->EMCTRL_b.START |= 1;
	while(ESPI->EFSTS_b.MAFTXDN == 0);						//Check MAFS Transaction done//Check FLASH_STS: 0x400A06A0 BIT0 = 0
	// printf("--------FLASH ERASE DONE--------\n");
	ESPI->EFSTS_b.MAFTXDN |= 1;								//FLASH_STS: 0x400A06A0 = BIT0
}

