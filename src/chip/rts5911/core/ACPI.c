#include <stdint.h>
#include "system/Type.h"
#include "hal/ACPI.h"
#include "hal/KBC.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Active IO port
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Init(void)
{
	ACPI->VWCTRL1_b.ACTEN = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Change 6266 io number
 * _62addr : new 62 port number
 * _66offset : new 66 port offset
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Change_PortAddr(uint16_t _62addr, uint8_t _66offset)
{
	ACPI->PTADDR_b.ADDR = (_62addr & 0x0FFF);
	ACPI->PTADDR_b.OFFSET = (_66offset & 0x07);
	return SUCCESS;
}

/******************************************************************************/
/** Set 6266 IRQ number
 * IRQ number
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Set_IRQ_Number(uint8_t IRQnum)
{
	ACPI->VWCTRL1_b.IRQNUM = IRQnum;
	return SUCCESS;
}

/******************************************************************************/
/** Enable IRQ
 * EnDis : Enable or Disable
 * 0 : low level 1 : high level
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Enable_autoIRQ(uint8_t EnDis, uint8_t level)
{
	ACPI->VWCTRL0_b.TGLV = level;
	ACPI->VWCTRL0_b.IRQEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable 6266 interrupt
 * IBOB : _IBF interrupt or _OBF interrupt
 * EnDis : Enable or disable
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis)
{
	if(IBOB == _OBF) {
		ACPI->INTEN_b.OBFINTEN = EnDis;
	}else if(IBOB == _IBF) {
		ACPI->INTEN_b.IBFINTEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Check OBF is set
 * return OBF flag
*******************************************************************************/
uint8_t ACPI_Is_OBF(void)
{
	return ACPI->STS_b.OBF;
}

/******************************************************************************/
/** Check IBF is set
 * return IBF flag
*******************************************************************************/
uint8_t ACPI_Is_IBF(void)
{
	return ACPI->STS_b.IBF;
}

/******************************************************************************/
/** Check command or data port
 * return CMDSEL flag
*******************************************************************************/
uint8_t ACPI_Is_CMD(void)
{
	return ACPI->STS_b.CMDSEL;
}

/******************************************************************************/
/** Check burst mode is enable
 * return BURST flag
*******************************************************************************/
uint8_t ACPI_Is_BURST(void)
{
	return ACPI->STS_b.BURST;
}

/******************************************************************************/
/** Check burst mode is enable
 * return BURST flag
*******************************************************************************/
void ACPI_BURST_Set(void)
{
	ACPI->STS_b.BURST = 1;
}

/******************************************************************************/
/** Check burst mode is enable
 * return BURST flag
*******************************************************************************/
void ACPI_BURST_Clr(void)
{
	ACPI->STS_b.BURST = 0;
}

/******************************************************************************/
/** Get IO port status
 * return port status
*******************************************************************************/
uint8_t ACPI_Get_Status(void)
{
	return (uint8_t) ACPI->STS;
}

/******************************************************************************/
/** Set IO port status
 * FlagNum : bit of byte
 * Value : 0 or 1
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Set_Status(uint8_t FlagNum, uint8_t Value)
{
	if((FlagNum == BIT2) || (FlagNum == BIT4) || (FlagNum == BIT5) || (FlagNum == BIT6) || (FlagNum == BIT7)) {
		if(Value == 1)
			ACPI->STS |= FlagNum;
		else if (Value == 0)
			ACPI->STS &= ~FlagNum;
		return SUCCESS;
	}else return FAIL;
}

/******************************************************************************/
/** Force clear IBF/OBF bit
 * IBOB : _IBF or _OBF
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_ForceClr_Status(uint8_t IBOB)
{
	if(IBOB == _OBF) {
		ACPI->OB_b.OBCLR = 1;
	}else if(IBOB == _IBF) {
		ACPI->IB_b.IBCLR = 1;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read input data buffer
 * return input data buffer
*******************************************************************************/
uint8_t ACPI_Read(void)
{
	uint8_t ret;
	ret = ACPI->IB_b.IBDAT;
	return ret;
}

/******************************************************************************/
/** Write output buffer data
 * data : output buffer data
 * return SUCCESS
*******************************************************************************/
uint8_t ACPI_Write(uint8_t data)
{
	uint32_t exData=0;
	exData = (uint32_t) data;
	ACPI->OB_b.OBDAT = exData;
	return SUCCESS;
}
