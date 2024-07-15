#include "RTK_Include.h"
#if 1
// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 1 write 
// Output:
//          0 : Fail
//          1 : OK
// ----------------------------------------------------------------------------
uint8_t PECI_WritePowerLimit1(void)
{
    uint8_t reslut;
    uint16_t UnitofPower;
    uint16_t UnitofTau;
    uint16_t PL1_TDPWatts;
    uint8_t PL1_PL1T;
    
	PECI_PL1TDP = WTDP;

    UnitofPower =(uint16_t)(1<<PECI_PowerUnit);
    PL1_TDPWatts = PECI_PL1TDP * UnitofPower;
    //PL1_TDPWatts = PowerLimit1TDP * UnitofPower;
    UnitofTau = (uint16_t)(1<<PECI_TimeUnit);
    //PL1_PL1T = (PowerLimit1Tau * UnitofTau)<<1;
    PL1_PL1T = 0x6E<<1;
        
    PECIWriteBuffer[0]=(uint8_t)(PL1_TDPWatts);
    PECIWriteBuffer[1]=(uint8_t)((PL1_TDPWatts)>>8 | 0x80);   // Set power limit 1 TDP value
    PECIWriteBuffer[2]=PL1_PL1T;            // bit17 ~ bit23 Power_Limit_1_Time
    PECIWriteBuffer[3]=0x00;
    
    //if(PECI_WrPkgConfig(PECI_CPU_ADDR, &PECIWriteBuffer, PECI_Domain_0, 0, PECI_Index_PPL1, 0x00, 0x00, 0x01, 0x0A))
	if(PECI_Write_Pkg_Config(0x30,1,PECI_Index_PPL1,0x0000,PECIWriteBuffer))
    {
        reslut = 0x01;
    }
    else
    {
        reslut = 0x00;
    }
    return(reslut);
}



// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 1 read
// Output:
//          0 : Fail
//          1 : OK
// ----------------------------------------------------------------------------
//uint8_t PECI_ReadPowerLimit1(void)
//{
//    uint8_t reslut;
//    
//    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_PPL1, 0x00, 0x00, 0x05, 0x05))
//    {
//        RTDP = (PECIReadBuffer[0]+((PECIReadBuffer[1] &= 0x7F) *256))/(1<<PECI_PowerUnit);
//        PowerLimit1Tau = PECIReadBuffer[2]>>1;
//        reslut = 0x01;
//    }
//    else
//    {
//        reslut = 0x00;
//    }
//    return(reslut);
//}

void PECI_WritePowerLimit2(uint8_t watts)
{
     uint16_t UnitofPower;
     uint16_t PL2_SettingWatts;
    //if(PECI_ReadPowerUnit()==0x01)
    //{
        UnitofPower =(uint16_t)(1<<PECI_PowerUnit);
        PL2_SettingWatts = watts * UnitofPower;
        
        PECIWriteBuffer[0]=(uint8_t)(PL2_SettingWatts);
        PECIWriteBuffer[1]=(uint8_t)((PL2_SettingWatts)>>8| 0x80);   // Set power limit 2 value
        PECIWriteBuffer[1]|=0x80;                   // Enables power limit 2
        PECIWriteBuffer[2]=0x00;
        PECIWriteBuffer[3]=0x00;
        //if(PECI_WrPkgConfig(PECI_CPU_ADDR, &PECIWriteBuffer, PECI_Domain_0, 0, PECI_Index_PPL2, 0x00, 0x00, 0x01, 0x0A))
		if(PECI_Write_Pkg_Config(0x30,1,PECI_Index_PPL2,0x0000,PECIWriteBuffer))
        {
            BIT_CLR(PECI_Ctrl, SetPL2Request);
        }
        else
        {

        }
    //}
    //else
    //{

    //}
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 2 read 
// ----------------------------------------------------------------------------
//void PECI_ReadPowerLimit2(void)
//{
//    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_PPL2, 0x00, 0x00, 0x05, 0x05))
//    {
//         //RTDP2 = (PECIReadBuffer[0]) / (1<<PECI_PowerUnit); //981004-221228-R
//    }
//    else
//    {
//         //RTDP2 = 0X2;
//    }
//}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 3 write 
// ----------------------------------------------------------------------------
void PECI_WritePowerLimit3(uint16_t watts)
{
    // uint16_t UnitofPower;
     uint16_t PL3_SettingWatts;
    
        //UnitofPower = 1<<PECI_PowerUnit;
        //PL3_SettingWatts = watts * UnitofPower;
		PL3_SettingWatts = watts;
        
        PECIWriteBuffer[0]=(uint8_t)(PL3_SettingWatts);
        PECIWriteBuffer[1]=(uint8_t)((PL3_SettingWatts)>>8| 0x80);   // Set power limit 3 value
        PECIWriteBuffer[1]|=0x80;                   // Enables power limit 3
        PECIWriteBuffer[2]= WTDP3_TIME;
        PECIWriteBuffer[3]= WTDP3_DUTY;		
        //if(PECI_WrPkgConfig(PECI_CPU_ADDR, &PECIWriteBuffer, PECI_Domain_0, 0, PECI_Index_PPL3, 0x00, 0x00, 0x01, 0x0A))
		if(PECI_Write_Pkg_Config(0x30,1,PECI_Index_PPL3,0x0000,PECIWriteBuffer))
        {		   
            BIT_CLR(PECI_Ctrl, SetPL3Request);
        }
        else
        {
          
        }
    //}
    //else
    //{

    //}
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 2 read 
// ----------------------------------------------------------------------------
//void PECI_ReadPowerLimit3(void)
//{
//    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_PPL3, 0x00, 0x00, 0x05, 0x05))
//    {
//         RTDP3 = (PECIReadBuffer[0]) / (1<<PECI_PowerUnit);
//    }
//    else
//    {
//         //RTDP3 = 0X2;
//    }
//}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 2 write 
// ----------------------------------------------------------------------------
void PECI_WritePowerLimit4(uint8_t watts)
{
     //uint16_t UnitofPower;
     uint16_t PL4_SettingWatts;
    //if(PECI_ReadPowerUnit()==0x01)
    //{
        //UnitofPower = 1<<PECI_PowerUnit;
        PL4_SettingWatts = watts * 8 ;
        
        PECIWriteBuffer[0]=(uint8_t)(PL4_SettingWatts);
        PECIWriteBuffer[1]=(uint8_t)((PL4_SettingWatts)>>8);   // Set power limit 4 value
        //PECIWriteBuffer[1]|=0x80;                   // Enables power limit 2
        PECIWriteBuffer[2]=0x00;
        PECIWriteBuffer[3]=0x00;		
        //if(PECI_WrPkgConfig(PECI_CPU_ADDR, &PECIWriteBuffer, PECI_Domain_0, 0, PECI_Index_PPL4, 0x00, 0x00, 0x01, 0x0A))
		if(PECI_Write_Pkg_Config(0x30,1,PECI_Index_PPL4,0x0000,PECIWriteBuffer))
        {		   
            BIT_CLR(PECI_Ctrl, SetPL4Request);
        }
        else
        {
           
        }
    //}
    //else
    //{

    //}
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power SKU unit read
// Output:
//          0 : Fail
//          1 : OK
// ----------------------------------------------------------------------------
uint8_t PECI_ReadPowerUnit(void)
{
    uint8_t result;
    //if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_PPSH, 0x00, 0x00, 0x05, 0x05))
	if(PECI_Read_Pkg_Config(0x30,1,26,0x0000,PECIReadBuffer))
    {
        PECI_PowerUnit = (PECIReadBuffer[0]&0x0F);      // bit 0 ~ bit3
        PECI_EnergyUnit = (PECIReadBuffer[1]&0x1F);     // bit 8 ~ bit12
        PECI_TimeUnit = (PECIReadBuffer[2]&0x0F);       // bit 16 ~ bit19
        result = 0x01;
    }
    else
    {
        result = 0x00;
    }
    return(result);
}
#endif

// ----------------------------------------------------------------------------
// The function of PECI3.0 Read the Maximum Allowed Processor Temperature
// ----------------------------------------------------------------------------
void PECI_ReadCPUTJMAX(void)
{
    //if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_TTR, 0x00, 0x00, 0x05, 0x05))
	if(PECI_Read_Pkg_Config(0x30,1,PECI_Index_TTR,0x0000,PECIReadBuffer))
    {
        ReadCPUTjmaxCUNT = 0x00;
        CPUTjmax = PECIReadBuffer[0];
    }
    else
    {
        if(++ReadCPUTjmaxCUNT>=PECI_Read_TjmaxTO)
        {
            ReadCPUTjmaxCUNT = 0x00;
            CPUTjmax = PECI_CPU_Tjmax; // Set default value if re-try PECI_Read_TjmaxTO times
        }
    }
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 CPU temperature read
// ----------------------------------------------------------------------------
void PECI_ReadCPUTemp(void)
{
    int16_t Temp;
    //if(PECI_GetTemp(PECI_CPU_ADDR,&PECIReadBuffer,PECI_Domain_0,2,1)) // Read OK
	if(PECI_Get_Temp(0x30,&Temp))
    {
        //cputemp = (PECIReadBuffer[1]<<8)+PECIReadBuffer[0]; // MSB+LSB
        //Temp = (~Temp)+1;                             // 2's complement
        //tempoffset = Temp>>6;                            // 1/64 degrees centigrade
        if(Temp<=CPUTjmax)        // PECI thermal reading temperature readings are                
        {                               // not reliable at temperatures above Tjmax
            PECI_CPU_temp =(uint8_t)(CPUTjmax-Temp);  // Save temperature
        }
        else
        {

        }
    }
    else        // Read fail
    {

    }
}
#if 0
// ----------------------------------------------------------------------------
// Clear PECI turbo control variables
// ----------------------------------------------------------------------------
void PECI_ClearTCVariables(void)
{
    PECI_ClearPowerSKUUnit();
  //  PowerLimit1TDP=0x00;
    PowerLimit2Max=0x00; 
    PECI_PL2Watts=0x00;
    PowerLimit1Tau=0x00;
    PECI_Ctrl = 0x00;
    PECI_Algorithm_Delay = 0x00;
}

// ----------------------------------------------------------------------------
// Clear Power SKU unit variables
// ----------------------------------------------------------------------------
void PECI_ClearPowerSKUUnit(void)
{
    PECI_PowerUnit = 0x00;
    PECI_EnergyUnit = 0x00;
    PECI_TimeUnit = 0x00;
}





// ----------------------------------------------------------------------------
// The function of battery mode turbo control
// ----------------------------------------------------------------------------
void PECI_ACToDCModeTurboCtrl(void)
{
    uint8_t retry;
    
    //PCH_PROCHOT_L = 0;

    for (retry=0x00; retry<5; retry++)         // Re-try
    {
        PECI_SETPL2Watts(PECI_PL1TDP);

        if (IS_MASK_CLEAR(PECI_Ctrl, SetPL2Request))
            break;
    }

    //PCH_PROCHOT_L = 1;
}

// ----------------------------------------------------------------------------
// The function of setting PL2 watts
// ----------------------------------------------------------------------------
void PECI_SETPL2Watts(uint8_t watts)
{
    PECI_PL2Watts = watts;
    SET_MASK(PECI_Ctrl, SetPL2Request);
    PECI_WritePowerLimit2(PECI_PL2Watts);
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package power limit 2 write 
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// The function of PECI3.0 CPU temperature read
// ----------------------------------------------------------------------------
void PECI_ReadCPUTemp(void)
{
    uint16_t cputemp;
    uint8_t tempoffset;
    
    if(PECI_GetTemp(PECI_CPU_ADDR,&PECIReadBuffer,PECI_Domain_0,2,1)) // Read OK
    {
        cputemp = (PECIReadBuffer[1]<<8)+PECIReadBuffer[0]; // MSB+LSB
        cputemp = (~cputemp)+1;                             // 2's complement
        tempoffset = cputemp>>6;                            // 1/64 degrees centigrade
        if(tempoffset<=CPUTjmax)        // PECI thermal reading temperature readings are                
        {                               // not reliable at temperatures above Tjmax
            PECI_CPU_temp = CPUTjmax-tempoffset;  // Save temperature
        }
        else
        {

        }
    }
    else        // Read fail
    {

    }
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Read the Maximum Allowed Processor Temperature
// ----------------------------------------------------------------------------
void PECI_ReadCPUTJMAX(void)
{
    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_TTR, 0x00, 0x00, 0x05, 0x05))
    {
        ReadCPUTjmaxCUNT = 0x00;
        CPUTjmax = PECIReadBuffer[2];
    }
    else
    {
        if(++ReadCPUTjmaxCUNT>=PECI_Read_TjmaxTO)
        {
            ReadCPUTjmaxCUNT = 0x00;
            CPUTjmax = PECI_CPU_Tjmax; // Set default value if re-try PECI_Read_TjmaxTO times
        }
    }
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 DRAM rank channel temperature read
// ----------------------------------------------------------------------------
void PECI_ReadDRAMTemperature(void)
{
    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_DRCTR, 0x00, 0x00, 0x05, 0x05))
    {
        TDIM0_temp = PECIReadBuffer[0];
        TDIM1_temp = PECIReadBuffer[1];
    }
    else
    {
        ;
    }
}

// ----------------------------------------------------------------------------
// The function of PECI3.0 Package temperature read
// ----------------------------------------------------------------------------
void PECI_ReadPkgTemperature(void)
{
    uint16_t pkgtemp;
    uint8_t tempoffset;
    if(PECI_RdPkgConfig(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, PECI_Index_PTR, 0xFF, 0x00, 0x05, 0x05))
    {
        pkgtemp = (PECIReadBuffer[1]<<8)+PECIReadBuffer[0]; // MSB+LSB
        pkgtemp = (~pkgtemp)+1;                             // 2's complement
        tempoffset = pkgtemp>>6;                            // 1/64 degrees centigrade
        if(tempoffset<=CPUTjmax)  // PECI thermal reading temperature readings are                
        {                               // not reliable at temperatures above Tjmax
            TPkg_temp = CPUTjmax-tempoffset;  // Save temperature
        }
    }
    else
    {
        ;
    }
}

// ----------------------------------------------------------------------------
// The example of PECI3.0 read MSR address 0x0400
// ----------------------------------------------------------------------------
void PECI_ReadMSRExample(void)
{
    if(PECI_RdIAMSR(PECI_CPU_ADDR, &PECIReadBuffer, PECI_Domain_0, 0, 0, 0x00, 0x04, 0x09, 0x05))
    {

    }
    else
    {

    }
}

// ----------------------------------------------------------------------------
// Get current platform total power
// ----------------------------------------------------------------------------
#if 0         // marked by Ted
void PECI_CheckCurrentPlatformPower(void)
{
    uint16_t SysCurrent;
    SysCurrent = Read_SYS_I();
    //PECI_SystemWatts
}
#endif

// ----------------------------------------------------------------------------
// The Algorithm of AC turbo control
// ----------------------------------------------------------------------------
void PECI_ACTurboControlAlgorithm(void)
{
    uint8_t NewPL2Watts,BATTERY_CHARGE_BUDGET,UpdatPL2;
    //if(PECI_PL2Watts==0x00)                   // Not ready
    //{
    //    return;
    //}
    
    if(IS_MASK_CLEAR(PECI_Ctrl, SetPL2Request)) // No any request of PL2 power setting
    {
        UpdatPL2=0x00;
        BATTERY_CHARGE_BUDGET=0x00;

        if(IS_MASK_SET(BT1_STATUS1,bat_InCharge))
        {
            if(BAT1_RSOC>50)
            {
                BATTERY_CHARGE_BUDGET = 0x00;   // 0W
            }
            else
            {
                BATTERY_CHARGE_BUDGET = 20;     // 20W
            }
        }
        
        NewPL2Watts = PECI_PL2Watts+PECI_AdaptorWatts-PECI_SystemWatts-BATTERY_CHARGE_BUDGET;
        
        if(NewPL2Watts>PowerLimit2Max)
        {
            NewPL2Watts = PowerLimit2Max;
            if(NewPL2Watts!=PECI_PL2Watts)
            {
                UpdatPL2=0x01;
            }
            //UpdatPL2=0x01;
        }
        else if(NewPL2Watts<PECI_PL1TDP)
        {
            NewPL2Watts = PECI_PL1TDP;
            if(NewPL2Watts!=PECI_PL2Watts)
            {
                UpdatPL2=0x01;
            }
            //UpdatPL2=0x01;
        }
        else
        {
            if(NewPL2Watts!=PECI_PL2Watts)
            {
                UpdatPL2=0x01;
            }
        }

        if(UpdatPL2==0x01)
        {
            PECI_SETPL2Watts(NewPL2Watts);
        }
    }
    else
    {
        PECI_WritePowerLimit2(PECI_PL2Watts);
    }
}

// ----------------------------------------------------------------------------
// decide adaptor watts
// ----------------------------------------------------------------------------
void ChecknSetAdaptorWatts(void)
{
    PECI_AdaptorWatts = ACPowerWatts;   // Set 65w adaptor
    PowerLimit2Max = PowerLimit2Max_Value;
}

// ----------------------------------------------------------------------------
// PECI power limit 2 control function
// ----------------------------------------------------------------------------
void PECI_PowerCtrlAlgorithm(void)
{
    switch(PECI_PowerCtrlStep)
    {
        case PECI_Step_Start:
            if(SystemIsS0)
            {
                //if(IS_MASK_SET(POWER_FLAG1, adapter_in))    // AC mode
				if ((IS_MASK_SET(POWER_FLAG1, adapter_in)) || (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)))
                {
                    ChecknSetAdaptorWatts();
                    SetPECIPowerCtrlStep(PECI_Step_ReadPSKUUnit);
                }
                else                                // DC mode
                {

                }
            }
            break;

        case PECI_Step_ReadPSKUUnit:
            if(PECI_ReadPowerUnit()==0x01)      // Read power SKU unit OK
            {
                SetPECIPowerCtrlStep(PECI_Step_ReadPL1);
            }
            break;

        case PECI_Step_ReadPL1:
            if(PECI_ReadPowerLimit1()==0x01)    // Read power limit 1 done
            {
                if(PECI_PL1TDP!=0x00)
                {
                    SetPECIPowerCtrlStep(PECI_Step_Algorithm);
                }
                else
                {
                    PECI_PL1TDP = PowerLimit1_TDP;
                    SetPECIPowerCtrlStep(PECI_Step_WritePL1);
                }
            }
            break;

        case PECI_Step_WritePL1:
            if(PECI_WritePowerLimit1()==0x01)
            {
                SetPECIPowerCtrlStep(PECI_Step_Algorithm);
            }
            break;
                
        case PECI_Step_Algorithm:
            if(++PECI_Algorithm_Delay>=AlgorithmDelayTime)
            {
                PECI_Algorithm_Delay = 0x00;
                PECI_ACTurboControlAlgorithm();
            }
            break;
            
        case PECI_Step_Stop:
            break;
        
        case PECI_Step_StopRequest:
            PECI_ClearTCVariables();
            SetPECIPowerCtrlStep(PECI_Step_Stop);
            break;
                
        default:
            break;
    }  
}

// ----------------------------------------------------------------------------
// CPU Power control via PECI
// ----------------------------------------------------------------------------
void PECI_PowerCtrlCenter(void)
{
    if (SystemIsS0)          // For PECI stress tool
    {
        if (IS_MASK_SET(PSTB_CmdStatus, ServivePECIStressTool))
        {
            if (++PSTB_Timer >= 0x02)    // 10 ms
            {
                PSTB_Timer = 0x00;

                if (PSTB_RepeatIntervalCount == 0x00)
                    ProcessPSTCmd();
                else
                    PSTB_RepeatIntervalCount--;
            }

            return;
        }
    }

    #if 0          // marked by Ted
    if (SystemIsS0)
        PECI_CheckCurrentPlatformPower();       // Get current platform total power every 5ms
    #endif

    #ifdef PECI_Support
        #if ACTurboControlAlgorithm
        PECI_PowerCtrlAlgorithm();
        #endif
    #endif
    

}

// ----------------------------------------------------------------------------
// Set PECI power control step
// ----------------------------------------------------------------------------
void SetPECIPowerCtrlStep(uint8_t step)
{
    PECI_PowerCtrlStep = step;
}

// ****************************************************************************
// PECI Stress Tool
// ****************************************************************************
// ----------------------------------------------------------------------------
// Process PECP stress tool command
// ----------------------------------------------------------------------------
void ProcessPSTCmd(void)
{
    uint8_t writelen, readlen,bufindex;
    uint8_t error;
    Xuint8_t *bufpoint;
    
    error = 0x00;
    bufindex = 0x00;

    bufpoint = &PSTB_RepeatCycle;
    
    if(PSTB_RepeatCycle!=0x00)
    {
        writelen = PECI_StressToolBuf[PSTB_WriteLength];
        readlen = PECI_StressToolBuf[PSTB_ReadLength];
        
        PECI_HostEnable();
        HOTRADDR = PECI_StressToolBuf[PSTB_ClientAddress];
        HOWRLR = PECI_StressToolBuf[PSTB_WriteLength];
        HORDLR = PECI_StressToolBuf[PSTB_ReadLength];
            
        if(writelen!=0x00)
        {
            HOCMDR = PECI_StressToolBuf[PSTB_CmdCode];
            writelen--;
            bufindex++;
        }
        if(PECI_StressToolBuf[PSTB_CmdCode]==PECI_CMD_WrPkgConfig)
        {
            PECI_HostControl(AWFCS_EN);
            writelen--;
        }

        while(writelen!=0x00)
        {
            HOWRDR = PECI_StressToolBuf[PSTB_CmdCode+bufindex];
            writelen--;
            bufindex++;
        }

        if(PECI_CheckHostBusy())
        {
            PECI_HostControl(START);
            if(PECI_CheckHostFinish())  // OK
            {
                if(PECI_StressToolBuf[PSTB_CmdCode]==PECI_CMD_WrPkgConfig)
                {
                    bufindex++;         // AWFCS
                }
                bufindex++;             // FCS

                while(readlen!=0x00)
                {
                    PECI_StressToolBuf[PSTB_CmdCode+bufindex] = HORDDR;
                    readlen--;
                    bufindex++;
                }
                error = 0x00;
            }
            else                        // error
            {
                error = 0x01;
            }
        }
        else
        {
            error = 0x01;
        }
        
        PSTB_RepeatCycle--;
        PECI_StressToolBuf[PSTB_RepeatCycle3] = *bufpoint;
        bufpoint++;
        PECI_StressToolBuf[PSTB_RepeatCycle2] = *bufpoint;
        bufpoint++;
        PECI_StressToolBuf[PSTB_RepeatCycle1] = *bufpoint;
        bufpoint++;
        PECI_StressToolBuf[PSTB_RepeatCycle0] = *bufpoint;
        
        PSTB_RepeatIntervalCount = PECI_StressToolBuf[PSTB_RepeatInterval];
        PECI_HostDisable();
        ResetPECIStatus();
        
        if(error==0x01)
        {
            if(PECI_StressToolBuf[PSTB_CmdCode]==PECI_CMD_WrPkgConfig)
            {
                bufindex++;             // AWFCS
            }
            bufindex++;                 // FCS

            while(readlen!=0x00)        // Clear read length buffer
            {
                PECI_StressToolBuf[PSTB_CmdCode+bufindex] = 0x00;
                readlen--;
                bufindex++;
            }

            PECI_ErrorCount++;
            if(PECI_StressToolBuf[PSTB_StopOnError]!=0x00)
            {
                BIT_CLR(PSTB_CmdStatus, ServivePECIStressTool);
            }
        }
    }
    else
    {
        BIT_CLR(PSTB_CmdStatus, ServivePECIStressTool);
    }
}

// ----------------------------------------------------------------------------
// Issue PECI command
// ----------------------------------------------------------------------------
void PECI_PSTIssueCmd(void)
{
    Xuint8_t *xptr;
    
    PECI_ErrorCount = 0x00;
    PSTB_Timer = 0x00;
    PSTB_RepeatIntervalCount = 0x00;
    SET_MASK(PSTB_CmdStatus, ServivePECIStressTool);
    xptr = &PSTB_RepeatCycle;
    *xptr = PECI_StressToolBuf[PSTB_RepeatCycle3];
    xptr++;
    *xptr = PECI_StressToolBuf[PSTB_RepeatCycle2];
    xptr++;
    *xptr = PECI_StressToolBuf[PSTB_RepeatCycle1];
    xptr++;
    *xptr = PECI_StressToolBuf[PSTB_RepeatCycle0];
}

// ----------------------------------------------------------------------------
// End PECI command
// ----------------------------------------------------------------------------
void PECI_PSTEndCmd(void)
{
    PECI_ClearPSTVariables();
}

// ----------------------------------------------------------------------------
// Write PECI stress tool buffer command
// ----------------------------------------------------------------------------
void PECI_PSTWriteBuffer(void)
{
    PECI_StressToolBuf[BufferLength-PM3DataCount] = PM3Data;
}

// ----------------------------------------------------------------------------
// Read PECI stress tool buffer command
// ----------------------------------------------------------------------------
void PECI_PSTReadBuffer(void)
{
    StressToolReadBufIndex = BufferLength;
    
    /*
    uint8_t index, timeout;

    timeout = 0x00;

    for(index=0x00;index<BufferLength;index++)
    {
        TR1 = 0;                 	    // Disable timer1
        ET1 = 0;                  	    // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_30ms>>8;            // Set timer1 counter 30ms
        TL1 = Timer_30ms;               // Set timer1 counter 30ms
        TF1 = 0;                  	    // Clear overflow flag
        TR1 = 1;                 	    // Enable timer1
        
        while(IS_MASK_SET(PM3STS, P_OBF))
        {
            if(TF1)
            {
                timeout = 0x01;
                break;
            }
            else
            {
                timeout = 0x00;
            }
        }
        
        if(timeout==0x01)
        {
            break;
        }
        else
        {
            PMC3Output(PECI_StressToolBuf[index]);
        }
    }

    TR1 = 0;                 	    // Disable timer1
    TF1 = 0;                  	    // Clear overflow flag
    ET1 = 1;                  	    // Enable timer1 interrupt
    */
}

// ----------------------------------------------------------------------------
// Read PECI error count command
// ----------------------------------------------------------------------------
void PECI_PSTReadErrorCount(void)
{
    uint8_t index, timeout;
    uint8_t buffer[4];
    Xuint8_t *xptr;

    timeout = 0x00;
    
    xptr = &PECI_ErrorCount;
    buffer[3] = *xptr;
    xptr++;
    buffer[2] = *xptr;
    xptr++;
    buffer[1] = *xptr;
    xptr++;
    buffer[0] = *xptr;


    for(index=0x00;index<4;index++)
    {
        TR1 = 0;                 	    // Disable timer1
        ET1 = 0;                  	    // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_30ms>>8;            // Set timer1 counter 30ms
        TL1 = Timer_30ms;               // Set timer1 counter 30ms
        TF1 = 0;                  	    // Clear overflow flag
        TR1 = 1;                 	    // Enable timer1
        
        while(IS_MASK_SET(PM3STS, P_OBF))
        {
            if(TF1)
            {
                timeout = 0x01;
                break;
            }
            else
            {
                timeout = 0x00;
            }
        }
        
        if(timeout==0x01)
        {
            break;
        }
        else
        {
            PMC3Output(buffer[index]);
        }
    }

    TR1 = 0;                 	    // Disable timer1
    TF1 = 0;                  	    // Clear overflow flag
    ET1 = 1;                  	    // Enable timer1 interrupt
}

// ----------------------------------------------------------------------------
// Read PECI status command
// ----------------------------------------------------------------------------
void PECI_PSTReadStatus(void)
{
    TR1 = 0;                 	    // Disable timer1
    ET1 = 0;                  	    // Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_30ms>>8;            // Set timer1 counter 30ms
    TL1 = Timer_30ms;               // Set timer1 counter 30ms
    TF1 = 0;                  	    // Clear overflow flag
    TR1 = 1;                 	    // Enable timer1
        
    while(IS_MASK_SET(PM3STS, P_OBF))
    {
        if(TF1)
        {
            break;
        }
    }

    if(!TF1)
    {    
        PMC3Output(PSTB_CmdStatus);
    }

    TR1 = 0;                 	    // Disable timer1
    TF1 = 0;                  	    // Clear overflow flag
    ET1 = 1;                  	    // Enable timer1 interrupt
}

// ----------------------------------------------------------------------------
// Clear PECI stress tool variables
// ----------------------------------------------------------------------------
void PECI_ClearPSTVariables(void)
{
    PSTB_Timer = 0x00;
    PSTB_CmdStatus = 0x00; 
    PSTB_RepeatIntervalCount = 0x00;
    PSTB_RepeatCycle = 0x00;
    StressToolReadBufIndex = 0x00;
}

// ----------------------------------------------------------------------------
// Send buffer data to PECI stress tool (5ms time base)
// ----------------------------------------------------------------------------
void PECI_SendBufferData(void)
{
    if(StressToolReadBufIndex!=0x00)
    {
        if(IS_MASK_CLEAR(PM3STS, P_OBF))
        {
            PMC3Output(PECI_StressToolBuf[BufferLength-StressToolReadBufIndex]);
            StressToolReadBufIndex--;
        }
    }
}

#endif