#include "hal/SYSTEM.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Hold or release reset stage for TIMER
 * tmr - Unit of timer
 * rst - 0: Release reset, 1: Hold reset
*******************************************************************************/
void Sys_TmrHoldRst(uint8_t tmr, uint8_t rst)
{
	SYSTEM->TMRRST = rst ? SYSTEM->TMRRST & ~(0x01ul << (SYSTEM_TMRRST_TMR0RST_Pos + tmr)) : 
	SYSTEM->TMRRST | (0x01ul << (SYSTEM_TMRRST_TMR0RST_Pos + tmr));
}

/******************************************************************************/
/** To pause TIMER
 * tmr - Unit of timer
 * pause - 0: Not pause, 1: Pause
*******************************************************************************/
void Sys_TmrPause(uint8_t tmr, uint8_t pause)
{
	SYSTEM->TMRDIV = pause ? SYSTEM->TMRRST | (0x01ul << (SYSTEM_TMRDIV_TMR0PAUSE_Pos + tmr)) : 
	SYSTEM->TMRDIV & ~(0x01ul << (SYSTEM_TMRDIV_TMR0PAUSE_Pos + tmr));
}

/******************************************************************************/
/** Enable TIMER clock power and setup clock divider
 * tmr  - Unit of timer
 * en   - 0: Disable clock power, 1: Enable clock power
 * div  - Clock divider
*******************************************************************************/
void Sys_TmrClkPwrEnable(uint8_t tmr, uint8_t en, uint8_t div)
{
	SYSTEM->TMRDIV &= ~(0x0Ful << (SYSTEM_TMRDIV_TMR0DIV_Pos + ((SYSTEM_TMRDIV_TMR1DIV_Pos - SYSTEM_TMRDIV_TMR0DIV_Pos) * tmr)));
	SYSTEM->TMRDIV |= (uint32_t)(div << (SYSTEM_TMRDIV_TMR0DIV_Pos + ((SYSTEM_TMRDIV_TMR1DIV_Pos - SYSTEM_TMRDIV_TMR0DIV_Pos) * tmr)));

	SYSTEM->PERICLKPWR1 &= ~(0x01ul << (SYSTEM_PERICLKPWR1_TMR0CLKPWR_Pos + tmr));
	SYSTEM->PERICLKPWR1 |= (uint32_t)(en << (SYSTEM_PERICLKPWR1_TMR0CLKPWR_Pos + tmr));
}

/******************************************************************************/
/** Enable I3C clock power and setup clock divider
 * i3c  - Unit of I3C
 * en   - 0: Disable clock power, 1: Enable clock power
 * div  - Clock divider
*******************************************************************************/
void Sys_I3cClkPwrEnable(uint8_t i3c, uint8_t en, uint8_t div)
{
	SYSTEM->PERICLKPWR1 &= ~(0x01ul << (SYSTEM_PERICLKPWR1_I3C0CLKPWR_Pos + i3c));
	SYSTEM->PERICLKPWR1 |= (uint32_t)(en << (SYSTEM_PERICLKPWR1_I3C0CLKPWR_Pos + i3c));

	SYSTEM->I3CCLKDIV &= ~(SYSTEM_I3CCLKDIV_I3C0DIV_Msk << ((SYSTEM_I3CCLKDIV_I3C1DIV_Pos - SYSTEM_I3CCLKDIV_I3C0DIV_Pos) * i3c));
	SYSTEM->I3CCLKDIV |= (uint32_t)(div << ((SYSTEM_I3CCLKDIV_I3C1DIV_Pos - SYSTEM_I3CCLKDIV_I3C0DIV_Pos) * i3c));
}

/******************************************************************************/
/** Enable I2C clock power and setup clock divider
 * i2c  - Unit of I2C
 * en   - 0: Disable clock power, 1: Enable clock power
 * src  - 0: From PLL, 1: From RC25M
 * div  - Clock divider
*******************************************************************************/
void Sys_I2cClkPwrEnable(uint8_t i2c, uint8_t en, uint8_t src, uint8_t div)
{
	uint32_t ctrl = SYSTEM->I2CCLKPWR;

	ctrl &= ~(0x01ul << (SYSTEM_I2CCLKPWR_I2C0CLKPWR_Pos + ((SYSTEM_I2CCLKPWR_I2C1CLKPWR_Pos - SYSTEM_I2CCLKPWR_I2C0CLKPWR_Pos) * i2c)));
	ctrl &= ~(0x01ul << (SYSTEM_I2CCLKPWR_I2C0CLKSRC_Pos + ((SYSTEM_I2CCLKPWR_I2C1CLKSRC_Pos - SYSTEM_I2CCLKPWR_I2C0CLKSRC_Pos) * i2c)));
	ctrl &= ~(0x03ul << (SYSTEM_I2CCLKPWR_I2C0CLKDIV_Pos + ((SYSTEM_I2CCLKPWR_I2C1CLKDIV_Pos - SYSTEM_I2CCLKPWR_I2C0CLKDIV_Pos) * i2c)));

	ctrl |= (uint32_t)(en << (SYSTEM_I2CCLKPWR_I2C0CLKPWR_Pos + ((SYSTEM_I2CCLKPWR_I2C1CLKPWR_Pos - SYSTEM_I2CCLKPWR_I2C0CLKPWR_Pos) * i2c)));
	ctrl |= (uint32_t)(src << (SYSTEM_I2CCLKPWR_I2C0CLKSRC_Pos + ((SYSTEM_I2CCLKPWR_I2C1CLKSRC_Pos - SYSTEM_I2CCLKPWR_I2C0CLKSRC_Pos) * i2c)));
	ctrl |= (uint32_t)(div << (SYSTEM_I2CCLKPWR_I2C0CLKDIV_Pos + ((SYSTEM_I2CCLKPWR_I2C1CLKDIV_Pos - SYSTEM_I2CCLKPWR_I2C0CLKDIV_Pos) * i2c)));

	SYSTEM->I2CCLKPWR = ctrl;
}

/******************************************************************************/
/** Enable UART clock power and setup clock divider
 * uart  - Unit of UART (unused)
 * en   - 0: Disable clock power, 1: Enable clock power
 * src  - 0: From RC25M, 1: From PLL
 * div  - Clock divider
*******************************************************************************/
void Sys_UartClkPwrEnable(uint8_t uart, uint8_t en, uint8_t src, uint8_t div)
{
	uint32_t ctrl = SYSTEM->UARTCLKPWR;
	(void)uart;

	ctrl &= ~(0x01ul << SYSTEM_UARTCLKPWR_PWR_Pos);
	ctrl &= ~(0x01ul << SYSTEM_UARTCLKPWR_CLKSRC_Pos);
	ctrl &= ~(0x03ul << SYSTEM_UARTCLKPWR_DIV_Pos);

	ctrl |= (uint32_t)(en << SYSTEM_UARTCLKPWR_PWR_Pos);
	ctrl |= (uint32_t)(src << SYSTEM_UARTCLKPWR_CLKSRC_Pos);
	ctrl |= (uint32_t)(div << SYSTEM_UARTCLKPWR_DIV_Pos);

	SYSTEM->UARTCLKPWR = ctrl;
}

/******************************************************************************/
/** To setup clock for system
 * src  - 0: From RC25M, 1: From PLL
 * div  - 0: DIV1, 1: DIV2
*******************************************************************************/
void Sys_SysClkSetup(uint8_t src, uint8_t div)
{
	uint32_t ctrl = SYSTEM->SYSCLK;

	ctrl &= ~(0x01ul << SYSTEM_SYSCLK_CLKSRC_Pos);
	ctrl &= ~(0x01ul << SYSTEM_SYSCLK_DIV_Pos);

	ctrl |= (uint32_t)(src << SYSTEM_SYSCLK_CLKSRC_Pos);
	ctrl |= (uint32_t)(div << SYSTEM_SYSCLK_DIV_Pos);

	SYSTEM->SYSCLK = ctrl;
}

/******************************************************************************/
/** Enable ADC clock power and setup clock divider
 * adc  - Unit of ADC (unused)
 * en   - 0: Disable clock power, 1: Enable clock power
 * src  - 0: From RC25M, 1: From PLL
 * div  - Clock divider
*******************************************************************************/
void Sys_AdcClkPwrEnable(uint8_t adc, uint8_t en, uint8_t src, uint8_t div)
{
	uint32_t ctrl = SYSTEM->ADCCLKPWR;
	(void)adc;

	ctrl &= ~(0x01ul << SYSTEM_ADCCLKPWR_PWR_Pos);
	ctrl &= ~(0x01ul << SYSTEM_ADCCLKPWR_CLKSRC_Pos);
	ctrl &= ~(0x07ul << SYSTEM_ADCCLKPWR_DIV_Pos);

	ctrl |= (uint32_t)(en << SYSTEM_ADCCLKPWR_PWR_Pos);
	ctrl |= (uint32_t)(src << SYSTEM_ADCCLKPWR_CLKSRC_Pos);
	ctrl |= (uint32_t)(div << SYSTEM_ADCCLKPWR_DIV_Pos);

	SYSTEM->ADCCLKPWR = ctrl;
}

/******************************************************************************/
/** Setup VIN function
 * vi_msk  - VIN mask (BIT1 = VIN0, BIT2 = VIN1..., BIT5 = VIN5)
 * pol_msk - VIN polarity (BIT1 = VIN0, BIT2 = VIN1..., BIT5 = VIN5)
*******************************************************************************/
void Sys_ViSetup(uint32_t vi_msk, uint32_t pol_msk)
{
	uint32_t ctrl = SYSTEM->VIVOCTRL;

	ctrl &= ~((0x3Ful << SYSTEM_VIVOCTRL_VI0MDSEL_Pos) | (0x3Ful << SYSTEM_VIVOCTRL_VI0POL_Pos));
	ctrl |= ((vi_msk << SYSTEM_VIVOCTRL_VI0MDSEL_Pos) | (pol_msk << SYSTEM_VIVOCTRL_VI0POL_Pos));

	SYSTEM->VIVOCTRL = ctrl;
}

/******************************************************************************/
/** Get VIN status
 * return VIN status (BIT1 = VIN0, BIT2 = VIN1..., BIT5 = VIN5)
*******************************************************************************/
uint32_t Sys_ViGetStatus(void)
{
	return ((SYSTEM->VIVOCTRL & ~(0x3Ful << SYSTEM_VIVOCTRL_VI0STS_Pos)) >> SYSTEM_VIVOCTRL_VI0STS_Pos);
}
