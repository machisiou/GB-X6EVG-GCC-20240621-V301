#ifndef __Flashtool_H__
#define __Flashtool_H__

#include "system/Type.h"

typedef struct
{
	union {
		struct
		{
			uint32_t FlashAddr0:8;
			uint32_t FlashAddr1:8;
			uint32_t FlashAddr2:8;
			uint32_t FlashAddr3:8;
		} Bits;
	uint32_t DWORD;
	}FlashAddr;
}FlashAddr_Type;

/*=======================================================================================*/
// Temporary use
//----------------------------------
// MCMPAD
//----------------------------------
typedef struct
{
    union {
        struct {
            uint32_t Sel_pad_mcm_wp_in_det:1;			// 0:Disable, 1:Enable
            uint32_t Sel_pad_mcm_wp_driving:1;
            uint32_t Sel_pad_mcm_wp_slew_rate:1;		// 0:Fast, 1:Slow
            uint32_t Sel_pad_mcm_wp_pulldown:1;		// 0:Disable, 1:Enable
            uint32_t Sel_pad_mcm_wp_pullup:1;			// 0:Disable, 1:Enable
            uint32_t Sel_pad_mcm_wp_schmitter:1;		// 0:Disable, 1:Enable
            uint32_t Sel_pad_mcm_wp_in_mode:1;		// 0:3.3V, 1:1.8V
            uint32_t :25;
        } BITS;
        uint32_t DWORD;                                // 0x00
    } Mcm_ctrl;
}MCMPAD_Type;

#define MCM_ADDR			0x40091000
#define Spi_flash_wp		((MCMPAD_Type *) MCM_ADDR)
#define Spi_flash_hold		((MCMPAD_Type *) (MCM_ADDR+0x04))
#define Spi_flash_si		((MCMPAD_Type *) (MCM_ADDR+0x08))
#define Spi_flash_so		((MCMPAD_Type *) (MCM_ADDR+0x0C))
#define Spi_flash_csn		((MCMPAD_Type *) (MCM_ADDR+0x10))
#define Spi_flash_sclk		((MCMPAD_Type *) (MCM_ADDR+0x14))
#define peci_pad			((MCMPAD_Type *) (MCM_ADDR+0x18))
#define PAD2				((MCMPAD_Type *) (MCM_ADDR+0x20))
#define PAD3				((MCMPAD_Type *) (MCM_ADDR+0x24))
/*=======================================================================================*/
extern FlashAddr_Type ToolFlaAddr;

#define	FlashControl	0xE7
#define	FlashAddrH		0xE8
#define	FlashAddrHM		0xE9
#define	FlashAddrM		0xEA
#define	FlashAddrL		0xEB
#define	FlashCmd		0xEC
#define	FlashData0		0xED
#define	FlashData1		0xEE
#define	FlashData2		0xEF

extern void FlashToolCmdPort(void);
extern void FlashToolDataPort(void);
extern void HandleCtrl(void);
extern void HandleFlashCmd(void);
extern void FlashChSel(uint8_t Channel);
extern void EnableExFlash(uint8_t Channel);
extern void DisableExFlash(uint8_t Channel);
extern void EnableInFlash(void);
extern void DisableInFlash(void);

//extern void HandleFlashRead(void);
	
#endif
