#include "system/Memory.h"
#include "hal/ESPI_OOB.h"
#include "chip/rts5911/RTS5911.h"
#include "oem/crb/Oem_timer.h"

 uint8_t OOB_PECI_Done;
 uint8_t OOB_PECI_valid;

void OOB_SetBuffer(uint8_t* WriteBuffer, uint8_t* ReadBuffer)
{
	ESPI->EOTXBUF = (uint32_t)WriteBuffer;
	ESPI->EORXBUF = (uint32_t)ReadBuffer;
}

/******************************************************************************/
/** Send OOB parameter
 * return Success
*******************************************************************************/
uint8_t OOB_Start_Head(uint8_t length)
{
    uint8_t passflag = 0;
    uint32_t trycount = 0;
    OOB_SetBuffer(OOB_OUT_BUF, OOB_IN_BUF); //setting TX/RX buffer
 
    length = length - 1;                    //Tx Length
    ESPI->EOTXLEN_b.LENGTH = length;        //set length
 
    #if Support_ESPI_ERPMC
    if (eRPMCFlag) {
        OOBNum = 0;
        return BUSY;
    } else {
        // ESPI->EOTXCTRL_b.TXSTR |= 1;         //start OOB ch transmit
        __disable_irq();
            ESPI->ELMSG = 0;
 
            ESPI->ELCTRL = 1;
            ESPI->EVTXDAT = 0x509;
 
            while (ESPI->EVSTS_b.TXFULL);
            ESPI->EVTXDAT = 0x509;
            ESPI->EOTXCTRL = 1;
        __enable_irq();
    }
    #else
    // ESPI->EOTXCTRL_b.TXSTR |= 1;         //start OOB ch transmit
    __disable_irq();
        ESPI->ELMSG = 0;
 
        ESPI->ELCTRL = 1;
        ESPI->EVTXDAT = 0x509;
 
        while (ESPI->EVSTS_b.TXFULL);
        ESPI->EVTXDAT = 0x509;
        ESPI->EOTXCTRL = 1;
    __enable_irq();
    #endif
    return SUCCESS;
}


/******************************************************************************/
/** get OOB return data
 * if return SUCCESS, data ready
 * if return BUSY, data not ready
*******************************************************************************/
uint8_t OOB_WaitData_Back(uint8_t* ReadBuffer)
{
	uint8_t cnt = 0;
	uint8_t RX_LEG = 0;

	RX_LEG = (uint8_t)ESPI->EORXLEN_b.LENGTH;
	for(cnt=0; cnt<RX_LEG; cnt++)
	{
		*(ReadBuffer+cnt) = *(OOB_IN_BUF+cnt);
	}
	return SUCCESS;
}

/******************************************************************************/
/** Send OOB Temperature Command
 * return Success / Busy
TX: 20 01 05 0F 30 01 02 01
RX: 0E 01 04 21 40 temp_L temp_H
*******************************************************************************/
uint8_t OOB_GetTemperature(void)
{
	uint8_t length;

	if (OOBNum ==0) {
		OOBNum = DTSNum;
		OOB_OUT_BUF[0] = 0x20;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x01;				//PECI Command()
		OOB_OUT_BUF[2] = 0x05;				//ByteCount
		OOB_OUT_BUF[3] = 0x0F;				//Source Slave Addr	(ByteCount[0])
		OOB_OUT_BUF[4] = 0x30;				//Client Address	(ByteCount[1])
		OOB_OUT_BUF[5] = 0x01;				//Write Lengrh		(ByteCount[2])
		OOB_OUT_BUF[6] = 0x02;				//Read Lengrh		(ByteCount[3])
		OOB_OUT_BUF[7] = 0x01;				//1st Data(Command)	(ByteCount[4])
		length  = 8;						//Buffer length 8 bytes
		OOB_Start_Head(length);
	}
	return BUSY;
}

/******************************************************************************/
/** Send OOB PCH Temperature Command
 * return Busy
RX: 02 01 01 1F
TX: 1E 01 02 03 25
*******************************************************************************/
uint8_t OOB_GetPchTemperature(void)
{
	uint8_t length;

	if(OOBNum ==0) {
		OOBNum = DTSNum;
		OOB_OUT_BUF[0] = 0x02;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x01;				//Command Code
		OOB_OUT_BUF[2] = 0x01;				//Byte Count
		OOB_OUT_BUF[3] = 0x1F;				//Source Slave Address
		length = 4;							//Buffer length 4 bytes
		OOB_Start_Head(length);
	}
	return BUSY;
}

/******************************************************************************/
/** Send OOB RTC Command
 * return Busy
RX: 02 02 01 1F
TX: 1E 02 09 03 02 45 01 00 03 16 05 23
*******************************************************************************/
uint8_t OOB_GetRtc(void)
{
	uint8_t length;

	if(OOBNum ==0) {
		OOBNum = RTCNum;
		OOB_OUT_BUF[0] = 0x02;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x02;				//Command Code
		OOB_OUT_BUF[2] = 0x01;				//Byte Count
		OOB_OUT_BUF[3] = 0x1F;				//Source Slave Address
		length = 4;							//Buffer length 4 bytes
		OOB_Start_Head(length);
	}
	return BUSY;
}

/******************************************************************************/
/** Send OOB PECI PING Command
 * return Busy
RX: 20 01 04 0E 30 00 00
TX: 0E 01 04 21 40 00 00
*******************************************************************************/
uint8_t OOB_PeciPing(void)
{
	uint8_t length;

	if(OOBNum == 0){
		OOBNum = PINGNum;
			//RdPkg
		OOB_OUT_BUF[0] = 0x20;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x01;				//PECI Command()
		OOB_OUT_BUF[2] = 0x04;				//ByteCount
		OOB_OUT_BUF[3] = 0x0E;				//Source Slave Addr	(ByteCount[0])
		OOB_OUT_BUF[4] = 0x30;				//Client Address	(ByteCount[1])
		OOB_OUT_BUF[5] = 0x00;				//Write Lengrh		(ByteCount[2])
		OOB_OUT_BUF[6] = 0x00;				//Read Lengrh		(ByteCount[3])
		length  = 7;						//Buffer length 7 bytes
		OOB_Start_Head(length);	
	}
	return BUSY;
}

/******************************************************************************/
/** Send OOB PECI DIB Command
 * return Busy
RX: 20 01 09 05 30 01 08 F7
TX: 0E 01 0A 21 40 33 00 00 00 00 00 00
*******************************************************************************/
uint8_t OOB_PeciDib(void)
{
	uint8_t length;

	if(OOBNum == 0){
		OOBNum = DIBNum;
			//RdPkg
		OOB_OUT_BUF[0] = 0x20;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x01;				//PECI Command()
		OOB_OUT_BUF[2] = 0x09;				//ByteCount
		OOB_OUT_BUF[3] = 0x05;				//Source Slave Addr	(ByteCount[0])
		OOB_OUT_BUF[4] = 0x30;				//Client Address	(ByteCount[1])
		OOB_OUT_BUF[5] = 0x01;				//Write Lengrh		(ByteCount[2])
		OOB_OUT_BUF[6] = 0x08;				//Read Lengrh		(ByteCount[3])
		OOB_OUT_BUF[7] = 0xF7;				//1st Data(Command)	(ByteCount[4])
		length  = 8;						//Buffer length 8 bytes
		OOB_Start_Head(length);	
	}
	return BUSY;
}

/******************************************************************************/
/** Send OOB PECI RdPkgConfig Command
 * return Busy
RX: 20 01 09 0F 30 05 05 A1 00 --(A1) --(00) --(00)
TX: 0E 01 07 21 40 40 00 00 00 00
*******************************************************************************/
uint8_t OOB_PECI_RdPkgConfig(uint8_t index, uint8_t* para, uint8_t* config)
{
	uint8_t length;
    uint16_t OOB_Timeout;

	if (OOBNum == 0) {
		OOBNum = RDPKGNum;
		if (index == 0x10) {				/* PECI_INDEX_TJMAX = 0x10 */
			RDPKGIdx = RDPKGIdx_CPUTjMax;
		} else if (index == 0x1C) {			/* PECI_INDEX_TDP = 0x1C */
			RDPKGIdx = RDPKGIdx_CPUTDP;
		} else if (index == 0x1A) {			/* PECI_INDEX_PL1 = 0x1A */
			RDPKGIdx = RDPKGIdx_PL1;
		} else if (index == 0x1B) {			/* PECI_INDEX_PL2 = 0x1B */
			RDPKGIdx = RDPKGIdx_PL2;
		} else if (index == 0x3C) {			/* PECI_INDEX_PL4 = 0x3C */
			RDPKGIdx = RDPKGIdx_PL4;
		}
		//RdPkg
		OOB_OUT_BUF[0] = 0x20;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x01;				//PECI Command()
		OOB_OUT_BUF[2] = 0x09;				//ByteCount
		OOB_OUT_BUF[3] = 0x0F;				//Source Slave Addr	(ByteCount[0])
		OOB_OUT_BUF[4] = 0x30;				//Client Address	(ByteCount[1])
		OOB_OUT_BUF[5] = 0x05;				//Write Lengrh		(ByteCount[2])
		OOB_OUT_BUF[6] = 0x05;				//Read Lengrh		(ByteCount[3])
		OOB_OUT_BUF[7] = 0xA1;				//1st Data(Command)	(ByteCount[4])
		OOB_OUT_BUF[8] = 0x00;				//HOST ID & Retry
		OOB_OUT_BUF[9] = index;				//Index
		OOB_OUT_BUF[10] = para[0];			//Parameter LSB
		OOB_OUT_BUF[11] = para[1];			//Parameter HSB		
		length  = 12;						//Buffer length 12 bytes
		OOB_Start_Head(length);	

		OOB_PECI_Done = 0;
		OOB_PECI_valid = 0;
		OOB_Timeout = 50;

		do {
			_Delay_1ms(1);
			if (OOB_PECI_Done) {
				/* check command passed/data is valid */
				if (OOB_PECI_valid) {
					if (index == 0x10) {		/* PECI_INDEX_TJMAX = 0x10 */
						*(config+8) = CPUTjMax;
					} else if (index == 0x1C) {	/* PECI_INDEX_TDP = 0x1C */
						*(config+6) = CPUTDP6;
						*(config+7) = CPUTDP7;
					} else if (index == 0x1A) {	/* PECI_INDEX_PL1 = 0x1A */
						// *(config+6) = CPUTDP6;
						// *(config+7) = CPUTDP7;
					} else if (index == 0x1B) {	/* PECI_INDEX_PL2 = 0x1B */
						// *(config+6) = CPUTDP6;
						// *(config+7) = CPUTDP7;
					} else if (index == 0x3C) {	/* PECI_INDEX_PL4 = 0x3C */
						// *(config+6) = CPUTDP6;
						// *(config+7) = CPUTDP7;
					}
					return SUCCESS;
				} else {
					return FAIL;
				}
			}
			OOB_Timeout--;
		} while (OOB_Timeout != 0);

		return FAIL;

	}
	return BUSY;
}

/******************************************************************************/
/** Send OOB PECI WrPkgConfig Command
 * return Busy
*******************************************************************************/
uint8_t OOB_PECI_WrPkgConfig(uint32_t WData, uint8_t index, uint16_t para)
{
	uint8_t length;
	uint16_t OOB_Timeout;

	if(OOBNum == 0){
		OOBNum = WRPKGNum;
			//RdPkg
		OOB_OUT_BUF[0] = 0x20;				//desination Slave Address
		OOB_OUT_BUF[1] = 0x01;				//PECI Command()
		OOB_OUT_BUF[2] = 0x0D;				//ByteCount
		OOB_OUT_BUF[3] = 0x0F;				//Source Slave Addr	(ByteCount[0])
		OOB_OUT_BUF[4] = 0x30;				//Client Address	(ByteCount[1])
		OOB_OUT_BUF[5] = 0x0A;				//Write Lengrh		(ByteCount[2])
		OOB_OUT_BUF[6] = 0x01;				//Read Lengrh		(ByteCount[3])
		OOB_OUT_BUF[7] = 0xA1;				//1st Data(Command)	(ByteCount[4])
		OOB_OUT_BUF[8] = 0x00;				//HOST ID & Retry
		OOB_OUT_BUF[9] = index;				//Index
		OOB_OUT_BUF[10] = para & 0x00FF;	//Parameter LSB
		OOB_OUT_BUF[11] = (para >> 8) & 0x00FF;		//Parameter HSB	
		OOB_OUT_BUF[12] = (uint8_t)(WData & 0x000000FF);			//write data byte 0
		OOB_OUT_BUF[13] = (uint8_t)((WData & 0x0000FF00) >> 8);		//write data byte 1
		OOB_OUT_BUF[14] = (uint8_t)((WData & 0x00FF0000) >> 16);	//write data byte 2
		OOB_OUT_BUF[15] = (uint8_t)((WData & 0xFF000000) >> 24);	//write data byte 3
		length  = 16;
		OOB_Start_Head(length);

		OOB_PECI_Done = 0;
		OOB_PECI_valid = 0;
		OOB_Timeout = 50;

		do {
			_Delay_1ms(1);
			if (OOB_PECI_Done) {
				/* check command passed/data is valid */
				if (OOB_PECI_valid) {
					return SUCCESS;
				} else {
					return FAIL;
				}
			}
			OOB_Timeout--;
		} while (OOB_Timeout != 0);

		return FAIL;
	}
	return BUSY;
}

/******************************************************************************/
/** OOB PECI PL1 test Command
 * return PL1 value
 * Package Power Limits PL1 and PL2 (Index 26/27)
 * [23:17] - Control Time Window,
 * [16] - Clamp Mode,
 * [15] - Power Limit Enable,
 * [14:0] - Power Limit (1/8) W units 
*******************************************************************************/
uint8_t OOB_PECI_RdPkg_PL1(void)
{
	uint8_t Status;
	uint8_t* config;

	uint8_t index = 0x1A;
	uint8_t para[2] = {0x00, 0x00};

	Status = OOB_PECI_RdPkgConfig(index, para, config);
	if(Status == SUCCESS)
	{
//		memcpy(pPL1, &OOBD[1], 4);
//		printf("OOB PECI Read PL1 0x%08x\n", PL1);
//		return PL1;
	}
	else
	{
		// printf("OOB PECI Read PL1 fail \n");
	}
	return Status;
}

/*-----------------------------------------------------------------------------
 * @subroutine - OOB_PECI_GetTemp
 * @function - OOB_PECI_GetTemp
 * @Upstream -
 * @input    - espi_temp
 * @return   - TRUE/FALSE
 * @note     - None
 */
uint8_t OOB_PECI_GetTemp(uint8_t *espi_temp)
{
	uint8_t  Tmp_CPU_T, tmp_t1;
	uint16_t tmp_t0, OOB_Timeout;

	OOB_GetTemperature();

	OOB_PECI_Done = 0;
	OOB_PECI_valid = 0;
	OOB_Timeout = 50;

	do {
		_Delay_1ms(1);
		if (OOB_PECI_Done) {
			/* check command passed/data is valid */
			if (OOB_PECI_valid) {
				tmp_t0 = (~CPUTemperature) + 1;     /* 2's complement */
				tmp_t1 = tmp_t0 >> 6;       		/* 1/64 degrees centigrade */

				if (CPUTjMax == 0) {
					Tmp_CPU_T = 100 - tmp_t1;
				} else {
					if ((tmp_t1 & 0x80) == 0x00) {
						Tmp_CPU_T = CPUTjMax - tmp_t1;
					} else {
						tmp_t1 = (~tmp_t1);
						Tmp_CPU_T = CPUTjMax + tmp_t1;
					}
				}
				*espi_temp = Tmp_CPU_T;
				return SUCCESS;
			} else {
				return FAIL;
			}
		}
		OOB_Timeout--;
	} while (OOB_Timeout != 0);

	return FAIL;
}