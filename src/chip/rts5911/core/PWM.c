#include "system/Type.h"
#include "hal/PWM.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Enable PWM channel
 * nPWM - PWM channel
 * return SUCCESS
*******************************************************************************/
uint8_t PWM_On(uint8_t nPWM, uint8_t OnOff)
{
	switch(nPWM) {
		case Pwm00:
			PWM0->CTRL_b.EN = OnOff;
			break;
		case Pwm01:
			PWM1->CTRL_b.EN = OnOff;
			break;
		case Pwm02:
			PWM2->CTRL_b.EN = OnOff;
			break;
		case Pwm03:
			PWM3->CTRL_b.EN = OnOff;
			break;
		case Pwm04:
			PWM4->CTRL_b.EN = OnOff;
			break;
		case Pwm05:
			PWM5->CTRL_b.EN = OnOff;
			break;
		case Pwm06:
			PWM6->CTRL_b.EN = OnOff;
			break;
		case Pwm07:
			PWM7->CTRL_b.EN = OnOff;
			break;
		case Pwm08:
			PWM8->CTRL_b.EN = OnOff;
			break;
		case Pwm09:
			PWM9->CTRL_b.EN = OnOff;
			break;
		case Pwm10:
			PWM10->CTRL_b.EN = OnOff;
			break;
		case Pwm11:
			PWM11->CTRL_b.EN = OnOff;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Reset PWM channel
 * nPWM - PWM channel
 * return SUCCESS
*******************************************************************************/
uint8_t PWM_Reset(uint8_t nPWM)
{
	switch(nPWM) {
		case Pwm00:
			PWM0->CTRL_b.RST = 1;
			break;
		case Pwm01:
			PWM1->CTRL_b.RST = 1;
			break;
		case Pwm02:
			PWM2->CTRL_b.RST = 1;
			break;
		case Pwm03:
			PWM3->CTRL_b.RST = 1;
			break;
		case Pwm04:
			PWM4->CTRL_b.RST = 1;
			break;
		case Pwm05:
			PWM5->CTRL_b.RST = 1;
			break;
		case Pwm06:
			PWM6->CTRL_b.RST = 1;
			break;
		case Pwm07:
			PWM7->CTRL_b.RST = 1;
			break;
		case Pwm08:
			PWM8->CTRL_b.RST = 1;
			break;
		case Pwm09:
			PWM9->CTRL_b.RST = 1;
			break;
		case Pwm10:
			PWM10->CTRL_b.RST = 1;
			break;
		case Pwm11:
			PWM11->CTRL_b.RST = 1;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Select PWM clock source
 * nPWM - PWM channel
 * Source - _50MHZ or _32KHZ
 * return SUCCESS
*******************************************************************************/
uint8_t PWM_Clock_Sel(uint8_t nPWM, uint8_t Source)
{
	switch(nPWM) {
		case Pwm00:
			PWM0->CTRL_b.CLKSRC = Source;
			break;
		case Pwm01:
			PWM1->CTRL_b.CLKSRC = Source;
			break;
		case Pwm02:
			PWM2->CTRL_b.CLKSRC = Source;
			break;
		case Pwm03:
			PWM3->CTRL_b.CLKSRC = Source;
			break;
		case Pwm04:
			PWM4->CTRL_b.CLKSRC = Source;
			break;
		case Pwm05:
			PWM5->CTRL_b.CLKSRC = Source;
			break;
		case Pwm06:
			PWM6->CTRL_b.CLKSRC = Source;
			break;
		case Pwm07:
			PWM7->CTRL_b.CLKSRC = Source;
			break;
		case Pwm08:
			PWM8->CTRL_b.CLKSRC = Source;
			break;
		case Pwm09:
			PWM9->CTRL_b.CLKSRC = Source;
			break;
		case Pwm10:
			PWM10->CTRL_b.CLKSRC = Source;
			break;
		case Pwm11:
			PWM11->CTRL_b.CLKSRC = Source;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Invert PWM signal
 * nPWM - PWM channel
 * Invt - NORMAL or INVERT
 * return SUCCESS
*******************************************************************************/
uint8_t PWM_Invert(uint8_t nPWM, uint8_t Invt)
{
	switch(nPWM) {
		case Pwm00:
			PWM0->CTRL_b.INVT = Invt;
			break;
		case Pwm01:
			PWM1->CTRL_b.INVT = Invt;
			break;
		case Pwm02:
			PWM2->CTRL_b.INVT = Invt;
			break;
		case Pwm03:
			PWM3->CTRL_b.INVT = Invt;
			break;
		case Pwm04:
			PWM4->CTRL_b.INVT = Invt;
			break;
		case Pwm05:
			PWM5->CTRL_b.INVT = Invt;
			break;
		case Pwm06:
			PWM6->CTRL_b.INVT = Invt;
			break;
		case Pwm07:
			PWM7->CTRL_b.INVT = Invt;
			break;
		case Pwm08:
			PWM8->CTRL_b.INVT = Invt;
			break;
		case Pwm09:
			PWM9->CTRL_b.INVT = Invt;
			break;
		case Pwm10:
			PWM10->CTRL_b.INVT = Invt;
			break;
		case Pwm11:
			PWM11->CTRL_b.INVT = Invt;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Set PWM duty cycle
 * nPWM - PWM channel
 * Duty - Duty cycle value
 * return SUCCESS
*******************************************************************************/
uint8_t PWM_Set_Duty(uint8_t nPWM, uint32_t Duty)
{
	switch(nPWM) {
		case Pwm00:
			PWM0->DUTY = Duty;
			break;
		case Pwm01:
			PWM1->DUTY = Duty;
			break;
		case Pwm02:
			PWM2->DUTY = Duty;
			break;
		case Pwm03:
			PWM3->DUTY = Duty;
			break;
		case Pwm04:
			PWM4->DUTY = Duty;
			break;
		case Pwm05:
			PWM5->DUTY = Duty;
			break;
		case Pwm06:
			PWM6->DUTY = Duty;
			break;
		case Pwm07:
			PWM7->DUTY = Duty;
			break;
		case Pwm08:
			PWM8->DUTY = Duty;
			break;
		case Pwm09:
			PWM9->DUTY = Duty;
			break;
		case Pwm10:
			PWM10->DUTY = Duty;
			break;
		case Pwm11:
			PWM11->DUTY = Duty;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Get PWM duty cycle
 * nPWM - PWM channel
 * return PWM dytu cycle value
*******************************************************************************/
uint32_t PWM_Get_Duty(uint8_t nPWM)
{
	uint32_t rDuty=0xFFFFFFFF;
	switch(nPWM) {
		case Pwm00:
			rDuty = PWM0->DUTY;
			break;
		case Pwm01:
			rDuty = PWM1->DUTY;
			break;
		case Pwm02:
			rDuty = PWM2->DUTY;
			break;
		case Pwm03:
			rDuty = PWM3->DUTY;
			break;
		case Pwm04:
			rDuty = PWM4->DUTY;
			break;
		case Pwm05:
			rDuty = PWM5->DUTY;
			break;
		case Pwm06:
			rDuty = PWM6->DUTY;
			break;
		case Pwm07:
			rDuty = PWM7->DUTY;
			break;
		case Pwm08:
			rDuty = PWM8->DUTY;
			break;
		case Pwm09:
			rDuty = PWM9->DUTY;
			break;
		case Pwm10:
			rDuty = PWM10->DUTY;
			break;
		case Pwm11:
			rDuty = PWM11->DUTY;
			//break;
	}
	return rDuty;
}

/******************************************************************************/
/** Set PWM duty cycle
 * nPWM - PWM channel
 * Div - Clock source divider
 * return SUCCESS
*******************************************************************************/
uint8_t PWM_Set_Divider(uint8_t nPWM, uint32_t Div)
{
	switch(nPWM) {
		case Pwm00:
			PWM0->DIV = Div;
			break;
		case Pwm01:
			PWM1->DIV = Div;
			break;
		case Pwm02:
			PWM2->DIV = Div;
			break;
		case Pwm03:
			PWM3->DIV = Div;
			break;
		case Pwm04:
			PWM4->DIV = Div;
			break;
		case Pwm05:
			PWM5->DIV = Div;
			break;
		case Pwm06:
			PWM6->DIV = Div;
			break;
		case Pwm07:
			PWM7->DIV = Div;
			break;
		case Pwm08:
			PWM8->DIV = Div;
			break;
		case Pwm09:
			PWM9->DIV = Div;
			break;
		case Pwm10:
			PWM10->DIV = Div;
			break;
		case Pwm11:
			PWM11->DIV = Div;
			break;
		default:
			return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Get PWM divider value
 * nPWM - PWM channel
 * return PWM divider value
*******************************************************************************/
uint32_t PWM_Get_Divider(uint8_t nPWM)
{
	uint32_t rDiv=0xFFFFFFFF;
	switch(nPWM) {
		case Pwm00:
			rDiv = PWM0->DIV;
			break;
		case Pwm01:
			rDiv = PWM1->DIV;
			break;
		case Pwm02:
			rDiv = PWM2->DIV;
			break;
		case Pwm03:
			rDiv = PWM3->DIV;
			break;
		case Pwm04:
			rDiv = PWM4->DIV;
			break;
		case Pwm05:
			rDiv = PWM5->DIV;
			break;
		case Pwm06:
			rDiv = PWM6->DIV;
			break;
		case Pwm07:
			rDiv = PWM7->DIV;
			break;
		case Pwm08:
			rDiv = PWM8->DIV;
			break;
		case Pwm09:
			rDiv = PWM9->DIV;
			break;
		case Pwm10:
			rDiv = PWM10->DIV;
			break;
		case Pwm11:
			rDiv = PWM11->DIV;
			//break;
	}
	return rDiv;
}
