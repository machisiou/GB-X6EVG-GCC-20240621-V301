#include <stdint.h>
#include "hal/KBM.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Write KSO
 * KSONum - KSO Number
 * Level - 0:Low
 * return None
*******************************************************************************/
void KBM_Write_KSOL(uint32_t KSONum)
{
	KBM->SCANOUT = ~(0x1ul << KSONum);
}

/******************************************************************************/
/** Write All KSO high
 * return None
*******************************************************************************/
void KBM_Write_KSO_All_High(void)
{
	if((KBM->CTRL_b.KSO18EN) && (KBM->CTRL_b.KSO19EN))
		KBM->SCANOUT = 0x000FFFFF;
	else if((KBM->CTRL_b.KSO18EN) && (!KBM->CTRL_b.KSO19EN))
		KBM->SCANOUT = 0x0007FFFF;
	else if((!KBM->CTRL_b.KSO18EN) && (!KBM->CTRL_b.KSO19EN))
		KBM->SCANOUT = 0x0003FFFF;
}

/******************************************************************************/
/** Write All KSO low
 * return None
*******************************************************************************/
void KBM_Write_KSO_All_Low(void)
{
	KBM->SCANOUT = 0x00000000;
}

/******************************************************************************/
/** Read KSI
 * KSINum - KSI Number
 * return Level - 0:Low, 1:High
*******************************************************************************/
_Bool KBM_Read_KSI(uint8_t KSINum)
{
	_Bool i;
	i = ((KBM->SCANIN >> KSINum) & 0x1ul);
	return i;
}

/******************************************************************************/
/** Check if any KSI low 
 * return KSI Status
*******************************************************************************/
uint32_t KBM_Read_All_KSI(void)
{
	uint32_t TempKSI;
	TempKSI = ~KBM->SCANIN;
	if((KBM->CTRL_b.KSI8EN) && (KBM->CTRL_b.KSI9EN)) {
		return (TempKSI & 0x000003FF);
	}
	else if((KBM->CTRL_b.KSI8EN) && (!KBM->CTRL_b.KSI9EN)) {
		return (TempKSI & 0x000001FF);
	}
	else if((!KBM->CTRL_b.KSI8EN) && (!KBM->CTRL_b.KSI9EN)) {
		return (TempKSI & 0x000000FF);
	}
	else
		return 0;
}

/******************************************************************************/
/** Extra KSO Configure
 * KSONum - KSO Number (Only KSO18, KSO19 are available)
 * Enable - 0:Disable, 1:Enable
 * return None
*******************************************************************************/
void KBM_Extra_KSO_Config(uint8_t KSONum, uint8_t Enable)
{
	if(KSONum == 18)
		KBM->CTRL_b.KSO18EN = Enable;
	else if(KSONum == 19)
		KBM->CTRL_b.KSO19EN = Enable;
}

/******************************************************************************/
/** Extra KSI Configure
 * KSINum - KSI Number (Only KSI8, KSI9 are available)
 * Enable - 0:Disable, 1:Enable
 * return None
*******************************************************************************/
void KBM_Extra_KSI_Config(uint8_t KSINum, uint8_t Enable)
{
	if(KSINum == 8)
		KBM->CTRL_b.KSI8EN = Enable;
	else if(KSINum == 9)
		KBM->CTRL_b.KSI9EN = Enable;
}

/******************************************************************************/
/** KBM Interrupt Configure
 * KSINum - KSI Number
 * Enable - 0:Disable, 1:Enable
 * return None
*******************************************************************************/
void KBM_Intr_Config(uint32_t KSINum, uint8_t Enable)
{
	if(Enable == 1)
		KBM->INTEN |= (0x1ul << KSINum);
	else if(Enable == 0)
		KBM->INTEN &= ~(0x1ul << KSINum);
}

/******************************************************************************/
/** KBM Output type Configure
 * Type - 0:Push-Pull, 1:Open-Drain
 * return None
*******************************************************************************/
void KBM_Output_Type(uint8_t Type)
{
	KBM->CTRL_b.EN = Type;
}

/******************************************************************************/
/** KBM Clear Interrupt
 * return None
*******************************************************************************/
void KBM_ClrIntr(void)
{
	KBM->CTRL_b.INTSTS = 1;		/* W1C */
}

/******************************************************************************/
/** KSI Interrupt Enable
 * return None
*******************************************************************************/
void KSI_Intr_Enable(void)
{
	KBM->INTEN = 0xFF;
}

/******************************************************************************/
/** KSI Interrupt Disable
 * return None
*******************************************************************************/
void KSI_Intr_Disable(void)
{
	KBM->INTEN = 0x00;
}
