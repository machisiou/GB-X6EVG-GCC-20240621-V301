#ifndef __MEM_H__
#define __MEM_H__

#include <stdint.h>
#include "system/Type.h"

#define ACPI_AREA	__attribute__((section(".acpi_sram")))
#define KERNEL_AREA	__attribute__((section(".kernel_sram")))

extern uint8_t   ITempB01;
extern uint8_t   ITempB02;
extern uint8_t   ITempB03;
extern uint8_t   ITempB04;
extern uint8_t   ITempB05;
extern uint8_t   ITempB06;
extern uint16_t  ITempW01;
extern uint16_t  ITempW02;
extern uint8_t   debug0;
extern uint8_t debug1;
extern uint8_t debug2;
extern uint8_t debug3;
extern uint32_t debug32_0;
extern uint32_t debug32_1;
extern uint8_t BAT_TX_BUF[4];
extern uint8_t BAT_RX_BUF[4];
extern uint8_t Pre_P80, Pre_P81;
extern uint8_t __attribute__ ((aligned(4))) OOB_TX_BUF[32];
extern uint8_t __attribute__ ((aligned(4))) OOB_RX_BUF[32];
extern uint8_t WaitBack;
extern uint8_t OOBNum;

#define ECOEMRAM1			0x20050100
#define ECRAM				0x20050200
#define OEMRAM3				0x20050300
#define OEMRAM4				0x20050400
#define OEMRAM5				0x20050500
#define OEMRAM8				0x20050800
#define OEMRAM9				0x20050900
#define OEMRAMA				0x20050A00
#define OEMRAMB				0x20050B00
#define OEMRAMC				0x20050C00
#define OEMRAMD				0x20050D00

#define KERNEL_DEBUG_RAM	0x20055000
#define DebugPtr			(*((uint16_t *)(KERNEL_DEBUG_RAM-1)))
#define DebugPage			((uint8_t*)(KERNEL_DEBUG_RAM))

#define SYSTEM_G3		0x99
#define SYSTEM_S5		0x05
///#define SYSTEM_S4		0x04
///#define SYSTEM_S3		0x03
///#define SYSTEM_S0		0x00
#define SYSTEM_G3S5		0x95
#define SYSTEM_S5S0		0x50
#define SYSTEM_S0S5		0x55
#define SYSTEM_S0S3		0x35
#define SYSTEM_S3S0		0x30

extern KERNEL_AREA uint32_t TimeSlot;
#define Time_Slot_1ms		BIT0
#define Time_Slot_5ms		BIT1
#define Time_Slot_10msA		BIT2
#define Time_Slot_10msB		BIT3
#define Time_Slot_50msA		BIT4
#define Time_Slot_50msB		BIT5
#define Time_Slot_100msA	BIT6
#define Time_Slot_100msB	BIT7
#define Time_Slot_100msC	BIT8
#define Time_Slot_500msA	BIT9
#define Time_Slot_500msB	BIT10
#define Time_Slot_1SA		BIT11
#define Time_Slot_1SB		BIT12
#define Time_Slot_1min		BIT13

extern KERNEL_AREA uint32_t SERVICEflag;
#define SERVICE_F_ERPMC		0x80000000
#define SERVICE_F_PMACPI	0x40000000
#define SERVICE_F_PMKBC		0x20000000
#define SERVICE_F_PMIO0		0x10000000
#define SERVICE_F_PMIO1		0x08000000
#define SERVICE_F_SENDKEY	0x04000000
#define SERVICE_F_PS2		0x02000000
#define SERVICE_F_SCANKEY	0x01000000
#define SERVICE_F_1ms		0x00800000
#define SERVICE_F_PMIO2		0x00400000
#define SERVICE_F_PMIO3		0x00200000
#define SERVICE_F_OEM1		0x00000000

extern KERNEL_AREA uint8_t ECtime10;
extern KERNEL_AREA uint8_t ECtime100;
extern KERNEL_AREA uint16_t ECtime1000;
extern KERNEL_AREA uint16_t ECtime1M;
extern KERNEL_AREA uint16_t ECtime33m;

extern KERNEL_AREA uint8_t FnCnt;
extern KERNEL_AREA uint8_t NumLockCnt;
extern KERNEL_AREA uint8_t KBValidDebounceCnt;
extern KERNEL_AREA uint8_t KeyPress;
extern KERNEL_AREA uint8_t SentKeyCnt;
extern KERNEL_AREA uint8_t ScanIntrvl;
extern KERNEL_AREA uint16_t KBDelayCnt;
extern KERNEL_AREA uint16_t KBRepetCnt;
extern KERNEL_AREA uint32_t KSIData;

extern KERNEL_AREA uint8_t KbcDLen;
extern KERNEL_AREA uint8_t KbcCmd;
extern KERNEL_AREA uint8_t KbcData;
extern KERNEL_AREA uint8_t KbdCmd;

extern KERNEL_AREA uint8_t AcpiDLen;
extern KERNEL_AREA uint8_t AcpiCmd;
extern KERNEL_AREA uint8_t AcpiData;
extern KERNEL_AREA uint8_t AcpiData2;

extern KERNEL_AREA uint8_t pm0len;
extern KERNEL_AREA uint8_t pm0cmd;
extern KERNEL_AREA uint8_t pm0dat;

extern KERNEL_AREA uint8_t pm1len;
extern KERNEL_AREA uint8_t pm1cmd;
extern KERNEL_AREA uint8_t pm1dat;

extern KERNEL_AREA uint8_t pm2len;
extern KERNEL_AREA uint8_t pm2cmd;
extern KERNEL_AREA uint8_t pm2dat;

extern KERNEL_AREA uint8_t pm3len;
extern KERNEL_AREA uint8_t pm3cmd;
extern KERNEL_AREA uint8_t pm3dat;

extern KERNEL_AREA uint8_t KBDataQueueHead;
extern KERNEL_AREA uint8_t KBDataQueueTail;
extern KERNEL_AREA uint8_t KBDataQueue[];
#define KBDQUEUELEN		0x10

extern KERNEL_AREA uint8_t SCIDataQueueHead;
extern KERNEL_AREA uint8_t SCIDataQueueTail;
extern KERNEL_AREA uint8_t SCIDataQueue[];
#define SCIDQLEN		0x10

extern KERNEL_AREA uint8_t Main_MOUSE_CHN;
extern KERNEL_AREA uint8_t Pass_On;
extern KERNEL_AREA uint8_t Pass_Off;
extern KERNEL_AREA uint8_t Pass_Make1;
extern KERNEL_AREA uint8_t Pass_Make2;
extern KERNEL_AREA uint8_t Pass_Buff_Idx;

extern KERNEL_AREA uint8_t MSPending;
extern KERNEL_AREA uint8_t MS_ID_CUNT;
extern KERNEL_AREA uint8_t TPACKCounter;
extern KERNEL_AREA uint8_t TPResolution;
extern KERNEL_AREA uint8_t TPSamplingRate;
extern KERNEL_AREA uint8_t AUXPortNum;

extern KERNEL_AREA uint8_t Manual;
extern KERNEL_AREA uint8_t Temp_Load;
extern KERNEL_AREA uint8_t Pass_Buff[8];

extern KERNEL_AREA uint8_t KCCB42;
#define Ccb42_INTR_KEY			BIT0
#define Ccb42_INTR_AUX			BIT1
#define Ccb42_SYS_FLAG			BIT2
#define Ccb42_RV01				BIT3
#define Ccb42_DISAB_KEY 		BIT4
#define Ccb42_DISAB_AUX 		BIT5
#define Ccb42_XLATE_PC			BIT6
#define Ccb42_RV02				BIT7

extern KERNEL_AREA uint8_t KBCodeSet;
extern KERNEL_AREA uint8_t KBTypematic;

extern KERNEL_AREA uint8_t MULPX;
#define EnableTP 				BIT0
#define MULPX_RV00				BIT1
#define MULPX_RV01				BIT2
#define MULPX_Multiplex 		BIT3
#define MULPX_RV02				BIT4
#define MULPX_RV03				BIT5
#define MULPX_RV04				BIT6
#define MULPX_RV05				BIT7

extern KERNEL_AREA uint8_t KBFlag;
#define SCAN_INH 				BIT0
#define KBFlag_RV00		 		BIT1
#define PASS_READY 				BIT2
#define KBFlag_RV01 			BIT3
#define KBFlag_RV02 			BIT4
#define KBFlag_RV03 			BIT5
#define KBFlag_RV04 			BIT6
#define KBFlag_RV05 			BIT7

extern KERNEL_AREA uint8_t CustomFlags;
#define ECCheckBurstMode		BIT0
#define ACPI_Mode				BIT1
#define CustomFlags_RV01		BIT2
#define FastA20 				BIT3
#define CustomFlags_RV02		BIT4
#define CustomFlags_RV03		BIT5
#define CustomFlags_RV04		BIT6
#define CustomFlags_RV05		BIT7

extern KERNEL_AREA uint8_t Led_Datas;
#define Led_Data_RV00			BIT0
#define Led_Data_RV01			BIT1
#define Led_Data_RV02			BIT2
#define Led_Data_RV03			BIT3
#define Led_Data_RV04			BIT4
#define Led_Data_RV05			BIT5
#define Led_Data_RV06			BIT6
#define Led_Data_RV07			BIT7

extern KERNEL_AREA uint8_t Gen_Info;
#define Gen_Info_RV00			BIT0
#define Gen_Info_RV01			BIT1
#define Gen_Info_RV02			BIT2
#define Gen_Info_RV03			BIT3
#define Gen_Info_PASS_ENABLE	BIT4
#define Gen_Info_RV04			BIT5
#define Gen_Info_RV05			BIT6
#define Gen_Info_RV06			BIT7

extern KERNEL_AREA uint8_t AuxFlags[3];
#define DEVICE_IS_ATTACHED			BIT0
#define DEVICE_NEED_INIT			BIT1
#define DEVICE_MS_DRIVER_NO_MATCH	BIT2
#define DEVICE_NEED_CONFIG			BIT3
#define DEVICE_IS_MAIN_KB			BIT4
#define DEVICE_IS_MAIN_MOUSE		BIT5
#define DEVICE_IS_KEYBOARD			BIT6
#define DEVICE_IS_MOUSE				BIT7

extern KERNEL_AREA uint8_t AuxTestFlagS;
#define PS2StartBit					BIT0
#define MouseDriverIn				BIT1
#define KeyboardDriverIn			BIT2
#define AUX2ByteCommand				BIT3
#define AuxTestFlagS_RV1			BIT4
#define AuxTestFlagS_RV2			BIT5
#define AuxTestFlagS_RV3			BIT6
#define AuxTestFlagS_RV4			BIT7

extern KERNEL_AREA uint8_t VW_IDX4;
extern KERNEL_AREA uint8_t VW_IDX5;
extern KERNEL_AREA uint8_t VW_IDX6;
extern KERNEL_AREA uint8_t VW_IDX40;

extern KERNEL_AREA uint8_t eRPMCFlag;
extern KERNEL_AREA uint8_t eRPMCBuf;
extern KERNEL_AREA uint8_t eRPMC_tx;

extern KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_IN_BUF[256];
extern KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_IN_BUF_1[128];
extern KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_IN_EMPTY[128];
extern KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_OUT_BUF[256];

extern KERNEL_AREA uint8_t OOBNum;
extern KERNEL_AREA uint8_t RDPKGIdx;
extern unsigned int MCdata[4];

extern ACPI_AREA uint8_t ACPIReserved[256];			// 0x00
extern uint16_t CPUTemperature;
extern uint8_t CPUTjMax;
extern uint8_t CPUTDP6;
extern uint8_t CPUTDP7;
extern uint8_t OOBNum;

extern uint8_t BAT_bInfor_Count;
#define PTRDEFRAM 1
//extern uint8_t SystemState;
#define SYSTEM_G3		0x99
#define SYSTEM_S5		0x05
///#define SYSTEM_S4		0x04
///#define SYSTEM_S3		0x03
///#define SYSTEM_S0		0x00
#define SYSTEM_G3S5		0x95
#define SYSTEM_S5S0		0x50
#define SYSTEM_S0S5		0x55

extern uint8_t PwrSwDelay;
extern uint8_t PwrSequStep;
extern uint8_t PwrSequDly;
extern uint8_t RSTStatus;
// extern uint8_t BAT1VoltL;
// extern uint8_t BAT1VoltH;
// extern uint8_t BAT1RemainingCapaL;
// extern uint8_t BAT1RemainingCapaH;
// extern uint8_t BAT1FCCL;
// extern uint8_t BAT1FCCH;
// extern uint8_t BAT1ModeL;
// extern uint8_t BAT1ModeH;
// extern uint8_t BAT1StatusL;
// extern uint8_t BAT1StatusH;
// extern uint8_t BAT1CurrentL;
// extern uint8_t BAT1CurrentH;
// extern uint8_t BAT1DesignCapaL;
// extern uint8_t BAT1DesignCapaH;
// extern uint8_t BAT1DesignVoltL;
// extern uint8_t BAT1DesignVoltH;
extern uint16_t FAN_RPM;
// extern void RAM_debug(uint8_t num);
//extern uint8_t LED7s_TABLE[];
//extern uint8_t I2C_WR_BUFFER[];
//#define BAT_STATUS2			(*((uint8_t *)(ECRAM+0x0000)))

//-------------------------------------------------------------------------------
//	0x100-0x1FF   OEM RAM 1  
//-------------------------------------------------------------------------------
#ifdef ECPowerDownModeSupport
XBYTE g_ECPowerDownCurrentMode            _at_ (ECPowerDownCtrl+0x00);
XBYTE g_KernelDelayPowerDownMode          _at_ (ECPowerDownCtrl+0x01);
XBYTE g_ECPowerDownPeriodWakeUpTime       _at_ (ECPowerDownCtrl+0x02);
XWORD g_OEMDelayPowerDownMode             _at_ (ECPowerDownCtrl+0x03);
XBYTE g_ECPowerDownModeTest               _at_ (ECPowerDownCtrl+0x05);
#endif
#define SystemFlag1                      (*((uint8_t *)(OEMRAM1+0x17)))//  _at_ (OEMRAM1+0x17);
#define SMB_PRTC                         (*((uint8_t *)(OEMRAM1+0x18)))//  _at_ (OEMRAM1+0x18);  // EC SMB1 Protocol register
#define SMB_STS                          (*((uint8_t *)(OEMRAM1+0x19)))//  _at_ (OEMRAM1+0x19); 	// EC SMB1 Status register
#define SMB_ADDR                         (*((uint8_t *)(OEMRAM1+0x1A)))//  _at_ (OEMRAM1+0x1A); 	// EC SMB1 Address register
#define SMB_CMD                          (*((uint8_t *)(OEMRAM1+0x1B)))//  _at_ (OEMRAM1+0x1B); 	// EC SMB1 Command register
#define SMB_DATA                         (*((uint8_t *)(OEMRAM1+0x1C)))//  _at_ (OEMRAM1+0x1C); 	// EC SMB1 Data register array (32 bytes)
#define SMB_DATA1                        (*((uint8_t (*)[31])(OEMRAM1+0x1D)))//  _at_ (OEMRAM1+0x1D);
#define SMB_BCNT                         (*((uint8_t *)(OEMRAM1+0x3C)))//  _at_ (OEMRAM1+0x3C); 	// EC SMB1 Block Count register
#define SMB_ALRA                         (*((uint8_t *)(OEMRAM1+0x3D)))//  _at_ (OEMRAM1+0x3D); 	// EC SMB1 Alarm Address register
#define SMB_ALRD0                        (*((uint8_t *)(OEMRAM1+0x3E)))//  _at_ (OEMRAM1+0x3E); 	// EC SMB1 Alarm Data register 0
#define SMB_ALRD1                        (*((uint8_t *)(OEMRAM1+0x3F)))//  _at_ (OEMRAM1+0x3F); 	// EC SMB1 Alarm Data register 1
#define ADCC_MemBase                0x0140
#define wADC                             (*((uint16_t (*)[16])(ADCC_MemBase + 0x00))) //_at_ ADCC_MemBase + 0x00;
#define xADC                             (*((uint8_t (*)[8])(ADCC_MemBase + 0x10))) //_at_ ADCC_MemBase + 0x10;
#define xADC_ScanTimer                   (*((uint8_t *)(ADCC_MemBase + 0x18))) //_at_ ADCC_MemBase + 0x18;
#define xADC_Count                       (*((uint8_t *)(ADCC_MemBase + 0x19))) //_at_ ADCC_MemBase + 0x19;
#define xEC_T1_CNT                       (*((uint8_t *)(ADCC_MemBase + 0x1A))) //_at_ ADCC_MemBase + 0x1A;
#define xEC_T2_CNT                       (*((uint8_t *)(ADCC_MemBase + 0x1B))) //_at_ ADCC_MemBase + 0x1B;
#define xEC_T3_CNT                       (*((uint8_t *)(ADCC_MemBase + 0x1C))) //_at_ ADCC_MemBase + 0x1C;
#define DPTF_MemBase                 0x0160
#define xEC_T1_LoLimit                   (*((uint8_t *)(DPTF_MemBase + 0x00))) //_at_ DPTF_MemBase + 0x00;
#define xEC_T1_HiLimit                   (*((uint8_t *)(DPTF_MemBase + 0x01))) //_at_ DPTF_MemBase + 0x01;
#define xEC_T2_LoLimit                   (*((uint8_t *)(DPTF_MemBase + 0x02))) //_at_ DPTF_MemBase + 0x02;
#define xEC_T2_HiLimit                   (*((uint8_t *)(DPTF_MemBase + 0x03))) //_at_ DPTF_MemBase + 0x03;
#define xEC_T3_LoLimit                   (*((uint8_t *)(DPTF_MemBase + 0x04))) //_at_ DPTF_MemBase + 0x04;
#define xEC_T3_HiLimit                   (*((uint8_t *)(DPTF_MemBase + 0x05))) //_at_ DPTF_MemBase + 0x05;
#define xEC_T4_LoLimit                   (*((uint8_t *)(DPTF_MemBase + 0x06))) //_at_ DPTF_MemBase + 0x06; //BATT_T
#define xEC_T4_HiLimit                   (*((uint8_t *)(DPTF_MemBase + 0x07))) //_at_ DPTF_MemBase + 0x07; //BATT_T

#define xEC_T1_SendEvent                 (*((uint8_t *)(DPTF_MemBase + 0x08))) //_at_ DPTF_MemBase + 0x08;
#define xEC_T1_THR                       (*((uint8_t *)(DPTF_MemBase + 0x09))) //_at_ DPTF_MemBase + 0x09;
#define wEC_T1_THR_ACC                   (*((uint8_t *)(DPTF_MemBase + 0x0A))) //_at_ DPTF_MemBase + 0x0A;
#define xEC_CPUT_EventTimer              (*((uint8_t *)(DPTF_MemBase + 0x0C))) //_at_ DPTF_MemBase + 0x0C;
#define xEC_CPUT_SendEvent               (*((uint8_t *)(DPTF_MemBase + 0x0D))) //_at_ DPTF_MemBase + 0x0D;

#define xEC_CPUT_HiLimit                 (*((uint8_t *)(DPTF_MemBase + 0x0E))) //_at_ DPTF_MemBase + 0x0E;
#define xEC_CPUT_LoLimit                 (*((uint8_t *)(DPTF_MemBase + 0x0F))) //_at_ DPTF_MemBase + 0x0F;
#define xEC_T1_AVG                       (*((uint8_t *)(DPTF_MemBase + 0x10))) //_at_ DPTF_MemBase + 0x10;
#define xEC_T1_EventTimer                (*((uint8_t *)(DPTF_MemBase + 0x11))) //_at_ DPTF_MemBase + 0x11;
#define xEC_T2_AVG                       (*((uint8_t *)(DPTF_MemBase + 0x12))) //_at_ DPTF_MemBase + 0x12;
#define xEC_T2_EventTimer                (*((uint8_t *)(DPTF_MemBase + 0x13))) //_at_ DPTF_MemBase + 0x13;
#define xEC_T3_AVG                       (*((uint8_t *)(DPTF_MemBase + 0x14))) //_at_ DPTF_MemBase + 0x14;
#define xEC_T3_EventTimer                (*((uint8_t *)(DPTF_MemBase + 0x15))) //_at_ DPTF_MemBase + 0x15;
#define xEC_T4_AVG                       (*((uint8_t *)(DPTF_MemBase + 0x16))) //_at_ DPTF_MemBase + 0x16;
#define xEC_T4_SendEvent                 (*((uint8_t *)(DPTF_MemBase + 0x17))) //_at_ DPTF_MemBase + 0x17;
#define xEC_T2_SendEvent                 (*((uint8_t *)(DPTF_MemBase + 0x18))) //_at_ DPTF_MemBase + 0x18;
#define xEC_T2_THR                       (*((uint8_t *)(DPTF_MemBase + 0x19))) //_at_ DPTF_MemBase + 0x19;
#define wEC_T2_THR_ACC                   (*((uint16_t *)(DPTF_MemBase + 0x1A))) //_at_ DPTF_MemBase + 0x1A;
#define xEC_T3_SendEvent                 (*((uint8_t *)(DPTF_MemBase + 0x1C))) //_at_ DPTF_MemBase + 0x1C;
#define xEC_T3_THR                       (*((uint8_t *)(DPTF_MemBase + 0x1D))) //_at_ DPTF_MemBase + 0x1D;
#define wEC_T3_THR_ACC                   (*((uint16_t *)(DPTF_MemBase + 0x1E))) //_at_ DPTF_MemBase + 0x1E;

#if PTRDEFRAM == 1
#define BAT_STATUS			(*((uint8_t *)(ECRAM+0x0000)))
#define POWER_FLAG1			(*((uint8_t *)(ECRAM+0x0001)))
#define POWER_FLAG2			(*((uint8_t *)(ECRAM+0x0002)))
#define POWER_FLAG3			(*((uint8_t *)(ECRAM+0x0003)))
#define POWER_FLAG4			(*((uint8_t *)(ECRAM+0x0004)))
#define POWER_FLAG5			(*((uint8_t *)(ECRAM+0x0005)))
#define POWER_FLAG6			(*((uint8_t *)(ECRAM+0x0006)))
#define POWER_FLAG7			(*((uint8_t *)(ECRAM+0x0007)))
#define POWER_FLAG8			(*((uint8_t *)(ECRAM+0x0008)))
#define POWER_FLAG9			(*((uint8_t *)(ECRAM+0x0009)))
#define POWER_FLAG10		(*((uint8_t *)(ECRAM+0x000A)))
#define POWER_FLAG11		(*((uint8_t *)(ECRAM+0x000B)))
#define POWER_FLAG12			(*((uint8_t *)(ECRAM+0x000C)))
#define POWER_FLAG13			(*((uint8_t *)(ECRAM+0x000D)))
#define POWER_FLAG14			(*((uint8_t *)(ECRAM+0x000E)))
#define POWER_FLAG15			(*((uint8_t *)(ECRAM+0x000F)))
#define BAT_DSNCAP			(*((uint16_t *)(ECRAM+0x0010)))
#define BAT_LFCCAP			(*((uint16_t *)(ECRAM+0x0012)))
#define BAT_RMCAP			(*((uint16_t *)(ECRAM+0x0014)))
#define BAT_PRSNTVOL			(*((uint16_t *)(ECRAM+0x0016)))
#define BAT_DSNCAPWN			(*((uint16_t *)(ECRAM+0x0018)))
#define BAT_DSNCAPLW			(*((uint16_t *)(ECRAM+0x001A)))
#define BAT_GRANUL1			(*((uint16_t *)(ECRAM+0x001C)))
#define BAT_GRANUL2			(*((uint16_t *)(ECRAM+0x001E)))
#define BAT_DSNVTG			(*((uint16_t *)(ECRAM+0x0020)))
#define BAT_PRSNTRATE			(*((uint16_t *)(ECRAM+0x0022)))
#define BAT_TEMPER			(*((uint16_t *)(ECRAM+0x0024)))
#define BAT_PWRUNT			(*((uint8_t *)(ECRAM+0x0026)))
#define BAT_TECH			(*((uint8_t *)(ECRAM+0x0027)))
#define BAT_RMTIME			(*((uint16_t *)(ECRAM+0x0028)))
#define BAT_DEVNAME			(*((uint32_t *)(ECRAM+0x002A)))


#define GAUGE_CURRENT			(*((uint16_t *)(ECRAM+0x003C)))
#define GAUGE_VOLTAGE			(*((uint16_t *)(ECRAM+0x003E)))
#define BAT_SERIALNM1			(*((uint16_t *)(ECRAM+0x0040)))
#define BAT_SERIALNM2			(*((uint16_t *)(ECRAM+0x0042)))
#define BAT_NEWDEVNAME			(*((uint32_t *)(ECRAM+0x0044)))
#define BAT_CYCLECNT			(*((uint16_t *)(ECRAM+0x004E)))

#define BAT_TYPE1			(*((uint16_t *)(ECRAM+0x0050)))
#define BAT_TYPE2			(*((uint16_t *)(ECRAM+0x0052)))
#define NewLfcCap			(*((uint16_t *)(ECRAM+0x0054)))
#define New_DSNCAP			(*((uint16_t *)(ECRAM+0x0056)))
#define BAT_MODELNUM1			(*((uint16_t *)(ECRAM+0x0058)))
#define BAT_MODELNUM2			(*((uint16_t *)(ECRAM+0x005A)))
#define LFCCAP			(*((uint16_t *)(ECRAM+0x005C)))
#define RMCAP			(*((uint16_t *)(ECRAM+0x005E)))

#define PECI_CPU_temp			(*((uint8_t *)(ECRAM+0x0060)))
#define GPU_TMPR			(*((uint8_t *)(ECRAM+0x0061)))
#define FINAL_TEMP1			(*((uint8_t *)(ECRAM+0x0062)))
#define RELEASE_TYPE			(*((uint8_t *)(ECRAM+0x0063)))
#define FINAL_TEMP2			(*((uint8_t *)(ECRAM+0x0065)))
#define FanDACLevel			(*((uint8_t *)(ECRAM+0x0068)))
#define USB_CHARGE			(*((uint8_t *)(ECRAM+0x0069)))
#define BR_Level			(*((uint8_t *)(ECRAM+0x006A)))
#define X6LVH_EC_VER			(*((uint8_t *)(ECRAM+0x006B)))

#define BATMODE			(*((uint16_t *)(ECRAM+0x006C)))
#define RMCAP_TEMP			(*((uint16_t *)(ECRAM+0x006E)))

#define DSNCAPLW_TEMP			(*((uint16_t *)(ECRAM+0x0070)))
#define BATRATE_TEMP			(*((uint16_t *)(ECRAM+0x072)))
#define LFCCAP_TEMP			(*((uint16_t *)(ECRAM+0x0074)))
#define LFCCAP_TEMP2			(*((uint16_t *)(ECRAM+0x0076)))
#define TEMPER_TEMP			(*((uint16_t *)(ECRAM+0x0078)))
#define PRSNTRATE_TEMP			(*((uint16_t *)(ECRAM+0x007A)))
#define RMCAP_FIRST_CHK			(*((uint16_t *)(ECRAM+0x007C)))
#define RMCAP_FIRST_CHK2			(*((uint16_t *)(ECRAM+0x007E)))


#define BATCAP10			(*((uint16_t *)(ECRAM+0x0080)))
#define BATCAP20			(*((uint16_t *)(ECRAM+0x0082)))
#define BATCAP30			(*((uint16_t *)(ECRAM+0x0084)))
#define BATCAP40			(*((uint16_t *)(ECRAM+0x0086)))
#define BATCAP50			(*((uint16_t *)(ECRAM+0x0088)))
#define BATCAP95			(*((uint16_t *)(ECRAM+0x008A)))
#define LS_DATA_L			(*((uint8_t *)(ECRAM+0x008C)))
#define LS_DATA_M			(*((uint8_t *)(ECRAM+0x008D)))
#define LS_DATA_H			(*((uint8_t *)(ECRAM+0x0008E)))
#define LSCTRL			(*((uint8_t *)(ECRAM+0x008F)))

#define SCI_NUM			(*((uint8_t *)(ECRAM+0x0090)))
#define Fullchgcnt			(*((uint8_t *)(ECRAM+0x0091)))
#define BATCAP25			(*((uint16_t *)(ECRAM+0x0092)))
#define BATCAP97			(*((uint16_t *)(ECRAM+0x0094)))
//#define BATCAP99			(*((uint16_t *)(ECRAM+0x0096)))
#define BATCAP60			(*((uint16_t *)(ECRAM+0x0098)))
#define BATCAP80			(*((uint16_t *)(ECRAM+0x009A)))
#define TEMP_TR1			(*((uint8_t *)(ECRAM+0x009C)))
#define TEMP_TR2			(*((uint8_t *)(ECRAM+0x009D)))
#define TEMP_TR3			(*((uint8_t *)(ECRAM+0x009E)))
#define TEMP_TR4			(*((uint8_t *)(ECRAM+0x009F)))


#define SetFAN_LV			(*((uint8_t *)(ECRAM+0x00A0)))
#define FAN_ON			(*((uint8_t *)(ECRAM+0x00A1)))
#define FAN_DW			(*((uint8_t *)(ECRAM+0x00A2)))
#define ReadFAN_LV			(*((uint8_t *)(ECRAM+0x00A3)))
#define FAN_ONR			(*((uint8_t *)(ECRAM+0x00A4)))
#define FAN_DWR			(*((uint8_t *)(ECRAM+0x00A5)))
#define Ship_mode			(*((uint16_t *)(ECRAM+0x00A6)))
#define BAT_CHG_START			(*((uint8_t *)(ECRAM+0x00A8)))
#define BAT_CHG_END			(*((uint8_t *)(ECRAM+0x00A9)))
#define NCT7601_CH1_On			(*((uint8_t *)(ECRAM+0x00AA)))
#define NCT7601_Start			(*((uint8_t *)(ECRAM+0x00AB)))
#define TEMP_TR7			(*((uint8_t *)(ECRAM+0x00AC)))
#define TEMP_TR5			(*((uint8_t *)(ECRAM+0x00AD)))
#define TEMP_TR6			(*((uint8_t *)(ECRAM+0x00AE)))
#define TEMP_TR8			(*((uint8_t *)(ECRAM+0x00AF)))

#define FanRPM1			(*((uint8_t *)(ECRAM+0x00B0)))
#define FanRPM2			(*((uint8_t *)(ECRAM+0x00B1)))
#define CPU_DUTY			(*((uint8_t *)(ECRAM+0x00B3)))
#define GPU_DUTY			(*((uint8_t *)(ECRAM+0x00B4)))
#define AVG_ADC1			(*((uint8_t *)(ECRAM+0x00B6)))
#define AVG_ADC2			(*((uint8_t *)(ECRAM+0x00B7)))
#define xEC_CMDR			(*((uint8_t *)(ECRAM+0x00B8)))
#define PD_FW_Ver			(*((uint8_t *)(ECRAM+0x00B9)))
#define PD_FW_Ver2			(*((uint8_t *)(ECRAM+0x00BA)))
#define TI_FW_Ver			(*((uint8_t *)(ECRAM+0x00BB)))
#define TI_FW_Model			(*((uint8_t *)(ECRAM+0x00BC)))
#define PD_FW1			    (*((uint8_t *)(ECRAM+0x00BD)))
#define PD_FW2			    (*((uint8_t *)(ECRAM+0x00BE)))
#define NVSETPL1			(*((uint8_t *)(ECRAM+0x00BF)))

#define BAT_CHGVOL			(*((uint16_t *)(ECRAM+0x00C0)))
#define BAT_CHGCURR			(*((uint16_t *)(ECRAM+0x00C2)))
#define BAT_INCURR			(*((uint16_t *)(ECRAM+0x00C4)))
#define BAT_OPTION			(*((uint16_t *)(ECRAM+0x00C6)))
#define BAT_OPTION2			(*((uint16_t *)(ECRAM+0x00C8)))
#define BAT_OPTION3         (*((uint16_t *)(ECRAM+0x00CA)))
#define OLD_PRSNTRATE			(*((uint16_t *)(ECRAM+0x00CE)))

#define PRSNTRATE_TEMP2			(*((uint16_t *)(ECRAM+0x00D0)))
#define BAT_RMCAP3			(*((uint16_t *)(ECRAM+0x00D2)))
#define BAT100CNT			(*((uint8_t *)(ECRAM+0x00D4)))
#define EC_timer			(*((uint8_t *)(ECRAM+0x00D5)))
#define FANLVDNCNT			(*((uint8_t *)(ECRAM+0x00D6)))
#define KB_Level			(*((uint8_t *)(ECRAM+0x00D7)))
#define BAT_LFCCAP2			(*((uint16_t *)(ECRAM+0x00D8)))
#define Device_Exist			(*((uint8_t *)(ECRAM+0x00DA)))
#define patchACout			(*((uint8_t *)(ECRAM+0x00DB)))
#define FanLevelTemp			(*((uint8_t *)(ECRAM+0x00DC)))
#define FANLVDNCNT1			(*((uint8_t *)(ECRAM+0x00DD)))
#define RMCAP_TEMP2			(*((uint16_t *)(ECRAM+0x00DE)))

#define testW0			(*((uint16_t *)(ECRAM+0x00F0)))
#define testW1			(*((uint16_t *)(ECRAM+0x00F2)))
#define testW2			(*((uint16_t *)(ECRAM+0x00F4)))
#define FAN1_TEMP			(*((uint8_t *)(ECRAM+0x00F6)))
#define FAN2_TEMP			(*((uint8_t *)(ECRAM+0x00F7)))
#define RPM3			(*((uint16_t *)(ECRAM+0x00F8)))
#define RPM4			(*((uint16_t *)(ECRAM+0x00FA)))
#define RPM1			(*((uint16_t *)(ECRAM+0x00FC)))
#define RPM2			(*((uint16_t *)(ECRAM+0x00FE)))



//extern ACPI_AREA uint8_t BAT_STATUS;			// 0x00
#define DISCHARGE         	BIT0	      // 1 discharge
#define CHARGE            	BIT1        // 1 charge
#define CRITICAL          	BIT2	      // 1 capacity low (0x0084mAH)
#define BAT_IN            	BIT3        // 1 Battery plugged
//extern ACPI_AREA uint8_t POWER_FLAG1;				// 0x01
#define adapter_in      	BIT0        // AC adapter exist
#define power_on        	BIT1        // 1 system power on
#define enter_S3        	BIT2        // 1 host enter suspend to RAM mode
#define wait_PSW_off    	BIT3        // 1 waiting for PSW released              
#define enter_S4        	BIT4        // 1 host enter suspend to HD mode
#define dp_attached   	    BIT5        // 1 Device is monitor //981004-130517-A for Normal USB Port charge under S3 mode
#define ccd_on    	    	BIT6        // 1 enable CCD
#define bt_on           	BIT7   	    // 1 bluetooth on  
//extern ACPI_AREA uint8_t POWER_FLAG2;			// 0x02
#define SLP_S3_ON       	BIT0        // 1 not in S3 Status 
#define SLP_S4_ON       	BIT1        // 1 not in S4 Status 
#define fan_on          	BIT2        // 1 Fan on           
#define lid_open        	BIT3        // 1 OPEN           
#define sci_on          	BIT4        // 1 SCI enable       
#define thrt_on         	BIT5        // 1 throttole on     
#define wlan_on         	BIT6        // 1 WLAN on      
//#define VR_ON           	BIT7      // 1 VR ON 
#define LED_TEST_ON     	BIT7        // 1 //Test Battery LED (DCR2) and Power LED (DCR4) //981004-190109-M
//extern ACPI_AREA uint8_t POWER_FLAG3;				// 0x03
#define Trickle_Chg_ON     	BIT0 
#define power_on_patch     	BIT1 //981004-210401-A 
#define adapter_overtemp   	BIT2 //981004-201201-A
#define gc6_on              BIT3  
#define DDS_Pwm_off         BIT4   
//#define img_on 	       	    BIT4  
//#define ps2_on           	  BIT5
#define CLR_CMOS_SHUTDN     BIT5 //981004-220706-A
#define ship_mode          	BIT6 //981004-190116-A
#define ac_present         	BIT7 
//extern ACPI_AREA uint8_t POWER_FLAG4;			// 0x04
#define resume_from_s4      BIT0 
#define bat_custom_end      BIT1 
#define bat30_on            BIT2 
#define bat50_on            BIT3 
#define bat_cap_first_chk   BIT4 
#define bat_cap_downgrade   BIT5 
#define pstate_off          BIT6 
#define resume_from_s3      BIT7 
//extern ACPI_AREA uint8_t POWER_FLAG5;			// 0x05
#define bios_cf9            BIT0 
#define modern_stby         BIT1 //981004-200721-A
#define BIOS_reboot         BIT2 //981004-211102-A
#define BIOS_reboot2        BIT3
#define BIOS_flash          BIT4
#define bat_check           BIT5 
#define Linux_fanon         BIT6 //981004-200410-A
//extern ACPI_AREA uint8_t POWER_FLAG6;		// 0x06
//#define ECRAM_80patch       BIT0 //981004-190109-R
#define win_adapter_in      BIT0 // Report to OS for AC adapter or PD adapter //981004-210224-A
#define BIOS_flash_ok       BIT1 
//#define bat_led_on          BIT2
#define Whisper_mode        BIT2 //981004-201105-A
#define bat20_on            BIT3   
#define adjustfan           BIT4 
#define ac_to_dc            BIT5 
#define GPU_on              BIT6 
#define sv_thrt_on          BIT7 
//extern ACPI_AREA uint8_t POWER_FLAG7;			// 0x07
#define PPAB_ON2             BIT0 //981004-221025-A
#define GPU_switch           BIT1 //981004-200709-A
#define PPAB_ON              BIT2 //981004-221025-A
#define bat_cap97            BIT3 
#define dgpu_9Aon            BIT4 
#define bat_100hrs           BIT5 //981004-191122-A
//extern ACPI_AREA uint8_t POWER_FLAG8;			// 0x08
//#define f2_press         BIT0 //981004-231121-R
//#define f9_press         BIT1 //981004-231121-R
//#define f12_press        BIT2 //981004-231121-R
//#define f10_press        BIT3 //981004-231121-R
//#define no_GPU_smbus     BIT4 //981004-200923-R
#define check_pd_ac_chg2     BIT0 //981004-240617-A
#define pd_ac_over65w2       BIT1 //981004-240617-A
#define dual_ac2             BIT2 //981004-240617-A
#define pd_adapter_in2       BIT7 //981004-240617-A
//#define pd_chargable        BIT7 //981004-211021-A
#define ALL_LED_OFF       BIT3 //981004-240529-A
#define DDS_reset        BIT4   //981004-201007-A
#define D7_flag_for_bios BIT5 
//#define fnesc_press      BIT5 
#define smart_cooling_on BIT6 
//#define AI_ON            BIT7 //981004-190419-A
//extern ACPI_AREA uint8_t POWER_FLAG9;			// 0x09
#define super_quiet      BIT0 //981004-190731-A for new fan policy
#define fn_bright_press  BIT1 
#define fn_bright_press2 BIT2
#define lcd_off          BIT3 
#define rtc_wake_support BIT4 
#define temp_over_45     BIT5 //981004-190308-A
#define DGPU_Mode        BIT6 
#define dgpu_timer2      BIT7 
//extern ACPI_AREA uint8_t POWER_FLAG10;			// 0x0A
#define fullspeed_fan    BIT0 
#define disable_fn_key   BIT1
#define disable_bt_key   BIT2
#define scion_ac_in      BIT3 
#define gtx970_bat_low   BIT4 
#define ac_current_180w  BIT5 //981004-190318-A for i7/i9 CPU (1:i9 CPU) 
#define sci_on_20sec     BIT6 
//#define win_key_disable  BIT7 //981004-220216-R
#define ac_boost_enable  BIT7 //981004-220216-A
//extern ACPI_AREA uint8_t POWER_FLAG11;				// 0x0B
#define bat_normal          BIT0 
#define bat_aging           BIT1 
#define bat_repair          BIT2
//#define pd_adapter_out     BIT1
//#define pdacin_chgcur      BIT2 
#define check_pd_ac_chg     BIT3
#define pd_ac_over65w       BIT4
#define dual_ac             BIT5
#define pd_adapter_in       BIT6
#define pd_chargable        BIT7 //981004-211021-A
//extern ACPI_AREA uint8_t POWER_FLAG12;				// 0x0C
#define bat_full         BIT0 //981004-151002-A
//#define LPC_low          BIT1 //981004-190612-R
#define BAT_QUALITY      BIT1 //981004-190906-S from POWER_FLAG15
#define ac_bat10         BIT2 //981004-151014-A
#define bat_100          BIT3 //981004-160108-A
#define autofan          BIT4 //992022-141002-A (autofan1 = 0, autofan2 = 1)
#define tbt_pwr_on       BIT5 //981004-200605-A // 0 => GPIO C5 TBT_POWER off (Default) 
#define EC_modern_stby   BIT6 //981004-200721-A //Modern standby 
#define windows8         BIT7 //For BIOS writing tell windows8
//extern ACPI_AREA uint8_t POWER_FLAG13;			// 0x0D
#define adjustfan2           BIT0 
#define fixBattery           BIT1 //Fix Battery no charge when shipmode wakeup.60.8w "Model :  
//#define adjustfan4           BIT2 //981004-231019-R
#define all_sys_pwrgd_off    BIT2  
#define Flash_ME_ON          BIT3 
#define GPU_temp_80          BIT4 //981004-190419-A
#define GPU_temp_85          BIT5 //981004-190419-A
#define HDA_SDO_BIOS         BIT6 
#define adjustfan3           BIT7 //10 Level fan policy
//extern ACPI_AREA uint8_t POWER_FLAG14;			// 0x0E

//extern ACPI_AREA uint8_t POWER_FLAG15;			// 0x0F
#define BAT_XCHG                  BIT0
//#define BAT_QUALITY               BIT1 //For C&C control battery charging voltage (3 MONTHS) //981004-190906-S to POWER_FLAG12
#define BAT_CUSTOM                BIT2


//-------------------------------------------------------------------------------
//	0x300-0x3FF   OEM RAM 3  
//-------------------------------------------------------------------------------

//extern uint8_t FanLV[10] ;                      
#define tFanOn 			(*((uint8_t (*)[15])(OEMRAM3+0x0000))) //981004-180126-M from 10
//extern uint8_t tFanOff[10] ; //981004-170427-R                    
#define tFandw 			(*((uint8_t (*)[15])(OEMRAM3+0x0010))) //981004-180126-M from 10
#define I2C_WR_BUFFER	(*((uint8_t (*)[16])(OEMRAM3+0x0020))) //981004-180126-M from 10

#define GPU_TEMP_CNT1 	(*((uint8_t *)(OEMRAM3+0x0030)))		//(OEMRAM3+0x30) //981004-190419-A
#define GPU_TEMP_CNT2 	(*((uint8_t *)(OEMRAM3+0x0031)))		//(OEMRAM3+0x31) //981004-190419-A
#define DCR7_TEMP       (*((uint8_t *)(OEMRAM3+0x0032)))
#define ThrottlingCnt6_2 (*((uint8_t *)(OEMRAM3+0x0033)))
#define EC_Flag6		(*((uint8_t *)(OEMRAM3+0x0038)))		// 0x38 
#define EC_Flag7		(*((uint8_t *)(OEMRAM3+0x0039)))		// 0x39
#define CMOS_BOOT          BIT0 //981004-231123-A
#define PD_COMPARE         BIT1
#define PD1_CHARGE         BIT2
#define PD2_CHARGE         BIT3
#define Last_P81HDR		(*((uint8_t *)(OEMRAM3+0x003A)))        // 0x3A  _at_ (OEMRAM3+0x3A); //981004-180104-M from 0x1C
#define Last_P80HDR		(*((uint8_t *)(OEMRAM3+0x003B)))        // 0x3B  _at_ (OEMRAM3+0x3B); //981004-180104-M from 0x1D

#define Learn_mode_CNT3 (*((uint16_t *)(OEMRAM3+0x003C))) 
#define Learn_mode_CNT5 (*((uint16_t *)(OEMRAM3+0x003E))) 
// extern uint16_t	BAT_CV1; //(OEMRAM3+0x30)//981004-160822-A
// extern uint16_t	BAT_CV2; //(OEMRAM3+0x32)//981004-160822-A
// extern uint16_t	BAT_CV3; //(OEMRAM3+0x34)//981004-160822-A
// extern uint16_t	BAT_CV4; //(OEMRAM3+0x36)//981004-160822-A
//extern uint8_t    RTD3_EN_CNT; //(OEMRAM3+0x38) //981004-190612-R
//extern uint8_t    LPCRST_L_OUT_CNT; //(OEMRAM3+0x39) //981004-190612-R
#define PD_60W             BIT0
#define PD_65W             BIT1
#define PD_80W             BIT2
#define PD_100W            BIT3
//extern uint8_t    GPU_OC_NUM;             //(OEMRAM3+0x40) //981004-190419-A
#define SYS_MISC1        (*((uint8_t *)(OEMRAM3+0x0043)))      //(OEMRAM3+0x43)  System Misc flag 1  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ACPI_OS         	BIT0        // 1: system in ACPI environment

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SYS_MISC2		(*((uint8_t *)(OEMRAM3+0x0044)))               //(OEMRAM3+0x44)  System Misc flag 2  
#define SYS_MISC3		(*((uint8_t *)(OEMRAM3+0x0045)))              //(OEMRAM3+0x45)  System Misc flag 3  

#define EVT_STATUS1 	(*((uint8_t *)(OEMRAM3+0x0046)))           //(OEMRAM3+0x46)  Event status flag 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define HDMI_IN		    BIT6        // 1:HDMI 
//#define LAN_IN		    BIT7        // 1:LAN Plug-in
#define DummyFlag           BIT7        // 1:CRT Sense
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define EVT_STATUS2 	(*((uint8_t *)(OEMRAM3+0x0047)))           //(OEMRAM3+0x47)  Event status flag 2
#define EVT_STATUS3 	(*((uint8_t *)(OEMRAM3+0x0048)))           //(OEMRAM3+0x48)  Event status flag 3

//extern uint8_t    MISC_FLAG1;             //(OEMRAM3+0x49)  Misc flag 1 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define	WL_En        		BIT6  	    // 1:Wireless Enable On 
//#define BT_En			    BIT7  	    // 1:BlueTooth Enable On
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//extern uint8_t    MISC_FLAG2;             //(OEMRAM3+0x4A)  Misc flag 2
//981004-221123-M-S
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define CPU_HOT1 		(*((uint8_t *)(OEMRAM3+0x0049)))             //(OEMRAM3+0x49)  CPU_HOT1 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	CPU_DTS        		BIT0  	    
#define NCT_TR1			    BIT1
#define NCT_TR4			    BIT2
#define CPU_TEMP_HOT	    BIT3 
#define CPU_Throttling1	    BIT4  	    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define GPU_HOT1 			(*((uint8_t *)(OEMRAM3+0x004A)))             //(OEMRAM3+0x4A)  GPU_HOT1 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	GPU_DTS        		BIT0  	    
#define NCT_TR2			    BIT1
#define NCT_TR3			    BIT2
#define NCT_TR5			    BIT3
#define NCT_TR6			    BIT4
#define NCT_TR8			    BIT5 
#define GPU_TEMP_HOT	    BIT6 
#define GPU_Throttling1	    BIT7
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define CPU_HOT2			(*((uint8_t *)(OEMRAM3+0x004B)))             //(OEMRAM3+0x4B)  CPU_HOT2 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	CPU_DTS_ONCE                BIT0  	    
#define NCT_TR1_ONCE			    BIT1
#define NCT_TR4_ONCE			    BIT2	
//#define CPU_TEMP_HOT_ONCE	        BIT3 
	    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define GPU_HOT2			(*((uint8_t *)(OEMRAM3+0x004C)))             //(OEMRAM3+0x4C)  GPU_HOT2 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	GPU_DTS_ONCE        		BIT0  	    
#define NCT_TR2_ONCE			    BIT1
#define NCT_TR3_ONCE			    BIT2
#define NCT_TR5_ONCE			    BIT3
#define NCT_TR6_ONCE			    BIT4
#define NCT_TR8_ONCE			    BIT5 
//#define GPU_TEMP_HOT_ONCE	        BIT6
#define NCT_TR3_FAST_CHG            BIT6 //981004-230116-A
	    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

#define NVDeventStatus2 	(*((uint8_t *)(OEMRAM3+0x004D)))            // 0x4D            _at_ (OEMRAM3+0x4D); 	// Misc flag 3
#define NVDeventStatus3 	(*((uint8_t *)(OEMRAM3+0x004E)))            // 0x4E            _at_ (OEMRAM3+0x4E); 	// Misc flag 4
// extern OEMRAM3 uint8_t    MISC_FLAG3;             //(OEMRAM3+0x4B)  Misc flag 3 
// extern OEMRAM3 uint8_t    MISC_FLAG4;             //(OEMRAM3+0x4C)  Misc flag 4 
// extern OEMRAM3 uint8_t    BrgLevel;               //(OEMRAM3+0x4D)  Brightness level 
// extern OEMRAM3 uint8_t    CrisisKeyStatus;        //(OEMRAM3+0x4E)  Crisis key flag
// extern OEMRAM3 uint8_t    PanelId;                //(OEMRAM3+0x4F)  Panel ID

#define TDIM0_temp (*((uint8_t *)(OEMRAM3+0x0050)))       	    //(OEMRAM3+0x50)  DRAM 0 temperature
#define TDIM1_temp (*((uint8_t *)(OEMRAM3+0x0051)))       	    //(OEMRAM3+0x51)  DRAM 1 temperature
#define TPkg_temp  (*((uint8_t *)(OEMRAM3+0x0052)))             //(OEMRAM3+0x52)  
#define TVGA_temp  (*((uint8_t *)(OEMRAM3+0x0053)))             //(OEMRAM3+0x53)  VGA Temperature
#define TPCH_temp (*((uint8_t *)(OEMRAM3+0x0054)))			    //(OEMRAM3+0x54)  PCH Temperature
#define TSys_temp  (*((uint8_t *)(OEMRAM3+0x0055)))             //(OEMRAM3+0x55)  system Temperature
#define TCPU_temp  (*((uint8_t *)(OEMRAM3+0x0056)))             //(OEMRAM3+0x56)  CPU Temperature
#define ME_CNT     (*((uint8_t *)(OEMRAM3+0x0057)))             //(OEMRAM3+0x57)  //FLASH BIOS ME count number
#define FCC_Ratio   (*((float *)(OEMRAM3+0x0058)))            //(OEMRAM3+0x58) //981004-160909-A => 4 bytes
#define BAT_FIRST_CHECK2_10CHK (*((float *)(OEMRAM3+0x005C))) //(OEMRAM3+0x5C) //981004-180717-A => 4 bytes

/*  BATTERYS INFORMATION    */
#define BT1_STATUS1 		(*((uint8_t *)(OEMRAM3+0x0060)))            //(OEMRAM3+0x60)  Battery 1 status1 flag
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_in         		BIT0	    // 1: Battery 1 exist
#define bat_valid           BIT1   	    // 1: Battery 1 battery idetify OK
#define bat_InCharge   		BIT2   	    // 1: battery 1 in any charge phase
#define bat_Full            BIT3   	    // 1: Battery 1 fully charged
#define bat_Dischg     		BIT4   	    // 1: Battery 1 in discharging
#define bat_Dead       		BIT5   	    // 1: Battery 1 fully discharged
#define bat_abnormal        BIT6   	    // 1: battery 1 abnormal

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define BT1_STATUS2 		(*((uint8_t *)(OEMRAM3+0x0061)))           //(OEMRAM3+0x61)  Battery 1 status2 flag
#define bat_DC         		BIT0	    // 1: Set Battery 1 discharge
#define bat_WC              BIT1   	    // 1: Set Battery 1 wake up charge
#define bat_PC         		BIT2	    // 1: Set Battery 1 pre-charge
#define bat_NC              BIT3   	    // 1: Set Battery 1 normal charge
#define bat_DC_OK           BIT4	    // 1: Battery 1 in discharge
#define bat_WC_OK           BIT5   	    // 1: Battery 1 in wake up charge
#define bat_PC_OK           BIT6	    // 1: Battery 1 in pre-charge
#define bat_NC_OK           BIT7   	    // 1: Battery 1 in normal charge

#define BAT1_temp_L			(*((uint8_t *)(OEMRAM3+0x0062)))            //(OEMRAM3+0x62)  Battery 1 
#define BAT1_temp_H			(*((uint8_t *)(OEMRAM3+0x0063)))            //(OEMRAM3+0x63)  Battery 1 
#define BAT1_volt_L			(*((uint8_t *)(OEMRAM3+0x0064)))            //(OEMRAM3+0x64)  Battery 1
#define BAT1_volt_H			(*((uint8_t *)(OEMRAM3+0x0065)))            //(OEMRAM3+0x65)  Battery 1
#define BAT1_current_L			(*((uint8_t *)(OEMRAM3+0x0066)))         //(OEMRAM3+0x66)  Battery 1
#define BAT1_current_H			(*((uint8_t *)(OEMRAM3+0x0067)))         //(OEMRAM3+0x67)  Battery 1
#define BAT1_RSOC			(*((uint8_t *)(OEMRAM3+0x0068)))              //(OEMRAM3+0x68)  Battery 1

// Never use offset 0x69 of OEMRAM3
#define BAT1_RMcap_L		(*((uint8_t *)(OEMRAM3+0x006A)))           //(OEMRAM3+0x6A)  Battery 1
#define HSW_EC_VER			(*((uint8_t *)(OEMRAM3+0x006B)))             //(OEMRAM3+0x6B)
//extern uint8_t    BAT1_RMcap_H;           //(OEMRAM3+0x6B)  Battery 1
#define BAT1_FCcap_L		(*((uint8_t *)(OEMRAM3+0x006C)))           //(OEMRAM3+0x6C)  Battery 1
#define BAT1_FCcap_H		(*((uint8_t *)(OEMRAM3+0x006D)))           //(OEMRAM3+0x6D)  Battery 1
#define BAT1_CC_L			(*((uint8_t *)(OEMRAM3+0x006E)))    	        //(OEMRAM3+0x6E)  Battery 1	
#define BAT1_CC_H			(*((uint8_t *)(OEMRAM3+0x006F)))   	        //(OEMRAM3+0x6F)  Battery 1	
#define BAT1_CV_L			(*((uint8_t *)(OEMRAM3+0x0070))    	        //(OEMRAM3+0x70)  Battery 1
#define BAT1_CV_H			(*((uint8_t *)(OEMRAM3+0x0071)))   	        //(OEMRAM3+0x71)  Battery 1

#define BAT1_ALARM1			(*((uint16t *)(OEMRAM3+0x0072)))            //(OEMRAM3+0x72)  Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SMBerror0    	BIT0            // error code bit0
#define SMBerror1    	BIT1            // error code bit1
#define SMBerror2      	BIT2            // error code bit2
#define SMBerror3      	BIT3            // error code bit3
#define FullyDsg    	BIT4            // statusfully discharged
#define FullyChg     	BIT5            // statusfully charged
#define Dsg         	BIT6            // statusdischarging
#define Initialized  	BIT7            // statusgauge initialized
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define BAT1_ALARM2			(*((uint8_t *)(OEMRAM3+0x0073)))            //(OEMRAM3+0x73)  Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RemTime_alarm	BIT0            // alarmremaining time
#define RemCap_alarm  	BIT1            // alarmremaining capacity
//#define  				BIT2        	//
#define TermDsg_alarm 	BIT3            // alarmterminate discharge
#define OverTemp_alarm 	BIT4            // alarmover temperature
//#define  				BIT5        	//
#define TermChg_alarm 	BIT6            // alarmterminate charge
#define OverChg_alarm 	BIT7            // alarmover charge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define BT1_STATUS3			(*((uint8_t *)(OEMRAM3+0x0074)))            //(OEMRAM3+0x74)  Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_ForceChg    BIT0            // Battery 1 in force charge mode   
#define bat_ForceDischg BIT1            // Battery 1 in force discharge mode 
#define bat_AL          BIT2            // Battery 1 in auto learning
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define xTIPD1_pd_mA		(*((uint8_t *)(OEMRAM3+0x0075)))            //(OEMRAM3+0x75)
#define xTIPD1_pd_mA2		(*((uint8_t *)(OEMRAM3+0x0076)))            //(OEMRAM3+0x75)
#define xTIPD1_pd_mV		(*((uint8_t *)(OEMRAM3+0x0077)))            //(OEMRAM3+0x77)
#define xTIPD1_pd_mV2		(*((uint8_t *)(OEMRAM3+0x0078)))            //(OEMRAM3+0x77)
#define xTIPD1_pd_watt		(*((uint8_t *)(OEMRAM3+0x0079)))          //(OEMRAM3+0x79)
#define FAN1_RPM_H			(*((uint8_t *)(OEMRAM3+0x007A)))           //(OEMRAM3+0x7A)
#define FAN2_RPM_H			(*((uint8_t *)(OEMRAM3+0x007B)))           //(OEMRAM3+0x7B)
#define FAN_RPM_L           (*((uint8_t *)(OEMRAM3+0x007C)))
#define Learn_on_CNT		(*((uint8_t *)(OEMRAM3+0x007D)))        		// 0x7D            _at_ (OEMRAM3+0x7D);
#define CMOS_CNT            (*((uint8_t *)(OEMRAM3+0x007E)))
#define AC_vol_cnt			(*((uint8_t *)(OEMRAM3+0x007F)))           //(OEMRAM3+0x7F)

//extern uint16_t DGPUCnt; //(OEMRAM3+0x75) //981004-130207-A //981004-150417-R

#define SpiMID				(*((uint8_t *)(OEMRAM3+0x0080)))  //(OEMRAM3+0x80)
#define SpiDID0				(*((uint8_t *)(OEMRAM3+0x0081))) //(OEMRAM3+0x81)
#define SpiDID1				(*((uint8_t *)(OEMRAM3+0x0082))) //(OEMRAM3+0x82)
#define POLLING_STEP		(*((uint8_t *)(OEMRAM3+0x0083))) //(OEMRAM3+0x83) //(byte)
#define SHIP_MODE_cnt		(*((uint8_t *)(OEMRAM3+0x0084))) //(OEMRAM3+0x84) //981004-190116-A
//extern uint8_t FAKE_ACOUT_CNT; //(OEMRAM3+0x84) //981004-190109-R 
//extern uint8_t FAKE_ACOUT_CNT2; //(OEMRAM3+0x85) //981004-190109-R
//981004-190923-A-S
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define EC_Flag1			(*((uint8_t *)(OEMRAM3+0x0085)))             //ECRAM3+0x85
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define acin_chgcur        BIT0
#define chgcur_step1       BIT1
#define chgcur_step2       BIT2
#define chgcur_step3       BIT3
#define chgcur_step4       BIT4
#define chgcur_step5       BIT5 //981004-220811-A for 1C charge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define EC_Flag2			(*((uint8_t *)(OEMRAM3+0x0086)))             //ECRAM3+0x86 //981004-210118-A
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define fan_lvup_no        BIT0 
#define fan_lvdn_no        BIT1
#define pdchgcur_step1     BIT3
#define pdchgcur_step2     BIT4
#define pdchgcur_step3     BIT5
#define pdchgcur_step4     BIT6
#define pdchgcur_step5     BIT7 //981004-230828-A

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define EC_Flag3			(*((uint8_t *)(OEMRAM3+0x0087)))             //ECRAM3+0x87
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define fan_lvup_no      BIT0 
#define fan_lvdn_no      BIT1
//#define fan_lvup_ga      BIT2
//#define fan_lvdn_ga      BIT3
//#define fan_lvup_qu      BIT4
//#define fan_lvdn_qu      BIT5
#define DC_PPAB_OFF       BIT7 //981004-230131-A
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//981004-201202-A-S
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define EC_Flag4			(*((uint8_t *)(OEMRAM3+0x0088)))             //ECRAM3+0x88
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//981004-221007-R-S
#define nv_db20_lv0      BIT0 //Battery capacity is over 80% 
#define nv_db20_lv1      BIT1 //Battery capacity is over 60%
#define nv_db20_lv2      BIT2 //Battery capacity is over 40%
#define nv_db20_lv3      BIT3 //Battery capacity is less 20%
#define nv_db20_lv4      BIT4 //Battery capacity is less 50%
#define old_99w          BIT5 //981004-230510-A
#define GPU_temp_75      BIT6 //981004-221122-A
#define GPU_temp_72      BIT7 //981004-221122-A

//981004-221007-R-E

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define EC_Flag5			(*((uint8_t *)(OEMRAM3+0x0089)))             //ECRAM3+0x89 //981004-210118-A
#define learn_mode0      BIT0 //981004-211208-A
#define learn_mode1      BIT1 //981004-211208-A
#define learn_mode2      BIT2 //981004-211208-A
//#define learn_on1        BIT3 //981004-240111-R
#define TR8_heat_CHG2    BIT3 //981004-240111-A
#define TR8_heat_CHG     BIT4 //981004-230217-A
//#define warm_reset2      BIT5 //981004-211222-A
#define fix_ac_voltage   BIT5 //981004-220510-A
#define BAT_1C_CHG       BIT6 //981004-220419-A
#define AC_PPAB_ON       BIT7 //981004-230131-A

#define CHGCUR_STEP_cnt		(*((uint8_t *)(OEMRAM3+0x008A))) //(OEMRAM3+0x8A) 
#define pd_ac_in_cnt		(*((uint8_t *)(OEMRAM3+0x008B)))    //(OEMRAM3+0x8B) //981004-210118-A
#define dual_ac_cnt			(*((uint8_t *)(OEMRAM3+0x008C)))     //(OEMRAM3+0x8C) //981004-210118-A
#define CHGCUR_STEP_cnt2	(*((uint8_t *)(OEMRAM3+0x008D))) //(OEMRAM3+0x8D) //981004-210118-A
#define temp_buff2			(*((uint16_t *)(OEMRAM3+0x008E)))            // 0x8E          	_at_ (OEMRAM3+0x8E); //981004-190419-A


#define test00				(*((uint8_t *)(OEMRAM3+0x0090))) //(OEMRAM3+0x90)
#define test01				(*((uint8_t *)(OEMRAM3+0x0091))) //(OEMRAM3+0x91)
#define test02				(*((uint8_t *)(OEMRAM3+0x0092))) //(OEMRAM3+0x92)
#define test03				(*((uint8_t *)(OEMRAM3+0x0093))) //(OEMRAM3+0x93)
#define test04				(*((uint8_t *)(OEMRAM3+0x0094))) //(OEMRAM3+0x94)
#define test05				(*((uint8_t *)(OEMRAM3+0x0095))) //(OEMRAM3+0x95)
#define test06				(*((uint8_t *)(OEMRAM3+0x0096))) //(OEMRAM3+0x96)
#define test07				(*((uint8_t *)(OEMRAM3+0x0097))) //(OEMRAM3+0x97)
#define test08				(*((uint8_t *)(OEMRAM3+0x0098))) //(OEMRAM3+0x98)
#define test09				(*((uint8_t *)(OEMRAM3+0x0099))) //(OEMRAM3+0x99)
#define test0A				(*((uint8_t *)(OEMRAM3+0x009A))) //(OEMRAM3+0x9A)
#define test0B				(*((uint8_t *)(OEMRAM3+0x009B))) //(OEMRAM3+0x9B)
#define test0C				(*((uint8_t *)(OEMRAM3+0x009C))) //(OEMRAM3+0x9C)
#define test0D				(*((uint8_t *)(OEMRAM3+0x009D))) //(OEMRAM3+0x9D)
#define test0E				(*((uint8_t *)(OEMRAM3+0x009E))) //(OEMRAM3+0x9E)
#define test0F				(*((uint8_t *)(OEMRAM3+0x009F))) //(OEMRAM3+0x9F)
#define ProcsH_cnt			(*((uint8_t *)(OEMRAM3+0x00A1)))  //(OEMRAM3+0xA1) //992022-130710-M //992022-130627-A for Processor Hot patch by Max request
#define ProcsH				(*((uint8_t *)(OEMRAM3+0x00A2)))   //(OEMRAM3+0xA2)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ProcsH_acout      BIT0  
#define ProcsH_scion20sec BIT1      //992022-130731-A patch for Max request
#define ProcsH_overamp    BIT2      //992022-131111-A 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define ProcsH_scion_cnt	(*((uint8_t *)(OEMRAM3+0x00A3)))  //(OEMRAM3+0xA3) //992022-130731-A patch for Max request
//981004-131030-A-E

#define AmpHighcnt			(*((uint8_t *)(OEMRAM3+0x00A4)))  //(OEMRAM3+0xA4) //992022-140324-A patch for Max request

#define AmpHigh_flag		(*((uint8_t *)(OEMRAM3+0x00A5))) //(OEMRAM3+0xA5)  //992022-140324-A patch for Max request
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AmpHigh_30times    BIT0  //992022-140324-A patch for Max request
#define AmpHigh            BIT1  //992022-140923-A
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//extern uint16_t AmpHighRecovercnt; //(OEMRAM3+0xA6) (OEMRAM3+0xA7) //981004-180717-R
#define BAT_FIRST_CHK2_cnt		(*((uint8_t *)(OEMRAM3+0x00A6))) //(OEMRAM3+0xA6) (OEMRAM3+0xA7) //981004-180717-A
#define Power_on_patch_cnt		(*((uint8_t *)(OEMRAM3+0x00A7))) //(OEMRAM3+0xA7) //981004-210401-A
#define SCI_on_AC_in_cnt		(*((uint8_t *)(OEMRAM3+0x00A8)))  //(OEMRAM3+0xA8) //992022-140904-A
#define BAT_FIRST_CHK_cnt		(*((uint8_t *)(OEMRAM3+0x00A9)))    //(OEMRAM3+0xA9) //981004-170412-A
#define BAT_DOWNGRADE_cnt		(*((uint8_t *)(OEMRAM3+0x00AA)))    //(OEMRAM3+0xAA) //981004-170412-A
#define FAN_TEMPUP_cnt			(*((uint8_t *)(OEMRAM3+0x00AB)))       //(OEMRAM3+0xAB) //981004-170527-A
#define FAN_TEMPDN_cnt			(*((uint8_t *)(OEMRAM3+0x00AC)))       //(OEMRAM3+0xAC) //981004-170527-A
//extern uint8_t ARAdata; //(OEMRAM3+0xA0) 
#define CNT_TF					(*((uint16_t *)(OEMRAM3+0x00AD))) //(OEMRAM3+0xAD)
#define BAT_Aging_cnt			(*((uint8_t *)(OEMRAM3+0x00AF))) //(OEMRAM3+0xAF)//981004-180712-A

#define LED7s_TABLE		(*((uint8_t (*)[16])(OEMRAM3+0x00B0)))

#define FanLevelTemp2					(*((uint8_t *)(OEMRAM3+0x00C0)))
#define FanDACLevel2					(*((uint8_t *)(OEMRAM3+0x00C1)))
#define FanUpCNT3					(*((uint8_t *)(OEMRAM3+0x00C2)))
#define FanDnCNT3					(*((uint8_t *)(OEMRAM3+0x00C3)))
#define FanUpCNT4					(*((uint8_t *)(OEMRAM3+0x00C4)))
#define FanDnCNT4					(*((uint8_t *)(OEMRAM3+0x00C5)))
#define FanUpCNT5					(*((uint8_t *)(OEMRAM3+0x00C6)))
#define FanDnCNT5					(*((uint8_t *)(OEMRAM3+0x00C7)))
#define FANLVDNCNT2					(*((uint8_t *)(OEMRAM3+0x00C8)))
#define FANLVDNCNT3 				(*((uint8_t *)(OEMRAM3+0x00C9))) //0xC9
#define Learn_mode_CNT1             (*((uint16_t *)(OEMRAM3+0x00CD)))
#define Learn_mode_CNT2             (*((uint16_t *)(OEMRAM3+0x00CF)))







#define Sci_on_20sec_cnt			(*((uint8_t *)(OEMRAM3+0x00D0))) //(OEMRAM3+0xD0) 
#define AC_boost_cnt1				(*((uint8_t *)(OEMRAM3+0x00D1))) //(OEMRAM3+0xD1) 
#define AC_boost_cnt2				(*((uint8_t *)(OEMRAM3+0x00D2))) //(OEMRAM3+0xD2) 
#define AC_boost_Status				(*((uint8_t *)(OEMRAM3+0x00D3))) //(OEMRAM3+0xD3)
#define Thermal_IC_ShutDn           (*((uint8_t *)(OEMRAM3+0x00D4)))
#define KSI1_STATUS                 (*((uint8_t *)(OEMRAM3+0x00D5)))

//extern uint8_t Heavy_Load_cnt; //(OEMRAM3+0xD4) //981004-181107-R
#define NVDeventStatus				(*((uint8_t *)(OEMRAM3+0x00D6)))  //(OEMRAM3+0xD6) 
#define Wait_BAT_cnt				(*((uint8_t *)(OEMRAM3+0x00D7)))//(OEMRAM3+0xD7) 
#define Lid_close_cnt				(*((uint8_t *)(OEMRAM3+0x00D8))) //(OEMRAM3+0xD8) 
#define FanUpCNT0					(*((uint8_t *)(OEMRAM3+0x00DA)))       //(OEMRAM3+0xDA) //981004-200326-A
#define FanDnCNT0					(*((uint8_t *)(OEMRAM3+0x00DB)))       //(OEMRAM3+0xDB) //981004-200326-A
#define KSO7_CNT					(*((uint8_t *)(OEMRAM3+0x00DC))) //(OEMRAM3+0xDC)   //981004-221111-A
#define KSO2_STATUS                 (*((uint8_t *)(OEMRAM3+0x00DD)))
#define Boost_CNT1					(*((uint8_t *)(OEMRAM3+0x00DE))) //(OEMRAM3+0xD4) //981004-220216-A
#define Boost_CNT2					(*((uint8_t *)(OEMRAM3+0x00DF))) //(OEMRAM3+0xD5) //981004-220216-A
#define PWMValue					(*((uint8_t (*)[16])(OEMRAM3+0x00E0))) //981004-150421-S from 2E0

//981004-200721-A-S
#define WTDP						(*((uint8_t *)(OEMRAM3+0x00F0)))//981004-151002-A                   
#define RTDP						(*((uint8_t *)(OEMRAM3+0x00F1)) //981004-151002-A    

#define WTDP2						(*((uint16_t *)(OEMRAM3+0x00F2))) //981004-151002-A                   
//extern uint8_t  RTDP2; //981004-151002-A

#define WTDP3						(*((uint16_t *)(OEMRAM3+0x00F4))) //981004-151002-A                  
#define RTDP3						(*((uint8_t *)(OEMRAM3+0x00F6))) //981004-151002-A 
#define WTDP3_TIME					(*((uint8_t *)(OEMRAM3+0x00F7))) //981004-151002-A
#define WTDP3_DUTY					(*((uint8_t *)(OEMRAM3+0x00F8))) //981004-151002-A

#define xEC_PLMX					(*((uint8_t *)(OEMRAM3+0x00F9)))           //Max Platform temperature
#define xEC_LTMP					(*((uint8_t *)(OEMRAM3+0x00FA)))           //Sensor Temperature
#define xEC_PWER					(*((uint8_t *)(OEMRAM3+0x00FB)))
#define Check_Power_Unit			(*((uint8_t *)(OEMRAM3+0x00FC)))
#define WTDP4						(*((uint8_t *)(OEMRAM3+0x00FF))) //981004-151002-A  
#define F_PWER_ACIN      BIT0      //Real AC Power (AC Present = 1)
#define F_PWER_DCKS      BIT2      //Dock Status (1 if Docked)
#define F_PWER_CFAN      BIT3      //CPU Fan (Fan On = 1)
#define F_PWER_LSTE      BIT6      //Lid State (Lid Open = 1)
//981004-200721-A-E

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x400-0x4FF   OEM RAM 4  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM4 Offset 0x00 ~ 0x0F   Power sequnce control 
#define PowerSequnceRAM     OEMRAM4+0x00

#define SystemState				(*((uint8_t *)(PowerSequnceRAM+0x0000)))//(PowerSequnceRAM+0x00)    //(byte)
#define PWSeqStep			    (*((uint8_t *)(PowerSequnceRAM+0x0001)))//(PowerSequnceRAM+0x01)    //(byte)
#define DeepSleepCunt		    (*((uint8_t *)(PowerSequnceRAM+0x0002)))//(PowerSequnceRAM+0x02)    //(byte)
#define DelayDoPowerSeq			(*((uint8_t *)(PowerSequnceRAM+0x0003)))//(PowerSequnceRAM+0x03)    //(word)
#define DelayDoPowerSeq2		(*((uint8_t *)(PowerSequnceRAM+0x0004)))//(PowerSequnceRAM+0x03)    //(word)
#define PowSeqDelay				(*((uint8_t *)(PowerSequnceRAM+0x0005)))//(PowerSequnceRAM+0x05)    //(word)
#define PowSeqDelay2			(*((uint8_t *)(PowerSequnceRAM+0x0006)))//(PowerSequnceRAM+0x05)    //(word)
#define ECAutoPowerOn		    (*((uint8_t *)(PowerSequnceRAM+0x0007)))//(PowerSequnceRAM+0x07)    //(byte)
#define ECWDTRSTNow				(*((uint8_t *)(PowerSequnceRAM+0x0008)))//(PowerSequnceRAM+0x08)    //(byte)
#define CheckPowerStateIndex   	(*((uint8_t *)(PowerSequnceRAM+0x0009)))//(PowerSequnceRAM+0x09)    //(byte)
#define SBSWReleaseCunt			(*((uint8_t *)(PowerSequnceRAM+0x000A)))//(PowerSequnceRAM+0x0A)    //(byte)
#define PSW_COUNTER            	(*((uint16_t *)(PowerSequnceRAM+0x000B)))//(PowerSequnceRAM+0x0B)    //(word)
//#define PSW_COUNTER2           	(*((uint8_t *)(PowerSequnceRAM+0x000C))) //(PowerSequnceRAM+0x0B)    //(word)
#define HWPG_TIMER             	(*((uint8_t *)(PowerSequnceRAM+0x000D)))//(PowerSequnceRAM+0x0D)    //(word)
#define HWPG_TIMER2            	(*((uint8_t *)(PowerSequnceRAM+0x000E))) //(PowerSequnceRAM+0x0D)    //(word)
#define ShutDnCause     	    (*((uint8_t *)(PowerSequnceRAM+0x000F)))//(PowerSequnceRAM+0x0F)    //(byte)
//===============================================================================


#define Mode_SEL 				(*((uint8_t *)(OEMRAM4+0x0012)))
#define Step_Up_Time 			(*((uint8_t *)(OEMRAM4+0x0013)))
#define Step_Dn_Time 			(*((uint8_t *)(OEMRAM4+0x0014)))
#define FAN1_LV1_TEMP 			(*((uint8_t *)(OEMRAM4+0x0015)))
#define FAN1_LV2_TEMP 			(*((uint8_t *)(OEMRAM4+0x0016)))
#define FAN1_LV3_TEMP 			(*((uint8_t *)(OEMRAM4+0x0017)))
#define FAN1_LV4_TEMP 			(*((uint8_t *)(OEMRAM4+0x0018)))
#define FAN1_Critical_TEMP 		(*((uint8_t *)(OEMRAM4+0x0019)))
#define FAN1_LV1_RPM 			(*((uint8_t *)(OEMRAM4+0x001A)))
#define FAN1_LV2_RPM 			(*((uint8_t *)(OEMRAM4+0x001B)))
#define FAN1_LV3_RPM 			(*((uint8_t *)(OEMRAM4+0x001C)))
#define FAN1_LV4_RPM 			(*((uint8_t *)(OEMRAM4+0x001D)))
#define FAN1_Hystersis 			(*((uint8_t *)(OEMRAM4+0x001E)))
#define FAN2_Hystersis 			(*((uint8_t *)(OEMRAM4+0x001F)))

#define FAN2_LV1_TEMP			(*((uint8_t *)(OEMRAM4+0x0020)))
#define FAN2_LV2_TEMP			(*((uint8_t *)(OEMRAM4+0x0021)))
#define FAN2_LV3_TEMP			(*((uint8_t *)(OEMRAM4+0x0022)))
#define FAN2_LV4_TEMP			(*((uint8_t *)(OEMRAM4+0x0023)))
#define FAN2_Critical_TEMP		(*((uint8_t *)(OEMRAM4+0x0024)))
#define FAN2_LV1_RPM			(*((uint8_t *)(OEMRAM4+0x0025)))
#define FAN2_LV2_RPM			(*((uint8_t *)(OEMRAM4+0x0026)))
#define FAN2_LV3_RPM			(*((uint8_t *)(OEMRAM4+0x0027)))
#define FAN2_LV4_RPM			(*((uint8_t *)(OEMRAM4+0x0028)))
#define RPM_Tolerance_Value		(*((uint8_t *)(OEMRAM4+0x0029)))
#define RPM_Mode				(*((uint8_t *)(OEMRAM4+0x002A)))
#define TEMP_Source_Sel			(*((uint8_t *)(OEMRAM4+0x002B)))
#define FANCTRL_Mapping_Sel		(*((uint8_t *)(OEMRAM4+0x002C)))
#define FANSTOP_Time			(*((uint8_t *)(OEMRAM4+0x002D)))
#define Set_Fan_to_Stop			(*((uint8_t *)(OEMRAM4+0x002E)))
#define START_SEL				(*((uint8_t *)(OEMRAM4+0x002F)))      	 // 0x2F          	   _at_ (OEMRAM4+0x2F); //981004-190419



//===============================================================================
// OEMRAM4 Offset 0x30 ~ 0x4F   ADC variables
#define ADCRAM     OEMRAM4+0x30
#define ADCAvg0					(*((uint16_t *)(ADCRAM+0x0000)))				//(ADCRAM+0x00) //(word)
#define ADCAvg1					(*((uint16_t *)(ADCRAM+0x0002)))				//(ADCRAM+0x02) //(word)
#define ADCAvg2					(*((uint16_t *)(ADCRAM+0x0004)))			    //(ADCRAM+0x04) //(word)
#define ADCAvg3					(*((uint16_t *)(ADCRAM+0x0006)))				//(ADCRAM+0x06) //(word)
#define ADCAvg4					(*((uint16_t *)(ADCRAM+0x0008)))				//(ADCRAM+0x08) //(word)
#define ADCAvg5					(*((uint16_t *)(ADCRAM+0x000A)))			    //(ADCRAM+0x0A) //(word)
#define Fix_ADCAvg0				(*((uint16_t *)(ADCRAM+0x000C)))			//(ADCRAM+0x0C) //(word)
#define Fix_ADCAvg1				(*((uint16_t *)(ADCRAM+0x000E)))			//(ADCRAM+0x0E) //(word)

#define ADCDyTable1Index		(*((uint8_t *)(ADCRAM+0x0010)))       //(ADCRAM+0x10) //(byte)
#define ADCDyTable2Index		(*((uint8_t *)(ADCRAM+0x0011)))       //(ADCRAM+0x11) //(byte)

#define LED_TEST_CNT            (*((uint8_t *)(OEMRAM4+0x0042)))
#define pd_ac_in_cnt2           (*((uint8_t *)(OEMRAM4+0x0043)))           // _at_ (OEMRAM4+0x43);
//Reserved offset 0x12 ~ 0x1F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x50 ~ 0x6F   SMBus center variables
#define SMBusCenterRAM      OEMRAM4+0x50

#define SMBus1Flag1				(*((uint8_t *)(SMBusCenterRAM+0x0000)))			//(SMBusCenterRAM+0x00)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define B1_RSOC         BIT0
#define B1_C            BIT1
#define B1_V            BIT2
#define B1_RMcap        BIT3
#define B1_Status       BIT4
#define B1_FCC          BIT5
#define B1_Temp         BIT6
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SMBus1Flag2				(*((uint8_t *)(SMBusCenterRAM+0x0001)))			//(SMBusCenterRAM+0x01)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define B1_CC           BIT0
#define B1_CV           BIT1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SMBus1Flag3				(*((uint8_t *)(SMBusCenterRAM+0x0002)))			//(SMBusCenterRAM+0x02)
#define SMBus1Flag4				(*((uint8_t *)(SMBusCenterRAM+0x0003)))		    //(SMBusCenterRAM+0x03)
#define SMBus1Flag5				(*((uint8_t *)(SMBusCenterRAM+0x0004)))		    //(SMBusCenterRAM+0x04)

#define SMBus2Flag1				(*((uint8_t *)(SMBusCenterRAM+0x0005)))		    //(SMBusCenterRAM+0x05)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PollRemote      BIT0            // Read thermal sensor remote temperature
#define PollLocal       BIT1            // Read thermal sensor local temperature
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SMBus2Flag2				(*((uint8_t *)(SMBusCenterRAM+0x0006)))		    //(SMBusCenterRAM+0x06)
#define SMBus2Flag3				(*((uint8_t *)(SMBusCenterRAM+0x0007)))		    //(SMBusCenterRAM+0x07)
#define SMBus2Flag4				(*((uint8_t *)(SMBusCenterRAM+0x0008)))		    //(SMBusCenterRAM+0x08)
#define SMBus2Flag5				(*((uint8_t *)(SMBusCenterRAM+0x0009)))		    //(SMBusCenterRAM+0x09)
#define SMBus3Flag1				(*((uint8_t *)(SMBusCenterRAM+0x000A)))			//(SMBusCenterRAM+0x0A)
#define SMBusSelection			(*((uint8_t *)(SMBusCenterRAM+0x000B)))			//(SMBusCenterRAM+0x0B)
#define F_Service_SMBus1		(*((uint8_t *)(SMBusCenterRAM+0x000C)))       //(SMBusCenterRAM+0x0C)
#define F_Service_SMBus2		(*((uint8_t *)(SMBusCenterRAM+0x000D)))       //(SMBusCenterRAM+0x0D)
#define F_Service_SMBus3		(*((uint8_t *)(SMBusCenterRAM+0x000E)))       //(SMBusCenterRAM+0x0E)
#define F_Service_SMBus4		(*((uint8_t *)(SMBusCenterRAM+0x000F)))       //(SMBusCenterRAM+0x0F)
#define SMBus1ByteCunt			(*((uint8_t *)(SMBusCenterRAM+0x0010)))	        //(SMBusCenterRAM+0x10)
#define SMBus2ByteCunt			(*((uint8_t *)(SMBusCenterRAM+0x0011)))		    //(SMBusCenterRAM+0x11)
#define SMBus3ByteCunt			(*((uint8_t *)(SMBusCenterRAM+0x0012)))		    //(SMBusCenterRAM+0x12)
#define SMBus1counter			(*((uint8_t *)(SMBusCenterRAM+0x0013)))		    //(SMBusCenterRAM+0x13)
#define SMBus2counter			(*((uint8_t *)(SMBusCenterRAM+0x0014)))		    //(SMBusCenterRAM+0x14)
#define SMBus3counter			(*((uint8_t *)(SMBusCenterRAM+0x0015)))		    //(SMBusCenterRAM+0x15)
#define SMBus1index				(*((uint8_t *)(SMBusCenterRAM+0x0016)))			//(SMBusCenterRAM+0x16)
#define SMBus2index				(*((uint8_t *)(SMBusCenterRAM+0x0017)))			//(SMBusCenterRAM+0x17)
#define SMBus3index				(*((uint8_t *)(SMBusCenterRAM+0x0018)))			//(SMBusCenterRAM+0x18)
#define SMBus1InUsing			(*((uint8_t *)(SMBusCenterRAM+0x0019)))          //(SMBusCenterRAM+0x19)
#define SMBus2InUsing			(*((uint8_t *)(SMBusCenterRAM+0x001A)))          //(SMBusCenterRAM+0x1A)
#define SMBus3InUsing			(*((uint8_t *)(SMBusCenterRAM+0x001B)))          //(SMBusCenterRAM+0x1B)
#define SMBus1TableSize			(*((uint8_t *)(SMBusCenterRAM+0x001C)))        //(SMBusCenterRAM+0x1C)
#define SMBus2TableSize			(*((uint8_t *)(SMBusCenterRAM+0x001D)))        //(SMBusCenterRAM+0x1D)
#define SMBus3TableSize			(*((uint8_t *)(SMBusCenterRAM+0x001E)))        //(SMBusCenterRAM+0x1E)
#define SMBusXStatus			(*((uint8_t *)(SMBusCenterRAM+0x001F)))           //(SMBusCenterRAM+0x1F)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SMBus1_OK       BIT0
#define SMBus1_Fail     BIT1
#define SMBus2_OK       BIT2
#define SMBus2_Fail     BIT3
#define SMBus3_OK       BIT4
#define SMBus3_Fail     BIT5
#define SMBus4_OK       BIT6
#define SMBus4_Fail     BIT7
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//extern uint8_t SMB_BUFFER[];                       //_at_ (SMBusCenterRAM+0x20); //981004-200721-R
//===============================================================================
//===============================================================================

//981004-210705-A-S
#define Lux_TEMP				(*((uint32_t *)(OEMRAM4+0x0070)))
#define Lux						(*((uint32_t *)(OEMRAM4+0x0074)))
#define Lux_NEW					(*((uint32_t *)(OEMRAM4+0x0078)))
//981004-210705-A-E

//981004-220510-A-S
#define GAUGE_CURRENT_CNT1		(*((uint8_t *)(OEMRAM4+0x0080)))
#define GAUGE_CURRENT_CNT2		(*((uint8_t *)(OEMRAM4+0x0081)))
#define GAUGE_CURRENT_CNT3		(*((uint8_t *)(OEMRAM4+0x0082)))
#define GAUGE_CURRENT_CNT4		(*((uint8_t *)(OEMRAM4+0x0083)))
#define GAUGE_CURRENT_CNT5		(*((uint8_t *)(OEMRAM4+0x0084)))
#define GAUGE_CURRENT_CNT6		(*((uint8_t *)(OEMRAM4+0x0085)))
#define GAUGE_VOLTAGE_CNT1		(*((uint8_t *)(OEMRAM4+0x0086)))
#define GAUGE_VOLTAGE_CNT2		(*((uint8_t *)(OEMRAM4+0x0087)))
#define GAUGE_VOLTAGE_CNT3		(*((uint8_t *)(OEMRAM4+0x0088)))
#define GAUGE_VOLTAGE_CNT4		(*((uint8_t *)(OEMRAM4+0x0089)))
#define GAUGE_VOLTAGE_CNT5		(*((uint8_t *)(OEMRAM4+0x008A)))
#define GAUGE_VOLTAGE_CNT6		(*((uint8_t *)(OEMRAM4+0x008B)))
#define GAUGE_VOLTAGE_CNT7		(*((uint8_t *)(OEMRAM4+0x008C)))
#define GAUGE_VOLTAGE_CNT8		(*((uint8_t *)(OEMRAM4+0x008D)))
#define GAUGE_VOLTAGE_CNT9		(*((uint8_t *)(OEMRAM4+0x008E)))
//981004-221123-A-S
#define ThrottlingCnt1			(*((uint8_t *)(OEMRAM4+0x0090)))
#define ThrottlingCnt2			(*((uint8_t *)(OEMRAM4+0x0091)))
#define ThrottlingCnt3			(*((uint8_t *)(OEMRAM4+0x0092)))
#define ThrottlingCnt4			(*((uint8_t *)(OEMRAM4+0x0093)))
#define ThrottlingCnt5			(*((uint8_t *)(OEMRAM4+0x0094)))
#define ThrottlingCnt6			(*((uint8_t *)(OEMRAM4+0x0095)))
#define ThrottlingCnt7			(*((uint8_t *)(OEMRAM4+0x0096)))
#define ThrottlingCnt8			(*((uint8_t *)(OEMRAM4+0x0097)))
#define ThrottlingCnt9			(*((uint8_t *)(OEMRAM4+0x0098)))
#define ThrottlingCnt10			(*((uint8_t *)(OEMRAM4+0x0099)))
#define ThrottlingCnt11			(*((uint8_t *)(OEMRAM4+0x009A)))
#define ThrottlingCnt12			(*((uint8_t *)(OEMRAM4+0x009B)))
#define ThrottlingCnt13			(*((uint8_t *)(OEMRAM4+0x009C)))
#define ThrottlingCnt14			(*((uint8_t *)(OEMRAM4+0x009D)))
#define ThrottlingCnt15			(*((uint8_t *)(OEMRAM4+0x009E)))
#define ThrottlingCnt16			(*((uint8_t *)(OEMRAM4+0x009F)))
#define ThrottlingCnt17			(*((uint8_t *)(OEMRAM4+0x00A0)))
#define ThrottlingCnt18			(*((uint8_t *)(OEMRAM4+0x00A1)))
#define VeryHotCnt				(*((uint8_t *)(OEMRAM4+0x00A2)))            
#define VeryHotCnt2				(*((uint8_t *)(OEMRAM4+0x00A3)))
#define NVDeventupCnt1			(*((uint8_t *)(OEMRAM4+0x00A4))) 
#define NVDeventupCnt2			(*((uint8_t *)(OEMRAM4+0x00A5))) 
#define NVDeventdnCnt1			(*((uint8_t *)(OEMRAM4+0x00A6)))           
#define NVDeventdnCnt2			(*((uint8_t *)(OEMRAM4+0x00A7)))                     
//981004-221123-A-E
#define BATCAP75				(*((uint16_t *)(OEMRAM4+0x00A8))) //981004-230510-A
#define BATCAP70				(*((uint16_t *)(OEMRAM4+0x00AA))) //981004-230510-A

#define AMP_XOR                 (*((uint8_t *)(OEMRAM4+0x00AE))) 
#define AMP_CRC                 (*((uint8_t *)(OEMRAM4+0x00AF))) 

//981004-220510-A-E
//981004-210617-A-E 
//===============================================================================
//===============================================================================
// OEMRAM4 Offset 0x70 ~ 0x9F   Battery 1 control variables
//981004-170821-R-S
#if 0
#define BAT1CtrlRAM     OEMRAM4+0x70
extern uint8_t    BAT1_CtrlStep;          //(BAT1CtrlRAM+0x00)
extern uint8_t    BAT1_ID_Step;           //(BAT1CtrlRAM+0x01)
extern uint8_t    BAT1_1SecTimer;         //(BAT1CtrlRAM+0x02)
extern uint8_t    BAT1_S_Number;          //(BAT1CtrlRAM+0x03)
extern uint8_t    ByteTemp01;             //(BAT1CtrlRAM+0x04)
extern uint8_t    ByteTemp02;             //(BAT1CtrlRAM+0x05)
extern uint8_t    BAT1_ID_TimeOut_CNT;    //(BAT1CtrlRAM+0x06)
extern uint8_t    BAT1_Number;            //(BAT1CtrlRAM+0x07)
extern uint8_t    BAT1_FailCause;         //(BAT1CtrlRAM+0x08)
extern uint8_t    BAT1_FirstDataIndex;    //(BAT1CtrlRAM+0x09)
extern uint8_t	INPUT_CURRENT_LO;       //(BAT1CtrlRAM+0x0A)
extern uint8_t	INPUT_CURRENT_HI;       //(BAT1CtrlRAM+0x0B)
extern uint8_t	CHARGE_CURRENT_LO;      //(BAT1CtrlRAM+0x0C)
extern uint8_t	CHARGE_CURRENT_HI;      //(BAT1CtrlRAM+0x0D)
extern uint8_t	CHARGE_VOLTAGE_LO;      //(BAT1CtrlRAM+0x0E)  
extern uint8_t	CHARGE_VOLTAGE_HI;      //(BAT1CtrlRAM+0x0F)
extern uint8_t	Charger_TimeOut;        //(BAT1CtrlRAM+0x10)
extern uint8_t    WakeUpChrCunt_Min;      //(BAT1CtrlRAM+0x11) 
extern uint16_t    PreChrCunt_Min;         //(BAT1CtrlRAM+0x12)
extern uint16_t    NormalChrCunt_Min;      //(BAT1CtrlRAM+0x14)
extern uint16_t    WakeUpChrCunt;          //(BAT1CtrlRAM+0x16) 
extern uint16_t    PreChrCunt;             //(BAT1CtrlRAM+0x18) 
extern uint16_t    NormalChrCunt;          //(BAT1CtrlRAM+0x1A)
extern uint8_t    BAT1_OTCunt;            //(BAT1CtrlRAM+0x1C)
extern uint8_t    BAT1_OVCunt;            //(BAT1CtrlRAM+0x1D)
extern uint16_t    CHARGE_CURRENT_BK;      //(BAT1CtrlRAM+0x1E)
extern uint16_t    CHARGE_VOLTAGE_BK;      //(BAT1CtrlRAM+0x20)
#endif
//981004-170821-R-E

//981004-180712-A-S 

//extern OEMRAM3 uint8_t I2C_WR_BUFFER[16];
//extern OEMRAM3 uint8_t LED7s_TABLE[16];

//981004-180712-A-E     

//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0xA0 ~ 0xAF   Power sequnce control 
#define PowerSequnce2RAM    OEMRAM4+0xE0

#define PowerStatusBK			(*((uint8_t *)(PowerSequnce2RAM+0x0000)))          //(PowerSequnce2RAM+0x00)
#define PowerOnWDT				(*((uint16_t *)(PowerSequnce2RAM+0x0001)))             //(PowerSequnce2RAM+0x01)
//Reserved OEMRAM4 offset 0xB0 ~ 0xEF

//===============================================================================
// OEMRAM4 Offset 0xF0 ~ 0xFF   Event debounce counter 
#define DebounceRAM     OEMRAM4+0xF0

#define	DEBOUNCE_CONT1			(*((uint8_t *)(DebounceRAM+0x0000)))	    //(DebounceRAM+0x00) 	//(byte)
#define	DEBOUNCE_CONT2			(*((uint8_t *)(DebounceRAM+0x0001)))	    //(DebounceRAM+0x01) 	//(byte)
#define	DEBOUNCE_CONT3			(*((uint8_t *)(DebounceRAM+0x0002)))	    //(DebounceRAM+0x02) 	//(byte)
#define	DEBOUNCE_CONT4			(*((uint8_t *)(DebounceRAM+0x0003)))	    //(DebounceRAM+0x03) 	//(byte) 
#define	DEBOUNCE_CONT5			(*((uint8_t *)(DebounceRAM+0x0004)))	    //(DebounceRAM+0x04) 	//(byte)
#define	DEBOUNCE_CONT6			(*((uint8_t *)(DebounceRAM+0x0005)))	    //(DebounceRAM+0x05) 	//(byte)
#define	DEBOUNCE_CONT7			(*((uint8_t *)(DebounceRAM+0x0006)))	    //(DebounceRAM+0x06) 	//(byte)
#define	DEBOUNCE_CONT8			(*((uint8_t *)(DebounceRAM+0x0007)))	    //(DebounceRAM+0x07) 	//(byte)
#define	DEBOUNCE_CONT9			(*((uint8_t *)(DebounceRAM+0x0008)))	    //(DebounceRAM+0x08) 	//(byte) 
#define	DEBOUNCE_CONT10			(*((uint8_t *)(DebounceRAM+0x0009)))		//(DebounceRAM+0x09) 	//(byte)
#define	DEBOUNCE_CONT11			(*((uint8_t *)(DebounceRAM+0x000A)))		//(DebounceRAM+0x0A) 	//(byte) 
#define	DEBOUNCE_CONT12			(*((uint8_t *)(DebounceRAM+0x000B)))		//(DebounceRAM+0x0B) 	//(byte)
#define	DEBOUNCE_CONT13			(*((uint8_t *)(DebounceRAM+0x000C)))		//(DebounceRAM+0x0C) 	//(byte)
#define	DEBOUNCE_CONT14			(*((uint8_t *)(DebounceRAM+0x000D)))		//(DebounceRAM+0x0D) 	//(byte)
#define	DEBOUNCE_CONT15			(*((uint8_t *)(DebounceRAM+0x000E)))		//(DebounceRAM+0x0E) 	//(byte)
#define	DEBOUNCE_CONT16			(*((uint8_t *)(DebounceRAM+0x000F)))		//(DebounceRAM+0x0F) 	//(byte) 
//===============================================================================

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x500-0x5FF   OEM RAM 5  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM5 Offset 0x00 ~ 0x3F   For fan control 

//981004-200721-R-S
#if 0
#define FanCtrlRAM      OEMRAM5+0x00
extern uint8_t	Fan1On_Step1;   		// FanCtrlRAM+0x00
extern uint8_t	Fan1On_Step2;   		// FanCtrlRAM+0x01
extern uint8_t	Fan1On_Step3;   		// FanCtrlRAM+0x02
extern uint8_t	Fan1On_Step4;  			// FanCtrlRAM+0x03
extern uint8_t	Fan1On_Step5;   		// FanCtrlRAM+0x04
extern uint8_t	Fan1On_Step6;   		// FanCtrlRAM+0x05
extern uint8_t	Fan1On_Step7;   		// FanCtrlRAM+0x06
extern uint8_t	Fan1On_Step8;   		// FanCtrlRAM+0x07
extern uint8_t	Fan2On_Step1; 			// FanCtrlRAM+0x08
extern uint8_t	Fan2On_Step2; 			// FanCtrlRAM+0x09
extern uint8_t	Fan2On_Step3; 			// FanCtrlRAM+0x0A
extern uint8_t	Fan2On_Step4; 			// FanCtrlRAM+0x0B
extern uint8_t	Fan2On_Step5; 			// FanCtrlRAM+0x0C
extern uint8_t	Fan2On_Step6; 			// FanCtrlRAM+0x0D
extern uint8_t	Fan2On_Step7; 			// FanCtrlRAM+0x0E
extern uint8_t	Fan2On_Step8; 			// FanCtrlRAM+0x0F

extern uint8_t	Fan1Off_Step1;  		// FanCtrlRAM+0x10
extern uint8_t	Fan1Off_Step2;  		// FanCtrlRAM+0x11
extern uint8_t	Fan1Off_Step3;  		// FanCtrlRAM+0x12
extern uint8_t	Fan1Off_Step4;  		// FanCtrlRAM+0x13
extern uint8_t	Fan1Off_Step5;  		// FanCtrlRAM+0x14
extern uint8_t	Fan1Off_Step6;  		// FanCtrlRAM+0x15
extern uint8_t	Fan1Off_Step7;  		// FanCtrlRAM+0x16
extern uint8_t	Fan1Off_Step8;  		// FanCtrlRAM+0x17
extern uint8_t	Fan2Off_Step1; 			// FanCtrlRAM+0x18
extern uint8_t	Fan2Off_Step2; 			// FanCtrlRAM+0x19
extern uint8_t	Fan2Off_Step3; 			// FanCtrlRAM+0x1A
extern uint8_t	Fan2Off_Step4; 			// FanCtrlRAM+0x1B
extern uint8_t	Fan2Off_Step5;			// FanCtrlRAM+0x1C
extern uint8_t	Fan2Off_Step6; 			// FanCtrlRAM+0x1D
extern uint8_t	Fan2Off_Step7; 			// FanCtrlRAM+0x1E
extern uint8_t	Fan2Off_Step8;			// FanCtrlRAM+0x1F

extern uint8_t	Fan1RPM_Step1; 			// FanCtrlRAM+0x20
extern uint8_t	Fan1RPM_Step2; 			// FanCtrlRAM+0x21
extern uint8_t	Fan1RPM_Step3; 			// FanCtrlRAM+0x22
extern uint8_t	Fan1RPM_Step4; 			// FanCtrlRAM+0x23
extern uint8_t	Fan1RPM_Step5; 			// FanCtrlRAM+0x24
extern uint8_t	Fan1RPM_Step6; 			// FanCtrlRAM+0x25
extern uint8_t	Fan1RPM_Step7; 			// FanCtrlRAM+0x26
extern uint8_t	Fan1RPM_Step8; 			// FanCtrlRAM+0x27
extern uint8_t	Fan2RPM_Step1; 			// FanCtrlRAM+0x28
extern uint8_t	Fan2RPM_Step2; 			// FanCtrlRAM+0x29
extern uint8_t	Fan2RPM_Step3; 			// FanCtrlRAM+0x2A
extern uint8_t	Fan2RPM_Step4; 			// FanCtrlRAM+0x2B
extern uint8_t	Fan2RPM_Step5; 			// FanCtrlRAM+0x2C
extern uint8_t	Fan2RPM_Step6; 			// FanCtrlRAM+0x2D
extern uint8_t	Fan2RPM_Step7; 			// FanCtrlRAM+0x2E
extern uint8_t	Fan2RPM_Step8; 			// FanCtrlRAM+0x2F

//extern uint16_t	RPM1;					// FanCtrlRAM+0x30
//extern uint16_t	RPM2;					// FanCtrlRAM+0x32
extern uint8_t	Fan1RPM;				// FanCtrlRAM+0x34
extern uint8_t	Fan2RPM;				// FanCtrlRAM+0x35
extern uint8_t	FanLevel1;				// FanCtrlRAM+0x36
extern uint8_t	FanLeve2;				// FanCtrlRAM+0x37
extern uint8_t	temperature1;			// FanCtrlRAM+0x38	
extern uint8_t	temperature2;			// FanCtrlRAM+0x39
extern uint8_t	Debugtemperature1;		// FanCtrlRAM+0x3A			
extern uint8_t	Debugtemperature2;		// FanCtrlRAM+0x3B	
extern uint8_t	DummyStep;				// FanCtrlRAM+0x3C
extern uint8_t	FanFullOnCont;			// FanCtrlRAM+0x3D
extern uint8_t	RPMTimeShift;			// FanCtrlRAM+0x3E
extern uint8_t	DebugFan1RPMT;			// FanCtrlRAM+0x3F
#endif
//981004-200721-R-E
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0x40 ~ 0xAF   For PECI function 
#define PECICtrlRAM      OEMRAM5+0x40

#define PECIReadBuffer        (*((uint8_t (*)[16])(PECICtrlRAM+0x0000)))// PECICtrlRAM + 0x000 offset 0x40 ~ 0x4F
#define PECIWriteBuffer       (*((uint8_t (*)[16])(PECICtrlRAM+0x0010)))// PECICtrlRAM + 0x010 offset 0x50 ~ 0x5F
#define PECI_CRC8             (*((uint8_t *)(PECICtrlRAM+0x0020))) // PECICtrlRAM + 0x020 offset 0x60
#define PECI_CompletionCode   (*((uint8_t *)(PECICtrlRAM+0x0021)))  // PECICtrlRAM + 0x021 offset 0x61
#define PECI_PCIConfigAddr    (*((uint8_t (*)[4])(PECICtrlRAM+0x0022))) // PECICtrlRAM + 0x022 offset 0x62 ~ 0x65
//Reserved offset 0x66 ~ 0x6F
#define PECI_PowerCtrlStep    (*((uint8_t *)(PECICtrlRAM+0x0030)))   // PECICtrlRAM + 0x030 offset 0x70
#define PECI_PowerUnit        (*((uint8_t *)(PECICtrlRAM+0x0031)))   // PECICtrlRAM + 0x031 offset 0x71
#define PECI_EnergyUnit       (*((uint8_t *)(PECICtrlRAM+0x0032)))   // PECICtrlRAM + 0x032 offset 0x72
#define PECI_TimeUnit         (*((uint8_t *)(PECICtrlRAM+0x0033)))   // PECICtrlRAM + 0x033 offset 0x73
#define PECI_PL2Watts         (*((uint8_t *)(PECICtrlRAM+0x0034)))   // PECICtrlRAM + 0x034 offset 0x74
#define PECI_MAXPL2           (*((uint8_t *)(PECICtrlRAM+0x0035)))   // PECICtrlRAM + 0x035 offset 0x75
#define PECI_PL1TDP           (*((uint8_t *)(PECICtrlRAM+0x0036)))   // PECICtrlRAM + 0x036 offset 0x76
#define PECI_PL1Time          (*((uint8_t *)(PECICtrlRAM+0x0037)))   // PECICtrlRAM + 0x037 offset 0x77
#define PECI_Ctrl             (*((uint8_t *)(PECICtrlRAM+0x0038)))   // PECICtrlRAM + 0x038 offset 0x78
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SetPL2Request           BIT0
#define SetPL3Request           BIT1 //981004-151002-A
#define SetPL4Request           BIT2 //981004-151002-A

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define PECI_AdaptorWatts		(*((uint8_t *)(PECICtrlRAM+0x0039)))       // PECICtrlRAM + 0x039 offset 0x79
#define PECI_SystemWatts 		(*((uint8_t *)(PECICtrlRAM+0x003A)))        // PECICtrlRAM + 0x03A offset 0x7A
#define PECI_Algorithm_Delay 	(*((uint8_t *)(PECICtrlRAM+0x003B)))    // PECICtrlRAM + 0x03B offset 0x7B
#define PECI_ErrorCount 		(*((uint32_t *)(PECICtrlRAM+0x003C)))         // PECICtrlRAM + 0x03C offset 0x7C ~ 0x0x7F
#define PECI_StressToolBuf 		(*((uint8_t (*)[32])(PECICtrlRAM+0x0040)))    // PECICtrlRAM + 0x040 offset 0x80 ~ 0x9F
//Reserved offset 0xAA ~ 0xAF


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PSTB_RepeatCycle0           0
#define PSTB_RepeatCycle1           1
#define PSTB_RepeatCycle2           2
#define PSTB_RepeatCycle3           3
#define PSTB_RepeatInterval         4           // 10ms timer base
#define PSTB_StopOnError            5
#define PSTB_ClientAddress          6
#define PSTB_WriteLength            7
#define PSTB_ReadLength             8

#define PSTB_CommandSpecificData    9
#define PSTB_CmdCode                PSTB_CommandSpecificData

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define PSTB_Timer 				(*((uint8_t *)(PECICtrlRAM+0x0060)))              // PECICtrlRAM + 0x060 offset 0xA0
#define PSTB_CmdStatus 			(*((uint8_t *)(PECICtrlRAM+0x0061)))          // PECICtrlRAM + 0x061 offset 0xA1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ServivePECIStressTool   BIT0

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define PSTB_RepeatIntervalCount (*((uint8_t *)(PECICtrlRAM+0x0062)))   // PECICtrlRAM + 0x062  offset 0xA2
#define PSTB_RepeatCycle 		(*((uint32_t *)(PECICtrlRAM+0x0063)))           // PECICtrlRAM + 0x063  offset 0xA3 ~ 0xA6
#define CPUTjmax 				(*((uint8_t *)(PECICtrlRAM+0x0067)))			        // PECICtrlRAM + 0x067
#define ReadCPUTjmaxCUNT 		(*((uint8_t *)(PECICtrlRAM+0x0068)))           // PECICtrlRAM + 0x068
#define StressToolReadBufIndex 	(*((uint8_t *)(PECICtrlRAM+0x0069)))     // PECICtrlRAM + 0x069
//Rese#define

//===============================================================================
#define FAST_CHG_CNT1                   (*((uint8_t *)(OEMRAM5+0x00B0))) //   _at_ (OEMRAM5+0xB0); //981004-230925-A
#define FAST_CHG_CNT2                   (*((uint8_t *)(OEMRAM5+0x00B1))) //   _at_ (OEMRAM5+0xB1); //981004-230925-A
#define CHG_TEMP1                       (*((uint8_t *)(OEMRAM5+0x00B2))) //   _at_ (OEMRAM5+0xB2); //981004-230925-A
#define CHG_TEMP2                       (*((uint8_t *)(OEMRAM5+0x00B3))) //   _at_ (OEMRAM5+0xB3); //981004-230925-A
#define CHG_TEMP3                       (*((uint8_t *)(OEMRAM5+0x00B4))) //   _at_ (OEMRAM5+0xB4); //981004-230925-A
#define CHG_TEMP4                       (*((uint8_t *)(OEMRAM5+0x00B5))) //   _at_ (OEMRAM5+0xB5); //981004-230925-A
#define CHG_TEMP5                       (*((uint8_t *)(OEMRAM5+0x00B6))) //   _at_ (OEMRAM5+0xB6); //981004-230925-A
#define CHG_TEMP6                       (*((uint8_t *)(OEMRAM5+0x00B7))) //   _at_ (OEMRAM5+0xB7); //981004-230925-A
#define CHG_TEMP7                       (*((uint8_t *)(OEMRAM5+0x00B8))) //   _at_ (OEMRAM5+0xB8); //981004-230925-A
//===============================================================================
// OEMRAM5 Offset 0xC0 ~ 0xCF   For OEM SPI function 
#define SPI_Mouse           OEMRAM5+0xC0

#define SPI_Mouse_Buf  (*((uint8_t (*)[3])(SPI_Mouse+0x0000)))         //( SPI_Mouse + 0x00)
#define SPI_Mouse_DeltaX  (*((uint8_t *)(SPI_Mouse+0x0003)))        //( SPI_Mouse + 0x03)
#define SPI_Mouse_DeltaY  (*((uint8_t *)(SPI_Mouse+0x0004)))        //( SPI_Mouse + 0x04)
#define SPI_Mouse_BYTE1  (*((uint8_t *)(SPI_Mouse+0x0005)))         //( SPI_Mouse + 0x05)

//#define SpiMID		      (*(uint8_t *)0x06B2)  //SPI ROM ID
//#define SpiDID0		      (*(uint8_t *)0x06B3)  //SPI ROM ID             
//#define SpiDID1		      (*(uint8_t *)0x06B4)  //SPI ROM ID 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define Y_Overflow          BIT7
#define X_Overflow          BIT6
#define Y_Signbit           BIT5
#define X_Signbit           BIT4
#define Always1             BIT3
#define MiddleBtn           BIT2
#define RightBtn            BIT1
#define LeftBtn             BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SPI_Mouse_XMovement  (*((uint8_t *)(SPI_Mouse+0x0006)))   //( SPI_Mouse + 0x06)
#define SPI_Mouse_YMovement  (*((uint8_t *)(SPI_Mouse+0x0007)))   //( SPI_Mouse + 0x07)
#define SPI_Mouse_Buf_Index  (*((uint8_t *)(SPI_Mouse+0x0008)))   //( SPI_Mouse + 0x08)
#define SPI_Mouse_Misc       (*((uint8_t *)(SPI_Mouse+0x0009)))  //( SPI_Mouse + 0x09)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SPI_Mouse_Need_Break    BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SPI_Mouse_ID 		(*((uint8_t *)(SPI_Mouse+0x000A)))           #define
//Reserved offset 0x0A ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xD0 ~ 0xEF   For OEM SCI qevent function
#define SCI_Qevent_Ctrl     OEMRAM5+0xD0

#define	SCI_Event_In_Index     (*((uint8_t *)(SCI_Qevent_Ctrl+0x0000)))							//( SCI_Qevent_Ctrl + 0x00);
#define	SCI_Event_Out_Index    (*((uint8_t *)(SCI_Qevent_Ctrl+0x0001)))							//( SCI_Qevent_Ctrl + 0x01);
#define	SCI_Event_Buffer       (*((uint8_t (*)[EVENT_BUFFER_SIZE])(SCI_Qevent_Ctrl+0x0002)))	//( SCI_Qevent_Ctrl + 0x02); // EVENT_BUFFER_SIZE bytes
#define	PD_SCI_Event_In_Index  (*((uint8_t *)(SCI_Qevent_Ctrl+0x0010)))							//( SCI_Qevent_Ctrl + 0x10);
#define	PD_SCI_Event_Out_Index (*((uint8_t *)(SCI_Qevent_Ctrl+0x0011)))							//( SCI_Qevent_Ctrl + 0x11);
#define	PD_SCI_Event_Buffer    (*((uint8_t (*)[PENDING_BUFFER])(SCI_Qevent_Ctrl+0x0012)))		//( SCI_Qevent_Ctrl + 0x12); // PENDING_BUFFER bytes
//===============================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define HSPI_ReLoadHSPIRamCode  BIT0    // 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//===============================================================================

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x800-0x8FF   OEM RAM 8  
//-------------------------------------------------------------------------------
//*******************************************************************************
#if 1   //UCSI_SUPPORT
#define UCSI_MemBase OEMRAM8 + 0x0000
//**********************************
// UCSI PPM Service Resources
//**********************************
#define xUCSI_I2C_RD_BUFF			(*((uint8_t (*)[32])(UCSI_MemBase+0x0000)))
#define xUCSI_I2C_WR_BUFF			(*((uint8_t (*)[32])(UCSI_MemBase+0x0020)))
#define xUCSI_GET_CAPABILITY		(*((uint8_t (*)[16])(UCSI_MemBase+0x0040)))
#define xUCSI_Mode					(*((uint8_t *)(UCSI_MemBase+0x0050)))
#define F_UCSI_VIRTUAL                  BIT7
#define xUCSI_ppm_ready				(*((uint8_t *)(UCSI_MemBase+0x0051)))
#define F_UCSI_VERSION                  BIT0
#define F_UCSI_PD_CHIP_READY1           BIT1
#define F_UCSI_PD_CHIP_READY2           BIT2
#define F_UCSI_PD_CHIP_READY3           BIT3
#define F_UCSI_PD_CHIP_READY4           BIT4
#define F_UCSI_PD_CHIP_READY5           BIT5
#define F_UCSI_PD_CHIP_READY6           BIT6
#define F_UCSI_PD_CHIP_READY7           BIT7
#define xUCSI_command_received		(*((uint8_t *)(UCSI_MemBase+0x0052)))
#define xUCSI_PPM_State				(*((uint8_t *)(UCSI_MemBase+0x0053)))
#define ENABLE_PD_Step				(*((uint8_t *)(UCSI_MemBase+0x0054)))
#define xUCSI_EventDelay			(*((uint8_t *)(UCSI_MemBase+0x0055)))
#define wUCSI_ppm_timeout			(*((uint16_t *)(UCSI_MemBase+0x0056)))
#define xUCSI_in_progress			(*((uint8_t *)(UCSI_MemBase+0x0058)))
#define xUCSI_AsyncDelay			(*((uint8_t *)(UCSI_MemBase+0x0059)))
#define xUCSI_I2C_ADDR				(*((uint8_t *)(UCSI_MemBase+0x005S)))
#define xUCSI_I2C_BYTECNT			(*((uint8_t *)(UCSI_MemBase+0x005B)))
#define xUCSI_Connector_Number		(*((uint8_t *)(UCSI_MemBase+0x005C)))
#define xUCSI_NotificationEnable0	(*((uint8_t *)(UCSI_MemBase+0x005D)))
#define xUCSI_NotificationEnable1	(*((uint8_t *)(UCSI_MemBase+0x005E)))

#define UCP1_MemBase OEMRAM8 + 0x0060
#define xUCSI_Port1ConnStatus0		(*((uint8_t *)(UCP1_MemBase+0x0000)))
#define xUCSI_Port1ConnStatus1		(*((uint8_t *)(UCP1_MemBase+0x0001)))
#define xUCSI_Port1ConnCapability0	(*((uint8_t *)(UCP1_MemBase+0x0002)))
#define xUCSI_Port1ConnCapability1	(*((uint8_t *)(UCP1_MemBase+0x0003)))
#define xUCSI_Port1Event0			(*((uint8_t *)(UCP1_MemBase+0x0004)))
#define xUCSI_Port1Event1			(*((uint8_t *)(UCP1_MemBase+0x0005)))
#define xUCSI_NotifyEvent0			(*((uint8_t *)(UCP1_MemBase+0x0006)))
#define xUCSI_NotifyEvent1			(*((uint8_t *)(UCP1_MemBase+0x0007)))
#define xUCSI_NotifyEvent0r			(*((uint8_t *)(UCP1_MemBase+0x0008)))
#define xUCSI_NotifyEvent1r			(*((uint8_t *)(UCP1_MemBase+0x0009)))

//**********************************
// UCSI Port#1 Service Resources
//**********************************
#define TIPD1_MemBase OEMRAM8 + 0x0070
#define xTIPD1_i2c_error			(*((uint8_t *)(TIPD1_MemBase+0x0000)))
#define xTIPD1_service_delay		(*((uint8_t *)(TIPD1_MemBase+0x0001)))
#define xTIPD1_poll_step			(*((uint8_t *)(TIPD1_MemBase+0x0002)))
#define xTIPD1_poll_pdo_delay		(*((uint8_t *)(TIPD1_MemBase+0x0003)))


#define xTIPD1_STATUS				(*((uint8_t (*)[6])(TIPD1_MemBase+0x0010)))
#define xTIPD1_POWER_STATUS			(*((uint8_t (*)[3])(TIPD1_MemBase+0x0017)))
#define xTIPD1_EVENT				(*((uint8_t (*)[11])(TIPD1_MemBase+0x001A)))
#define xTIPD1_UCSI_CONN_STS		(*((uint8_t (*)[10])(TIPD1_MemBase+0x0030)))


//**********************************
// UCSI Port#2 Service Resources
//**********************************
#define TIPD2_MemBase OEMRAM8 + 0x00B0
#define xTIPD2_i2c_error			(*((uint8_t *)(TIPD2_MemBase+0x0000)))
#define xTIPD2_service_delay		(*((uint8_t *)(TIPD2_MemBase+0x0001)))
#define xTIPD2_poll_step			(*((uint8_t *)(TIPD2_MemBase+0x0002)))
#define xTIPD2_poll_pdo_delay		(*((uint8_t *)(TIPD2_MemBase+0x0003)))
#define xTIPD2_pd_watt				(*((uint8_t *)(TIPD2_MemBase+0x0005)))
#define xTIPD2_pd_mV				(*((uint8_t *)(TIPD2_MemBase+0x0006)))
#define xTIPD2_pd_mA				(*((uint8_t *)(TIPD2_MemBase+0x0008)))
#define xTIPD2_STATUS				(*((uint8_t (*)[6])(TIPD2_MemBase+0x0010)))
#define xTIPD2_POWER_STATUS			(*((uint8_t (*)[3])(TIPD2_MemBase+0x0017)))
#define xTIPD2_EVENT				(*((uint8_t (*)[11])(TIPD2_MemBase+0x001A)))
#define xTIPD2_UCSI_CONN_STS		(*((uint8_t (*)[10])(TIPD2_MemBase+0x0030)))

#define xTIFW_Step					(*((uint8_t *)(TIPD2_MemBase+0x0040)))
#define xTIFW_States				(*((uint8_t *)(TIPD2_MemBase+0x0041)))
#define F_TIFW_Finish					BIT7
#define xTIFW_Custuse			    (*((uint8_t (*)[8])(TIPD2_MemBase+0x0042)))	
#define xTIFW_Version			    (*((uint8_t (*)[4])(TIPD2_MemBase+0x004A)))	
#define xTIFW_Bin_Size			    (*((uint16_t *)(TIPD2_MemBase+0x004E)))

#endif  //UCSI_SUPPORT
//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x900-0x9FF   OEM RAM 9  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define SPIBuffer			    (*((uint8_t (*)[256])(OEMRAM9+0x004E)))

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xA00-0xAFF   OEM RAM A  
//-------------------------------------------------------------------------------
//*******************************************************************************

#define BAT_ALARM1					(*((uint16_t *)(OEMRAMA+0x0000)))       //0xA00
//======================================
#define SMBerror0    	       BIT0
#define SMBerror1              BIT1
#define SMBerror2              BIT2
#define SMBerror3              BIT3
#define FullyDsg               BIT4
#define FullyChg               BIT5
#define Dsg                    BIT6
#define Initialized            BIT7

#define BAT_ALARM2					(*((uint8_t *)(OEMRAMA+0x0001)))       //0xA01
//======================================
#define RemTime_alarm          BIT0
#define RemCap_alarm 	         BIT1
//       ;
#define TermDsg_alarm 	       BIT3
#define OverTemp_alarm	       BIT4
//       ;
#define TermChg_alarm 	       BIT6
#define OverChg_alarm          BIT7

#define BatPollingStep				(*((uint8_t *)(OEMRAMA+0x0004)))   //0xA04
#define BAT_INFO_STEP				(*((uint8_t *)(OEMRAMA+0x0005)))    //0xA05
//===========================================================================
// Battery data temperary buffer
//===========================================================================
//Battery A
#define BAT_RMCAPTEMP				(*((uint16_t *)(OEMRAMA+0x0010)))    //0x410      
#define BAT_DSNCAPLWTEMP			(*((uint16_t *)(OEMRAMA+0x0012))) //0x412      
#define BAT_RATETEMP				(*((uint16_t *)(OEMRAMA+0x0014)))     //0x414     
#define BAT_LFCCAPTEMP				(*((uint16_t *)(OEMRAMA+0x0016)))   //0x416      
#define BATCAP90					(*((uint16_t *)(OEMRAMA+0x0018)))         //0x418
#define BATCAP98					(*((uint16_t *)(OEMRAMA+0x001A)))         //0x41A
#define BATCAP35 					(*((uint16_t *)(OEMRAMA+0x001C)))     //0x41C
#define BATCAP55					(*((uint16_t *)(OEMRAMA+0x001E)))				//0x1E
#define BATCAP99					(*((uint16_t *)(OEMRAMA+0x0020)))
//extern uint16_t BATCAP10;         //0x41E
//extern uint16_t BATCAP95;         //0x420

#define BATLEDSTS					(*((uint16_t *)(OEMRAMA+0x0022)))        //0x422
//======================================
#define blink                  BIT0
#define on                     BIT1
#define off                    BIT2
//======================================
#define xTIPD1_pd_watt2             (*((uint8_t *)(OEMRAMA+0x0024)))        //0x422
//981004-121122-A-S
#define eEDPDATA00					(*((uint8_t *)(OEMRAMA+0x0030)))
#define eEDPDATA01					(*((uint8_t *)(OEMRAMA+0x0031)))
#define eEDPDATA03					(*((uint8_t *)(OEMRAMA+0x0032)))
#define eEDPDATA04					(*((uint8_t *)(OEMRAMA+0x0033)))
#define eEDPDATA06					(*((uint8_t *)(OEMRAMA+0x0034)))
#define eEDPDATA07					(*((uint8_t *)(OEMRAMA+0x0035)))
#define eEDPDATA08					(*((uint8_t *)(OEMRAMA+0x0036)))
#define eEDPDATA0C					(*((uint8_t *)(OEMRAMA+0x0037)))
#define eEDPDATA10					(*((uint8_t *)(OEMRAMA+0x0038)))
#define eEDPDATA12					(*((uint8_t *)(OEMRAMA+0x0039)))
#define eEDPDATA14					(*((uint8_t *)(OEMRAMA+0x003A)))
#define eEDPDATA1C					(*((uint8_t *)(OEMRAMA+0x003B)))
#define eEDPDATA20					(*((uint8_t *)(OEMRAMA+0x003C)))
#define eEDPDATA2D					(*((uint8_t *)(OEMRAMA+0x003D)))
#define eEDPDATA32					(*((uint8_t *)(OEMRAMA+0x003E)))
#define eEDPDATA35					(*((uint8_t *)(OEMRAMA+0x003F)))
#define eEDPDATA40					(*((uint8_t *)(OEMRAMA+0x0040)))
#define eEDPDATA41					(*((uint8_t *)(OEMRAMA+0x0041)))
#define eEDPDATA44					(*((uint8_t *)(OEMRAMA+0x0042)))
#define eEDPDATA4C					(*((uint8_t *)(OEMRAMA+0x0043)))
#define eEDPDATA56					(*((uint8_t *)(OEMRAMA+0x0044)))
#define eEDPDATA60					(*((uint8_t *)(OEMRAMA+0x0045)))
#define eEDPDATA80					(*((uint8_t *)(OEMRAMA+0x0046)))
#define eEDPDATA91					(*((uint8_t *)(OEMRAMA+0x0047)))
#define eEDPDATA92					(*((uint8_t *)(OEMRAMA+0x0048)))
#define eEDPDATAB0					(*((uint8_t *)(OEMRAMA+0x0049)))
#define eEDPDATAF8					(*((uint8_t *)(OEMRAMA+0x004A)))
#define eEDPDATAFD					(*((uint8_t *)(OEMRAMA+0x004B)))
//981004-121122-A-E


#define xPORT_FW_VER				(*((uint8_t (*)[8])(OEMRAMA+0x0050)))	 //981004-211119-A

#define xDATA_STS				    (*((uint8_t (*)[5])(OEMRAMA+0x0064)))	 //981004-211119-A


//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xB00-0xBFF   OEM RAM B  
//-------------------------------------------------------------------------------
//*******************************************************************************
//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xC00-0xCFF   OEM RAM C  
//-------------------------------------------------------------------------------
//*******************************************************************************

//981004-200721-A-S
/*****************************************************************************/
/* EXTERNAL RAM AREA      (0x0C00 ~ 0x0CFF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define xMSBY_Mode					(*((uint8_t *)(OEMRAMC+0x0000)))
#define xMSBY_SleepCounter			(*((uint8_t *)(OEMRAMC+0x0001)))
#define xMSBY_DozeCounter			(*((uint8_t *)(OEMRAMC+0x0002)))
#define xMSBY_ServiceKey			(*((uint8_t *)(OEMRAMC+0x0003)))
#define xMSBY_ExitKey				(*((uint8_t *)(OEMRAMC+0x0004)))
#define xMSBY_EnLidOpenWake			(*((uint8_t *)(OEMRAMC+0x0005)))
#define xMSBY_SleepDelay			(*((uint8_t *)(OEMRAMC+0x0006)))
#define xMSBY_GetBatteryStep		(*((uint8_t *)(OEMRAMC+0x0007)))
#define xMSBY_GetThermalStep		(*((uint8_t *)(OEMRAMC+0x0008)))
#define wMSBY_SLP_S0_LoT			(*((uint16_t *)(OEMRAMC+0x0010)))
#define wMSBY_SLP_S0_HiT			(*((uint16_t *)(OEMRAMC+0x0012)))
#define wMSBY_EnterDelay			(*((uint16_t *)(OEMRAMC+0x0014)))

//981004-200721-A-E

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xD00-0xDFF   OEM RAM D  //TI PD FLASH
//-------------------------------------------------------------------------------
//*******************************************************************************
//981004-220208-A-S
#if 1   //SUPPORT_TI_PD_APP_UPDATE
#define xAPP_PD_EnterUpdate		(*((uint8_t *)(OEMRAMD+0x0000)))
#define xAPP_PD_UpdStep			(*((uint8_t *)(OEMRAMD+0x0001)))
#define xAPP_PD_UpdStepFinish	(*((uint8_t *)(OEMRAMD+0x0002)))
#define xTIFW_OUID				(*((uint8_t(*)[8])(OEMRAMD+0x0003)))
#define xTIFW_4K_Size			(*((uint8_t *)(OEMRAMD+0x000B)))
#define xTIFW_CMD_Step			(*((uint8_t *)(OEMRAMD+0x000C)))
#define xTIFW_Erase_Step		(*((uint8_t *)(OEMRAMD+0x000D)))

#define xNewRegPointer			(*((uint16_t *)(OEMRAMD+0x0010)))
#define xNewRegStart			(*((uint16_t *)(OEMRAMD+0x0012)))
#define xAppConfigOffset		(*((uint16_t *)(OEMRAMD+0x0014)))
#define xOldRegPointer			(*((uint16_t *)(OEMRAMD+0x0016)))
#define xOldRegStart			(*((uint16_t *)(OEMRAMD+0x0018)))
#define xAPP_BIN_Buffer			(*((uint8_t (*)[34])(OEMRAMD+0x0020)))
#endif
//981004-220208-A-E
//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xE00-0xEFF   OEM RAM E  //RAMDEBUG
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xF00-0xFFF   OEM RAM F  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x9100-0x91FF //981004-231030-A
//-------------------------------------------------------------------------------
//*******************************************************************************
#if 1	//UCSI_SUPPORT
//**********************************
// UCSI PPM Service Resources - Main Service Code Resources
//**********************************
#define UCSI_PPMBase                0x20050E00//0x9100
#define   xUCSI_ppm_step              (*((uint8_t *)(UCSI_PPMBase+0x0000))) //_at_ UCSI_PPMBase + 0x00;
#define   xUCSI_init                  (*((uint8_t *)(UCSI_PPMBase+0x0001))) //_at_ UCSI_PPMBase + 0x01;
#define   xUCSI_opm_cmd_ready         (*((uint8_t *)(UCSI_PPMBase+0x0002))) //_at_ UCSI_PPMBase + 0x02;
#define   xUCSI_i2c_fail              (*((uint8_t *)(UCSI_PPMBase+0x0003))) //_at_ UCSI_PPMBase + 0x03;
#define   wUCSI_task_running          (*((uint16_t *)(UCSI_PPMBase+0x0004))) //_at_ UCSI_PPMBase + 0x04; 

//**********************************
// ITE PD Flash Utility //981004-211015-A 
//**********************************
#define PDFU_MemBase               0x20050E10// 0x9160
#define   xITEPD_FlashUtilityEnable   (*((uint8_t *)(PDFU_MemBase+0x0000))) //_at_ PDFU_MemBase + 0x00;
#define   xITEPD_FlashUtilityCmd      (*((uint8_t *)(PDFU_MemBase+0x0001))) //_at_ PDFU_MemBase + 0x01;
#define   xITEPD_FlashUtilityCmd2     (*((uint8_t *)(PDFU_MemBase+0x0002))) //_at_ PDFU_MemBase + 0x02;
#define   xITEPD_FlashUtilityCmd3     (*((uint8_t *)(PDFU_MemBase+0x0003))) //_at_ PDFU_MemBase + 0x03;
#define   xITEPD_FlashUtilityAck      (*((uint8_t *)(PDFU_MemBase+0x0004))) //_at_ PDFU_MemBase + 0x04;

//**********************************
// PD Port#1 Reg.Service Resources
//**********************************
#define ECPD1_MemBase              0x20050E20 //0x9170
#define   xPD1_i2c_addr              (*((uint8_t *)(ECPD1_MemBase+0x0000))) // _at_ ECPD1_MemBase + 0x00;
#define   xPD1_i2c_error             (*((uint8_t *)(ECPD1_MemBase+0x0001))) // _at_ ECPD1_MemBase + 0x01;
#define   xPD1_pd_mVoltage           (*((uint16_t *)(ECPD1_MemBase+0x0002))) // _at_ ECPD1_MemBase + 0x02;
#define   xPD1_pd_mCurrent           (*((uint16_t *)(ECPD1_MemBase+0x0004))) // _at_ ECPD1_MemBase + 0x04;
#define   xPD1_pd_mWatt              (*((uint16_t *)(ECPD1_MemBase+0x0006))) // _at_ ECPD1_MemBase + 0x06;
#define   xPD1_pd_Voltage            (*((uint8_t *)(ECPD1_MemBase+0x0008))) // _at_ ECPD1_MemBase + 0x08;
#define   xPD1_pd_Current            (*((uint8_t *)(ECPD1_MemBase+0x0009))) // _at_ ECPD1_MemBase + 0x09;
#define   xPD1_pd_PowWatt            (*((uint8_t *)(ECPD1_MemBase+0x000A))) // _at_ ECPD1_MemBase + 0x0A;
#define   xPD1_int_service           (*((uint8_t *)(ECPD1_MemBase+0x000B))) // _at_ ECPD1_MemBase + 0x0B;
#define   xPD1_BIN_VERSION           (*((uint8_t (*)[4])(ECPD1_MemBase+0x0010))) // _at_ ECPD1_MemBase + 0x10;
#define   xPD1_FW_VERSION            (*((uint8_t (*)[2])(ECPD1_MemBase+0x0014))) // _at_ ECPD1_MemBase + 0x14;
#define   xPD1_fw_update             (*((uint8_t *)(ECPD1_MemBase+0x0016))) // _at_ ECPD1_MemBase + 0x16;

//**********************************
// UCSI Port#2 Reg.Service Resources
//**********************************
#define ECPD2_MemBase             	0x20050E40//0x91B0
#define  xPD2_i2c_addr              (*((uint8_t *)(ECPD2_MemBase+0x0000))) // _at_ ECPD2_MemBase + 0x00;
#define  xPD2_i2c_error             (*((uint8_t *)(ECPD2_MemBase+0x0001))) // _at_ ECPD2_MemBase + 0x01;
#define  xPD2_pd_mVoltage           (*((uint16_t *)(ECPD2_MemBase+0x0002))) // _at_ ECPD2_MemBase + 0x02;
#define  xPD2_pd_mCurrent           (*((uint16_t *)(ECPD2_MemBase+0x0004))) // _at_ ECPD2_MemBase + 0x04;
#define  xPD2_pd_mWatt              (*((uint16_t *)(ECPD2_MemBase+0x0006))) // _at_ ECPD2_MemBase + 0x06;
#define  xPD2_pd_Voltage            (*((uint8_t *)(ECPD2_MemBase+0x0008))) // _at_ ECPD2_MemBase + 0x08;
#define  xPD2_pd_Current            (*((uint8_t *)(ECPD2_MemBase+0x0009))) // _at_ ECPD2_MemBase + 0x09;
#define  xPD2_pd_PowWatt            (*((uint8_t *)(ECPD2_MemBase+0x000A))) // _at_ ECPD2_MemBase + 0x0A;
#define  xPD2_int_service           (*((uint8_t *)(ECPD2_MemBase+0x000B))) // _at_ ECPD2_MemBase + 0x0B;
#define  xPD2_BIN_VERSION           (*((uint8_t (*)[4])(ECPD2_MemBase+0x0010))) // _at_ ECPD2_MemBase + 0x10;
#define  xPD2_FW_VERSION            (*((uint8_t (*)[2])(ECPD2_MemBase+0x0014))) // _at_ ECPD2_MemBase + 0x14;
#define  xPD2_fw_update             (*((uint8_t *)(ECPD2_MemBase+0x0016))) // _at_ ECPD2_MemBase + 0x16;
#endif  //UCSI_SUPPORT
//981004-210831-A-E
//981004-140806-A-S
//-----------------------------------------------------------------------------
/*****************************************************************************/
/* BRAM AREA      (0x2280 ~ 0x22BF) ******************************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
#define BRAM_MemBase                0x2200
//-----------------------------------------------------------------------------
//extern uint8_t    MBX_EC_MAIN_VER;
//extern uint8_t    MBX_EC_SUB_VER;
//extern uint8_t    MBX_EC_TEST_VER;
//extern ECBRAM uint8_t RESERVED_BRAM00[16];        //  0x00        _at_ BRAM_MemBase+0x10;
//981004-190109-M-S
#define MBX_CPU_TEMP            (*((uint8_t *)(40005000+0x0010)))
#define MBX_GPU_TEMP            (*((uint8_t *)(40005000+0x0011)))

#define MBX_CPU_FAN_FLAG        (*((uint8_t *)(40005000+0x0012)))
#define MBX_CPU_FAN_RPMH        (*((uint8_t *)(40005000+0x0013)))
#define MBX_CPU_FAN_RPML        (*((uint8_t *)(40005000+0x0014)))

#define MBX_GPU_FAN_FLAG        (*((uint8_t *)(40005000+0x0015)))
#define MBX_GPU_FAN_RPMH        (*((uint8_t *)(40005000+0x0016)))
#define MBX_GPU_FAN_RPML        (*((uint8_t *)(40005000+0x0017)))

#if 0
extern uint8_t    MBX_EC_DEV_CMD;
extern uint8_t    MBX_EC_SYS_FLAG;
extern uint8_t    MBX_EC_BRIGHTNESS;
extern uint8_t    MBX_EC_LIGHTSENSOR;
extern uint8_t    MBX_EC_DEV_CTL1;
extern uint8_t    MBX_EC_DEV_STS2;
extern uint8_t    MBX_EC_DEV_KEY;
#endif
//981004-190109-M-E
#if 0
//-----------------------------------------------------------------------------
//#define MBX_MemBase                 0x2280
//-----------------------------------------------------------------------------
extern uint8_t    MBX_STS;
extern uint8_t    MBX_CMD[];
extern uint8_t    MBX_DATA[];
#endif
//981004-180104-R-E

extern uint8_t BAT_TX_BUF[4];
extern uint8_t BAT_RX_BUF[4];
	
//#define PowerSequnceRAM ((*uint8_t*))ACPI_AREA +0x10    

extern void RAM_debug(uint8_t num);
extern void Clear_Ram(uint32_t* ptr, uint16_t size);
#endif

#endif
