#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

typedef enum _LED_Config {
	PWMOFF,
	LEDBREATH,
	LEDBLINKING,
	PWMON,
} _LED_Config;

typedef enum LED_En {
	OFF,
	ON,
} LED_En;


extern void LED_FullyOn(uint8_t Channel);
extern void LED_FullyOff(uint8_t Channel);
extern void LED_Config(uint8_t Channel, uint8_t Type, uint32_t Breathstep, uint32_t BreathInter, uint16_t BreathLdelay, uint16_t BreathHdelay, uint8_t Breathmin, uint8_t Breathmax);
extern void LED_GenCnt(uint8_t Channel, uint8_t PWMCnt);
extern void LED_Enable(uint8_t Channel, uint8_t On);
extern void LED_Invert(uint8_t Channel, uint8_t On);
extern void LED_Reset(uint8_t Channel);
#endif
