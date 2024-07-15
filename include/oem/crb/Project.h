#ifndef __Project_H__
#define __Project_H__
/******************************************************************************/
/** Chip sleep selection
 * 0: Light sleep, 1: Heavy Sleep
/*******************************************************************************/
#define SupportHeavySleep   1

/******************************************************************************/
/** LDN PORT
 * 0: 2E/2F, 1:4E/4F
*******************************************************************************/
#define LDNPORT 0

/******************************************************************************/
/** PM0 Channel Select
*******************************************************************************/
#define SupportPM0  1
#define PM0PORT 0x0068

/******************************************************************************/
/** PM1 Channel Select
*******************************************************************************/
#define SupportPM1  1
#define PM1PORT 0x006A

/******************************************************************************/
/** PM2 Channel Select
*******************************************************************************/
#define SupportPM2  0
#define PM2PORT 0x0078

/******************************************************************************/
/** PM3 Channel Select
*******************************************************************************/
#define SupportPM3  0
#define PM3PORT 0x007A

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef Enable
#define Enable	1
#endif

#ifndef Disable
#define Disable	0
#endif


//*****************************************************************************
// Kernel code feature
//*****************************************************************************
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function define
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define SMBusServiceCenterFunc          // Define : for SMBus service center
#define ITE_CHIP_IT557x_eSPI_MIRROR     TRUE
#define ITE_CHIP_IT557x_eSPI_NoMIRROR   FALSE
#define EC_CHIP_IT858X                  FALSE
#define EC_CHIP_IT851X                  FALSE
#define SUPPORT_PD_CHIP_ITE             TRUE //981004-231030-A

#define SUPPORT_UCSI                    FALSE //981004-231030-A
#define ITE_CHIP_IT557X                 TRUE
#define SUPPORT_INTERFACE_eSPI          TRUE
#define ITE_eSPI_LOW_FREQUENCY          TRUE    // TRUE: For Bring Up, LA Analyzer
#define eSPI_RESET_FOR_DSW_PWROK        TRUE    // TRUE: eSPI with None-DeepSx
#define SUPPORT_EN_VW_ACK_BOOT_LOAD     TRUE    // TRUE: Boot Ack after VW enable
#define SUPPORT_LPC_BUS_1_8V            FALSE   // TRUE: Setting LPC Bus 1.8V //981004-200523-M from TRUE
#define SUPPORT_MIRROR_ONCE             FALSE
#define SUPPORT_HOOK_WARMBOOT           FALSE
#define SUPPORT_MODERN_STANDBY          TRUE 
#define SUPPORT_KBSCAN_IS_GPIO          TRUE //981004-220916-A

#define _EFLASH_NV_ADDRH        0x01    //0x03F000 //981004-240422-A
#define _EFLASH_NV_ADDRM        0xF0    //981004-240422-A
#define _EFLASH_NV_ADDRL        0x00    //981004-240422-A
 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function Setting and selection
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define EC_Signature_Flag       0xB5    // For 8518 crystal free

//-----------------------------------------------------------------------------
// PS2 interface
//-----------------------------------------------------------------------------
#define TouchPad_only           TRUE    // True : Only touch pad device in this project
                                        /* Note : If TouchPad_only is set, remeber to call 
                                            PowerOffClearTPPendingData() function in power off sequnce
                                            include (S3, S4, and S5)¡C*/   

#if TouchPad_only                                     
#define MultiplexedModes        FALSE   // 0 : Doesn't support multiplexed modes.
#define PS2IFHotPlugHotSwap     FALSE   // 1 : Support PS2 interface hot-plug, hot-swap
//#define Hook_Func_DisableTP           // Support "Hook_DisableInternalTB" for EC on/off touchpad
#else
#define MultiplexedModes        TRUE    // 1 : Support multiplexed modes.
#define PS2IFHotPlugHotSwap     FALSE   // 1 : Support PS2 interface hot-plug, hot-swap
#endif

//-----------------------------------------------------------------------------
// Keyboard scan
//-----------------------------------------------------------------------------
#define KB_FnStickKey           FALSE   // True : for Fn stick key function
//#define KB_HW_KeyScan                 // To support hardward keyscan


//*****************************************************************************
// UART debug interface
// Timer 2 baudrate = Fosc / 32 / (0x10000-RCAP2)¡C
//*****************************************************************************
//#define UART_Debug        // Define : enable Tx debug (GPIO B1)

#ifdef UART_Debug 
// 9600 bps-------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xE2  
// 9600 bps-------------------------

// 19200 bps------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xF1  
// 19200 bps------------------------

// 57600 bps------------------------
#define R2HV                    0xFF
#define R2LV                    0xFB  
// 57600 bps------------------------
#endif


//*****************************************************************************
// OEM code feature
//*****************************************************************************
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// OEM Function define
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define ITE8500                   // Define : chip is 8500
//#define HSPI                      // Define : support HSPI function
#define PECI_Support              // Define : support PECI function //981004-121225-A
//#define PMC3_Support              // Define : For Intel PECI stress tool and other OEM command via PMC3
//#define SysMemory2ECRam	        // Define : support system memory cycle mapping to ec ram
#define SMBusChannel4Support      // Define : GPH1/GPH2 will select SMBus function //981004-130905-A
//#define ECPowerDownModeSupport

#ifdef ECPowerDownModeSupport
//#define ECPowerDownModeStressTest
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// OEM EC Function Setting and selection
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
// Base address select 0x00:2E/2F 0x01:4E/4F 0x02:User define  
//-----------------------------------------------------------------------------
#define Init_BADR           0x02    // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define SWCBALR | SWCBAHR 
#define Init_SWCBAHR        0x00    // I/O Port High Byte 
#define Init_SWCBALR        0x4E    // I/O Port Low  Byte
#define Init_I2EC           0x43    // Enable I2EC R/W and log 80 port 

//-----------------------------------------------------------------------------
// HSPI share
//-----------------------------------------------------------------------------
#ifdef HSPI
    //*************************************************************************
    // Define : HSPI deffering mode, Non define : HSPI non deffering mode
    //*************************************************************************
    //#define HSPI_DefferingMode    // Define : HSPI is deffering mode

    //*************************************************************************
    // HSPI setting selection
    //*************************************************************************
    //#define HSPI_Setting01    // Host[All/20MHz],                                         EC[READ(03h)/33MHz]
    //#define HSPI_Setting02    // Host[FREAD/33MHz,Otherwise/20MHz,DOFR isn't supported],  EC[1.READ(03h)/33MHz, and 2.FREAD(0Bh)/66MHz, and 3.Others/66MHz]
    //#define HSPI_Setting03    // Host[FREAD/33MHz,Otherwise/20MHz,DOFR isn't supported],  EC[1.READ(03h)/33MHz, and 2.Dual(BBh)/33MHz]
    //#define HSPI_Setting04    // Host[DOFR/50MHz Otherwise/20MHz FREAD isn't supported],  EC[1.READ(03h)/33MHz, and 2.DIOFR(BBh)/66MHz, and 3.Others/66MHz]
    #define HSPI_Setting05      // Host[All/20MHz],                                         EC[1.READ(03h)/33MHz, and 2.FREAD(0Bh)/66MHz, and 3.Others/66MHz]
    //#define HSPI_Setting06    // Host[All/20MHz],                                         EC[1.READ(03h)/33MHz, and 2.Dual(BBh)/33MHz]
    //#define HSPI_Setting07    // Host[DOFR/33MHz,Otherwise/20MHz,FREAD isn't supported],  EC[1.READ(03h)/33MHz, and 2.DIOFR(BBh)/66MHz, and 3.Others/66MHz]

    #ifdef HSPI_Setting01
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_0           // Read cycle
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting02
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_1           // Fast read cycle
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting03
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting04
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_0 // HSPI request Setting 1, 2, 3, and 4
    #endif

    #ifdef HSPI_Setting05
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_1           // Fast read cycle
    #define HSRSMode            HSPI_RequestSelection_2 // HSPI request Setting 5
    #endif

    #ifdef HSPI_Setting06
    #define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_1 // HSPI request Setting 6 and 7
    #endif

    #ifdef HSPI_Setting07
    #define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    #define SPIReadMode         SPIReadMode_3           // Fast read dual input/output
    #define HSRSMode            HSPI_RequestSelection_1 // HSPI request Setting 6 and 7
    #endif
    
	#define Init_FMSSR	    0x0E	// 0x1F 16M Bytes Share Rom for HSPI
	
#else       
//-----------------------------------------------------------------------------
// LPC share
//-----------------------------------------------------------------------------
    //*************************************************************************
    // EC SPI [fast read, 64.5MHZ]
    //*************************************************************************
    //#define PLLFrequency        PLLFreqSetting07        // 64.5 MHZ PLL frequency
    //#define SPIReadMode         SPIReadMode_1           // Fast read cycle

    //*************************************************************************
    // EC SPI [read, 46MHZ]
    //*************************************************************************
    //#define PLLFrequency        PLLFreqSetting05        // 46 MHZ PLL frequency
    //#define SPIReadMode         SPIReadMode_0           // read cycle

    //*************************************************************************
    // EC SPI [read, 32.3MHZ]
    //*************************************************************************
    //#define PLLFrequency        PLLFreqSetting03        // 32.3 MHZ PLL frequency //981004-121214-R
    //#define SPIReadMode         SPIReadMode_0           // read cycle, 2012/08/07 for eFlash Compatible
    
	#define Init_FMSSR	    0x07	// 0x1F 2M Bytes Share Rom //from 0x1F
#endif						        // 0x0F 1M Bytes Share Rom 
							        // 0x07 512K Bytes Share Rom 
//-----------------------------------------------------------------------------
// GPIO pin scan keybaord
//-----------------------------------------------------------------------------
#define ExternMatrixGPO		    FALSE   // True : using GPO Pin scan keyboard
									    // Note : just support one GPIO pin now !!!
#define GPOKeyPin1H		        SET_MASK(GPDRF,BIT(0))	// For extend GPIO scan keys
#define GPOKeyPin1L		        CLEAR_MASK(GPDRF,BIT(0))	
#define GPOKeyPin1Ctl	        GPCRF0  // GPCRF0

//-----------------------------------------------------------------------------
// Control ACPI
//-----------------------------------------------------------------------------
#define ACPI_Smbus			    FALSE   // True : for ACPI Smbus function
#define ACPI_QEventPending      FALSE   // True : EC will pending q-event, if 62/66 IBF

//*****************************************************************************
//-----------------------------------------------------------------------------
// OEM support function selection
//-----------------------------------------------------------------------------
//*****************************************************************************
#define ADCFuncSupport			TRUE    // True : support ADC function //981004-231002-M from FALSE
#define CIRFuncSupport			FALSE   // True : support cir function
#define LEDFuncSupport          FALSE   // True : support LEC control function
#define HookFucnofWriteECRam    FALSE   // True : Hook function For ACPI command 0x81 write EC space 
#define S3KeyboardWakeUp        FALSE   // True : support S3 wake up from internal keyboard
#define MailBoxRWECRam          FALSE
#define Insyde_Bios             FALSE

//-----------------------------------------------------------------------------
// Power sequence
//-----------------------------------------------------------------------------
#define ECSleepModeSupport      FALSE   // True : support EC sleep mode
#define PowerSequnceOnly        FALSE   // True : only support 1ms function

//-----------------------------------------------------------------------------
// Fan & Thermal
//-----------------------------------------------------------------------------
#define SmartFanSupport         FALSE   // True : Support smart fan control function
#define GetCPUTempSupport       1   // True : get cpu temperature via PECI or thermal sensor per second
#define GetSysTempSupport       FALSE   // True : get thermal sensor local temperature per second

//-----------------------------------------------------------------------------
// Battery
//-----------------------------------------------------------------------------
#define SmartCharger_Support    FALSE   // True : using charger IC for battery charge control
#define BAT1FuncSupport         FALSE   // True : support battery 1 management function

//-----------------------------------------------------------------------------
// PECI
//-----------------------------------------------------------------------------
#ifdef PECI_Support
#define ReadCPUTemperature      1   // 1 : Getting CPU temperature via PECI interface //981004-121225-M
#define ReadPKGTemperature      1  // 1 : Getting package temperature via PECI interface //981004-121225-M
#define ReadDRAMTemperature     1   // 1 : Getting DRAM temperature via PECI interface //981004-121225-M
#define ACTurboControlAlgorithm 1 //981004-121225-M
#endif

//-----------------------------------------------------------------------------
// OEM_Event.C Debounce time setting
//-----------------------------------------------------------------------------
#define T_AC_DEBOUNCE    	    1       // 10 ms (timebase: 10 ms) //50ms=>10ms If EC no power under AC mode with S5 status,press power button slightly may not be able to boot up  
#define T_PSW_DEBOUNCE   	    5    	// 50 ms (timebase: 10 ms)
#define T_BAT_DEBOUNCE   	    15      // 150 ms (timebase: 10 ms)
#define T_PSWOFF         	    400 	// 4 secs (timebase: 10ms) EC 4sec override turn off system power //981004-210401-M from 500
#define T_EXTEVT_DEBOUNCE 	    10      // 100 ms (timebase: 10 ms)
#define T_PDAC_DEBOUNCE       	5       // 50 ms  (timebase: 10 ms) //981004-210114-A

//#define T_AC_DEBOUNCE            1      // 100 ms   (timebase: 100ms) //981004-100531-M from 50ms
//#define T_PSW_DEBOUNCE           5      // 50 ms   (timebase: 10ms)
#define T_SMRT_DEBOUNCE          5      // 50 ms   (timebase: 10ms)  //981004-100421-A
#define T_V3DPLUS_DEBOUNCE       5      // 50 ms   (timebase: 10ms)  //981004-101118-A
#define T_V3DMINUS_DEBOUNCE      5      // 50 ms   (timebase: 10ms)  //981004-101118-A	
//#define T_BAT_DEBOUNCE           2      // 200 ms  (timebase: 100ms) //981004-100421-M
#define T_LID_DEBOUNCE           50      // 500ms      (timebase: 10ms)
#define T_HDMI_DEBOUNCE          50      // 500ms      (timebase: 10ms)
#define T_SLP_S3                 1      // 10ms
#define T_SLP_S4                 1      // 10ms
//#define T_PSWOFF               380      // 3.8 sec (timebase: 10ms)

//-----------------------------------------------------------------------------
// Power On Sequence Time-Out Condition
//-----------------------------------------------------------------------------
#define T_HWPG           	    500  	// 500ms (timebase: 1ms)

//-----------------------------------------------------------------------------
// SCI Q-event define
//-----------------------------------------------------------------------------
//#define PowerManagement         0x20
#endif
