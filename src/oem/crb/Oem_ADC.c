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


//GB

//----------------------------------------------------------------------------
// The Table of scaning ADC
//----------------------------------------------------------------------------
#ifdef ScanDyChannel1
const sADCDyinput code asADCDyInput1[]=
{
	#ifdef DyCh0
	{   DyCh0,  &ADCAvg0 	},
	#endif
	
	#ifdef DyCh1
	{   DyCh1,  &ADCAvg1 	},
	#endif

	#ifdef DyCh2
	{   DyCh2,  &ADCAvg2 	}
	#endif	
};
#endif

#ifdef ScanDyChannel2
const sADCDyinput code asADCDyInput2[]=
{
	#ifdef DyCh3
	{   DyCh3,  &ADCAvg3 	},
	#endif
	
	#ifdef DyCh4
	{   DyCh4,  &ADCAvg4 	},
	#endif

	#ifdef DyCh5
	{   DyCh5,  &ADCAvg5 	}
	#endif	
};
#endif

//----------------------------------------------------------------------------
// The function of disabling ADC channel
//----------------------------------------------------------------------------
void DisableADCChannel(void)
{
	//VCH0CTL=0x1F;
	//VCH1CTL=0x1F;
	//VCH2CTL=0x1F;
	//VCH3CTL=0x1F;
    ADC->CHCTRL_b.CH0EN = 0;
    ADC->CHCTRL_b.CH1EN = 0;
    ADC->CHCTRL_b.CH2EN = 0;
    ADC->CHCTRL_b.CH3EN = 0;
	DisableADCModule();
}

//----------------------------------------------------------------------------
// The function of Enabling ADC channel
//----------------------------------------------------------------------------
void EnableADCChannel(void)
{
    Init_ADC();
}

void EnableADCFixChannel(void)
{
#ifdef FixCh0
	//VCH0CTL=FixCh0;
#endif

#ifdef FixCh1
	//VCH1CTL=FixCh1;
#endif
    ADC_TriggerConversion(ADC,ADC_REPEAT_CONVERSION,ADC_CH0_MSK|ADC_CH1_MSK);
}

void EnableADCDyChannel(void)
{
#ifdef ScanDyChannel1
	VCH2CTL=asADCDyInput1[ADCDyTable1Index].channelsel;
#endif

#ifdef ScanDyChannel2
	VCH3CTL=asADCDyInput2[ADCDyTable2Index].channelsel;
#endif
}

//----------------------------------------------------------------------------
// The function of scaning ADC channel
//----------------------------------------------------------------------------
void ScanADCFixChannel(void)
{
#ifdef FixCh0
#if 0
    if(IS_MASK_SET(VCH0CTL, DATVAL))
    {
        VCH0CTL |= 0x80;        // write clear data vaild flag
        Fix_ADCAvg0 = (VCH0DATM*0xFF)+VCH0DATL;
    }
#endif
	if (ADC_GetChDoneIntFlag(ADC, 0))
	{
        Fix_ADCAvg0 = (uint16_t)(ADC_GetConversionResult(ADC, 0));
    }
#endif	

#ifdef FixCh1
#if 0
    if(IS_MASK_SET(VCH1CTL, DATVAL))
    {
        VCH1CTL |= 0x80;        // write clear data vaild flag
        Fix_ADCAvg1 = (VCH1DATM*0xFF)+VCH1DATL;
    }
#endif
	if (ADC_GetChDoneIntFlag(ADC, 0))
	{
        Fix_ADCAvg1 = (uint16_t)(ADC_GetConversionResult(ADC, 1));
    }
#endif	
}

void ScanADCDyChannel1(void)
{
#ifdef ScanDyChannel1
    if(IS_MASK_SET(VCH2CTL, DATVAL))
    {
        *asADCDyInput1[ADCDyTable1Index].var = VCH2DATM;
        *(asADCDyInput1[ADCDyTable1Index].var+1) = VCH2DATL;
        ADCDyTable1Index++;
        if(ADCDyTable1Index >= (sizeof(asADCDyInput1)/sizeof(sADCDyinput)))
        {
            ADCDyTable1Index = 0x00;
        }
        
        VCH2CTL = asADCDyInput1[ADCDyTable1Index].channelsel;  // write clear data vaild flag
    }
#endif	
}

void ScanADCDyChannel2(void)
{
#ifdef ScanDyChannel2
    if(IS_MASK_SET(VCH3CTL, DATVAL))
    {
        *asADCDyInput2[ADCDyTable2Index].var = VCH3DATM;
        *(asADCDyInput2[ADCDyTable2Index].var+1) = VCH3DATL;
        ADCDyTable2Index++;
        if(ADCDyTable2Index >= (sizeof(asADCDyInput2)/sizeof(sADCDyinput)))
        {
            ADCDyTable2Index = 0x00;
        }
        
        VCH3CTL = asADCDyInput2[ADCDyTable2Index].channelsel;  // write clear data vaild flag
    }
#endif	
}

//----------------------------------------------------------------------------
// Disable ADC module
//----------------------------------------------------------------------------
void DisableADCModule(void)
{
	//CLEAR_MASK(ADCCFG, ADCEN);
    CLEAR_MASK( ADC->CTRL , BIT0);
}

//----------------------------------------------------------------------------
// Enable ADC module
//----------------------------------------------------------------------------
void EnableADCModule(void)
{
	//SET_MASK(ADCCFG, ADCEN);
    SET_MASK( ADC->CTRL , BIT0);
}

//----------------------------------------------------------------------------
// Init ADC module
//----------------------------------------------------------------------------
void Init_ADC(void)
{
    /* Initial ADC registers */
    //ADCCFG |= BIT0;
    //ADCCFG |= (AINITB + DOVE + EOCE);
    //VCH0CTL = 0x80;
    //VCH1CTL = 0x81;
    //VCH2CTL = 0x82;
    //VCH3CTL = 0x83;
    //ADCCFG |= BIT0;
    //ADCGCR |= ADCDBKEN;
    //ADCDyTable1Index = 0x00;
    //ADCDyTable2Index = 0x00;
	ADC_BypassLinearCalibraion(ADC, 0);
    ADC_BypassLowPassFilter(ADC, 0ul);
    
    ADC_BypassLinearCalibraion(ADC, 1);
    ADC_BypassLowPassFilter(ADC, 0xFFFul);    
    EnableADCFixChannel();
    //EnableADCDyChannel();
    EnableADCModule();
}

//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
/*
//------------------------------------------------------------------------------
    Part Number NCP15WB473D
    Resistance  47KOhm
    B-Constant  4050K   ADC_VCC:3.3V, PULL_UP: 47KOhm
//------------------------------------------------------------------------------
Temp'C Resistance(KOhm) ADC_V       ADC_10Bit      ADC_8Bit
-40.00   1690.586       3.210738231 996    03E4    249     00F9    -3
-35.00   1215.318       3.177130802 986    03D9    246     00F6    -3
-30.00   882.908        3.133209307 972    03CC    243     00F3    -4
-25.00   647.911        3.076805951 955    03BA    239     00EE    -6
-20.00   480.069        3.005731128 933    03A4    233     00E9    -7
-15.00   359.009        2.917988764 905    0389    226     00E2    -8
-10.00   270.868        2.81206161  873    0368    218     00DA    -10
 -5.00   206.113        2.687230209 834    0341    208     00D0    -11
  0.00   158.126        2.543879372 789    0315    197     00C5    -12
  5.00   122.267        2.383696172 740    02E3    185     00B8    -13
 10.00   95.256         2.209712068 686    02AD    171     00AB    -14
 15.00   74.754         2.026119881 629    0274    157     009D    -15
 20.00   59.075         1.837827009 570    023A    143     008E    -15
 25.00   47             1.65        512    0200    128     0080    -14
 30.00   37.636         1.467446477 455    01C7    114     0071    -13
 35.00   30.326         1.294206347 402    0191    100     0064    -12
 40.00   24.583         1.133284439 352    015F    88      0057    -11
 45.00   20.043         0.986559372 306    0132    77      004C    -10
 50.00   16.433         0.854900446 265    0109    66      0042    -9
 55.00   13.545         0.738269056 229    00E5    57      0039    -8
 60.00   11.223         0.636104289 197    00C5    49      0031    -7
 65.00   9.345          0.547315645 170    00A9    42      002A    -6
 70.00   7.818          0.470637382 146    0092    37      0024    -5
 75.00   6.571          0.404776838 126    007D    31      001F    -4
 80.00   5.548          0.34841288  108    006C    27      001B    -4
 85.00   4.704          0.30023209  93     005D    23      0017    -3
 90.00   4.004          0.259062034 80     0050    20      0014    -3
 95.00   3.422          0.223961763 69     0045    17      0011    -2
 100.00  2.936          0.194024351 60     003C    15      000F    -2
 105.00  2.528          0.168438055 52     0034    13      000D    -2
 110.00  2.184          0.146535459 45     002D    11      000B    -1
 115.00  1.893          0.127766756 40     0027    10      0009    -1
 120.00  1.646          0.111659746 35     0022    9       0008    -1
 125.00  1.436          0.09783632  30     001E    8       0007    -8
//------------------------------------------------------------------------------
*/
/*-----------------------------------------------------------------------------
 * @subroutine - Get_ADC_Thermistor
 * @function - Get_ADC_Thermistor
 * @upstream - service_500mS_B
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
const unsigned char code NCP15WB473D[] =
{
    /* -0-  -1-  -2-  -3-  -4-  -5-  -6-  -7-  -8-  -9-  -A-  -B-  -C-  -D-  -E-  -F- */
    125, 125, 125, 125, 125, 125, 125, 125, 120, 115, 113, 110, 108, 105, 103, 100,   //0
    98,  95,  94,  92,  90,  89,  87,  85,  84,  83,  81,  80,  79,  78,  76,  75,   //1
    74,  73,  72,  71,  70,  69,  69,  68,  67,  66,  65,  64,  63,  62,  61,  61,   //2
    60,  60,  59,  58,  58,  57,  56,  56,  55,  55,  54,  53,  53,  52,  52,  51,   //3
    51,  50,  50,  50,  49,  49,  48,  48,  47,  47,  46,  46,  45,  45,  44,  44,   //4
    43,  43,  42,  42,  41,  41,  40,  40,  39,  39,  39,  38,  38,  38,  37,  37,   //5
    37,  36,  36,  36,  35,  35,  34,  34,  34,  33,  33,  33,  32,  32,  31,  31,   //6
    30,  30,  29,  29,  29,  28,  28,  28,  27,  27,  27,  26,  26,  26,  25,  25,   //7
    25,  24,  24,  24,  23,  23,  23,  22,  22,  22,  21,  21,  21,  20,  20,  20,   //8
    19,  19,  19,  18,  18,  18,  17,  17,  17,  16,  16,  16,  15,  15,  15,  14,   //9
    14,  14,  13,  13,  13,  12,  12,  12,  11,  11,  10,  10,   9,   9,   8,   8,   //A
    8,   8,   7,   7,   7,   6,   6,   6,   5,   5,   5,   4,   4,   4,   3,   3,    //B
    3,   2,   2,   1,   1,   0,   0,   0,   0,   0,   0,   0, 201, 202, 203, 204,    //C
    205, 205, 206, 206, 207, 207, 208, 208, 209, 209, 210, 210, 211, 212, 212, 213,   //D
    214, 214, 215, 216, 217, 217, 218, 219, 219, 220, 221, 222, 223, 224, 225, 226,   //E
    227, 228, 229, 230, 232, 234, 235, 237, 239, 240, 240, 240, 240, 240, 240, 240,   //F
};
/* PS: 200=0'C ~ 240=-40'C */
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - Service_Scan_ADC
 * @function - Process ADC Channel-0,N Data
 * @upstream - service_100mS_A
 * @input    -
 * @return   -
 * @note     -
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
void Service_Scan_ADC(void)
{
#if 1
    //if (GPCRI1 == ALT)
    if(GPIO->GCR_b[75].MFCTRL == 1)
    {
        //if (IS_MASK_SET(VCH1CTL, BIT7))
        if (ADC_GetChDoneIntFlag(ADC, 1))
        {
           // wADC[1] = (((WORD)VCH1DATM << 8) | VCH1DATL);
           wADC[1] = (uint16_t)(ADC_GetConversionResult(ADC, 1));
            xADC[1] = wADC[1] >> 2;
            AVG_ADC2 = xADC[1]; //Table location           
            xADC_Count++;
        }
        ///ADCCFG |= (BIT0 + BIT1);
        ///GPCRI1 = ALT;
        ///VCH1CTL = 0x81; //981004-201124-M from VCH2CTL=0x82
    }
    else
    {
        ///ADCCFG |= (BIT0 + BIT1);
        ///GPCRI1 = ALT;
        ///VCH1CTL = 0x81;
    }
#else
    if (GPCRI0 == ALT)
    {
        if (IS_MASK_SET(VCH0CTL, BIT7))
        {
            wADC[0] = (((WORD)VCH0DATM << 8) | VCH0DATL);
            xADC[0] = wADC[0] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI0 = INPUT;
        GPCRI1 = ALT;
        VCH1CTL = 0x81;
    }
    else if (GPCRI1 == ALT)
    {
        if (IS_MASK_SET(VCH1CTL, BIT7))
        {
            wADC[1] = (((WORD)VCH1DATM << 8) | VCH1DATL);
            xADC[1] = wADC[1] >> 2;
			AVG_ADC2 = xADC[1];
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI1 = INPUT;
#if 1
        GPCRI2 = ALT;
        VCH2CTL = 0x82;
#else
        GPCRI3 = ALT;
        VCH3CTL = 0x90;
#endif
    }
    else if (GPCRI2 == ALT)
    {
        if (IS_MASK_SET(VCH2CTL, BIT7))
        {
            wADC[2] = (((WORD)VCH2DATM << 8) | VCH2DATL);
            xADC[2] = wADC[2] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI2 = INPUT;
        GPCRI3 = ALT;
        VCH3CTL = 0x83;
    }
    else if (GPCRI3 == ALT)
    {
        if (IS_MASK_SET(VCH3CTL, BIT7))
        {
            wADC[3] = (((WORD)VCH3DATM << 8) | VCH3DATL);
            xADC[3] = wADC[3] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI3 = INPUT;
        GPCRI4 = ALT;
        VCH4CTL = 0x90;
    }
    else if (GPCRI4 == ALT)
    {
        if (IS_MASK_SET(VCH4CTL, BIT7))
        {
            wADC[4] = (((WORD)VCH4DATM << 8) | VCH4DATL);
            xADC[4] = wADC[4] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI4 = INPUT;
#if 0
        GPCRI5 = ALT;
        VCH5CTL = 0x90;
#else
        GPCRI0 = ALT;
        VCH0CTL = 0x80;
#endif
    }
    else if (GPCRI5 == ALT)
    {
        if (IS_MASK_SET(VCH5CTL, BIT7))
        {
            wADC[5] = (((WORD)VCH5DATM << 8) | VCH5DATL);
            xADC[5] = wADC[5] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI5 = INPUT;
        GPCRI6 = ALT;
        VCH6CTL = 0x90;
    }
    else if (GPCRI6 == ALT)
    {
        if (IS_MASK_SET(VCH6CTL, BIT7))
        {
            wADC[6] = (((WORD)VCH6DATM << 8) | VCH6DATL);
            xADC[6] = wADC[6] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI6 = INPUT;
        GPCRI7 = ALT;
        VCH7CTL = 0x90;
    }
    else if (GPCRI7 == ALT)
    {
        if (IS_MASK_SET(VCH7CTL, BIT7))
        {
            wADC[7] = (((WORD)VCH7DATM << 8) | VCH7DATL);
            xADC[7] = wADC[7] >> 2;
            xADC_Count++;
        }
        ADCCFG |= (BIT0 + BIT1);
        GPCRI7 = INPUT;
        GPCRI0 = ALT;
        VCH0CTL = 0x80;
    }
    else
    {
        ADCCFG |= (BIT0 + BIT1);
        GPCRI1 = INPUT;
        GPCRI0 = ALT;
        VCH0CTL = 0x80;
    }
#endif
}
//-----------------------------------------------------------------------------
void Get_ADC0_Thermistor(void)
{
    //-------------------------------------------------------------------------
    //if (IS_eSPI_SLP_S3_LO())
    //{
    //    return;
    //}
    //-------------------------------------------------------------------------
    ITempB05 = xADC[0];
    xEC_T1_THR = NCP15WB473D[ITempB05];
    if (xEC_T1_THR >= 200)
    {
        /* Under 0'C */
        xEC_T1_THR = 0;
#if 0   //1: Support Intel DPTF
        xEC_Sensor_1_T = 0;
#endif
        return;
    }
    //-------------------------------------------------------------------------
    wEC_T1_THR_ACC += xEC_T1_THR;
    xEC_T1_CNT++;
    if (xEC_T1_CNT >= 8)
    {
        xEC_T1_CNT = 0;
        xEC_T1_AVG = wEC_T1_THR_ACC / 8;
        wEC_T1_THR_ACC = 0;
#if 0   //1: Support Intel DPTF
        xEC_Sensor_1_T = xEC_T1_AVG;

        if (xEC_Sensor_1_T >= xEC_T1_HiLimit)
        {
            xEC_T1_HiLimit = xEC_Sensor_1_T + 2;
            if (xEC_Sensor_1_T >= 2)
            {
                xEC_T1_LoLimit = xEC_Sensor_1_T - 2;
            }
            xEC_T1_SendEvent = 1;
        }
        else
        {
            ITempB05 = 0;
            if (xEC_T1_LoLimit > 2)
            {
                ITempB05 = xEC_T1_LoLimit - 2;
            }
            if (xEC_Sensor_1_T < ITempB05)
            {
                xEC_T1_HiLimit = xEC_Sensor_1_T + 2;
                if (xEC_Sensor_1_T >= 2)
                {
                    xEC_T1_LoLimit = xEC_Sensor_1_T - 2;
                    xEC_T1_SendEvent = 1;
                }
            }
        }
#endif
    }
    //-------------------------------------------------------------------------
}

/*-----------------------------------------------------------------------------
 * @subroutine - Get_ADC1_Thermistor
 * @function - Get_ADC1_Thermistor
 * @upstream - service_500mS_B
 * @input    - None
 * @return   - None
 * @note     - None
 *---------------------------------------------------------------------------*/
void Get_ADC1_Thermistor(void)
{
    //-------------------------------------------------------------------------
    //if (IS_eSPI_SLP_S3_LO())
    //{
    //    return;
    //}
    //-------------------------------------------------------------------------
    ITempB05 = xADC[1];
    xEC_T2_THR = NCP15WB473D[ITempB05];
#if 0   //1: Support Intel DPTF
    xEC_SensorT_Error_F = 0;
#endif
    if ((xEC_T2_THR >= 200) || (xEC_T2_THR < 5)) /* Under 0'C */
    {
        xEC_T2_THR = 0;
#if 0   //1: Support Intel DPTF
        xEC_Sensor_2_T = 0;
        if ((xEC_T2_THR >= 226) || (xEC_T2_THR < 5))
        {
            SET_MASK(xEC_SensorT_Error_F, F_Skin_Sensor_error);
        }
#endif
        return;
    }
    //-------------------------------------------------------------------------
    wEC_T2_THR_ACC += xEC_T2_THR;
    xEC_T2_CNT++;
    if (xEC_T2_CNT >= 8)
    {
        xEC_T2_CNT = 0;
        xEC_T2_AVG = wEC_T2_THR_ACC / 8; //0x172
        wEC_T2_THR_ACC = 0;
		if ((xEC_T2_AVG >=0) && (xEC_T2_AVG <= 70))
		{           			
		   AVG_ADC1 = xEC_T2_AVG; //0x2B6
		}
        else
        {           
		   AVG_ADC1 = 25;
		}   
       	
#if 0   //1: Support Intel DPTF
        xEC_Sensor_2_T = xEC_T2_AVG;

        if (xEC_Sensor_2_T >= xEC_T2_HiLimit)
        {
            xEC_T2_HiLimit = xEC_Sensor_2_T + 2;
            if (xEC_Sensor_2_T >= 2)
            {
                xEC_T2_LoLimit = xEC_Sensor_2_T - 2;
            }
            xEC_T2_SendEvent = 1;
        }
        else
        {
            ITempB05 = 0;
            if (xEC_T2_LoLimit > 2)
            {
                ITempB05 = xEC_T2_LoLimit - 2;
            }
            if (xEC_Sensor_2_T < ITempB05)
            {
                xEC_T2_HiLimit = xEC_Sensor_2_T + 2;
                if (xEC_Sensor_2_T >= 2)
                {
                    xEC_T2_LoLimit = xEC_Sensor_2_T - 2;
                    xEC_T2_SendEvent = 1;
                }
            }
        }
#endif
    }
    //-------------------------------------------------------------------------
}