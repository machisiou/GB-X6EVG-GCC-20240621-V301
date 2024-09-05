#ifndef __GPIO_H__
#define __GPIO_H__

#include "system/Type.h"
#include <stdint.h>

#define FUNC0			0			// GPIO mode
#define FUNC1			BIT0		// Function mode use BIT0~2
#define FUNC2			BIT1
#define FUNC3			BIT0+BIT1
#define FUNC4			BIT2
#define GPIO_PINON		BIT3		// Pin EN : 1 enable 0 disable
#define GPIO_INOUT		BIT4		// IN/OUT : 0 input 1 output
#define GPIO_HILOW		BIT5		// OUTPUT : 0 low 1 high
#define GPIO_TYPE		BIT6		// TYPE : 0 push pull 1 open drain
#define GPIO_PULLUP		BIT7		// PULL UP : 0 disable 1 ebable
#define GPIO_PULLDN		BIT8		// PULL DOWN : 0 disable 1 ebable
#define GPIO_VOLT		BIT9		// Pin Volt : 1 1.8V 0 3.3V
#define GPIO_SCHMITTER	BIT10		// Schmitter : 1 ebable 0 disable
#define GPIO_DRIVING	BIT11		// DRIVING : 0 low driving capability 1 high driving capability
#define GPIO_SLEW		BIT12		// SLEW : 0 fast slew rate 1 slow slew rate

extern void GPIO_Init(const uint32_t* GPIOTbl);
extern void GPIO_Func_Mode(uint32_t GPIOnum, uint8_t Func);
extern void GPIO_Pin_On(uint32_t GPIOnum, uint8_t OnOff);
extern void GPIO_Set_IO(uint32_t GPIOnum, uint8_t InOut);
extern void GPIO_Write(uint32_t GPIOnum, uint8_t Level);
extern uint8_t GPIO_Read(uint32_t GPIOnum);
extern uint8_t GPIO_ReadType(uint32_t GPIOnum);
extern void GPIO_Config(uint32_t GPIOnum, uint8_t Type, uint8_t PullUp, uint8_t PullDn);
extern void GPIO_Set_Vlot(uint32_t GPIOnum, uint8_t Volt);
extern void GPIO_Set_Schmit(uint32_t GPIOnum, uint8_t Schmit);
extern void GPIO_Set_Driving(uint32_t GPIOnum, uint8_t Driv);
extern void GPIO_Set_Slew(uint32_t GPIOnum, uint8_t Slew);
extern void GPIO_Intr_Config(uint32_t GPIOnum, uint8_t Intr, uint8_t IntrTrigger);
extern void GPIO_ClrIntr(uint32_t GPIOnum);
extern uint8_t GPIO_ReadIOType(uint32_t GPIOnum);
#endif
