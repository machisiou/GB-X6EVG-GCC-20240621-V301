#ifndef __Oem_PECI_H__
#define __Oem_PECI_H__

extern void PECI_ClearTCVariables(void);
extern void PECI_ClearPowerSKUUnit(void);
extern uint8_t PECI_ReadPowerUnit(void);
extern uint8_t PECI_WritePowerLimit1(void);
extern uint8_t PECI_ReadPowerLimit1(void);
extern void PECI_ACToDCModeTurboCtrl(void);
extern void PECI_SETPL2Watts(uint8_t watts);
extern void PECI_WritePowerLimit2(uint8_t watts);
extern void PECI_ReadPowerLimit2(void);
extern void PECI_WritePowerLimit3(uint16_t watts);
extern void PECI_WritePowerLimit4(uint8_t watts); //981004-150925-A
extern void PECI_ReadPowerLimit3(void);
extern void PECI_ReadCPUTemp(void);
extern void PECI_ReadCPUTJMAX(void);
extern void PECI_ReadDRAMTemperature(void);
extern void PECI_ReadPkgTemperature(void);
extern void PECI_ReadMSRExample(void);
extern void PECI_CheckCurrentPlatformPower(void);
extern void PECI_ACTurboControlAlgorithm(void);
extern void ChecknSetAdaptorWatts(void);
extern void PECI_PowerCtrlCenter(void);
extern void SetPECIPowerCtrlStep(uint8_t step);

extern void ProcessPSTCmd(void);
extern void PECI_PSTIssueCmd(void);
extern void PECI_PSTEndCmd(void);
extern void PECI_PSTWriteBuffer(void);
extern void PECI_PSTReadBuffer(void);
extern void PECI_PSTReadErrorCount(void);
extern void PECI_PSTReadStatus(void);
extern void PECI_ClearPSTVariables(void);
extern void PECI_SendBufferData(void);

#define PECI_Index_PTR          2       // Package temperature read
#define PECI_Index_TTR          16      // Read the Maximum Allowed Processor Temperature
#define PECI_Index_DRCTR        22      // DRAM rank channel temperature read
#define PECI_Index_PPL1         26      // Power limit 1
#define PECI_Index_PPL2         27      // Power limit 2
#define PECI_Index_PPL3         57      // Power limit 3 //981004-150824-A
#define PECI_Index_PPL4         60      // Power limit 4 //981004-150824-A
#define PECI_Index_PPSU         28      // Power SKU unit
#define PECI_Index_PPSL         29      // Package power and time limit information
#define PECI_Index_PPSH         30      // Package power and time limit information

//-----------------------------------------------------------------------------
// Define processor Tjmax
//-----------------------------------------------------------------------------
#define PECI_CPU_Tjmax      100
#define PECI_Read_TjmaxTO   10      // Re-try to read CPU Tjmax via PECI

#define PECI_CPU_ADDR       0x30
#endif