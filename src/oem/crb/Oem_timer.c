#include "system/Type.h"
#include "hal/TIMER.h"
#include "hal/SYSTEM.h"
#include "hal/WDT.h"
#include "oem/crb/Oem_timer.h"
#include "system/peripheral.h"
#include "system/interrupt.h"
void Initial_GPIO();
// 32-2 10us delay(10us)
// 32-3 ACPI burst (2ms)
// 32-4 SBMus time-out (26ms)

/******************************************************************************/
/** us delay
*******************************************************************************/
/*	if i=0x0A; from Start to B about 40.88us
	i increase 1, delay increase about 4us
	initial i value about 0.48us
	i=1; about 7.76us
	i=2; about 11.44us
	i=3; about 15.12us

	Here is code Start
	i=2;			// Here is A =>> A to B about 10.96us
	while(--i) {}	// Here is B => Start to B about 11.44us
*/

/******************************************************************************/
/** Use CPU tune for 10us delay base
 * Clock source 25MHz and 12.5MHZ(divider is 2)
*******************************************************************************/
void delay_10us(uint32_t times) 
{
	if (SYSTEM->SYSCLK == 4) {
		for (uint32_t i = 2; i < times * 2; i++) {
			__NOP();
		}
		return;
	} else if (SYSTEM->SYSCLK == 0) {
		for (uint32_t i = 3; i < times * 4; i++) {
			__NOP();
		}
	}
	return;
}

/******************************************************************************/
/** Use timer2 for 10us delay
 * Clock source 25MHz, divider is 16
 * 1.5625Mhz => 0.64us, 0.64us*14=8.96us
 * return SUCCESS
*******************************************************************************/
uint8_t timer322_10usDelay_Setting(void)
{
	TIME32_Type T2;

	T2.Tmr_Num = TIMER2;
	T2.LoadCount = 14;
	T2.Mode = One_Shut;
	T2.MASK_INT = disable;
	T2.OnOff = 0;
	TIMER32_Config(&T2);

	return SUCCESS;
}

/******************************************************************************/
/** touch and wait 10us time-out
 * return SUCCESS
*******************************************************************************/
uint8_t _10usDelay_wait(void)
{
	TIMER32_Enable(TIMER2, enable);

	while(!TIMER32_Read_Intsts(TIMER2)) {
	}

	TIMER32_Enable(TIMER2, disable);
	TIMER32_Clear_Intsts(TIMER2);
	return SUCCESS;
}

/******************************************************************************/
/** Use timer3 for ACPIburst mode
 * Clock source 25MHz, divider is 16
 * 1.5625Mhz => 0.64us, 0.64us*2950=1.888ms
 * code setting time about 120us
 * return SUCCESS
*******************************************************************************/
uint8_t timer323_BurstMode_Setting(void)
{
	TIME32_Type T3;

	T3.Tmr_Num = TIMER3;
	T3.LoadCount = 2950;
	T3.Mode = One_Shut;
	T3.MASK_INT = disable;
	T3.OnOff = 0;
	TIMER32_Config(&T3);

	return SUCCESS;
}

/******************************************************************************/
/** touch to count 2ms time-out
 * return SUCCESS
*******************************************************************************/
uint8_t BurstMode_touch(void)
{
	TIMER32_Enable(TIMER3, enable);
	return SUCCESS;
}

/******************************************************************************/
/** touch to count 2ms time-out
 * return SUCCESS
*******************************************************************************/
uint8_t BurstMode_check(void)
{
	if(TIMER32_Read_Intsts(TIMER3)) {
		TIMER32_Enable(TIMER3, disable);
		TIMER32_Clear_Intsts(TIMER3);
		return SUCCESS;
	}
	return FAIL;
}

/******************************************************************************/
/** Use timer4 for SMBus 26ms timeout
 * Clock source 25MHz, divider is 8
 * 3.125Mhz => 0.32us, 0.32us*81=25.92ms
 * code setting time about 120us
 * return SUCCESS
*******************************************************************************/
uint8_t timer324_SMBus26ms_Setting(void)
{
	TIME32_Type T4;

	T4.Tmr_Num = TIMER4;
	T4.LoadCount = 81;
	T4.Mode = One_Shut;
	T4.MASK_INT = disable;
	T4.OnOff = 0;
	TIMER32_Config(&T4);

	return SUCCESS;
}

/******************************************************************************/
/** touch to count 26ms time-out
 * return SUCCESS
*******************************************************************************/
uint8_t SMBus26ms_touch(void)
{
	TIMER32_Enable(TIMER4, enable);
	return SUCCESS;
}

/******************************************************************************/
/** touch to count 26ms time-out
 * return SUCCESS
*******************************************************************************/
uint8_t SMBus26ms_check(void)
{
	if(TIMER32_Read_Intsts(TIMER4)) {
		TIMER32_Enable(TIMER4, disable);
		TIMER32_Clear_Intsts(TIMER4);
		return SUCCESS;
	}
	return FAIL;
}

/******************************************************************************/
/** Use SLWT1 count Xms for waitting
 * 1ms=>1.16ms, 2ms=>2.17ms, 3ms=>3.16ms
 * Correction ... setting time about 0.16ms
 * return SUCCESS
*******************************************************************************/
uint8_t _Delay_1ms(uint16_t ms)
{
	RSTIMER_Type delay_SLWT1;

	if(ms==0) return FAIL;
	delay_SLWT1.Tmr_Num = STIMER1;
	delay_SLWT1.LoadCount = (ms * 1000)-160;
	delay_SLWT1.Mode = One_Shut;
	delay_SLWT1.INT_En = enable;
	delay_SLWT1.OnOff = 1;
	SLWTIMER_Config(&delay_SLWT1);

	while(!SLWTIMER_Read_Intsts(delay_SLWT1.Tmr_Num)) {}
	SLWTIMER_Enable(STIMER1, disable);
	SLWTIMER_Clear_Intsts(delay_SLWT1.Tmr_Num);

	return SUCCESS;
}

/******************************************************************************/
/** Enable PWRBTN WDT function
 *  dTIME press time, base on 1 second
*  TrigMode 0:low level 1:high level
*******************************************************************************/
void PWRBTN_WDT_Setting(uint8_t dTIME, uint8_t TrigMode)
{
	PWRBTN_WDT_Enable_Interrupt();
	PWRBTN_WDT_Disable_Rst();

	PWRBTN_WDT_Set_LoadValue(dTIME);
	PWRBTN_WDT_Set_Divider(0x8000);
	PWRBTN_WDT_Trig_Mode(TrigMode);

	PWRBTN_WDT_Enable_Interrupt();
	PWRBTN_WDT_Enable();
	PWRBTN_WDT_Enable_PB();
	PWRBTN_EnableIRQ();
}

/******************************************************************************/
/** Enable WDT function for restart
*******************************************************************************/
void WDT_NOW(void)
{
	WDT_Enable_Rst();
	WDT_Init(1, 1);
}

void InternalWDTNow(void)
{
	Initial_GPIO();
	WDT_Enable_Rst();
	WDT_Set_Divider(1);
	WDT_Set_LoadValue(1);
	WDT_Enable();
}

