#include "system/Type.h"
#include "hal/PS2.h"
#include "hal/TIMER.h"
#include "hal/SYSTEM.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Enable PS2 channel
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_On(void)
{
	PS2->CTRL_b.EN = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Reset PS2 channel
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_Reset(void)
{
	PS2->CTRL_b.RST = 0;
	PS2->CTRL_b.RST = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Enable PS2 interrupt
 * Bit2 : all status interrupt
 * Bit1 : stop condition interrupt (PS2_TDS)
 * Bit0 : start condition interrupt (PS2_STS)
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_Enable_Interrupt(uint8_t EnDis)
{
	PS2->INTEN = EnDis;
	return SUCCESS;
}

/******************************************************************************/
/** Read PS2 status
 * Bit7 : PS2 receive timerout
 * Bit6 : PS2 transmit timeout, recevie over 2ms
 * Bit5 : PS2 transmit timeout, sending over 2ms
 * Bit4 : PS2 channel state
 * Bit3 : all stop bir error
 * Bit2 : parity error
 * Bit1 : transaction done status (for rx/tx done)
 * Bit0 : start transaction status
 * return PS2 status
*******************************************************************************/
uint8_t PS2_Read_STS(void)
{
	uint32_t STS;
	STS = PS2->STS;
	return (uint8_t)STS;
}

/******************************************************************************/
/** Clear PS2 interrupt status
 * Bit7 : PS2 receive timerout
 * Bit6 : PS2 transmit timeout, recevie over 2ms
 * Bit5 : PS2 transmit timeout, sending over 2ms
 * Bit4 : PS2 channel state
 * Bit3 : all stop bir error
 * Bit2 : parity error
 * Bit1 : transaction done status (for rx/tx done)
 * Bit0 : start transaction status
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_Clear_STS(uint8_t Flag)
{
	PS2->STS = Flag;
	return SUCCESS;
}

/******************************************************************************/
/** Send out data from PS2
 * uData - Raw data
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_SetTxBuf(uint8_t uData)
{
	TIME32_Type timer_tmp;

	// Trans mode
	PS2->CTRL_b.MDSEL = 1;
	PS2->TXDAT_b.DATA = uData;

	SYSTEM->TMRDIV_b.TMR4DIV = TMR_CLK_DVI2;		// 25M/2
	timer_tmp.Tmr_Num = TIMER4;
	timer_tmp.Mode = One_Shut;
	timer_tmp.MASK_INT = MASK_INT_OFF;
	timer_tmp.LoadCount = 62500;					// (1/25M)*2*62500 = 0.005S
	timer_tmp.OnOff = 1;
	TIMER32_Config(&timer_tmp);
	//check PS2 ready
	while(!(PS2->CTRL_b.READY)) {
		if(TIMER32_Read_Intsts(timer_tmp.Tmr_Num)) {
			TIMER32_Clear_Intsts(timer_tmp.Tmr_Num);
			return FAIL;
		}
	}

	PS2->CTRL_b.TXSTR = 1;
	return SUCCESS;
}

/******************************************************************************/
/** Read PS2 data
 * return PS2 data
*******************************************************************************/
uint8_t PS2_GetRxBuf(void)
{
	return PS2->RXDAT_b.DATA;
}

/******************************************************************************/
/** Send data to device
 * uData - Data
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_WriteByte(uint8_t uData)
{
	uint8_t STS;
	if(!PS2_SetTxBuf(uData)) return FAIL;

	// Check if Trans done
	do {
		STS = PS2_Read_STS();
		if(STS & 0x02) break;
	}while(1);

	PS2_Clear_STS(0xFF);
	return SUCCESS;
}

/******************************************************************************/
/** Change PS2 pin status
 * PS2 mode - Receive_Mode or Transmit_Mode or Inhibit_Mode
 * return SUCCESS
*******************************************************************************/
uint8_t PS2_Mode_Change(uint8_t Mode, uint8_t ClkPin)
{
	if((ClkPin != GPIO092) &&(ClkPin != GPIO096)) {
		return FAIL;
	}
	if(Mode == Inhibit_Mode) {
		GPIO->GCR_b[ClkPin].MFCTRL = 0x00;	// GPIO mode
		GPIO->GCR_b[ClkPin].DIR = 1;		// output
		GPIO->GCR_b[ClkPin].OUTCTRL = 0;	// low
		return SUCCESS;
	}else if (Mode == Receive_Mode) {
		PS2->CTRL_b.MDSEL = 0;
	}else if (Mode == Transmit_Mode) {
		PS2->CTRL_b.MDSEL = 1;
	}
	if(ClkPin == GPIO092) GPIO->GCR_b[92].MFCTRL = 0x01;	//MFC pin
	if(ClkPin == GPIO096) GPIO->GCR_b[96].MFCTRL = 0x02;	//MFC pin

	return SUCCESS;
}
