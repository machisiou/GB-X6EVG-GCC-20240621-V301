#ifndef __MBX_H__
#define __MBX_H__

#include <stdint.h>

extern uint8_t MBX_Set_IRQ_Number(uint8_t IRQnum);
extern uint8_t MBX_Enable_autoIRQ(uint8_t EnDis, uint8_t level);
extern uint8_t MBX_Enable_Interrupt(uint8_t EnDis);
extern uint8_t MBX_Read_Intsts(void);
extern uint8_t MBX_Clear_Intsts(void);
extern uint8_t MBX_Set_Status(uint8_t MBXSTS);
extern uint8_t MBX_Get_Status(void);
extern uint8_t MBX_Set_Data(uint8_t offset, uint8_t data);
extern uint8_t MBX_Get_Data(uint8_t offset);

#endif
