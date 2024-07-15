#ifndef __EMI_H__
#define __EMI_H__

#include <stdint.h>

#define EMI_0 0
#define EMI_1 1
#define EMI_2 2
#define EMI_3 3
#define EMI_4 4
#define EMI_5 5
#define EMI_6 6
#define EMI_7 7

extern uint8_t EMI_RW_Mode(uint8_t EMI_chl, uint8_t mode);
extern uint8_t EMI_Status_Loc(uint8_t EMI_chl, uint8_t offset);
extern uint8_t EMI_Enable_autoIRQ(uint8_t EMI_chl, uint8_t EnDis, uint8_t level);
extern uint8_t EMI_Set_IRQ_Number(uint8_t EMI_chl, uint8_t IRQnum);
extern uint8_t EMI_Enable_Interrupt(uint8_t EMI_chl, uint8_t EnDis);
extern uint8_t EMI_Set_SAR_Address(uint8_t EMI_chl, uint32_t SARaddr);
extern uint8_t EMI_Read_Intsts(uint8_t EMI_chl);
extern uint8_t EMI_Clear_Intsts(uint8_t EMI_chl);
extern uint8_t EMI_Config(uint32_t BaseAddr, uint32_t HostAddr);

#endif
