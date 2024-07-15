#ifndef __SPIC_H__
#define __SPIC_H__

#include <stdint.h>

typedef struct
{
	uint8_t ID;
	uint8_t Write_Enable;
	uint8_t Write_Disable;
	uint8_t Read_Status_1;
	uint8_t Read_Status_2;
	uint8_t Write_Status;
	uint8_t PP;
	uint8_t QPP;
	uint8_t SectErase_4K;
	uint8_t BE_32K;
	uint8_t BE_64K;
	uint8_t Chip_Erase;
	uint8_t PwrDown;
	uint8_t Release_PwrDown;
	uint8_t Read_Data;
	uint8_t Fast_Read;
	uint8_t Fast_Read_Dual_Output;
	uint8_t Fast_Read_Quad_Output;
	uint8_t Fast_Read_Dual_IO;
	uint8_t Fast_Read_Quad_IO;
	uint8_t JEDEC_ID;
	uint8_t DummyLength;
	uint8_t RpmcCmd;
	uint8_t RpmcRead;
	uint8_t Reserved;
}SPI_Type;

typedef struct
{
	uint8_t MID;
	uint8_t Type;
	uint8_t Density;
	uint8_t Reserved;
}ID_Type;

typedef struct
{
	ID_Type VendorID;
	const SPI_Type* VendorFlash;
}Flash_Vendor_Type;

extern const SPI_Type WindBond[];
extern const SPI_Type MX[];
extern const SPI_Type GigaDev[];
extern const Flash_Vendor_Type SelectFlash[];
extern void SPIC_Initial(void);
extern uint8_t SPIC_CheckState(void);
extern void SPIC_AutoMode(void);
extern void SPIC_UserMode(void);
extern uint32_t SPIC_ReadID(const SPI_Type* Flash);
extern uint32_t SPIC_ReadFlash(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_WriteFlash(uint32_t Addr, uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_WriteEn(const SPI_Type* Flash, uint8_t Enable);
extern uint32_t SPIC_Erase(uint32_t Addr, const SPI_Type* Flash, uint8_t EraseType);
extern uint32_t SPIC_ChipErase(const SPI_Type* Flash);
extern uint8_t SPIC_FlashStatus(const SPI_Type* Flash);
extern uint8_t SPIC_FlashStatus2(const SPI_Type* Flash);
extern uint8_t SPIC_WriteStatus(const SPI_Type* Flash, uint8_t Status, uint8_t Status2);
extern uint32_t SPIC_QuadReadFlash(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_QuadOutputFastReadDMA(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_QuadWriteFlash(uint32_t Addr, uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_QuadWriteFlashDMA(uint32_t Addr, uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_DualReadFlash(uint32_t Addr, uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_RpmcCmd(uint32_t Length ,uint8_t* WBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_RpmcRead(uint32_t Length ,uint8_t* RBuffer ,const SPI_Type* Flash);
extern uint32_t SPIC_EntPD(const SPI_Type* Flash);
extern uint32_t SPIC_ExtPD(const SPI_Type* Flash);
extern void SPIC_DMA_En(void);
#endif
