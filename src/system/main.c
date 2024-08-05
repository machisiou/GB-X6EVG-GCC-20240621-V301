/*
 * Includes
 */
#include "RTK_Include.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "system/Memory.h"
#include "system/ACPI_Command.h"
#include "system/KBC_Command.h"
#include "hal/PerVW.h"
#include "hal/SPIC.h"
#include "hal/SYSTEM.h"
#include "hal/TIMER.h"
#include "hal/UART.h"
#include "hal/GPIO.h"
#include "hal/KBC.h"
#include "hal/ACPI.h"
#include "hal/KBM.h"
#include "hal/PMPORT0.h"
#include "hal/PMPORT1.h"
#include "system/peripheral.h"
#include "system/interrupt.h"
#include "oem/crb/Oem_main.h"
#include "oem/crb/Oem_timer.h"
#include "oem/crb/Oem_scan.h"
#include "oem/crb/Oem_pmport0.h"
#include "oem/crb/Oem_pmport1.h"
#include "oem/crb/Oem_pmport2.h"
#include "oem/crb/Oem_pmport3.h"
#include "oem/crb/Project.h"


/*
 * Defines
 */

/*
 * Private Prototype
 */
static void system_init(void);
static void slowtmr_dealyus(uint32_t us);
static void slowtmr_dealyms(uint32_t ms);
static void Kernel_RAM_init(void);
static void Kernel_init(void);
static void Main_Service(void);
static void Service_1ms(void);
static void DisableModule(void);
static void EnableModule(void);
static void System_EnterSleepMode(void);

/*
 * Global Function
 */

#if (defined(RTE_Compiler_IO_STDOUT_User) || defined(RTE_Compiler_IO_STDIN_User))
//
// stdout_init
//
int stdout_init(void)
{
	/* 
	* Set UART parameter
	*  - 8-bit data, 1-bit stop, no parity
	*/
	UART->LCR_b.DLS = 3;
	UART->LCR_b.STOP = 0;
	UART->LCR_b.PEN = 0;

	/* Enable FIFO mode */
	UART->FCR_b.FIFOE = 1;

	/* Disable auto-flow control */
	UART->MCR_b.AFCE = 0;   

	/* Disable all interrupt */
	UART->IER = 0ul;

	/* 
	* Set baud rate 
	*  - Baud rate = (uart_clk) / (16 * divisor)
	*/
	UART->LCR_b.DLAB = 1;
	UART->DLH = 0x00000000ul;
	UART->DLL = 0x0000000Dul;
	UART->LCR_b.DLAB = 0;

	return 0;
}
#endif 

#if defined(RTE_Compiler_IO_STDOUT_User)
//
// stdout_putchar
//
int stdout_putchar(int ch)
{
	UART->THR_b.DATA = (uint8_t)ch;
	while(!UART->USR_b.TFNF);

	return 0;
}
#endif

#if defined(RTE_Compiler_IO_STDIN_User)
//
// stdin_getchar
//
int stdin_getchar(void)
{
	while(!UART->USR_b.RFNE);
	return (int)UART->RBR_b.DATA;
}
#endif

//
// main
//
int main(void)
{
	extern uint32_t __RAWDATA_BEGIN__, __RAWDATA_LENGTH__;
	__disable_irq();
	void* ptr = (void*)&__RAWDATA_BEGIN__;
	memset(ptr,0,(size_t)&__RAWDATA_LENGTH__);			// Clear from 0x20050000 to 0x2005F000
	/* Initial NVIC and stack*/
	/* Initialize system clock and ip power */
	system_init();
	/* IP or kernel function initialize */
	Kernel_init();
	/* Oem function initialize*/
	Oem_init();
	SPIC_AutoMode();

	_Delay_1ms(10);


	SERVICEflag = 0;
	__enable_irq();
	/* Infinite loop */
	SystemState = SYSTEM_G3;
	//EC_3A = 1;
	while(1) {
		Main_Service();
	}
}

/*
 * Private Function
 */

//
// slowtmr_dealyus
//
static void slowtmr_dealyus(uint32_t us)
{
	SLWTMR0->LDCNT = us;

	SLWTMR0->CTRL_b.EN = 0;
	SLWTMR0->CTRL_b.MDSEL = 0;
	SLWTMR0->INTSTS_b.STS = 1;

	SLWTMR0->CTRL_b.EN = 1;
	while(!SLWTMR0->INTSTS_b.STS);
	SLWTMR0->INTSTS_b.STS = 1;
	SLWTMR0->CTRL_b.EN = 0;
}

//
// slowtmr_dealyms
//
static void slowtmr_dealyms(uint32_t ms)
{
	SLWTMR0->LDCNT = (1000 * ms);

	SLWTMR0->CTRL_b.MDSEL = 0;
	SLWTMR0->CTRL_b.MDSEL = 0;
	SLWTMR0->INTSTS_b.STS = 1;

	SLWTMR0->CTRL_b.EN = 1;
	while(!SLWTMR0->INTSTS_b.STS);
	SLWTMR0->INTSTS_b.STS = 1;
	SLWTMR0->CTRL_b.EN = 0;
}

//
// system_init
//
static void system_init(void)
{
	/*
	* Set SLOWTIMER0 clock power = ON
	*/
	SYSTEM->PERICLKPWR1_b.SLWTMR0CLKPWR = 1;

	/*
	* Enable LDO2
	*/
	SYSTEM->LDOCTRL_b.LDO2PWREN = 1;
	slowtmr_dealyus(125);

	/*
	* Enable LDO3
	*/
	SYSTEM->LDOCTRL_b.LDO3PWREN = 1;
	slowtmr_dealyus(125);

	/* Enable REG_WR_EN of VINVOUT to kick 32K OSC start */
	SYSTEM->VIVOCTRL_b.REGWREN = 1;
	SYSTEM->VIVOCTRL_b.VOMDSEL = 1;

	/*
	* Enable PLL
	*/
	SYSTEM->PLLCTRL_b.PWREN = 1;
	slowtmr_dealyus(5);

	/*
	* Enable RC32K
	*/
	SYSTEM->RC32KCTRL_b.PWREN = 1;
	slowtmr_dealyms(10);

	/*
	* Set SLOWTIMER0 clock power = OFF
	*/
	SYSTEM->PERICLKPWR1_b.SLWTMR0CLKPWR = 0;

	/* 
	* Set System Clock 
	*  - From PLL
	*  - DIV1
	*/
	//SYSTEM->SYSCLK_b.CLKSRC = 1;
	//SYSTEM->SYSCLK_b.DIV = 0;

	//using 12.5MHz
	SYSTEM->SYSCLK_b.CLKSRC = 0;
	SYSTEM->SYSCLK_b.DIV = 1;

	/* 
	* Set UART clock
	*  - From PLL, div1
	*/
	SYSTEM->UARTCLKPWR_b.PWR = 1;
	SYSTEM->UARTCLKPWR_b.CLKSRC = 1;
	SYSTEM->UARTCLKPWR_b.DIV = 0;

	/* 
	 * Set ADC clock
	 */
	SYSTEM->ADCCLKPWR_b.PWR = 1;
	SYSTEM->ADCCLKPWR_b.CLKSRC = 0;
	SYSTEM->ADCCLKPWR_b.DIV = 2;

	/* Update System Clock */
	SystemCoreClockUpdate();

	/* Peripherals clock power */
	// ----- GPIO power -----
	SYS_WAKE_EN_GPIO(enable);

	// ----- RTMR power -----
	SYS_CLKPWR_RTMR(enable);

	// ----- SLWTMR power -----
	SYS_CLKPWR_SLWTMR0(enable);
	SYS_CLKPWR_SLWTMR1(enable);

	// ----- TIMER32 power -----
	Sys_TmrClkPwrEnable(TIMER0, CLK_ENABLE, TMR_CLK_DVI1);
	Sys_TmrClkPwrEnable(TIMER1, CLK_ENABLE, TMR_CLK_DVI2);
	Sys_TmrClkPwrEnable(TIMER2, CLK_ENABLE, TMR_CLK_DVI16);
	Sys_TmrClkPwrEnable(TIMER3, CLK_ENABLE, TMR_CLK_DVI16);
	Sys_TmrClkPwrEnable(TIMER4, CLK_ENABLE, TMR_CLK_DVI8);
	Sys_TmrClkPwrEnable(TIMER5, CLK_ENABLE, TMR_CLK_DVI32);

	// ----- RTC power -----
	SYS_CLKPWR_RTC(enable);
	SYSTEM->PERICLKPWR2_b.RC32KSRCSEL = 1;

	// ----- WDT power -----
	SYS_CLKPWR_WDT(enable);
	SYS_CLKPWR_PWRBTN(enable);

	// ----- eSPI power -----
	SYS_CLKPWR_ESPI(enable);

	// ----- Monotonic power -----
	SYS_CLKPWR_MONOTONMIC(enable);

	// ----- DIO enable -----
	SYSTEM->FUNOPTION_b.DIOACCESSEN = 1;

	// ----- IO power -----
	SYS_CLKPWR_KBC(enable);
	SYS_CLKPWR_ACPI0(enable);
	SYS_CLKPWR_ACPI1(enable);
	SYS_CLKPWR_ACPI2(enable);
	SYS_CLKPWR_ACPI3(enable);
	SYS_CLKPWR_ACPI4(enable);

	// ----- EMI power -----
	SYS_CLKPWR_EMI0(enable);
	SYS_CLKPWR_EMI1(enable);
	SYS_CLKPWR_EMI2(enable);
	SYS_CLKPWR_EMI3(enable);
	SYS_CLKPWR_EMI4(enable);
	SYS_CLKPWR_EMI5(enable);
	SYS_CLKPWR_EMI6(enable);
	SYS_CLKPWR_EMI7(enable);

	// ----- KBM power -----
	SYS_CLKPWR_KBM(enable);

	// ----- P8081 power -----
	SYS_CLKPWR_PORT80(enable);

	// ----- PWM power -----
	SYS_CLKPWR_PWM0(enable);
	SYS_CLKPWR_PWM1(enable);
	SYS_CLKPWR_PWM2(enable);
	SYS_CLKPWR_PWM3(enable);
	SYS_CLKPWR_PWM4(enable);
	SYS_CLKPWR_PWM5(enable);
	SYS_CLKPWR_PWM6(enable);
	SYS_CLKPWR_PWM7(enable);
	SYS_CLKPWR_PWM8(enable);
	SYS_CLKPWR_PWM9(enable);
	SYS_CLKPWR_PWM10(enable);
	SYS_CLKPWR_PWM11(enable);

	// ----- LED power -----
	SYS_CLKPWR_PL0(enable);
	SYS_CLKPWR_PL1(enable);

	// ----- PS2 power -----
	SYS_CLKPWR_PS2(enable);

	// ----- I2C power -----
	SYS_CLKPWR_I2CAUTO(enable);
	Sys_I2cClkPwrEnable(I2C0_UNIT, enable, 0,0);
	Sys_I2cClkPwrEnable(I2C1_UNIT, enable, 0,0);
	Sys_I2cClkPwrEnable(I2C4_UNIT, enable, 0,0);

	// ----- TACH power -----
	SYS_CLKPWR_TACHO0(enable);
	SYS_CLKPWR_TACHO1(enable);
	SYS_CLKPWR_TACHO2(enable);
	SYS_CLKPWR_TACHO3(enable);
}

static void Kernel_init(void)
{
	RSTIMER_Type Kernel_SLWT0;
	RSTIMER_Type Kernel_RT;

	Sys_TmrPause(TIMER0, TMR_NOT_PUASE);
	Sys_TmrPause(TIMER1, TMR_NOT_PUASE);
	Sys_TmrPause(TIMER2, TMR_NOT_PUASE);
	Sys_TmrPause(TIMER3, TMR_NOT_PUASE);
	Sys_TmrPause(TIMER4, TMR_NOT_PUASE);
	Sys_TmrPause(TIMER5, TMR_NOT_PUASE);

	Sys_TmrHoldRst(TIMER0, TMR_HOLD_RST);
	Sys_TmrHoldRst(TIMER0, TMR_RELEASE_RST);
	Sys_TmrHoldRst(TIMER1, TMR_HOLD_RST);
	Sys_TmrHoldRst(TIMER1, TMR_RELEASE_RST);
	Sys_TmrHoldRst(TIMER2, TMR_HOLD_RST);
	Sys_TmrHoldRst(TIMER2, TMR_RELEASE_RST);
	Sys_TmrHoldRst(TIMER3, TMR_HOLD_RST);
	Sys_TmrHoldRst(TIMER3, TMR_RELEASE_RST);
	Sys_TmrHoldRst(TIMER4, TMR_HOLD_RST);
	Sys_TmrHoldRst(TIMER4, TMR_RELEASE_RST);
	Sys_TmrHoldRst(TIMER5, TMR_HOLD_RST);
	Sys_TmrHoldRst(TIMER5, TMR_RELEASE_RST);

	// Use SLWTIMER0 for kernel timer
	//Kernel_SLWT0.Tmr_Num = STIMER0;
	//Kernel_SLWT0.LoadCount = 1000;
	//Kernel_SLWT0.Mode = Continuous;
	//Kernel_SLWT0.INT_En = enable;
	//Kernel_SLWT0.OnOff = 1;
	//SLWTIMER_Config(&Kernel_SLWT0);

	//SLWTMR0_EnableIRQ();

	Kernel_RT.LoadCount = 32;		// 1ms
	Kernel_RT.Mode = Continuous;
	Kernel_RT.INT_En = true;
	Kernel_RT.OnOff = 1;
	RTIMER_Config(&Kernel_RT);
	RTMR_EnableIRQ();

	Kernel_RAM_init();
	
	// VW INIT
	VW_ResetSts();
	ESPI->ESPICFG = 0x0000000F;	// 20MHz, single mode

	ESPI->EVRXINTEN_b.RXCHGEN = 1;
	EVCHIDX3_EnableIRQ();
	EVCHIDX7_EnableIRQ();

	// Config SPI
	GPIO_Pin_On(107,0);
	GPIO_Pin_On(108,0);
	GPIO_Pin_On(109,0);
	GPIO_Pin_On(111,0);

	//Init ESPI
	GPIO_Set_Vlot(9,0);		// for AMD
	GPIO_Pin_On(20,0);
	// Config espi
	GPIO_Func_Mode(3,1);
	GPIO_Func_Mode(4,1);
	GPIO_Func_Mode(5,1);
	GPIO_Func_Mode(6,1);
	GPIO_Func_Mode(7,1);
	GPIO_Func_Mode(8,1);
	GPIO_Func_Mode(9,1);
	
	// Smitter trigger disable
	GPIO_Set_Schmit(3,0);
	GPIO_Set_Schmit(5,0);
	GPIO_Set_Schmit(6,0);
	GPIO_Set_Schmit(7,0);
	GPIO_Set_Schmit(8,0);
	GPIO_Set_Schmit(9,0);
	
	GPIO_Set_Driving(3,1);
	GPIO_Set_Driving(4,1);
	GPIO_Set_Driving(5,1);
	GPIO_Set_Driving(6,1);
	GPIO_Set_Driving(7,1);
	GPIO_Set_Driving(8,1);
	GPIO_Set_Driving(9,1);

	/* eRPMC initial */
	EOCHTX_EnableIRQ();
	EOCHRX_EnableIRQ();
	ESPI->EORXBUF = (uint32_t) &OOB_IN_BUF[0];

	ESPI->EORXINTEN_b.RXEN = 1;
	ESPI->EOTXINTEN_b.TXEN = 1;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Initial LDN function
	// KBC/ACPI/PMPORT...
	// EMI/MailBox/RTC/UART
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// default LDN port 2E/2F
#if (LDNPORT == 1)
	ESPI->LDNCFG_b.IDX = 0x004E;
#endif

	// Enable KBC IRQ
	KBC_Set_IRQ_Number(1);
	KBC_Enable_autoIRQ(enable, 1);
	KBC_Enable_Interrupt(_IBF, enable);
	KBC_Init();
	KBC_IB_EnableIRQ();

	// Enable ACPI IRQ
	ACPI_Enable_Interrupt(_IBF, enable);
	ACPI_Init();
	ACPI_IB_EnableIRQ();
	timer323_BurstMode_Setting();

#if SupportPM0
	// Enable PMPORT0 setting and IRQ
	PM0_Change_PortAddr(PM0PORT, 1);
	PM0_Enable_Interrupt(_IBF, enable);
	PM0_Init();
	PMPORT0_IB_EnableIRQ();
#endif

#if SupportPM1
	// Enable PMPORT1 setting and IRQ
	PM1_Change_PortAddr(PM1PORT, 1);
	PM1_Enable_Interrupt(_IBF, enable);
	PM1_Init();
	PMPORT1_IB_EnableIRQ();
#endif

#if SupportPM2
	// Enable PMPORT2 setting and IRQ
	PM2_Change_PortAddr(PM2PORT, 1);
	PM2_Enable_Interrupt(_IBF, enable);
	PM2_Init();
	PMPORT2_IB_EnableIRQ();
#endif

#if SupportPM3
	// Enable PMPORT3 setting and IRQ
	PM3_Change_PortAddr(PM3PORT, 1);
	PM3_Enable_Interrupt(_IBF, enable);
	PM3_Init();
	PMPORT3_IB_EnableIRQ();
#endif

	IniKBM();
	KBM_EnableIRQ();
}

void Kernel_RAM_init(void)
{
#if Support_ESPI_ERPMC
	MCdata[0] = 0;
	MCdata[1] = 0;
	MCdata[2] = 0;
	MCdata[3] = 0;
#endif
	DebugPtr = 0;
}

static void DisableModule(void)
{


}

static void EnableModule(void)
{


}

static void System_EnterSleepMode(void)
{
	DisableModule();
	SYSTEM->PLLCTRL_b.PWREN = 1;			// Force to enable PLL
	while(SYSTEM->PLLCTRL_b.RDY != 1);		// Wait until PLL is ready
	SYSTEM->SYSCLK_b.CLKSRC = 1;			// Switch system clock to PLL

#if SupportHeavySleep
	SYSTEM->SLPCTRL_b.SLPMDSEL = 1;			// Heavy Sleep mode
#else
	SYSTEM->SLPCTRL_b.SLPMDSEL = 0;			// Light Sleep mode
#endif

	GPIO_Func_Mode(4,0);					// Config CS pin as GPIO
	GPIO_Set_IO(4,0);						// Config GPIO004 as input
	GPIO_Intr_Config(4,1,3);				// Config GPIO004 low trigger
	GPIO004_EnableIRQ();
	__enable_irq();
	if(KBM->DBG_b.STEP == 0 && !(DCB->DHCSR & DCB_DHCSR_C_DEBUGEN_Msk))
	{
		__asm volatile ("wfi");
	}
	SYSTEM->SYSCLK_b.CLKSRC = 0;			// Switch system clock to OSC25MHz
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	EnableModule();
}

static void ERPMCEventHandler()
{
    BIT_CLR(SERVICEflag,SERVICE_F_ERPMC);
#if Support_ESPI_ERPMC
    ESPI_ERPMC();
#endif
    eRPMCFlag = 0;
}

static void ACPIEventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PMACPI);
    __enable_irq();
    ACPI_Process();
}

static void KBCEventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PMKBC);
    __enable_irq();
    KBC_Process();
}

static void PMIO0EventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PMIO0);
    __enable_irq();
    PM0_process();
}

static void PMIO1EventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PMIO1);
    __enable_irq();
    PM1_process();
}

static void KeyboardOutputEventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_SENDKEY);
    __enable_irq();
  //  Service_KBC_OBF();
}

static void PS2EventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PS2);
    __enable_irq();
}

static void KeyboardInputEventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_SCANKEY);
    __enable_irq();
    KbScan();
}

static void Timer1MsEventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_1ms);
    Service_1ms();
	__enable_irq();
}

static void PMIO2EventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PMIO2);
    __enable_irq();
    PM2_process();
}

static void PMIO3EventHandler()
{
    __disable_irq();
    BIT_CLR(SERVICEflag,SERVICE_F_PMIO3);
    __enable_irq();
    PM3_process();
}

static void idleEventHandler()
{
    // do nothing ...
	//System_EnterSleepMode();
}

static void(* const services[33])(void) = {
    ERPMCEventHandler, 				// 0
    ACPIEventHandler,				// 1
    KBCEventHandler,				// 2
    PMIO0EventHandler,				// 3
    PMIO1EventHandler,				// 4
    KeyboardOutputEventHandler,		// 5
    PS2EventHandler,				// 6
    KeyboardInputEventHandler,		// 7
    Timer1MsEventHandler,			// 8
    PMIO2EventHandler,				// 9
    PMIO3EventHandler,				// 10
    idleEventHandler,               // 11
    idleEventHandler,               // 12
    idleEventHandler,               // 13
    idleEventHandler,               // 14
    idleEventHandler,               // 15
    idleEventHandler,               // 16
    idleEventHandler,               // 17
    idleEventHandler,               // 18
    idleEventHandler,               // 19
    idleEventHandler,               // 20
    idleEventHandler,               // 21
    idleEventHandler,               // 22
    idleEventHandler,               // 23
    idleEventHandler,               // 24
    idleEventHandler,               // 25
    idleEventHandler,               // 26
    idleEventHandler,               // 27
    idleEventHandler,               // 28
    idleEventHandler,               // 29
    idleEventHandler,               // 30
    idleEventHandler,               // 31
    idleEventHandler,               // 32
};

static void Main_Service(void)
{
#if SupportOD
	if(KBM->DBG_b.STEP == 4) {
		KBM_Output_Type(0);
		if(KBM->DBG_b.JTAGSEL == 1) {
			*(uint32_t*) 0x400900B8 = 0x00000000;   // GPIO46 KSO5
		}
	} else if(KBM->DBG_b.STEP < 4) {
		KBM_Output_Type(1);
	}
#endif

    services[__CLZ(SERVICEflag)]();
}

static void Service_1ms(void)
{
	// 1ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_1ms)) {
		oem_1ms_service();
		BIT_CLR(TimeSlot,Time_Slot_1ms);
	}

	// 5ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_5ms)) {
		oem_5ms_service();
		BIT_CLR(TimeSlot,Time_Slot_5ms);
	}

	// 10ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_10msA)) {
		oem_10msA_service();
		BIT_CLR(TimeSlot,Time_Slot_10msA);
	}

	// 10ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_10msB)) {
		oem_10msB_service();
		BIT_CLR(TimeSlot,Time_Slot_10msB);
	}

	// 50ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_50msA)) {
		oem_50msA_service();
		BIT_CLR(TimeSlot,Time_Slot_50msA);
	}

	// 50ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_50msB)) {
		oem_50msB_service();
		BIT_CLR(TimeSlot,Time_Slot_50msB);
	}

	// 100ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_100msA)) {
		oem_100msA_service();
		BIT_CLR(TimeSlot,Time_Slot_100msA);
	}

	// 100ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_100msB)) {
		oem_100msB_service();
		BIT_CLR(TimeSlot,Time_Slot_100msB);
	}

	// 100ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_100msC)) {
		oem_100msC_service();
		BIT_CLR(TimeSlot,Time_Slot_100msC);
	}

	// 500ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_500msA)) {
		oem_500msA_service();
		BIT_CLR(TimeSlot,Time_Slot_500msA);
	}

	// 500ms service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_500msB)) {
		oem_500msB_service();
		BIT_CLR(TimeSlot,Time_Slot_500msB);
	}

	// 1S service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_1SA)) {
		oem_1SA_service();
		BIT_CLR(TimeSlot,Time_Slot_1SA);
	}

	// 1S service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_1SB)) {
		oem_1SB_service();
		BIT_CLR(TimeSlot,Time_Slot_1SB);
	}

	// 1min service routine
	if(IS_BIT_SET(TimeSlot,Time_Slot_1min)) {
		oem_1min_service();
		BIT_CLR(TimeSlot,Time_Slot_1min);
	}
}
