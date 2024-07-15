#include "system/Type.h"
#include "hal/PMPORT1.h"
#include "hal/KBC.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Active IO port
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Init(void)
{
	PMPORT1->VWCTRL1_b.ACTEN = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Change 6A6E io number
 * _6Aaddr : new 6A port number
 * _6Eoffset : new 6E port offset
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Change_PortAddr(uint16_t PM1addr, uint8_t PM1offset)
{
	PMPORT1->PTADDR_b.ADDR = (PM1addr & 0x0FFF);
	PMPORT1->PTADDR_b.OFFSET = (PM1offset & 0x07);
	return SUCCESS;
}

/******************************************************************************/
/** Set 6A6E IRQ number
 * IRQ number
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Set_IRQ_Number(uint8_t IRQnum)
{
	PMPORT1->VWCTRL1_b.IRQNUM = IRQnum;
	return SUCCESS;
}

/******************************************************************************/
/** Enable IRQ
 * EnDis : Enable or Disable
 * 0 : low level 1 : high level
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Enable_autoIRQ(uint8_t EnDis, uint8_t level)
{
	PMPORT1->VWCTRL0_b.TGLV = level;
	PMPORT1->VWCTRL0_b.IRQEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable 7478 interrupt
 * IBOB : _IBF interrupt or _OBF interrupt
 * EnDis : Enable or disable
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis)
{
	if(IBOB == _OBF) {
		PMPORT1->INTEN_b.OBFINTEN = EnDis;
	}else if(IBOB == _IBF) {
		PMPORT1->INTEN_b.IBFINTEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Check OBF is set
 * return OBF flag
*******************************************************************************/
uint8_t PM1_Is_OBF(void)
{
	return PMPORT1->STS_b.OBF;
}

/******************************************************************************/
/** Check IBF is set
 * return IBF flag
*******************************************************************************/
uint8_t PM1_Is_IBF(void)
{
	return PMPORT1->STS_b.IBF;
}

/******************************************************************************/
/** Check command or data port
 * return CMDSEL flag
*******************************************************************************/
uint8_t PM1_Is_CMD(void)
{
	return PMPORT1->STS_b.CMDSEL;
}

/******************************************************************************/
/** Get IO port status
 * return port status
*******************************************************************************/
uint8_t PM1_Get_Status(void)
{
	return (uint8_t) PMPORT1->STS;
}

/******************************************************************************/
/** Set IO port status
 * FlagNum : bit of byte
 * Value : 0 or 1
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Set_Status(uint8_t FlagNum, uint8_t Value)
{
	if((FlagNum == BIT2) || (FlagNum == BIT4) || (FlagNum == BIT5) || (FlagNum == BIT6) || (FlagNum == BIT7)) {
		if(Value == 1)
			PMPORT1->STS |= FlagNum;
		else if (Value == 0)
			PMPORT1->STS &= ~FlagNum;
		return SUCCESS;
	}else return FAIL;
}

/******************************************************************************/
/** Force clear IBF/OBF bit
 * IBOB : _IBF or _OBF
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_ForceClr_Status(uint8_t IBOB)
{
	if(IBOB == _OBF) {
		PMPORT1->OB_b.OBCLR = 1;
	}else if(IBOB == _IBF) {
		PMPORT1->IB_b.IBCLR = 1;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read input data buffer
 * return input data buffer
*******************************************************************************/
uint8_t PM1_Read(void)
{
	uint32_t ret;
	ret = PMPORT1->IB;
	return (uint8_t) ret;
}

/******************************************************************************/
/** Write output buffer data
 * data : output buffer data
 * return SUCCESS
*******************************************************************************/
uint8_t PM1_Write(uint8_t data)
{
	uint32_t exData=0;
	exData = (uint32_t) data;
	PMPORT1->OB = exData;
	return SUCCESS;
}
