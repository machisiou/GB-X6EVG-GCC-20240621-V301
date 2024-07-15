#ifndef __KBC_Command_H__
#define __KBC_Command_H__

#include <stdint.h>

#define AOBF			BIT5
#define KEYL			BIT4
#define SYSF			BIT2

extern void KBC_Process(void);
extern void Service_KBC_OBF(void);
extern void Kbcwritedata(uint8_t Value);
extern void Data2Host(uint8_t data_byte);
extern void KBC_DataQueuing(uint8_t nQueuing);
extern uint8_t Get_KBData_From_Queue(void);
extern void KBD_Process(void);

extern void KBC_64PORT(void);
extern void HOOK_64PORT(void);
extern void KBC_20CMD(void);
extern void KBC_60CMD(void);
extern void KBC_A4CMD(void);
extern void KBC_A5CMD(void);
extern void KBC_A6CMD(void);
extern void KBC_A7CMD(void);
extern void KBC_A8CMD(void);
extern void KBC_A9CMD(void);
extern void KBC_AACMD(void);
extern void KBC_ABCMD(void);
extern void KBC_ACCMD(void);
extern void KBC_ADCMD(void);
extern void KBC_AECMD(void);
extern void KBC_C0CMD(void);
extern void KBC_C1CMD(void);
extern void KBC_C2CMD(void);
extern void KBC_D0CMD(void);
extern void KBC_D1CMD(void);
extern void KBC_D2CMD(void);
extern void KBC_D3CMD(void);
extern void KBC_D4CMD(void);
extern void KBC_E0CMD(void);
extern void KBC_FXCMD(void);
extern void HOOK_60PORT(void);
extern void KBC_60PORT(void);
extern void KBC_60DATA(void);
extern void KBC_A5DATA(void);
extern void KBC_D1DATA(void);
extern void KBC_D2DATA(void);
extern void KBC_D3DATA(void);
extern void KBC_D4DATA(void);

extern void Aux_Data_To_Host(uint8_t data_byte);
extern void SendFromAux(uint8_t auxdata);
extern void SendCmdtoMouse(uint8_t PortNum);
extern void ResetMSPendingData(void);
extern void SetPS2CmdACKCounter(uint8_t ackcunt);

#endif
