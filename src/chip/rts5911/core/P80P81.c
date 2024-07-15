#include "system/Type.h"
#include "hal/P80P81.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Port 80 by pass to UART enable/disable
 * EnDis : Enable or Disable
 * return SUCCESS
*******************************************************************************/
uint8_t Port80_2_UART(uint8_t EnDis)
{
	PORT80->CFG_b.UARTPASS = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/disable port 80 thershold and set thershold byte count
 * EnDis : Enable or Disable
 * ByteCount : 0->1byte, 1->4bytes, 2->8bytes, 3->12bytes
 * return SUCCESS
*******************************************************************************/
uint8_t Port80_Enalbe_Threshold(uint8_t EnDis, uint8_t ByteCount)
{
	PORT80->CFG_b.THRE = (ByteCount & 0x03);
	PORT80->CFG_b.THREEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/disable thershold interrupt
 * EnDis : Enable or Disable
 * return SUCCESS
*******************************************************************************/
uint8_t Port80_Enalbe_Thershold_INT(uint8_t EnDis)
{
	PORT80->INTEN_b.THREINTEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Get port 80 status
 * return port 80 status
*******************************************************************************/
uint8_t Port80_Get_Port_Status(void)
{
	return (uint8_t) PORT80->STS;
}

/******************************************************************************/
/** Clear port 80 status
 * return SUCCESS
*******************************************************************************/
uint8_t Port80_Clear_Port_Status(void)
{
	PORT80->CFG_b.CLRFLG = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Get port 80 data
 * return port 80 data
*******************************************************************************/
uint8_t Port80_Get_Data(void)
{
	return (uint8_t) PORT80->DATA;
}

/******************************************************************************/
/** Change port 80 address
 * P80addr : new port 80 number
 * return SUCCESS
*******************************************************************************/
uint8_t Port80_Change_Addr(uint8_t P80addr)
{
	PORT80->ADDR = P80addr;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/disable port 81 thershold and set thershold byte count
 * EnDis : Enable or Disable
 * ByteCount : 0->1byte, 1->4bytes, 2->8bytes, 3->12bytes
 * return SUCCESS
*******************************************************************************/
uint8_t Port81_Enalbe_Threshold(uint8_t EnDis, uint8_t ByteCount)
{
	PORT81->CFG_b.THRE = (ByteCount & 0x03);
	PORT81->CFG_b.THREEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/disable thershold interrupt
 * EnDis : Enable or Disable
 * return SUCCESS
*******************************************************************************/
uint8_t Port81_Enalbe_Thershold_INT(uint8_t EnDis)
{
	PORT81->INTEN_b.THREINTEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Get port 81 status
 * return port 81 status
*******************************************************************************/
uint8_t Port81_Get_Port_Status(void)
{
	return (uint8_t) PORT81->STS;
}

/******************************************************************************/
/** Clear port 81 status
 * return SUCCESS
*******************************************************************************/
uint8_t Port81_Clear_Port_Status(void)
{
	PORT81->CFG_b.CLRFLG = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Get port 81 data
 * return port 81 data
*******************************************************************************/
uint8_t Port81_Get_Data(void)
{
	return (uint8_t) PORT81->DATA;
}

/******************************************************************************/
/** Change port 81 address
 * P81addr : new port 81 number
 * return SUCCESS
*******************************************************************************/
uint8_t Port81_Change_Addr(uint8_t P81addr)
{
	PORT81->ADDR = P81addr;
	return SUCCESS;
}

