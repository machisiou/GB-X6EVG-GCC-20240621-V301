#include "hal/PerVW.h"

/******************************************************************************/
/** Initial DMA Source Address
 * EC Source Address - (UINT:uint32_t)
 * Compare Address - (UINT:uint32_t)
 * return None
*******************************************************************************/
void Perpheral_InitDMASrcAddr(uint32_t SrcAddr, uint32_t ComAddr)
{
	ESPI->EPBUF = SrcAddr;					/* EC Source Address */
	ESPI->EPCPRADR = ComAddr;				/* Compare with protocol Address */
	ESPI->EPCPRVLD_b.VALIDEN = 1;			/* Enable Compare address function */
}

/******************************************************************************/
/** Virtual Wire Get Index
 * Index - (UINT:uint8_t)
 * return None
*******************************************************************************/
uint8_t VW_Get_Index(uint8_t Index)
{
	if(INDEX2 <= Index && INDEX4A >= Index)
		return (uint8_t) *(&ESPI->EVIDX2 + Index);
	else if(INDEX51 <= Index && INDEX61 >= Index)
		return (uint8_t) *(&ESPI->EVIDX51 + Index);
	else
		return ERROR;
}

/******************************************************************************/
/** Virtual Wire Set Index
 * Index - (UINT:uint8_t)
 * Data - (UINT:uint8_t)
 * return None
*******************************************************************************/
void VW_Set_Index(uint8_t Index, uint8_t Data)
{
	uint32_t i;
	i = (0x0000FFFF & ((uint32_t)Index << 8 | (uint32_t)Data));
	ESPI->EVTXDAT = i;
	while(ESPI->EVSTS_b.TXFULL == 1);
	SetVWTransclr;
}

/******************************************************************************/
/** Virtual Wire Enable Interrupt
 * RXChgEn - 0: Disable, 1: Enable
 * TXEmptyEn - 0: Disable, 1: Enable
 * VWConfigChg - 0: Disable, 1: Enable
 * return None
*******************************************************************************/
void VW_Set_IntEn(_Bool RXChgEn, _Bool TXEmptyEn, _Bool VWConfigChg)
{
	ESPI->EVRXINTEN_b.RXCHGEN = RXChgEn;
	ESPI->EVRXINTEN_b.CFGCHGEN = VWConfigChg;
	ESPI->EVTXINTEN_b.TXMPTEN = TXEmptyEn;
}

/******************************************************************************/
/** Virtual Wire Get Status
 * return Status (UINT:uint32_t)
*******************************************************************************/
uint32_t VW_GetSts(void)
{
	return ESPI->EVSTS;
}

/******************************************************************************/
/** Virtual Wire Clear Status
 * ClrPos - (UINT:uint32_t)
 * return None
*******************************************************************************/
void VW_ClrSts(uint32_t ClrPos)
{
	ESPI->EVSTS = ClrPos;
}

/******************************************************************************/
/** Virtual Wire Reset Status
 * return None
*******************************************************************************/
void VW_ResetSts(void)
{
	ESPI->EVSTS = 0x00003FFFA;
}
