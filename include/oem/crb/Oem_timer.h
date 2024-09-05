#ifndef __Oem_timer_H__
#define __Oem_timer_H__

#include <stdint.h>

//us=1; about 7.76us
//us=2; about 11.44us
//us=3; about 15.12us
#define Delay7us		uint8_t i=1; while(--i)
#define Delay11us		uint8_t i=2; while(--i)
#define Delay15us		uint8_t i=3; while(--i)
#define Delay19us		uint8_t i=4; while(--i)
#define Delay23us		uint8_t i=5; while(--i)
#define Delay27us		uint8_t i=6; while(--i)

// default Timer2 for 10us delay(10us)
// default Timer3 for ACPI burst mode(2ms)
// default Timer4 for SBMus time-out(26ms)
// default SLWTIME1 for ms waiting delay

extern void delay_10us(uint32_t);
extern uint8_t timer322_10usDelay_Setting(void);
extern uint8_t _10usDelay_wait(void);
extern uint8_t timer323_BurstMode_Setting(void);
extern uint8_t BurstMode_touch(void);
extern uint8_t BurstMode_check(void);
extern uint8_t timer324_SMBus26ms_Setting(void);
extern uint8_t SMBus26ms_touch(void);
extern uint8_t SMBus26ms_check(void);
extern uint8_t _Delay_1ms(uint16_t ms);
extern void PWRBTN_WDT_Setting(uint8_t dTIME, uint8_t TrigMode);
extern void WDT_NOW(void);
extern void InternalWDTNow(void);
#endif
