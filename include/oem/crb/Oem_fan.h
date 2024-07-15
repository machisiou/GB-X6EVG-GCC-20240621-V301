/**
 * @file Oem_fan.h
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <stdint.h>

#define CPUTHERMSHDN        0x64 //981004-130328-M from 0x69 //EC THERMAL SHUTDOWN
#define CPUTHERMSHDN_BROADWELL  0x69 //981004-150424-A
#define THRTLOFF            0x5A //981004-120419-M from 0x5F
#define THRTLON             0x65 //981004-120419-M from 0x66

//-----------------------------------------------------------------------------
// Define PCH address
//-----------------------------------------------------------------------------

//#define RPCHThermalAddr 	    0x4B
#define PCHThermalAddr 	    0x96
//#define WPCHThermalAddr 	    0x4C


//-----------------------------------------------------------------------------
// Define PCH Command
//-----------------------------------------------------------------------------
#define RPCHDAT	        0x40	// Read block data (20 Byte)
#define WSTS	        0x41	// Write STS registers (6 Bytes)
#define WCPULIMIT	    0x42	// Write CPU temperature limit (4 Bytes)
#define WMCHLIMIT	    0x43	// Write MCH temperature limit (2 Bytes)
#define WPCHLIMIT	    0x44	// Write PCH temperature limit (2 Bytes)
#define WDIMMLIMIT	    0x45	// Write Memory temperature limit (2 Bytes)
#define WCPUPOWER	    0x50	// Write CPU power clamp(2 Bytes) 

//-----------------------------------------------------------------------------
// Define GPU address & Command
//-----------------------------------------------------------------------------
#define GPUThermalAddr 	0x9E    // Nvidia Second GPU SMBUS address //981004-151210-M from 0x9C
#define GPUThermalAddr2 0x9E    // Nvidia Master GPU SMBUS address //981004-130906-A
#define RLTS	        0x00	// Read Nvidia GPU Temperature //981004-100212-A
#define VENDOR_ID	    0xFE	// Read Nvidia GPU Vendor ID //981004-100212-A
#define REV_ID	        0xFF	// Read Nvidia GPU Revision ID //981004-100212-A
//-----------------------------------------------------------------------------


//981004-210617-A-S
//-----------------------------------------------------------------------------
// Define Light Sensor address & Command (LTR-F216A)
//-----------------------------------------------------------------------------
#define LightSensorAddr 0xA6    //981004-210617-M drom 0x90
#define CONTROL	        0x00	// Power on/off Light sensor (BIT 0)
#define SET_RATE	    0x04    // Set rate and resolution (R/W)
#define CLEARDATA_L	    0x0A	// Clear LSB ALS 8bits data (Read Only)
#define CLEARDATA_M	    0x0B	// Clear Medium ALS 8bits data (Read Only)
#define CLEARDATA_H	    0x0C	// Clear MSB ALS 8bits data (Read Only)
#define DATAREAD_L	    0x0D	// LSB ALS 8bits data (Read Only)
#define DATAREAD_M	    0x0E	// Medium ALS 8bits data (Read Only)
#define DATAREAD_H	    0x0F	// MSB ALS 8bits data (Read Only)
#define LightSensorAddr2 0x18 //0x0C //981004-150821-A for SM3218 Light sensor
//-----------------------------------------------------------------------------
//981004-210617-A-E

//981004-220509-A-S
//-----------------------------------------------------------------------------
// Define Thermal IC NCT7802Y address & Command
//-----------------------------------------------------------------------------
#define NCT7802YAddr    0x50    // Thermal IC NCT7802Y address (ADD0 = LOW,ADD1 = LOW,ADD2 = LOW) //981004-220810-M from 0x52
#define FAN1_THERMAL	0x01	// FAN1 Thermal High Byte readout(Read Only)
#define FAN2_THERMAL	0x02	// FAN2 Thermal High Byte readout(Read Only)
#define FAN3_THERMAL	0x03	// FAN3 Thermal High Byte readout(Read Only)
#define FAN1_RPMH	    0x10	// FAN1 RPM High Byte readout(Read Only)
#define FAN2_RPMH	    0x11	// FAN2 RPM High Byte readout(Read Only)
#define FAN3_RPMH	    0x12	// FAN3 RPM High Byte readout(Read Only) //981004-231002-A
#define FAN_RPML	    0x13	// FAN1/FAN2 RPM LOW Byte readout(Read Only) => Bit3 ~ Bit7 
#define START_SET	    0x21	// Start NCT7802Y (R/W)
#define NCT_MODE_SEL	0x22	// Select FAN1/FAN2 Thermistor (R/W)
#define FANCTRL1	    0x60    // SMART FAN READ ONLY to read FAN1 DUTY	
#define FANCTRL2	    0x61    // SMART FAN READ ONLY to read FAN2 DUTY
#define FANCTRL3	    0x62
#define RPM_MODE_SEL	0x63	// Set FAN1/FAN2 to RPM mode (R/W) => BIT5/BIT6 (FAN1/FAN2)
#define FANCTRL_MAP  	0x64	// Set FAN1/FAN2 TEMP1/TEMP2 mapping => Should Set 0x21 
#define TEMP_SOURCE  	0x68	// Set FAN1/FAN2 TEMP1/TEMP2 source selection (R/W) => Should Set 0x10 
#define RPM_TOL      	0x6D	// Set FAN1/FAN2 RPM tolerance (R/W) => Unit is 50 
#define FANCTRL_UP_Time	0x6E	// Set FAN1/FAN2 step up timing(R/W) => Unit 0.1 SEC Default is 0x0A => 1 SEC
#define FANCTRL_DN_Time	0x6F	// Set FAN1/FAN2 step down timing(R/W) => Unit 0.1 SEC Default is 0x0A => 1 SEC
#define HYSTERSIS_CTRL1	0x74	// Set temperature1 curve(R/W) => Default is 0x53h page 59
#define HYSTERSIS_CTRL2	0x75	// Set temperature2 curve(R/W) => Default is 0x53h page 59
#define FAN_STOP    	0x78	// Set FANCTRL1/FANCTRL2 stop timing (R/W) => Unit 0.1 SEC Default is 0xFF => 25.5 SEC
#define FANCTRL_NONSTOP 0x79	// Set FANCTRL1/FANCTRL2 N0NSTOP function => BIT0/BIT1(FAN1/FAN2)
#define FAN1_TEMP1	    0x80	// Set FAN1 LEVEL 1 temperature (R/W)
#define FAN1_TEMP2	    0x81	// Set FAN1 LEVEL 2 temperature (R/W)
#define FAN1_TEMP3	    0x82	// Set FAN1 LEVEL 3 temperature (R/W)
#define FAN1_TEMP4	    0x83	// Set FAN1 LEVEL 4 temperature (R/W)
#define CRITICAL_TEMP1	0x84	// Set FAN1 Critical temperature (R/W) => Default value is 0x3C(60C)
#define FAN1_RPM1	    0x85	// Set FAN1 LEVEL 1 RPM (R/W) => Set 0x28 => 40 * 50 = 2000
#define FAN1_RPM2	    0x86	// Set FAN1 LEVEL 2 RPM (R/W)
#define FAN1_RPM3	    0x87	// Set FAN1 LEVEL 3 RPM (R/W) 
#define FAN1_RPM4	    0x88	// Set FAN1 LEVEL 4 RPM (R/W)
#define FAN2_TEMP1	    0x90	// Set FAN2 LEVEL 1 temperature (R/W)
#define FAN2_TEMP2	    0x91	// Set FAN2 LEVEL 2 temperature (R/W)
#define FAN2_TEMP3	    0x92	// Set FAN2 LEVEL 3 temperature (R/W)
#define FAN2_TEMP4	    0x93	// Set FAN2 LEVEL 4 temperature (R/W) 1
#define CRITICAL_TEMP2	0x94	// Set FAN2 Critical temperature (R/W) => Default value is 0x3C(60C)
#define FAN2_RPM1	    0x95	// Set FAN2 LEVEL 1 RPM (R/W) => Set 0x28 => 40 * 50 = 2000
#define FAN2_RPM2	    0x96	// Set FAN2 LEVEL 2 RPM (R/W)
#define FAN2_RPM3	    0x97	// Set FAN2 LEVEL 3 RPM (R/W) 
#define FAN2_RPM4	    0x98	// Set FAN2 LEVEL 4 RPM (R/W)

//-----------------------------------------------------------------------------
//981004-220509-A-E

//981004-180712-A-S
//-----------------------------------------------------------------------------
// Define PS8803 address & Command
//-----------------------------------------------------------------------------
#define PS8803Addr      0x0A
//-----------------------------------------------------------------------------
//981004-180712-A-E
typedef struct thermalstruct
{
	BYTE Level;
	BYTE FanOn;
	BYTE FanOff;
	BYTE DACValue;	
}thermal;


typedef struct thermal2struct
{
	BYTE Level;
	BYTE FanOn;
	BYTE FanOff;
	BYTE DACValue;
    BYTE DACValue2;	
}thermal2;

//-----------------------------------------------------------------------------
// Moniter temperature
//-----------------------------------------------------------------------------
#define CpuTooHot        95
#define CpuTooHotTimes   10 //981004-221130-M from 3
#define SysTooHot        90
#define SysTooHotTimes   20

//#define CPUTemp        0xF0660000
//#define MCHTemp        0x6000
//#define PCHTemp        0x6400

//981004-121122-A-S
#define EDPAddr0 	0x10
#define EDPAddr2 	0x12
#define EDPAddr4 	0x14
#define EDPAddr8 	0x18
//981004-121122-A-S


#if 0
//-----------------------------------------------------------------------------
// Polling thermal sensor data
//-----------------------------------------------------------------------------
#define CPULocalCmd	0x00	// Read Local temprature
#define CPURemoteCmd	0x01	// Read remote temprature
#define CPURemoteOVTCmd	0x19	// HW shutdown command 
#define CPULocalOVTCmd	0x20	// HW shutdown command

#define CPU_Local_OVT	80      // Set HW shutdown point of CPU local temperature            
#define CPU_Remote_OVT	106     // Set HW shutdown point of CPU remote temperature  
#define VGA_Local_OVT	85      // Set HW shutdown point of VGA local temperature  
#define VGA_Remote_OVT	106     // Set HW shutdown point of VGA remote temperature 
#define dummy_data	0x00
#endif
//981004-100414-R-E


extern void bGetThermalData(void);
extern void vFanControl (void);
extern void vFanControl2 (void); //981004-170419-A                                                       
extern void vFanCustomize(void); //981004-150722-A
extern void vMoniterTemprature(void);
extern void vCheckAlertStatus(void);
//140587-161202-A-S
extern void fanfunc_run(void);
extern void fanfunc_SET(BYTE, BYTE ,BYTE  );
extern void fanfunc_READ(BYTE );
extern void tSetDefault(void);
//140587-161202-A-E
//-----------------------------------------------------------------------------
// Define Smbus device address
//-----------------------------------------------------------------------------
#define ThermalAddr	        0x98	// thermal sensor address
#define PCH_Address         0x96    // PCH address


//-----------------------------------------------------------------------------
// Define PCH Command
//-----------------------------------------------------------------------------
#define RPCHDAT	        0x40	// Read block data (20 Byte)
#define WSTS	        0x41	// Write STS registers (6 Bytes)
#define WCPULIMIT	    0x42	// Write CPU temperature limit (4 Bytes)
#define WMCHLIMIT	    0x43	// Write MCH temperature limit (2 Bytes)
#define WPCHLIMIT	    0x44	// Write PCH temperature limit (2 Bytes)
#define WDIMMLIMIT	    0x45	// Write Memory temperature limit (2 Bytes)
#define WCPUPOWER	    0x50	// Write CPU power clamp(2 Bytes) 

//-----------------------------------------------------------------------------
// Define thermal sensor commands
//-----------------------------------------------------------------------------
#define LocalCmd		    0x00	// Read Local temprature
#define RemoteCmd	        0x01	// Read remote temprature
#define ReadStatsuCmd       0x02	// Read thermal status

#define CPURemoteOVTCmd	    0x19	// HW shutdown command 
#define CPULocalOVTCmd	    0x20	// HW shutdown command
#define CPURACmd            0x0D    // Stores the integer portion of the high limit for the External Diode
#define CPULACmd            0x0B    // Stores the 8-bit high limit for the Internal Diode
#define CPURALCmd           0x0E    // Stores the integer portion of the low limit for the External Diode
#define CPULALCmd           0x0C    // Stores the 8-bit low limit for the Internal Diode
#define ManifactorID        0xFE

#define Configuration       0x09
#define ThermHysteresis     0x21
#define ConsecutiveAlert    0x22
#define DiodeFactor         0x27
#define DiodeFactor2        0x28
#define FilterControl       0x40
#define AlertConfig         0xBF

//-----------------------------------------------------------------------------
// For SMSC thermal sensor setting
//-----------------------------------------------------------------------------
#define SMSC_ID             0x5D
#define SMSC_CPU_Local_OVT  0x78            
#define SMSC_CPU_Remote_OVT 0x78   
#define SMSC_CPURAValue     0x78    
#define SMSC_CPULAValue     0x5A   

#define GMT_ID              0x47
#define GMT_CPU_Local_OVT   0x78          
#define GMT_CPU_Remote_OVT  0x78  
#define GMT_CPURAValue      0x78
#define GMT_CPULAValue      0x5A
#define GMT_CPURALValue     0xC9
#define GMT_CPULALValue     0xC9

#define NS_ID               0x01
#define NS_CPU_Local_OVT    0x78            
#define NS_CPU_Remote_OVT   0x78   
#define NS_CPURAValue       0x78
#define NS_CPULAValue       0x5A
#define NS_CPURALValue      0xC9
#define NS_CPULALValue      0xC9

//-----------------------------------------------------------------------------
// PCH Thermal Command
//-----------------------------------------------------------------------------
#define WriteSTSPreferences 0x41
#define WriteCPUTempLimits  0x42
#define WriteMCHTempLimits  0x43
#define WritePCHTempLimits  0x44
#define WriteDIMMTempLimits 0x45
#define WriteMPCCPUPowerClamp   0x50
#define PCHBlockRead        0x40

//-----------------------------------------------------------------------------
// Fan control define
//-----------------------------------------------------------------------------
#define FanValue		    Fan_volt    // The register of voltage output. (DAC or PWM)
#define FanInitValue	    160
#define	MaxOutValue		    240
#define FullOnCounter	    20		    // time base 100ms
#define RPMACC			    100		    // +- 100 rpm ACC
#define RPM1Max			    7000	    // rpm max value for softwave filter
#define RPM2Max			    7000	    // rpm2 max value for softwave filter //981004-140813-A

//-----------------------------------------------------------------------------
// Compute R.P.M to TACH value
//-----------------------------------------------------------------------------
//	Fan Speed(R.P.M) = 60 /((1/Fs) * Tach * P )
//	Fs = FreqEC(9.2MHz) / 128
//	P denotes the numbers of square pulses per revolution.
//	(60 * 9.2M/128  = 4312500
//-----------------------------------------------------------------------------
#define TACH1P		        2			// the numbers of square pulses per revolution.
#define TACH2P		        2			// the numbers of square pulses per revolution.

//-----------------------------------------------------------------------------
// Moniter temperature
//-----------------------------------------------------------------------------
//#define CpuTooHot 		    110
//#define CpuTooHotTimes 	    3
//#define SysTooHot		    80
//#define SysTooHotTimes	    20

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void GetThermalData(void);
extern void FanControl (void);
extern void MoniterTemprature(void);
extern void InitThermalChip(void);
extern void ReadThermalID(void);
extern void FanFullOn(void);
extern void FanFullOff(void);
extern void FanInitOn(void);
extern void GetRPM1(void);
extern void GetRPM2(void);
extern void GetRPM3(void); //981004-231002-A
extern void GetRPM4(void); //981004-231002-A
extern void GetRPM5(void); //981004-231002-A
extern void InitThermalTable1(void);
extern void InitThermalTable2(void);
extern void CheckFanRPM1(void);
extern void CheckFanRPM2(void);
extern void FanManager(void);
extern void ReadCPUTemp(void);
extern void ReadSysTemp(void);

//-----------------------------------------------------------------------------
// Structure define
//-----------------------------------------------------------------------------
//981004-170418-R-S
#if 0
typedef struct thermal2struct
{
	BYTE 	Level;
	BYTE 	CFanOn;
	BYTE 	CFanOff;
	BYTE	CRPM;
	XBYTE	*FanOn;
	XBYTE	*FanOff;
	XBYTE	*RPM;
}thermal2;
#endif
//981004-170418-R-E

typedef	struct	TooHotStruct
{
	XBYTE	*Temprature;
	BYTE	Limit;
	XBYTE	*Counter;
	BYTE	Times;
}sTooHot;

typedef struct ThermalInitTablt
{
	BYTE	cmd	;	        // thermal init. command
	BYTE	value	;       // value of command	
	BYTE	RorW	;       // 0: read byte, 1: write byte
} sThermalInitTablt;

extern sThermalInitTablt code asThermalInitTablt[];

#define DCR0 PWM0->DUTY
#define DCR1 PWM1->DUTY
#define DCR2 PWM2->DUTY
#define DCR3 PWM3->DUTY
#define DCR4 PWM4->DUTY
#define DCR5 PWM5->DUTY
#define DCR6 PWM6->DUTY
#define DCR7 PWM7->DUTY
