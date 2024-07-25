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

//GB

//----------------------------------------------------------------------------
// The function of scaning ADC input
//----------------------------------------------------------------------------
#define ADCChannel_0     0x80
#define ADCChannel_1     0x81
#define ADCChannel_2     0x82
#define ADCChannel_3     0x83
#define ADCChannel_4     0x84
#define ADCChannel_5     0x85
#define ADCChannel_6     0x86
#define ADCChannel_7     0x87

//----------------------------------------------------------------------------
// Define used ADC channel 
// Note : 
//		If the project doesn't use the channel. Please mark the define.
//----------------------------------------------------------------------------
#define FixCh0          ADCChannel_0    // Save to Fix_ADCAvg0
#define FixCh1          ADCChannel_2    // Save to Fix_ADCAvg1

//#define DyCh0           ADCChannel_4    // Save to ADCAvg0
//#define DyCh1           ADCChannel_6    // Save to ADCAvg1
//#define DyCh2           ADCChannel_2    // Save to ADCAvg2
//#define DyCh3           ADCChannel_5    // Save to ADCAvg3
//#define DyCh4           ADCChannel_7    // Save to ADCAvg4
//#define DyCh5           ADCChannel_7    // Save to ADCAvg5
//----------------------------------------------------------------------------

extern void DisableADCChannel(void);
extern void EnableADCChannel(void);
extern void DisableADCModule(void);
extern void EnableADCModule(void);
extern void ScanADCFixChannel(void);
extern void ScanADCDyChannel1(void);
extern void ScanADCDyChannel2(void);
extern void Init_ADC(void);
extern void Service_Scan_ADC(void);
extern void Get_ADC0_Thermistor(void);
extern void Get_ADC1_Thermistor(void);


typedef struct ADCDyInput
{
    BYTE    channelsel;
	XBYTE	*var;
}sADCDyinput;

#ifdef DyCh0
	#ifndef ScanDyChannel1
	#define ScanDyChannel1
	#endif
#endif

#ifdef DyCh1
	#ifndef ScanDyChannel1
	#define ScanDyChannel1
	#endif
#endif

#ifdef DyCh2
	#ifndef ScanDyChannel1
	#define ScanDyChannel1
	#endif
#endif

#ifdef DyCh3
	#ifndef ScanDyChannel2
	#define ScanDyChannel2
	#endif
#endif

#ifdef DyCh4
	#ifndef ScanDyChannel2
	#define ScanDyChannel2
	#endif
#endif

#ifdef DyCh5
	#ifndef ScanDyChannel2
	#define ScanDyChannel2
	#endif
#endif

#endif
