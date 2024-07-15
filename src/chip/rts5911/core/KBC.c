#include "system/Type.h"
#include "hal/KBC.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Active IO port
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Init(void)
{
	KBC->VWCTRL1_b.ACTEN = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Change 6064 io number
 * _62addr : new 60 port number
 * _66offset : new 64 port offset
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Change_PortAddr(uint16_t _60addr, uint8_t _64offset)
{
	KBC->PTADDR_b.ADDR = (_60addr & 0x0FFF);
	KBC->PTADDR_b.OFFSET = (_64offset & 0x07);
	return SUCCESS;
}

/******************************************************************************/
/** Set 6064 IRQ number
 * IRQ number
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Set_IRQ_Number(uint8_t IRQnum)
{
	KBC->VWCTRL1_b.IRQNUM = IRQnum;
	return SUCCESS;
}

/******************************************************************************/
/** Enable IRQ
 * EnDis : Enable or Disable
 * 0 : low level 1 : high level
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Enable_autoIRQ(uint8_t EnDis, uint8_t level)
{
	KBC->VWCTRL0_b.TGLV = level;
	KBC->VWCTRL0_b.IRQEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable 6064 interrupt
 * IBOB : _IBF interrupt or _OBF interrupt
 * EnDis : Enable or disable
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis)
{
	if(IBOB == _OBF) {
		KBC->INTEN_b.OBFINTEN = EnDis;
	}else if(IBOB == _IBF) {
		KBC->INTEN_b.IBFINTEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Check OBF is set
 * return OBF flag
*******************************************************************************/
uint8_t KBC_Is_OBF(void)
{
	return KBC->STS_b.OBF;
}

/******************************************************************************/
/** Check IBF is set
 * return IBF flag
*******************************************************************************/
uint8_t KBC_Is_IBF(void)
{
	return KBC->STS_b.IBF;
}

/******************************************************************************/
/** Check command or data port
 * return CMDSEL flag
*******************************************************************************/
uint8_t KBC_Is_CMD(void)
{
	return KBC->STS_b.CMDSEL;
}

/******************************************************************************/
/** Get IO port status
 * return port status
*******************************************************************************/
uint8_t KBC_Get_Status(void)
{
	return (uint8_t) KBC->STS;
}

/******************************************************************************/
/** Set IO port status
 * FlagNum : bit of byte
 * Value : 0 or 1
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Set_Status(uint8_t FlagNum, uint8_t Value)
{
	if((FlagNum == BIT2) || (FlagNum == BIT4) || (FlagNum == BIT5) || (FlagNum == BIT6) || (FlagNum == BIT7)) {
		if(Value == 1)
			KBC->STS |= FlagNum;
		else if (Value == 0)
			KBC->STS &= ~FlagNum;
	}else return FAIL;
	return SUCCESS;
}

/******************************************************************************/
/** Force clear IBF/OBF bit
 * IBOB : _IBF or _OBF
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_ForceClr_Status(uint8_t IBOB)
{
	if(IBOB == _OBF) {
		KBC->OB_b.OBCLR = 1;
	}else if(IBOB == _IBF) {
		KBC->IB_b.IBCLR = 1;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read input data buffer
 * return input data buffer
*******************************************************************************/
uint8_t KBC_Read(void)
{
	uint32_t ret;
	ret = KBC->IB;
	return (uint8_t) ret;
}

/******************************************************************************/
/** Write output buffer data
 * data : output buffer data
 * return SUCCESS
*******************************************************************************/
uint8_t KBC_Write(uint8_t data)
{
	uint32_t exData=0;
	exData = (uint32_t) data;
	KBC->OB = exData;
	return SUCCESS;
}
