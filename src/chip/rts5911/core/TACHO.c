#include "system/Type.h"
#include "hal/TACHO.h"
#include "chip/rts5911/RTS5911.h"

/*
*****************************************************************************
* @brief Initial Tach 
* @param Channel
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Init(uint8_t Channel)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	
	TACH->CTRL_b.EN = 1;
	return SUCCESS;
}

/*
*****************************************************************************
* @brief Read counter 
* @param Channel
* @return Channel fail or couter
*****************************************************************************
*/
uint16_t TACHO_Read_Count(uint8_t Channel)
{
  if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	return TACH->CTRL_b.CNT;
}
/*
*****************************************************************************
* @brief Enable Interrupt 
* @param Channel
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Enable_Interrupt(uint8_t Channel, uint8_t intnum)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));

	if(intnum == COUNTER_EXCEED_LIMIT_STAT)
		TACH->INTEN_b.LIMITEN = 1;
	if(intnum == COUNTER_READY_STAT)
		TACH->INTEN_b.CNTRDYEN = 1;
	if(intnum == COUNTER_TOGGLE_STAT)
		TACH->INTEN_b.CHGEN= 1;

	return SUCCESS;
}
/*
*****************************************************************************
* @brief Disable Interrupt 
* @param Channel
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Disable_Interrupt(uint8_t Channel, uint8_t intnum)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	
	if(intnum == COUNTER_EXCEED_LIMIT_STAT)
		TACH->INTEN_b.LIMITEN = 0;
	if(intnum == COUNTER_TOGGLE_STAT)
		TACH->INTEN_b.CHGEN = 0;
	if(intnum == COUNTER_READY_STAT)
		TACH->INTEN_b.CNTRDYEN = 0;

	return SUCCESS;
}
/*
*****************************************************************************
* @brief Set reading mode 
* @param Channel
* @param mode, 
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Set_Mode(uint8_t Channel, uint8_t mode)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	TACH->CTRL_b.READMODE = mode;
	return SUCCESS;
}

/*
*****************************************************************************
* @brief Set tach edge 
* @param Channel
* @param mode, 
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Set_Edge(uint8_t Channel, uint8_t EdgeNum)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	TACH->CTRL_b.SELEDGE = EdgeNum;
	
	return SUCCESS;
}

/*
*****************************************************************************
* @brief Set filter enable
* @param Channel
* @param mode, 
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Set_Filter(uint8_t Channel, uint8_t filterEn)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	TACH->CTRL_b.FILTEREN =filterEn;
	
	return SUCCESS;
}
/*
*****************************************************************************
* @brief Set High limit value 
* @param Channel
* @param counter high limit value
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Set_High_Limit(uint8_t Channel, uint16_t countH)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	TACH->LIMITH = countH;
	return SUCCESS;
}

/*
*****************************************************************************
* @brief Set Low limit value 
* @param Channel
* @param counter low limit value
* @return fail or success
*****************************************************************************
*/
uint8_t TACHO_Set_Low_Limit(uint8_t Channel, uint16_t countL)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	TACH->LIMITL = countL;
	return SUCCESS;
}

/*
*****************************************************************************
* @brief Get TACHO status
* @param Channel
* @return Status
*****************************************************************************
*/
uint16_t TACHO_Get_Status(uint8_t Channel)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	return (uint16_t)TACH->STS;
}

uint8_t TACHO_Clear_Status(uint8_t Channel,uint8_t sta)
{
	if(Channel > MAX_TACH_CH)
	{
		return FAIL;
	}
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));
	
	if(sta == COUNTER_EXCEED_LIMIT_STAT)
	{
		TACH->STS_b.LIMIT = 1;
	}
	if(sta == COUNTER_TOGGLE_STAT)
	{
		TACH->STS_b.CHG = 1;
	}
	if(sta == COUNTER_READY_STAT)
	{
		TACH->STS_b.CNTRDY = 1;
	}
	return SUCCESS;
}

uint8_t TACHO_isON(uint8_t Channel)
{
	if(Channel > MAX_TACH_CH)
		return FAIL;
	TACHO_Type* TACH;
	TACH = (TACHO_Type*)((uint32_t)TACHO0_BASE + (uint32_t)(Channel * 0x40UL));

	if(TACH->CTRL_b.EN)
		return SUCCESS;
	else 
		return FAIL;
}
