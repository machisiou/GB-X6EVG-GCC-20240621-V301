#include "system/Memory.h"

KERNEL_AREA uint32_t TimeSlot;
KERNEL_AREA uint32_t SERVICEflag;
KERNEL_AREA uint8_t ECtime10;
KERNEL_AREA uint8_t ECtime100;
KERNEL_AREA uint16_t ECtime1000;
KERNEL_AREA uint16_t ECtime1M;
KERNEL_AREA uint16_t ECtime33m;
KERNEL_AREA uint8_t FnCnt;
KERNEL_AREA uint8_t NumLockCnt;
KERNEL_AREA uint8_t KBValidDebounceCnt;
KERNEL_AREA uint8_t KeyPress;
KERNEL_AREA uint8_t SentKeyCnt;
KERNEL_AREA uint8_t ScanIntrvl;
KERNEL_AREA uint16_t KBDelayCnt;
KERNEL_AREA uint16_t KBRepetCnt;
KERNEL_AREA uint32_t KSIData;
KERNEL_AREA uint8_t KbcDLen;
KERNEL_AREA uint8_t KbcCmd;
KERNEL_AREA uint8_t KbcData;
KERNEL_AREA uint8_t KbdCmd;
KERNEL_AREA uint8_t AcpiDLen;
KERNEL_AREA uint8_t AcpiCmd;
KERNEL_AREA uint8_t AcpiData;
KERNEL_AREA uint8_t AcpiData2;
KERNEL_AREA uint8_t pm0len;
KERNEL_AREA uint8_t pm0cmd;
KERNEL_AREA uint8_t pm0dat;
KERNEL_AREA uint8_t pm1len;
KERNEL_AREA uint8_t pm1cmd;
KERNEL_AREA uint8_t pm1dat;
KERNEL_AREA uint8_t pm2len;
KERNEL_AREA uint8_t pm2cmd;
KERNEL_AREA uint8_t pm2dat;
KERNEL_AREA uint8_t pm3len;
KERNEL_AREA uint8_t pm3cmd;
KERNEL_AREA uint8_t pm3dat;
KERNEL_AREA uint8_t KBDataQueueHead;
KERNEL_AREA uint8_t KBDataQueueTail;
KERNEL_AREA uint8_t KBDataQueue[KBDQUEUELEN];
KERNEL_AREA uint8_t SCIDataQueueHead;
KERNEL_AREA uint8_t SCIDataQueueTail;
KERNEL_AREA uint8_t SCIDataQueue[SCIDQLEN];
KERNEL_AREA uint8_t Pass_On;
KERNEL_AREA uint8_t Pass_Off;
KERNEL_AREA uint8_t Pass_Make1;
KERNEL_AREA uint8_t Pass_Make2;
KERNEL_AREA uint8_t Pass_Buff_Idx;
KERNEL_AREA uint8_t Main_MOUSE_CHN;
KERNEL_AREA uint8_t MSPending;
KERNEL_AREA uint8_t MS_ID_CUNT;
KERNEL_AREA uint8_t TPACKCounter;
KERNEL_AREA uint8_t TPResolution;
KERNEL_AREA uint8_t TPSamplingRate;
KERNEL_AREA uint8_t AUXPortNum;
KERNEL_AREA uint8_t Manual;
KERNEL_AREA uint8_t Temp_Load;
KERNEL_AREA uint8_t Pass_Buff[8];
KERNEL_AREA uint8_t KCCB42;
KERNEL_AREA uint8_t KBCodeSet;
KERNEL_AREA uint8_t KBTypematic;
KERNEL_AREA uint8_t MULPX;
KERNEL_AREA uint8_t KBFlag;
KERNEL_AREA uint8_t CustomFlags;
KERNEL_AREA uint8_t Led_Datas;
KERNEL_AREA uint8_t Gen_Info;
KERNEL_AREA uint8_t AuxFlags[3];
KERNEL_AREA uint8_t AuxTestFlagS;
KERNEL_AREA uint8_t VW_IDX4;
KERNEL_AREA uint8_t VW_IDX5;
KERNEL_AREA uint8_t VW_IDX6;
KERNEL_AREA uint8_t VW_IDX40;
KERNEL_AREA uint8_t eRPMCFlag;
KERNEL_AREA uint8_t eRPMCBuf;
KERNEL_AREA uint8_t eRPMC_tx;
KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_IN_BUF[256];
KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_IN_BUF_1[128];
KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_IN_EMPTY[128];
KERNEL_AREA uint8_t __attribute__ ((aligned(4))) OOB_OUT_BUF[256];
KERNEL_AREA uint8_t OOBNum;
KERNEL_AREA uint8_t RDPKGIdx;
uint8_t* Tmp_XPntr;
uint8_t* Tmp_XPntr1;
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ACPI_AREA uint8_t ACPIReserved[256]={0};

uint8_t   ITempB01;
uint8_t   ITempB02;
uint8_t   ITempB03;
uint8_t   ITempB04;
uint8_t   ITempB05;
uint8_t   ITempB06;
uint16_t  ITempW01;
uint16_t  ITempW02;
uint8_t   debug0;
uint8_t debug1;
uint8_t debug2;
uint8_t debug3;
uint32_t debug32_0;
uint32_t debug32_1;
uint8_t BAT_TX_BUF[4];
uint8_t BAT_RX_BUF[4];
uint8_t Pre_P80, Pre_P81 = 0;
// uint8_t CPUTemperature;
uint8_t __attribute__ ((aligned(4))) OOB_TX_BUF[32];
uint8_t __attribute__ ((aligned(4))) OOB_RX_BUF[32];
uint8_t WaitBack;

uint8_t OOBNum;

uint16_t CPUTemperature;
uint8_t CPUTjMax;
uint8_t CPUTDP6;
uint8_t CPUTDP7;
uint16_t FAN_RPM;
uint8_t BAT_bInfor_Count=0;
uint8_t SystemState;
uint8_t PwrSwDelay;
uint8_t PwrSequStep=0;
uint8_t PwrSequDly;
uint8_t BAT1VoltL;
uint8_t BAT1VoltH;
uint8_t BAT1RemainingCapaL;
uint8_t BAT1RemainingCapaH;
uint8_t BAT1FCCL;
uint8_t BAT1FCCH;
uint8_t BAT1ModeL;
uint8_t BAT1ModeH;
uint8_t BAT1StatusL;
uint8_t BAT1StatusH;
uint8_t BAT1CurrentL;
uint8_t BAT1CurrentH;
uint8_t BAT1DesignCapaL;
uint8_t BAT1DesignCapaH;
uint8_t BAT1DesignVoltL;
uint8_t BAT1DesignVoltH;

void RAM_debug(uint8_t num)
{
	DebugPage[DebugPtr++] = num;
	if(DebugPtr == 0x100)
		DebugPtr = 0;
}
