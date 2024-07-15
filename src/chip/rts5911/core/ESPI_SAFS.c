#include <stdint.h>
#include "system/Type.h"
#include "hal/ESPI_SAFS.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/* Set SAF data buffer address, default value should be SPIC memory mapping address (0x60000000) for auto read/write
 * BufferAddr - buffer address
 * return None
*******************************************************************************/
void SAF_Set_DataBuffer(uint32_t BufferAddr)
{
	ESPI->ESBUF = BufferAddr;
}

/******************************************************************************/
/* Set buffer address for RPMC command of RPMC flash
 * BufferAddr - buffer address
 * return None
*******************************************************************************/
void SAF_Set_RPMCBuffer(uint32_t BufferAddr)
{
	ESPI->ESBUF1 = BufferAddr;
}

/******************************************************************************/
/* Set SAF tag to group (refer Intel definition of Tag)
 * SAFTag - tag of eSPI SAF format
 * TagGroup - group number of tag
 * return SUCCESS / FAIL (input value error)
*******************************************************************************/
uint8_t SAF_TagGroup(uint8_t SAFTag, uint8_t TagGroup)
{
	uint8_t result;
	if(SAFTag>0xF || TagGroup>7)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		switch(SAFTag)
		{
			case 0x0: ESPI->ESPRG0_b.TAG0GRP = TagGroup; break;
			case 0x1: ESPI->ESPRG0_b.TAG1GRP = TagGroup; break;
			case 0x2: ESPI->ESPRG0_b.TAG2GRP = TagGroup; break;
			case 0x3: ESPI->ESPRG0_b.TAG3GRP = TagGroup; break;
			case 0x4: ESPI->ESPRG0_b.TAG4GRP = TagGroup; break;
			case 0x5: ESPI->ESPRG0_b.TAG5GRP = TagGroup; break;
			case 0x6: ESPI->ESPRG0_b.TAG6GRP = TagGroup; break;
			case 0x7: ESPI->ESPRG0_b.TAG7GRP = TagGroup; break;
			case 0x8: ESPI->ESPRG1_b.TAG8GRP = TagGroup; break;
			case 0x9: ESPI->ESPRG1_b.TAG9GRP = TagGroup; break;
			case 0xA: ESPI->ESPRG1_b.TAGAGRP = TagGroup; break;
			case 0xB: ESPI->ESPRG1_b.TAGBGRP = TagGroup; break;
			case 0xC: ESPI->ESPRG1_b.TAGCGRP = TagGroup; break;
			case 0xD: ESPI->ESPRG1_b.TAGDGRP = TagGroup; break;
			case 0xE: ESPI->ESPRG1_b.TAGEGRP = TagGroup; break;
			case 0xF: ESPI->ESPRG1_b.TAGFGRP = TagGroup; break;
			default : break;
		}
	}
	return result;
}

/******************************************************************************/
/* Set SAF protection region
 * RegionNum - region select
 * StartAddr - region start address
 * Length - region length
 * return SUCCESS / FAIL (input value error)
*******************************************************************************/
uint8_t SAF_ProtecRegion(uint8_t RegionNum, uint32_t StartAddr, uint32_t Length)
{
	uint8_t result;
	if(RegionNum>0xF || Length>0xFFFFF)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		switch(RegionNum)
		{
			case 0x0: ESPI->ESP0STR_b.ADDR = StartAddr; ESPI->ESP0LEN_b.LEN = Length; break;
			case 0x1: ESPI->ESP1STR_b.ADDR = StartAddr; ESPI->ESP1LEN_b.LEN = Length; break;
			case 0x2: ESPI->ESP2STR_b.ADDR = StartAddr; ESPI->ESP2LEN_b.LEN = Length; break;
			case 0x3: ESPI->ESP3STR_b.ADDR = StartAddr; ESPI->ESP3LEN_b.LEN = Length; break;
			case 0x4: ESPI->ESP4STR_b.ADDR = StartAddr; ESPI->ESP4LEN_b.LEN = Length; break;
			case 0x5: ESPI->ESP5STR_b.ADDR = StartAddr; ESPI->ESP5LEN_b.LEN = Length; break;
			case 0x6: ESPI->ESP6STR_b.ADDR = StartAddr; ESPI->ESP6LEN_b.LEN = Length; break;
			case 0x7: ESPI->ESP7STR_b.ADDR = StartAddr; ESPI->ESP7LEN_b.LEN = Length; break;
			case 0x8: ESPI->ESP8STR_b.ADDR = StartAddr; ESPI->ESP8LEN_b.LEN = Length; break;
			case 0x9: ESPI->ESP9STR_b.ADDR = StartAddr; ESPI->ESP9LEN_b.LEN = Length; break;
			case 0xA: ESPI->ESPASTR_b.ADDR = StartAddr; ESPI->ESPALEN_b.LEN = Length; break;
			case 0xB: ESPI->ESPBSTR_b.ADDR = StartAddr; ESPI->ESPBLEN_b.LEN = Length; break;
			case 0xC: ESPI->ESPCSTR_b.ADDR = StartAddr; ESPI->ESPCLEN_b.LEN = Length; break;
			case 0xD: ESPI->ESPDSTR_b.ADDR = StartAddr; ESPI->ESPDLEN_b.LEN = Length; break;
			case 0xE: ESPI->ESPESTR_b.ADDR = StartAddr; ESPI->ESPELEN_b.LEN = Length; break;
			case 0xF: ESPI->ESPFSTR_b.ADDR = StartAddr; ESPI->ESPFLEN_b.LEN = Length; break;
			default : break;
		}
	}
	return result;
}

/******************************************************************************/
/* Set SAF write/erase protection region
 * RegionNum - region select
 * Group - bit0 = group0, bit1 = group1 ........bit7 = group7
 *        bit = 1 = block group from the region, bit = 0 = the group can access the region
 * return SUCCESS / FAIL (input value error)
*******************************************************************************/
uint8_t SAF_WrProtect(uint8_t RegionNum, uint8_t Group)
{
	uint8_t result;
	if(RegionNum>0xF)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		switch(RegionNum)
		{
			case 0x0: ESPI->ESWPRG0 = Group; break;
			case 0x1: ESPI->ESWPRG1 = Group; break;
			case 0x2: ESPI->ESWPRG2 = Group; break;
			case 0x3: ESPI->ESWPRG3 = Group; break;
			case 0x4: ESPI->ESWPRG4 = Group; break;
			case 0x5: ESPI->ESWPRG5 = Group; break;
			case 0x6: ESPI->ESWPRG6 = Group; break;
			case 0x7: ESPI->ESWPRG7 = Group; break;
			case 0x8: ESPI->ESWPRG8 = Group; break;
			case 0x9: ESPI->ESWPRG9 = Group; break;
			case 0xA: ESPI->ESWPRGA = Group; break;
			case 0xB: ESPI->ESWPRGB = Group; break;
			case 0xC: ESPI->ESWPRGC = Group; break;
			case 0xD: ESPI->ESWPRGD = Group; break;
			case 0xE: ESPI->ESWPRGE = Group; break;
			case 0xF: ESPI->ESWPRGF = Group; break;
			default: break;
		}
	}
	return result;
}

/******************************************************************************/
/* Set SAF read protection region
 * RegionNum - region select
 * Group - bit0 = group0, bit1 = group1 ........bit7 = group7
 *        bit = 1 = block group from the region, bit = 0 = the group can access the region
 * return SUCCESS / FAIL (input value error)
*******************************************************************************/
uint8_t SAF_RdProtect(uint8_t RegionNum, uint8_t Group)
{
	uint8_t result;
	if(RegionNum>0xF)
	{
		result = FAIL;
	}
	else
	{
		result = SUCCESS;
		switch(RegionNum)
		{
			case 0x0: ESPI->ESRPRG0 = Group; break;
			case 0x1: ESPI->ESRPRG1 = Group; break;
			case 0x2: ESPI->ESRPRG2 = Group; break;
			case 0x3: ESPI->ESRPRG3 = Group; break;
			case 0x4: ESPI->ESRPRG4 = Group; break;
			case 0x5: ESPI->ESRPRG5 = Group; break;
			case 0x6: ESPI->ESRPRG6 = Group; break;
			case 0x7: ESPI->ESRPRG7 = Group; break;
			case 0x8: ESPI->ESRPRG8 = Group; break;
			case 0x9: ESPI->ESRPRG9 = Group; break;
			case 0xA: ESPI->ESRPRGA = Group; break;
			case 0xB: ESPI->ESRPRGB = Group; break;
			case 0xC: ESPI->ESRPRGC = Group; break;
			case 0xD: ESPI->ESRPRGD = Group; break;
			case 0xE: ESPI->ESRPRGE = Group; break;
			case 0xF: ESPI->ESRPRGF = Group; break;
			default: break;
		}
	}
	return result;
}

/******************************************************************************/
/* SAF protection enable
 * Enable : 1 = enable, 0 = disable
 * return None
*******************************************************************************/
void SAF_ProtecEn(uint8_t Enable)
{
	ESPI->ESPREN_b.EN = Enable;
}
