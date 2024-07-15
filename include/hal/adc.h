#ifndef __ADC_H__
#define __ADC_H__

/*
 * Includes
 */


typedef enum {
    ADC_SINGLE_CONVERSION = 0,
    ADC_REPEAT_CONVERSION,
} ADC_CONVERSION_TYPE;

enum {
    ADC_CH0_MSK     = (0x01ul << 0),
    ADC_CH1_MSK     = (0x01ul << 1),
    ADC_CH2_MSK     = (0x01ul << 2),
    ADC_CH3_MSK     = (0x01ul << 3),
    ADC_CH4_MSK     = (0x01ul << 4),
    ADC_CH5_MSK     = (0x01ul << 5),
    ADC_CH6_MSK     = (0x01ul << 6),
    ADC_CH7_MSK     = (0x01ul << 7),
    ADC_CH8_MSK     = (0x01ul << 8),
    ADC_CH9_MSK     = (0x01ul << 9),
    ADC_CH10_MSK    = (0x01ul << 10),
    ADC_CH11_MSK    = (0x01ul << 11),
};

/******************************************************************************/
/** Enable ADC conversion done interrupt
 * adc - The pointer of ADC 
 * type - The type of conversion, should be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * en - 0: Disalbe, 1: Enable
 * return None
*******************************************************************************/
void ADC_EnableConvDoneInt(ADC_Type* adc, ADC_CONVERSION_TYPE type, uint8_t en);

/******************************************************************************/
/** Get ADC conversion done interrupt flag
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * return 1: Specified interrupt occurred, 0: Specified interrupt not occurred
*******************************************************************************/
uint32_t ADC_GetConvDoneIntFlag(ADC_Type* adc, ADC_CONVERSION_TYPE type);

/******************************************************************************/
/** Clear ADC conversion done interrupt flag
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * return None
*******************************************************************************/
void ADC_ClrConvDoneIntFlag(ADC_Type* adc, ADC_CONVERSION_TYPE type);

/******************************************************************************/
/** Get ADC channel done interrupt flag
 * adc - The pointer of ADC 
 * ch - The specified channel, 0: ADC_CH0, 1: ADC_CH1...., 11: ADC_CH11
 * return 1: Specified interrupt occurred, 0: Specified interrupt not occurred
*******************************************************************************/
uint32_t ADC_GetChDoneIntFlag(ADC_Type* adc, uint32_t ch);

/******************************************************************************/
/** Clear ADC channel done interrupt flag
 * adc - The pointer of ADC 
 * ch - The specified channel, 0: ADC_CH0, 1: ADC_CH1...., 11: ADC_CH11
 * return None
*******************************************************************************/
void ADC_ClrChDoneIntFlag(ADC_Type* adc, uint32_t ch);

/******************************************************************************/
/** Bypass ADC linear calibration
 * adc - The pointer of ADC 
 * bypass - 0: Not bypass, 1: Bypass
 * return None
*******************************************************************************/
void ADC_BypassLinearCalibraion(ADC_Type* adc, uint8_t bypass);

/******************************************************************************/
/** Bypass ADC specified channel low pass filter
 * adc - The pointer of ADC 
 * ch_msk - The specified channel to bypass low pass filter, BIT0: ADC_CH0, BIT1: ADC_CH1..., BIT11: ADC_CH11
 * return None
*******************************************************************************/
void ADC_BypassLowPassFilter(ADC_Type* adc, uint32_t ch_msk);

/******************************************************************************/
/** Trigger ADC to convert
 * adc - The pointer of ADC 
 * type - The type of conversion, could be ADC_SINGLE_CONVERSION or ADC_REPEAT_CONVERSION
 * ch_msk - The specified channel want to convert, BIT0: ADC_CH0, BIT1: ADC_CH1..., BIT11: ADC_CH11
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t ADC_TriggerConversion(ADC_Type* adc, ADC_CONVERSION_TYPE type, uint32_t ch_msk);

/******************************************************************************/
/** To stop ADC conversion
 * adc - The pointer of ADC 
 * return 0: Fail, 1: Success
*******************************************************************************/
uint32_t ADC_StopConversion(ADC_Type* adc);

/******************************************************************************/
/** Get ADC channel conversion result
 * adc - The pointer of ADC 
 * ch - The specified channel of ADC
 * return (uint32_t): ADC conversion result
*******************************************************************************/
uint32_t ADC_GetConversionResult(ADC_Type* adc, uint32_t ch);

#endif  /* __ADC_H__ */
