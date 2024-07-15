#ifndef __ESPI_SAFS_H__
#define __ESPI_SAFS_H__

#include <stdint.h>

extern void SAF_Set_DataBuffer(uint32_t BufferAddr);
extern void SAF_Set_RPMCBuffer(uint32_t BufferAddr);
extern uint8_t SAF_TagGroup(uint8_t SAFTag, uint8_t TagGroup);
extern uint8_t SAF_ProtecRegion(uint8_t RegionNum, uint32_t StartAddr, uint32_t Length);
extern uint8_t SAF_WrProtect(uint8_t RegionNum, uint8_t Group);
extern uint8_t SAF_RdProtect(uint8_t RegionNum, uint8_t Group);
extern void SAF_ProtecEn(uint8_t Enable);

#endif
