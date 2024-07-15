#include "system/Type.h"
#include "hal/PMPORT0.h"
#include "hal/KBC.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Active IO port
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Init(void)
{
	PMPORT0->VWCTRL1_b.ACTEN = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Change 686C io number
 * _68addr : new 68 port number
 * _6Coffset : new 6C port offset
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Change_PortAddr(uint16_t PM0addr, uint8_t PM0offset)
{
	PMPORT0->PTADDR_b.ADDR = (PM0addr & 0x0FFF);
	PMPORT0->PTADDR_b.OFFSET = (PM0offset & 0x07);
	return SUCCESS;
}

/******************************************************************************/
/** Set 686C IRQ number
 * IRQ number
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Set_IRQ_Number(uint8_t IRQnum)
{
	PMPORT0->VWCTRL1_b.IRQNUM = IRQnum;
	return SUCCESS;
}

/******************************************************************************/
/** Enable IRQ
 * EnDis : Enable or Disable
 * 0 : low level 1 : high level
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Enable_autoIRQ(uint8_t EnDis, uint8_t level)
{
	PMPORT0->VWCTRL0_b.TGLV = level;
	PMPORT0->VWCTRL0_b.IRQEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable 686C interrupt
 * IBOB : _IBF interrupt or _OBF interrupt
 * EnDis : Enable or disable
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis)
{
	if(IBOB == _OBF) {
		PMPORT0->INTEN_b.OBFINTEN = EnDis;
	}else if(IBOB == _IBF) {
		PMPORT0->INTEN_b.IBFINTEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Check OBF is set
 * return OBF flag
*******************************************************************************/
uint8_t PM0_Is_OBF(void)
{
	return PMPORT0->STS_b.OBF;
}

/******************************************************************************/
/** Check IBF is set
 * return IBF flag
*******************************************************************************/
uint8_t PM0_Is_IBF(void)
{
	return PMPORT0->STS_b.IBF;
}

/******************************************************************************/
/** Check command or data port
 * return CMDSEL flag
*******************************************************************************/
uint8_t PM0_Is_CMD(void)
{
	return PMPORT0->STS_b.CMDSEL;
}

/******************************************************************************/
/** Get IO port status
 * return port status
*******************************************************************************/
uint8_t PM0_Get_Status(void)
{
	return (uint8_t) PMPORT0->STS;
}

/******************************************************************************/
/** Set IO port status
 * FlagNum : bit of byte
 * Value : 0 or 1
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Set_Status(uint8_t FlagNum, uint8_t Value)
{
	if((FlagNum == BIT2) || (FlagNum == BIT4) || (FlagNum == BIT5) || (FlagNum == BIT6) || (FlagNum == BIT7)) {
		if(Value == 1)
			PMPORT0->STS |= FlagNum;
		else if (Value == 0)
			PMPORT0->STS &= ~FlagNum;
		return SUCCESS;
	}else return FAIL;
}

/******************************************************************************/
/** Force clear IBF/OBF bit
 * IBOB : _IBF or _OBF
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_ForceClr_Status(uint8_t IBOB)
{
	if(IBOB == _OBF) {
		PMPORT0->OB_b.OBCLR = 1;
	}else if(IBOB == _IBF) {
		PMPORT0->IB_b.IBCLR = 1;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read input data buffer
 * return input data buffer
*******************************************************************************/
uint8_t PM0_Read(void)
{
	uint32_t ret;
	ret = PMPORT0->IB;
	return (uint8_t) ret;
}

/******************************************************************************/
/** Write output buffer data
 * data : output buffer data
 * return SUCCESS
*******************************************************************************/
uint8_t PM0_Write(uint8_t data)
{
	uint32_t exData=0;
	exData = (uint32_t) data;
	PMPORT0->OB = exData;
	return SUCCESS;
}
