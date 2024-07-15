#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

#define Pwm00 0x00
#define Pwm01 0x01
#define Pwm02 0x02
#define Pwm03 0x03
#define Pwm04 0x04
#define Pwm05 0x05
#define Pwm06 0x06
#define Pwm07 0x07
#define Pwm08 0x08
#define Pwm09 0x09
#define Pwm10 0x0A
#define Pwm11 0x0B

#define _50MHZ 0
#define _32KHZ 1

#define NORMAL 0
#define INVERT 1

extern uint8_t PWM_On(uint8_t nPWM, uint8_t OnOff);
extern uint8_t PWM_Reset(uint8_t nPWM);
extern uint8_t PWM_Clock_Sel(uint8_t nPWM, uint8_t Source);
extern uint8_t PWM_Invert(uint8_t nPWM, uint8_t Invt);
extern uint8_t PWM_Set_Duty(uint8_t nPWM, uint32_t Duty);
extern uint32_t PWM_Get_Duty(uint8_t nPWM);
extern uint8_t PWM_Set_Divider(uint8_t nPWM, uint32_t Div);
extern uint32_t PWM_Get_Divider(uint8_t nPWM);

#endif
