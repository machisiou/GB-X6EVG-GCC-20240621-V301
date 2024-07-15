#include "RTK_Include.h"

static uint32_t TimeOutCnt =0;

/******************************************************************************/
/** Check for timeout
 * None
 * return - success or fail
*******************************************************************************/
uint8_t CheckForTimeout(void)
{
	if(TimeOutCnt)
	{
		TimeOutCnt--;
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
/** Calculate temperature from GetTemp command
 * bLSB - LSB value
 * bMSB - MSB value
 * return - temperature value
*******************************************************************************/
int8_t TempConvert(uint8_t bLSB, uint8_t bMSB)
{
	int16_t cputemp;
	int8_t tempcpu;
	cputemp =(int16_t)((bMSB<<8)+bLSB);
	cputemp = (~cputemp)+1;
	tempcpu =(int8_t) (cputemp>>6);
	return tempcpu;
}

/******************************************************************************/
/* PECI Reset
  * None
  *return - None
*******************************************************************************/

void PECI_Reset(void)
{
	uint8_t i;

	PECI->CTRL_b.RST = 1;
	PECI->CTRL_b.FIFORST = 1;

	PECI->CTRL = 0x01;
	for (i=0;i<3;i++)
	{
		// Try hard for a short period of time
 		if (PECI_Wait_Idle())    // 100us
 		{
 			break;
 		}

	}
	PECI->OBTL_b.VAL = 0x81;
	PECI->OBTH_b.VAL = 0x00;

}

/******************************************************************************/
/* Read Byte
  * read_data[] - data buffer
  * num_byte -  read length
  *return - None
*******************************************************************************/
void PECI_Read_Bytes  ( uint8_t read_data[], uint8_t num_bytes )
{
	uint8_t readdcnt = 0;
	
		// Read specified number of bytes or until FIFO is empty
	for (readdcnt = 0; readdcnt < num_bytes; readdcnt++)
	{
		if(!(PECI->STS1_b.RXEMPTY))
		{
			read_data[readdcnt] = PECI->RX_b.DATA;
		}
	}
}

/******************************************************************************/
/* Wait Idle
  * max_delay_us - maximum waiting time
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Wait_Idle(void)
{
	/// Check if bus is busy
	while (1)
	{
		//Check Busy or Idle, 0 means Busy, 1 means IDLE
		if (CHECK_PECI_BUSY())
		{
			return SUCCESS;
		}

		if(CheckForTimeout())
		{
			if (CHECK_PECI_BUSY())
			{
				return SUCCESS;
			}
			// Timed out
			return FAIL;
		}
	}
}

/******************************************************************************/
/* Software FCS calculation
  * data_blk_ptr - buffer
  * length - data length
  *return - FCS value
*******************************************************************************/
uint8_t PECI_Fcs_Check(uint8_t crc, uint8_t *data_blk_ptr, uint32_t length )
{
	uint8_t temp1,data_byte,bit0;
	unsigned int i,j;

	for (i = 0; i < length; i++)
	{
		data_byte = *data_blk_ptr++;
		for (j = 0; j < 8; j++)
		{
			bit0 = (data_byte & 0x80) ? 0x80 : 0;
			data_byte <<= 1;
			crc ^= bit0;
			temp1 = crc & 0x80;
			crc <<= 1;
			if( temp1 )
				crc ^= 0x07;
		}
	}
	return crc;
}

/******************************************************************************/
/* Write command
  * cmd_fifo[] - buffer
  * length - data length
  *return - None
*******************************************************************************/
void PECI_Write_Command(uint8_t cmd_fifo[], uint8_t cmd_length)
{
	uint8_t i = 0;

    // Write specified number of bytes or until FIFO is full
	while((!(PECI->STS1_b.TXFULL)) && (i<cmd_length))
	{
		PECI->TX_b.DATA = cmd_fifo[i++];
	}

	// Wait for  idle state
	while(!CHECK_PECI_BUSY());

	// Clear the BOF and EOF_
	PECI->STS0_b.BOFSTS = 1;
	PECI->STS0_b.EOFSTS = 1;

    // Set transmit enable to start transmission of message
	PECI->CTRL_b.TXEN = 1;

	// Wait for EOF_ (End Of Frame)
	while(PECI->STS0_b.EOFSTS);
	// Wait for the bus to go idle
	while(!CHECK_PECI_BUSY());
}

/******************************************************************************/
/* Handle Read Write command function
  * header[] - write buffer
  * headerLen - write length
  * readBuf[] - read buffer
  * readLen - read length
  *return - success or fail
*******************************************************************************/
int PECI_Command(uint8_t header[], uint8_t headerLen, uint8_t readBuf[], uint8_t readLen)
{
	uint8_t error = 0, done = 0, i, retry = 0, valid_data=0;
	uint8_t sw_first_fcs, sw_end_fcs, client_first_fcs, client_end_fcs = 0;
	uint8_t do_reset_on_error;
	uint8_t read_data_no_fcs[20];

	// Calculate expected header FCS value for later comparison
	sw_first_fcs = PECI_Fcs_Check(0, header, headerLen);
	

	while (!done)
	{
		do_reset_on_error = 1;

		PECI_Write_Command (header, headerLen);

		PECI_Read_Bytes(readBuf, readLen);
		client_first_fcs = readBuf[0];
		client_end_fcs = readBuf[readLen-1];

		if(readLen == 0)
		{
			return 1;
		}
		else if(readLen == 1)	
		{
			if(client_first_fcs == sw_first_fcs)
			{
				return 0;	// ping cmd only has one FCS data back
			}
			else
			{
				error = 1;
			}
		}
		else
		{	
			for (i = 0; i < readLen - 2; i++) 
			{
				read_data_no_fcs[i] = readBuf[i + 1];
			}
			if (sw_first_fcs != client_first_fcs)
			{
				error = 1;
			}
			else if (client_first_fcs==0 && client_end_fcs)
			{
				for(i = 0;i<readLen-2;i++)
				{
 					// Assume that non-zero data means it's valid
					if(read_data_no_fcs[i] != 0)
						valid_data++;
				}
				if(valid_data)
				{
					error = 1;
				}
			}
			if(!error)
			{
				sw_end_fcs = PECI_Fcs_Check(0, read_data_no_fcs, readLen-2);
				if (sw_end_fcs != client_end_fcs)
				{
					error = 1;
				}
			}

		}			

		if (CHECK_PECI_ERROR())
		{
			error = 1;
			if(CHECK_PECI_FCS_ERROR())
			{
				// Reset the fifos
				PECI_FIFO_RESET_SET();
				PECI_FIFO_RESET_CLEAR();
				do_reset_on_error = 0;
			}
			
			//Clear the error status register
			PECI->ERR = 0xff;
		}
		// If we get here with errors, we need to possibly reset the controller and attempt retry
		if(error)
		{
			if (retry == MAX_RETRIES)
			{
				done = 1;
			}
			else
			{
				error = 0;
				retry++;

				if(do_reset_on_error)
				{
					PECI_Reset();
				}
			}
		}
		// .. otherwise the transaction was successful
		else
		{	  
			return 0;
		}
	}

	// If we get here, the message has failed.
	return 1;
}

/******************************************************************************/
/* Ping command
  * Peciaddr - client address
  * Numretries - retry time
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Ping(uint8_t Peciaddr, uint8_t Numretries)
{
	uint8_t Writearray[PECI_PING_WRITE_ARRAY_LENGTH];
	uint8_t Readarray[PECI_PING_READ_ARRAY_LENGTH];
	uint8_t status = FAIL;

	while (Numretries--)
	{
		Writearray[0] = Peciaddr;								// [0] - PECI client address
		Writearray[1] = 0;										// [1] - Write length
		Writearray[2] = 0;										// [2] - Read length

		if (!PECI_Command(Writearray, PECI_PING_WRITE_ARRAY_LENGTH, Readarray, PECI_PING_READ_ARRAY_LENGTH))
		{
			status = SUCCESS;
			break;
		}
	}

	return status;
}

/******************************************************************************/
/* Get temperature command
  * Peciaddr - client address
  * *Temp - temperature pointer
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Get_Temp(uint8_t Peciaddr, int16_t *Temp)
{
	uint8_t Writearray[PECI_GETTEMP_WRITE_ARRAY_LENGTH];
	uint8_t Readarray[PECI_GETTEMP_READ_ARRAY_LENGTH];
	uint8_t status = FAIL;
	Writearray[0] = Peciaddr;								// [0] - PECI client address
	Writearray[1] = PECI_GETTEMP_WRITE_DATA_LENGTH;					// [1] - Write length
	Writearray[2] = PECI_GETTEMP_READ_DATA_LENGTH;					// [2] - Read length
	Writearray[3] = PECI_GETTEMP_CMD;							// [3] - Command byte
	
	if (!PECI_Command(Writearray, PECI_GETTEMP_WRITE_ARRAY_LENGTH, Readarray, PECI_GETTEMP_READ_ARRAY_LENGTH))
	{
		if(Readarray[PECI_GETTEMP_MSB] != PECI_GETTEMP_ERR_MSB)
		{
			*Temp = TempConvert(Readarray[PECI_GETTEMP_LSB],Readarray[PECI_GETTEMP_MSB]);
			status = SUCCESS;
		}
	}
	return status;
}


/******************************************************************************/
/* Get DIB command
  * Peciaddr - client address
  * *Version - Version pointer
  * Numretries - retry time
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Get_DIB(uint8_t Peciaddr,uint8_t Numretries, uint8_t *Version)
{
	uint8_t Writearray[PECI_GETDIB_WRITE_ARRAY_LENGTH];
	uint8_t Readarray[PECI_GETDIB_READ_ARRAY_LENGTH];
	uint8_t status = FAIL;
	while (Numretries--)
	{
		Writearray[0] = Peciaddr;								// [0] - PECI client address
		Writearray[1] = PECI_GETDIB_WRITE_DATA_LENGTH;						// [1] - Write length
		Writearray[2] = PECI_GETDIB_READ_DATA_LENGTH;						// [2] - Read length
		Writearray[3] = PECI_GETDIB_CMD;							// [3] - Command byte
	
		if (!PECI_Command(Writearray, PECI_GETDIB_WRITE_ARRAY_LENGTH, Readarray, PECI_GETDIB_READ_ARRAY_LENGTH))
		{
			*Version = Readarray[PECI_GET_REVISION];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

/******************************************************************************/
/* Read package command
  * Peciaddr - client address
  * Numretries - retry time
  * Index - Index value
  * Parameter - Parameter value
  * *Value - Value pointer
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Read_Pkg_Config(uint8_t Peciaddr,uint8_t Numretries,uint8_t Index, uint16_t Parameter, uint8_t *Value)
{
	uint8_t Writearray[20];
	uint8_t Readarray[20];
	uint8_t RETRY_BIT = 0;
	uint8_t status = FAIL;
	
	while (Numretries--)
	{
		Writearray[0] = Peciaddr;								// [0] - PECI client address
		Writearray[1] = PECI_RDPKGCONFIG_WRITE_DATA_LENGTH;				// [1] - Write length
		Writearray[2] = PECI_RDPKGCONFIG_READ_DATA_LENGTH;				// [2] - Read length
		Writearray[3] = PECI_RDPKGCONFIG_CMD;	   					// [3] - Command byte
		Writearray[4] = RETRY_BIT;								// [4] - Host ID [7:1], Retry [0]
		Writearray[5] = Index;									// [5] - Index
		Writearray[6] = (uint8_t)(Parameter & 0xFF);						// [6] - Parameter low byte
		Writearray[7] = (uint8_t)((Parameter >> 8) & 0xFF);				// [7] - Parameter high byte	
	
		if (!PECI_Command(Writearray, PECI_RDPKGCONFIG_WRITE_ARRAY_LENGTH, Readarray, PECI_RDPKGCONFIG_READ_ARRAY_LENGTH))
		{
			switch (Readarray[PECI_RDPKGCONFIG_CC])
			{
				case PECI_RDPKGCONFIG_CC_SUCCESS:
					*(Value++) = Readarray[PECI_RDPKGCONFIG_DATA+3];
					*(Value++) = Readarray[PECI_RDPKGCONFIG_DATA+2];
					*(Value++) = Readarray[PECI_RDPKGCONFIG_DATA+1];
					*(Value) = Readarray[PECI_RDPKGCONFIG_DATA];
					RETRY_BIT = 0;
					status = SUCCESS;
					break;

				case PECI_RDPKGCONFIG_CC_TIMEOUT:
					RETRY_BIT = PECI_RDPKGCONFIG_RETRY;
					break;

				case PECI_RDPKGCONFIG_CC_ILLEGAL:
					break;

				default:
					break;
            }
		}
	}
	return status;
}

/******************************************************************************/
/* Write package command
  * Peciaddr - client address
  * Numretries - retry time
  * Index - Index value
  * Parameter - Parameter value
  * *Value - Value pointer
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Write_Pkg_Config(uint8_t Peciaddr,uint8_t Numretries,uint8_t Index, uint16_t Parameter, uint8_t *Value)
{
	uint8_t Writearray[20];
	uint8_t Readarray[20];
	uint8_t RETRY_BIT = 0;
	uint8_t status = FAIL;


	while (Numretries--)
	{
		Writearray[0] = Peciaddr;								// [0] - PECI client address
		Writearray[1] = PECI_WRPKGCONFIG_WRITE_DATA_LENGTH;				// [1] - Write length
		Writearray[2] = PECI_WRPKGCONFIG_READ_DATA_LENGTH;				// [2] - Read length
		Writearray[3] = PECI_WRPKGCONFIG_CMD;	   					// [3] - Command byte
		Writearray[4] = RETRY_BIT;								// [4] - Host ID [7:1], Retry [0]
		Writearray[5] = Index;									// [5] - Index
		Writearray[6] = (uint8_t)(Parameter & 0xFF);										// [6] - Parameter low byte
		Writearray[7] = (uint8_t)((Parameter >>8) & 0xFF);										// [7] - Parameter high byte	
		Writearray[8] = (uint8_t)(Value[0]);						// [8] - Data[0]	
		Writearray[9] = (uint8_t)(Value[1]);					// [9] - Data[1]	
		Writearray[10] = (uint8_t)(Value[2]);					// [10] - Data[2]	
		Writearray[11] = (uint8_t)(Value[3]);					// [11] - Dsata[3]
		Writearray[12] = (PECI_Fcs_Check(0, Writearray, (PECI_WRPKGCONFIG_WRITE_ARRAY_LENGTH - 1)) ^ 0x80);			// [12] - AW FCS
		if (!PECI_Command(Writearray, PECI_WRPKGCONFIG_WRITE_ARRAY_LENGTH, Readarray, 1))
		{
			switch (Readarray[PECI_WRPKGCONFIG_CC])
			{
				case PECI_WRPKGCONFIG_CC_SUCCESS:
					RETRY_BIT = 0;
					status = SUCCESS;
					break;
				
				case PECI_WRPKGCONFIG_CC_TIMEOUT:
					RETRY_BIT = PECI_WRPKGCONFIG_RETRY;
					break;
				
				case PECI_WRPKGCONFIG_CC_ILLEGAL:
					break;
				
				default:
					break;
				
            }

		}
	}
	return status;
}

/******************************************************************************/
/* Read Intel Architecture
  * Peciaddr - client address
  *return - success or fail
*******************************************************************************/
uint8_t PECI_Read_IA_MSR(uint8_t Peciaddr,uint8_t Numretries)
{
	uint8_t Writearray[20];
	uint8_t Readarray[20];
	uint8_t RETRY_BIT = 0;
	uint8_t status = FAIL;
	while (Numretries--)
	{
		Writearray[0] = Peciaddr;								// [0] - PECI client address
		Writearray[1] = 0x05;								 	// [1] - Write length
		Writearray[2] = 9;										// [2] - Read length
		Writearray[3] = 0xB1;	   								// [3] - Command byte
		Writearray[4] = RETRY_BIT;								// [4] - Host ID [7:1], Retry [0]
		Writearray[5] = 00;										// [5] - Process ID
		Writearray[6] = 0x02;									// [6] - MSR Address low byte(IA32_MC0_ADDR)
		Writearray[7] = 0x04;									// [7] - MSR Address high bytes	

		if (!PECI_Command(Writearray, 3+5, Readarray, 9))
		{
			status = SUCCESS;
			break;
		}
	}
	return status;
}

/******************************************************************************/
/* Enable PECI Interrupt
  * 
  * 
  * return Success
*******************************************************************************/

uint8_t PECI_Enable_Interrupt(void)
{
	PECI->CTRL_b.EN = 1;
	return 1;
}

/******************************************************************************/
/* Disable PECI Interrupt
  * 
  * 
  * return Success
*******************************************************************************/

uint8_t PECI_Disable_Interrupt(void)
{
	PECI->CTRL_b.EN = 0;
	return 1;
}