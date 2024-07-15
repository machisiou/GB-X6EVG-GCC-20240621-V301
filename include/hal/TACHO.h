#ifndef __TACHO_H__
#define __TACHO_H__

#include <stdint.h>
#include "system/Type.h"

extern uint8_t TACHO_Init(uint8_t Channel);
extern uint16_t TACHO_Read_Count(uint8_t Channel);
extern uint8_t TACHO_Reset_Count(uint8_t Channel);
extern uint8_t TACHO_Enable_Interrupt(uint8_t Channel, uint8_t intnum);
extern uint8_t TACHO_Disable_Interrupt(uint8_t Channel, uint8_t intnum);
extern uint16_t TACHO_Get_Status(uint8_t Channel);
extern uint8_t TACHO_Clear_Status(uint8_t Channel, uint8_t sta);
extern uint8_t TACHO_Set_Mode(uint8_t Channel, uint8_t mode);
extern uint8_t TACHO_Set_High_Limit(uint8_t Channel, uint16_t countH);
extern uint8_t TACHO_Set_Low_Limit(uint8_t Channel, uint16_t countL);
extern uint8_t TACHO_Set_Edge(uint8_t Channel, uint8_t EdgeNum);
extern uint8_t TACHO_Set_Filter(uint8_t Channel, uint8_t filterEn);
extern uint8_t TACHO_isON(uint8_t Channel);

#define MAX_TACH_CH						4

#define TACHO_ch0						0
#define TACHO_ch1						1
#define TACHO_ch2						2
#define TACHO_ch3						3

#define FILTERENABLE					1
#define FILTERDISABLE					0

#define PERIODS_4						3
#define PERIODS_2						2
#define PERIODS_1						1
#define PERIODS_0_5						0

#define RISING_EDGE_MODE_100KHZ			1
#define RISING_EDGE_MODE				0

#define TACHO_STATUS_TOGGLE				BIT2

#define COUNTER_EXCEED_LIMIT_STAT		BIT0
#define COUNTER_TOGGLE_STAT				BIT2
#define COUNTER_READY_STAT				BIT3
#endif
