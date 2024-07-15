#ifndef __TIMER_H__
#define __TIMER_H__

// TIMER number define at SYSTEM.h
// timer clock source diver define at SYSTEM.h

#include <stdint.h>

#define One_Shut 0
#define Continuous 1

#define MASK_INT_OFF 0
#define MASK_INT_ON 1

typedef struct {
	uint8_t Tmr_Num;
	uint8_t Mode;
	uint8_t MASK_INT;
	uint8_t OnOff;
	uint32_t LoadCount;
}TIME32_Type;

typedef struct {
	uint8_t Tmr_Num;
	uint8_t Mode;
	uint8_t INT_En;
	uint8_t OnOff;
	uint32_t LoadCount;
}RSTIMER_Type;

extern uint8_t TIMER32_Load_Count(uint8_t N_timer, uint32_t LoadCount);
extern uint8_t TIMER32_Set_Mode(uint8_t N_timer, uint8_t Mode);
extern uint8_t TIMER32_Enable_INT_Mask(uint8_t N_timer, uint8_t EnDis);
extern uint8_t TIMER32_Enable(uint8_t N_timer, uint8_t EnDis);
extern uint8_t TIMER32_Read_Intsts(uint8_t N_timer);
extern uint8_t TIMER32_Clear_Intsts(uint8_t N_timer);
extern uint8_t TIMER32_Config(TIME32_Type* tmr_ptr);

extern uint8_t SLWTIMER_Load_Count(uint8_t N_timer, uint32_t LoadCount);
extern uint8_t SLWTIMER_Set_Mode(uint8_t N_timer, uint8_t Mode);
extern uint8_t SLWTIMER_Enable_Interrupt(uint8_t N_timer, uint8_t EnDis);
extern uint8_t SLWTIMER_Enable(uint8_t N_timer, uint8_t EnDis);
extern uint8_t SLWTIMER_Read_Intsts(uint8_t N_timer);
extern uint8_t SLWTIMER_Clear_Intsts(uint8_t N_timer);
extern uint8_t SLWTIMER_Config(RSTIMER_Type* tmr_ptr);

extern uint8_t RTIMER_Load_Count(uint32_t LoadCount);
extern uint8_t RTIMER_Set_Mode(uint8_t Mode);
extern uint8_t RTIMER_Enable_Interrupt(uint8_t EnDis);
extern uint8_t RTIMER_Enable(uint8_t EnDis);
extern uint8_t RTIMER_Read_Intsts(void);
extern uint8_t RTIMER_Clear_Intsts(void);
extern uint8_t RTIMER_Config(RSTIMER_Type* tmr_ptr);

#endif
