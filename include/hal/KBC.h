#ifndef __KBC_H__
#define __KBC_H__

#include <stdint.h>

#define _OBF 0
#define _IBF 1

extern uint8_t KBC_Init(void);
extern uint8_t KBC_Change_PortAddr(uint16_t _60addr, uint8_t _64offset);
extern uint8_t KBC_Set_IRQ_Number(uint8_t IRQnum);
extern uint8_t KBC_Enable_autoIRQ(uint8_t EnDis, uint8_t level);
extern uint8_t KBC_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis);
extern uint8_t KBC_Is_OBF(void);
extern uint8_t KBC_Is_IBF(void);
extern uint8_t KBC_Is_CMD(void);
extern uint8_t KBC_Get_Status(void);
extern uint8_t KBC_Set_Status(uint8_t FlagNum, uint8_t Value);
extern uint8_t KBC_ForceClr_Status(uint8_t IBOB);
extern uint8_t KBC_Read(void);
extern uint8_t KBC_Write(uint8_t data);

#endif
