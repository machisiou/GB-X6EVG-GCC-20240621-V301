#include <stdint.h>
#include "system/Flashtool.h"
#include "system/Memory.h"
#include "hal/KBC.h"
#include "hal/SPIC.h"
#include "hal/GPIO.h"
#include "oem/crb/Oem_timer.h"

FlashAddr_Type ToolFlaAddr;

void FlashToolCmdPort(void)
{
	switch(KbcCmd)
	{
		case FlashControl:
		case FlashAddrH:
		case FlashAddrHM:
		case FlashAddrM:
		case FlashAddrL:
			KbcDLen = 1;
			break;
		case FlashCmd:
			HandleFlashCmd();
			break;
		case FlashData0:
		case FlashData1:
		case FlashData2:
			//HandleFlashRead();
			break;
	}
}

void FlashToolDataPort(void)
{
	switch(KbcCmd)
	{
		case FlashControl:
			HandleCtrl();
			break;
		case FlashAddrH:
			ToolFlaAddr.FlashAddr.Bits.FlashAddr3 = KbcData;
			break;
		case FlashAddrHM:
			ToolFlaAddr.FlashAddr.Bits.FlashAddr2 = KbcData;
			break;
		case FlashAddrM:
			ToolFlaAddr.FlashAddr.Bits.FlashAddr1 = KbcData;
			break;
		case FlashAddrL:
			ToolFlaAddr.FlashAddr.Bits.FlashAddr0 = KbcData;
			break;
		//case FlashCmd:
		//	HandleFlashCmd();
		//	break;
	}
}

void HandleCtrl(void)
{
	switch(KbcData)
	{
		case 0x01:		/* Select External Flash 0 */
			FlashChSel(0);
			break;
		case 0x02:		/* Select Internal Flash */
			FlashChSel(1);
			break;
		case 0x03:		/* Select External Flash 1 */
			FlashChSel(2);
			break;
		case 0x04:		/* Enter Flash mode */
			SPIC_Initial();
			break;
		case 0x05:		/* Exit Flash mode */
			DisableExFlash(0);
			DisableExFlash(2);
			DisableInFlash();
			break;
		case 0x06:		/* Enable WDT */
			WDT_NOW();
			break;
		case 0x07:		/* SPIC AUTO mode */
			SPIC_AutoMode();
			break;
		case 0x08:		/* SPIC USER mode */
			SPIC_UserMode();
			break;

	}
}

void HandleFlashCmd(void)
{
	uint8_t j;

	SPIC_WriteEn(GigaDev,1);
	while(1) {
	j = SPIC_FlashStatus(GigaDev);
		if((j & BIT1+BIT0) == BIT1)
			break;
	}
	SPIC_Erase(ToolFlaAddr.FlashAddr.DWORD, GigaDev, 2);
	while(1) {
	j = SPIC_FlashStatus(GigaDev);
		if((j & BIT0) == 0)
			break;
	}

	KBC_Write(0xFA);	/* if pass return Ack */
}

void FlashChSel(uint8_t Channel)
{
	if((Channel == 0) || (Channel == 2)){		/* Select External Flash 0/1 */ 
		EnableExFlash(Channel);
		DisableInFlash();
	}
	else if(Channel == 1) {		/* Select Internal Flash */
		EnableInFlash();
		DisableExFlash(0);
		DisableExFlash(2);
	}
}

void EnableExFlash(uint8_t Channel)
{
	if(Channel == 0) {
		GPIO_Func_Mode(107,1);	/* CS0 */
		GPIO_Func_Mode(106,0);	/* GPIO */
	}
	else if(Channel == 1) {
		GPIO_Func_Mode(106,2);	/* CS1 */
		GPIO_Func_Mode(107,0);	/* GPIO */
	}
	GPIO_Func_Mode(108,1);	/* MOSI */
	GPIO_Func_Mode(109,1);	/* MISO */
	GPIO_Func_Mode(111,1);	/* CLK */
	GPIO_Func_Mode(122,1);	/* DIO3 */
	GPIO_Func_Mode(124,2);	/* DIO2 */
	GPIO_Pin_On(108,1); 	/* Input detection Enable */
	GPIO_Pin_On(109,1); 	/* Input detection Enable */
	GPIO_Pin_On(122,1); 	/* Input detection Enable */
	GPIO_Pin_On(124,1); 	/* Input detection Enable */
}

void DisableExFlash(uint8_t Channel)
{
	if(Channel == 0) {
		GPIO_Func_Mode(107,0);	/* GPIO */
	}
	else if(Channel == 1) {
		GPIO_Func_Mode(106,0);	/* GPIO */
	}
	GPIO_Func_Mode(108,0);	/* GPIO */
	GPIO_Func_Mode(109,0);	/* GPIO */
	GPIO_Func_Mode(111,0);	/* GPIO */
	GPIO_Func_Mode(122,0);	/* GPIO */
	GPIO_Func_Mode(124,0);	/* GPIO */
	GPIO_Pin_On(108,0); 	/* Input detection Disable */
	GPIO_Pin_On(109,0); 	/* Input detection Disable */
	GPIO_Pin_On(122,0); 	/* Input detection Disable */
	GPIO_Pin_On(124,0); 	/* Input detection Disable */
}

void EnableInFlash(void)
{
	Spi_flash_wp->Mcm_ctrl.DWORD = 0x00000001;
	Spi_flash_hold->Mcm_ctrl.DWORD = 0x00000001;
	Spi_flash_si->Mcm_ctrl.DWORD = 0x00000001;
	Spi_flash_so->Mcm_ctrl.DWORD = 0x00000001;
	Spi_flash_csn->Mcm_ctrl.DWORD = 0x00000001;
	Spi_flash_sclk->Mcm_ctrl.DWORD = 0x00000001;
}

void DisableInFlash(void)
{
	Spi_flash_wp->Mcm_ctrl.DWORD = 0x00000000;
	Spi_flash_hold->Mcm_ctrl.DWORD = 0x00000000;
	Spi_flash_si->Mcm_ctrl.DWORD = 0x00000000;
	Spi_flash_so->Mcm_ctrl.DWORD = 0x00000000;
	Spi_flash_csn->Mcm_ctrl.DWORD = 0x00000000;
	Spi_flash_sclk->Mcm_ctrl.DWORD = 0x00000000;
}


//void HandleFlashRead(void)
//{
//	;
//}




