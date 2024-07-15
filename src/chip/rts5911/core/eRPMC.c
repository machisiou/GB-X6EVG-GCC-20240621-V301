#include "system/Type.h"
#include "system/Memory.h"
#include "hal/eRPMC.h"
#include "hal/SPIC.h"
#include "chip/rts5911/RTS5911.h"
#include "md.h"

#if Support_ESPI_ERPMC

static uint8_t wr_root_key_done;
static uint8_t hmac_update_done;

unsigned int MCdata[4];
static unsigned int MCIDX[4];
static unsigned int MCHI[4];

static unsigned char rootkey[32] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
								0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

static uint8_t __attribute__ ((aligned(4))) eRPMC_BUF[256];

static unsigned char HMAC_Storage_0[32];
static unsigned char HMAC_Storage_1[32];
static unsigned char HMAC_Storage_2[32];
static unsigned char HMAC_Storage_3[32];

void Initial_OOB4eRPMC(void)
{
/////////////PUT_OOB from master for eRPMC////////////
	//while(ESPI->OOB_CONFIG.BITS.OOB_en == 0x0);
	ESPI->EORXBUF = (volatile uint32_t)OOB_IN_BUF;
	//while(ESPI->EOSTS_b.RXDONE ==0x0);
}

uint8_t ESPI_ERPMC(void)
{
	volatile uint8_t result;
	volatile uint8_t oob_tx_en=0;
	volatile uint8_t incrMC = 0;
	volatile uint8_t wrRK = 0;
	MST_ERPMC_HEADER_Type *ERPMC_Header;

/////////////PUT_OOB from master for eRPMC////////////
	//while(ESPI->OOB_CONFIG.BITS.OOB_en == 0x0);
	//ESPI->EORXBUF = (volatile uint32_t)OOB_IN_BUF;
	//while(ESPI->EOSTS_b.RXDONE ==0x0);

	ERPMC_Header = (MST_ERPMC_HEADER_Type *)(&OOB_IN_BUF[0]);

/////////////Check OOB eRPMC command////////////
	if(ERPMC_Header->Opcode == 0x9B)
	{
		if(ERPMC_Header->CmdType == 0x00)   //Write Root Key
		{
//			printf("Write Root Key \n");
			if((ERPMC_Header->Byte10.BITS.EOM ==1) && (ERPMC_Header->Byte10.BITS.SOM ==1))
			{
				result = eRPMCWriteRootKey(&OOB_IN_BUF[0]);

				wr_root_key_done = 1;
				ERPMC_Response(&OOB_OUT_BUF[0], &OOB_IN_BUF[0],result);
				
				ESPI->EOTXLEN = 0x0B;
				oob_tx_en = 1;
				wrRK = 1;
			}
			else
			{
//				printf("Write Root Key trauncated \n");
				eRPMCWriteRootKey_buffer(&OOB_IN_BUF[0],&OOB_IN_BUF_1[0],&eRPMC_BUF[0]);
				result = eRPMCWriteRootKey(&eRPMC_BUF[0]);

				wr_root_key_done = 1;
				ERPMC_Response(&OOB_OUT_BUF[0], &eRPMC_BUF[0],result);

				ESPI->EOTXLEN = 0x0B;
				oob_tx_en = 1;
				eRPMC_tx = 1;
				wrRK = 1;
			}
		}
		else if(ERPMC_Header->CmdType == 0x01)   // Upadte HMAC Key
		{
			result = UpdateHMACKey(&OOB_IN_BUF[0]);
			ERPMC_Response(&OOB_OUT_BUF[0], &OOB_IN_BUF[0],result);
			ESPI->EOTXLEN = 0x0B;
			oob_tx_en = 1;
			if(result == 0x80)
				hmac_update_done = 1;
		}
		else if(ERPMC_Header->CmdType == 0x02)
		{
			result = IncreMonotonicCounter(&OOB_IN_BUF[0]);
			ERPMC_Response(&OOB_OUT_BUF[0], &OOB_IN_BUF[0],result);
			
			ESPI->EOTXLEN = 0x0B;
			oob_tx_en = 1;
			if(result == 0x80)
				incrMC = 1;

		}
		else if(ERPMC_Header->CmdType == 0x03)
		{
			result = ReqMonotonicCounter(&OOB_IN_BUF[0]);

//			if(result) //signature error
//				ERPMC_SLV_REQ_Response(&OOB_OUT_BUF[0], &OOB_IN_BUF[0],0x04);
//			else   //success
				ERPMC_SLV_REQ_Response(&OOB_OUT_BUF[0], &OOB_IN_BUF[0],result);
			
			ESPI->EOTXLEN = 0x3B;
			oob_tx_en = 1;
		}
	}
	else	if(ERPMC_Header->Opcode == 0x9F)
	{
		ERPMC_Parameter_Response(&OOB_OUT_BUF[0], &OOB_IN_BUF[0],0x80);
		ESPI->EOTXLEN = 0x11;
		oob_tx_en = 1;
	}

	if(incrMC)
	{
			MST_INCREMENT_MC_Type *ERPMC_DATA;
			ERPMC_DATA = (MST_INCREMENT_MC_Type *)(&OOB_IN_BUF[0]);
			AddMC(ERPMC_DATA->header.CounterAddr,&VFLASH);
	}

	if(wrRK)
	{
		SPIC_Erase(0, GigaDev, 1);

//		printf("Block Erase Done \n");
		/*
		for(i=4096;i<8188;i++)
		{
			*((&VFLASH) + i) = 0;
		}
		*/
		SPIC_AutoMode();

		*((&VFLASH) + 8189) = 0;
		*((&VFLASH) + 8190) = 0;
		*((&VFLASH) + 8191) = 0;
		*((&VFLASH) + 0x2000 +8189) = 0;
		*((&VFLASH) + 0x2000 + 8190) = 0;
		*((&VFLASH) + 0x2000 + 8191) = 0;
		*((&VFLASH) + 0x4000 + 8189) = 0;
		*((&VFLASH) + 0x4000 + 8190) = 0;
		*((&VFLASH) + 0x4000 + 8191) = 0;
		*((&VFLASH) + 0x6000 + 8189) = 0;
		*((&VFLASH) + 0x6000 + 8190) = 0;
		*((&VFLASH) + 0x6000 + 8191) = 0;
		wrRK = 0;
		ESPI->EORXINTEN_b.RXEN = 0x1;
	}

	ESPI->EOSTS_b.RXDONE = 0x1;
	ESPI->EOTXBUF = (volatile uint32_t)OOB_OUT_BUF;
	ESPI->EOTXINTEN = 0x1;
	if(oob_tx_en)
		ESPI->EOTXCTRL_b.TXSTR = 0x1;

	return 1;
}

uint8_t eRPMCWriteRootKey(uint8_t *data)
{
//	printf("Start Write Root Key \n");
	int ret,i;
	volatile uint8_t result=0;
	MST_WRITE_ROOT_KEY_Type *ERPMC_DATA;
	ERPMC_DATA = (MST_WRITE_ROOT_KEY_Type *)data;
	const unsigned char message[] = {ERPMC_DATA->header.Opcode,
																	 ERPMC_DATA->header.CmdType,
																	 ERPMC_DATA->header.CounterAddr,
																	 ERPMC_DATA->header.Rsvd};
	//unsigned char rx_root_key[32];

	for(i=0;i<=31;i++)
	{
		rootkey[i] = ERPMC_DATA->RootKey[i];
	}

	unsigned char Signature[32];
	const mbedtls_md_info_t* const md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
	ret = mbedtls_md_hmac(md_info,&rootkey[0],sizeof(rootkey),&message[0],sizeof(message),&Signature[0]);
	
	if(ERPMC_DATA->header.CounterAddr > 3)
	{
		result |= 0x02;
	}

	for(i=0;i<=27;i++)
	{
		if(Signature[i+4] != ERPMC_DATA->TruncatedSignature[i])
		{
			result |= 0x04;
			break;
		}
	}
//result bit7 (no error)
//result bit1 (root key overwrite / counter address out of range)
//result bit2 (sign. mismatch)
	if(result == 0)
		result = 0x80;
	
	return result;
}

void eRPMCWriteRootKey_buffer(uint8_t *data0, uint8_t *data1, uint8_t *buffer)
{
	int i;

	for(i=0;i<72;i++)
	{
		*(buffer + i) = *(data0 + i);
	}

	*(buffer + 72) = *(data1 + 9);
	*(buffer + 73) = *(data1 + 10);
}


void ERPMC_Parameter_Response(uint8_t *data_rsp ,uint8_t *data_header ,uint8_t status)
{
	MST_ERPMC_HEADER_Type *ERPMC_Header;
	SLV_PARAMETER_RESPONSE_Type *ERPMC_RSP;
	ERPMC_Header = (MST_ERPMC_HEADER_Type *)data_header;
	ERPMC_RSP = (SLV_PARAMETER_RESPONSE_Type *)data_rsp;
	ERPMC_RSP->DestSlvAddr.BITS.DestSlvAddr = 0x08;
	ERPMC_RSP->DestSlvAddr.BITS.Bit0 = 0x0;
	ERPMC_RSP->CommandCode = 0x0F;
	ERPMC_RSP->ByteCount = 0x0F;
	ERPMC_RSP->SrcSlvAddr.BITS.SrcSlvAddr = 0x07;
	ERPMC_RSP->SrcSlvAddr.BITS.Bit0 = 0x1;
	ERPMC_RSP->MCTP_Ver.BITS.MCTPReserved = 0x0;
	ERPMC_RSP->MCTP_Ver.BITS.HeaderVersion = 0x01;
	ERPMC_RSP->DestEndpointID = ERPMC_Header->SrcEndpointID;
	ERPMC_RSP->SrcEndpointID = ERPMC_Header->DestEndpointID;
	ERPMC_RSP->Byte10.CHAR = 0xC0;//ERPMC_Header->Byte10.CHAR;
	ERPMC_RSP->MSGType.BITS.IC = 0x0;
	ERPMC_RSP->MSGType.BITS.MSGType = 0x7D;
	ERPMC_RSP->Extended_status = status;
	ERPMC_RSP->Parameter_table.BITS.Num_RPMC = 1;
	ERPMC_RSP->Parameter_table.BITS.Doc_ver = 0;
	ERPMC_RSP->Num_counter = 3;
	ERPMC_RSP->OP1 = 0x9B;
	ERPMC_RSP->Parameter_table_RPMC_dev_3.BITS.Update_rate = 0;
	ERPMC_RSP->Parameter_table_RPMC_dev_3.BITS.RPMC_dev = 0;
	ERPMC_RSP->Parameter_table_RPMC_dev_3.BITS.MC_size = 0;
	ERPMC_RSP->Parameter_table_RPMC_dev_3.BITS.SHA_size = 0;
	ERPMC_RSP->Parameter_table_RPMC_dec_reserved = 0;
	ERPMC_RSP->Parameter_table_resv[0] = 0;
	ERPMC_RSP->Parameter_table_resv[1] = 0;
	ERPMC_RSP->Parameter_table_resv[2] = 0;
}

void ERPMC_Response(uint8_t *data_rsp ,uint8_t *data_header ,uint8_t status)
{
	MST_ERPMC_HEADER_Type *ERPMC_Header;
	SLV_NORMAL_RESPONSE_Type *ERPMC_RSP;
	ERPMC_Header = (MST_ERPMC_HEADER_Type *)data_header;
	ERPMC_RSP = (SLV_NORMAL_RESPONSE_Type *)data_rsp;
	ERPMC_RSP->DestSlvAddr.BITS.DestSlvAddr = 0x08;
	ERPMC_RSP->DestSlvAddr.BITS.Bit0 = 0x0;
	ERPMC_RSP->CommandCode = 0x0F;
	ERPMC_RSP->ByteCount = 0x09;
	ERPMC_RSP->SrcSlvAddr.BITS.SrcSlvAddr = 0x07;
	ERPMC_RSP->SrcSlvAddr.BITS.Bit0 = 0x1;
	ERPMC_RSP->MCTP_Ver.BITS.MCTPReserved = 0x0;
	ERPMC_RSP->MCTP_Ver.BITS.HeaderVersion = 0x01;
	ERPMC_RSP->DestEndpointID = ERPMC_Header->SrcEndpointID;
	ERPMC_RSP->SrcEndpointID = ERPMC_Header->DestEndpointID;
	ERPMC_RSP->Byte10.CHAR = 0xC0;//ERPMC_Header->Byte10.CHAR;
	ERPMC_RSP->MSGType.BITS.IC = 0x0;
	ERPMC_RSP->MSGType.BITS.MSGType = 0x7D;
	ERPMC_RSP->RPMCDevice = ERPMC_Header->RPMCDevice;
	ERPMC_RSP->CounterAddr = ERPMC_Header->CounterAddr;
	ERPMC_RSP->ExtendedStatus = status;
}

void ERPMC_SLV_REQ_Response(uint8_t *data_rsp ,uint8_t *data_header ,uint8_t status)
{
	int i,ret;
	MST_REQ_MC_Type *ERPMC_REQ_MCHeader;
	SLV_REQ_MC_Type *ERPMC_RSP;
	ERPMC_REQ_MCHeader = (MST_REQ_MC_Type *)data_header;
	ERPMC_RSP = (SLV_REQ_MC_Type *)data_rsp;
	ERPMC_RSP->DestSlvAddr.BITS.DestSlvAddr = 0x08;
	ERPMC_RSP->DestSlvAddr.BITS.Bit0 = 0x0;
	ERPMC_RSP->CommandCode = 0x0F;
	ERPMC_RSP->ByteCount = 0x39;
	ERPMC_RSP->SrcSlvAddr.BITS.SrcSlvAddr = 0x07;
	ERPMC_RSP->SrcSlvAddr.BITS.Bit0 = 0x1;
	ERPMC_RSP->MCTP_Ver.BITS.MCTPReserved = 0x0;
	ERPMC_RSP->MCTP_Ver.BITS.HeaderVersion = 0x01;
	ERPMC_RSP->DestEndpointID = ERPMC_REQ_MCHeader->header.SrcEndpointID;//ERPMC_Header->SrcEndpointID;
	ERPMC_RSP->SrcEndpointID = ERPMC_REQ_MCHeader->header.DestEndpointID;//ERPMC_Header->DestEndpointID;
	ERPMC_RSP->Byte10.CHAR = 0xC0;//ERPMC_REQ_MCHeader->header.Byte10.CHAR;
	ERPMC_RSP->MSGType.BITS.IC = 0x0;
	ERPMC_RSP->MSGType.BITS.MSGType = 0x7D;
	ERPMC_RSP->RPMCDevice = ERPMC_REQ_MCHeader->header.RPMCDevice;
	ERPMC_RSP->CounterAddr = ERPMC_REQ_MCHeader->header.CounterAddr;
	ERPMC_RSP->ExtendedStatus = status;
	for(i=0;i<=11;i++)
	{
		ERPMC_RSP->Tag[i] = ERPMC_REQ_MCHeader->Tag[i];
	}
	
	//MONOTONIC->Ctrl.BITS.LOAD = 1;
	Load_MC(&VFLASH);
	/////////////Should replace for real MC/////////////
	if(ERPMC_REQ_MCHeader->header.CounterAddr == 0)
	{
		ERPMC_RSP->CounterReadData[0] = (uint8_t)(MCdata[0] >> 24);
		ERPMC_RSP->CounterReadData[1] = (uint8_t)(MCdata[0] >> 16);
		ERPMC_RSP->CounterReadData[2] = (uint8_t)(MCdata[0] >> 8);
		ERPMC_RSP->CounterReadData[3] = (uint8_t)(MCdata[0]);
	}
	else if(ERPMC_REQ_MCHeader->header.CounterAddr == 1)
	{
		ERPMC_RSP->CounterReadData[0] = (uint8_t)(MCdata[1] >> 24);
		ERPMC_RSP->CounterReadData[1] = (uint8_t)(MCdata[1] >> 16);
		ERPMC_RSP->CounterReadData[2] = (uint8_t)(MCdata[1] >> 8);
		ERPMC_RSP->CounterReadData[3] = (uint8_t)(MCdata[1]);
	}
	else if(ERPMC_REQ_MCHeader->header.CounterAddr == 2)
	{
		ERPMC_RSP->CounterReadData[0] = (uint8_t)(MCdata[2] >> 24);
		ERPMC_RSP->CounterReadData[1] = (uint8_t)(MCdata[2] >> 16);
		ERPMC_RSP->CounterReadData[2] = (uint8_t)(MCdata[2] >> 8);
		ERPMC_RSP->CounterReadData[3] = (uint8_t)(MCdata[2] );
	}
	else if(ERPMC_REQ_MCHeader->header.CounterAddr == 3)
	{
		ERPMC_RSP->CounterReadData[0] = (uint8_t)(MCdata[3] >> 24);
		ERPMC_RSP->CounterReadData[1] = (uint8_t)(MCdata[3] >> 16);
		ERPMC_RSP->CounterReadData[2] = (uint8_t)(MCdata[3] >> 8);
		ERPMC_RSP->CounterReadData[3] = (uint8_t)(MCdata[3]);
	}
	
	const mbedtls_md_info_t* const md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
	
	const unsigned char message[] = { ERPMC_RSP->Tag[0],
																		ERPMC_RSP->Tag[1],
																		ERPMC_RSP->Tag[2],
																		ERPMC_RSP->Tag[3],
																		ERPMC_RSP->Tag[4],
																		ERPMC_RSP->Tag[5],
																		ERPMC_RSP->Tag[6],
																		ERPMC_RSP->Tag[7],
																		ERPMC_RSP->Tag[8],
																		ERPMC_RSP->Tag[9],
																		ERPMC_RSP->Tag[10],
																		ERPMC_RSP->Tag[11],
																		ERPMC_RSP->CounterReadData[0],
																		ERPMC_RSP->CounterReadData[1],
																		ERPMC_RSP->CounterReadData[2],
																		ERPMC_RSP->CounterReadData[3]
																		};
	unsigned char Signature[32];

	if(ERPMC_REQ_MCHeader->header.CounterAddr == 0)
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_0[0],sizeof(HMAC_Storage_0),&message[0],sizeof(message),&Signature[0]);
	else if(ERPMC_REQ_MCHeader->header.CounterAddr == 1)
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_1[0],sizeof(HMAC_Storage_1),&message[0],sizeof(message),&Signature[0]);
	else if(ERPMC_REQ_MCHeader->header.CounterAddr == 2)
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_2[0],sizeof(HMAC_Storage_2),&message[0],sizeof(message),&Signature[0]);
	else
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_3[0],sizeof(HMAC_Storage_3),&message[0],sizeof(message),&Signature[0]);

//	if(ret == 0)
	{
		for(i=0;i<32;i++)
		{
			//printf("Signature[%x] = %x \n",i,Signature[i]);
			ERPMC_RSP->Signature[i] = Signature[i];
		}
	}

}


uint8_t UpdateHMACKey(uint8_t *data)
{
	//struct Flash_Type TestFlash;
	uint8_t result=0x80;
	int ret,i;
	unsigned char Signature[32];
	MST_UPDATE_HMAC_KEY_Type *ERPMC_DATA;
	ERPMC_DATA = (MST_UPDATE_HMAC_KEY_Type *)data;

	// Operation 1 output

//	printf("Update HMAC\n");

//	if(wr_root_key_done)
	{
		// Key data 4 Bytes
		//const unsigned char KeyData[] = {0x00,0x11,0x22,0x33};
		const mbedtls_md_info_t* const md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
		// non string use
		if(ERPMC_DATA->header.CounterAddr == 0x0)
			ret = mbedtls_md_hmac(md_info,&rootkey[0],sizeof(rootkey),&(ERPMC_DATA->KeyData[0]),sizeof(ERPMC_DATA->KeyData),&HMAC_Storage_0[0]);
		else if(ERPMC_DATA->header.CounterAddr == 0x1)
			ret = mbedtls_md_hmac(md_info,&rootkey[0],sizeof(rootkey),&(ERPMC_DATA->KeyData[0]),sizeof(ERPMC_DATA->KeyData),&HMAC_Storage_1[0]);
		else if(ERPMC_DATA->header.CounterAddr == 0x2)
			ret = mbedtls_md_hmac(md_info,&rootkey[0],sizeof(rootkey),&(ERPMC_DATA->KeyData[0]),sizeof(ERPMC_DATA->KeyData),&HMAC_Storage_2[0]);
		else
			ret = mbedtls_md_hmac(md_info,&rootkey[0],sizeof(rootkey),&(ERPMC_DATA->KeyData[0]),sizeof(ERPMC_DATA->KeyData),&HMAC_Storage_3[0]);

		if(ret == 0)
		{
//			printf("Counter Address = %x \n",ERPMC_DATA->header.CounterAddr);
			/*
			if(ERPMC_DATA->header.CounterAddr == 0x0)
				for(i=0;i<32;i++)
					printf("HMAC_Storage[%x] = %x \n",i,HMAC_Storage_0[i]);
			else if(ERPMC_DATA->header.CounterAddr == 0x1)
				for(i=0;i<32;i++)
					printf("HMAC_Storage[%x] = %x \n",i,HMAC_Storage_1[i]);
			else if(ERPMC_DATA->header.CounterAddr == 0x2)
				for(i=0;i<32;i++)
					printf("HMAC_Storage[%x] = %x \n",i,HMAC_Storage_2[i]);
			else if(ERPMC_DATA->header.CounterAddr == 0x3)
				for(i=0;i<32;i++)
					printf("HMAC_Storage[%x] = %x \n",i,HMAC_Storage_3[i]);
			*/
		}

		// Operation 2 output

		const unsigned char message[] = {ERPMC_DATA->header.Opcode,
																		 ERPMC_DATA->header.CmdType,
																		 ERPMC_DATA->header.CounterAddr,
																		 ERPMC_DATA->header.Rsvd,
																		 ERPMC_DATA->KeyData[0],
																		 ERPMC_DATA->KeyData[1],
																		 ERPMC_DATA->KeyData[2],
																		 ERPMC_DATA->KeyData[3]};

		if(ERPMC_DATA->header.CounterAddr == 0x0)
			ret = mbedtls_md_hmac(md_info,&HMAC_Storage_0[0],sizeof(HMAC_Storage_0),&message[0],sizeof(message),&Signature[0]);
		else if(ERPMC_DATA->header.CounterAddr == 0x1)
			ret = mbedtls_md_hmac(md_info,&HMAC_Storage_1[0],sizeof(HMAC_Storage_1),&message[0],sizeof(message),&Signature[0]);
		else if(ERPMC_DATA->header.CounterAddr == 0x2)
			ret = mbedtls_md_hmac(md_info,&HMAC_Storage_2[0],sizeof(HMAC_Storage_2),&message[0],sizeof(message),&Signature[0]);
		else
			ret = mbedtls_md_hmac(md_info,&HMAC_Storage_3[0],sizeof(HMAC_Storage_3),&message[0],sizeof(message),&Signature[0]);
/*
		if(ret == 0)
		{
			for(i=0;i<32;i++)
			{
				printf("Signature[%x] = %x \n",i,Signature[i]);
			}
		}
		*/
	}
	for(i=0;i<32;i++)
	{
		if(Signature[i] != ERPMC_DATA->Signature[i])
			result=0x4;    //Sign. mismatch
	}
	
	if((ERPMC_DATA->header.CounterAddr > 3) || (ERPMC_DATA->header.CmdType > 3))
		result=0x4;

//	printf("Update HMAC finish\n");
	return result;
}

uint8_t IncreMonotonicCounter(uint8_t *data)
{
//	printf("Start Increase Monotonic counter \n");
	int ret,i;
	uint8_t result=0;
//	uint32_t rx_cnt_data;
	MST_INCREMENT_MC_Type *ERPMC_DATA;
	ERPMC_DATA = (MST_INCREMENT_MC_Type *)data;
	const unsigned char message[] = {ERPMC_DATA->header.Opcode,
																	 ERPMC_DATA->header.CmdType,
																	 ERPMC_DATA->header.CounterAddr,
																	 ERPMC_DATA->header.Rsvd,
																	 ERPMC_DATA->CounterData[0],
																	 ERPMC_DATA->CounterData[1],
																	 ERPMC_DATA->CounterData[2],
																	 ERPMC_DATA->CounterData[3]};
	unsigned char Signature[32];
	const mbedtls_md_info_t* const md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);

	if(ERPMC_DATA->header.CounterAddr == 0x0)
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_0[0],sizeof(HMAC_Storage_0),&message[0],sizeof(message),&Signature[0]);
	else if(ERPMC_DATA->header.CounterAddr == 0x1)
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_1[0],sizeof(HMAC_Storage_1),&message[0],sizeof(message),&Signature[0]);
	else if(ERPMC_DATA->header.CounterAddr == 0x2)
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_2[0],sizeof(HMAC_Storage_2),&message[0],sizeof(message),&Signature[0]);
	else
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_3[0],sizeof(HMAC_Storage_3),&message[0],sizeof(message),&Signature[0]);
/*
	if(ret == 0)
	{
		for(i=0;i<32;i++)
		{
			printf("Signature[%x] = %x \n",i,Signature[i]);
		}
	}
*/
	/*
	rx_cnt_data = (uint32_t) (ERPMC_DATA->CounterData[3] | (ERPMC_DATA->CounterData[2]<<8) | (ERPMC_DATA->CounterData[1]<<16) | (ERPMC_DATA->CounterData[0]<<24));
	
	if(rx_cnt_data != MCdata[ERPMC_DATA->header.CounterAddr])
	{
		result |= 0x10;
	}
		*/
	
	for(i=0;i<32;i++)
	{
		if(Signature[i] != ERPMC_DATA->Signature[i])
			result |= 0x4;
	}
	if(ERPMC_DATA->header.CounterAddr > 0x3)
	{
		result |= 0x4;
	}
	
	if(hmac_update_done != 1)
		result |= 0x08;
	
	if(result == 0)
	{
		if(ERPMC_DATA->header.CounterAddr == 0)
		{
			MCdata[0]++;
//			printf("MC0= %d \n",(uint32_t)MCdata[0]);
		}
		else if(ERPMC_DATA->header.CounterAddr == 1)
		{
			MCdata[1]++;
//			printf("MC1= %d \n",(uint32_t)MCdata[1]);
		}
		else if(ERPMC_DATA->header.CounterAddr == 2)
		{
			MCdata[2]++;
//			printf("MC2= %d \n",(uint32_t)MCdata[2]);
		}
		else if(ERPMC_DATA->header.CounterAddr == 3)
		{
			MCdata[3]++;
//			printf("MC3= %d \n",(uint32_t)MCdata[3]);
		}
	}

//	printf("Increase Monotonic counter finish\n");
	
//result bit7 (no error)
//result bit2 (sign. mismatch)
//result bit3 (HMAC KEY no update)
//result bit4 (Monotonic counter mis match)

	if(result == 0)
		result = 0x80;

	return result;
}

uint8_t ReqMonotonicCounter(uint8_t *data)
{
//	printf("Start request Monotonic counter \n");

	uint8_t result=0;
	MST_REQ_MC_Type *ERPMC_DATA;
	ERPMC_DATA = (MST_REQ_MC_Type *)data;
	int ret,i;

	const mbedtls_md_info_t* const md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);

	const unsigned char message[] = {ERPMC_DATA->header.Opcode,
																	 ERPMC_DATA->header.CmdType,
																	 ERPMC_DATA->header.CounterAddr,
																	 ERPMC_DATA->header.Rsvd,
																	 ERPMC_DATA->Tag[0],
																	 ERPMC_DATA->Tag[1],
																	 ERPMC_DATA->Tag[2],
																	 ERPMC_DATA->Tag[3],
																	 ERPMC_DATA->Tag[4],
																	 ERPMC_DATA->Tag[5],
																	 ERPMC_DATA->Tag[6],
																	 ERPMC_DATA->Tag[7],
																	 ERPMC_DATA->Tag[8],
																	 ERPMC_DATA->Tag[9],
																	 ERPMC_DATA->Tag[10],
																	 ERPMC_DATA->Tag[11]};
	unsigned char Signature[32];

	if(ERPMC_DATA->header.CounterAddr == 0)																	 
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_0[0],sizeof(HMAC_Storage_0),&message[0],sizeof(message),&Signature[0]);
	else if(ERPMC_DATA->header.CounterAddr == 1)																	 
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_1[0],sizeof(HMAC_Storage_1),&message[0],sizeof(message),&Signature[0]);
	else if(ERPMC_DATA->header.CounterAddr == 2)																	 
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_2[0],sizeof(HMAC_Storage_2),&message[0],sizeof(message),&Signature[0]);
	else
		ret = mbedtls_md_hmac(md_info,&HMAC_Storage_3[0],sizeof(HMAC_Storage_3),&message[0],sizeof(message),&Signature[0]);

	for(i=0;i<32;i++)
	{
		if(Signature[i] != ERPMC_DATA->Signature[i])
		{
			result |= 0x04;
			break;
		}
	}

	//	if((hmac_update_done != 1) || (wr_root_key_done != 1))
	if(hmac_update_done != 1)
	{
		result |= 0x08;
	}

	if(result == 0x00)
		result = 0x80;
//	printf("Request Monotonic counter finish \n");
	return result;
}

void AddMC(volatile uint8_t MC_num,uint8_t *addr)
{
	uint8_t *data;
	uint8_t *MC_addr;
	unsigned int HIword;

	MC_addr = addr+8192*MC_num;

	data = MC_addr + MCIDX[MC_num];

	//////////Low word +1/////////
	if(*data != 0x00)
			*data <<= 1;				//write 1 bit0 +1
	else
	{
		if(MCIDX[MC_num] < 8188)
		{
			if(MCIDX[MC_num] == 4095)	////determin counting to last address of 1st sector of MC
			{
				////////First sector of MC erase//////
				SPIC_Erase((uint32_t) MC_addr, GigaDev, 0);
				SPIC_AutoMode();
			}
			MCIDX[MC_num]++;
			data = MC_addr + MCIDX[MC_num];
			*data <<= 1;
		}
		else
		{
			//////////erase & Hi word +1/////////
			MCHI[MC_num] ++;
			HIword = MCHI[MC_num];     //////keep Hi word +1 in buffer
			SPIC_Erase((uint32_t) MC_addr + 4096, GigaDev, 0);
			SPIC_AutoMode();
			/////////Write buffer back to the Hi word storage space
			*(MC_addr + 8189) = (volatile uint8_t) (HIword >> 16);
			*(MC_addr + 8190) = (volatile uint8_t) (HIword >> 8);
			*(MC_addr + 8191) = (volatile uint8_t) HIword;
		}
	}
	
}

void Load_MC(uint8_t *addr)
{
	uint8_t MC_num;
	uint8_t *MC_addr;
	unsigned int i;
	unsigned int left,right,m;

	for(MC_num=0;MC_num<4;MC_num++)
	{
		MC_addr = addr+8192*MC_num;
		//////////Determine the bit counting sector//////////////
		if(*(MC_addr+4096)!=0xFF)
		{
			left = 4096;
			right = 8188;
			i=4095;
		}
		else
		{
			left = 0;
			right = 4095;
			i=8188;
		}
		//////////Searching Low word non-written address/////////
		while(left != 4092)
		{
			m = (left+right)/2;
			if(*(MC_addr+m) == 0xFF)
				right = m;
			else
				left = m;

			if((left == right))
			{
				i = m;
				break;
			}
			if(left == right-1)
			{
				i = right;
				break;
			}
		}

		if(i>0 && *(MC_addr + i -1)!=0)
		{
			i--;
		}
		MCIDX[MC_num] = i;

		/////////Dtermine Hi word number/////////////
		MCHI[MC_num] = (unsigned int) ((*(MC_addr  + 8189) << 16) + (*(MC_addr + 8190) << 8) + (*(MC_addr + 8191)));
		if(MCHI[MC_num] == 0x00FFFFFF)
		{
			MCHI[MC_num] = 0;
		}
		////////Determine MC value//////////////////
			MCdata[MC_num] = (MCHI[MC_num] * 65513) + ((MCIDX[MC_num])*8)  + Byte2Bit_LUT(*(MC_addr+i));
	}
//	printf("MCdata[0] = %d\n",MCdata[0]);

}

uint8_t Byte2Bit_LUT(uint8_t data)
{
	volatile uint8_t BitCNT;
	BitCNT = (data == 0xFF) ? 0 :
			(data == 0xFE) ? 1 :
			(data == 0xFC) ? 2 :
			(data == 0xF8) ? 3 :
			(data == 0xF0) ? 4 :
			(data == 0xE0) ? 5 :
			(data == 0xC0) ? 6 :
			(data == 0x80) ? 7 : 8 ;
	return BitCNT;
}

#endif
