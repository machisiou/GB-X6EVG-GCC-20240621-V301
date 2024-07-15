#ifndef _PM2_H__
#define _PM2_H__

#include <stdint.h>

extern uint8_t PM2_Init(void);
extern uint8_t PM2_Change_PortAddr(uint16_t PM2addr, uint8_t PM2offset);
extern uint8_t PM2_Set_IRQ_Number(uint8_t IRQnum);
extern uint8_t PM2_Enable_autoIRQ(uint8_t EnDis, uint8_t level);
extern uint8_t PM2_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis);
extern uint8_t PM2_Is_OBF(void);
extern uint8_t PM2_Is_IBF(void);
extern uint8_t PM2_Is_CMD(void);
extern uint8_t PM2_Get_Status(void);
extern uint8_t PM2_Set_Status(uint8_t FlagNum, uint8_t Value);
extern uint8_t PM2_ForceClr_Status(uint8_t IBOB);
extern uint8_t PM2_Read(void);
extern uint8_t PM2_Write(uint8_t data);

#endif
