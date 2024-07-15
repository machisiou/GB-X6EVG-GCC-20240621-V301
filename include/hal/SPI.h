#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

extern void HSPI_BufCfg(uint32_t Tx_StartAddr, uint32_t Tx_Length, uint32_t Rx_StartAddr, uint32_t Rx_Length);
extern uint8_t MSPI_Set_CmdData(uint32_t CmdData0, uint32_t CmdData1,uint8_t DataLength);
extern uint8_t MSPI_Set_AddrData(uint32_t AddrData, uint8_t DataLength);
extern uint8_t MSPI_AutoModeSel(uint8_t Mode);
extern uint8_t MSPI_Config(uint8_t CS_IdleStatus, uint8_t LSBFirst, uint8_t SampleTiming);
extern void MSPI_Reset(void);
extern void MSPI_Divider(uint16_t DivValue);
extern uint8_t MSPI_Write_Data(uint32_t *TxBufAddr, uint8_t DataLenght);
extern uint8_t MSPI_Read_Data(uint32_t *RxBufAddr, uint8_t DataLenght);
extern void MSPI_Start(void);
extern void MSPI_Length(uint8_t Length);

#endif
