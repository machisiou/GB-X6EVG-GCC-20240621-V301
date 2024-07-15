#ifndef __eRPMC_H__
#define __eRPMC_H__

#include <stdint.h>
#include "system/Type.h"

#define Support_ESPI_ERPMC 1

#define MC_Sector		0x00   // depend on internal flash size
#define VFLASH			(*(uint8_t*)(0x60000000 + (MC_Sector  * 0x1000)))

extern void Initial_OOB4eRPMC(void);
extern uint8_t ESPI_ERPMC(void);
extern uint8_t eRPMCWriteRootKey(uint8_t *data);
extern void eRPMCWriteRootKey_buffer(uint8_t *data0, uint8_t *data1, uint8_t *buffer);
extern void ERPMC_Parameter_Response(uint8_t *data_rsp ,uint8_t *data_header ,uint8_t status);
extern void ERPMC_Response(uint8_t *data_rsp ,uint8_t *data_header ,uint8_t status);
extern void ERPMC_SLV_REQ_Response(uint8_t *data_rsp ,uint8_t *data_header ,uint8_t status);
extern uint8_t UpdateHMACKey(uint8_t *data);
extern uint8_t IncreMonotonicCounter(uint8_t *data);
extern uint8_t ReqMonotonicCounter(uint8_t *data);
extern void AddMC(volatile uint8_t MC_num,uint8_t *addr);
extern void Load_MC(uint8_t *addr);
extern uint8_t Byte2Bit_LUT(uint8_t data);

typedef struct
{
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t DestSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} DestSlvAddr;								//Byte 3
	uint8_t CommandCode;						//Byte 4
	uint8_t ByteCount;							//Byte 5
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t SrcSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} SrcSlvAddr;								//Byte 6
	union
	{
		struct
		{
			uint8_t HeaderVersion:4;
			uint8_t MCTPReserved:4;
		} BITS;
		uint8_t CHAR;
	} MCTP_Ver;									//Byte 7
	uint8_t DestEndpointID;						//Byte 8
	uint8_t SrcEndpointID;						//Byte 9
	union
	{
		struct
		{
			uint8_t MsgTag:3;
			uint8_t TO:1;
			uint8_t PacketSeq:2;
			uint8_t EOM:1;
			uint8_t SOM:1;
		} BITS;
		uint8_t CHAR;
	} Byte10;									//Byte 10
	union
	{
		struct
		{
			uint8_t MSGType:7;
			uint8_t IC:1;
		} BITS;
		uint8_t CHAR;
	} MSGType;									//Byte 11
	uint8_t RPMCDevice;							//Byte 12
	uint8_t Opcode;								//Byte 13
	uint8_t CmdType;							//Byte 14
	uint8_t CounterAddr;						//Byte 15
	uint8_t Rsvd;								//Byte 16
}MST_ERPMC_HEADER_Type;

typedef struct
{
	MST_ERPMC_HEADER_Type header;
	uint8_t RootKey[32];						//Byte 17~48
	uint8_t TruncatedSignature[28];				//Byte 49~76
}MST_WRITE_ROOT_KEY_Type;

typedef struct
{
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t DestSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} DestSlvAddr;								//Byte 3
	uint8_t CommandCode;						//Byte 4
	uint8_t ByteCount;							//Byte 5
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t SrcSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} SrcSlvAddr;								//Byte 6
	union
	{
		struct
		{
			uint8_t HeaderVersion:4;
			uint8_t MCTPReserved:4;
		} BITS;
		uint8_t CHAR;
	} MCTP_Ver;									//Byte 7
	uint8_t DestEndpointID;						//Byte 8
	uint8_t SrcEndpointID;						//Byte 9
	union
	{
		struct
		{
			uint8_t MsgTag:3;
			uint8_t TO:1;
			uint8_t PacketSeq:2;
			uint8_t EOM:1;
			uint8_t SOM:1;
		} BITS;
		uint8_t CHAR;
	} Byte10;									//Byte 10
	union
	{
		struct
		{
			uint8_t MSGType:7;
			uint8_t IC:1;
		} BITS;
		uint8_t CHAR;
	} MSGType;									//Byte 11
	uint8_t RPMCDevice;							//Byte 12
	uint8_t CounterAddr;						//Byte 13
	uint8_t ExtendedStatus;						//Byte 14
}SLV_NORMAL_RESPONSE_Type;

typedef struct
{
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t DestSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} DestSlvAddr;								//Byte 3
	uint8_t CommandCode;						//Byte 4
	uint8_t ByteCount;							//Byte 5
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t SrcSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} SrcSlvAddr;								//Byte 6
	union
	{
		struct
		{
			uint8_t HeaderVersion:4;
			uint8_t MCTPReserved:4;
		} BITS;
		uint8_t CHAR;
	} MCTP_Ver;									//Byte 7
	uint8_t DestEndpointID;						//Byte 8
	uint8_t SrcEndpointID;						//Byte 9
	union
	{
		struct
		{
			uint8_t MsgTag:3;
			uint8_t TO:1;
			uint8_t PacketSeq:2;
			uint8_t EOM:1;
			uint8_t SOM:1;
		} BITS;
		uint8_t CHAR;
	} Byte10;									//Byte 10
	union
	{
		struct
		{
			uint8_t MSGType:7;
			uint8_t IC:1;
		} BITS;
		uint8_t CHAR;
	} MSGType;									//Byte 11
	uint8_t Extended_status;					//Byte 12
	uint8_t Parameter_table_resv[3];			//Byte 13~15
	union
	{
		struct
		{
			uint8_t Num_RPMC:4;
			uint8_t Doc_ver:4;
		} BITS;
		uint8_t CHAR;
	} Parameter_table;							//Byte 16
	union
	{
		struct
		{
			uint8_t SHA_size:1;
			uint8_t MC_size:1;
			uint8_t RPMC_dev:2;
			uint8_t Update_rate:4;
		} BITS;
		uint8_t CHAR;
	} Parameter_table_RPMC_dev_3;				//Byte 17
	uint8_t Parameter_table_RPMC_dec_reserved;	//Byte 18
	uint8_t OP1;								//Byte 19
	uint8_t Num_counter;						//Byte 20
}SLV_PARAMETER_RESPONSE_Type;

typedef struct
{
	MST_ERPMC_HEADER_Type header;
	uint8_t KeyData[4];							//Byte 17~20
	uint8_t Signature[32];						//Byte 21~52
}MST_UPDATE_HMAC_KEY_Type;

typedef struct
{
	MST_ERPMC_HEADER_Type header;
	uint8_t CounterData[4];						//Byte 17~20
	uint8_t Signature[32];						//Byte 21~52
}MST_INCREMENT_MC_Type;

typedef struct
{
	MST_ERPMC_HEADER_Type header;
	uint8_t Tag[12];							//Byte 17~28
	uint8_t Signature[32];						//Byte 29~60
}MST_REQ_MC_Type;

typedef struct
{
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t DestSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} DestSlvAddr;								//Byte 3
	uint8_t CommandCode;						//Byte 4
	uint8_t ByteCount;							//Byte 5
	union
	{
		struct
		{
			uint8_t Bit0:1;
			uint8_t SrcSlvAddr:7;
		} BITS;
		uint8_t CHAR;
	} SrcSlvAddr;								//Byte 6
	union
	{
		struct
		{
			uint8_t HeaderVersion:4;
			uint8_t MCTPReserved:4;
		} BITS;
		uint8_t CHAR;
	} MCTP_Ver;									//Byte 7
	uint8_t DestEndpointID;						//Byte 8
	uint8_t SrcEndpointID;						//Byte 9
	union
	{
		struct
		{
			uint8_t MsgTag:3;
			uint8_t TO:1;
			uint8_t PacketSeq:2;
			uint8_t EOM:1;
			uint8_t SOM:1;
		} BITS;
		uint8_t CHAR;
	} Byte10;									//Byte 10
	union
	{
		struct
		{
			uint8_t MSGType:7;
			uint8_t IC:1;
		} BITS;
		uint8_t CHAR;
	} MSGType;									//Byte 11
	uint8_t RPMCDevice;							//Byte 12
	uint8_t CounterAddr;						//Byte 13
	uint8_t ExtendedStatus;						//Byte 14
	uint8_t Tag[12];							//Byte 15~26
	uint8_t CounterReadData[4];					//Byte 27~30
	uint8_t Signature[32];						//Byte 31~62
}SLV_REQ_MC_Type;

//extern uint8_t wr_root_key_done;
//extern uint8_t hmac_update_done;

//extern unsigned char rootkey[32];
//extern unsigned char HMAC_Storage_0[32];
//extern unsigned char HMAC_Storage_1[32];
//extern unsigned char HMAC_Storage_2[32];
//extern unsigned char HMAC_Storage_3[32];

#endif
