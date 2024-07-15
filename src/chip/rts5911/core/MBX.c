#include "system/Type.h"
#include "hal/MBX.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Set MBX IRQ number
 * IRQnum : IRQ numberr
 * return SUCCESS
*******************************************************************************/
uint8_t MBX_Set_IRQ_Number(uint8_t IRQnum)
{
	MBX->IRQNUM_b.NUM = IRQnum;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable IRQ and setting reiger level
 * EnDis : Enable or Disable
 * level : 0 low trigger 1 high reigger
 * return SUCCESS
*******************************************************************************/
uint8_t MBX_Enable_autoIRQ(uint8_t EnDis, uint8_t level)
{
	MBX->INTCTRL_b.TGLV = level;
	MBX->INTCTRL_b.IRQEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable MBX interrupt
 * EnDis : Enable or Disable
 * return SUCCESS
*******************************************************************************/
uint8_t MBX_Enable_Interrupt(uint8_t EnDis)
{
	MBX->INTCTRL_b.INTEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Read MBX interrupt status
 * return MBX interrupt status
*******************************************************************************/
uint8_t MBX_Read_Intsts(void)
{
	return MBX->INTSTS_b.STS;
}

/******************************************************************************/
/** Clear MBX interrupt status
 * return SUCCESS
*******************************************************************************/
uint8_t MBX_Clear_Intsts(void)
{
	MBX->INTSTS_b.CLR = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Set MBX status byte
 * MBXSTS : MBX status data
 * return SUCCESS
*******************************************************************************/
uint8_t MBX_Set_Status(uint8_t MBXSTS)
{
	MBX->STS = MBXSTS;
	return SUCCESS;
}

/******************************************************************************/
/** Get MBX status byte
 * return MBX status byte
*******************************************************************************/
uint8_t MBX_Get_Status(void)
{
	return MBX->STS_b.STS;
}

/******************************************************************************/
/** Set MBX data
 * offset : data offset
 * data : data
 * return SUCCESS
*******************************************************************************/
uint8_t MBX_Set_Data(uint8_t offset, uint8_t data)
{
	if(offset >48) return ERROR;
	MBX->DATA[offset] = data;
	return SUCCESS;
}

/******************************************************************************/
/** Get MBX data
 * offset : data offset
 * return MBX data
*******************************************************************************/
uint8_t MBX_Get_Data(uint8_t offset)
{
	if(offset > 48) return ERROR;
	return (uint8_t) MBX->DATA[offset];
}
