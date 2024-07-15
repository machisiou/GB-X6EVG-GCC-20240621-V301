#ifndef __Type_H__
#define __Type_H__

#include <stdint.h>

#define	BIT0	0x01		// 0000,0001
#define	BIT1	0x02		// 0000,0010
#define	BIT2	0x04		// 0000,0100
#define	BIT3	0x08		// 0000,1000
#define	BIT4	0x10		// 0001,0000
#define	BIT5	0x20		// 0010,0000
#define	BIT6	0x40		// 0100,0000
#define	BIT7	0x80		// 1000,0000
#define	BIT8	0x0100		// 0000,0001,0000,0000
#define	BIT9	0x0200		// 0000,0010,0000,0000
#define	BIT10	0x0400		// 0000,0100,0000,0000
#define	BIT11	0x0800		// 0000,1000,0000,0000
#define	BIT12	0x1000		// 0001,0000,0000,0000
#define	BIT13	0x2000		// 0010,0000,0000,0000
#define	BIT14	0x4000		// 0100,0000,0000,0000
#define	BIT15	0x8000		// 1000,0000,0000,0000
#define	BIT16	0x00010000	// 0000,0000,0000,0001,0000,0000,0000,0000
#define	BIT17	0x00020000	// 0000,0000,0000,0010,0000,0000,0000,0000
#define	BIT18	0x00040000	// 0000,0000,0000,0100,0000,0000,0000,0000
#define	BIT19	0x00080000	// 0000,0000,0000,1000,0000,0000,0000,0000
#define	BIT20	0x00100000	// 0000,0000,0001,0000,0000,0000,0000,0000
#define	BIT21	0x00200000	// 0000,0000,0010,0000,0000,0000,0000,0000
#define	BIT22	0x00400000	// 0000,0000,0100,0000,0000,0000,0000,0000
#define	BIT23	0x00800000	// 0000,0000,1000,0000,0000,0000,0000,0000
#define	BIT24	0x01000000	// 0000,0001,0000,0000,0000,0000,0000,0000
#define	BIT25	0x02000000	// 0000,0010,0000,0000,0000,0000,0000,0000
#define	BIT26	0x04000000	// 0000,0100,0000,0000,0000,0000,0000,0000
#define	BIT27	0x08000000	// 0000,1000,0000,0000,0000,0000,0000,0000
#define	BIT28	0x10000000	// 0001,0000,0000,0000,0000,0000,0000,0000
#define	BIT29	0x20000000	// 0010,0000,0000,0000,0000,0000,0000,0000
#define	BIT30	0x40000000	// 0100,0000,0000,0000,0000,0000,0000,0000
#define	BIT31	0x80000000	// 1000,0000,0000,0000,0000,0000,0000,0000
#define BIT(x) (1 << (x))

#define LoByte(w)		((w) & 0xFF)
#define HiByte(w)		(((w) >> 8) & 0xFF)

#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))

#define BIT_SET(a,b)	(a|=b)
#define BIT_CLR(a,b)	((a)&=(uint32_t)(~(b)))
#define IS_BIT_SET(a,b)	((a&b)!=0)
#define IS_BIT_CLR(a,b)	((a&b)==0)
#define DW2B(a,b)		((a>>b)&0x000000FFUL)

typedef enum _Protocol_Status {
	FAIL = 0,
	SUCCESS,
	IDLE,
	BUSY,
	ERROR = 0xFF,
} _Protocol_Status;

#define enable 1
#define disable 0

#define IS_MASK_CLEAR(a,b)  IS_BIT_CLR(a,b)
#define IS_MASK_SET(a,b)    IS_BIT_SET(a,b)
#define CLEAR_MASK(a,b)     BIT_CLR(a,b)
#define SET_MASK(a,b)       BIT_SET(a,b)
#define NULL ((void *)0)
#define code

#define BYTE uint8_t 
#define XBYTE uint8_t 
#define bit bool
#define ECQEvent(a,b) QeventSend(a)
#define	Delay1MS(a) _Delay_1ms(a)
#endif
