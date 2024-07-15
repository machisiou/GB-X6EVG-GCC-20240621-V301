#ifndef _PM3_H__
#define _PM3_H__

#include <stdint.h>

extern uint8_t PM3_Init(void);
extern uint8_t PM3_Change_PortAddr(uint16_t PM3addr, uint8_t PM3offset);
extern uint8_t PM3_Set_IRQ_Number(uint8_t IRQnum);
extern uint8_t PM3_Enable_autoIRQ(uint8_t EnDis, uint8_t level);
extern uint8_t PM3_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis);
extern uint8_t PM3_Is_OBF(void);
extern uint8_t PM3_Is_IBF(void);
extern uint8_t PM3_Is_CMD(void);
extern uint8_t PM3_Get_Status(void);
extern uint8_t PM3_Set_Status(uint8_t FlagNum, uint8_t Value);
extern uint8_t PM3_ForceClr_Status(uint8_t IBOB);
extern uint8_t PM3_Read(void);
extern uint8_t PM3_Write(uint8_t data);

#endif
