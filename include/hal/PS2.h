#ifndef __PS2_H__
#define __PS2_H__

#include <stdint.h>

#define Receive_Mode 1
#define Transmit_Mode 2
#define Inhibit_Mode 3

#define GPIO092 92
#define GPIO096 96

extern uint8_t PS2_On(void);
extern uint8_t PS2_Reset(void);
extern uint8_t PS2_Enable_Interrupt(uint8_t EnDis);
extern uint8_t PS2_Read_STS(void);
extern uint8_t PS2_Clear_STS(uint8_t Flag);
extern uint8_t PS2_SetTxBuf(uint8_t uData);
extern uint8_t PS2_GetRxBuf(void);
extern uint8_t PS2_WriteByte(uint8_t uData);
extern uint8_t PS2_Mode_Change(uint8_t Mode, uint8_t ClkPin);

#endif
