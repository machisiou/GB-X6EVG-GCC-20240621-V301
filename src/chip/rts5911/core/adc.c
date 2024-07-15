#include "hal/adc.h"
#include "chip/rts5911/RTS5911.h"
#include "RTK_Include.h"
/******************************************************************************/
/** Enable ADC conversion done interrupt
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * en - 0: Disalbe, 1: Enable
 * return None
*******************************************************************************/
void ADC_EnableConvDoneInt(ADC_Type* adc, ADC_CONVERSION_TYPE type, uint8_t en)
{
    switch(type) {
    case ADC_SINGLE_CONVERSION:
        adc->CTRL = (en > 0) ? (adc->CTRL | ADC_CTRL_SINGLEINTEN_Msk) : (adc->CTRL & ~ADC_CTRL_SINGLEINTEN_Msk);
        break;
    case ADC_REPEAT_CONVERSION:
        adc->CTRL = (en > 0) ? (adc->CTRL | ADC_CTRL_REPEATINTEN_Msk) : (adc->CTRL & ~ADC_CTRL_REPEATINTEN_Msk);
        break;
    }
}

/******************************************************************************/
/** Get ADC conversion done interrupt flag
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * return 1: Specified interrupt occurred, 0: Specified interrupt not occurred
*******************************************************************************/
uint32_t ADC_GetConvDoneIntFlag(ADC_Type* adc, ADC_CONVERSION_TYPE type)
{
    switch(type) {
    case ADC_SINGLE_CONVERSION:
        return (adc->STS & ADC_STS_SINGLEDONE_Msk) ? 1ul : 0ul;
    case ADC_REPEAT_CONVERSION:
        return (adc->STS & ADC_STS_REPEATDONE_Msk) ? 1ul : 0ul;
    }  
}

/******************************************************************************/
/** Clear ADC conversion done interrupt flag
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * return None
*******************************************************************************/
void ADC_ClrConvDoneIntFlag(ADC_Type* adc, ADC_CONVERSION_TYPE type)
{
    switch(type) {
    case ADC_SINGLE_CONVERSION:
        adc->STS = ADC_STS_SINGLEDONE_Msk;
        break;
    case ADC_REPEAT_CONVERSION:
        adc->STS = ADC_STS_REPEATDONE_Msk;
        break;
    }  
}

/******************************************************************************/
/** Get ADC channel done interrupt flag
 * adc - The pointer of ADC 
 * ch - The specified channel, 0: ADC_CH0, 1: ADC_CH1...., 11: ADC_CH11
 * return 1: Specified interrupt occurred, 0: Specified interrupt not occurred
*******************************************************************************/
uint32_t ADC_GetChDoneIntFlag(ADC_Type* adc, uint32_t ch)
{
    return (adc->STS & ((0x01ul << ch) << ADC_STS_CHDONE_Pos)) ? 1ul : 0ul;
}

/******************************************************************************/
/** Clear ADC channel done interrupt flag
 * adc - The pointer of ADC 
 * ch - The specified channel, 0: ADC_CH0, 1: ADC_CH1...., 11: ADC_CH11
 * return None
*******************************************************************************/
void ADC_ClrChDoneIntFlag(ADC_Type* adc, uint32_t ch)
{
    adc->STS = (0x01ul << (ADC_STS_CHDONE_Pos + ch));
}

/******************************************************************************/
/** Bypass ADC linear calibration
 * adc - The pointer of ADC 
 * bypass - 0: Not bypass, 1: Bypass
 * return None
*******************************************************************************/
void ADC_BypassLinearCalibraion(ADC_Type* adc, uint8_t bypass)
{
    adc->CHCTRL = (bypass > 0) ? (adc->CTRL | ADC_CHCTRL_CALBYPASS_Msk) : (adc->CTRL & ~ADC_CHCTRL_CALBYPASS_Msk);
}

/******************************************************************************/
/** Bypass ADC specified channel low pass filter
 * adc - The pointer of ADC 
 * ch_msk - The specified channel to bypass low pass filter, BIT0: ADC_CH0, BIT1: ADC_CH1..., BIT11: ADC_CH11
 * return None
*******************************************************************************/
void ADC_BypassLowPassFilter(ADC_Type* adc, uint32_t ch_msk)
{
    ch_msk = (ch_msk & 0xFFFul);
    
    adc->CHCTRL &= ~(0xFFFul << ADC_CHCTRL_CHLPFBYPASS_Pos);
    adc->CHCTRL |= (ch_msk << ADC_CHCTRL_CHLPFBYPASS_Pos);
}

/******************************************************************************/
/** Trigger ADC to convert
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * ch_msk - The specified channel want to convert, BIT0: ADC_CH0, BIT1: ADC_CH1..., BIT11: ADC_CH11
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t ADC_TriggerConversion(ADC_Type* adc, ADC_CONVERSION_TYPE type, uint32_t ch_msk)
{
    ch_msk = (ch_msk & 0xFFFul);
    
    /* Reset and disable ADC controller */
    adc->CTRL_b.EN = 0;
    adc->CTRL_b.RST = 0;
    adc->CTRL_b.RST = 1;
    
    /* Wait ADC controller ready */
    adc->CTRL_b.EN = 1;
    while(!ADC->STS_b.READY);
    
    /* Set conversion mode */
    adc->CTRL_b.MDSEL = type;
    
    /* Enable channel and LPF */
    adc->CHCTRL &= ~(0xFFFul << ADC_CHCTRL_CHEN_Pos);
    adc->CHCTRL |= (ch_msk << ADC_CHCTRL_CHEN_Pos);
    
    /* Kick start */
    adc->CTRL_b.START = 1;
    
    return 1;
}

/******************************************************************************/
/** To stop ADC conversion
 * adc - The pointer of ADC 
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t ADC_StopConversion(ADC_Type* adc)
{
    /* Reset and disable ADC controller */
    adc->CTRL_b.EN = 0;
    adc->CTRL_b.RST = 0;
    adc->CTRL_b.RST = 1;
    
    return 1;
}

/******************************************************************************/
/** Get ADC channel conversion result
 * adc - The pointer of ADC 
 * ch - The specified channel of ADC
 * return (uint32_t): ADC conversion result
*******************************************************************************/
uint32_t ADC_GetConversionResult(ADC_Type* adc, uint32_t ch)
{
    return (adc->CHDATA[ch] & 0xFFFul);
}
