#ifndef __KBM_H__
#define __KBM_H__

#include <stdint.h>

extern void KBM_Write_KSOL(uint32_t KSONum);
extern void KBM_Write_KSO_All_High(void);
extern void KBM_Write_KSO_All_Low(void);
extern _Bool KBM_Read_KSI(uint8_t KSINum);
extern uint32_t KBM_Read_All_KSI(void);
extern void KBM_Extra_KSO_Config(uint8_t KSONum, uint8_t Enable);
extern void KBM_Extra_KSI_Config(uint8_t KSINum, uint8_t Enable);
extern void KBM_Intr_Config(uint32_t KSINum, uint8_t Enable);
extern void KBM_Output_Type(uint8_t Type);
extern void KBM_ClrIntr(void);

extern void KSI_Intr_Enable(void);
extern void KSI_Intr_Disable(void);

#endif
