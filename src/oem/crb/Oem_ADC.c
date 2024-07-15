#include "RTK_Include.h"

void ADC_Initialization(uint16_t adc_on_ch)
{
    if(IS_BIT_SET(adc_on_ch,BIT0)) ADC_BypassLinearCalibraion(ADC, 0);
    if(IS_BIT_SET(adc_on_ch,BIT1)) ADC_BypassLinearCalibraion(ADC, 1);
    if(IS_BIT_SET(adc_on_ch,BIT2)) ADC_BypassLinearCalibraion(ADC, 2);
    if(IS_BIT_SET(adc_on_ch,BIT3)) ADC_BypassLinearCalibraion(ADC, 3);
    if(IS_BIT_SET(adc_on_ch,BIT4)) ADC_BypassLinearCalibraion(ADC, 4);
    if(IS_BIT_SET(adc_on_ch,BIT5)) ADC_BypassLinearCalibraion(ADC, 5);
    if(IS_BIT_SET(adc_on_ch,BIT6)) ADC_BypassLinearCalibraion(ADC, 6);
    if(IS_BIT_SET(adc_on_ch,BIT7)) ADC_BypassLinearCalibraion(ADC, 7);
    if(IS_BIT_SET(adc_on_ch,BIT8)) ADC_BypassLinearCalibraion(ADC, 8);
    if(IS_BIT_SET(adc_on_ch,BIT9)) ADC_BypassLinearCalibraion(ADC, 9);
    if(IS_BIT_SET(adc_on_ch,BIT10)) ADC_BypassLinearCalibraion(ADC, 10);
    if(IS_BIT_SET(adc_on_ch,BIT11)) ADC_BypassLinearCalibraion(ADC, 11);
    ADC_BypassLowPassFilter(ADC, 0xFFFul);
}

uint32_t adc_GetConversionResult(uint32_t ch)
{
    return ADC_GetConversionResult(ADC, ch);
}

void adc_ClrConvDoneIntFlag(ADC_CONVERSION_TYPE type)
{
    ADC_ClrConvDoneIntFlag(ADC, type);
}

uint32_t adc_TriggerConversion(ADC_CONVERSION_TYPE type, uint32_t ch_msk)
{
    return ADC_TriggerConversion(ADC, type, ch_msk);
}

uint32_t adc_GetConvDoneIntFlag(ADC_CONVERSION_TYPE type)
{
    return ADC_GetConvDoneIntFlag(ADC, type);
}

uint32_t adc_GetChDoneIntFlag(uint32_t ch)
{
    return ADC_GetChDoneIntFlag(ADC, ch);
}

void adc_ClrChDoneIntFlag(uint32_t ch)
{
    ADC_ClrChDoneIntFlag(ADC, ch);
}

void adc_StopConversion(void)
{
    ADC_StopConversion(ADC);
}
