#include "system/Type.h"
#include "hal/TIMER.h"
#include "hal/SYSTEM.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Load count into TIMER32 timer
 * N_timer - TIMER number
 * LoadCount - count number
 * return SUCCESS
*******************************************************************************/
uint8_t TIMER32_Load_Count(uint8_t N_timer, uint32_t LoadCount)
{
	switch(N_timer) {
		case TIMER0:
			TMR0->LDCNT = LoadCount;
			break;
		case TIMER1:
			TMR1->LDCNT = LoadCount;
			break;
		case TIMER2:
			TMR2->LDCNT = LoadCount;
			break;
		case TIMER3:
			TMR3->LDCNT = LoadCount;
			break;
		case TIMER4:
			TMR4->LDCNT = LoadCount;
			break;
		case TIMER5:
			TMR5->LDCNT = LoadCount;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Set TIMER32 timer counter mode
 * N_timer - TIMER number
 * Mode - One_Shut or Continuous
 * return SUCCESS
*******************************************************************************/
uint8_t TIMER32_Set_Mode(uint8_t N_timer, uint8_t Mode)
{
	switch(N_timer) {
		case TIMER0:
			TMR0->CTRL_b.MDSEL = Mode;
			break;
		case TIMER1:
			TMR1->CTRL_b.MDSEL = Mode;
			break;
		case TIMER2:
			TMR2->CTRL_b.MDSEL = Mode;
			break;
		case TIMER3:
			TMR3->CTRL_b.MDSEL = Mode;
			break;
		case TIMER4:
			TMR4->CTRL_b.MDSEL = Mode;
			break;
		case TIMER5:
			TMR5->CTRL_b.MDSEL = Mode;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable TIMER32 timer interrupt mask
 * N_timer - TIMER number
 * EnDis - MASK_INT_OFF(use INT) or MASK_INT_ON(don't use INT)
 * return SUCCESS
 * PS. No interrupt no INTSTS
*******************************************************************************/
uint8_t TIMER32_Enable_INT_Mask(uint8_t N_timer, uint8_t EnDis)
{
	switch(N_timer) {
		case TIMER0:
			TMR0->CTRL_b.INTMSK = EnDis;
			break;
		case TIMER1:
			TMR1->CTRL_b.INTMSK = EnDis;
			break;
		case TIMER2:
			TMR2->CTRL_b.INTMSK = EnDis;
			break;
		case TIMER3:
			TMR3->CTRL_b.INTMSK = EnDis;
			break;
		case TIMER4:
			TMR4->CTRL_b.INTMSK = EnDis;
			break;
		case TIMER5:
			TMR5->CTRL_b.INTMSK = EnDis;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable TIMER32 timer
 * N_timer - TIMER number
 * EnDis - 1:enable 0:disable
 * return SUCCESS
*******************************************************************************/
uint8_t TIMER32_Enable(uint8_t N_timer, uint8_t EnDis)
{
	switch(N_timer) {
		case TIMER0:
			TMR0->CTRL_b.EN = EnDis;
			break;
		case TIMER1:
			TMR1->CTRL_b.EN = EnDis;
			break;
		case TIMER2:
			TMR2->CTRL_b.EN = EnDis;
			break;
		case TIMER3:
			TMR3->CTRL_b.EN = EnDis;
			break;
		case TIMER4:
			TMR4->CTRL_b.EN = EnDis;
			break;
		case TIMER5:
			TMR5->CTRL_b.EN = EnDis;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read TIMER32 interrupt status
 * N_timer - TIMER number
 * return Interrupt status
*******************************************************************************/
uint8_t TIMER32_Read_Intsts(uint8_t N_timer)
{
	uint8_t STS=0;
	switch(N_timer) {
		case TIMER0:
			STS = TMR0->INTSTS_b.STS;
			break;
		case TIMER1:
			STS = TMR1->INTSTS_b.STS;
			break;
		case TIMER2:
			STS = TMR2->INTSTS_b.STS;
			break;
		case TIMER3:
			STS = TMR3->INTSTS_b.STS;
			break;
		case TIMER4:
			STS = TMR4->INTSTS_b.STS;
			break;
		case TIMER5:
			STS = TMR5->INTSTS_b.STS;
			break;
		default:
			return ERROR;
	}
	return STS;
}

/******************************************************************************/
/** Clear TIMER32 interrupt status
 * N_timer - TIMER number
 * return SUCCESS
*******************************************************************************/
uint8_t TIMER32_Clear_Intsts(uint8_t N_timer)
{
	switch(N_timer) {
		case TIMER0:
			SYSTEM->TMRRST_b.TMR0RST = 0;
			while(TMR0->INTSTS_b.STS)
				TMR0->INTCLR;
			SYSTEM->TMRRST_b.TMR0RST = 1;
			break;
		case TIMER1:
			SYSTEM->TMRRST_b.TMR1RST = 0;
			while(TMR1->INTSTS_b.STS)
				TMR1->INTCLR;
			SYSTEM->TMRRST_b.TMR1RST = 1;
			break;
		case TIMER2:
			SYSTEM->TMRRST_b.TMR2RST = 0;
			while(TMR2->INTSTS_b.STS)
				TMR2->INTCLR;
			SYSTEM->TMRRST_b.TMR2RST = 1;
			break;
		case TIMER3:
			SYSTEM->TMRRST_b.TMR3RST = 0;
			while(TMR3->INTSTS_b.STS)
				TMR3->INTCLR;
			SYSTEM->TMRRST_b.TMR3RST = 1;
			break;
		case TIMER4:
			SYSTEM->TMRRST_b.TMR4RST = 0;
			while(TMR4->INTSTS_b.STS)
				TMR4->INTCLR;
			SYSTEM->TMRRST_b.TMR4RST = 1;
			break;
		case TIMER5:
			SYSTEM->TMRRST_b.TMR5RST = 0;
			while(TMR5->INTSTS_b.STS)
				TMR5->INTCLR;
			SYSTEM->TMRRST_b.TMR5RST = 1;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Initial one TIMER32 parameter
 * Timer struct
 * return SUCCESS
*******************************************************************************/
uint8_t TIMER32_Config(TIME32_Type* tmr_ptr)
{
	TIMER32_Enable(tmr_ptr->Tmr_Num, disable);
	TIMER32_Set_Mode(tmr_ptr->Tmr_Num, tmr_ptr->Mode);
	TIMER32_Enable_INT_Mask(tmr_ptr->Tmr_Num, tmr_ptr->MASK_INT);
	TIMER32_Load_Count(tmr_ptr->Tmr_Num, tmr_ptr->LoadCount);
	TIMER32_Clear_Intsts(tmr_ptr->Tmr_Num);
	TIMER32_Enable(tmr_ptr->Tmr_Num, tmr_ptr->OnOff);
	return SUCCESS;
}

/******************************************************************************/
/** Load count into SLWTMR timer
 * N_timer - TIMER number
 * LoadCount - count number
 * return SUCCESS
*******************************************************************************/
uint8_t SLWTIMER_Load_Count(uint8_t N_timer, uint32_t LoadCount)
{
	switch(N_timer) {
		case STIMER0:
			SLWTMR0->LDCNT = LoadCount;
			break;
		case STIMER1:
			SLWTMR1->LDCNT = LoadCount;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Set SLWTMR timer counter mode
 * N_timer - TIMER number
 * Mode - One_Shut or Continuous
 * return SUCCESS
*******************************************************************************/
uint8_t SLWTIMER_Set_Mode(uint8_t N_timer, uint8_t Mode)
{
	switch(N_timer) {
		case STIMER0:
			SLWTMR0->CTRL_b.MDSEL = Mode;
			break;
		case STIMER1:
			SLWTMR1->CTRL_b.MDSEL = Mode;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable SLWTMR timer interrupt
 * N_timer - TIMER number
 * EnDis - 1:enable 0:disable
 * return SUCCESS
*******************************************************************************/
uint8_t SLWTIMER_Enable_Interrupt(uint8_t N_timer, uint8_t EnDis)
{
	switch(N_timer) {
		case STIMER0:
			SLWTMR0->CTRL_b.INTEN = EnDis;
			break;
		case STIMER1:
			SLWTMR1->CTRL_b.INTEN = EnDis;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable SLWTMR timer
 * N_timer - TIMER number
 * EnDis - 1:enable 0:disable
 * return SUCCESS
*******************************************************************************/
uint8_t SLWTIMER_Enable(uint8_t N_timer, uint8_t EnDis)
{
	switch(N_timer) {
		case STIMER0:
			SLWTMR0->CTRL_b.EN = EnDis;
			break;
		case STIMER1:
			SLWTMR1->CTRL_b.EN = EnDis;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Read SLWTMR interrupt status
 * N_timer - TIMER number
 * return Interrupt status
*******************************************************************************/
uint8_t SLWTIMER_Read_Intsts(uint8_t N_timer)
{
	uint8_t STS=0;
	switch(N_timer) {
		case STIMER0:
			STS = SLWTMR0->INTSTS_b.STS;
			break;
		case STIMER1:
			STS = SLWTMR1->INTSTS_b.STS;
			break;
		default:
			return ERROR;
	}
	return STS;
}

/******************************************************************************/
/** Clear SLWTMR interrupt status
 * N_timer - TIMER number
 * return SUCCESS
*******************************************************************************/
uint8_t SLWTIMER_Clear_Intsts(uint8_t N_timer)
{
	switch(N_timer) {
		case STIMER0:
			SLWTMR0->INTSTS_b.STS = 1;
			break;
		case STIMER1:
			SLWTMR1->INTSTS_b.STS = 1;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Initial SLWTMR parameter
 * Timer struct
 * return SUCCESS
*******************************************************************************/
uint8_t SLWTIMER_Config(RSTIMER_Type* tmr_ptr)
{
	SLWTIMER_Enable(tmr_ptr->Tmr_Num, disable);
	SLWTIMER_Load_Count(tmr_ptr->Tmr_Num, tmr_ptr->LoadCount);
	SLWTIMER_Set_Mode(tmr_ptr->Tmr_Num, tmr_ptr->Mode);
	SLWTIMER_Enable_Interrupt(tmr_ptr->Tmr_Num, tmr_ptr->INT_En);
	SLWTIMER_Clear_Intsts(tmr_ptr->Tmr_Num);
	SLWTIMER_Enable(tmr_ptr->Tmr_Num, tmr_ptr->INT_En);
	return SUCCESS;
}

/******************************************************************************/
/** Load count into RTMR timer
 * LoadCount - count number
 * return SUCCESS
*******************************************************************************/
uint8_t RTIMER_Load_Count(uint32_t LoadCount)
{
	RTMR->LDCNT = LoadCount;
	return SUCCESS;
}

/******************************************************************************/
/** Set RTMR timer counter mode
 * Mode - One_Shut or Continuous
 * return SUCCESS
*******************************************************************************/
uint8_t RTIMER_Set_Mode(uint8_t Mode)
{
	RTMR->CTRL_b.MDSEL = Mode;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable RTMR timer interrupt
 * EnDis - 1:enable 0:disable
 * return SUCCESS
*******************************************************************************/
uint8_t RTIMER_Enable_Interrupt(uint8_t EnDis)
{
	RTMR->CTRL_b.INTEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Enable/Disable RTMR timer
 * EnDis - 1:enable 0:disable
 * return SUCCESS
*******************************************************************************/
uint8_t RTIMER_Enable(uint8_t EnDis)
{
	RTMR->CTRL_b.EN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Read RTMR interrupt status
 * return Interrupt status
*******************************************************************************/
uint8_t RTIMER_Read_Intsts(void)
{
	uint8_t STS=0;
	STS = RTMR->INTSTS_b.STS;
	return STS;
}

/******************************************************************************/
/** Clear RTMR interrupt status
 * return SUCCESS
*******************************************************************************/
uint8_t RTIMER_Clear_Intsts(void)
{
	RTMR->INTSTS_b.STS = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Initial RTMR parameter
 * Timer struct
 * return SUCCESS
*******************************************************************************/
uint8_t RTIMER_Config(RSTIMER_Type* tmr_ptr)
{
	RTIMER_Enable(disable);
	RTIMER_Load_Count(tmr_ptr->LoadCount);
	RTIMER_Set_Mode(tmr_ptr->Mode);
	RTIMER_Enable_Interrupt(tmr_ptr->INT_En);
	RTIMER_Clear_Intsts();
	RTIMER_Enable(tmr_ptr->OnOff);
	return SUCCESS;
}
