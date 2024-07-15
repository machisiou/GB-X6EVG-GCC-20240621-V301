#ifndef __ACPI_H__
#define __ACPI_H__

#include <stdint.h>

extern uint8_t ACPI_Init(void);
extern uint8_t ACPI_Change_PortAddr(uint16_t _62addr, uint8_t _66offset);
extern uint8_t ACPI_Set_IRQ_Number(uint8_t IRQnum);
extern uint8_t ACPI_Enable_autoIRQ(uint8_t EnDis, uint8_t level);
extern uint8_t ACPI_Enable_Interrupt(uint8_t IBOB, uint8_t EnDis);
extern uint8_t ACPI_Is_OBF(void);
extern uint8_t ACPI_Is_IBF(void);
extern uint8_t ACPI_Is_CMD(void);
extern uint8_t ACPI_Is_BURST(void);
extern void ACPI_BURST_Set(void);
extern void ACPI_BURST_Clr(void);
extern uint8_t ACPI_Get_Status(void);
extern uint8_t ACPI_Set_Status(uint8_t FlagNum, uint8_t Value);
extern uint8_t ACPI_ForceClr_Status(uint8_t IBOB);
extern uint8_t ACPI_Read(void);
extern uint8_t ACPI_Write(uint8_t data);

#endif
