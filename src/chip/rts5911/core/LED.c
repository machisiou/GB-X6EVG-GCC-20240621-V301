#include "hal/LED.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** LED Fully On
 * Channel - Select Channel 0~1
 * return None
*******************************************************************************/
void LED_FullyOn(uint8_t Channel)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	Ptr->MODE_b.SEL = LEDBLINKING;							/* Config as LedBlinking */
	Ptr->DL_b.MINV = 0xFF;									/* Config Duty Cycle Range = 0xFF */
	Ptr->CTRL_b.OUTPUT = 0;									/* Config PWM generator Number as always */
	Ptr->CTRL_b.EN = 1;										/* Enable PWM generator */
}

/******************************************************************************/
/** LED Fully Off
 * Channel - Select Channel 0~1
 * return None
*******************************************************************************/
void LED_FullyOff(uint8_t Channel)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	Ptr->MODE_b.SEL = LEDBLINKING;							/* Config as LedBlinking */
	Ptr->DL_b.MINV = 0x00;									/* Config Duty Cycle Range = 0x00 */
	Ptr->CTRL_b.OUTPUT = 0;									/* Config PWM generator Number as always */
	Ptr->CTRL_b.EN = 1;										/* Enable PWM generator */
}

/******************************************************************************/
/** LED Configure
 * Channel - Select Channel 0~1
 * Type - 0:Breathing mode, 1:Blinking mode
 * if Type = 0
 * Breathstep: Set Increase/decrease duty cycle for each step
 * Bit0~3:step 0    4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit4~7:step 1    4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit8~11:step 2   4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit12~15:step 3  4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit16~19:step 4  4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit20~23:step 5  4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit24~27:step 6  4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * Bit28~31:step 7  4'h0=> 1 duty cycle, 4'hF=> 16 duty cycle
 * BreathInter: Set delay PWM period for each step
 * Bit0~3:step 0    4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit4~7:step 1    4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit8~11:step 2   4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit12~15:step 3  4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit16~19:step 4  4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit20~23:step 5  4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit24~27:step 6  4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * Bit28~31:step 7  4'h0=> wait 1 PWM period, 4'hF=> wait 16 PWM period
 * BreathLdelay: Breathing mode delay when achieve min threshold
 * Bit0~11:  12'h0=> wait 1 PWM period, 12'hFFF=> wait 4096 PWM period
 * BreathHdelay: Breathing mode delay when achieve max threshold
 * Bit0~11:  12'h0=> wait 1 PWM period, 12'hFFF=> wait 4096 PWM period
 * Breathmin: Breathing mode min duty cycle threshold
 * Bit0~7:  8'h0=> 0 duty cycle, 8'hFF=> 255 duty cycle
 * Breathmax: Breathing mode max duty cycle threshold
 * Bit0~7:  8'h0=> 0 duty cycle, 8'hFF=> 255 duty cycle
 * if Type = 1
 * Pre-scale	Blinking Frequency
 *   0x00	           128Hz
 *   0x01	            64Hz
 *   0x03	            32Hz
 *   0x7F	             1Hz
 *   0xFF	           0.5Hz
 *  0x1FF	          0.25Hz
 * Breathmin: Duty cycle range
 * Bit0~7:  8'h0=> 0 duty cycle, 8'hFF=> 255 duty cycle
 * return None
*******************************************************************************/
void LED_Config(uint8_t Channel, uint8_t Type, uint32_t Breathstep, uint32_t BreathInter,
    uint16_t BreathLdelay, uint16_t BreathHdelay, uint8_t Breathmin, uint8_t Breathmax)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	if(Type == LEDBREATH) {
		Ptr->MODE_b.SEL = LEDBREATH;							/* Config as LedBreathing */
		Ptr->SD = Breathstep;									/* Config Step */
		Ptr->ST = BreathInter;									/* Config Interval */
		Ptr->WT_b.LKV = BreathLdelay;							/* Config Delay time when arrival min duty */
		Ptr->WT_b.HKV = BreathHdelay;							/* Config Delay time when arrival max duty */
		Ptr->DL_b.MINV = Breathmin;								/* Config Duty cycle min */
		Ptr->DL_b.MAXV = Breathmax;								/* Config Duty cycle max */
	}
	else if(Type == LEDBLINKING) {
		Ptr->MODE_b.SEL = LEDBLINKING;							/* Config as LedBlinking */
		Ptr->WT_b.LKV = BreathLdelay;							/* Config Prescale */
		Ptr->DL_b.MINV = Breathmin;								/* Config Duty cycle range */
	}
}

/******************************************************************************/
/**  Generate LED PWM Count
 * Channel - Select Channel 0~1
 * PWMCnt - Generate numbers of PWM (0: Means PWM period always on)
* return None
*******************************************************************************/
void LED_GenCnt(uint8_t Channel, uint8_t PWMCnt)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	if(PWMCnt != 0) {
		Ptr->CTRL_b.OUTPUT = 1;									/* Enable PWM number of Generator */
		Ptr->CTRL_b.CYCLE = PWMCnt;								/* Number of PWM */
	}
	else
		Ptr->CTRL_b.OUTPUT = 0;									/* Config PWM generator Number as always */
}

/******************************************************************************/
/**  LED Module Enable
 * Channel - Select Channel 0~1
 * On - 0: Disable, 1: Enable
 * return None
*******************************************************************************/
void LED_Enable(uint8_t Channel, uint8_t On)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	Ptr->CTRL_b.EN = On;
}

/******************************************************************************/
/**  LED PWM Invert
 * Channel - Select Channel 0~1
 * On - 0: Disable, 1: Enable
 * return None
*******************************************************************************/
void LED_Invert(uint8_t Channel, uint8_t On)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	Ptr->CTRL_b.INV = On;
}

/******************************************************************************/
/**  LED PWM Module Reset
 * Channel - Select Channel 0~1
 * return None
*******************************************************************************/
void LED_Reset(uint8_t Channel)
{
	PWMLED_Type* Ptr;
	Ptr = (PWMLED_Type*)((uint32_t)PWMLED0_BASE + (uint32_t)(Channel * 0x018UL));
	Ptr->CTRL_b.RST = 1;
}
