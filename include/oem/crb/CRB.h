#ifndef __CRB_H__
#define __CRB_H__

#define	BOARDID	0x0D
#define	ChargingMethodSelect	0x13  // need return 0x00
#define	SMCHOST_READ_PLAT_SIGNATURE	0x92

extern void HookHandle66Port(void);
extern uint8_t HandleACPI80Data(void);
extern void CRBS5toS0(void);
#endif
