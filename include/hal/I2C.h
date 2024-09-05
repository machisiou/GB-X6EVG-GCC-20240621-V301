#ifndef __I2C_H__
#define __I2C_H__
 
#include <stdint.h>
#include "system/Type.h"
#include "system/peripheral.h"

extern uint32_t g_i2c_slave_0_byte_write_index;
extern uint32_t g_i2c_slave_1_byte_write_index;
extern uint32_t g_i2c_slave_2_byte_write_index;
extern uint32_t g_i2c_slave_0_byte_read_index;
extern uint32_t g_i2c_slave_1_byte_read_index;
extern uint32_t g_i2c_slave_2_byte_read_index;

extern uint8_t *g_i2c_slave_2_byte_write_buffer_pointer;

typedef enum I2C_Mode_Type {
	I2C_Master,
	I2C_Slave,
} I2C_Mode;

typedef enum SMB_Frequency {
	_100KHz,
	_400KHz,
	_1MHz,
} SMB_Frequency;

typedef enum SMB_Protocol {
	QuickCommandWr,
	QuickCommandRd,
	SendByte,
	ReceiveByte,
	WriteByte,
	ReadByte,
	WriteWord,
	ReadWord,
	WriteBlock,
	ReadBlock,
} SMB_Protocol;

typedef enum _I2C_Protocol {
	I2CRead,
	I2CWrite,
} _I2C_Protocol;

extern void I2C_Initial(uint8_t Channel, uint8_t Frequency, uint8_t Mode, uint8_t SlvAddr);
extern uint8_t I2C_SMBusModProtocol(uint8_t Channel, uint8_t Protocol, uint8_t Addr, uint8_t DatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf);
extern uint8_t I2C_Protocol(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf);
extern uint8_t I2C_Slave_ByteRead (uint8_t Channel, uint8_t *RDatBuf);
extern uint8_t I2C_Slave_ByteWrite (uint8_t Channel, uint8_t *WDatBuf);
extern void I2C_Slave_2_Variables_Reset(void);
extern void I2C_Reset_Handler_Isr(uint8_t Channel);
extern uint8_t I2C_Timeout_Handler(I2C_Type* Ptr);
extern uint8_t I2C_ProtocolFIFO_W(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t *WDatBuf);
extern uint8_t I2C_ProtocolFIFO_R(uint8_t Channel, uint8_t Addr, uint8_t RDatCnt, uint8_t *RDatBuf);
extern uint8_t SMBUS_RW_W(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint16_t *var);
extern uint8_t SMBUS_RW_B(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var);
extern uint8_t SMBUS_RW_BLK(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint32_t *var);
extern uint8_t bRWSMBus(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var, uint8_t PECSupport);
extern uint8_t bWSMBusBlock(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var, uint8_t PECSupport);
extern uint8_t bRSMBusBlock(uint8_t Channel, uint8_t Protocol, uint8_t Addr ,uint8_t Cmd,uint8_t *var, uint8_t PECSupport);

#endif
