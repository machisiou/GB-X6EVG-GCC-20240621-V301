#ifndef __P80P81_H__
#define __P80P81_H__

#include <stdint.h>

extern uint8_t Port80_2_UART(uint8_t EnDis);
extern uint8_t Port80_Enalbe_Threshold(uint8_t EnDis, uint8_t ByteCount);
extern uint8_t Port80_Enalbe_Thershold_INT(uint8_t EnDis);
extern uint8_t Port80_Get_Port_Status(void);
extern uint8_t Port80_Clear_Port_Status(void);
extern uint8_t Port80_Get_Data(void);
extern uint8_t Port80_Change_Addr(uint8_t P80addr);
extern uint8_t Port81_Enalbe_Threshold(uint8_t EnDis, uint8_t ByteCount);
extern uint8_t Port81_Enalbe_Thershold_INT(uint8_t EnDis);
extern uint8_t Port81_Get_Port_Status(void);
extern uint8_t Port81_Clear_Port_Status(void);
extern uint8_t Port81_Get_Data(void);
extern uint8_t Port81_Change_Addr(uint8_t P81addr);

#endif
