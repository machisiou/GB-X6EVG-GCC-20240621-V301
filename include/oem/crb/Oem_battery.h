/**
 * @file Oem_battery.h
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief
 * @version 0.1
 * @date 2024-03-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "annotation.h"

#define SHOWTIME        0x10
//981004-121221-A-S
#define CAP0    0  
#define CRITICAL_TEMPER    3130  //(0x0C3A , 40 Celsius degree , C=K+273) 
#define PSTATE1_TEMPER     3180  //(0x0C6C , 45 Celsius degree , C=K+273) //981004-140505-M from 3180
#define PSTATE2_TEMPER     3230  //(0x0CD0 , 50 Celsius degree , C=K+273) //981004-140505-M from 3230
#define ProcsH_LTEMPER     3230  //(50 degree) //981004-131030-A MAX
#define ProcsH_HTEMPER     3280  //(55 degree) //981004-131030-A MAX
#define LOW_TEMPER	       2880  //(0x0B40 , 15 Celsius degree , C=K+273) //981004-180301-M from 2830 
#define HIGH_TEMPER	       3180  //(0x0C6C , 45 Celsius degree , C=K+273) //981004-181107-M from 3230
#define BAT_HIGH_CURRENT1  9700  //(0x2328 , 9.7 AMP) 
#define BAT_LOW_CURRENT1   8500  //(0x1D4C , 8.5 AMP) 
#define BAT_LOW_CURRENT2   8000  //(0x1770 , 8.0 AMP)
#define BAT_HIGH_CURRENT2  7700  //(0x1E14 , 7.7 AMP) //981004-130819-M from 9000
#define BAT_LOW_CURRENT3   6000  //(0x1770 , 6.0 AMP) //981004-130819-M from 8000 
#define BAT_LOW_CURRENT4   6500  //(0x1964 , 6.5 AMP) //981004-130819-M from 7500    
//981004-121221-A-E

//-------------------------------------------------------------------------------
// Battery in ADC rang
//-------------------------------------------------------------------------------
//#define BAT_IN_H			    827     // high
//#define BAT_IN_L			    168     // low

//-----------------------------------------------------------------
// Define SMBus device address
//-------------------------------------------- --------------------
#define SmBat_Addr          0x16        // smart battery address
#define Charger_Addr        0x12        // charger address

//-----------------------------------------------------------------
// Define smart battery command
//-------------------------------------------- --------------------
#define C_access            0x00  	// manufacture access
#define C_RCalarm           0x01 	// remaining capacity alarm
#define C_RTalarm           0x02   	// remaining time alarm
#define C_mode              0x03  	// battery mode
#define C_AtRate            0x04   	// AtRate
#define C_AtRateFull        0x05  	// AtRate time to full
#define C_AtRateEmpty       0x06  	// AtRate time to empty
#define C_AtRateOK          0x07   	// AtRate OK
#define C_temp              0x08   	// temperature
#define C_volt              0x09   	// voltage
#define C_current           0x0A   	// current
#define C_AVcurrent         0x0B   	// average current
#define C_MaxError          0x0C  	// maximum error
#define C_RSOC              0x0D  	// relative state of charge
#define C_ASOC              0x0E   	// absolute state of charge
#define C_RMcap             0x0F   	// remaining capacity
#define C_FCcap             0x10   	// full charge capacity
#define C_RunTimeEmpty      0x11 	// run time to empty
#define C_AVTimeEmpty       0x12  	// average time to empty
#define C_AVTimeFull        0x13   	// average time to full
#define C_ChargingCurrent   0x14  	// charging current
#define C_ChargingVoltage   0x15   	// charging voltage
#define C_BatStatus         0x16   	// battery status
#define C_CycleCount        0x17   	// cycle count
#define C_DCap              0x18   	// design capacity
#define C_DVolt             0x19   	// design voltage
#define C_Spec              0x1A 	// spec information
#define C_Date              0x1B   	// manufacture date
#define C_SerialNo          0x1C   	// serial number
#define C_Mname             0x20 	// manufacturer name
#define C_Dname             0x21  	// device name
#define C_Dchem             0x22  	// device chemistry
#define C_Mdata             0x23 	// manufacture data

#if 0
//-----------------------------------------------------------------
// Define charger command
//-------------------------------------------- --------------------
#define C_ChargeCurrent     0x14        // Set charge curretn
#define C_ChargeVoltage     0x15        // Set charge voltage
#define C_InputCurrent      0x3F        // Set input current	
#define C_MFID              0xFE        // Get Manufacturer ID
#define C_DeviceID          0xFF        // Get device ID
#define ChargeDeviceID      0x08
#define ChargeMFID          0x4D
#endif

//-----------------------------------------------------------------
// Charge and discharge charger rules
//-----------------------------------------------------------------
#define ChangeChgBattery    0x82
#define ChangeDischgBattery 0x20
#define ABatteryLow         0x05
#define BBatteryLow         0x05
#define ACriticalLow        0x02
#define BCriticalLow        0x02
#define AOverVoltage        13400
#define BOverVoltage        13400
#define TrickleThreshold    0x1960   //trickle charge under 6.5V
#define DebounceTime        0x05

//-------------------------------------------------------------------------------
// Define SMBus device address and channel
//-------------------------------------------------------------------------------
#define SmartBat_Addr	        0x16    // Smart battery address
#define Charger_Addr		    0x12    // Smart charger address
#define SmartBatChannel         SMbusCh1
#define SmartChargerChannel     SMbusCh1

//981004-220808-A-S //NCT7601Y
#define Thermal1_Addr	        0x3A    // Thermal IC NCT760X address
#define Thermal2_Addr	        0x3C    // Thermal IC NCT760X address
#define Thermal1_TR1	        0x00    // Thermal IC NCT760X reading TR1
#define Thermal1_TR2	        0x01    // Thermal IC NCT760X reading TR2
#define Thermal1_TR3	        0x02    // Thermal IC NCT760X reading TR3 //981004-221123-A
#define Thermal1_TR4	        0x03    // Thermal IC NCT760X reading TR4 //981004-221123-A
#define Thermal1_TR5	        0x04    // Thermal IC NCT760X reading TR5
#define Thermal1_TR6	        0x05    // Thermal IC NCT760X reading TR6
#define Thermal1_TR8	        0x07    // Thermal IC NCT760X reading TR8 //981004-221123-A
#define Thermal1_Read	        0x0F    // Thermal IC NCT760X reading All
#define Thermal1_Config	        0x10    // Thermal IC NCT760X Configure
#define Thermal1_ADV_Config     0x11    // Thermal IC NCT760X Advanced Configuration
#define Thermal1_CH1_Enable     0x13    // Thermal IC NCT760X Channel 1 ENABLE
#define Thermal1_SMBUS_RW       0xFC    // SMBUS address reading
#define Thermal1_CHIPID         0xFD    // SMBUS CHIP ID
#define Thermal1_VENDORID       0xFE    // SMBUS Vendor ID
#define Thermal1_DEVICEID       0xFF    // SMBUS Device ID
//981004-220808-A-E

//-------------------------------------------------------------------------------
// Define smart battery command
//-------------------------------------------------------------------------------
#define BATCmd_access           0x00  	// manufacture access
#define BATCmd_RCalarm          0x01 	// remaining capacity alarm
#define BATCmd_RTalarm          0x02   	// remaining time alarm
#define BATCmd_mode             0x03  	// battery mode
#define BATCmd_AtRate           0x04   	// AtRate
#define BATCmd_AtRateFull       0x05  	// AtRate time to full
#define BATCmd_AtRateEmpty      0x06  	// AtRate time to empty
#define BATCmd_AtRateOK         0x07   	// AtRate OK
#define BATCmd_Temp             0x08   	// temperature
#define BATCmd_Volt             0x09   	// voltage
#define BATCmd_Current          0x0A   	// current
#define BATCmd_AVcurrent        0x0B   	// average current
#define BATCmd_MaxError         0x0C  	// maximum error
#define BATCmd_RSOC             0x0D  	// relative state of charge
#define BATCmd_ASOC             0x0E   	// absolute state of charge
#define BATCmd_RMcap            0x0F   	// remaining capacity
#define BATCmd_FCcap            0x10   	// full charge capacity
#define BATCmd_RunTimeEmpty     0x11 	// run time to empty
#define BATCmd_AVTimeEmpty      0x12  	// average time to empty
#define BATCmd_AVTimeFull       0x13   	// average time to full
#define BATCmd_CC               0x14  	// charging current
#define BATCmd_CV               0x15   	// charging voltage
#define BATCmd_BatStatus        0x16   	// battery status
#define BATCmd_CycleCount       0x17   	// cycle count
#define BATCmd_DCap             0x18   	// design capacity
#define BATCmd_DVolt            0x19   	// design voltage
#define BATCmd_Spec             0x1A 	// spec information
#define BATCmd_Date             0x1B   	// manufacture date
#define BATCmd_SerialNo         0x1C   	// serial number
#define BATCmd_Mname            0x20 	// manufacturer name
#define BATCmd_Dname            0x21  	// device name
#define BATCmd_Dchem            0x22  	// device chemistry
#define BATCmd_Mdata            0x23 	// manufacture data
#define BATCmd_CV4              0x3C 	// Cell Voltage 4 //981004-160822-A
#define BATCmd_CV3              0x3D 	// Cell Voltage 3 //981004-160822-A
#define BATCmd_CV2              0x3E 	// Cell Voltage 2 //981004-160822-A
#define BATCmd_CV1              0x3F 	// Cell Voltage 1 //981004-160822-A 

//-------------------------------------------------------------------------------
// Define smart charger command (BQ24780S)
//-------------------------------------------------------------------------------
#define CHGCmd_Option           0x12 
#define CHGCmd_Option2          0x3B 
#define CHGCmd_Option3          0x37 //981004-220824-R //bq24780 not support 0x37h command
#define CHGCmd_Voltage          0x15
#define CHGCmd_ChgCurr          0x14
#define CHGCmd_InCurr           0x3F
#define CHGCmd_Ctrl             0x44
#define CHGCmd_Sts              0xFF
// Charge and discharge control step define
//-------------------------------------------------------------------------------
#define BAT_Step_ID	            0x01    // Identify main battery
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define BATID_Step_GetDV        0x01    // First time to get battery design voltage and checking SMBus communication is OK
#define BATID_Step_Auth         0x02    // Battery Authentication if necessary
#define BATID_Step_MFName       0x03    // Get manufacturer name and checking battery is supported
#define BATID_Step_FirstData    0x04    // Polling first data

#define BATID_Step_InitOK       0x05    // Init_OK,prepare Discharge/Pre-Charge. (always at last step)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define BAT_Step_WC			    0x02    // Battery wake up charge
#define BAT_Step_PC		        0x03    // Battery pre-charge
#define BAT_Step_NC		        0x04    // Battery normal charge
#define BAT_Step_DC			    0x05    // Battery discharge

#define BAT_Step_FullyChg       0x10    // Battery fully charged
#define BAT_Step_FullyDisChg    0x11    // Battery fully discharged

#define BAT_Step_SetFail        0x20    // Battery will fail
#define BAT_Step_Fail		    0x21    // Battery abnormal

#define BAT_Step_ForceDC        0x30    // Battery force discharge
#define BAT_Step_ForceC         0x31    // Battery force charge
#define BAT_Step_AutoLN         0x32    // Battery auot learning

#define BAT_Step_ChargerFail    0x40    // Smart charger abnormal

#define BAT_Step_Out		    0x50    // Battery plug out

//-------------------------------------------------------------------------------
// Define smart charger command
//-------------------------------------------------------------------------------
#define C_ChargeCurrent 	    0x14    // Set charge current
#define C_ChargeVoltage		    0x15    // Set charge voltage
#define C_InputCurrent		    0x3F    // Set input current	
#define C_MFID				    0xFE	// Get Manufacturer ID
#define C_DeviceID			    0xFF	// Get device ID

#define ChargeDeviceID		    0x0008
#define ChargeMFID			    0x004D

//-------------------------------------------------------------------------------
// Smart charger
//-------------------------------------------------------------------------------
#define SC_Current_Sense        1

#define BAT1_VOLT_WUCHG         8400
#define BAT1_CURR_WUCHG	        (128*SC_Current_Sense)

#define BAT1_VOLT_PRECHG        (4200*BAT1_S_Number)
#define BAT1_CURR_PRECHG        (256*SC_Current_Sense)

#define Bat1_PC2NC_Cap          256    

#define I_20W   			    (1024/2)
#define I_25W                   (1280/2)
#define I_30W				    (1536/2)
#define I_45W   			    (2048/2)
#define I_65W   			    (3072/2)
#define I_90W   			    (4096/2)
#define I_130W  			    (6144/2)
#define I_150W  			    (7168/2)
#define InputCurrent            I_65W

//-------------------------------------------------------------------------------
// Main battery protect
//-------------------------------------------------------------------------------
#define BAT1_Low			    10      // RSOC 10%
#define BAT2_Low			    10      // RSOC 10%

#define BAT1_CriticalLow	    3       // RSOC 3%
#define BAT2_CriticalLow	    3       // RSOC 3%

#define BATOverVoltage		    (4400*BAT1_S_Number)

#define ChargerSettingTimeOut   3       // re-try counter of setting of smart charger
#define BatIDTimeOut            5       // battery 1 identify re-try counter
#define BatWCTimeOut            60      // timer base is 1min (1hr)
#define BatPCTimeOut            120     // timer base is 1min (2hr)
#define BatNCTimeOut            480     // timer base is 1min (8hr)

#define BatOVTimeOut            5       // Main battery over voltage 5sec
#define BatOTTimeOut            5       // Main battery over temperature

//-------------------------------------------------------------------------------
// Battery Fail cause
//-------------------------------------------------------------------------------
#define Bat_WakeUpChargeFail    0x01
#define Bat_PreChargeFail       0x02
#define Bat_NormalChargeFail    0x03
#define Bat_Weak                0x04
#define Bat_OverVoltage         0x05
#define Bat_OverTemperature     0x06
#define Bat_NoSupport           0x07
#define Bat_AuthFail            0x08

//-------------------------------------------------------------------------------
// Battery Stop charge cause
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// Functions prototype
//-------------------------------------------------------------------------------
extern void Battey1ControlCenter(void);
extern void SetBAT1CtrlStep(uint8_t ctrlstep);
extern void BAT1IdentifyNextStep(void);
extern void SetBAT1IDTimeOutCNT(void);
extern void BAT1_SetFail(uint8_t failcause);
extern void BAT1_PlugOutClrVariables(void);
extern void Hook_BAT1_ChargePinON(uint8_t on_off);
extern uint8_t DisableCharger(void);
extern uint8_t SetSmartCharger(void);
extern void PollingBatteryData(void);
extern void ProcessDischarge(void);
extern void ProcessCharge(void);
extern void ConfigBatIn(void);
extern void ConfigBatOut(void);
extern void ConfigCharger(void);
extern void ConfigACLIMIT(void); //981004-230707-A
extern float Smartcharge(uint8_t Charge); //981004-121221-A from return BYTE
//extern BYTE OEM_ShowRmCap(void); //981004-180731-R
extern float Check_FCC_Ratio1(void); 
extern void CheckChargerSetting(void); //981004-180104-A
extern void SetBatCHGCurrent(void); //981004-220510-A
extern void SetBatCHGVoltage(void); //981004-220510-A
extern void NV_DB20_SUPPORT(void); //981004-221228-A
extern void FCC_PERCENTAGE(void); //981004-230510-A
extern void Fix_Battery_Abnormal(void);
extern uint8_t BAT_CUSTOMIZE_CHECK(int sel_item);
extern void BAT_STD_CHECK(void);
extern void BatLfcCapCal(void);
typedef struct batINFO
{
	//uint8_t DeviceNO;
	//uint8_t DeviceName[12];
	  uint16_t BatID;
    uint16_t ChgVoltage;
    uint16_t ChgCurrent;
    uint16_t InCurrent;
}sbatINFO;

typedef struct batFirstData
{
	uint8_t Cmd;
	uint8_t *Var;
}sbatFirstData;