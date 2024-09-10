
#include "RTK_Include.h"
#ifdef SupportMTLCRB
#include "oem/crb/CRB.h"
#endif
uint8_t OOB_PECI_GetTemp(uint8_t*);
/******************************************************************************/
/** 1ms service routine
 * if necessary, don't use this service
*******************************************************************************/
void oem_1ms_service(void)
{
	if(KeyPress && IS_BIT_CLR(SERVICEflag,SERVICE_F_SCANKEY)) {
#if SupportOD
		if(KBM->DBG_b.STEP == 4) {
			BIT_CLR(SERVICEflag,SERVICE_F_SCANKEY);
			ScanIntrvl = 0;
			return;
		}
#endif
		ScanIntrvl++;
		if(ScanIntrvl >= ScanIntrval1msbase) {
			BIT_SET(SERVICEflag,SERVICE_F_SCANKEY);
			ScanIntrvl = 0;
		}
	}

    if (xEC_CMDR > 0)
	//if (IS_MASK_SET(POWER_FLAG5, modern_stby)) //0x205 bit1	
    {
        Hook_Intel_Cmd();
    }
    #if MailBoxRWECRam
    HandleMailBox();
    #endif


	static uint8_t i =0;
	Oem_SysPowerContrl();
	if(i<10)
	{
		EventManager(i++);
	}
	else
	{i=0;}

	// if(IS_BIT_SET(ESPI->EVIDX7, IDX7_HOST_RST_WARN)) {
	// 	VW_Set_Index(0x06, 0x8F);
    //     while(IS_BIT_SET(ESPI->EVIDX7, IDX7_HOST_RST_WARN)) {}
	// 	VW_Set_Index(0x06, 0x87);
    // }
	// ESPI->EVSTS_b.IDX7CHG = 1;

    if (!SLP_S3_L)
	{
		BT_EN = 0;
	    //WLAN_EN = 0; 	
	}
	//981004-220408-A-E	
		
	CLEAR_MASK(EC_Flag4, old_99w); //981004-231025-A not support old battery


}

/******************************************************************************/
/** 5ms service routine
*******************************************************************************/
void oem_5ms_service(void)
{
#ifdef SupportMTLCRB
	if(SystemState == SYSTEM_G3) {
		CRBS5toS0();
	}
#endif

#if SUPPORT_PD_CHIP_ITE //981004-210831-A    
	//service_ucsi_ite();
#endif
    #if ADCFuncSupport  
	ScanADCFixChannel();
    #endif

	#ifdef PECI_Support
    ///PECI_PowerCtrlCenter(); //Stress Tool
    #endif

    #ifdef PMC3_Support
    if(SystemIsS0)
    {
        PECI_SendBufferData();
    }
    #endif

    #if ACPI_QEventPending
    Get_PendingECQEvent();
    #endif
    
	if (xAPP_PD_EnterUpdate > 0x00) //981004-220208-A
    {
		//SET_MASK(EC_Flag5, TI_PD_Flash); //EC RAM 0x389 BIT6
        service_app_update_ti_pd();
    }
}
/******************************************************************************/
/** 10ms A service routine
*******************************************************************************/
void oem_10msA_service(void)
{
    #if ADCFuncSupport 
    ScanADCDyChannel1();
    #endif

    #if BAT1FuncSupport
    Battey1ControlCenter();
    #endif

    #ifdef ECPowerDownModeSupport
    ECPowerDownModeManager();
    #endif
	
	
	
    //981004-200923-R-S No need to skip reading GPU temperature
	#if 0
    if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))) 
    {  
        if (IS_MASK_CLEAR(POWER_FLAG8, no_GPU_smbus)) //EC RAM 208 BIT 4	
        {
            CLEAR_MASK(POWER_FLAG7, no_smbus_start); //EC RAM 207 BIT 6		
            (bRWSMBus(SMbusChB, SMbusRB, GPUThermalAddr2, RLTS, &GPU_TMPR, SMBus_NoPEC));                         
        }
        else
        {   
            SET_MASK(POWER_FLAG7, no_smbus_start); //EC RAM 207 BIT 6
        }  		
    }
	#endif
    //981004-210104-A-S
	#if 0 
    if( IS_MASK_CLEAR(xTIFW_States,F_TIFW_Finish))
    {
    	TI_FirmwareUpdate();		
    }
	#endif
	
    //981004-220726-A-S	
	#if 0
	//if (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))
	//if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3)))	
	if (IS_MASK_CLEAR(POWER_FLAG12, EC_modern_stby)) //981004-230830-A      					
	{
        if (IS_MASK_SET(POWER_FLAG8, DDS_reset)) //0x208 bit4 
		{
			DDS_PANEL_RST = 1; //GPIO H3			
		}
        else
        {
            DDS_PANEL_RST = 0; //GPIO H3			
        }	
    }   
    		
	if (IS_MASK_CLEAR(POWER_FLAG7, GPU_switch)) //EC RAM 0x207 bit 1 
	{
        //EC adjust brightness		
        DDS_PWM_SWITCH = 0; //GPIO D3 //981004-231218-M to support HDR brightness control
		EDP_GPU_SEL = 0; //Intel GPU (SG Mode) //GPIO H4 
        DDS_MUX_CNTL = 0; //Intel GPU (SG Mode) brightness //GPIO D4
		//981004-220106-M-S
        if (DDS_PWM_Value >= 23)
        {			
            DCR7 = DDS_PWM_Value * 1.8; //0x2AC //981004-220707-M from 1.8 (2.3)		
		}
        else
        {
			DCR7 = DDS_PWM_Value + 18;  //981004-220707-M from +18 (36)		
		}			
	    
		#if 0
        if (DCR7 == 0)
	    {          
	      DCR7 = 2; 
	    }
        #endif
		//981004-220106-M-E		
    }
    else
    {
		//NV driver adjust brightness		
        DDS_PWM_SWITCH = 0; //GPIO D3 
		EDP_GPU_SEL = 1;   //GPIO H4 
        DDS_MUX_CNTL = 1; //GPIO D4
		if (DDS_PWM_Value >= 18) //981004-220707-M from 18
        {			
            DCR7 = DDS_PWM_Value * 1.8; //0x2AC //981004-220707-M from 1.8		
		}
        else
        {
			DCR7 = DDS_PWM_Value + 18;  //981004-220707-M from +18			
		}			
    }    
    #endif
	
	if (IS_MASK_SET(POWER_FLAG2, sci_on)) //981004-240424-A-S
	{
		if (IS_MASK_SET(POWER_FLAG13, all_sys_pwrgd_off)) //0x213 bit2
		{
			ALL_SYS_PWRGD = 0;
			CLEAR_MASK(POWER_FLAG13, all_sys_pwrgd_off);
		}
	}	//981004-240424-A-E


}

/******************************************************************************/
/** 10ms B service routine
*******************************************************************************/
void oem_10msB_service(void)
{
    CheckSBPowerButton();
    #if ADCFuncSupport 
    //ScanADCDyChannel2();
	;
    #endif

#if 1 //SUPPORT_APP_UPDFW_MODULE //981004-211015-A-S   
    if (xITEPD_FlashUtilityEnable > 0)
    {
        ///ITE_PD_FlashUtility();
    }
#endif  
}

/******************************************************************************/
/** 50ms A service routine
*******************************************************************************/
void oem_50msA_service(void)
{
}

/******************************************************************************/
/** 50ms B service routine
*******************************************************************************/
void oem_50msB_service(void)
{
}

/******************************************************************************/
/** 100ms A service routine
*******************************************************************************/
void oem_100msA_service(void)
{
	 if ((SystemIsS3)) //981004-200724-A
        //F_Service_OEM_3 = 1;
        BIT_SET(SERVICEflag,SERVICE_F_OEM3);    
	if (SystemIsS0)
	{
		Check_PORT80();
	}

	if (IS_MASK_SET(POWER_FLAG3, power_on_patch))
	{
		Power_on_patch_cnt++;
		if (Power_on_patch_cnt >= 2)
		{
			RSMRST_L = 0;
           /// if (ECHIPVER >= _CHIP_EX) //981004-231214-A
            {    
            ///    SET_MASK(ESGCTRL2, F_ESPIIPG);
            } 
			Power_on_patch_cnt =0;
			CLEAR_MASK(POWER_FLAG3, power_on_patch);//203 bit1
		}
    }

}

/******************************************************************************/
/** 100ms B service routine
*******************************************************************************/
void oem_100msB_service(void)
{
    ///CKCON = 0xC0;         // P144 Clock counter register bit 7-6 (WD Time out counter select 3h : 26bits counter) WDT 6sec
    ///WDTCON = 0x03;        // P150 bit0 : WD timer reset bit1 : WD timer Enable  
    //981004-231002-A-S
	#if 1	
	if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (SLP_S3_L))	
    {		        
        Service_Scan_ADC();
        Get_ADC1_Thermistor();
		//Get_ADC0_Thermistor();
	}
    #endif	
    //981004-211208-R-E	
	#if 0
	if (IS_MASK_SET(EC_Flag5,learn_on2)) //EC RAM 0x389 bit4 
    {
		BAT_OPTION = 0x6CF9;
	}
	#endif
    #if 1 //981004-220808-S from 10ms
    //if (IS_MASK_SET(POWER_FLAG1, power_on)) //981004-230906-A-S PER EE request
	if ((SLP_S3_L) && (IS_MASK_CLEAR(POWER_FLAG12, EC_modern_stby))) //981004-231128-M
	//if (SLP_S4_L)	
    {	 	
	  if (IS_MASK_CLEAR(POWER_FLAG7, GPU_switch)) //EC RAM 0x207 bit 1 
	  {
        //EC adjust brightness	
        DDS_PANEL_RST = 1; //GPIO H3
		if (LID_L) //981004-231206-A
		{	
            EC_BKLOUT = 1; //GPIO J1
        }			
        DDS_PWM_SWITCH = 0; //GPIO D3 //981004-231218-M for NV driver adajust brightness
		EDP_GPU_SEL = 0; //Intel GPU (SG Mode) //GPIO H4 
        DDS_MUX_CNTL = 0; //Intel GPU (SG Mode) brightness //GPIO D4
		//DDS_PWM = 0; //GPIO A7
		//981004-220106-M-S
        //981004-220106-M-S
	  #if 0	//981004-231218-R
	  if (IS_MASK_CLEAR(POWER_FLAG3, DDS_Pwm_off)) //EC RAM 0x203 bit 4 //981004-230526-A
      {       		  
		//if (SLP_S3_L)	
        if (IS_MASK_CLEAR(POWER_FLAG12, EC_modern_stby)) //981004-230831-M  			
		{
         			
          if (DDS_PWM_Value >= 23)
          {
			  if (DDS_PWM_Value != 100) //981004-230830-A
			  {	  
                  DCR7_TEMP = DDS_PWM_Value * 1.8; //0x2AC //981004-220707-M from 1.8 (2.3)				  
              }	
              else
		      {
				  DCR7_TEMP = 200;	//981004-230830-A			  
			  }				  
		  }
          else
          {
              DCR7_TEMP = DDS_PWM_Value + 18;  //981004-220707-M from +18 (36) 
		  }
          if (DCR7_TEMP != DCR7)
          {
             DCR7 = DCR7_TEMP;
          }	
        }
        else
        {
			DCR7 = 0;
		
		}
	   }
       else
	   {
		  DCR7 = 0;
		  
	   }
       #endif	   
      }
      else
      {
		//NV driver adjust brightness
        DDS_PANEL_RST = 1; //GPIO H3
        if (LID_L) //981004-231206-A
		{	
            EC_BKLOUT = 1; //GPIO J1
        }				
        DDS_PWM_SWITCH = 0; //GPIO D3 		
		EDP_GPU_SEL = 1;   //GPIO H4 
        DDS_MUX_CNTL = 1; //GPIO D4
        //DDS_PWM = 0; //GPIO A7 //981004-231031-R
        //DCR7 = 0; //GPIO A7 //981004-231031-R		
      }
    }
    else //981004-231120-A for power leakage
    {
		DDS_PANEL_RST = 0; //GPIO H3
	}		
    #endif
    //981004-231006-A-E
}

/******************************************************************************/
/** 100ms C service routine
*******************************************************************************/
void oem_100msC_service(void)
{
    #if SmartFanSupport
    if(SystemIsS0)
    {
        FanManager();
    }
    #endif
    //981004-210401-A-S	
	if (IS_MASK_SET(POWER_FLAG3, power_on_patch))
	{
		Power_on_patch_cnt++;
		if (Power_on_patch_cnt >= 2)
		{
			RSMRST_L = 0;
            ///if (ECHIPVER >= _CHIP_EX) //981004-231214-A
            {    
               /// SET_MASK(ESGCTRL2, F_ESPIIPG);
            } 
			Power_on_patch_cnt =0;
			CLEAR_MASK(POWER_FLAG3, power_on_patch);//203 bit1
		}
    }
    //981004-210401-A-E       
}

/******************************************************************************/
/** 500ms A service routine
*******************************************************************************/
void oem_500msA_service(void)
{
    #if ECSleepModeSupport
   /// if(CheckEnterDeepSleep())
   /// {
	///    EnterDeepSleep();
   /// }
    #endif			
	
	//981004-171102-A-S 
	#if 1
	if (IS_MASK_CLEAR(POWER_FLAG9, rtc_wake_support)) //EC RAM 209 bit 4
    {	 
        if (IS_MASK_CLEAR(POWER_FLAG6, BIOS_flash_ok)) 
		{
            Check_Adapter();
        } 			
    }
	#endif
    //981004-171102-A-E	
}

/******************************************************************************/
/** 500ms B service routine
*******************************************************************************/
void oem_500msB_service(void)
{
       BYTE cnt = 0; //981004-141014-A	 
    //981004-141014-A-S

    //981004-210617-A-S Change new camera and no light sensor
	if (LID_L) //981004-230118-A
	{	
       #if 1
       if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))) 
       {	              
		  /// F_Service_OEM_1 = 1;
           BIT_SET(Service_OEM, F_Service_OEM_1);
       }
	   #endif
	}   
	//981004-210617-A-E

	//if (AC_IN_L) //Battery mode
	//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
	//if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG11, acout_pdin)))
	if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2)))	
	{
	  if (IS_MASK_SET(POWER_FLAG2, sci_on) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))) 
      {	
        if ((IS_MASK_CLEAR(ProcsH, ProcsH_scion20sec)) && (IS_MASK_CLEAR(ProcsH, ProcsH_acout))) 
        {
		  for (cnt=0; cnt<5; cnt++)
              ///if (bRWSMBus(SMbusCh1, SMbusRW, SmBat_Addr, C_current, &BATRATE_TEMP, SMBus_NoPEC))
              if (SMBUS_RW_W(SMbusCh1, SMbusRW, SmBat_Addr, C_current, &BATRATE_TEMP))
                  break;
					  
          temp_buff2 = ~((BATRATE_TEMP<<8)|(BATRATE_TEMP>>8)-1); //negative current
          BAT_PRSNTRATE = (temp_buff2<<8) | (temp_buff2>>8);

         (PRSNTRATE_TEMP = (BAT_PRSNTRATE<<8) | (BAT_PRSNTRATE>>8)); 	   

          //992022-140923-A-S         
          if (PRSNTRATE_TEMP > 8000) //8 AMP
          {
              if (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh))
              {
                  SET_MASK(AmpHigh_flag, AmpHigh);
                  if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2)) //981004-221005-M
			      {
                      H_PROCHOT_L = 0; //dCPU 
                      dGPU_HOLD_EC_RST_L = 1; //dGPU
				  }
                  else
                  {
					  H_PROCHOT_L = 0; //dCPU 
                      dGPU_HOLD_EC_RST_L = 1; //dGPU
				  }				  
                  SET_MASK(POWER_FLAG8, D7_flag_for_bios);  //for BIOS to know and force keep in CPU P16 because smartcooling will let BIOS to become P8
				  
				  if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                  {
                     ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA 				  
                     NVDeventStatus = 0x0A;
				  }	 
				  //981004-200130-M-S
				  //if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	              //{
                     WTDP = 15;
                     WTDP2 = 45;		
                     WTDP4 = 90; 
				  //}
                  //else //i9 CPU
                  //{
                     //WTDP4 = 1;
                  //}
                  //981004-200130-M-E 
              }
          }         
		}
      }
    }

    if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG2, sci_on)))	
    {
       //if (!PD_ADAPTER_IN)
	    if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) //EC RAM 0x211 bit4  	   
	    {
		  if (IS_MASK_SET(POWER_FLAG1, power_on))
		  {	 
		     H_PROCHOT_L = 1; //dCPU //981004-221005-M
             dGPU_HOLD_EC_RST_L = 0; //dGPU //981004-221014-M
             PD_Adapter_setting();
		  }
          else
          {
             WTDP = 1; 
	         WTDP2 = 1; 
             WTDP4 = 1;
          }	 
       }   
    }
	//981004-220707-A-S
	if (IS_MASK_SET(POWER_FLAG3, ship_mode))
	{
	    SHIP_MODE_cnt++;
		if (SHIP_MODE_cnt >= 3)
		{
		    SHIP_MODE_cnt = 0;
			//CLEAR_MASK(POWER_FLAG3, ship_mode); //981004-220901-R
		    //SysPowState = SYSTEM_S0_S4; //981004-220901-R
			
			Ship_mode = 0x1000;
            //bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
            SMBUS_RW_W(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode);
            Delay1MS(250); 
            //bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
            SMBUS_RW_W(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode);
			Delay1MS(250); //981004-220901-A
			#if 0
			if (AC_IN_L)
			{	
               for(ITempB01=0x00;ITempB01<20;ITempB01++)	//240us loop
	           {
                  Delay1MS(250);
               }
			}
            #endif			
			CLEAR_MASK(POWER_FLAG3, ship_mode); //981004-220901-A
		}
	}
}

/******************************************************************************/
/** 1second A service routine
*******************************************************************************/
void oem_1SA_service(void)
{
    uint8_t temp = 0;
    uint16_t temp2 = 0;
    if(SystemIsS0)
    {
      PECI_Get_Temp(0x30,&temp2);
      OOB_PECI_GetTemp(&temp);
    }
    
    #if 0       
    if (IS_MASK_CLEAR(POWER_FLAG7, GPU_switch)) //EC RAM 0x207 bit 1 
	{
	    EDP_GPU_SEL = 0; //Intel GPU (SG Mode) //GPIO H4	
        DDS_MUX_CNTL = 0; 
	}
    else
    {
	    EDP_GPU_SEL = 1; //NV GPU (PEG Mode) //GPIO H4			 
        DDS_MUX_CNTL = 1; 
	}
	#endif
	
	if (IS_MASK_SET(POWER_FLAG3, CLR_CMOS_SHUTDN)) //0x203 Bit5 //981004-231123-A
	{		
		CLEAR_MASK(POWER_FLAG3, CLR_CMOS_SHUTDN);
		RSMRST_L = 0;
		SET_MASK(EC_Flag7, CMOS_BOOT); //EC RAM 0x339 BIT0
					
		//SysPowState = SYSTEM_S4_S0;		
	}
    else
    {
	;
	}

    if (IS_MASK_SET(EC_Flag7,CMOS_BOOT))
    {
		CMOS_CNT++;		
		if (CMOS_CNT >= 4)
		{
			CMOS_CNT = 0;
			CLEAR_MASK(EC_Flag7, CMOS_BOOT);			
			SysPowState = SYSTEM_S4_S0;
        }			
	}		
	
	#if 0
	if (IS_MASK_SET(EC_Flag5,learn_on1)) //EC RAM 0x389 bit3 
    {
		Learn_on_CNT++;
		if (Learn_on_CNT >= 5)
		{	
		    BAT_OPTION = 0x6CF9;
			Learn_on_CNT = 0;
			CLEAR_MASK(EC_Flag5, learn_on1);
		    SET_MASK(EC_Flag5, learn_on2); //EC RAM 0x389 BIT4
		}       		
	}			
	#endif
	//981004-231002-A-S 
	#if 0 //981004-231019-R-S
    if ((!AC_IN_L) && (IS_MASK_SET(POWER_FLAG2, sci_on)) && (SLP_S3_L))
    {
	   if ((AVG_ADC1 >=60) && (IS_MASK_CLEAR(POWER_FLAG3, adapter_overtemp)) ) //0x203 bit2
	   { 	
         SET_MASK(POWER_FLAG3, adapter_overtemp);
		 //ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3 
         ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2	//981004-210325-M	 
		 //981004-210325-M-S			
		 if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	     {
            WTDP = 35;
            WTDP2 = 45;	
	        WTDP4 = 90; //0xD3 
	     }
         else //i9 CPU
         {
           WTDP = 35;
           WTDP2 = 45;	
	       WTDP4 = 90; //0xD3
         }
         //981004-200130-M-E                    			
       }
       if ((AVG_ADC1 <=54) && (IS_MASK_SET(POWER_FLAG3, adapter_overtemp)) ) //0x203 bit2
	   { 	
         CLEAR_MASK(POWER_FLAG3, adapter_overtemp);
		 ECQEvent(SCI_BATT_LOW_TEMPER, SCIMode_ACPI_SMBus); //0xD1                                
		 if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	     {						           
             WTDP = 157; 
			 WTDP2 = 157;
			 WTDP4 = 246;
         }			 						          			 
         else //i9 CPU
         {		 
             WTDP = 157; 
			 WTDP2 = 157;
			 WTDP4 = 246;
         }                                 			
       }		   
	}	
	#endif //981004-231019-R-E
	
	//981004-200724-A-S 
    #if 0	
    if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))) 
    {          
        if (IS_MASK_SET(POWER_FLAG8, AI_ON)) //EC RAM 208 BIT 7
        {          			
          if (IS_MASK_CLEAR(POWER_FLAG13, GPU_temp_80)) //EC RAM 20D BIT 4	
          {           
            if (GPU_TMPR < 80) //LV4
            {
                GPU_OC(4); //GPIO E5
				GPU_TEMP_CNT1 = 0;				
            }
			else //((GPU_TMPR >= 80) && (GPU_TMPR <= 85)) //LV3
            {
				GPU_TEMP_CNT1++;
				if (GPU_TEMP_CNT1 >=5)
				{	
                    GPU_OC(3); //GPIO E0
					GPU_TEMP_CNT1 = 0;
					SET_MASK(POWER_FLAG13, GPU_temp_80); //EC RAM 20D bit 4				   
				}	
            } 
		  }
          else
          {
            if (GPU_TMPR < 80) //LV4
            {
				GPU_TEMP_CNT1++;
				if (GPU_TEMP_CNT1 >=5)
				{	 
                    GPU_OC(4); //GPIO E5
				    GPU_TEMP_CNT1 = 0;
					CLEAR_MASK(POWER_FLAG13, GPU_temp_80);				    
				}	
            }
			else 
			{
                GPU_TEMP_CNT1 = 0;				
            }
            if (IS_MASK_CLEAR(POWER_FLAG13, GPU_temp_85)) //EC RAM 20D BIT 5	
            {               		            
                if (GPU_TMPR >= 85) //LV0
                {
                    GPU_TEMP_CNT2++;
				    if (GPU_TEMP_CNT2 >=5)
				    {	
                        GPU_OC(0); //GPIO D5
					    GPU_TEMP_CNT2 = 0;
						SET_MASK(POWER_FLAG13, GPU_temp_85); //EC RAM 20D bit 5				        
				    }
                }
                else
                {
                    GPU_TEMP_CNT2 = 0;				    
                }					
            }
            else
            {
                if (GPU_TMPR < 85) //LV3
                {
                    GPU_TEMP_CNT2++;
				    if (GPU_TEMP_CNT2 >=5)
				    {	
                        GPU_OC(3); //GPIO E0
					    GPU_TEMP_CNT2 = 0;
						CLEAR_MASK(POWER_FLAG13, GPU_temp_85); //EC RAM 20D bit 5				        
				    }
                }
                else
                {
                    GPU_TEMP_CNT2 = 0;				   
                }			
            }				
          }
		}
        else
        {           	   
		   GPU_OC(0);//LV0
		   GPU_TEMP_CNT1 = 0;
		   CLEAR_MASK(POWER_FLAG13, GPU_temp_80); //EC RAM 20D bit 4
		   GPU_TEMP_CNT2 = 0;
		   CLEAR_MASK(POWER_FLAG13, GPU_temp_85); //EC RAM 20D bit 5
        }			
    }        
    #endif
	//981004-200724-A-E
	
	
    #if SmartFanSupport
    if(SystemIsS0)
    {
        CheckFanRPM1();
    }
    #endif
    if(IS_MASK_SET(POWER_FLAG13, fixBattery))//981004-150525-A Fix Battery no charge when shipmode wakeup.60.8w "Model : GAG-K40" 
    {	
		Fix_Battery_Abnormal();//981004-150525-A Fix Battery no charge when shipmode wakeup.60.8w "Model : GAG-K40"
	}
    PollingBatteryData();
	if (IS_MASK_SET(POWER_FLAG1, power_on) && IS_MASK_SET(POWER_FLAG2, SLP_S3_ON)) //981004-121225-M
    {	    
       bGetThermalData();            
       vMoniterTemprature();
	   vFanControl2(); //For X5X8 NV 970 + X5Y8 NV 980  
       //981004-170419-M-E 	   
    } 
    else if (!SLP_S3_L) //981004-221003-A	
	{
       DCR0 = 0x00;
       DCR3 = 0x00;	   
	   //FanRPM3 = 0x00; //981004-220928-R
	   //FanRPM4 = 0x00; //981004-220928-R
	   //bRWSMBus(SMbusCh1, SMbusWB, NCT7802YAddr, FANCTRL1, &FanRPM3 ,  SMBus_NoPEC); //981004-220928-R		  
       //bRWSMBus(SMbusCh1, SMbusWB, NCT7802YAddr, FANCTRL2, &FanRPM4 ,  SMBus_NoPEC); //981004-220928-R
    }
	    		
	//981004-180712-R-S
	#if 1
	if(IS_MASK_SET(POWER_FLAG13, HDA_SDO_BIOS))  
    {
        ME_CNT++;
        if(ME_CNT==5)
		{	
            SysPowState = SYSTEM_S4_S0;
		}	
                        
        if(ME_CNT >6)        
            ME_CNT = 6;
    }
	#endif
	//981004-180712-R-E
	
	
	
	//981004-211203-R-S
	#if 0
	if (IS_MASK_SET(POWER_FLAG9, lcd_off))
	{
	    Lid_close_cnt++;		
		if (Lid_close_cnt >= 2)
        {
            Lid_close_cnt =0;
			EC_BKLOUT = 0;           			
        }		   		
	}
	#endif
	//981004-211203-R-E
	
	//981004-210312-R-S
	#if 0
	if (IS_MASK_SET(POWER_FLAG3, power_on_patch))
	{
		Power_on_patch_cnt++;
		if (Power_on_patch_cnt >= 5)
		{
            Power_on_patch_cnt =0;
			CLEAR_MASK(POWER_FLAG3, power_on_patch);//203 bit1
			//CLEAR_MASK(POWER_FLAG2, sci_on);
        }			
    }
    #endif	
	//981004-210312-R-E
	
	//981004-231002-R-S
	#if 0
	if (SLP_S3_L) //981004-220822-A
	{
	  if (IS_MASK_SET(POWER_FLAG2, sci_on)) 
      {
        (bRWSMBus(SMbusCh4, SMbusRW, Thermal1_Addr, Thermal1_Read, &Thermal_Value , SMBus_NoPEC)); //0x90 => NVU17 
        (bRWSMBus(SMbusCh4, SMbusRW, Thermal2_Addr, Thermal1_Read, &Thermal2_Value , SMBus_NoPEC)); //0x92 => CPU1 
	    (bRWSMBus(SMbusCh4, SMbusRW, Thermal3_Addr, Thermal1_Read, &Thermal3_Value , SMBus_NoPEC)); //0x94 => GPU1 
	  }
	  Thermal_Value = (Thermal_Value >> 8);
      if ((Thermal_Value) & 0x80)
      {
		  Thermal_Value = 0x0000;
	  }
	  Thermal2_Value = (Thermal2_Value >> 8); 
      if ((Thermal2_Value) & 0x80)
      {
		  Thermal2_Value = 0x0000;
	  }
	  Thermal3_Value = (Thermal3_Value >> 8);
      if ((Thermal3_Value) & 0x80)
      {
		  Thermal3_Value = 0x0000;
	  }
	} 
	#endif   
	//981004-231002-R-E



	//KSI1_STATUS = KSIGDATR; //0X1D08 //981004-220629-A
	//KSI2_STATUS = KSIGDMRRR; //0X1D09 //981004-220629-A
    #if GetCPUTempSupport
    //ReadCPUTemp(); //981004-190508-R shift to OEM_FAN.C
    #endif
	//if(SystemIsS4)
	//{
	  //PWR_LED2 = ~PWR_LED2; //981004-201223-M
	  //PWR_LED_L =~PWR_LED_L;  
	//} 

	//981004-211213-M-S  
	//if (IS_MASK_SET(POWER_FLAG2, sci_on) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3)))
	
    //{		
	    #if 0	//981004-220510-R-S	
		if (IS_MASK_SET(POWER_FLAG5, BIOS_reboot)) //EC RAM 0x205 bit2
		{		
			//TI_PD_Warm_reset();
			//TBT_Reconnet();
			CLEAR_MASK(POWER_FLAG5, BIOS_reboot);
		} 
        if (IS_MASK_SET(POWER_FLAG5, BIOS_reboot2)) //EC RAM 0x205 bit3
		{		
			//ResetSMBus(SMbusCh4);
			//TBT_Reconnet();
			Display_Mode();
			CLEAR_MASK(POWER_FLAG5, BIOS_reboot2);
		}       		
		#endif //981004-220510-R-E      		
	//}
	//981004-211213-M-E

    #if SmartFanSupport
    if(SystemIsS0)
    {
        CheckFanRPM2();
    }
    #endif
	//981004-200410-A-S
	if (IS_MASK_CLEAR(POWER_FLAG2, sci_on)) //202 BIT4
	{        
		if (IS_MASK_SET(POWER_FLAG5, Linux_fanon)) //205 BIT6
		{           
			SET_MASK(POWER_FLAG6, adjustfan);
			FanRPM1=0x5D; 
	        FanRPM2=0x5D;
			//CLEAR_MASK(POWER_FLAG5, Linux_fanon);
        }	
    }
	//981004-200410-A-E
    if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //981004-230707-A
	{
		if (IS_MASK_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
		{
            if (NVSETPL1 == 0) //981004-221228-A
            {
				NVSETPL1 = 40;				
			}           			
			WTDP = NVSETPL1; //EC RAM 0x29E
			WTDP2 = NVSETPL1 * 1.25;
		}		
	}	
	PECI_WritePowerLimit1(); //981004-210115-A	    
	PECI_WritePowerLimit2(WTDP2); //981004-210115-A
	//981004-151001-A-S
	if (IS_MASK_SET(POWER_FLAG2, sci_on) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3)))
        {		
		    //PECI_WritePowerLimit3(WTDP3); //98104-150825-A
			PECI_WritePowerLimit4(WTDP4); 
		}
	
    //981004-210115-A-S	
	if (Check_Power_Unit == 0)
	{
        Check_Power_Unit = PECI_ReadPowerUnit();
    }
    //981004-210115-A-E
	
    ProcessCharge();
    //981004-131030-A-S patch for Max request
    if (IS_MASK_SET(ProcsH, ProcsH_scion20sec))
    {
        ProcsH_scion_cnt++;	        	
		
        if (ProcsH_scion_cnt == 0x01) //992022-140922-M from 0x03 //992022-140519-M from 0x14
        {            
            //if (!AC_IN_L)
			if ((!AC_IN_L) || (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))	
            {
				if (!AC_IN_L) //981004-221005-M
				{	
                   H_PROCHOT_L = 0; //Normal               				
                   dGPU_HOLD_EC_RST_L = 1; //Normal
				   WTDP4 = 246; //981004-221005-A
				}
                else if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) //981004-221005-M
				{	
                   H_PROCHOT_L = 0; //Normal                				
                   dGPU_HOLD_EC_RST_L = 1; //Normal
				   WTDP4 = 45; //981004-221005-A
				} 
				                				
				//SET_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
				SET_MASK(POWER_FLAG1, adapter_in); //201 BIT0 //981004-210224-A
                ECQEvent(SCI_ADAPTERIN, SCIMode_ACPI_SMBus); //992022-140402-A to let BIOS know AC in or BAT only to do P0 or P1
				Delay1MS(50); //981004-210224-A
				AC_PRESENT = 1; //981004-210224-A
            }
            else //battery mode
            {
                //CLEAR_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
                CLEAR_MASK(POWER_FLAG1, adapter_in); //981004-210224-A				
                ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus); //992022-140402-A to let BIOS know AC in or BAT only to do P0 or P1
				Delay1MS(50); //981004-210224-A
				AC_PRESENT = 0; //981004-210224-A
            }
            //DCR5 = 0x00; //992022-140519-R
        } 

		//981004-151117-A-S 
        if (ProcsH_scion_cnt == 0x02) 
        {
		    if (LID_L)
			{
			    SET_MASK(POWER_FLAG2, lid_open);
			    ECQEvent(SCI_LID_CHANGE, SCIMode_ACPI_SMBus); //0x70 
			}
			//981004-220726-A-S
			if (!HPD_EC_L)
			{	                	
			    ECQEvent(SCI_HDMI, SCIMode_ACPI_SMBus); //0x79
			}
		    //981004-220726-A-E
		}
        //981004-151117-A-E    		
		//981004-160705-S-S from command B0	 
        if (ProcsH_scion_cnt == 0x03) //981004-160906-M from 0x08 to prevent SM can not set the status 
        {
            //981004-191001-M-S			
            #if 0
			if(IS_MASK_CLEAR(POWER_FLAG12, windows8)) 
               BT_EN = IS_MASK_SET(POWER_FLAG1, bt_on) ? 1 :0; 
            else //Always on under Windows 8/10
	        {
	            SET_MASK(POWER_FLAG1, bt_on); 
                BT_EN = 1; 
            }
			#endif
			SET_MASK(POWER_FLAG1, bt_on); 
            BT_EN = 1;             
            //981004-191001-M-E			
        }
        //981004-160705-S-E

       if (ProcsH_scion_cnt == 0x04) //981004-210202-A  
       {		
           if (!PD_ADAPTER_IN)
		   {
               SET_MASK(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
           }
		   if (!PD_ADAPTER_IN2)
		   {
               SET_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x208 bit0
           }
           if (IS_MASK_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
           {
			    CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	            CLEAR_MASK(EC_Flag4, nv_db20_lv4);
                NV_DB20_SUPPORT();
	       }				   
	   }
        //992022-140922-A-S
        if (ProcsH_scion_cnt == 0x12) //18sec
        {
            if (AC_IN_L) //battery mode
            {
			  //if (PD_ADAPTER_IN) //No PD adapter
			  if ((IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) 
			  { 
                if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                {
                   if (NVDeventStatus3 == 0) //981004-221130-A
                   {					
                       NVDeventStatus = 0x0A;
				   }	   
                   ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA				
				//981004-200130-M-S
				//if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	            //{
                   WTDP = 15;
                   WTDP2 = 45;		
                   WTDP4 = 90; 
				//}
				}
				else
				{
					CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                    CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                    CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                    CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	                CLEAR_MASK(EC_Flag4, nv_db20_lv4);
					NV_DB20_SUPPORT(); //981004-221025-A
				}	
			  	
             }
			 else
			 {
			   ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
               PD_Adapter_setting();	 
             }		 
		   }	
        }
        
        if (ProcsH_scion_cnt >= 0x14) //20sec
        {
            CLEAR_MASK(ProcsH, ProcsH_scion20sec);
            ProcsH_scion_cnt = 0;
			
			//981004-221005-M-S
			if (!AC_IN_L) //981004-221005-M	
	        {	   
	            H_PROCHOT_L = 0; //Normal                
                dGPU_HOLD_EC_RST_L = 1; //Normal
                WTDP4 = 246;				
	        }
	        else
	        {
                if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2)) //981004-221005-M
                {		                      
					if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) )
			        {
                       H_PROCHOT_L = 1;	//Normal //981004-221005-M                        				   
                       dGPU_HOLD_EC_RST_L = 0; //Normal //981004-221005-M                        					   
                    }
					else
					{
					   H_PROCHOT_L = 0; //dCPU
                       dGPU_HOLD_EC_RST_L = 1; //dGPU					   
					}
					if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                    {
                       WTDP4 = 90;					
                    }
				}	
                else
		        {
			        if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) //EC RAM 0x211 bit4
	                {
		                H_PROCHOT_L = 0;	//Normal //981004-221005-M                        				   
                        dGPU_HOLD_EC_RST_L = 1; //Normal //981004-221005-M 
                        WTDP4 = 45;					   
	                }
			        else
			        {
				        if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) )
			            {
                           H_PROCHOT_L = 1;	//Normal //981004-221005-M                        				   
                           dGPU_HOLD_EC_RST_L = 0; //Normal //981004-221005-M                        					   
                        }
					    else
					    {
					       H_PROCHOT_L = 0; //dCPU
                           dGPU_HOLD_EC_RST_L = 1; //dGPU					   
					    }
						if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                        {
                            WTDP4 = 90;
						}
			        }	
		        }	
      		  
	        }	
			#if 0
            if (AC_IN_L) //battery mode
            {
			  //if (PD_ADAPTER_IN) //No PD adapter
			  if (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) //981004-210309-M 
			  {  
			    if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) )
			    {
                   H_PROCHOT_L = 1;	//Normal //981004-221005-M 
                   WTDP4 = 90;				   
                   dGPU_HOLD_EC_RST_L = 0; //Normal //981004-221005-M 				    
                }
			 }
             else
             {
                H_PROCHOT_L = 0; //Normal //981004-221005-M
				WTDP4 = 246; 
                dGPU_HOLD_EC_RST_L = 1; //Normal //981004-221005-M 
             }		 
		   }
		   //981004-210325-A-S
           else //AC mode
           {
               H_PROCHOT_L = 0; //Normal
			   WTDP4 = 246; 
               dGPU_HOLD_EC_RST_L = 1; //Normal
           }
		   #endif
           //981004-221005-M-E		   
        }
        //992022-140922-A-E
    }
    //992022-140218-A for Processor Hot patch by Max request

    //992022-140904-A-S for AC in to delay 3 sec. and 5 sec. action
	//981004-141014-M-S
    if (IS_MASK_SET(POWER_FLAG10, scion_ac_in)) 
    {
	  if ((IS_MASK_CLEAR(POWER_FLAG11, check_pd_ac_chg)) && (IS_MASK_CLEAR(POWER_FLAG8, check_pd_ac_chg2)) ) //EC RAM 0x211 bit3 / //EC RAM 0x208 bit0 
      {	
        SCI_on_AC_in_cnt++;
		if (SCI_on_AC_in_cnt == 2)
        {  
		    if (!AC_IN_L) //981004-221005-M
			{	
	            H_PROCHOT_L = 0; //CPU recover
			}
            else //PD adapter //981004-221005-M
            {	
	            H_PROCHOT_L = 0; //CPU recover
			}				
	    }
		if (SCI_on_AC_in_cnt == 5)
        {            
            ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3 
            //981004-200130-M-S			
			if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	        {
               WTDP = 35;
               WTDP2 = 45;	
	           WTDP4 = 90; //0xD3 
			}
            else //i9 CPU
            {
              WTDP = 35;
              WTDP2 = 45;	
	          WTDP4 = 90; //0xD3
            }
            //981004-200130-M-E 			
        }
		if (SCI_on_AC_in_cnt == 7)
        {            
			if (!AC_IN_L) //981004-221005-M
			{	
	            dGPU_HOLD_EC_RST_L = 1; //Normal //GPU recover
			}
            else //PD adapter //981004-221005-M
            {	
	           dGPU_HOLD_EC_RST_L = 1; //Normal //GPU recover
			}				 
			// WTDP4 = 246; //981004-221011-R
        }
		if (SCI_on_AC_in_cnt == 8)
        {
		  if (IS_MASK_CLEAR(POWER_FLAG3, adapter_overtemp))
          {	
            ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
		   //981004-200306-M-S
		   if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	       {
               WTDP = 35;
               WTDP2 = 45;	
	           WTDP4 = 90; //0xD2 
		   }
           else //i9 CPU
           {
              WTDP = 35;
              WTDP2 = 45;	
	          WTDP4 = 90; //0xD2 
           }
           //981004-200306-M-E 
        }
       }
		 //981004-140930
		if (SCI_on_AC_in_cnt >= 11)
        {
            CLEAR_MASK(POWER_FLAG10, scion_ac_in); //981004-140930
            SCI_on_AC_in_cnt = 0; //981004-140930
		  if (IS_MASK_CLEAR(POWER_FLAG3, adapter_overtemp))
          {	
			ECQEvent(SCI_BATT_LOW_TEMPER, SCIMode_ACPI_SMBus); //0xD1
			//981004-190318-M-S
            if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w))
	        {
		        WTDP = 110; //981004-231012-M from 157
			    WTDP2 = 157;
			    WTDP4 = 246; //i7 CPU
	        }
	        else
	        {
                WTDP = 110; //981004-231012-M from 157
			    WTDP2 = 157;
			    WTDP4 = 246; //i9 CPU
            }			
            //981004-190318-M-E
		  }	
        }
	  }
      else
      {
         CLEAR_MASK(POWER_FLAG10, scion_ac_in); 
         SCI_on_AC_in_cnt = 0;
		 H_PROCHOT_L = 1; //CPU recover //981004-221005-M 
		 if (SCI_NUM != 0xDB)
		 {	 
		    ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		 }	
		 PD_Adapter_setting();
      }  
    }
	//981004-141014-M-E
    //992022-140904-A-E for AC in to delay 3 sec. and 5 sec. action
	if (IS_MASK_CLEAR(EC_Flag4, old_99w)) //981004-220510-A
	{
	  if (IS_MASK_SET(EC_Flag5, fix_ac_voltage)) //389 BIT6 //981004-220524-A
      {
		  AC_vol_cnt++;
		  BAT_CHGCURR = 0x0001; //0.256A
          //BAT_CHGVOL = 0x1030; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)
		  //BAT_CHGVOL = 0x6032; // 8.192+4.096+0.512+0.064+0.032 = 12.896V (Target => 12.9V)
		  BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)
		  if (AC_vol_cnt >= 11) //981004-240620-M from 10
	  	  {
			  AC_vol_cnt = 0;
			  CLEAR_MASK(EC_Flag5, fix_ac_voltage); //389 BIT6 
		  }	
	  }
   }	  
	//981004-210118-A-S
   #if 1
   if (AC_IN_L)
   {        
	   if (IS_MASK_SET(POWER_FLAG11, check_pd_ac_chg)) //EC RAM 0x211 bit3  
       {
		   pd_ac_in_cnt++;		  		   	   
		   #if 1
		   if (pd_ac_in_cnt == 4)
           {			      
			   pd_ti_get_active_PDO(); //To get PD adapter Watt            				   
		   }
		   #endif
		   
		   if (pd_ac_in_cnt == 5)
           {
			  //981004-211021-A-S 
			  #if 0
			  if (xTIPD1_pd_watt > 0) 			  	  
			  {                
				 //SET_MASK(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7
              }
              else
              {			
                //CLEAR_MASK(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7				
			  }
			  #endif
			  //981004-230707-A-S
			  #if 1
			  if (xTIPD1_pd_watt == 60)
			  {
				  SET_MASK(EC_Flag6, PD_60W); //EC RAM 0x37E bit0                  			  
			  }
              else if ((xTIPD1_pd_watt > 60) && (xTIPD1_pd_watt < 80))
              {
				  SET_MASK(EC_Flag6, PD_65W); //EC RAM 0x37E bit1				  
			  }
              else if ((xTIPD1_pd_watt >= 80)	&& (xTIPD1_pd_watt < 100))
              {
				  SET_MASK(EC_Flag6, PD_80W); //EC RAM 0x37E bit2				  
			  }	
              else if (xTIPD1_pd_watt >= 100)
              {
				  SET_MASK(EC_Flag6, PD_100W); //EC RAM 0x37E bit3				  
			  }
			  #endif
              //981004-230707-A-E
			  
              //981004-211021-A-E			  
			  if (xTIPD1_pd_watt >= 60) //981004-211021-M from 85			  	  
			  {                                   
				  SET_MASK(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4
				  //SET_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
				  SET_MASK(POWER_FLAG1, adapter_in); //201 BIT0 //981004-210224-A
				  //BAT_OPTION = 0x4DF9;
				  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
                  if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	              {
				     BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
				  }
				  else
				  {
				     BAT_CHGCURR = 0x0001; //0.256A
				  }	 
				 // bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
                  SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR);
				  BAT_INCURR = 0x0004; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008
				  //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
                  //BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt //981004-221012-R	
	              //BAT_INCURR = 0x8004; //1.024+0.128 = 1.152A (1.152*4 = 4.608A) //981004-230707-R
                  //BAT_INCURR = 0x0009; //2.048++0.256 = 2.304A (2.304*2 = 4.608A) //84 Watt //981004-210824-M
                  //BAT_INCURR = 0x0005; //1.024+0.256 = 1.28A (1.28*2 = 2.56A) //84Watt /981004-220927-R				  
				  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);
                  SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR);
                  if (SCI_NUM != 0xDB)
		          {	 
		              ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		          }	
		          PD_Adapter_setting();	  
				  if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	              {       
		               //ECQEvent(SCI_PD_ACIN, SCIMode_ACPI_SMBus); //0x90					   
                       ECQEvent(SCI_ADAPTERIN, SCIMode_ACPI_SMBus); //0x60					   
	              }
                  Enable_pd_adapter();
                  //else
                  //{
					 //Enable_pd_adapter2();
				 // }					  
			      H_PROCHOT_L = 1; //dCPU //981004-221005-M
                  dGPU_HOLD_EC_RST_L = 0; //dGPU //981004-221005-M
				  Delay1MS(50); //981004-210224-A
				  AC_PRESENT = 1;
				  if ((SLP_S3_L) && (LID_L)) //981004-230428-A
				  {
                       if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
			           {					  
				          PWR_LED2_L = 0; 
					   }	  
				  }
                  //981004-221228-A-S
				  CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                  CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                  CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                  CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	              CLEAR_MASK(EC_Flag4, nv_db20_lv4);
				  CLEAR_MASK(EC_Flag2, pdchgcur_step1); //981004-230630-A-S
	              CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	              CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	              CLEAR_MASK(EC_Flag2, pdchgcur_step4); //981004-230621-A-E
				  CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230828-A
	              CHGCUR_STEP_cnt2 = 0;    
              }
              else
              {
                  CLEAR_MASK(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4
				  //CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2);
				  //CLEAR_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
				  CLEAR_MASK(POWER_FLAG1, adapter_in); //981004-210224-A
				  //CLEAR_MASK(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6				  
                  if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	              {        
		              //ECQEvent(SCI_PD_ACOUT, SCIMode_ACPI_SMBus); //0x91					  
                      ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus); //0X61					  
	              }
                  BAT_OPTION = 0x4DF9;
                  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
                  SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR);   				  
				  Disable_pd_adapter();
                  //else
                  //{
					 //Disable_pd_adapter2();
				  //}					  
                  Delay1MS(50); //981004-210224-A				  
                  AC_PRESENT = 0;
                  if (IS_MASK_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                  {
					  CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                      CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	                  CLEAR_MASK(EC_Flag4, nv_db20_lv4);
                      NV_DB20_SUPPORT();
				  }					  
              }
              ConfigACLIMIT(); //981004-230707-A			  
           }
           if (pd_ac_in_cnt == 6)
           {
              if (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) //EC RAM 0x211 bit4  
              {
				 if (IS_MASK_SET(POWER_FLAG1, power_on))
				 {	 
				    ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
                    PD_Adapter_setting();
                 }
                 else
                 {
                    WTDP = 1; 
	                WTDP2 = 1; 
                    WTDP4 = 1;
                 }			 
			  }
              else //Battery mode
              {
				   if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                   {		   
                        ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA //981004-220929-A
						if (NVDeventStatus3 == 0) //981004-221130-A
                        {
                            NVDeventStatus = 0x0A; //981004-220929-A 
                        }							
                   }
                   else
                   {
		              CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                      CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	                  CLEAR_MASK(EC_Flag4, nv_db20_lv4);
                      NV_DB20_SUPPORT();						
	               }		                  			   
              }
           }	   
           if (pd_ac_in_cnt == 7)
           {			   
               if (IS_MASK_CLEAR(ProcsH, ProcsH_scion20sec)) 
               { 
                  if (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) //EC RAM 0x211 bit4  
                  {		   
                     H_PROCHOT_L = 0; //Normal //981004-221005-M            			                      
                     //dGPU_HOLD_EC_RST_L = 0; //Normal
					 if (IS_MASK_SET(POWER_FLAG1, power_on))
				     {	
                        WTDP4 = 45; //981004-210901-M from 215
                     }						
				  }
                  else //PD Battery mode
                  {
				    if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) )			       
                    { 
                        H_PROCHOT_L = 1; //Normal //981004-221005-M             			                      
                        dGPU_HOLD_EC_RST_L = 0; //Normal //981004-221005-M
						if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-230828-A-S
                        {
					       WTDP4 = 90; //981004-210407-A 
					    } 									
                   }			  
			     }
			   }			   
           }
           if (pd_ac_in_cnt >= 9) //981004-221005-A
           {
			   if (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) //EC RAM 0x211 bit4  
               {		                                  			                      
                     dGPU_HOLD_EC_RST_L = 1; //Normal 					 								   
			   }			   
               CLEAR_MASK(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
			   pd_ac_in_cnt = 0;    			   
		   }			   
       }
       if (IS_MASK_SET(POWER_FLAG8, check_pd_ac_chg2)) //EC RAM 0x208 bit0  
       {
		   pd_ac_in_cnt2++;		  		   	   
		   #if 1
		   if (pd_ac_in_cnt2 == 4)
           {
			   pd_ti_get_active_PDO2(); //To get PD adapter Watt				   
		   }
		   #endif
		   
		   if (pd_ac_in_cnt2 == 5)
           {
			  //981004-211021-A-S 
			  #if 0
			  if (xTIPD1_pd_watt2 > 0) 			  	  
			  {                
				 //SET_MASK(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7
              }
              else
              {			
                //CLEAR_MASK(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7				
			  }
			  #endif
			  //981004-230707-A-S
			  #if 1
			  if (xTIPD1_pd_watt2 == 60)
			  {
				  SET_MASK(EC_Flag6, PD_60W); //EC RAM 0x37E bit0                  			  
			  }
              else if ((xTIPD1_pd_watt2 > 60) && (xTIPD1_pd_watt2 < 80))
              {
				  SET_MASK(EC_Flag6, PD_65W); //EC RAM 0x37E bit1				  
			  }
              else if ((xTIPD1_pd_watt2 >= 80)	&& (xTIPD1_pd_watt2 < 100))
              {
				  SET_MASK(EC_Flag6, PD_80W); //EC RAM 0x37E bit2				  
			  }	
              else if (xTIPD1_pd_watt2 >= 100)
              {
				  SET_MASK(EC_Flag6, PD_100W); //EC RAM 0x37E bit3				  
			  }
			  #endif
              //981004-230707-A-E
			  
              //981004-211021-A-E			  
			  if (xTIPD1_pd_watt2 >= 60) //981004-211021-M from 85			  	  
			  {                                   
				  SET_MASK(POWER_FLAG8, pd_ac_over65w2);
				  SET_MASK(POWER_FLAG1, adapter_in); //201 BIT0 //981004-210224-A
                  if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	              {
				     BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
				  }
				  else
				  {
				     BAT_CHGCURR = 0x0001; //0.256A
				  }	 
				  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
                  SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR);
				  BAT_INCURR = 0x0004; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008
				  //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
                  //BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt //981004-221012-R	
	              //BAT_INCURR = 0x8004; //1.024+0.128 = 1.152A (1.152*4 = 4.608A) //981004-230707-R
                  //BAT_INCURR = 0x0009; //2.048++0.256 = 2.304A (2.304*2 = 4.608A) //84 Watt //981004-210824-M
                  //BAT_INCURR = 0x0005; //1.024+0.256 = 1.28A (1.28*2 = 2.56A) //84Watt /981004-220927-R				  
				  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);
                  SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR);
                  if (SCI_NUM != 0xDB)
		          {	 
		              ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		          }	
		          PD_Adapter_setting();	  
				  if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	              {       
		               //ECQEvent(SCI_PD_ACIN, SCIMode_ACPI_SMBus); //0x90					   
                       ECQEvent(SCI_ADAPTERIN, SCIMode_ACPI_SMBus); //0x60					   
	              }                  
				  Enable_pd_adapter2();				  
			      H_PROCHOT_L = 1; //dCPU //981004-221005-M
                  dGPU_HOLD_EC_RST_L = 0; //dGPU //981004-221005-M
				  Delay1MS(50); //981004-210224-A
				  AC_PRESENT = 1;
				  if ((SLP_S3_L) && (LID_L)) //981004-230428-A
				  {
                       if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
			           {					  
				          PWR_LED2_L = 0; 
					   }	  
				  }
                  //981004-221228-A-S
				  CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                  CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                  CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                  CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	              CLEAR_MASK(EC_Flag4, nv_db20_lv4);
				  CLEAR_MASK(EC_Flag2, pdchgcur_step1); //981004-230630-A-S
	              CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	              CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	              CLEAR_MASK(EC_Flag2, pdchgcur_step4); //981004-230621-A-E
				  CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230828-A
	              CHGCUR_STEP_cnt2 = 0;    
              }
              else
              {
				  CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2);
				  CLEAR_MASK(POWER_FLAG1, adapter_in); 			  
                  if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	              {        
		              //ECQEvent(SCI_PD_ACOUT, SCIMode_ACPI_SMBus); //0x91					  
                      ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus); //0X61					  
	              }
                  BAT_OPTION = 0x4DF9;
                  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
                  SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);
                  Disable_pd_adapter2();				  
                  Delay1MS(50); //981004-210224-A				  
                  AC_PRESENT = 0;
                  if (IS_MASK_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                  {
					  CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                      CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	                  CLEAR_MASK(EC_Flag4, nv_db20_lv4);
                      NV_DB20_SUPPORT();
				  }					  
              }
              ConfigACLIMIT(); //981004-230707-A			  
           }
           if (pd_ac_in_cnt2 == 6)
           {
              if (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)) //EC RAM 0x208 bit0  
              {
				 if (IS_MASK_SET(POWER_FLAG1, power_on))
				 {	 
				    ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
                    PD_Adapter_setting();
                 }
                 else
                 {
                    WTDP = 1; 
	                WTDP2 = 1; 
                    WTDP4 = 1;
                 }			 
			  }
              else if (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) //Battery mode
              {
				   if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                   {		   
                        ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA //981004-220929-A
						if (NVDeventStatus3 == 0) //981004-221130-A
                        {
                            NVDeventStatus = 0x0A; //981004-220929-A 
                        }							
                   }
                   else
                   {
		              CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                      CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                      CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	                  CLEAR_MASK(EC_Flag4, nv_db20_lv4);
                      NV_DB20_SUPPORT();						
	               }		                  			   
              }
           }	   
           if (pd_ac_in_cnt2 == 7)
           {			   
               if (IS_MASK_CLEAR(ProcsH, ProcsH_scion20sec)) 
               { 
                  if (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)) //EC RAM 0x208 bit0  
                  {		   
                     H_PROCHOT_L = 0; //Normal //981004-221005-M            			                      
                     //dGPU_HOLD_EC_RST_L = 0; //Normal
					 if (IS_MASK_SET(POWER_FLAG1, power_on))
				     {	
                        WTDP4 = 45; //981004-210901-M from 215
                     }						
				  }
                  else if (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) //PD Battery mode
                  {
				    if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) )			       
                    { 
                        H_PROCHOT_L = 1; //Normal //981004-221005-M             			                      
                        dGPU_HOLD_EC_RST_L = 0; //Normal //981004-221005-M
						if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-230828-A-S
                        {
					       WTDP4 = 90; //981004-210407-A 
					    } 									
                   }			  
			     }
			   }			   
           }
           if (pd_ac_in_cnt2 >= 9) //981004-221005-A
           {
			   if (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)) //EC RAM 0x208 bit0  
               {		                                  			                      
                     dGPU_HOLD_EC_RST_L = 1; //Normal 					 								   
			   }			   
               CLEAR_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x208 bit0
			   pd_ac_in_cnt2 = 0;    			   
		   }			   
       }
	   if (AC_IN_L)
       {
	     if ((!PD_ADAPTER_IN) && (!PD_ADAPTER_IN2))
	     {
          if ((pd_ac_in_cnt == 0) && (pd_ac_in_cnt2 = 0))
          {		  
           if (xTIPD1_pd_watt >=  xTIPD1_pd_watt2)
           {
		      if (xTIPD1_pd_watt == 60)
			  {
				  SET_MASK(EC_Flag6, PD_60W); //EC RAM 0x338 bit0                  			  
			  }
              else if ((xTIPD1_pd_watt > 60) && (xTIPD1_pd_watt < 80))
              {
				  SET_MASK(EC_Flag6, PD_65W); //EC RAM 0x338 bit1				  
			  }
              else if ((xTIPD1_pd_watt >= 80)	&& (xTIPD1_pd_watt < 100))
              {
				  SET_MASK(EC_Flag6, PD_80W); //EC RAM 0x338 bit2				  
			  }	
              else if (xTIPD1_pd_watt >= 100)
              {
				  SET_MASK(EC_Flag6, PD_100W); //EC RAM 0x338 bit3				  
			  }
			  if (IS_MASK_CLEAR(EC_Flag7, PD_COMPARE))
			  {	  
			     Enable_pd_adapter();
			     Disable_pd_adapter2();
				 //CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2);
				 SET_MASK(EC_Flag7, PD_COMPARE); //EC RAM 0x339 bit1
			  }
              SET_MASK(EC_Flag7, PD1_CHARGE); //EC RAM 0x339 bit2
              CLEAR_MASK(EC_Flag7, PD2_CHARGE); //EC RAM 0x339 bit3			  
	       }
	       else
	       {
		      if (xTIPD1_pd_watt2 == 60)
			  {
				  SET_MASK(EC_Flag6, PD_60W); //EC RAM 0x338 bit0                  			  
			  }
              else if ((xTIPD1_pd_watt2 > 60) && (xTIPD1_pd_watt2 < 80))
              {
				  SET_MASK(EC_Flag6, PD_65W); //EC RAM 0x338 bit1				  
			  }
              else if ((xTIPD1_pd_watt2 >= 80)	&& (xTIPD1_pd_watt2 < 100))
              {
				  SET_MASK(EC_Flag6, PD_80W); //EC RAM 0x338 bit2				  
			  }	
              else if (xTIPD1_pd_watt2 >= 100)
              {
				  SET_MASK(EC_Flag6, PD_100W); //EC RAM 0x338 bit3				  
			  }
			  if (IS_MASK_CLEAR(EC_Flag7, PD_COMPARE))
			  {	  
			     Enable_pd_adapter2();
			     Disable_pd_adapter();
				 //CLEAR_MASK(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4
				 SET_MASK(EC_Flag7, PD_COMPARE); //EC RAM 0x339 bit1
			  }
              SET_MASK(EC_Flag7, PD2_CHARGE); //EC RAM 0x339 bit3
              CLEAR_MASK(EC_Flag7, PD1_CHARGE); //EC RAM 0x339 bit2			  
	       }
          }	
          ConfigACLIMIT();		  
	     }
	   }
       else
       {
		   CLEAR_MASK(EC_Flag7, PD_COMPARE); //EC RAM 0x339 bit1
		   CLEAR_MASK(EC_Flag7, PD1_CHARGE); //EC RAM 0x339 bit2
	       CLEAR_MASK(EC_Flag7, PD2_CHARGE); //EC RAM 0x339 bit3
	   }		   
     //if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	 //{
	   #if 0 //981004-231115-R-S AUTO SETTING	 
	   if (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) //EC RAM 0x211 bit4
	   {
		  #if 1 
		  if ((TEMPER_TEMP <= LOW_TEMPER) || (TEMPER_TEMP >= HIGH_TEMPER)) //(15 Lower or 45 Higher Celsius degree) //981004-171107-M from 10/40
	      {
               BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A (Target : 1271mA )
            #if 0            
            CLEAR_MASK(EC_Flag2, pdchgcur_step1); //981004-230621-A-S
	        CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	        CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	        CLEAR_MASK(EC_Flag2, pdchgcur_step4); //981004-230621-A-E
			CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230731-A			
	        CHGCUR_STEP_cnt2 = 0;
            #endif			
	      }
          #endif		  
          else
          {
			  bRWSMBus(SMbusCh1, SMbusRW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION3 ,  SMBus_NoPEC);
              if (IS_MASK_CLEAR(EC_Flag2, pdchgcur_step1))
              {
                  if((BAT_OPTION3 & 0x0200)==0x00)
				  {
                     CHGCUR_STEP_cnt2++;				   
				     if (CHGCUR_STEP_cnt2 >= 20)
				     {
                        CHGCUR_STEP_cnt2 = 0;
					    SET_MASK(EC_Flag2, pdchgcur_step1);
                        BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A	(Actual : 1264mA)					 
                     }			   
                  }
				  else
			      {
                       CHGCUR_STEP_cnt2 = 0;					 
                  }							
             }
             else if (IS_MASK_CLEAR(EC_Flag2, pdchgcur_step2))
             {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt2++;				   
				   if (CHGCUR_STEP_cnt2 >= 20)
				   {
                      CHGCUR_STEP_cnt2 = 0;
					  SET_MASK(EC_Flag2, pdchgcur_step2);
                      BAT_CHGCURR = 0x0007; //1.024+0.512+0.256 = 1.792A	(Actual : 1779mA)					 
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt2 = 0;					 
                }							
            }
			else if ((IS_MASK_CLEAR(EC_Flag2, pdchgcur_step3)) && (IS_MASK_CLEAR(POWER_FLAG1, power_on))) //981004-230925-M
			//else if (IS_MASK_CLEAR(EC_Flag2, pdchgcur_step3))	
            {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt2++;				   
				   if (CHGCUR_STEP_cnt2 >= 20)
				   {
                      CHGCUR_STEP_cnt2 = 0;
					  SET_MASK(EC_Flag2, pdchgcur_step3);
                      BAT_CHGCURR = 0x8009; //2.048+0.256+0.128+0.064 = 2.496A	(Actual : 2425mA)					 
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt2 = 0;					 
                }							
            }
			else if ((IS_MASK_CLEAR(EC_Flag2, pdchgcur_step4)) && (IS_MASK_CLEAR(POWER_FLAG1, power_on))) //981004-230925-M
			//else if (IS_MASK_CLEAR(EC_Flag2, pdchgcur_step4))	
            {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt2++;				   
				   if (CHGCUR_STEP_cnt2 >= 20)
				   {
                      CHGCUR_STEP_cnt2 = 0;
					  SET_MASK(EC_Flag2, pdchgcur_step4);
                      BAT_CHGCURR = 0x800C; //2.048+1.024+0.128 = 3.2A	(Actual : 3198mA)					 
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt2 = 0;					 
                }							
            }
            //else //981004-230621-R
            //{
                //BAT_CHGCURR = 0x0007; //1.024+0.512+0.256 = 1.792A	(Actual : 1791mA)				
            //}	
		  }			
	     }
		 #endif //981004-231115-R-E
   }
   else //AC IN
   {
       if (IS_MASK_SET(POWER_FLAG11, dual_ac)) //EC RAM 0x211 bit5
       {
		  dual_ac_cnt++;
          if (dual_ac_cnt == 1)
          {
              Disable_pd_adapter();
			  //CLEAR_MASK(POWER_FLAG11, dual_ac); //EC RAM 0x211 bit5
			  CLEAR_MASK(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4
              CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2);			  
			  //dual_ac_cnt = 0;
			  //981004-230707-A-S
	          CLEAR_MASK(EC_Flag6, PD_60W);
	          CLEAR_MASK(EC_Flag6, PD_65W);
	          CLEAR_MASK(EC_Flag6, PD_80W);
	          CLEAR_MASK(EC_Flag6, PD_100W);
	          //981004-230707-A-E
          }	
          if (dual_ac_cnt >= 2)
          {
             PD_POWER_ON = 1;			  
             CLEAR_MASK(POWER_FLAG11, dual_ac); //EC RAM 0x211 bit5			  
			 dual_ac_cnt = 0;
          }	  
       }		   
   }
   #endif   
	//981004-210118-A-E
	
    //992022-140904-A-S patch for Qevent can't be received when Windows logo
    if (IS_MASK_SET(POWER_FLAG10, sci_on_20sec)) 
    {
        Sci_on_20sec_cnt++;
        //NVDeventStatus = 0x0A; //992022-140922-M
        //ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //992022-140922-M //0xDA
        if (Sci_on_20sec_cnt >= 20)
        {
            CLEAR_MASK(POWER_FLAG10, sci_on_20sec);
            Sci_on_20sec_cnt = 0;			
			EC_AMP_MUTE_L = 1; //Unmute 981004-150803-A
            //if (AC_IN_L) //battery mode
			//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
			if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
            {
                if (RMCAP_TEMP <= BATCAP50)
                    SET_MASK(POWER_FLAG4, bat30_on);
                else
                    CLEAR_MASK(POWER_FLAG4, bat30_on);
                //CLEAR_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
				CLEAR_MASK(POWER_FLAG1, adapter_in); //981004-210224-A
                ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus);
                ECQEvent(SCI_BAT30ON, SCIMode_ACPI_SMBus); //0x65 //992022-130423-M  Max request
                //NVDeventStatus = 0x0A; //981004-190320-R
                //ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //981004-190320-R //0xDA
				//WTDP4 = 1; //981004-190320-R from 5
            }			
            else if (!AC_IN_L) 
            {
				//981004-200410-R-S
				#if 0
                if (AC_boost_Status)
                    ECQEvent(SCI_P1, SCIMode_ACPI_SMBus); //0xA1 
                else
                    ECQEvent(SCI_P0, SCIMode_ACPI_SMBus); //0xA0
                #endif				
				//981004-231002-M-E
				if (IS_MASK_CLEAR(POWER_FLAG3, adapter_overtemp))
				{	
                    ECQEvent(SCI_BATT_LOW_TEMPER, SCIMode_ACPI_SMBus); //0xD1
                }
                else
                {
                    ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2	
                }			
                //981004-231002-M-S
				//if (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on))
				if ((IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)) && (IS_MASK_CLEAR(POWER_FLAG3, adapter_overtemp))) //981004-231002--M	
				{	
                   if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w))
	               {
		               WTDP = 110; //981004-231012-M from 157
			           WTDP2 = 157;
			           WTDP4 = 246; //i7 CPU
	               }
	               else
	               {
                       WTDP = 110; //981004-231012-M from 157
			           WTDP2 = 157;
			           WTDP4 = 246; //i9 CPU
                   }
                }
                else if (IS_MASK_SET(POWER_FLAG6, sv_thrt_on)) //981004-231002-M
                {
                   if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) )
			       {
			          if (NVDeventStatus <= 7)
				      {			       
				          if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                      {
                              WTDP = 20;
                              WTDP2 = 45;							  
                              WTDP4 = 90; 
						  }
                          else //i9 CPU
                          {
                              WTDP = 20;
                              WTDP2 = 45;							  
                              WTDP4 = 90;
                          }                   				   
				      }   
		           }
                }			
                //981004-200410-M-E 				
            }
            else if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))
            {
               ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
               PD_Adapter_setting();
			   H_PROCHOT_L = 0; //Normal //981004-221005-M
            }		
        }
         

    }
    //992022-140904-A-E patch for Qevent can't be received when Windows logo

}

/******************************************************************************/
/** 1second B service routine
*******************************************************************************/
void oem_1SB_service(void)
{
    ProcessCharge();

    	//981004-200923-A-S //Step charging
	
   //if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
   //{
	if (IS_MASK_SET(EC_Flag1, acin_chgcur))
    {
	  //if (IS_MASK_CLEAR(POWER_FLAG3, boost_on1) && (IS_MASK_CLEAR(POWER_FLAG4, bat_cap_downgrade))) //981004-200429-A 	
	  //{
        #if 0	//981004-230925-M	  
	    if ((TEMPER_TEMP <= LOW_TEMPER) || (TEMPER_TEMP >= HIGH_TEMPER)) //(15 Lower or 45 Higher Celsius degree) //981004-171107-M from 10/40
	    {  		    
            BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A (Target : 1271mA )
            CLEAR_MASK(EC_Flag1, chgcur_step1); //981004-230621-A-S
	        CLEAR_MASK(EC_Flag1, chgcur_step2);
	        CLEAR_MASK(EC_Flag1, chgcur_step3);
	        CLEAR_MASK(EC_Flag1, chgcur_step4);
	        CLEAR_MASK(EC_Flag1, chgcur_step5); //981004-230621-A-E
	        CHGCUR_STEP_cnt = 0;			            			
	    }
        #endif		
        //else
        //{
			//bRWSMBus(SMbusCh1, SMbusRW, Charger_Addr, CHGCmd_Option3,  &BAT_OPTION3 ,  SMBus_NoPEC);
           SMBUS_RW_W(SMbusCh1, SMbusRW, Charger_Addr, CHGCmd_Option3,  &BAT_OPTION3);
            if (IS_MASK_CLEAR(EC_Flag1, chgcur_step1))
            {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt++;				   
				   if (CHGCUR_STEP_cnt >= 20)
				   {
                      CHGCUR_STEP_cnt = 0;
					  SET_MASK(EC_Flag1, chgcur_step1);
                      BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A	(Actual : 1278mA)					 
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt = 0;					 
                }							
            }
            else if (IS_MASK_CLEAR(EC_Flag1, chgcur_step2))
            {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt++;				   
				   if (CHGCUR_STEP_cnt >= 20)
				   {
                      CHGCUR_STEP_cnt = 0;
					  SET_MASK(EC_Flag1, chgcur_step2);
                      BAT_CHGCURR = 0x0007; //1.024+0.512+0.256 = 1.792A	(Actual : 1791mA)					 
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt = 0;					 
                }							
            }
            else if (IS_MASK_CLEAR(EC_Flag1, chgcur_step3))
            {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt++;				  
				   if (CHGCUR_STEP_cnt >= 20)
				   {
                      CHGCUR_STEP_cnt = 0;
					  SET_MASK(EC_Flag1, chgcur_step3);
                      BAT_CHGCURR = 0x8009; //2.048+0.256+0.128 = 2.432A	(Actual : 2432mA)					  
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt = 0;					  
                }							
            }		
            else if (IS_MASK_CLEAR(EC_Flag1, chgcur_step4))
            {
                if((BAT_OPTION3 & 0x0200)==0x00)
				{
                   CHGCUR_STEP_cnt++;				   
				   if (CHGCUR_STEP_cnt >= 20)
				   {
                      CHGCUR_STEP_cnt = 0;
					  SET_MASK(EC_Flag1, chgcur_step4);
                      BAT_CHGCURR = 0x800C; //2.048+1.024+0.128 = 3.2A	(Actual : 3200mA)					  
                   }			   
                }
				else
			    {
                      CHGCUR_STEP_cnt = 0;					 
                }							
            }
			else if (IS_MASK_CLEAR(EC_Flag1, chgcur_step5))
            {
                if((BAT_OPTION3 & 0x0200)==0x00) 
				{
                   CHGCUR_STEP_cnt++;                   				   
				   if (CHGCUR_STEP_cnt >= 20)
				   {
                      CHGCUR_STEP_cnt = 0;
					  SET_MASK(EC_Flag1, chgcur_step5);
                      if (RMCAP_TEMP <= BATCAP50) //981004-221209-M
			          {
                        if ((RMCAP_TEMP) <= (BATCAP35)) //BATCAP35 = 1954 //981004-221209-A
					    {		 						        
						    BAT_CHGCURR = 0x0018; //4.096+2.048 = 6.144A
							
                        }
                        else
                        {
							BAT_CHGCURR = 0x8011; //4.096+0.256+0.128 = 4.48A
						
						}						  
                      }
                      else
                      {						      						  
                          BAT_CHGCURR = 0x800C;	//3.2A					
					  }	
				   }					  
                }
				else
			    {
                      CHGCUR_STEP_cnt = 0;					 
                }							
            }
            //else
            //{
                //BAT_CHGCURR = 0x0018; //2.048+1.024+0.128 = 3.2A	(Actual : 3200mA)				
            //}		
        }
	  //}
	//}  
	  #if 0
      else //981004-200429-A-S
	  {
		 if (IS_MASK_CLEAR(POWER_FLAG4, bat_cap_downgrade))
         {			 
		     BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A
         }			 
         CLEAR_MASK(EC_Flag1, chgcur_step1);
	     CLEAR_MASK(EC_Flag1, chgcur_step2);
	     CLEAR_MASK(EC_Flag1, chgcur_step3);
	     CLEAR_MASK(EC_Flag1, chgcur_step4);
		 CLEAR_MASK(EC_Flag1, chgcur_step5);
	     CHGCUR_STEP_cnt = 0;		 
	  } //981004-200429-A-E 
      #endif	  
	//}
    //981004-200923-A-E
	
    //981004-190109-A-S	
	//if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3)))
    if (SLP_S3_L) 		
    {
         if (IS_MASK_SET(POWER_FLAG2, LED_TEST_ON)) //EC RAM 0x202 Bit 7
		 {
			//BAT_LED_L = ~BAT_LED_L; //981004-231212-R
			//BAT_LED_L = ~BAT_FULL_L; 
			PWR_LED2_L = ~PWR_LED2_L; //981004-191129-M
			//981004-231120-A-S
			if (LED_TEST_CNT == 0)
			{
               BAT_LED_L = 1; //981004-231218-A
               BAT_FULL_L = 0; //981004-231218-A			   
			   SET_GPO_KSO12_HI();  //EC_KBLED_EN
		       SET_GPO_KSO13_HI();  //EC_LBLED_EN
			   LED_TEST_CNT = 1;
               SET_GPO_KSO6_HI(); //981004-240529-A			   
			}
            else
            {
			   BAT_LED_L = 0; //981004-231218-A
               BAT_FULL_L = 1; //981004-231218-A	
			   SET_GPO_KSO12_LO(); //EC_KBLED_EN
               SET_GPO_KSO13_LO(); //EC_LBLED_EN7
               LED_TEST_CNT = 0;
               SET_GPO_KSO6_LO(); //981004-240529-A			   
			}
            //981004-231120-A-E			
         }
        else 
        {
		  if (IS_MASK_CLEAR(POWER_FLAG12, EC_modern_stby)) //981004-220916-A
          { 	
		     if (LID_L) //981004-211130-A
             {			   
                if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
			    {					  
				    PWR_LED2_L = 0; 
			    }
		     }
			 SET_GPO_KSO12_HI(); //981004-231117-A //EC_KBLED_EN
		     SET_GPO_KSO13_HI(); //981004-231117-A //EC_LBLED_EN
	      }
          else
          {
			   PWR_LED2_L = 1; //981004-220916-A
			   SET_GPO_KSO12_LO(); //EC_KBLED_EN
               SET_GPO_KSO13_LO(); //EC_LBLED_EN7
		  }	          
          LED_TEST_CNT = 0; //981004-231120-A			  
        }
		
		//981004-240529-A-S
        if (IS_MASK_SET(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3
	    {
		   SET_GPO_KSO6_LO(); //KSOLGOENR 0X1D0E BIT6 => 0 //HDD LED
		   BAT_LED_L = 1; 
           BAT_FULL_L = 1; 
		   PWR_LED2_L = 1;
	    }
        else
        {
		   if (IS_MASK_CLEAR(POWER_FLAG12, EC_modern_stby)) //981004-220916-A
           { 
              if (LID_L) //981004-211130-A
              {		   
		        SET_GPO_KSO6_HI(); //KSOLGOENR 0X1D0E BIT6 => 1 //HDD LED
			    PWR_LED2_L = 0;
			  }	
		   }	  
	    }
        //981004-240529-A-E		
    }
	
    //981004-190109-A-E
	
	//981004-220803-M-S
	if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))) 
    {
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR1, &TEMP_TR1 , SMBus_NoPEC)) //NCT7601Y TR1
       {		   
           if ((TEMP_TR1) & 0x80)
		   {
		       TEMP_TR1 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR2, &TEMP_TR2 , SMBus_NoPEC)) //NCT7601Y TR2
       {		   
           if ((TEMP_TR2) & 0x80)
		   {
		       TEMP_TR2 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR6, &TEMP_TR3 , SMBus_NoPEC)) //NCT7601Y TR3 EC RAM 0x29E //981004-221111-M from Thermal1_TR3
       {		   
           if ((TEMP_TR3) & 0x80)
		   {
		       TEMP_TR3 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR5, &TEMP_TR4 , SMBus_NoPEC)) //NCT7601Y TR4 EC RAM 0x29F //981004-221111-M from Thermal1_TR4
       {		   
           if ((TEMP_TR4) & 0x80)
		   {
		       TEMP_TR4 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR4, &TEMP_TR5 , SMBus_NoPEC)) //NCT7601Y TR5 EC RAM 0x2AD //981004-221111-M from Thermal1_TR5
       {		   
           if ((TEMP_TR5) & 0x80)
		   {
		       TEMP_TR5 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR3, &TEMP_TR6 , SMBus_NoPEC)) //NCT7601Y TR6 EC RAM 0x2AE //981004-221111-M from Thermal1_TR6
       {		   
           if ((TEMP_TR6) & 0x80)
		   {
		       TEMP_TR6 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR7, &TEMP_TR7 , SMBus_NoPEC)) //NCT7601Y TR7 //981004-221220-A EC RAM 0x2AC
       {		   
           if ((TEMP_TR7) & 0x80)
		   {
		       TEMP_TR7 = 0;
		   }
	   }
	   if (bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR8, &TEMP_TR8 , SMBus_NoPEC)) //NCT7601Y TR8 //981004-221028-A EC RAM 0x2AF
       {		   
           if ((TEMP_TR8) & 0x80)
		   {
		       TEMP_TR8 = 0;
		   }
	   }
        
		//bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR2, &TEMP_TR2 , SMBus_NoPEC); //NCT7601Y TR2
		//bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR5, &TEMP_TR5 , SMBus_NoPEC); //NCT7601Y TR5
		//bRWSMBus(SMbusCh1, SMbusRB, Thermal1_Addr, Thermal1_TR6, &TEMP_TR6 , SMBus_NoPEC); //NCT7601Y TR6
    }		
	//981004-220803-M-E
	
	//981004-220707-S to 500ms
	#if 0
	if (IS_MASK_SET(POWER_FLAG3, ship_mode))
	{
	    SHIP_MODE_cnt++;
		if (SHIP_MODE_cnt >= 3)
		{
		    SHIP_MODE_cnt = 0;
			CLEAR_MASK(POWER_FLAG3, ship_mode);
			SysPowState = SYSTEM_S0_S4;
			
			Ship_mode = 0x1000;
            bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
            Delay1MS(250); 
            bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC); //981004-221213-A
            Delay1MS(250);  //981004-221213-A
            #if 0			
            bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
            for(ITempB01=0x00;ITempB01<20;ITempB01++)	//240us loop
	        {
               Delay1MS(250);
            }
			#endif
			CLEAR_MASK(POWER_FLAG3, ship_mode);
		}
	}
	#endif
    //981004-220707-S
	
    #ifdef PECI_Support
    if(SystemIsS0)
    {
        #if ReadPKGTemperature
        PECI_ReadPkgTemperature();
        #endif
    }
    #endif
    if ((IS_MASK_SET(POWER_FLAG2, sci_on)) && (IS_MASK_CLEAR(POWER_FLAG1, enter_S3))) 
    {
	   GetRPM1(); //981004-140709-A
	   GetRPM2(); //981004-140813-A
	   //GetRPM3(); //981004-220509-A
	   //GetRPM4(); //981004-220509-A
	}   
	
	//981004-190109-A-S
	MBX_CPU_FAN_FLAG = 1;
	MBX_CPU_FAN_RPMH = RPM1 >> 8;
	MBX_CPU_FAN_RPML = RPM1;
	MBX_CPU_FAN_FLAG = 0;
	
	MBX_GPU_FAN_FLAG = 1;
	MBX_GPU_FAN_RPMH = RPM2 >> 8;
	MBX_GPU_FAN_RPML = RPM2;
	MBX_GPU_FAN_FLAG = 0;
	//981004-190109-A-E
	
    #if GetSysTempSupport
    ReadSysTemp();
    #endif

    ProcessDischarge();
    
    //992022-140904-A-S Control status for NV Devent when AC out

    //if (AC_IN_L)
	//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
    if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
    {
        if ((IS_MASK_CLEAR(POWER_FLAG2, sci_on)) || (IS_MASK_SET(ProcsH, ProcsH_acout)) || (IS_MASK_SET(ProcsH, ProcsH_scion20sec)) || (IS_MASK_SET(AmpHigh_flag, AmpHigh)))
		{		   
            return;
        }
		if ((IS_MASK_SET(POWER_FLAG11, check_pd_ac_chg)) || (IS_MASK_SET(POWER_FLAG8, check_pd_ac_chg2)))
		{
			PD_Adapter_setting();
			//NVDeventStatus = 2;
            return;
        }	
    
        if (IS_MASK_SET(POWER_FLAG7, dgpu_9Aon))
        {
            //switch (NVcnt1 & 0x01) //after 2 sec.
            //{    

            //    case 0x01: //after 2 sec.
              
                    if (NVDeventStatus < 0x0A) 
                    {
                        NVDeventStatus++;

                        switch (NVDeventStatus)
                        {
                            case 0x02:
                                 ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
								 //981004-200306-M-S
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {	
                                       WTDP = 35;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD3
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD3  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 35;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD3 
						            }
                                    else
                                    {
									  WTDP = 20;
                                      WTDP2 = 45;	
	                                  WTDP4 = 90; //0xD3  
					                }
                                 }                                 							 
                                 //981004-200130-M-E								 
                                break;
            
                            case 0x03:
                                 ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3
                                 //981004-200130-M-S
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {	
                                       WTDP = 35;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 35;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 							 
                                 //981004-200130-M-E								 
                                break;
                                
                            case 0x04:
                                 ECQEvent(SCI_NV_D4, SCIMode_ACPI_SMBus); //0xD4								 
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 30;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 30;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 
                                break;
                                
                            case 0x05:
                                 ECQEvent(SCI_NV_D5, SCIMode_ACPI_SMBus); //0xD5                                 
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 27;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 27;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 								 
                                break;
                                
                            case 0x06:
                                 ECQEvent(SCI_NV_D6, SCIMode_ACPI_SMBus);  //0xD6
								 //981004-200130-M-S
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 23;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 23;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 								 
                                 //981004-200130-M-E
                                break;

                            //992022-140922-M-S
                            case 0x07:
                                 ECQEvent(SCI_NV_D7, SCIMode_ACPI_SMBus);  //0xD7								
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
                                     WTDP = 20;
                                     WTDP2 = 45; 									 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 20;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }                             
                                break;

                            case 0x08:
                                 ECQEvent(SCI_NV_D8, SCIMode_ACPI_SMBus);  //0xD8								 
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
									 WTDP = 19;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 19;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }                                 
                                break;

                            case 0x09:  
                                 SET_MASK(POWER_FLAG8, D7_flag_for_bios);  //for BIOS to know and force keep in CPU P12 because smartcooling will let BIOS to become P8
                                 ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
                                     WTDP = 17;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 17;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }        
                                break;

                            case 0x0A:  
                                 SET_MASK(POWER_FLAG8, D7_flag_for_bios);  //for BIOS to know and force keep in CPU P16 because smartcooling will let BIOS to become P8
                                 ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA                                							 
				                 if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
                                     WTDP = 15; 
									 WTDP2 = 45; 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 15;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }                                 
                                break;
								
								#if 0
                            case 0x0B:                                    
                                 //ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB								 
				                 //PD_Adapter_setting();                                                										
								 break;
						   #endif 
                            //992022-140922-M-E
                            default:
                                break;
                        }
                    }    
        }        
		else if ((IS_MASK_CLEAR(POWER_FLAG7, dgpu_9Aon)) && (IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) 
			     && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on))) //981004-190329-M
		{		 
                    if (NVDeventStatus > 2) //992022-140922-M from 1
                    {
                        NVDeventStatus--;
						#if 0
						if (NVDeventStatus == 7)
						{
                            if (IS_MASK_SET(POWER_FLAG11, acout_pdin)) //EC RAM 0x211 bit6
							{
								//ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
                                //PD_Adapter_setting();
								//NVDeventStatus = 2;
                                return;								
							}	
                        }					
						#endif	

                        switch (NVDeventStatus)
                        {
                            //992022-140922-R-S
                            //case 0x01:
                            //     ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
                            //    break;
                            //992022-140922-R-E
                                
                            case 0x02:
                                 ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
								 //981004-200130-M-S
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 35;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD2
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90;   
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 35;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD2 
						            }
                                    else
                                    {
									  WTDP = 20;
                                      WTDP2 = 45;	
	                                  WTDP4 = 90;   
					                }
                                 }                                 							 
                                 //981004-200130-M-E								 
                                break;
            
                            case 0x03:
                                 ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3
                                 //981004-200130-M-S
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 35;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 35;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 							 
                                 //981004-200130-M-E								 
                                break;
                                
                            case 0x04:
                                 ECQEvent(SCI_NV_D4, SCIMode_ACPI_SMBus); //0xD4								 
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 30;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 30;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 
                                break;
                                
                            case 0x05:
                                 ECQEvent(SCI_NV_D5, SCIMode_ACPI_SMBus); //0xD5                                 
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 27;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 27;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 								 
                                break;
                                
                            case 0x06:
                                 ECQEvent(SCI_NV_D6, SCIMode_ACPI_SMBus);  //0xD6
								 //981004-200130-M-S
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 23;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
						         }								 
                                 else //i9 CPU
                                 {
						            if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                    {
                                       WTDP = 23;
                                       WTDP2 = 45;									   
						               WTDP4 = 90; 
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;									   
						               WTDP4 = 90;  
					                }
                                 }                                 								 
                                 //981004-200130-M-E
                                break;

                            //992022-140922-M-S
                            case 0x07:
                                 ECQEvent(SCI_NV_D7, SCIMode_ACPI_SMBus);  //0xD7								
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
                                     WTDP = 20;
                                     WTDP2 = 45; 									 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 20;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }                             
                                break;

                            case 0x08:
                                 ECQEvent(SCI_NV_D8, SCIMode_ACPI_SMBus);  //0xD8								 
						         if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
									 WTDP = 19;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 19;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }                                 
                                break;

                            case 0x09:  
                                 SET_MASK(POWER_FLAG8, D7_flag_for_bios);  //for BIOS to know and force keep in CPU P12 because smartcooling will let BIOS to become P8
                                 ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                             {
                                     WTDP = 17;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90; 
						         }
                                 else //i9 CPU
                                 {
                                     WTDP = 17;
                                     WTDP2 = 45;									 
                                     WTDP4 = 90;
                                 }                                        
                                break;

                            //992022-140922-M-E
                                
                            default:
                                break;
                        }
                    }
            //}
            //NVcnt2++;
            //NVcnt1 = 0;

        }
        
    }
}

/******************************************************************************/
/** 1min service routine
*******************************************************************************/
void oem_1min_service(void)
{
}

/******************************************************************************/
/** Initial function, variable, GPIO
*******************************************************************************/
void Oem_init(void)
{
	Initial_GPIO();
    Port80_Enalbe_Threshold(1,0);
    Port81_Enalbe_Threshold(1,0);

    LED7s_TABLE[0] = 0x3F;
    LED7s_TABLE[1] = 0x06;
    LED7s_TABLE[2] = 0x5B;
    LED7s_TABLE[3] = 0x4F;
    LED7s_TABLE[4] = 0x66;
    LED7s_TABLE[5] = 0x6D;
    LED7s_TABLE[6] = 0x7D;
    LED7s_TABLE[7] = 0x07;
    LED7s_TABLE[8] = 0x7F;
    LED7s_TABLE[9] = 0x6F;
    LED7s_TABLE[10] = 0x77;
    LED7s_TABLE[11] = 0x7C;
    LED7s_TABLE[12] = 0x39;
    LED7s_TABLE[13] = 0x5E;
    LED7s_TABLE[14] = 0x79;
    LED7s_TABLE[15] = 0x71;
	//BAT_STATUS2 = 55;
	// ~23.7Khz fan
	PWM_Reset(Pwm00);
	PWM_Clock_Sel(Pwm00, _50MHZ);
	PWM_Set_Divider(Pwm00,2110);
	PWM_Set_Duty(Pwm00,800);
	PWM_On(Pwm00,enable);

	PWM_Reset(Pwm02);
	PWM_Clock_Sel(Pwm02, _50MHZ);
	PWM_Set_Divider(Pwm02,2110);
	//PWM_Set_Duty(Pwm02,1055);
	PWM_On(Pwm02,enable);
	
	PWM_Reset(Pwm03);
	PWM_Clock_Sel(Pwm03, _50MHZ);
	PWM_Set_Divider(Pwm03,2110);
	PWM_Set_Duty(Pwm03,800);
	PWM_On(Pwm03,enable);

	//TACHO
	TACHO_Init(0);
	TACHO_Set_Mode(0,1);
	TACHO_Set_High_Limit(0,0x1000);
	TACHO_Set_Low_Limit(0,0x500);
	TACHO_Enable_Interrupt(0,COUNTER_EXCEED_LIMIT_STAT+COUNTER_TOGGLE_STAT+COUNTER_READY_STAT);
	// ACPI_RAM(BRAM) data
//	BAT_STATUS=0xFF;			// 0x00
//	POWER_FLAG1=0x59;				// 0x01
//	POWER_FLAG2=0x11;			// 0x02
//	POWER_FLAG3=0xAA;				// 0x03
//	POWER_FLAG4=0xBB;			// 0x04
//	POWER_FLAG5=0xB4;			// 0x05
//	POWER_FLAG6=0x44;		// 0x06
//	RELEASE_TYPE = 0x03;
//	X5LVG1_EC_VER = 0x05;

	I2C_Initial(0,0,0,0);
	I2C_Initial(1,0,0,0);
    I2C_Initial(3,0,0,0);
	I2C_Initial(4,0,0,0);
	
	//uint8_t OEMRAM00;
	//OEMRAM00[0] = *((uint8_t *)(ECOEMRAM1 + 0x0000));
	//OEMRAM00[1] = 0;
	
	//PWRBTN_WDT_Init(1, 0x7FFF,0,0x500,0xFF);
	SystemState = SYSTEM_G3;
}

void GETRPM1(void)
{
	uint16_t RPM;
	RPM = (uint16_t)(100000/(TACHO0->CTRL_b.CNT))*30;
	*(uint16_t*)(0x200300FC) = RPM;	// for test

	
}
#if 0
void INIT_TM1650(void)
{
	
	uint8_t test_val[1] = {0x59};
    I2C_WR_BUFFER[0] = 0x41;    //Brightness = 4,
    //I2C_WriteStream(SMbusCh4, 0x48, &I2C_WR_BUFFER[0], 1);
	I2C_Protocol(3, 0x48, 1, 0, I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x3F;
    //I2C_WriteStream(SMbusCh4, 0x68, &I2C_WR_BUFFER[0], 1);
	I2C_Protocol(3, 0x68, 1, 0, I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x06;
    //I2C_WriteStream(SMbusCh4, 0x6A, &I2C_WR_BUFFER[0], 1);
	I2C_Protocol(3, 0x6A, 1, 0, I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x5B;
    //I2C_WriteStream(SMbusCh4, 0x6C, &I2C_WR_BUFFER[0], 1);
	I2C_Protocol(3, 0x6C, 1, 0, I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x4F;
    //I2C_WriteStream(SMbusCh4, 0x6E, &I2C_WR_BUFFER[0], 1);
	I2C_Protocol(3, 0x6E, 1, 0, I2C_WR_BUFFER,NULL);

//    Last_P81HDR = P81HDR;
//    Last_P80HDR = P80HDR;

//    bRWSMBus(SMbusCh4, SMbusSBC, 0x48,
//                0x59, &I2C_WR_BUFFER[0], 0);
	I2C_SMBusModProtocol(3,3,0x48,NULL,test_val,NULL);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[P80HDR & 0x0F];
//    bRWSMBus(SMbusCh4, SMbusSBC, 0x68,
//                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
	I2C_SMBusModProtocol(3,3,0x68,NULL,I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[(P80HDR >> 4) & 0x0F];
//    bRWSMBus(SMbusCh4, SMbusSBC, 0x6A,
//                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
	I2C_SMBusModProtocol(3,3,0x6A,NULL,I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[P81HDR & 0x0F];
//    bRWSMBus(SMbusCh4, SMbusSBC, 0x6C,
//                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
	I2C_SMBusModProtocol(3,3,0x6C,NULL,I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[(P81HDR >> 4) & 0x0F];
//    bRWSMBus(SMbusCh4, SMbusSBC, 0x6E,
//                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
	I2C_SMBusModProtocol(3,3,0x6E,NULL,I2C_WR_BUFFER,NULL);
	
	
	I2C_WR_BUFFER[0] = 0x41;
	I2C_Protocol(4, 0x48, 1, 0, I2C_WR_BUFFER,NULL);
	I2C_WR_BUFFER[0] = 0x3F;
	I2C_Protocol(4, 0x68, 1, 0, I2C_WR_BUFFER,NULL);	
    I2C_WR_BUFFER[0] = 0x06;
    I2C_Protocol(4, 0x6A, 1, 0, I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x5B;
    I2C_Protocol(4, 0x6C, 1, 0, I2C_WR_BUFFER,NULL);
    I2C_WR_BUFFER[0] = 0x4F;
    I2C_Protocol(4, 0x6E, 1, 0, I2C_WR_BUFFER,NULL);
	
	Last_P81HDR = Port81_Get_Data();
    Last_P80HDR = Port80_Get_Data();

	SMBUS_RW_B(4, 3, 0x48 ,0x59 ,NULL);
	SMBUS_RW_B(4, 3, 0x68 ,0x0F ,NULL);
	SMBUS_RW_B(4, 3, 0x6A ,0x0F ,NULL);
	SMBUS_RW_B(4, 3, 0x6C ,0x0F ,NULL);
	SMBUS_RW_B(4, 3, 0x6E ,0x0F ,NULL);
}
#endif

//------------------------------------------------------------
// service_OEM_1
//------------------------------------------------------------
void service_OEM_1(void)
{   
    //981004-210617-A-S No LTR-F216A Light sensor		
    #if 0
	 if (!bRWSMBus(SMbusChB, SMbusRW, LightSensorAddr, DATAREAD, &LS_DATA, SMBus_NoPEC))
	 {	    	
		(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr2, DATAREAD, &ARAdata, SMBus_NoPEC));
        LSCTRL = 0x0100; //981004-150821-M 		
       (bRWSMBus(SMbusChB, SMbusWW, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); //(EC RAM : 0x27C)
        PORDATA = 0x0000;   
       (bRWSMBus(SMbusChB, SMbusWW, LightSensorAddr, POR, &PORDATA, SMBus_NoPEC)); //(EC RAM : 0x266)
        LSCTRL = 0x0000;   
       (bRWSMBus(SMbusChB, SMbusWW, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); //(EC RAM : 0x27C)	
	 }	
	 //981004-210617-A-E
	 #endif
	 if(!xITEPD_FlashUtilityEnable) //981004-231114-A
     {
        //981004-210705-A-S
	    ///(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_L, &LS_DATA_L, SMBus_NoPEC));
	    ///(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_M, &LS_DATA_M, SMBus_NoPEC));
	    ///(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_H, &LS_DATA_H, SMBus_NoPEC));
        SMBUS_RW_B(1, SMbusRB, LightSensorAddr, DATAREAD_L, &LS_DATA_L);
        SMBUS_RW_B(1, SMbusRB, LightSensorAddr, DATAREAD_L, &LS_DATA_L);
        SMBUS_RW_B(1, SMbusRB, LightSensorAddr, DATAREAD_L, &LS_DATA_L);
	    // Lux = (LS_DATA<<8) | (LS_DATA>>8);
        Lux =((LS_DATA_H<<16) | (LS_DATA_M<<8) | (LS_DATA_L)); //981004-210705-M
        Lux_NEW = Lux;	
        
        if (IS_MASK_SET(POWER_FLAG2, sci_on))
        {	    
            if ((Lux_NEW > ((Lux_TEMP) + (Lux_TEMP>>2))) || (Lux_NEW < ((Lux_TEMP) - (Lux_TEMP>>2))))
            {           
                Lux_TEMP = Lux_NEW;			            
                ECQEvent(SCI_LS_DATA, SCIMode_ACPI_SMBus); //0x98 			
            }	
        }	
     }
	 
	//981004-210617-A-E
}

//------------------------------------------------------------
// service_OEM_2
//------------------------------------------------------------
void service_OEM_2(void)
{

}

//981004-121214-A-S
//------------------------------------------------------------
// service_OEM_3
//------------------------------------------------------------
void service_OEM_3(void)
{
    static BYTE DarkDelay;
    static bit CntDown;
    static BYTE dimcnt;

					        
	//  BYTE PWMValue[] = {0x00,0x13,0x22,0x31,0x40,0x4F,0x5E,0x6D,    	
    //                     0x7C,0x8B,0x9A,0xA9,0xB8,0xC7,0xD6,0xE5};

    PWMValue[0] = 0x00;
    PWMValue[1] = 0x13;
    PWMValue[2] = 0x22;
    PWMValue[3] = 0x31;
    PWMValue[4] = 0x40;
    PWMValue[5] = 0x4F;
    PWMValue[6] = 0x5E;
    PWMValue[7] = 0x6D;
    PWMValue[8] = 0x7C;
    PWMValue[9] = 0x8B;
    PWMValue[10] = 0x9A;
    PWMValue[11] = 0xA9;
    PWMValue[12] = 0xB8;
    PWMValue[13] = 0xC7;
    PWMValue[14] = 0xD6;
    PWMValue[15] = 0xE5;				   
	//BYTE PWMValue[] = {0xE2,0xE3,0xE4,0xE5};				   
 
    if (DarkDelay)
    {
        DarkDelay--;		
        return;
    }

    if (CntDown)
    {
        dimcnt--;
		///GPCRA4 = ALT; //981004-181011-R per SPEC
        GPIO_Func_Mode(27,1);
        
        if (dimcnt == 0x00)
        {
            CntDown = 0;
            //DarkDelay = 0x14; //981004-150506-R (Brightness time)			
        }
    }
    else
    {
        dimcnt++;
        
        if (dimcnt == 0x0F)      
		{
            CntDown = 1;
		    DarkDelay = 0x14; //981004-150506-A (Darkness time)
			//GPCRA4 = OUTPUT+PULL_DW;
            GPIO_Set_IO(27,1);
            GPIO_Config(27,0,0,1); 	
            PWR_LED2_L = 1; //981004-201223-M 	 
		}	
    }
        
    DCR2 = PWMValue[dimcnt]; //981004-210104-M from DCR1
	DCR4 = DCR2;  //981004-220719-A per EE Request 
}
//981004-121214-A-E

//------------------------------------------------------------
// service_OEM_4
//------------------------------------------------------------
void service_OEM_4(void)
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
void Hook_main_service_H(void) 
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
void Hook_main_service_L(void) 
{

}

//------------------------------------------------------------
// Timer event control function
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
//------------------------------------------------------------
BYTE Hook_Only_Timer1msEvent(void)
{
    if ((SysPowState==SYSTEM_S4_S0) || (SysPowState==SYSTEM_S3_S0))
    {
        if (++PowerOnWDT > 4400)  // > 4.4 sec
        {
            PowerOnWDT = 0x00;
            Oem_TriggerS0S4(SC_PowerOnWatchDog);
        }

        return(Only_Timer1msEvent);
    }
    else
        PowerOnWDT = 0x00;
    
    #if PowerSequnceOnly    
    return(Only_Timer1msEvent);
    #endif

// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
    return(All_TimerEvent);
}

//----------------------------------------------------------------------------
// OEM_SkipMainServiceFunc
//  Note:
//      1. Always return(0xFF|Normal_MainService) to run normal main_service function.
//      2. If you don't understand the use of OEM_SkipMainServiceFunc function, don't change anything.
//----------------------------------------------------------------------------
BYTE OEM_SkipMainServiceFunc(void)
{
    
    // Return :
    return(Normal_MainService);
}

//981004-211217-R-S
#if 0
void GPU_OC(BYTE NUM)
{	
	GPU_OC_NUM = NUM;
	
	switch(NUM)
	{
		case 0x00:     			
	        GPU_OC1 = 0; //GPIO D1
	        GPU_OC2 = 1; //GPIO D5
	        GPU_OC3 = 0; //GPIO E0
	        GPU_OC4 = 0; //GPIO E5
			  break;
			  
		case 0x01:     			
	        GPU_OC1 = 0; //GPIO D1
	        GPU_OC2 = 0; //GPIO D5
	        GPU_OC3 = 0; //GPIO E0
	        GPU_OC4 = 0; //GPIO E5
			  break;
  
        case 0x02:     			
	        GPU_OC1 = 1; //GPIO D1
	        GPU_OC2 = 0; //GPIO D5
	        GPU_OC3 = 0; //GPIO E0
	        GPU_OC4 = 0; //GPIO E5
			  break;   

		case 0x03:     			
	        GPU_OC1 = 0; //GPIO D1
	        GPU_OC2 = 0; //GPIO D5
	        GPU_OC3 = 1; //GPIO E0
	        GPU_OC4 = 0; //GPIO E5
			  break; 	   
	
	    case 0x04:     			
	        GPU_OC1 = 0; //GPIO D1
	        GPU_OC2 = 0; //GPIO D5
	        GPU_OC3 = 0; //GPIO E0
	        GPU_OC4 = 1; //GPIO E5
			  break; 
			  
		default:			           
		    GPU_OC1 = 0; //GPIO D1
	        GPU_OC2 = 1; //GPIO D5
	        GPU_OC3 = 0; //GPIO E0
	        GPU_OC4 = 0; //GPIO E5
			break;	  	
	}
}	
#endif
//981004-211217-R-E

void PD_Adapter_setting(void)
{
	 if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	 {
         WTDP = 20; 
	     WTDP2 = 20; 
         WTDP4 = 45; 
	 }
     else
     {
         WTDP = 20; 
		 WTDP2 = 20; 
         WTDP4 = 45;
     }		
}

uint8_t Check_PORT80(void)
{
		uint8_t led;
		uint8_t test_val[1] = {0x79};
		
	#if SUPPORT_DEBUG_CARD
				//Last_P81HDR = Port81_Get_Data();
				//Last_P80HDR = Port80_Get_Data();
			if((Last_P81HDR != Port81_Get_Data()) || (Last_P80HDR != Port80_Get_Data()))
			{

				/* Update TM1650 when debug code changed */
				Last_P81HDR = Port81_Get_Data();
				Last_P80HDR = Port80_Get_Data();
				led =(uint8_t)(Last_P80HDR<<4)|(Last_P80HDR>>4); //981004-200812-A
				I2C_SMBusModProtocol(4,SendByte,0x48,1,test_val,0);	 		
				I2C_WR_BUFFER[0] = LED7s_TABLE[led & 0x0F]; //981004-200812-M
				I2C_SMBusModProtocol(4,SendByte,0x68,1,I2C_WR_BUFFER,0);
				I2C_WR_BUFFER[0] = LED7s_TABLE[(led >> 4) & 0x0F]; //981004-200812-M
				I2C_SMBusModProtocol(4,SendByte,0x6A,1,I2C_WR_BUFFER,0);
				led = (uint8_t)(Last_P81HDR<<4)|(Last_P81HDR>>4); //981004-200812-A
				I2C_WR_BUFFER[0] = LED7s_TABLE[led & 0x0F]; //981004-200812-M		
				I2C_SMBusModProtocol(4,SendByte,0x6C,1,I2C_WR_BUFFER,0);
				I2C_WR_BUFFER[0] = LED7s_TABLE[(led >> 4) & 0x0F]; //981004-200812-M 		
				I2C_SMBusModProtocol(4,SendByte,0x6E,1,I2C_WR_BUFFER,0);
				
			}
		
		#endif
}

void EC_ACK_eSPI_SUS_WARN(void)
{
#if 0
    /* Use internal registers */
    if (IS_MASK_SET(REG_32A6, BIT3))
    {
        VWIDX40 |= (F_IDX40_VALID + F_IDX40_SUSACK);
        REG_32A6 = 0x0F;
    }
#else
    /* Use formal registers */
    if (IS_MASK_SET(ESPI->EVIDX41, IDX41_SUS_WARN) &&
        IS_MASK_SET(ESPI->EVIDX41, IDX41_SUS_WARN_VALID))
    {
        //ESPI->EVIDX40 |= (IDX40_SUSACK + IDX40_SUSACK_VALID);
		VW_Set_Index(0x40,IDX40_SUSACK + IDX40_SUSACK_VALID);
    }
    if (IS_MASK_CLEAR(ESPI->EVIDX41, IDX41_SUS_WARN) &&
        IS_MASK_SET(ESPI->EVIDX41, IDX41_SUS_WARN_VALID))
    {
       // ESPI->EVIDX40 &= ~(IDX40_SUSACK);
       // ESPI->EVIDX40 |= IDX40_SUSACK_VALID;
		VW_Set_Index(0x40,0x10);
    }
#endif
}

void EC_ACK_eSPI_Boot_Ready(void)
{
#if SUPPORT_EN_VW_ACK_BOOT_LOAD
    //if (IS_MASK_SET(REG_310F, F_VW_CHN_ENABLE))
    {
        //if (IS_MASK_SET(REG_310F, F_VW_CHN_READY))
		if(GetVWEnable)
        {
            // VWIDX5 = (F_IDX5_SLAVE_BOOT_LOAD_STATUS_VALID +
            //           F_IDX5_SLAVE_BOOT_LOAD_DONE_VALID +
            //           F_IDX5_SLAVE_BOOT_LOAD_STATUS +
            //           F_IDX5_SLAVE_BOOT_LOAD_DONE);
			VW_Set_Index(0x05,0x99);
        }
    }
#else    
    if (IS_MASK_SET(REG_3117, F_FLASH_CHN_ENABLE))
    {
        if (IS_MASK_SET(REG_3117, F_FLASH_CHN_READY))
        {            
            VWIDX5 = (F_IDX5_SLAVE_BOOT_LOAD_STATUS_VALID +
                      F_IDX5_SLAVE_BOOT_LOAD_DONE_VALID +
                      F_IDX5_SLAVE_BOOT_LOAD_STATUS +
                      F_IDX5_SLAVE_BOOT_LOAD_DONE);
        }
    }
#endif
}

void EC_ACK_eSPI_Reset(void)
{
    if (IS_MASK_SET(ESPI->EVIDX7 , IDX7_HOST_RST_WARN))
    {
        // VWIDX6 = (F_IDX6_HOST_RST_ACK_VALID +
        //           F_IDX6_HOST_RST_ACK +
        //           F_IDX6_RCIN +
        //           F_IDX6_SMI +
        //           F_IDX6_SCI);
		VW_Set_Index(0x06,0x7F);
        ITempW01 = 60000;
        while (IS_MASK_SET(ESPI->EVIDX7 , IDX7_HOST_RST_WARN))
        {
            ITempW01--;
#if 1   /* Timeout if need */
            if (ITempW01 == 0)
            {
                break;
            }
#endif
        }
        // VWIDX6 = (F_IDX6_HOST_RST_ACK_VALID +
        //           F_IDX6_RCIN +
        //           F_IDX6_SMI +
        //           F_IDX6_SCI);
		VW_Set_Index(0x06,0x77);
        //Hook_EC_ACK_eSPI_Reset();
    }
    if (IS_MASK_SET(ESPI->EVIDX3, IDX3_OOB_RST_WARN))
    {
        //ESPI->EVIDX4 |= (IDX3_OOB_RST_WARN_VALID + IDX3_OOB_RST_WARN);
		VW_Set_Index(0x04,0x11);
        ITempW01 = 60000;
        while (IS_MASK_SET(ESPI->EVIDX3, IDX3_OOB_RST_WARN))
        {
            ITempW01--;
#if 1   /* Timeout if need */
            if (ITempW01 == 0)
            {
                break;
            }
#endif
        }
        //ITempB01 = (VWIDX4 | F_IDX4_OOB_RST_ACK_VALID);
        //ITempB01 &= (~F_IDX4_OOB_RST_ACK_VALID);
        //VWIDX4 = ITempB01;  //(F_IDX4_OOB_RST_ACK_VALID);
    }
}

void service_eSPI_handshake(void)
{
    //-----------------------------------
    // eSPI Interface Control
    //-----------------------------------
    if (1)
    {
        // if (VWIDX5 == (F_IDX5_SLAVE_BOOT_LOAD_STATUS_VALID +
        //                 F_IDX5_SLAVE_BOOT_LOAD_DONE_VALID +
        //                 F_IDX5_SLAVE_BOOT_LOAD_STATUS +
        //                 F_IDX5_SLAVE_BOOT_LOAD_DONE))
		if(ESPI->EVTXDAT == 0x0599)
        {
            EC_ACK_eSPI_SUS_WARN();
            EC_ACK_eSPI_Reset();
#if SUPPORT_HOOK_WARMBOOT
            if (eSPI_PLTRST_TAG == F_PLTRST_DETECTED)
            {
                eSPI_PLTRST_TAG = F_PLTRST_HI_LEVEL;
                SystemWarmBoot();
            }
#endif
        }
        else
        {
            EC_ACK_eSPI_Boot_Ready();
        }
    }
}