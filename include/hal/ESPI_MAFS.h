#ifndef __ESPI_MAFS_H__
#define __ESPI_MAFS_H__

#include <stdint.h>

extern void MAFS_SendDatatoFlash(uint32_t FlashAddr, uint8_t* WriteBuffer, uint32_t WriteLength);
extern void MAFS_GetDataFromFlash(uint32_t FlashAddr, uint8_t* ReadBuffer, uint32_t ReadLength);
extern void MAFS_EraseFlash(uint32_t FlashAddr);

#endif
