#include "hal/GPIO.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Initial GPIO Table
 * GPIOTbl - GPIO Initial Table
 * return None
*******************************************************************************/
void GPIO_Init(const uint32_t* GPIOTbl)
{
	__label__ __L_set_next_gpio__;
	uint32_t index,gpio_data;
	const uint32_t *source_pntr = GPIOTbl;

	//*source_pntr = GPIOTbl;
	while(*source_pntr != 0xFFFF) {
		index = *source_pntr++;
		gpio_data = *source_pntr++;

		if(DCB->DHCSR & DCB_DHCSR_C_DEBUGEN_Msk)
		{
		switch (index)
		{
			/// FIXME: eliminate magic number
			case 41: case 42: case 43: case 44: // KSO 0-3
			case 64: case 65: case 66: case 67: // KSI 0-3
			case 68: case 69: case 70: case 71: // KSI 4-7
				goto __L_set_next_gpio__;
		}
	}

		GPIO_Func_Mode(index, (gpio_data & 0x07));
		GPIO_Set_Vlot(index, IS_BIT_SET(gpio_data,GPIO_VOLT));
		GPIO_Config(index, IS_BIT_SET(gpio_data,GPIO_TYPE), IS_BIT_SET(gpio_data,GPIO_PULLUP),
			IS_BIT_SET(gpio_data,GPIO_PULLDN));
		GPIO_Write(index, IS_BIT_SET(gpio_data,GPIO_HILOW));
		GPIO_Set_IO(index, IS_BIT_SET(gpio_data,GPIO_INOUT));
		GPIO_Set_Schmit(index, IS_BIT_SET(gpio_data,GPIO_SCHMITTER));
		GPIO_Set_Driving(index, IS_BIT_SET(gpio_data,GPIO_DRIVING));
		GPIO_Set_Slew(index, IS_BIT_SET(gpio_data,GPIO_SLEW));
		GPIO_Pin_On(index, IS_BIT_SET(gpio_data,GPIO_PINON));

__L_set_next_gpio__:
		continue;
	}
}

/******************************************************************************/
/** GPIO Function select
 * GPIOnum - GPIO number
 * Func - 0 FUNC0 1 FUNC1 2 FUNC2 3 FUNC3 ...
 * return None
*******************************************************************************/
void GPIO_Func_Mode(uint32_t GPIOnum, uint8_t Func)
{
	GPIO->GCR_b[GPIOnum].MFCTRL = Func;
}

/******************************************************************************/
/** GPIO Pin On (pin tri-state set off)
 * GPIOnum - GPIO number
 * OnOff - 0: Disable, 1: Enable
 * return None
*******************************************************************************/
void GPIO_Pin_On(uint32_t GPIOnum, uint8_t OnOff)
{
	if(OnOff == 0)
		GPIO->GCR[GPIOnum] &= ~GPIO_GCR_INDETEN_Msk;
	else if(OnOff == 1)
		GPIO->GCR[GPIOnum] |= GPIO_GCR_INDETEN_Msk;
}

/******************************************************************************/
/** GPIO INPUT/OUTPUT select
 * GPIOnum - GPIO number
 * InOut - 0 input 1 output
 * return None
*******************************************************************************/
void GPIO_Set_IO(uint32_t GPIOnum, uint8_t InOut)
{
	GPIO->GCR_b[GPIOnum].DIR = InOut;
}

/******************************************************************************/
/** Set GPIO Output High/Low
 * GPIOnum - GPIO number
 * Level - 0:Low, 1:High
 * return None
*******************************************************************************/
void GPIO_Write(uint32_t GPIOnum, uint8_t Level)
{
	// Check if GPIO is OD and Level is High
	if((GPIO->GCR_b[GPIOnum].OUTTYPCTRL == 1) && (Level == 1))
	{
		GPIO->GCR_b[GPIOnum].DIR = 0;		// Config as input
	}
	else if((GPIO->GCR_b[GPIOnum].OUTTYPCTRL == 1) && (Level == 0))
	{
		GPIO->GCR_b[GPIOnum].OUTCTRL = 0;
		GPIO->GCR_b[GPIOnum].DIR = 1;		// Config as output
	}
	else
		GPIO->GCR_b[GPIOnum].OUTCTRL = Level;
}

/******************************************************************************/
/** Read GPIO
 * GPIOnum - GPIO number
 * return 0:Low, 1:High
*******************************************************************************/
uint8_t GPIO_Read(uint32_t GPIOnum)
{
	return GPIO->GCR_b[GPIOnum].PINSTS;
}

/******************************************************************************/
/** Read GPIO Output Type
 * GPIOnum - GPIO number
 * return 0:Push-Pull, 1:Open-Drain
*******************************************************************************/
uint8_t GPIO_ReadType(uint32_t GPIOnum)
{
	return GPIO->GCR_b[GPIOnum].OUTTYPCTRL;
}

/******************************************************************************/
/** GPIO Configure
 * GPIOnum - GPIO number
 * Type - 0: Push-Pull, 1: Open-Drain
 * PullUp - 0: Disable, 1: Enable
 * PullDn - 0: Disable, 1: Enable
 * return None
*******************************************************************************/
void GPIO_Config(uint32_t GPIOnum, uint8_t Type, uint8_t PullUp, uint8_t PullDn)
{
	GPIO->GCR_b[GPIOnum].OUTTYPCTRL = Type;
	GPIO->GCR_b[GPIOnum].PULLUPEN = PullUp;
	GPIO->GCR_b[GPIOnum].PULLDWEN = PullDn;
}

/******************************************************************************/
/** GPIO Voltage select
 * GPIOnum - GPIO number
 * Volt - 1 1.8V 0 3.3V
 * return None
*******************************************************************************/
void GPIO_Set_Vlot(uint32_t GPIOnum, uint8_t Volt)
{
	GPIO->GCR_b[GPIOnum].INVOLMD = Volt;
}

/******************************************************************************/
/** GPIO Schmitter select
 * GPIOnum - GPIO number
 * Schmit - 1 ebable 0 disable
 * return None
*******************************************************************************/
void GPIO_Set_Schmit(uint32_t GPIOnum, uint8_t Schmit)
{
	GPIO->GCR_b[GPIOnum].SCHEN = Schmit;
}

/******************************************************************************/
/** GPIO Driving Capability select
 * GPIOnum - GPIO number
 * Driv - 0 low driving capability 1 high driving capability
 * return None
*******************************************************************************/
void GPIO_Set_Driving(uint32_t GPIOnum, uint8_t Driv)
{
	GPIO->GCR_b[GPIOnum].OUTDRV = Driv;
}

/******************************************************************************/
/** GPIO Slew Rate select
 * GPIOnum - GPIO number
 * Slew - 0 fast slew rate 1 slow slew rate
 * return None
*******************************************************************************/
void GPIO_Set_Slew(uint32_t GPIOnum, uint8_t Slew)
{
	GPIO->GCR_b[GPIOnum].SLEWRATE = Slew;
}

/******************************************************************************/
/** GPIO Interrupt Configure
 * GPIOnum - GPIO number
 * Intr - 0: Disable, 1: Enable
 * IntrTrigger - 
 * 0 = rising edge trigger, 
 * 1 = falling edge trigger, 
 * 2 = dual edge trigger, 
 * 3 = low level trigger, 
 * 4 = high level trigger
 * return None
*******************************************************************************/
void GPIO_Intr_Config(uint32_t GPIOnum, uint8_t Intr, uint8_t IntrTrigger)
{
	GPIO->GCR_b[GPIOnum].INTCTRL = IntrTrigger;
	GPIO->GCR_b[GPIOnum].INTEN = Intr;
}

/******************************************************************************/
/** GPIO Clear Interrupt
 * GPIOnum - GPIO number
 * return None
******************************************************************************/
void GPIO_ClrIntr(uint32_t GPIOnum)
{
	GPIO->GCR_b[GPIOnum].INTSTS = 1;
}
