#include <stddef.h>
#include "system/Type.h"
#include "hal/SPIC.h"
#include "hal/DMA.h"
#include "chip/rts5911/RTS5911.h"

const Flash_Vendor_Type SelectFlash[] = 
{
	{{0xEF, 0x00, 0x00, 0x00}, WindBond},
	{{0xC8, 0x64, 0x13, 0x00}, GigaDev},		// GD25WD40E
	{{0xC8, 0x40, 0x14, 0x00}, GigaDev},		// GD25D80E
	{{0x00, 0x00, 0x00, 0x00}, NULL}
};


const SPI_Type WindBond[] =
{{
	0xEF,	// Windbond ID
	0x06,	// Write Enable
	0x04,	// Write Disable
	0x05,	// Read Status-1
	0x35,	// Read Status-2
	0x01,	// Write Status
	0x02,	// Page Program
	0x32,	// Quad Page Program
	0x20,	// Sector Erase(4K)
	0x52,	// Block Erase(32K)
	0xD8,	// Block Erase(64K)
	0x60,	// Chip Erase
	0xB9,	// Power-down
	0xAB,	// Release Power-down
	0x03,	// Read Data
	0x0B,	// Fast Read
	0x3B,	// Fast Read Daul Output
	0x6B,	// Fast Read Quad Output
	0xBB,	// Fast Read Dual I/O
	0xEB,	// Fast Read Quad I/O
	0x9F,	// JEDEC ID
	0x10,	// Dummy cycle 8 clock
	0x9B,	// RPMC Command
	0x96,	// RPMC Read
	0x00,	// Reserved
}};

const SPI_Type MX[] =
{{
	0x9F,	// MX ID
	0x06,	// Write Enable
	0x04,	// Write Disable
	0x05,	// Read Status-1
	0x00,	// Read Status-2(Null)
	0x01,	// Write Status
	0x12,	// Page Program
	0x3E,	// Quad Page Program
	0x20,	// Sector Erase(4K)
	0x52,	// Block Erase(32K)
	0xD8,	// Block Erase(64K)
	0x60,	// Chip Erase
	0xB9,	// Power-down
	0xAB,	// Release Power-down
	0x03,	// Read Data
	0x0B,	// Fast Read
	0x3B,	// Fast Read Daul Output
	0x6B,	// Fast Read Quad Output
	0xBB,	// Fast Read Dual I/O
	0xEB,	// Fast Read Quad I/O
	0x9F,	// JEDEC ID
	0x00,	// Dummy cycle 8 clock(Null)
	0x9B,	// RPMC Command
	0x96,	// RPMC Read
	0x00,	// Reserved
}};

const SPI_Type GigaDev[] =
{{
	0xC8,	// Giga Device ID
	0x06,	// Write Enable
	0x04,	// Write Disable
	0x05,	// Read Status-1
	0x00,	// Read Status-2(Null)
	0x01,	// Write Status
	0x02,	// Page Program
	0x00,	// Quad Page Program(Null)
	0x20,	// Sector Erase(4K)
	0x52,	// Block Erase(32K)
	0xD8,	// Block Erase(64K)
	0x60,	// Chip Erase
	0xB9,	// Power-down
	0xAB,	// Release Power-down
	0x03,	// Read Data
	0x0B,	// Fast Read
	0x3B,	// Fast Read Daul Output
	0x00,	// Fast Read Quad Output(Null)
	0xBB,	// Fast Read Dual I/O(Null)
	0xEB,	// Fast Read Quad I/O(Null)
	0x9F,	// JEDEC ID
	0x10,	// Dummy cycle 8 clock
	0x00,	// RPMC Command(Null)
	0x00,	// RPMC Read(Null)
	0x00,	// Reserved
}};

/******************************************************************************/
/** Initial SPIC
 * return None
*******************************************************************************/
void SPIC_Initial(void)
{
	while(SPIC->SR_b.BOOTFIN == 0);
	SPIC->SSIENR = 0;
	SPIC->SER_b.SLVNUM = 1;
	SPIC->CTRL0_b.USERMODE = 1;					/* Change to user mode */
	SPIC->BAUDR_b.SCKDV = 1;					/* SPI_CLK = PLL/2 */
}

/******************************************************************************/
/** Check SPIC busy
 * return 0: Idle, 1: Busy
*******************************************************************************/
uint8_t SPIC_CheckState(void)
{
	if(SPIC->SR_b.BUSY) {						/* Check if busy */
		return BUSY;
	}
	return IDLE;
}

/******************************************************************************/
/** Auto mode
 * return None
*******************************************************************************/
void SPIC_AutoMode(void)
{
	SPIC->CTRL0_b.USERMODE = 0;
}

/******************************************************************************/
/** User mode
 * return None
*******************************************************************************/
void SPIC_UserMode(void)
{
	SPIC->CTRL0_b.USERMODE = 1;
}

/******************************************************************************/
/** Read ID
 * Flash - Flash type
 * return Flash ID (uint32_t)
*******************************************************************************/
uint32_t SPIC_ReadID(const SPI_Type* Flash)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;						/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;							/* Receive mode */
	SPIC->CTRL0_b.DATACH = 0;						/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;					/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;					/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;						/* Set Write data length */
	SPIC->RXNDF = 0x00000003;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->JEDEC_ID;				/* Read ID Command */
	SPIC->SSIENR_b.SPICEN = 1;						/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0; 
	SPIC->CTRL0_b.TMOD = 0;							/* Trans mode */
	return SPIC->WORD_DR[0];
}

/******************************************************************************/
/** Single Read Flash
 * Addr - Flash Address (32 bit)
 * Length - Read Data length
 * RBuffer - Read Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_ReadFlash(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;						/* Receive mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;					/* Set Write data length */
	SPIC->RXNDF = Length;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->Read_Data;		/* Read Command */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;
	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */

	SPIC->IMR_b.RXOIM = 1;						/* Enable RX FIFO enable */
	SPIC->RXFTLR = 2;
	for (i=0;i<Length;i++)
		*(RBuffer+i) = SPIC->BYTE_DR[0];

	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */
	return SUCCESS;
}

/******************************************************************************/
/** Single Write Flash
 * Addr - Flash Address (32 bit)
 * Length - Write Data length
 * WBuffer - Write Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_WriteFlash(uint32_t Addr, uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;						/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;							/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;						/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;					/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;					/* Set Address Length(Default 3) */
	SPIC->TXNDF = Length;							/* Set Write data length */
	SPIC->RXNDF = 0x00000000;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->PP;					/* Page Program Command */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;

	if(Length < 13) {
		for(i=0;i<Length;i++)
			SPIC->BYTE_DR[0] = *(WBuffer+i);
		SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
		SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
		while(SPIC->SSIENR_b.SPICEN == 1);
		SPIC->SSIENR_b.SPICEN = 0;
	}
	else {
		SPIC->TXFTLR = 2;							/* Set FIFO threshold = 2 */
		for(i=0;i<11;i++)
			SPIC->BYTE_DR[0] = *(WBuffer+i);
		SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
		SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
		for(i=11;i<Length;i++) {
			if((SPIC->TXFLR<0x10)||(SPIC->RISR_b.TXEIR == 1))
				SPIC->BYTE_DR[0] = *(WBuffer+i);
			else {
				//printf("SPIC->Txflr = %lx\n",SPIC->TXFLR);
				//printf("SPIC->RISR_b.TXEIR = %x\n",SPIC->RISR_b.TXEIR);
			}
		}
	}
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0; 
	return SUCCESS;
}

/******************************************************************************/
/** Single Write Enable
 * Flash - Flash type
 * Enable - 0:Disable, 1:Enable
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_WriteEn(const SPI_Type* Flash, uint8_t Enable)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;						/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;							/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;						/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;					/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;					/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;						/* Set Write data length */
	SPIC->RXNDF = 0x00000000;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	if (Enable == 1)
		SPIC->BYTE_DR[0] = Flash->Write_Enable;		/* Write Enable Command */
	else if(Enable == 0)
		SPIC->BYTE_DR[0] = Flash->Write_Disable;	/* Write Disable Command */

	SPIC->SSIENR_b.ATCKCMD = 1;						/* Auto check status */
	SPIC->SSIENR_b.SPICEN = 1;						/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	return SUCCESS;
}

/******************************************************************************/
/** Single Erase
 * Addr - Flash Address (32 bit)
 * Flash - Flash type
 * EraseType - 0: 4K erase, 1: 32K erase, 2: 64K erase
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_Erase(uint32_t Addr, const SPI_Type* Flash, uint8_t EraseType)
{
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;						/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;							/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;						/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;					/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;					/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;						/* Set Write data length */
	SPIC->RXNDF = 0x00000000;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	if (EraseType == 0)
		SPIC->BYTE_DR[0] = Flash->SectErase_4K;		/* Sector erase */
	else if(EraseType == 1)
		SPIC->BYTE_DR[0] = Flash->BE_32K;			/* Block erase (32K) */
	else if(EraseType == 2)
		SPIC->BYTE_DR[0] = Flash->BE_64K;			/* Block erase (64K) */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;

	SPIC->SSIENR_b.ATCKCMD = 1;						/* Auto check status */
	SPIC->SSIENR_b.SPICEN = 1;						/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	return SUCCESS;
}

/******************************************************************************/
/** Chip Erase
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_ChipErase(const SPI_Type* Flash)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;					/* Set Write data length */
	SPIC->RXNDF = 0x00000000;					/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->Chip_Erase;		/* Chip erase */

	SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	return SUCCESS;
}

/******************************************************************************/
/** Read Flash Status
 * Flash - Flash type
 * return Flash status (uint8_t)
*******************************************************************************/
uint8_t SPIC_FlashStatus(const SPI_Type* Flash)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;						/* Receive mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;					/* Set Write data length */
	SPIC->RXNDF = 0x00000001;					/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->Read_Status_1;	/* Read status1 */

	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */

	return SPIC->BYTE_DR[0];
}

/******************************************************************************/
/** Read Flash Status 2
 * Flash - Flash type
 * return Flash status (uint8_t)
*******************************************************************************/
uint8_t SPIC_FlashStatus2(const SPI_Type* Flash)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;						/* Receive mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;					/* Set Write data length */
	SPIC->RXNDF = 0x00000001;					/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->Read_Status_2;	/* Read status1 */

	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */

	return SPIC->BYTE_DR[0];
}

/******************************************************************************/
/** Write Flash Status
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint8_t SPIC_WriteStatus(const SPI_Type* Flash, uint8_t Status, uint8_t Status2)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000002;					/* Set Write data length */
	SPIC->RXNDF = 0x00000001;					/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->Write_Status;		/* Write status command */
	SPIC->BYTE_DR[0] = Status;					/* Write status */
	SPIC->BYTE_DR[0] = Status2;					/* Write status2 */

	SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;

	return SUCCESS;
}

/******************************************************************************/
/** Quad Read Flash
 * Addr - Flash Address (32 bit)
 * Length - Read Data length
 * RBuffer - Read Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_QuadReadFlash(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;
		
	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;							/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;								/* Receive mode */
	SPIC->CTRL0_b.DATACH = 2;							/* Quad Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;							/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;							/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;						/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;						/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;							/* Set Write data length */
	SPIC->RXNDF = Length;								/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = Flash->DummyLength;
	SPIC->BYTE_DR[0] = Flash->Fast_Read_Quad_Output;	/* Quad Read Command */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;
	SPIC->SSIENR_b.SPICEN = 1;							/* Start trans */

	for (i=0;i<Length;i++)
		*(RBuffer+i) = SPIC->BYTE_DR[0];

	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;								/* Trans mode */
	return SUCCESS;
}

/******************************************************************************/
/** Quad Read Flash DMA
 * Addr - Flash Address (32 bit)
 * Length - Read Data length
 * RBuffer - Read Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_QuadOutputFastReadDMA(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash)
{
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;
		
	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;							/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;								/* Receive mode */
	SPIC->CTRL0_b.DATACH = 2;							/* Quad Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;							/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;							/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;						/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;						/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;							/* Set Write data length */
	SPIC->RXNDF = Length;								/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = Flash->DummyLength;
	SPIC->BYTE_DR[0] = Flash->Fast_Read_Quad_Output;	/* Quad Read Command */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;
	SPIC->RXFTLR = 1;

	DMAC_PtoM(SPIC_BASE+0x60,(uint32_t)&RBuffer[0],Length);

	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;								/* Trans mode */
	return SUCCESS;
}

/******************************************************************************/
/** Quad Write Flash
 * Addr - Flash Address (32 bit)
 * Length - Write Data length
 * WBuffer - Write Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_QuadWriteFlash(uint32_t Addr, uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;							/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;								/* Trans mode */
	if(Flash->ID == 0xEF) {								/* Windbond ID */
		SPIC->CTRL0_b.DATACH = 2;						/* Quad Channel for Data channel */
		SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
		SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */
	}
	else {
		SPIC->CTRL0_b.DATACH = 2;						/* Quad Channel for Data channel */
		SPIC->CTRL0_b.ADDRCH = 0;						/* Quad Channel for Address channel */
		SPIC->CTRL0_b.CMDCH = 0;						/* Quad Channel for Command channel */
	}
	SPIC->USERLENGTH_b.CMDLEN = 1;						/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;						/* Set Address Length(Default 3) */
	SPIC->TXNDF = Length;								/* Set Write data length */
	SPIC->RXNDF = 0x00000000;							/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->QPP;						/* Page Program Command */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;

	if(Length < 13) {
		for(i=0;i<Length;i++)
			SPIC->BYTE_DR[0] = *(WBuffer+i);
		SPIC->SSIENR_b.ATCKCMD = 1;						/* Auto check status */
		SPIC->SSIENR_b.SPICEN = 1;						/* Start trans */
		while(SPIC->SSIENR_b.SPICEN == 1);
		SPIC->SSIENR_b.SPICEN = 0;
	}
	else {
		SPIC->TXFTLR = 2;								/* Set FIFO threshold = 2 */
		for(i=0;i<11;i++)
			SPIC->BYTE_DR[0] = *(WBuffer+i);
		SPIC->SSIENR_b.ATCKCMD = 1;						/* Auto check status */
		SPIC->SSIENR_b.SPICEN = 1;						/* Start trans */
		for(i=11;i<Length;i++) {
			if((SPIC->TXFLR<0x10)||(SPIC->RISR_b.TXEIR == 1))
				SPIC->BYTE_DR[0] = *(WBuffer+i);
			else {
				//printf("SPIC->Txflr = %lx\n",SPIC->TXFLR);
				//printf("SPIC->RISR_b.TXEIR = %x\n",SPIC->RISR_b.TXEIR);
			}
		}
	}
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0; 
	return SUCCESS;
}

/******************************************************************************/
/** Quad Write Flash with DMA
 * Addr - Flash Address (32 bit)
 * Length - Write Data length
 * WBuffer - Write Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_QuadWriteFlashDMA(uint32_t Addr, uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash)
{
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;							/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;								/* Trans mode */
	if(Flash->ID == 0xEF) {								/* Windbond ID */
		SPIC->CTRL0_b.DATACH = 2;						/* Quad Channel for Data channel */
		SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
		SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */
	}
	else {
		SPIC->CTRL0_b.DATACH = 2;						/* Quad Channel for Data channel */
		SPIC->CTRL0_b.ADDRCH = 2;						/* Quad Channel for Address channel */
		SPIC->CTRL0_b.CMDCH = 2;						/* Quad Channel for Command channel */
	}
	SPIC->USERLENGTH_b.CMDLEN = 1;						/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 3;						/* Set Address Length(Default 3) */
	SPIC->TXNDF = Length;								/* Set Write data length */
	SPIC->RXNDF = 0x00000000;							/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->QPP;						/* Page Program Command */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;

	SPIC->SSIENR_b.ATCKCMD = 1; 						/* Auto check status */

	DMAC_MtoP((uint32_t)&WBuffer[0],SPIC_BASE+0x60,Length);

	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0; 
	return SUCCESS;
}

/******************************************************************************/
/** Dual Read Flash
 * Addr - Flash Address (32 bit)
 * Length - Read Data length
 * RBuffer - Read Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_DualReadFlash(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	uint8_t AddrH, AddrM, AddrL;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;						/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;							/* Receive mode */
	SPIC->CTRL0_b.DATACH = 1;						/* Dual Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */

	if(Flash->ID == 0xC2) {							/* MXIC ID */
		SPIC->USERLENGTH_b.RDDUMMYLEN = 8;			/* Dummy cycle 6T in MXIC spec */
		SPIC->USERLENGTH_b.ADDRLEN = 4;				/* Set Address Length(Default 3) */
	}
	else if(Flash->ID == 0xC8) {					/* Giga device ID */
		SPIC->USERLENGTH_b.RDDUMMYLEN = 16;			/* Dummy cycle 8T in MXIC spec */
		SPIC->USERLENGTH_b.ADDRLEN = 3;				/* Set Address Length(Default 3) */
	}
	else {
		//printf("Need check spec\n");
	}
	SPIC->USERLENGTH_b.CMDLEN = 1;					/* Set Command Length */
	SPIC->TXNDF = 0x00000000;						/* Set Write data length */
	SPIC->RXNDF = Length;							/* Set Read data length */

	SPIC->BYTE_DR[0] = Flash->Fast_Read_Dual_Output;	/* Dual Output Fast Read */

	AddrH = (uint8_t)((Addr & 0x00FF0000) >> 16);
	AddrM = (uint8_t)((Addr & 0x0000FF00) >> 8);
	AddrL = (uint8_t)(Addr & 0x000000FF);
	SPIC->BYTE_DR[0] = AddrH;
	SPIC->BYTE_DR[0] = AddrM;
	SPIC->BYTE_DR[0] = AddrL;
	if(Flash->ID == 0xC2) {
		SPIC->BYTE_DR[0] = 0;
	}
	SPIC->SSIENR_b.SPICEN = 1;						/* Start trans */

	for (i=0;i<Length;i++)
		*(RBuffer+i) = SPIC->BYTE_DR[0];

	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;							/* Trans mode */
	return SUCCESS;
}

/******************************************************************************/
/** RPMC Command
 * Length - Write Data length
 * WBuffer - Write Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_RpmcCmd(uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;						/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;							/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;						/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;						/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;						/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;					/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;					/* Set Address Length(Default 3) */
	SPIC->TXNDF = Length;							/* Set Write data length */
	SPIC->RXNDF = 0x00000000;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->RpmcCmd;				/* RPMC Write */

	if(Length < 13) {
		for(i=0;i<Length;i++)
			SPIC->BYTE_DR[0] = *(WBuffer+i);
		SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
		SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
		while(SPIC->SSIENR_b.SPICEN == 1);
		SPIC->SSIENR_b.SPICEN = 0; 
	}
	else {
		SPIC->TXFTLR = 2;							/* Set FIFO threshold = 2 */
		for(i=0;i<11;i++)
			SPIC->BYTE_DR[0] = *(WBuffer+i);
		SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
		SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
		for(i=11;i<Length;i++) {
			if((SPIC->TXFLR<0x10)||(SPIC->RISR_b.TXEIR == 1))
				SPIC->BYTE_DR[0] = *(WBuffer+i);
			else {
				//printf("SPIC->Txflr = %lx\n",SPIC->TXFLR);
				//printf("SPIC->RISR_b.TXEIR = %x\n",SPIC->RISR_b.TXEIR);
			}
		}
	}
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0; 
	return SUCCESS;
}

/******************************************************************************/
/** RPMC Read
 * Length - Read Data length
 * RBuffer - Read Data Buffer
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_RpmcRead(uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash)
{
	uint32_t i;
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 3;						/* Receive mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000001;					/* Set Write data length */
	SPIC->RXNDF = Length;						/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;
	SPIC->BYTE_DR[0] = Flash->RpmcRead;			/* RPMC Read Command */
	SPIC->BYTE_DR[0] = 0x00;					/* Dummy byte */
	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */

	for (i=0;i<Length;i++)
		*(RBuffer+i) = SPIC->BYTE_DR[0];

	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */
	return SUCCESS;
}

/******************************************************************************/
/** Entry Power down
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_EntPD(const SPI_Type* Flash)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;					/* Set Write data length8 */
	SPIC->RXNDF = 0x00000000;					/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;

	SPIC->BYTE_DR[0] = Flash->PwrDown;			/* Power Down Command */

	SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0;
	return SUCCESS;
}

/******************************************************************************/
/** Release from Power down
 * Flash - Flash type
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t SPIC_ExtPD(const SPI_Type* Flash)
{
	if(SPIC_CheckState() == BUSY)
		return BUSY;

	SPIC->SSIENR = 0x00000000;
	SPIC->CTRL0_b.USERMODE = 1;					/* User Mode */
	SPIC->CTRL0_b.TMOD = 0;						/* Trans mode */
	SPIC->CTRL0_b.DATACH = 0;					/* Single Channel for Data channel */
	SPIC->CTRL0_b.ADDRCH = 0;					/* Single Channel for Address channel */
	SPIC->CTRL0_b.CMDCH = 0;					/* Single Channel for Command channel */

	SPIC->USERLENGTH_b.CMDLEN = 1;				/* Set Command Length */
	SPIC->USERLENGTH_b.ADDRLEN = 0;				/* Set Address Length(Default 3) */
	SPIC->TXNDF = 0x00000000;					/* Set Write data length */
	SPIC->RXNDF = 0x00000000;					/* Set Read data length */
	SPIC->USERLENGTH_b.RDDUMMYLEN = 0;

	SPIC->BYTE_DR[0] = Flash->Release_PwrDown;	/* Release from Power Down Command */

	SPIC->SSIENR_b.ATCKCMD = 1;					/* Auto check status */
	SPIC->SSIENR_b.SPICEN = 1;					/* Start trans */
	while(SPIC->SSIENR_b.SPICEN == 1);
	SPIC->SSIENR_b.SPICEN = 0; 
	return SUCCESS;
}

void SPIC_DMA_En(void)
{
	SPIC->DMACR_b.TXDMACEN = 1;					/* Enable SPIC DMA */
	SPIC->SSIENR_b.SPICEN = 1;					/* Enable trans */
}
