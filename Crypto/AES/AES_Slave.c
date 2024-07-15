#include "Include.h"

// Slave mode
// ECB
void ProcessECBmode(const DWORD* Testkey, const DWORD* InData, DWORD* OutData, UINT8 EnDecrp)
{
	//printf("AES->DATAIN0 = %x\n", *InData);
	//printf("AES->DATAIN1 = %x\n", *(InData+1));
	//printf("AES->DATAIN2 = %x\n", *(InData+2));
	//printf("AES->DATAIN3 = %x\n", *(InData+3));

	AES->DATAIN0 = *InData;
	AES->DATAIN1 = *(InData+1);
	AES->DATAIN2 = *(InData+2);
	AES->DATAIN3 = *(InData+3);

	AES->KEY0 = *Testkey;
	AES->KEY1 = *(Testkey+1);
	AES->KEY2 = *(Testkey+2);
	AES->KEY3 = *(Testkey+3);

	// Slave mode
	AES->CONF_b.MODE = 0;
	// ECB mode
	AES->CONF_b.CIPHERMD = 0;
	// Key size = 128
	AES->CONF_b.KEYSIZE = 0;
	// Encryption
	AES->CONF_b.DECRYPT = EnDecrp;

	printf("AES->CONF_b.DECRYPT = %x\n", AES->CONF_b.DECRYPT);

	AES->CONF_b.DEKEYGEN = 1;
	// Swap
	//AES->Config.BITS.Byte_swap = 1;
	// Start run
	AES->CONF_b.FIRSTBLK = 1;

	while(!AES->INTRAW_b.SLVDONE)
	{
		printf("AES is in process\n");
	}
	printf("AES complete\n");
	// Clear interrupt
	AES->INTCLR_b.AESINTCLR =1;

	//printf("AES->DATAOUT0 = %lx\n", AES->DATAOUT0);
	//printf("AES->DATAOUT1 = %lx\n", AES->DATAOUT1);
	//printf("AES->DATAOUT2 = %lx\n", AES->DATAOUT2);
	//printf("AES->DATAOUT3 = %lx\n", AES->DATAOUT3);

	*OutData = AES->DATAOUT0;
	*(OutData+1) = AES->DATAOUT1;
	*(OutData+2) = AES->DATAOUT2;
	*(OutData+3) = AES->DATAOUT3;


}

// CBC
void ProcessCBCmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp)
{
	AES->DATAIN0 = *InData;
	AES->DATAIN1 = *(InData+1);
	AES->DATAIN2 = *(InData+2);
	AES->DATAIN3 = *(InData+3);

	AES->KEY0 = *Testkey;
	AES->KEY1 = *(Testkey+1);
	AES->KEY2 = *(Testkey+2);
	AES->KEY3 = *(Testkey+3);

	//printf("AES->IV0 = %x\n", *Iv);
	//printf("AES->IV1 = %x\n", *(Iv+1));
	//printf("AES->IV2 = %x\n", *(Iv+2));
	//printf("AES->IV3 = %x\n", *(Iv+3));


	AES->IV0 = *Iv;
	AES->IV1 = *(Iv+1);
	AES->IV2 = *(Iv+2);
	AES->IV3 = *(Iv+3);

	// Slave mode
	AES->CONF_b.MODE = 0;
	// CBC mode
	AES->CONF_b.CIPHERMD = 1;
	// Key size = 128
	AES->CONF_b.KEYSIZE = 0;
	// Encryption
	AES->CONF_b.DECRYPT = EnDecrp;

	printf("AES->CONF_b.DECRYPT = %x\n", AES->CONF_b.DECRYPT);

	AES->CONF_b.DEKEYGEN = 1;
	// Swap
	//AES->Config.BITS.Byte_swap = 1;
	// Start run
	AES->CONF_b.FIRSTBLK = 1;

	while(!AES->INTRAW_b.SLVDONE)
	{
		printf("AES is in process\n");
	}
	printf("AES complete\n");

	//printf("AES->DATAOUT0 = %lx\n", AES->DATAOUT0);
	//printf("AES->DATAOUT1 = %lx\n", AES->DATAOUT1);
	//printf("AES->DATAOUT2 = %lx\n", AES->DATAOUT2);
	//printf("AES->DATAOUT3 = %lx\n", AES->DATAOUT3);

	*OutData = AES->DATAOUT0;
	*(OutData+1) = AES->DATAOUT1;
	*(OutData+2) = AES->DATAOUT2;
	*(OutData+3) = AES->DATAOUT3;

	// Clear interrupt
	AES->INTCLR_b.AESINTCLR =1;
}

// CFB
void ProcessCFBmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp)
{
	AES->DATAIN0 = *InData;
	AES->DATAIN1 = *(InData+1);
	AES->DATAIN2 = *(InData+2);
	AES->DATAIN3 = *(InData+3);

	AES->KEY0 = *Testkey;
	AES->KEY1 = *(Testkey+1);
	AES->KEY2 = *(Testkey+2);
	AES->KEY3 = *(Testkey+3);

	AES->IV0 = *Iv;
	AES->IV1 = *(Iv+1);
	AES->IV2 = *(Iv+2);
	AES->IV3 = *(Iv+3);

	// Slave mode
	AES->CONF_b.MODE = 0;
	// CFB mode
	AES->CONF_b.CIPHERMD = 2;
	// Key size = 128
	AES->CONF_b.KEYSIZE = 0;
	// Encryption
	AES->CONF_b.DECRYPT = EnDecrp;

	AES->CONF_b.DEKEYGEN = 1;
	// Swap
	//AES->Config.BITS.Byte_swap = 1;
	// Start run
	AES->CONF_b.FIRSTBLK = 1;

	while(!AES->INTRAW_b.SLVDONE)
	{
		printf("AES is in process\n");
	}
	printf("AES complete\n");

	//printf("AES->DATAOUT0 = %lx\n", AES->DATAOUT0);
	//printf("AES->DATAOUT1 = %lx\n", AES->DATAOUT1);
	//printf("AES->DATAOUT2 = %lx\n", AES->DATAOUT2);
	//printf("AES->DATAOUT3 = %lx\n", AES->DATAOUT3);

	*OutData = AES->DATAOUT0;
	*(OutData+1) = AES->DATAOUT1;
	*(OutData+2) = AES->DATAOUT2;
	*(OutData+3) = AES->DATAOUT3;

	// Clear interrupt
	AES->INTCLR_b.AESINTCLR =1;
}

// OFB
void ProcessOFBmode(const DWORD* Testkey, const DWORD* InData, const DWORD* Iv, DWORD* OutData, UINT8 EnDecrp)
{
	AES->DATAIN0 = *InData;
	AES->DATAIN1 = *(InData+1);
	AES->DATAIN2 = *(InData+2);
	AES->DATAIN3 = *(InData+3);

	AES->KEY0 = *Testkey;
	AES->KEY1 = *(Testkey+1);
	AES->KEY2 = *(Testkey+2);
	AES->KEY3 = *(Testkey+3);

	AES->IV0 = *Iv;
	AES->IV1 = *(Iv+1);
	AES->IV2 = *(Iv+2);
	AES->IV3 = *(Iv+3);

	// Slave mode
	
	AES->CONF_b.MODE = 0;
	// OFB mode
	AES->CONF_b.CIPHERMD = 3;
	// Key size = 128
	AES->CONF_b.KEYSIZE = 0;
	// Encryption
	AES->CONF_b.DECRYPT = EnDecrp;

	AES->CONF_b.DEKEYGEN = 1;
	// Swap
	//AES->Config.BITS.Byte_swap = 1;
	// Start run
	AES->CONF_b.FIRSTBLK = 1;

	while(!AES->INTRAW_b.SLVDONE)
	{
		printf("AES is in process\n");
	}
	printf("AES complete\n");

	//printf("AES->DATAOUT0 = %lx\n", AES->DATAOUT0);
	//printf("AES->DATAOUT1 = %lx\n", AES->DATAOUT1);
	//printf("AES->DATAOUT2 = %lx\n", AES->DATAOUT2);
	//printf("AES->DATAOUT3 = %lx\n", AES->DATAOUT3);

	*OutData = AES->DATAOUT0;
	*(OutData+1) = AES->DATAOUT1;
	*(OutData+2) = AES->DATAOUT2;
	*(OutData+3) = AES->DATAOUT3;
}


