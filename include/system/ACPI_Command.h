#ifndef __ACPI_Command_H__
#define __ACPI_Command_H__

#include <stdint.h>

#define SMIEVT			BIT6
#define SCIEVT			BIT5

#define ACPISCI			0x00
#define QeventSCI		0x01

extern void ACPI_Process(void);
extern uint8_t ACPI_Burst_wait(void);

extern void ACPI_66PORT(void);
extern void ACPI_80CMD(void);
extern void ACPI_81CMD(void);
extern void ACPI_82CMD(void);
extern void ACPI_83CMD(void);
extern void ACPI_84CMD(void);

extern void ACPI_62PORT(void);
extern void ACPI_80DATA(void);
extern void ACPI_81DATA(void);
extern void ACPI_82DATA(void);
extern void ACPI_83DATA(void);
extern void ACPI_84DATA(void);

extern void ACPI2HOST(uint8_t acpiData);
extern void QeventSend(uint8_t Qnumber);
extern void ACPI_SCI_OUT(uint8_t Qevent);
extern void SCI_ON(void);
extern void SCI_OFF(void);
extern void ECSpace_Write(uint8_t offset, uint8_t data);
extern uint8_t ECSpace_Read(uint8_t offset);

extern void oem_set_acpi_event_pending(void);
extern void oem_clr_acpi_event_pending(void);

extern void ACPI_SMBusCmd(void);
extern void ResetSCIEvent(void);
#endif
