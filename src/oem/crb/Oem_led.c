#include "oem/crb/Oem_led.h"

static uint8_t CntDown;
static uint8_t Index_cnt;
static uint8_t Darktime;

void LED_Breath(uint8_t PwmCh)
{			        
	uint32_t PWMValue[] = {0, 156, 280, 405, 529, 653,
	777, 902, 1026, 1150, 1275, 1499, 1623, 1747, 1872, 2110};
	if (Darktime)
	{
		Darktime--;
		return;
	}

	if (CntDown)
	{
		Index_cnt--;

		if (Index_cnt == 0x00)
		{
			CntDown = 0;
		}
	}
	else
	{
		Index_cnt++;

		if (Index_cnt == 0x0F)
		{
			CntDown = 1;
			Darktime = 0x14; //Dark time value x time base
		}
	}
		PWM_Set_Duty(PwmCh,PWMValue[Index_cnt]);
}

void LED_Blink(uint8_t PwmCh)
{
	uint32_t PWMValue[] = {0,2110};
	if (CntDown)
	{
		Index_cnt--;

		if (Index_cnt == 0x00)
		{
			CntDown = 0;
		}
	}
	else
	{
		Index_cnt++;
		
		if (Index_cnt == 0x01)
		{
			CntDown = 1;
		}
	}
		PWM_Set_Duty(PwmCh,PWMValue[Index_cnt]);

}
