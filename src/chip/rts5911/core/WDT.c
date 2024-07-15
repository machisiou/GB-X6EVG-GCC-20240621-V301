#include "system/Type.h"
#include "hal/WDT.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/* Enable WDT Function
  * divval - divider value.
  * loadval - count value.
  * return SUCCESS
*******************************************************************************/
uint8_t WDT_Init(uint16_t divval, uint8_t loadval)
{
	WDT_Set_Divider(divval);
	WDT_Set_LoadValue(loadval);
	WDT_Enable_Interrupt();
	WDT_Enable();
	return SUCCESS;
}

/******************************************************************************/
/* Enable Power button WDT Function
  * rstouttri - reset output triggermode
  * rstoutwidth - reset output pulse 
  * pbtri - power button trigger mode
  * pbwidth - power button width
  * loadval - count value.
  * return SUCCESS
*******************************************************************************/
uint8_t PWRBTN_WDT_Init(uint8_t rstouttri, uint16_t rstoutwidth ,uint8_t pbtri, uint16_t pbwidth, uint8_t loadval)
{
	PWRBTN_WDT_Enable_PB();
	PWRBTN_WDT_Enable_Rst();
	PWRBTN_WDT_Rst_Out_Width(rstoutwidth);
	PWRBTN_WDT_Rst_Mode(rstouttri);
	PWRBTN_WDT_Trig_Mode(pbtri);
	PWRBTN_WDT_Set_Divider(pbwidth);
	PWRBTN_WDT_Set_LoadValue(loadval);
	PWRBTN_WDT_Enable_Interrupt();
	PWRBTN_WDT_Enable();
	return SUCCESS;
}
