#ifndef OEM_SMBUS_H
#define OEM_SMBUS_H

typedef struct _SMBUS_COMMAND_SET
{
	uint8_t           protocol;
	uint8_t           address;
	uint8_t           cmd;
	uint16_t           *smbdata;
	uint8_t           Conditionflag;
	uint8_t           *ConditionVar;
	FUNCT_PTR_V_V   hookfunc;
	FUNCT_PTR_V_V   errorfunc;
	uint8_t           Bcunt;
} SMBUS_COMMAND_SET;

typedef struct _I2C_COMMAND_SET
{
	uint16_t          WrLen;
	uint16_t          RdLen;
	FUNCT_PTR_V_V   hookfunc;
} I2C_COMMAND_SET;


typedef struct _SMBUS_CENTER_CONTROL
{
	uint8_t           *index;
	uint8_t           *timeout;
	uint8_t           *bytecount;
	uint8_t           *inusing;
	uint8_t           *tablesize;
	uint8_t           *serviceflag;
	FUNCT_PTR_V_V   servicefunc;
} SMBUS_CENTER_CONTROL;

typedef struct _THERMISTORTBL
{
	uint8_t 	        Level;
	uint8_t 	        TFanOn;
	uint8_t 	        TFanOff;
} THERMISTORTBL;

extern const SMBUS_CENTER_CONTROL SMBUS_CTRL_TBL[];
extern const SMBUS_COMMAND_SET SMBUS_CH0_TBL[];
extern const SMBUS_COMMAND_SET SMBUS_CH1_TBL[];
extern const SMBUS_COMMAND_SET SMBUS_CH2_TBL[];
extern const SMBUS_COMMAND_SET SMBUS_CH3_TBL[];

extern const I2C_COMMAND_SET I2C_CH0_TBL[];
extern const I2C_COMMAND_SET I2C_CH1_TBL[];
extern const I2C_COMMAND_SET I2C_CH2_TBL[];
extern const I2C_COMMAND_SET I2C_CH3_TBL[];

extern void SMBusMgr(void);
extern void SMBusDataSender(uint8_t);
extern void SMBusDataHandle(void);
extern void PollReadSMBusWord(uint8_t ch,uint8_t addr, uint8_t cmd);

extern void ProcessSMBus0(void);
extern void CheckSMBusTableSize(void);
#endif