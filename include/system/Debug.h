#ifndef __Debug_H__
#define __Debug_H__

#include <stdint.h>

typedef struct
{
	union {
		struct
		{
			uint32_t IOAddr0:8;
			uint32_t IOAddr1:8;
			uint32_t IOAddr2:8;
			uint32_t IOAddr3:8;
		} Bits;
	uint32_t DWORD;
	}IOAddr;
}Debug_Type;

#define SupportIODebug64	0
#define SupportIODebug66	0
#define SupportIODebugPM0	0
#define SupportIODebugPM1	1
#define SupportIODebugPM2	0
#define SupportIODebugPM3	0

#define DebugCmdW 0xE1
#define DebugCmdR 0xE2
#define DebugIO0 0xE3
#define DebugIO1 0xE4
#define DebugIO2 0xE5
#define DebugIO3 0xE6

extern Debug_Type DebugIO32;
extern void DebugCMDR(void);
extern void DebugAddr(void);
extern void DebugData(void);
extern void DebugCmdPort(void);
extern void DebugDataPort(void);
#endif
