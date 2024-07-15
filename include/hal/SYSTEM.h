#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/*
 * Includes
 */
#include "system/peripheral.h"

/*
 * Defines
 */

enum {
	CLK_DISABLE = 0,
	CLK_ENABLE  = 1,
};

enum {
	LDO_DISABLE = 0,
	LDO_ENABLE  = 1,
};

enum {
	WAKEUP_DISABLE = 0,
	WAKEUP_ENABLE  = 1,
};

enum {
	I3C0_UNIT = 0,
	I3C1_UNIT = 1,
};

enum {
	I3C_CLK_DVI1 = 0,
	I3C_CLK_DVI2 = 1,
	I3C_CLK_DVI4 = 2,
};

enum {
	I2C0_UNIT = 0,
	I2C1_UNIT = 1,
	I2C2_UNIT = 2,
	I2C3_UNIT = 3,
	I2C4_UNIT = 4,
	I2C5_UNIT = 5,
	I2C6_UNIT = 6,
	I2C7_UNIT = 7,
};

enum {
	I2C_CLKSRC_RC25M	= 0,
	I2C_CLKSRC_PLL		= 1,
};

enum {
	I2C_CLK_DVI1 = 0,
	I2C_CLK_DVI2 = 1,
	I2C_CLK_DVI4 = 2,
	I2C_CLK_DVI8 = 3,
};

enum {
	TMR_HOLD_RST	= 0,
	TMR_RELEASE_RST	= 1,
};

enum {
	TMR_NOT_PUASE	= 0,
	TMR_PAUSE		= 1,
};

enum {
	TIMER0 = 0,
	TIMER1 = 1,
	TIMER2 = 2,
	TIMER3 = 3,
	TIMER4 = 4,
	TIMER5 = 5,
	STIMER0 = 6,
	STIMER1 = 7,
};

// select timer clock source divider
// 000:25M/1 010:25M/4 ... 111:25M/256
enum {
	TMR_CLK_DVI1	= 0,
	TMR_CLK_DVI2	= 1,
	TMR_CLK_DVI4	= 2,
	TMR_CLK_DVI8	= 3,
	TMR_CLK_DVI16	= 4,
	TMR_CLK_DVI32	= 5,
	TMR_CLK_DVI64	= 6,
	TMR_CLK_DVI128	= 7,
	TMR_CLK_DVI256	= 8,
};

enum {
	UART_CLKSRC_RC25M	= 0,
	UART_CLKSRC_PLL		= 1,
};

enum {
	UART_CLK_DVI1 = 0,
	UART_CLK_DVI2 = 1,
	UART_CLK_DVI4 = 2,
	UART_CLK_DVI8 = 3,
};

enum {
	ADC_CLKSRC_RC25M = 0,
	ADC_CLKSRC_PLL = 1,
};

enum {
	ADC_CLK_DVI1 = 0,
	ADC_CLK_DVI2 = 1,
	ADC_CLK_DVI3 = 2,
	ADC_CLK_DVI4 = 3,
	ADC_CLK_DVI6 = 4,
	ADC_CLK_DVI8 = 5,
	ADC_CLK_DVI12 = 6,
	ADC_CLK_DVI16 = 7,
};

enum {
	SYS_CLKSRC_RC25M = 0,
	SYS_CLKSRC_PLL = 1,
};

enum {
	SYS_CLK_DVI1 = 0,
	SYS_CLK_DVI2 = 1,
};

/*
 *  Macro
 */

/* LDO2 & LDO3 */
#define SYS_LDO2_EN(en)				(en ? (SYSTEM->LDOCTRL |= SYSTEM_LDOCTRL_LDO2PWREN_Msk) : (SYSTEM->LDOCTRL &= ~SYSTEM_LDOCTRL_LDO2PWREN_Msk))
#define SYS_LDO3_EN(en)				(en ? (SYSTEM->LDOCTRL |= SYSTEM_LDOCTRL_LDO3PWREN_Msk) : (SYSTEM->LDOCTRL &= ~SYSTEM_LDOCTRL_LDO3PWREN_Msk))

/* RC32K & PLL */
#define SYS_PLL_EN(en)				(en ? (SYSTEM->PLLCTRL |= SYSTEM_PLLCTRL_PWREN_Msk) : (SYSTEM->PLLCTRL &= ~SYSTEM_PLLCTRL_PWREN_Msk))
#define SYS_RC32K_EN(en)			(en ? (SYSTEM->RC32KCTRL |= SYSTEM_RC32KCTRL_PWREN_Msk) : (SYSTEM->RC32KCTRL &= ~SYSTEM_RC32KCTRL_PWREN_Msk))

/* Sleep Mode */
#define SYS_HEAVY_SLEEP_EN(en)		(en ? (SYSTEM->SLPCTRL |= SYSTEM_SLPCTRL_SLPMDSEL_Msk) : (SYSTEM->SLPCTRL &= ~SYSTEM_SLPCTRL_SLPMDSEL_Msk))

/* Wakeup Source */
#define SYS_WAKE_EN_ESPI(en)		(en ? (SYSTEM->SLPCTRL |= SYSTEM_SLPCTRL_ESPIWKEN_Msk) : (SYSTEM->SLPCTRL &= ~SYSTEM_SLPCTRL_ESPIWKEN_Msk))
#define SYS_WAKE_EN_PS2(en)			(en ? (SYSTEM->SLPCTRL |= SYSTEM_SLPCTRL_PS2WKEN_Msk) : (SYSTEM->SLPCTRL &= ~SYSTEM_SLPCTRL_PS2WKEN_Msk))
#define SYS_WAKE_EN_I2C(en)			(en ? (SYSTEM->SLPCTRL |= SYSTEM_SLPCTRL_I2CWKEN_Msk) : (SYSTEM->SLPCTRL &= ~SYSTEM_SLPCTRL_I2CWKEN_Msk))
#define SYS_WAKE_EN_GPIO(en)		(en ? (SYSTEM->SLPCTRL |= SYSTEM_SLPCTRL_GPIOWKEN_Msk) : (SYSTEM->SLPCTRL &= ~SYSTEM_SLPCTRL_GPIOWKEN_Msk))
#define SYS_WAKE_EN_SPISLV(en)		(en ? (SYSTEM->SLPCTRL |= SYSTEM_SLPCTRL_SPISLVWKEN_Msk) : (SYSTEM->SLPCTRL &= ~SYSTEM_SLPCTRL_SPISLVWKEN_Msk))

/* Peripheral Group #0 */
#define SYS_CLKPWR_GPIO(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_GPIOCLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_GPIOCLKPWR_Msk))
#define SYS_CLKPWR_TACHO0(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_TACHO0CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_TACHO0CLKPWR_Msk))
#define SYS_CLKPWR_TACHO1(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_TACHO1CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_TACHO1CLKPWR_Msk))
#define SYS_CLKPWR_TACHO2(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_TACHO2CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_TACHO2CLKPWR_Msk))
#define SYS_CLKPWR_TACHO3(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_TACHO3CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_TACHO3CLKPWR_Msk))
#define SYS_CLKPWR_PS2(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PS2CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PS2CLKPWR_Msk))
#define SYS_CLKPWR_KBM(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_KBMCLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_KBMCLKPWR_Msk))
#define SYS_CLKPWR_PECI(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PECICLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PECICLKPWR_Msk))
#define SYS_CLKPWR_PL0(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PL0CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PL0CLKPWR_Msk))
#define SYS_CLKPWR_PL1(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PL1CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PL1CLKPWR_Msk))
#define SYS_CLKPWR_PWM0(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM0CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM0CLKPWR_Msk))
#define SYS_CLKPWR_PWM1(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM1CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM1CLKPWR_Msk))
#define SYS_CLKPWR_PWM2(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM2CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM2CLKPWR_Msk))
#define SYS_CLKPWR_PWM3(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM3CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM3CLKPWR_Msk))
#define SYS_CLKPWR_PWM4(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM4CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM4CLKPWR_Msk))
#define SYS_CLKPWR_PWM5(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM5CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM5CLKPWR_Msk))
#define SYS_CLKPWR_PWM6(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM6CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM6CLKPWR_Msk))
#define SYS_CLKPWR_PWM7(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM7CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM7CLKPWR_Msk))
#define SYS_CLKPWR_PWM8(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM8CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM8CLKPWR_Msk))
#define SYS_CLKPWR_PWM9(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM9CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM9CLKPWR_Msk))
#define SYS_CLKPWR_PWM10(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM10CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM10CLKPWR_Msk))
#define SYS_CLKPWR_PWM11(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_PWM11CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_PWM11CLKPWR_Msk))
#define SYS_CLKPWR_ESPI(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_ESPICLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_ESPICLKPWR_Msk))
#define SYS_CLKPWR_KBC(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_KBCCLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_KBCCLKPWR_Msk))
#define SYS_CLKPWR_ACPI0(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_ACPI0CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_ACPI0CLKPWR_Msk))
#define SYS_CLKPWR_ACPI1(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_ACPI1CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_ACPI1CLKPWR_Msk))
#define SYS_CLKPWR_ACPI2(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_ACPI2CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_ACPI2CLKPWR_Msk))
#define SYS_CLKPWR_ACPI3(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_ACPI3CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_ACPI3CLKPWR_Msk))
#define SYS_CLKPWR_ACPI4(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_ACPI4CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_ACPI4CLKPWR_Msk))
#define SYS_CLKPWR_PORT80(en)		(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_P80CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_P80CLKPWR_Msk))
#define SYS_CLKPWR_EMI0(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_EMI0CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_EMI0CLKPWR_Msk))
#define SYS_CLKPWR_EMI1(en)			(en ? (SYSTEM->PERICLKPWR0 |= SYSTEM_PERICLKPWR0_EMI1CLKPWR_Msk) : (SYSTEM->PERICLKPWR0 &= ~SYSTEM_PERICLKPWR0_EMI1CLKPWR_Msk))

/* Peripheral Group #1 */
#define SYS_CLKPWR_EMI2(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_EMI2CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_EMI2CLKPWR_Msk))
#define SYS_CLKPWR_EMI3(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_EMI3CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_EMI3CLKPWR_Msk))
#define SYS_CLKPWR_EMI4(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_EMI4CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_EMI4CLKPWR_Msk))
#define SYS_CLKPWR_EMI5(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_EMI5CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_EMI5CLKPWR_Msk))
#define SYS_CLKPWR_EMI6(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_EMI6CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_EMI6CLKPWR_Msk))
#define SYS_CLKPWR_EMI7(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_EMI7CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_EMI7CLKPWR_Msk))
#define SYS_CLKPWR_OTPDMA(en)		(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_OTPDMACLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_OTPDMACLKPWR_Msk))
#define SYS_CLKPWR_RC25MCAL(en)		(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_RC25MCALCLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_RC25MCALCLKPWR_Msk))
#define SYS_CLKPWR_RC32KCAL(en)		(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_RC32KCALCLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_RC32KCALCLKPWR_Msk))
#define SYS_CLKPWR_I3C0(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_I3C0CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_I3C0CLKPWR_Msk))
#define SYS_CLKPWR_I3C1(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_I3C1CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_I3C1CLKPWR_Msk))
#define SYS_CLKPWR_I2CAUTO(en)		(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_I2CAUTOPWRCLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_I2CAUTOPWRCLKPWR_Msk))
#define SYS_CLKPWR_MONOTONMIC(en)	(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_MCCLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_MCCLKPWR_Msk))
#define SYS_CLKPWR_TMR0(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_TMR0CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_TMR0CLKPWR_Msk))
#define SYS_CLKPWR_TMR1(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_TMR1CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_TMR1CLKPWR_Msk))
#define SYS_CLKPWR_TMR2(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_TMR2CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_TMR2CLKPWR_Msk))
#define SYS_CLKPWR_TMR3(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_TMR3CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_TMR3CLKPWR_Msk))
#define SYS_CLKPWR_TMR4(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_TMR4CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_TMR4CLKPWR_Msk))
#define SYS_CLKPWR_TMR5(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_TMR5CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_TMR5CLKPWR_Msk))
#define SYS_CLKPWR_RTMR(en)			(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_RTMRCLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_RTMRCLKPWR_Msk))
#define SYS_CLKPWR_SLWTMR0(en)		(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_SLWTMR0CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_SLWTMR0CLKPWR_Msk))
#define SYS_CLKPWR_SLWTMR1(en)		(en ? (SYSTEM->PERICLKPWR1 |= SYSTEM_PERICLKPWR1_SLWTMR1CLKPWR_Msk) : (SYSTEM->PERICLKPWR1 &= ~SYSTEM_PERICLKPWR1_SLWTMR1CLKPWR_Msk))

/* Peripheral Group #2 */
#define SYS_CLKPWR_RTC(en)			(en ? (SYSTEM->PERICLKPWR2 |= SYSTEM_PERICLKPWR2_RTCCLKPWR_Msk) : (SYSTEM->PERICLKPWR2 &= ~SYSTEM_PERICLKPWR2_RTCCLKPWR_Msk))
#define SYS_CLKPWR_WDT(en)			(en ? (SYSTEM->PERICLKPWR2 |= SYSTEM_PERICLKPWR2_WDTCLKPWR_Msk) : (SYSTEM->PERICLKPWR2 &= ~SYSTEM_PERICLKPWR2_WDTCLKPWR_Msk))
#define SYS_CLKPWR_PWRBTN(en)		(en ? (SYSTEM->PERICLKPWR2 |= SYSTEM_PERICLKPWR2_PWRBTNCLKPWR_Msk) : (SYSTEM->PERICLKPWR2 &= ~SYSTEM_PERICLKPWR2_PWRBTNCLKPWR_Msk))

/* VIO Control */
#define SYS_VIO_REG_WREN(en)		(en ? (SYSTEM->VIVOCTRL |= SYSTEM_VIVOCTRL_REGWREN_Msk) : (SYSTEM->VIVOCTRL &= ~SYSTEM_VIVOCTRL_REGWREN_Msk))
#define SYS_VO_FUN_SEL(fun)			(fun ? (SYSTEM->VIVOCTRL |= SYSTEM_VIVOCTRL_VOMDSEL_Msk) : (SYSTEM->VIVOCTRL &= ~SYSTEM_VIVOCTRL_VOMDSEL_Msk))

/*
 * Functions 
 */
void Sys_TmrHoldRst(uint8_t tmr, uint8_t rst);
void Sys_TmrPause(uint8_t tmr, uint8_t pause);
void Sys_I3cClkPwrEnable(uint8_t i3c, uint8_t en, uint8_t div);
void Sys_I2cClkPwrEnable(uint8_t i2c, uint8_t en, uint8_t src, uint8_t div);
void Sys_TmrClkPwrEnable(uint8_t tmr, uint8_t en, uint8_t div);
void Sys_UartClkPwrEnable(uint8_t uart, uint8_t en, uint8_t src, uint8_t div);
void Sys_AdcClkPwrEnable(uint8_t adc, uint8_t en, uint8_t src, uint8_t div);
void Sys_SysClkSetup(uint8_t src, uint8_t div);
void Sys_ViSetup(uint32_t vi_msk, uint32_t pol_msk);
uint32_t Sys_ViGetStatus(void);

#endif  /* __SYSTEM_H__ */
