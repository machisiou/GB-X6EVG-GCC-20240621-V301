#ifndef __PERVW_H__
#define __PERVW_H__

#include "system/Type.h"
#include "system/peripheral.h"

typedef enum _RXIndex {
	INDEX2 = 0,
	INDEX3,
	INDEX7,
	INDEX41,
	INDEX42,
	INDEX43,
	INDEX47,
	INDEX4A,
	INDEX51,
	INDEX61,
} _RXIndex;

// define VW index2 bit
#define IDX2_BIT7_RESERVED					BIT7
#define IDX2_SLP_S5_VALID					BIT6
#define IDX2_SLP_S4_VALID					BIT5
#define IDX2_SLP_S3_VALID					BIT4
#define IDX2_BIT3_RESERVED					BIT3
#define IDX2_SLP_S5							BIT2
#define IDX2_SLP_S4							BIT1
#define IDX2_SLP_S3							BIT0

// define VW index3 bit
#define IDX3_BIT7_RESERVED					BIT7
#define IDX3_OOB_RST_WARN_VALID				BIT6
#define IDX3_PLTRST_VALID					BIT5
#define IDX3_SUS_STAT_VALID					BIT4
#define IDX3_BIT3_RESERVED					BIT3
#define IDX3_OOB_RST_WARN					BIT2
#define IDX3_PLTRST							BIT1
#define IDX3_SUS_STAT						BIT0

// define VW index4 bit
#define IDX4_PME_VALID						BIT7
#define IDX4_WAKE_VALID						BIT6
#define IDX4_BIT5_RESERVED					BIT5
#define IDX4_OOB_RST_ACK_VALID				BIT4
#define IDX4_PME							BIT3
#define IDX4_WAKE							BIT2
#define IDX4_BIT1_RESERVED					BIT1
#define IDX4_OOB_RST_ACK					BIT0

// define VW index5 bit
#define IDX5_SLAVE_BOOT_LOAD_STATUS_VALID	BIT7
#define IDX5_ERROR_NONFATAL_VALID			BIT6
#define IDX5_ERROR_FATAL_VALID				BIT5
#define IDX5_SLAVE_BOOT_LOAD_DONE_VALID		BIT4
#define IDX5_SLAVE_BOOT_LOAD_STATUS			BIT3
#define IDX5_ERROR_NONFATAL					BIT2
#define IDX5_ERROR_FATAL					BIT1
#define IDX5_SLAVE_BOOT_LOAD_DONE			BIT0

// define VW index6 bit
#define IDX6_HOST_RST_ACK_VALID				BIT7
#define IDX6_RCIN_VALID						BIT6
#define IDX6_SMI_VALID						BIT5
#define IDX6_SCI_VALID						BIT4
#define IDX6_HOST_RST_ACK					BIT3
#define IDX6_RCIN							BIT2
#define IDX6_SMI							BIT1
#define IDX6_SCI							BIT0

// define VW index7 bit
#define IDX7_BIT7_RESERVED					BIT7
#define IDX7_NMIOUT_VALID					BIT6
#define IDX7_SMIOUT_VALID					BIT5
#define IDX7_HOST_RST_WARN_VALID			BIT4
#define IDX7_BIT3_RESERVED					BIT3
#define IDX7_NMIOUT							BIT2
#define IDX7_SMIOUT							BIT1
#define IDX7_HOST_RST_WARN					BIT0

// define VW index40 bit
#define IDX40_SUSACK_VALID					BIT4
#define IDX40_SUSACK						BIT0

//define VW index41 bit
#define IDX41_SUS_WARN_VALID				BIT4
#define IDX41_SUS_WARN						BIT0

#define GetSlp_S5			IS_BIT_SET(ESPI->EVIDX2, IDX2_SLP_S5)
#define GetSlp_S4			IS_BIT_SET(ESPI->EVIDX2, IDX2_SLP_S4)
#define GetSlp_S3			IS_BIT_SET(ESPI->EVIDX2, IDX2_SLP_S3)
#define GetOOB_RST_WARN		IS_BIT_SET(ESPI->EVIDX3, IDX3_OOB_RST_WARN)
#define GetHOST_RST_WARN	IS_BIT_SET(ESPI->EVIDX7, IDX7_HOST_RST_WARN)
#define GetSus_warn			IS_BIT_SET(ESPI->EVIDX41, IDX41_SUS_WARN)

#define GetVWEnable			(IS_BIT_SET(ESPI->EVCFG, BIT0) && IS_BIT_SET(ESPI->EVCFG, BIT1))
#define GetVWTransSts		IS_BIT_SET(ESPI->EVSTS, BIT16)
#define SetVWTransclr		BIT_SET(ESPI->EVSTS, BIT16)
#define GetPLTRST			IS_BIT_SET(ESPI->EVIDX3, BIT1)

#define SetSCIHigh		VW_Set_Index(0x06, 0x17)
#define SetSCILow		VW_Set_Index(0x06, 0x16)
#define SetSMIHigh		VW_Set_Index(0x06, 0x27)
#define SetSMILow		VW_Set_Index(0x06, 0x25)
#define SetRCINHigh		VW_Set_Index(0x06, 0x47)
#define SetRCINLow		VW_Set_Index(0x06, 0x43)

extern void Perpheral_InitDMASrcAddr(uint32_t SrcAddr, uint32_t ComAddr);
extern uint8_t VW_Get_Index(uint8_t Index);
extern void VW_Set_Index(uint8_t Index, uint8_t Data);
extern void VW_Set_IntEn(_Bool RXChgEn, _Bool TXEmptyEn, _Bool VWConfigChg);
extern uint32_t VW_GetSts(void);
extern void VW_ClrSts(uint32_t ClrPos);
extern void VW_ResetSts(void);
#endif
