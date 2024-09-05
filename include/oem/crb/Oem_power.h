#ifndef __Oem_power_H__
#define __Oem_power_H__

extern void G3_S5_PS(void);
extern void S5_S0_PS(void);
extern void S0_S5_PS(void);
extern void S0_S3_PS(void);
extern void S3_S0_PS(void);
extern void DoPowerStatus(void);

extern void S0_S3Variable(void);
extern void Oem_TriggerS0S3(uint8_t causecode); 
extern void Oem_TriggerS0S4(uint8_t causecode);
extern void Oem_TriggerS3S0(void); 
extern void Oem_TriggerS4S0(void);

extern void CheckPowerState(void);
extern void InitDevice(void);

#define PWR_PULSE_L             GPIO->GCR_b[114].OUTCTRL
//#define PM_PWRBTN_EC_HIGH()		GPIO_Write(114,1)
//#define PM_PWRBTN_EC_LOW()		GPIO_Write(114,0)

#define PWRSW_L				    GPIO_Read(112)

#define PCH_PWROK               GPIO->GCR_b[19].OUTCTRL
//#define EC_PCH_PWROK_HIGH()		GPIO_Write(19,1)
//#define EC_PCH_PWROK_LOW()		GPIO_Write(19,0)

#define ALL_SYS_PWRGD           GPIO->GCR_b[116].OUTCTRL
//#define ALL_SYSTEM_PWRGD_HIGH()	GPIO_Write(116,1)
//#define ALL_SYSTEM_PWRGD_LOW()	GPIO_Write(116,0)

#define EC_SYS_PWROK_HIGH()		GPIO_Write(125,1)
#define EC_SYS_PWROK_LOW()		GPIO_Write(125,0)

#define IMVP_VR_READY			GPIO_Read(117)

#define EC_BKLOUT               GPIO->GCR_b[84].OUTCTRL

#define USB_EN_EC               GPIO->GCR_b[121].OUTCTRL

#define USB_V5A_EN              GPIO->GCR_b[96].OUTCTRL

#define VCCIO_PWRGD()			1//GPIO_Read(1)

#define RSMRST_L                GPIO->GCR_b[86].OUTCTRL

#define IS_PCH_RSMRST_HI()      GPIO_Read(86)

#define EC_CLR_LATCH            GPIO->GCR_b[87].OUTCTRL

#define EC_EN_V5A               GPIO->GCR_b[122].OUTCTRL

#define AC_PRESENT              GPIO->GCR_b[97].OUTCTRL

#define dGPU_HOLD_EC_RST_L      GPIO->GCR_b[105].OUTCTRL

#define AC_IN_L 				GPIO_Read(16)

#define H_PROCHOT_L             GPIO->GCR_b[28].OUTCTRL

#define SMBSW_RST_HIGH			GPIO_Write(3,1)		//GPB6 SMBSW_RST_L
#define SMBSW_RST_LOW			GPIO_Write(3,0)


#define BAT_LED_L               GPIO->GCR_b[25].OUTCTRL


#define PWR_LED2_L              GPIO->GCR_b[27].OUTCTRL


#define DDS_PANEL_RST           GPIO->GCR_b[102].OUTCTRL


#define EC_3A                   GPIO->GCR_b[0].OUTCTRL 

#define PD_ADAPTER_IN			GPIO_Read(81)		//GPI7 PD_ADAPTER_IN
#define PD_ADAPTER_IN2          GPIO_Read(2)		//GPB6 PD_ADAPTER_IN

#define EC_AMP_MUTE_L           GPIO->GCR_b[18].OUTCTRL

#define BAT_IN_L				GPIO_Read(113)

#define EDP_GPU_SEL_HIGH		GPIO_Write(103,1)		//GPH4 GPIO103
#define EDP_GPU_SEL_LOW			GPIO_Write(103,0)

#define DDS_MUX_CNTL_HIGH		GPIO_Write(13,1)	//GPD4 GPIO013
#define DDS_MUX_CNTL_LOW		GPIO_Write(13,0)

#define EC_BKLOUT_HIGH			GPIO_Write(84,1)//GPJ1 GPIO84
#define EC_BKLOUT_LOW			GPIO_Write(84,0)

#define LID_L					GPIO_Read(123)	//GPC4 GPIO123
#define IS_LID_SW_CLOSE()       (GPIO_Read(123)==1)

#define HPD_EC_L				GPIO_Read(104)	//GPH5 GPIO104

#define BT_EN                   GPIO->GCR_b[83].OUTCTRL


#define PD_POWER_ON             GPIO->GCR_b[130].OUTCTRL


#define WLAN_EN                 GPIO->GCR_b[82].OUTCTRL


#define CCD_EN                  GPIO->GCR_b[94].OUTCTRL



#if RTK_FPGA_MODE
#define EC_S3_DDR5_EN_HIGH()	GPIO_Write(35,1)	//GPIO035 in FPGA mode
#define EC_S3_DDR5_EN_LOW()		GPIO_Write(35,0)	//GPIO035 in FPGA mode
#else
#define EC_S3_DDR5_EN           GPIO->GCR_b[90].OUTCTRL

#define USB_KBD_PWR             GPIO->GCR_b[95].OUTCTRL
#define TBT_POWER               GPIO->GCR_b[61].OUTCTRL
#define TBT_SWITCH              GPIO->GCR_b[126].OUTCTRL

#define HDA_SDO                 GPIO->GCR_b[128].OUTCTRL
#define DDS_PWM                 GPIO->GCR_b[31].OUTCTRL
#define DDS_PWM_SWITCH          GPIO->GCR_b[21].OUTCTRL
//#define SLP_S4_L                GPIO_Read(78)

#define BAT_FULL_L              GPIO->GCR_b[29].OUTCTRL

#define DEBUG_CARD_L            GPIO_Read(60)

#endif


#define	SYSTEM_EC_WDTRST	0x0F

#define SC_S0SLPOff		    0x01	// System shutdown by S3/S4/S5 Off
#define SC_S3S4SLPOff		0x02	// System shutdown by S3/S4/S5 fail Off
#define SC_4SEC		        0x03	// System shutdown by power button 4 sec overwrite
#define SC_CPUHOT		    0x04	// System shutdown by CPU too hot to shutdown
#define SC_HWPGSx_S0Off		0x05	// System shutdown by HWPG Fail in Sx_S0 power sequence
#define SC_HWPS0Off		    0x06	// System shutdown by HWPG Fail in S0
#define SC_PowerOnWatchDog  0x07    // System shutdown by Power on WDT

#define SC_EC_0x0000        0xEC    // EC code reset
#define SC_ExtWatchDog      0xFF    // external watch-dog
#define SC_IntWatchDog      0xFE    // internal watch-dog
#define SC_ECColdBoot       0xFC    // EC VSTBY or WRST reset

//-----------------------------------------------------------------------------
// System status define
//-----------------------------------------------------------------------------
#define SysPowState         SystemState
#define SystemIsS0          SystemState==SYSTEM_S0
#define SystemIsS3          SystemState==SYSTEM_S3
#define SystemIsS4          SystemState==SYSTEM_S4

#define SystemNotS0         SystemState!=SYSTEM_S0
#define SystemNotS3         SystemState!=SYSTEM_S3
#define SystemNotS4         SystemState!=SYSTEM_S4

#define SLP_S4_L GetSlp_S4
#define SLP_S3_L GetSlp_S3



//-----------------------------------------------------------------------------
// Define
//-----------------------------------------------------------------------------
#define	SYSTEM_S0			0x10
#define	SYSTEM_S3			0x33
#define	SYSTEM_S4			0x44
#define	SYSTEM_S4_S0		0x01
#define	SYSTEM_S3_S0		0x02
#define	SYSTEM_S0_S3		0x03
#define	SYSTEM_S0_S4		0x04
#define	SYSTEM_EC_WDTRST	0x0F

//-----------------------------------------------------------------------------
// Shutdown cause
//-----------------------------------------------------------------------------
#define SC_S0SLPOff		    0x01	// System shutdown by S3/S4/S5 Off
#define SC_S3S4SLPOff		0x02	// System shutdown by S3/S4/S5 fail Off
#define SC_4SEC		        0x03	// System shutdown by power button 4 sec overwrite
#define SC_CPUHOT		    0x04	// System shutdown by CPU too hot to shutdown
#define SC_HWPGSx_S0Off		0x05	// System shutdown by HWPG Fail in Sx_S0 power sequence
#define SC_HWPS0Off		    0x06	// System shutdown by HWPG Fail in S0
#define SC_PowerOnWatchDog  0x07    // System shutdown by Power on WDT

#define SC_EC_0x0000        0xEC    // EC code reset
#define SC_ExtWatchDog      0xFF    // external watch-dog
#define SC_IntWatchDog      0xFE    // internal watch-dog
#define SC_ECColdBoot       0xFC    // EC VSTBY or WRST reset


//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void CheckPowerState(void);
extern void Oem_TriggerS3S0(void);
extern void Oem_TriggerS4S0(void);
extern void Oem_TriggerS5S0(void);
extern void Oem_S4S0Sequence(void);
extern void Oem_S3S0Sequence(void);

extern void EnterDeepSleep(void);
extern BYTE CheckEnterDeepSleep(void);

extern void MoniterHWPG(void);
extern void Oem_SysPowerContrl(void);
extern void Oem_TriggerS0S3(BYTE causecode);
extern void Oem_TriggerS0S4(BYTE causecode);
extern void Oem_S0S3Sequence(void);
extern void Oem_S0S4Sequence(void);
extern void CheckResetSource(void);

extern void S4_S0Variable(void);
extern void S3_S0Variable(void);
extern void S0_S4Variable(void);
extern void S0_S3Variable(void);

extern void CheckSLP_S3(void);
extern void CheckSLP_S4(void);
extern void PulseSBPowerButton(void);
extern void CheckSBPowerButton(void);

static void InitPWM(void); //981004-121122-A
///static void InitDevice(void); //981004-121122-A
extern void InitLVDS(void); //981004-130124-A
extern BYTE KBbclCtrl(BYTE Level); 
extern void INIT_TM1650(void); //981004-180712-A
extern void EC_ACK_eSPI_Reset(void);

typedef struct PowerSEQ
{
    FUNCT_PTR_B_V	func;         // Do step function
    WORD          delay;        // delay time (ms) 
    BYTE          checkstatus;	// step function is check pin status (EX: slp_s3 HWPG ...)
} sPowerSEQ;

//981004-200721-A-S
/*-----------------------------------------------------------------------------
 * ModernStandby Calling Prototype
 *---------------------------------------------------------------------------*/
#define _EC_GENERAL_IDLE        0x80
#define _EC_ATHENA_IDLE         0x81
#define _EC_MODERN_STANDBY      0x82
#define _EC_POWER_DOWN_IDLE     0x83

extern void InitEntry_DeepSleep(void);
extern void InitExit_DeepSleep(void);
extern void CheckCanGo_AthenaIdle(void);
extern void CheckCanGo_ModernStandby(void);
extern void InitEntry_AthenaIdle(void);
extern void InitExit_AthenaIdle(void);
extern void InitEntry_ModernStandby(void);
extern void InitExit_ModernStandby(void);
extern void InitWake_ModernStandby(void);
extern void InitSleep_ModernStandby(void);
extern void Hook_ModernStandbyService(void);
extern void Hook_ModernStandbyService1ms(void);
extern void SET_ExitMS(BYTE ExitCode, BYTE ExitTsec);
//981004-200721-A-E

 extern void service_eSPI_handshake(void);

#endif
