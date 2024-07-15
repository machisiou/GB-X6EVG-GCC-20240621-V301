#ifndef __Oem_ADC_H__
#define __Oem_ADC_H__

#include <stdint.h>
#include "hal/adc.h"

extern void adc_Initialization(uint16_t adc_on_ch);
uint32_t adc_GetConversionResult(uint32_t ch);
void adc_ClrConvDoneIntFlag(ADC_CONVERSION_TYPE type);
uint32_t adc_TriggerConversion(ADC_CONVERSION_TYPE type, uint32_t ch_msk);
uint32_t adc_GetConvDoneIntFlag(ADC_CONVERSION_TYPE type);
uint32_t adc_GetChDoneIntFlag(uint32_t ch);
void adc_ClrChDoneIntFlag(uint32_t ch);
void adc_StopConversion(void);

#endif
