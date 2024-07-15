#include "system/Type.h"
#include "hal/EMI.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Set EMIx page just can Read or can R/W
 * EMI_chl: EMI channel
 * mode : 0 R/W 1 read only
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_RW_Mode(uint8_t EMI_chl, uint8_t mode)
{
	if(EMI_chl == EMI_0) {
		EMI0->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_1) {
		EMI1->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_2) {
		EMI2->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_3) {
		EMI3->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_4) {
		EMI4->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_5) {
		EMI5->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_6) {
		EMI6->CFG_b.WRPROT = mode;
	}else if(EMI_chl == EMI_7) {
		EMI7->CFG_b.WRPROT = mode;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Set EMIx page status location
 * EMI_chl: EMI channel
 * offset : 0~3
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Status_Loc(uint8_t EMI_chl, uint8_t offset)
{
	if(offset > 0x03) return FAIL;

	if(EMI_chl == EMI_0) {
		EMI0->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_1) {
		EMI1->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_2) {
		EMI2->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_3) {
		EMI3->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_4) {
		EMI4->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_5) {
		EMI5->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_6) {
		EMI6->CFG_b.STSADDR = offset;
	}else if(EMI_chl == EMI_7) {
		EMI7->CFG_b.STSADDR = offset;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable EMIx page IRQ
 * EMI_chl: EMI channel
 * EnDis : 0 Enable or Disable
 * level : 0 low trigger 1 high reigger
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Enable_autoIRQ(uint8_t EMI_chl, uint8_t EnDis, uint8_t level)
{
	if(EMI_chl == EMI_0) {
		EMI0->INTCTRL_b.TGLV = level;
		EMI0->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_1) {
		EMI1->INTCTRL_b.TGLV = level;
		EMI1->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_2) {
		EMI2->INTCTRL_b.TGLV = level;
		EMI2->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_3) {
		EMI3->INTCTRL_b.TGLV = level;
		EMI3->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_4) {
		EMI4->INTCTRL_b.TGLV = level;
		EMI4->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_5) {
		EMI5->INTCTRL_b.TGLV = level;
		EMI5->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_6) {
		EMI6->INTCTRL_b.TGLV = level;
		EMI6->INTCTRL_b.IRQEN = EnDis;
	}else if(EMI_chl == EMI_7) {
		EMI7->INTCTRL_b.TGLV = level;
		EMI7->INTCTRL_b.IRQEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Set EMIx page IRQ number
 * EMI_chl: EMI channel
 * IRQnum : IRQ number
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Set_IRQ_Number(uint8_t EMI_chl, uint8_t IRQnum)
{
	if(EMI_chl == EMI_0) {
		EMI0->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_1) {
		EMI1->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_2) {
		EMI2->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_3) {
		EMI3->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_4) {
		EMI4->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_5) {
		EMI5->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_6) {
		EMI6->IRQNUM = IRQnum;
	}else if(EMI_chl == EMI_7) {
		EMI7->IRQNUM = IRQnum;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable EMIx page interrupt
 * EMI_chl: EMI channel
 * EnDis : Enable or Disable
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Enable_Interrupt(uint8_t EMI_chl, uint8_t EnDis)
{
	if(EMI_chl == EMI_0) {
		EMI0->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_1) {
		EMI1->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_2) {
		EMI2->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_3) {
		EMI3->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_4) {
		EMI4->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_5) {
		EMI5->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_6) {
		EMI6->INTCTRL_b.INTEN = EnDis;
	}else if(EMI_chl == EMI_7) {
		EMI7->INTCTRL_b.INTEN = EnDis;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Set EMIx page SAR address
 * EMI_chl: EMI channel
 * SARaddr : memory address
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Set_SAR_Address(uint8_t EMI_chl, uint32_t SARaddr)
{
	if(EMI_chl == EMI_0) {
		EMI0->SAR = SARaddr;
	}else if(EMI_chl == EMI_1) {
		EMI1->SAR = SARaddr;
	}else if(EMI_chl == EMI_2) {
		EMI2->SAR = SARaddr;
	}else if(EMI_chl == EMI_3) {
		EMI3->SAR = SARaddr;
	}else if(EMI_chl == EMI_4) {
		EMI4->SAR = SARaddr;
	}else if(EMI_chl == EMI_5) {
		EMI5->SAR = SARaddr;
	}else if(EMI_chl == EMI_6) {
		EMI6->SAR = SARaddr;
	}else if(EMI_chl == EMI_7) {
		EMI7->SAR = SARaddr;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read EMIx page interrupt status
 * EMI_chl: EMI channel
 * return interrupt status
*******************************************************************************/
uint8_t EMI_Read_Intsts(uint8_t EMI_chl)
{
	if(EMI_chl == EMI_0) {
		return EMI0->INTSTS_b.STS;
	}else if(EMI_chl == EMI_1) {
		return EMI1->INTSTS_b.STS;
	}else if(EMI_chl == EMI_2) {
		return EMI2->INTSTS_b.STS;
	}else if(EMI_chl == EMI_3) {
		return EMI3->INTSTS_b.STS;
	}else if(EMI_chl == EMI_4) {
		return EMI4->INTSTS_b.STS;
	}else if(EMI_chl == EMI_5) {
		return EMI5->INTSTS_b.STS;
	}else if(EMI_chl == EMI_6) {
		return EMI6->INTSTS_b.STS;
	}else if(EMI_chl == EMI_7) {
		return EMI7->INTSTS_b.STS;
	}else {
		return ERROR;
	}
}

/******************************************************************************/
/** Clear EMIx page interrupt status
 * EMI_chl: EMI channel
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Clear_Intsts(uint8_t EMI_chl)
{
	if(EMI_chl == EMI_0) {
		EMI0->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_1) {
		EMI1->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_2) {
		EMI2->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_3) {
		EMI3->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_4) {
		EMI4->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_5) {
		EMI5->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_6) {
		EMI6->INTSTS_b.STS = 1;
	}else if(EMI_chl == EMI_7) {
		EMI7->INTSTS_b.STS = 1;
	}else {
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Configure EMI setting
 * BaseAddr: 
 * HostAddr: host side address
 * return SUCCESS
*******************************************************************************/
uint8_t EMI_Config(uint32_t BaseAddr, uint32_t HostAddr)
{
	ESPI->EPBUF = BaseAddr;
	ESPI->EPCPRADR = HostAddr;
	ESPI->EPCPRVLD_b.VALIDEN = 1;
	return SUCCESS;
}
