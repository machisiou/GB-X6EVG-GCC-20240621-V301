#include "system/Type.h"
#include "hal/PMPORT3.h"
#include "hal/KBC.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Active IO port
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Init(void)
{
	PMPORT3->VWCTRL1_b.ACTEN = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Change 7A7E io number
 * _7Aaddr : new 7a port number
 * _7Eoffset : new 7e port offset
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Change_PortAddr(uint16_t PM3addr, uint8_t PM3offset)
{
	PMPORT3->PTADDR_b.ADDR = (PM3addr & 0x0FFF);
	PMPORT3->PTADDR_b.OFFSET = (PM3offset & 0x07);
	return SUCCESS;
}

/******************************************************************************/
/** Set 7A7E IRQ number
 * IRQ number
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Set_IRQ_Number(uint8_t IRQnum)
{
	PMPORT3->VWCTRL1_b.IRQNUM = IRQnum;
	return SUCCESS;
}

/******************************************************************************/
/** Enable IRQ
 * EnDis : Enable or Disable
 * 0 : low level 1 : high level
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Enable_autoIRQ(uint8_t EnDis, uint8_t level)
{
	PMPORT3->VWCTRL0_b.TGLV = level;
	PMPORT3->VWCTRL0_b.IRQEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable 7A7E interrupt
 * IBOB : _IBF interrupt or _OBF interrupt
 * EnDis : Enable or disable
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis)
{
	if(IBOB == _OBF) {
		PMPORT3->INTEN_b.OBFINTEN = EnDis;
	}else if(IBOB == _IBF) {
		PMPORT3->INTEN_b.IBFINTEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Check OBF is set
 * return OBF flag
*******************************************************************************/
uint8_t PM3_Is_OBF(void)
{
	return PMPORT3->STS_b.OBF;
}

/******************************************************************************/
/** Check IBF is set
 * return IBF flag
*******************************************************************************/
uint8_t PM3_Is_IBF(void)
{
	return PMPORT3->STS_b.IBF;
}

/******************************************************************************/
/** Check command or data port
 * return CMDSEL flag
*******************************************************************************/
uint8_t PM3_Is_CMD(void)
{
	return PMPORT3->STS_b.CMDSEL;
}

/******************************************************************************/
/** Get IO port status
 * return port status
*******************************************************************************/
uint8_t PM3_Get_Status(void)
{
	return (uint8_t) PMPORT3->STS;
}

/******************************************************************************/
/** Set IO port status
 * FlagNum : bit of byte
 * Value : 0 or 1
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Set_Status(uint8_t FlagNum, uint8_t Value)
{
	if((FlagNum == BIT2) || (FlagNum == BIT4) || (FlagNum == BIT5) || (FlagNum == BIT6) || (FlagNum == BIT7)) {
		if(Value == 1)
			PMPORT3->STS |= FlagNum;
		else if (Value == 0)
			PMPORT3->STS &= ~FlagNum;
		return SUCCESS;
	}else return FAIL;
}

/******************************************************************************/
/** Force clear IBF/OBF bit
 * IBOB : _IBF or _OBF
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_ForceClr_Status(uint8_t IBOB)
{
	if(IBOB == _OBF) {
		PMPORT3->OB_b.OBCLR = 1;
	}else if(IBOB == _IBF) {
		PMPORT3->IB_b.IBCLR = 1;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read input data buffer
 * return input data buffer
*******************************************************************************/
uint8_t PM3_Read(void)
{
	uint32_t ret;
	ret = PMPORT3->IB;
	return (uint8_t) ret;
}

/******************************************************************************/
/** Write output buffer data
 * data : output buffer data
 * return SUCCESS
*******************************************************************************/
uint8_t PM3_Write(uint8_t data)
{
	uint32_t exData=0;
	exData = (uint32_t) data;
	PMPORT3->OB = exData;
	return SUCCESS;
}
