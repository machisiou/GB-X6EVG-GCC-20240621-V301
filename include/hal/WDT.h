#ifndef __WDT_H__
#define __WDT_H__

#include <stdint.h>

#define WDT_Enable()						(WDT->CTRL_b.EN = 1)
#define WDT_Disable() 						(WDT->CTRL_b.EN = 0)
#define WDT_Enable_Rst()					(WDT->CTRL_b.RSTEN = 1)
#define WDT_Disable_Rst()					(WDT->CTRL_b.RSTEN = 0)
#define WDT_Set_LoadValue(loadval) 			(WDT->CNT = loadval)
#define WDT_Set_Divider(divval)				(WDT->DIV = divval)
#define WDT_Get_Rst_Flag()					(WDT->STS_b.RSTFLAG)
#define WDT_Enable_Interrupt()				(WDT->INTEN_b.WDTINTEN = 1)
#define WDT_Disable_Interrupt()				(WDT->INTEN_b.WDTINTEN = 0)
#define WDT_Clear_Rst_Flag()				(WDT->CTRL_b.CLRRSTFLAG = 1)

#define PWRBTN_WDT_Enable() 				(PWRBTN->CTRL_b.EN = 1)
#define PWRBTN_WDT_Disable() 				(PWRBTN->CTRL_b.EN = 0)
#define PWRBTN_WDT_Enable_Rst()				(PWRBTN->CTRL_b.RSTEN = 1)
#define PWRBTN_WDT_Disable_Rst()			(PWRBTN->CTRL_b.RSTEN = 0)
#define PWRBTN_WDT_Set_LoadValue(loadval) 	(PWRBTN->CNT_b.CNT = loadval)
#define PWRBTN_WDT_Set_Divider(divval)		(PWRBTN->DIV_b.DIV = divval)
#define PWRBTN_WDT_Get_Rst_Flag()			(PWRBTN->STS_b.RSTFLAG)
#define PWRBTN_WDT_Clear_Rst_Flag()			(PWRBTN->STS_b.RSTFLAG = 1)
#define PWRBTN_WDT_Enable_Interrupt()		(PWRBTN->INTEN_b.WDTINTEN = 1)
#define PWRBTN_WDT_Disable_Interrupt()		(PWRBTN->INTEN_b.WDTINTEN = 0)
#define PWRBTN_WDT_Trig_Mode(mode)			(PWRBTN->CONF_b.TRIGMD = mode)
#define PWRBTN_WDT_Rst_Mode(mode)			(PWRBTN->CONF_b.RSTOUTPOL = mode)
#define PWRBTN_WDT_Rst_Out_Width(width)		(PWRBTN->CONF_b.RSTPULSEWIDTH = width)
#define PWRBTN_WDT_Enable_PB()				(PWRBTN->CONF_b.EN = 1)
#define PWRBTN_WDT_Disable_PB()				(PWRBTN->CONF_b.EN = 0)

extern uint8_t WDT_Init(uint16_t divval, uint8_t loadval);
extern uint8_t PWRBTN_WDT_Init(uint8_t rstouttri ,uint16_t rstoutwidth,uint8_t pbtri ,uint16_t pbwidth,uint8_t loadval);

#endif
