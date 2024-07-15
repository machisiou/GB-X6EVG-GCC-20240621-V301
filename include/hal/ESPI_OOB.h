#ifndef __ESPI_OOB_H__
#define __ESPI_OOB_H__

#include <stdint.h>

#define DTSNum		0x11
#define RTCNum		0x21
#define PINGNum		0x31
#define DIBNum		0x41
#define RDPKGNum	0x51
#define RDPKGIdx_CPUTjMax   0x52
#define RDPKGIdx_CPUTDP     0x53
#define RDPKGIdx_PL1        0x54
#define RDPKGIdx_PL2        0x55
#define RDPKGIdx_PL4        0x56
#define WRPKGNum	0x61

extern void OOB_SetBuffer(uint8_t* WriteBuffer, uint8_t* ReadBuffer);
extern uint8_t OOB_Start_Head(uint8_t length);
extern uint8_t OOB_WaitData_Back(uint8_t* ReadBuffer);

extern uint8_t OOB_GetPchTemperature(void);
extern uint8_t OOB_GetRtc(void);
extern uint8_t OOB_PeciPing(void);
extern uint8_t OOB_PeciDib(void);
extern uint8_t OOB_PECI_RdPkgConfig(uint8_t index, uint8_t* para, uint8_t* config);
extern uint8_t OOB_PECI_WrPkgConfig(uint32_t WData, uint8_t index, uint16_t para);

extern uint8_t OOB_PECI_RdPkg_PL1(void);

 extern uint8_t OOB_PECI_Done;
 extern uint8_t OOB_PECI_valid;

#endif
