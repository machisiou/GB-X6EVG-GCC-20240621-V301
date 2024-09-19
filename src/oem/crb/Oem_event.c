#include "RTK_Include.h"

const struct sDebounce Debounce_TBL[];


//-----------------------------------------------------------------------------
// no change function

//-----------------------------------------------------------------------------
void NullEvent(void)
{

}

//-----------------------------------------------------------------------------
// Adapter in function
//-----------------------------------------------------------------------------
void AdapterIn(void)
{
	#if 1
    BIT_SET(POWER_FLAG1, adapter_in); //201 BIT0
    BIT_SET(POWER_FLAG6, win_adapter_in); //206 BIT0 //981004-210224-A   
	//DoUSBCharge(); //981004-161226-R
	if (IS_BIT_CLR(EC_Flag4, old_99w)) //981004-230510-A
	{  
       BIT_SET(EC_Flag5, fix_ac_voltage); //389 BIT6 //981004-230510-A
	}
    PD_POWER_ON = 1; //GPIO J6 //981004-220112-M from 0
	//GPIO_Write(130,1);
	
	//981004-150722-A-S	
   // if (!BAT_IN_L) //GPIO B0, GPIO113
	if(!BAT_IN_L)
    {
	   //if (PD_ADAPTER_IN) //NO PD	 GPIO I7 GPIO081
       if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2)) //NO PD
       { 
	    //981004-180112-M-S
	    if (IS_BIT_CLR(POWER_FLAG12, bat_full))
        {
           BAT_OPTION = 0x4CF9; 
        }
        else
        {
           BAT_OPTION = 0x4DF9;
        }
        //981004-180112-M-E					
		//981004-150525-A-S Fix Battery no charge when shipmode wakeup.60.8w "Model : GAG-K40"
		if (IS_BIT_CLR(POWER_FLAG13, fixBattery))
		     ConfigCharger();
      }
	  else
	  {
         BAT_OPTION = 0x4DF9;
      }
     // bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); //981004-150615-M
		SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
		//ProcessCharge(); //981004-180702-R	 
    }
    else
    {               
		BAT_OPTION = 0x49F1; //981004-150525-A //Battery only setting + Inhibit charging
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); //981004-150429-A	
		SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);		
    }
    //981004-150722-A-E
	
	#if 1	
	//if (IS_BIT_CLR(POWER_FLAG1, power_on) && (SystemState == SYSTEM_S5)) //981004-150408-M
    if (IS_BIT_CLR(POWER_FLAG1, power_on) && (SystemState == SYSTEM_G3)) //981004-150408-M					
    {
	  //if ((PWRSW_L) && ((IS_BIT_CLR(POWER_FLAG1, wait_PSW_off)))) //981004-150408-A GPIO E4 GPIO112
	  //if ((PWRSW_L) && ((IS_BIT_CLR(POWER_FLAG1, wait_PSW_off))))
	  { 	   
			EC_EN_V5A = 1; //GPIO G6 GPIO122
			  //GPIO_Write(122,1);
		   //if (FUC_EN_L) //981004-180731-R
		   //{
	          EC_CLR_LATCH = 1; //GPIO J4 GPIO087
				//GPIO_Write(87,1);
		      _Delay_1ms(10);
		      EC_CLR_LATCH = 0;
				//GPIO_Write(87,0);
		   //}		
      }		
    } 	
    #endif
	
	//981004-210818-M-S
	#if 0
	if ((SystemIsS3) || (SystemIsS4))
	{
	   USB_V5A_EN = 1; //USB_PWR_EN //981004-210611-M from 0
       USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0 
	}
	#endif
	
	#if 0
	if (SystemIsS3)
	{
	   EC_S3_DDR5_EN = 1;
	   _Delay_1ms(1);	
	   USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0
       USB_EN_EC = 0; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0 
	}
	if (SystemIsS4)
	{	  
	  if (IS_BIT_CLR(POWER_FLAG9, rtc_wake_support)) //EC RAM 209 bit 4
      {	 	     		    
          USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0 
          USB_EN_EC = 0; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0        
      }
      else
      {	       
          USB_V5A_EN = 1; //USB_PWR_EN 
          USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7)
      }	  
	}
    #endif	
	//981004-210818-M-E
	
	//if (IS_BIT_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	if (IS_BIT_SET(POWER_FLAG2, sci_on) && (GetSlp_S3))
	{       
		//ECQEvent(SCI_ADAPTERIN, SCIMode_ACPI_SMBus); //0x60
		QeventSend(SCI_ADAPTERIN);
        BIT_SET(POWER_FLAG10, scion_ac_in);          		   
	}		
	
	_Delay_1ms(50);
    AC_PRESENT = 1;	//GPIO F5 GPIO097
	//GPIO_Write(97,1);
    BIT_SET(POWER_FLAG3, ac_present);
    BIT_SET(POWER_FLAG6, ac_to_dc);	 		
    BIT_CLR(POWER_FLAG4, bat30_on);     
    BIT_CLR(POWER_FLAG7, dgpu_9Aon); 
	BIT_CLR(POWER_FLAG4, pstate_off); 	   	
    AmpHigh_flag = 0x00; //981004-140505-A patch for Max request
    AmpHighcnt = 0x00;   //981004-140505-A patch for Max request
    //AmpHighRecovercnt = 0x00; //981004-180717-R
    BIT_CLR(POWER_FLAG10, gtx970_bat_low); //992022-140904-A
    BIT_CLR(POWER_FLAG8, D7_flag_for_bios); //992022-140905-A for BIOS to know and force keep in CPU P16 because smartcooling will let BIOS to become P8
	//if ((IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) && (IS_BIT_CLR(POWER_FLAG3, adapter_overtemp))) //EC RAM 0x211 bit3 //981004-210325-M
	if (((IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) && (IS_BIT_CLR(POWER_FLAG3, adapter_overtemp))) || ((IS_BIT_CLR(POWER_FLAG1, power_on) && (SystemState==SYSTEM_S5))))
    {
       if (NVDeventStatus3 == 0) //981004-221123-A
       {		
			NVDeventStatus = 0x01; //992022-140904-A
	   }
	   dGPU_HOLD_EC_RST_L = 0; //981004-200724-A GPIO H6 GPIO105
		//GPIO_Write(105,0);
	} 
    else
    {
       dGPU_HOLD_EC_RST_L = 1;
		//GPIO_Write(105,1);		
    }
	//981004-181107-M-E
	
    ProcsH_cnt = 0; //981004-131030-A for Processor Hot patch by Max request   
    if ((IS_BIT_CLR(ProcsH, ProcsH_scion20sec)))  //981004-210325-M patch for Max request
	{       
        H_PROCHOT_L = 0; //981004-210407-M from 1		GPIO A5 GPIO028
		//GPIO_Write(28,0);
        //WTDP4 = 30; //981004-210413-A 		
        //BIT_SET(ProcsH, ProcsH_acout); //981004-131210-S  from ADAPTEROUT //3A2 BIT0	 		
    }
    if(NVDeventStatus3==0)
    {
        QeventSend(SCI_NV_D3);
    }
      //BAT_INCURR = 0x0018; //4.096+1.024++0.512+0.256 = 5.888A (5.888*2 = 11.776A) //232.8Watt //981004-201027-M from 0x0018
	  BAT_INCURR = 0x0018; //4.096+1.024+0.512+0.128 = 5.76A (5.76*2 = 11.52A)
      //BAT_INCURR = 0x8016; //4.096+1.024+0.512+0.128 = 5.76A (5.76*2 = 11.52A) //981004-210322-M
    //981004-200130-M-S	
	   if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	   {
        if (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)) //981004-151204-A
	    {
            if (NVDeventStatus2 == 0) //981004-221123-A		   
	        {  		   
	            WTDP = 35;
		    }
           WTDP2 = 45;	
	       WTDP4 = 90; //0xD3 //981004-210407-R
	    }
       }    	
       else //i9 CPU
       {
        if (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)) //981004-151204-A
	    {
         if (NVDeventStatus2 == 0) //981004-221123-A		   
	     {  		   
		   WTDP = 35;
		 }
           WTDP2 = 45;	
	       WTDP4 = 90; //0xD3 //981004-210407-R
        }
	   }
       	//981004-220510-A-S
	//if (IS_MASK_CLEAR(EC_Flag4, old_99w)) //981004-230828-R
	//{
       BAT_CHGCURR = 0x0001; //0.256A
       //BAT_CHGVOL = 0x1030; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)
       BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V) //981004-230828-M from 0x1030	   
       //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, BAT_CHGCURR , SMBus_NoPEC);
	   //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, BAT_CHGVOL , SMBus_NoPEC);
       SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR);
       SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL);

	//}
    //981004-220510-A-E
		
	    CLEAR_MASK(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4 //981004-230510-A
	    CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2); 
	    SET_MASK(EC_Flag1, acin_chgcur); //981004-230602-A   
		if(IS_BIT_CLR(EC_Flag4, old_99w))  //981004-230510-A
		{
		   BAT_CHGCURR = 0x0001; //0.256A
		   BAT_CHGVOL = 0x1040; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)	
		   //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
		   //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Voltage,&BAT_CHGVOL);
		}	
	//981004-200923-A-S
	BIT_CLR(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4 //981004-230510-A
    BIT_CLR(POWER_FLAG8, pd_ac_over65w2); //EC RAM 0x211 bit4 //981004-230510-A
	BIT_SET(EC_Flag1, acin_chgcur);
	 if (IS_BIT_SET(EC_Flag4, old_99w)) //981004-230510-A
	 {	
		 
		//BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)	//981004-221011-A
		//BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
		BIT_CLR(EC_Flag2, pdchgcur_step1);
		BIT_CLR(EC_Flag2, pdchgcur_step2);
		BIT_CLR(EC_Flag2, pdchgcur_step3);
		BIT_CLR(EC_Flag2, pdchgcur_step4);
        BIT_CLR(EC_Flag2, pdchgcur_step5);
		CHGCUR_STEP_cnt2 = 0;
	 }
	 	//981004-230707-A-S
		BIT_CLR(EC_Flag6, PD_60W);
		BIT_CLR(EC_Flag6, PD_65W);
		BIT_CLR(EC_Flag6, PD_80W);
		BIT_CLR(EC_Flag6, PD_100W);
		//981004-230707-A-E
	//if (IS_BIT_CLR(POWER_FLAG12, bat_full))
	//{
	    //PD_POWER_ON = 1; //GPIO J6
    //}		
	
	#if 1
	//981004-210118-A-S
	//if (!PD_ADAPTER_IN) //Low active
	if (!PD_ADAPTER_IN) //Low active	
    { 
	    PD_POWER_ON = 1; //981004-220112-M from 0	
		//GPIO_Write(130,1);
        BIT_SET(POWER_FLAG11, dual_ac);		    
		BAT_OPTION = 0x4DF9;
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
		SMBUS_RW_W(0,WriteWord, Charger_Addr,CHGCmd_Option,&BAT_OPTION);
		if (IS_BIT_SET(POWER_FLAG11, check_pd_ac_chg)) //EC RAM 0x211 bit3  
        {		                 
			BIT_CLR(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
			pd_ac_in_cnt = 0;	
	    }		  
	}
    if (!PD_ADAPTER_IN2) //Low active
	{
		PD_POWER_ON = 1; //981004-220112-M from 0	
        SET_MASK(POWER_FLAG11, dual_ac);		    
		BAT_OPTION = 0x4DF9;
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);
		if (IS_MASK_SET(POWER_FLAG8, check_pd_ac_chg2)) //EC RAM 0x208 bit0  
        {		                 
			CLEAR_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x208 bit0
			pd_ac_in_cnt2 = 0;	
	    }	
	}
    if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2))
    {
        PD_POWER_ON = 1;
		//GPIO_Write(130,1);
    }
	//BIT_CLR(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6
    #endif	
	 //981004-210118-A-E
	 
	 //981004-210407-A-S
	 ProcsH_cnt =0;
	 BIT_CLR(ProcsH, ProcsH_acout);
	 //981004-210407-A-E
	 #endif
	//981004-221228-A-S
	BIT_CLR(EC_Flag4, nv_db20_lv0); 
    BIT_CLR(EC_Flag4, nv_db20_lv1); 
    BIT_CLR(EC_Flag4, nv_db20_lv2);
    BIT_CLR(EC_Flag4, nv_db20_lv3);
	BIT_CLR(EC_Flag4, nv_db20_lv4);
	CHG_TEMP6 = 0; //981004-230925-A
	CHG_TEMP7 = 0; //981004-230925-A
   //981004-221228-A-E
    BIT_CLR(POWER_FLAG1, dp_attached); //981004-231116-A
    pd_ac_in_cnt = 0;
    pd_ac_in_cnt2 = 0;	
	xTIPD1_pd_watt = 0;
	xTIPD1_pd_watt2 = 0;
	CLEAR_MASK(EC_Flag7, PD_COMPARE); //EC RAM 0x339 bit1
	CLEAR_MASK(EC_Flag7, PD1_CHARGE); //EC RAM 0x339 bit2
	CLEAR_MASK(EC_Flag7, PD2_CHARGE); //EC RAM 0x339 bit3 
}

//-----------------------------------------------------------------------------
// Adapter out function
//-----------------------------------------------------------------------------
void AdapterOut(void)
{
	#if 1
    BIT_CLR(POWER_FLAG1, adapter_in);
	BIT_CLR(POWER_FLAG6, win_adapter_in); //206 BIT0 //981004-210224-A 
    BIT_CLR(POWER_FLAG3, adapter_overtemp); //981004-210325-A	
	BIT_CLR(EC_Flag5, fix_ac_voltage); //389 BIT6 //981004-220510-A
    //981004-200724-A-E	
	
    //ProcessDischarge();
	
	//981004-150722-A-S for BQ24780 battery only setting +Inhibit charging		
    BAT_OPTION = 0x49F1;
	//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); //981004-150429-A
	SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
	//981004-150722-A-E
	 

   // if ((IS_BIT_SET(POWER_FLAG1, enter_S4)) && (IS_BIT_CLR(POWER_FLAG5, bios_cf9))) 
	
    //981004-210818-M-S
    #if 0
	if (SystemIsS3)
	{
	   EC_S3_DDR5_EN = 1;
	   _Delay_1ms(1);	
	   USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0
       USB_EN_EC = 0; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0 
	}
	if (SystemIsS4)
	{	  
	  if (IS_BIT_CLR(POWER_FLAG9, rtc_wake_support)) //EC RAM 209 bit 4
      {	 	     		    
          USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0
          USB_EN_EC = 0; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0        
      }
      else
      {	       
          USB_V5A_EN = 1; //USB_PWR_EN 
          USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7)
      }	  
	}
    #endif
    //981004-210818-M-E 
	  if (NVDeventStatus2 == 0)	//981004-221123-A	   
	  { 	
		WTDP = 15;
	  }
      WTDP2 = 45;		
       //WTDP4 = 90; //981004-210407-R 
	

    //981004-210224-A-A	
	if (IS_BIT_SET(POWER_FLAG2, sci_on) && (GetSlp_S3))  //in Win OS and S0
    {       
		//ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus); //0X61
		QeventSend(SCI_ADAPTEROUT);
		
	}

    //__Delay_1ms(50);
	_Delay_1ms(50);
    AC_PRESENT = 0;
	//GPIO_Write(97,1);
    //981004-210224-A-E
	
	//981004-210118-A-S
	#if 1
	if (!PD_ADAPTER_IN) //Low active	   
    {
        H_PROCHOT_L = 0; //981004-210407-M from 0
        dGPU_HOLD_EC_RST_L = 1;
        WTDP4 = 90; //981004-210413-A		
	    BAT_OPTION = 0x4DF9;
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
		SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);		
        //Enable_pd_adapter();
        //BIT_SET(POWER_FLAG3, enable_pd_ac); //EC RAM 0x203 bit1		
		BIT_SET(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
		//BIT_SET(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6
		ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		PD_Adapter_setting();
	    //BIT_CLR(POWER_FLAG10, scion_ac_in); 
        SCI_on_AC_in_cnt = 0;
       //BIT_SET(POWER_FLAG1, adapter_in); //201 BIT0	   
       //AC_PRESENT = 1;
       patchACout = 0; //981004-211021-A
       Fullchgcnt =0; //981004-211021-A   	   
	}
    if (!PD_ADAPTER_IN2) //Low active	   
    {
        H_PROCHOT_L = 0; //981004-220224-M from 1 
        dGPU_HOLD_EC_RST_L = 1;
        WTDP4 = 90; //981004-220929-M from 15		
	    BAT_OPTION = 0x4DF9;
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);				
		SET_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x208 bit3
		ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		PD_Adapter_setting(); 
        SCI_on_AC_in_cnt = 0;
        patchACout = 0; 
        Fullchgcnt =0;   	   
	}
	if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2))
	{
	   if (IS_BIT_SET(POWER_FLAG2, sci_on) && (GetSlp_S3))  //in Win OS and S0
       {        
          if (IS_BIT_CLR(ProcsH, ProcsH_scion20sec)) //992022-140218-A patch for Max request
          {       
            H_PROCHOT_L = 0; //981004-210407-M from 0
            WTDP4 = 30; //981004-210413-A 			
            BIT_SET(ProcsH, ProcsH_acout); //992022-140218-A patch for Max request 
          }			
      }
	  if (IS_BIT_SET(POWER_FLAG2, sci_on) && (GetSlp_S3))  //in Win OS and S0
	  {
		if (IS_BIT_CLR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
        {			  
            ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA 
		}			
	  }
        dGPU_HOLD_EC_RST_L = 1;
		BIT_CLR(EC_Flag4, nv_db20_lv0); //981004-221228-A
        BIT_CLR(EC_Flag4, nv_db20_lv1); 
        BIT_CLR(EC_Flag4, nv_db20_lv2);
        BIT_CLR(EC_Flag4, nv_db20_lv3);
	    BIT_CLR(EC_Flag4, nv_db20_lv4);
	   //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
       //BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt //981004-210322-M	
       //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )	   
        if (IS_BIT_CLR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
       {
           if (NVDeventStatus3 == 0) //981004-221130-A
           {			   
               NVDeventStatus = 0x0A;
           }			   
       }
       else
       {
		   //NV_DB20_SUPPORT(); //981004-221025-A
	   }       
       //_Delay_1ms(50); //981004-210224-R
       //AC_PRESENT = 0; //981004-210224-R	   
    }
    #endif	
    //981004-210118-A-E	
		
	BAT_INCURR = 0x8000; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008
	
	BIT_CLR(POWER_FLAG3, ac_present);				
	//ECQEvent(SCI_P0, SCIMode_ACPI_SMBus); //0xA0 //981004-200410-R	
    BIT_CLR(POWER_FLAG10, scion_ac_in); //992022-140904-A
    SCI_on_AC_in_cnt = 0; //992022-140904-A
	AC_vol_cnt = 0; //981004-220510-A
	AC_boost_Status = 0; //981004-151008-A
	AC_boost_cnt1 = 0; //981004-151001-A
	AC_boost_cnt2 = 0; //981004-151001-A	
	BAT100CNT = 0;    
    BIT_CLR(POWER_FLAG4, bat_cap_first_chk); //981004-170412-A
	BIT_CLR(POWER_FLAG4, bat_cap_downgrade); //981004-170412-A
    BAT_FIRST_CHK_cnt = 0; //981004-170412-A
    BAT_DOWNGRADE_cnt = 0; //981004-170412-A
    BAT_FIRST_CHK2_cnt = 0; //981004-170717-A
	//BIT_CLR(POWER_FLAG5, bat_cap_first_chk2); //981004-181107-R	
    BIT_CLR(POWER_FLAG6, sv_thrt_on); //981004-190329-A
	//981004-200923-A-S
	BIT_CLR(EC_Flag1, acin_chgcur);
	BIT_CLR(EC_Flag1, chgcur_step1);
	BIT_CLR(EC_Flag1, chgcur_step2);
	BIT_CLR(EC_Flag1, chgcur_step3);
	BIT_CLR(EC_Flag1, chgcur_step4);
	BIT_CLR(EC_Flag1, chgcur_step5); //981004-220811-A for 1C charge
	CHGCUR_STEP_cnt = 0;
	PD_POWER_ON = 0; //GPIO J6
	//GPIO_Write(130,1);
	if (IS_BIT_SET(EC_Flag4, old_99w)) //981004-230510-A
	{
	   //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
       BAT_CHGCURR = 0x0001;
	}
	//981004-200923-A-E
    if (IS_BIT_CLR(EC_Flag4, old_99w)) //981004-220510-A
	{
	   BAT_CHGCURR = 0x0001; //0.256A
       //BAT_CHGVOL = 0x1030; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)
	   BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V) //981004-230828-M from 0x1030
	}    
    
    #if  0	
	if (RMCAP_TEMP <= BATCAP20)
    {
		BIT_SET(POWER_FLAG10, gtx970_bat_low);
	}
    #endif

    PWR_LED2_L = 1; 
	BIT_CLR(EC_Flag5, BAT_1C_CHG); //EC RAM 0x389 bit6 //981004-220419-A
	
	//981004-230116-A-S
	ThrottlingCnt6_2 = 0;
	BIT_CLR(GPU_HOT2, NCT_TR3_FAST_CHG); //0x34C bit6
	FAST_CHG_CNT1 = 0; //981004-230925-A
	FAST_CHG_CNT2 = 0; //981004-230925-A
	CHG_TEMP1 = 0; //981004-230925-A
	CHG_TEMP2 = 0; //981004-230925-A
	CHG_TEMP3 = 0; //981004-230925-A
	//981004-230116-A-E 
	BIT_CLR(POWER_FLAG1, dp_attached);
}	
//981004-210118-A-S
//-----------------------------------------------------------------------------
// PD Adapter in function
//-----------------------------------------------------------------------------
void PD_ACIn(void)
{	
    BIT_SET(POWER_FLAG11, pd_adapter_in); //211 BIT0    			
	#if 0
	if (!BAT_IN_L) 
    {
	  //if (AC_IN_L)	  	   
      {  
	    if (IS_BIT_CLR(POWER_FLAG12, bat_full))
        {
           BAT_OPTION = 0x4CF9; 
        }
        else
        {
           BAT_OPTION = 0x4DF9;
        }
        	
		bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); //981004-150615-M			
		if (IS_BIT_CLR(POWER_FLAG13, fixBattery))
		     ConfigCharger();
     }	  			 
   }
   else
   {               
		BAT_OPTION = 0x49F1; //981004-150525-A //Battery only setting + Inhibit charging
		bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        Disable_pd_adapter(); 		
   }
   #endif
   //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
   //BAT_OPTION = 0x4DF9;
   //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); 
   //bRWSMBus(SMbusCh1, SMbusRW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
   if (AC_IN_L)
   {
      BAT_OPTION = 0x4DF9;
      //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);	   
      SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION );
	   #if 0   
	  if (IS_BIT_CLR(POWER_FLAG1, power_on) && (SystemIsS4)) 				
      {
	   if ((PWRSW_L) && ((IS_BIT_CLR(POWER_FLAG1, wait_PSW_off)))) 
	   { 	   
           EC_EN_V5A = 1;		  
	       EC_CLR_LATCH = 1;
		   _Delay_1ms(10);
		   EC_CLR_LATCH = 0;
           BIT_SET(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3	
           pd_ac_in_cnt = 1;		   
           //Enable_pd_adapter();
		   //BIT_SET(POWER_FLAG3, enable_pd_ac); //EC RAM 0x203 bit1		            	   
       }		
     }
	 #endif
	 //else if (IS_BIT_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	 //else
	 //{
        if (IS_BIT_SET(POWER_FLAG2, sci_on) && (GetSlp_S3))  //in Win OS and S0
        {		
		    //ECQEvent(SCI_PD_ACIN, SCIMode_ACPI_SMBus); //0x90
			//ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
			QeventSend(SCI_NV_DB);
		}
        //Enable_pd_adapter();
        //BIT_SET(POWER_FLAG3, enable_pd_ac); //EC RAM 0x203 bit1		
	 //}
	  
     PD_Adapter_setting();	
	 BIT_SET(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3 
	 //SCI_on_AC_in_cnt = 0;  
		 
	 
	  		
     BIT_CLR(POWER_FLAG4, bat30_on);     
     BIT_CLR(POWER_FLAG7, dgpu_9Aon); 
	 BIT_CLR(POWER_FLAG4, pstate_off); 	   	
     AmpHigh_flag = 0x00; 
     AmpHighcnt = 0x00;      
     BIT_CLR(POWER_FLAG10, gtx970_bat_low); 
     BIT_CLR(POWER_FLAG8, D7_flag_for_bios);     
	 //GPIO_Write(105,1);
     dGPU_HOLD_EC_RST_L = 1;
     //GPIO_Write(28,1);
     H_PROCHOT_L = 0; //981004-210407-M from 0
     //WTDP4 = 20; //981004-210407-A 	 
     ProcsH_cnt = 0;     	  
	 //BIT_SET(POWER_FLAG11, pdacin_chgcur);
     if (IS_BIT_SET(EC_Flag4, old_99w)) //981004-230510-A
	 {
	    //BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)	//981004-221011-A
	    //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
        BAT_CHGCURR = 0x0001;
	 }
	 else
	 {
	     BAT_CHGCURR = 0x0001; //0.256A	
         //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
		 SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
	 }
     BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V) //981004-230828-A	
   }
   else
   {	  
	    BIT_CLR(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4 //981004-210118-A
        //BIT_CLR(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7 //981004-230718-A	
        //Disable_pd_adapter();		//Raymond this function will implement in PD_UPDATE	
        //981004-230707-A-S
	    BIT_CLR(EC_Flag6, PD_60W);
	    BIT_CLR(EC_Flag6, PD_65W);
	    BIT_CLR(EC_Flag6, PD_80W);
	    BIT_CLR(EC_Flag6, PD_100W);
	    //981004-230707-A-E		
   }
   
   //981004-210407-A-S
   ProcsH_cnt =0;
   BIT_CLR(ProcsH, ProcsH_acout);
   //981004-210407-A-E 
   patchACout = 0; //981004-211021-A
   Fullchgcnt =0; //981004-211021-A   
}

//-----------------------------------------------------------------------------
// Dual Adapter out function
//-----------------------------------------------------------------------------
void PD_ACOut(void)
{	
    BIT_CLR(POWER_FLAG11, pd_adapter_in); //211 BIT0
	BIT_CLR(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
	//BIT_CLR(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6
	pd_ac_in_cnt = 0;    	
    BIT_CLR(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4 //981004-210118-A
	//BIT_CLR(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7	//981004-211021-A
    BIT_CLR(EC_Flag2, pdchgcur_step1);
	BIT_CLR(EC_Flag2, pdchgcur_step2);
	BIT_CLR(EC_Flag2, pdchgcur_step3);
	BIT_CLR(EC_Flag2, pdchgcur_step4);
    BIT_CLR(EC_Flag2, pdchgcur_step5);
	CHGCUR_STEP_cnt2 = 0;
	//981004-230707-A-S
	BIT_CLR(EC_Flag6, PD_60W);
	BIT_CLR(EC_Flag6, PD_65W);
	BIT_CLR(EC_Flag6, PD_80W);
	BIT_CLR(EC_Flag6, PD_100W);
	//981004-230707-A-E
    BIT_CLR(POWER_FLAG11, dual_ac); //EC RAM 0x211 bit5			  
	dual_ac_cnt = 0;	
		if (AC_IN_L)
    {
	  if (!PD_ADAPTER_IN2) //Low active	   
      {
        H_PROCHOT_L = 0; //981004-220224-M from 1 
        dGPU_HOLD_EC_RST_L = 1;
        WTDP4 = 90; //981004-220929-M from 15		
	    BAT_OPTION = 0x4DF9;
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION );				
		SET_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x208 bit3
		ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		PD_Adapter_setting(); 
        SCI_on_AC_in_cnt = 0;
        patchACout = 0; 
        Fullchgcnt =0;   	   
	  }
      else
      {		  
		BAT_OPTION = 0x49F1;
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);		
		if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
        {        
           if (IS_MASK_CLEAR(ProcsH, ProcsH_scion20sec)) //992022-140218-A patch for Max request
           {       
             H_PROCHOT_L = 0; //dCPU
             //WTDP4 = 15; //981004-221005-M	 
             SET_MASK(ProcsH, ProcsH_acout); 
           }			
        }
		
        dGPU_HOLD_EC_RST_L = 1; //dGPU 	       	    	    
		//ProcessDischarge(); //981004-221005-R
		BAT_OPTION = 0x4DF9;
       // bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
       SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION );
		Disable_pd_adapter();
		#if 0
		if (SystemIsS3)
	    {
		   EC_S3_DDR5_EN = 1;
	       Delay1MS(1);	
	       USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0
           USB_EN_EC = 0; //Cut Standard USB port power (GPIO F7)//981004-210611-M from 0 
	    }
	    if (SystemIsS4)
	    {	  
	       if (IS_MASK_CLEAR(POWER_FLAG9, rtc_wake_support)) //EC RAM 209 bit 4
           {	 	     		    
              USB_V5A_EN = 1; //USB_PWR_EN //981004-210611-M from 0 
              USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0        
           }
           else
           {	       
              USB_V5A_EN = 1; //USB_PWR_EN 
              USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7)
           }	  
	    }		
	    #endif
	CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
    CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
    CLEAR_MASK(EC_Flag4, nv_db20_lv2);
    CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	CLEAR_MASK(EC_Flag4, nv_db20_lv4);	
	if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
    {	
       if (NVDeventStatus3 == 0) //981004-221123-A
       {		
           NVDeventStatus = 0x0A;
       }		   
    }
    else
    {
		NV_DB20_SUPPORT(); //981004-221025-A
	}		
    
    if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	{
        //H_PROCHOT_L = 1;
		//ECQEvent(SCI_PD_ACOUT, SCIMode_ACPI_SMBus); //0X91 //981004-210224-R
		if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
        {	
             ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA
        }			 
	}
	
    //981004-221005-A-S	
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
    //981004-221005-A-E
		
	//Delay1MS(50);
    //AC_PRESENT = 0;
	
	//CLEAR_MASK(POWER_FLAG3, ac_present);						
    CLEAR_MASK(POWER_FLAG10, scion_ac_in); //992022-140904-A
	//CLEAR_MASK(POWER_FLAG6, dual_ac_out); //EC RAM 0x206 bit2 //981004-201224-A	
    SCI_on_AC_in_cnt = 0; //992022-140904-A
	AC_boost_Status = 0; //981004-151008-A
	AC_boost_cnt1 = 0; //981004-151001-A
	AC_boost_cnt2 = 0; //981004-151001-A	
	BAT100CNT = 0;    
    CLEAR_MASK(POWER_FLAG4, bat_cap_first_chk); //981004-170412-A
	CLEAR_MASK(POWER_FLAG4, bat_cap_downgrade); //981004-170412-A
    BAT_FIRST_CHK_cnt = 0; //981004-170412-A
    BAT_DOWNGRADE_cnt = 0; //981004-170412-A
    BAT_FIRST_CHK2_cnt = 0; //981004-170717-A
	//CLEAR_MASK(POWER_FLAG5, bat_cap_first_chk2); //981004-181107-R	
    CLEAR_MASK(POWER_FLAG6, sv_thrt_on); //981004-190329-A
	//981004-200923-A-S
	//CLEAR_MASK(EC_Flag2, pdacin_chgcur);	
	CHGCUR_STEP_cnt2 = 0;	
	//BAT_CHGCURR = 0x0004; //0.512+0.128 = 0.64A (Target : 0.637A )
	//BAT_INCURR = 0x0004; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008
	//BAT_INCURR = 0x8002;  //981004-230731-M from 0x0004
	if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	{
 	   //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
	   BAT_CHGCURR = 0x0001; //0.256A //981004-230828-M from 0x8002
	}
	else
	{
	   	BAT_CHGCURR = 0x0001; //0.256A
        //BAT_CHGVOL = 0x1030; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)
	} 
    BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V) //981004-230828-A	
	//CLEAR_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
    //981004-210224-A-S
	CLEAR_MASK(POWER_FLAG1, adapter_in);
	ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus); //0X61
	Delay1MS(50);				  
    AC_PRESENT = 0;
	CLEAR_MASK(EC_Flag7, PD2_CHARGE); //EC RAM 0x339 bit3
    //981004-210224-A-E
	  }
	}
    else
    {
		BAT_OPTION = 0x4DF9;
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);
		Disable_pd_adapter();
		//SET_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
        //981004-210224-A-S
		SET_MASK(POWER_FLAG1, adapter_in); //201 BIT0
		ECQEvent(SCI_ADAPTERIN, SCIMode_ACPI_SMBus); //0x60
		Delay1MS(50);				  
        AC_PRESENT = 1;
        //981004-210224-A-E
	}	
    
 	//AC_PRESENT = 0;
    CLEAR_MASK(EC_Flag5, BAT_1C_CHG); //EC RAM 0x389 bit6 //981004-220419-A	
	FAST_CHG_CNT1 = 0; //981004-230925-A
	FAST_CHG_CNT2 = 0; //981004-230925-A
	CHG_TEMP1 = 0; //981004-230925-A
	CHG_TEMP2 = 0; //981004-230925-A
	CHG_TEMP3 = 0; //981004-230925-A
	CHG_TEMP6 = 0; //981004-230925-A
	CHG_TEMP7 = 0; //981004-230925-A
	CLEAR_MASK(POWER_FLAG1, dp_attached); //981004-231116-A
	xTIPD1_pd_mV = 0;
    xTIPD1_pd_mA = 0;
	xTIPD1_pd_watt = 0;
	CLEAR_MASK(EC_Flag7, PD_COMPARE); //EC RAM 0x339 bit1
	CLEAR_MASK(EC_Flag7, PD1_CHARGE); //EC RAM 0x339 bit2
}
//981004-210118-A-E

//-----------------------------------------------------------------------------
// PD Adapter in function
//-----------------------------------------------------------------------------
void PD_ACIn2(void)
{	
    SET_MASK(POWER_FLAG8, pd_adapter_in2); //211 BIT0    			
	#if 0
	if (!BAT_IN_L) 
    {
	  if (AC_IN_L)	  	   
      {  
	    if (IS_MASK_CLEAR(POWER_FLAG12, bat_full))
        {
           BAT_OPTION = 0x4CF9; 
        }
        else
        {
           BAT_OPTION = 0x4DF9;
        }
        	
		bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); //981004-150615-M			
		if (IS_MASK_CLEAR(POWER_FLAG13, fixBattery))
		     ConfigCharger();
     }	  			 
   }
   else
   {               
		BAT_OPTION = 0x49F1; //981004-150525-A //Battery only setting + Inhibit charging
		bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        Disable_pd_adapter(); 		
   }
   #endif
   //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
   //BAT_OPTION = 0x4DF9;
   //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); 
   //bRWSMBus(SMbusCh1, SMbusRW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
   if (AC_IN_L)
   {
      BAT_OPTION = 0x4DF9;
      //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
      SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);	   
      #if 0   
	  if (IS_MASK_CLEAR(POWER_FLAG1, power_on) && (SystemIsS4)) 				
      {
	   if ((PWRSW_L) && ((IS_MASK_CLEAR(POWER_FLAG1, wait_PSW_off)))) 
	   { 	   
           EC_EN_V5A = 1;		  
	       EC_CLR_LATCH = 1;
		   Delay1MS(10);
		   EC_CLR_LATCH = 0;
           SET_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x211 bit3	
           pd_ac_in_cnt = 1;		   
           //Enable_pd_adapter();
		   //SET_MASK(POWER_FLAG3, enable_pd_ac); //EC RAM 0x203 bit1		            	   
       }		
     }
	 #endif
	 //else if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	 //else
	 //{
        if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
        {		
		    //ECQEvent(SCI_PD_ACIN, SCIMode_ACPI_SMBus); //0x90
			ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		}
        //Enable_pd_adapter();
        //SET_MASK(POWER_FLAG3, enable_pd_ac); //EC RAM 0x203 bit1		
	 //}
	  
     PD_Adapter_setting();	
	 SET_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x211 bit3 
	 //SCI_on_AC_in_cnt = 0;  
		 
	 
	  		
     CLEAR_MASK(POWER_FLAG4, bat30_on);     
     CLEAR_MASK(POWER_FLAG7, dgpu_9Aon); 
	 CLEAR_MASK(POWER_FLAG4, pstate_off); 	   	
     AmpHigh_flag = 0x00; 
     AmpHighcnt = 0x00;      
     CLEAR_MASK(POWER_FLAG10, gtx970_bat_low); 
     CLEAR_MASK(POWER_FLAG8, D7_flag_for_bios);     
	 dGPU_HOLD_EC_RST_L = 1;
     H_PROCHOT_L = 0; //981004-220224-M from 1
     //WTDP4 = 15; //981004-220302-R	 
     ProcsH_cnt = 0;     	  
	 //SET_MASK(POWER_FLAG11, pdacin_chgcur);
     if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	 {
	    //BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)	//981004-221011-A
	    //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
		BAT_CHGCURR = 0x0001; //0.256A //981004-230828-M from 0x8002
	 }
	 else
	 {
	     BAT_CHGCURR = 0x0001; //0.256A	
         //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
         SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR);
	 }
     BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V) //981004-230828-A	 
   }
   else
   {	  
	    CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2); //EC RAM 0x211 bit4 //981004-210118-A        		
        //CLEAR_MASK(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7 //981004-231002-A	
        Disable_pd_adapter();
        //981004-230707-A-S
	    CLEAR_MASK(EC_Flag6, PD_60W);
	    CLEAR_MASK(EC_Flag6, PD_65W);
	    CLEAR_MASK(EC_Flag6, PD_80W);
	    CLEAR_MASK(EC_Flag6, PD_100W);
	    //981004-230707-A-E		
   }
   
   //981004-210407-A-S
   ProcsH_cnt =0;
   CLEAR_MASK(ProcsH, ProcsH_acout);
   //981004-210407-A-E 
   patchACout = 0; //981004-211021-A
   Fullchgcnt =0; //981004-211021-A   
}

//-----------------------------------------------------------------------------
// Dual Adapter out function
//-----------------------------------------------------------------------------
void PD_ACOut2(void)
{	
    CLEAR_MASK(POWER_FLAG8, pd_adapter_in2); //211 BIT0
	CLEAR_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x211 bit3
	//CLEAR_MASK(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6
	pd_ac_in_cnt2 = 0;    	
    CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2); //EC RAM 0x211 bit4 //981004-210118-A
	//CLEAR_MASK(POWER_FLAG11, pd_chargable); //EC RAM 0x211 bit7	//981004-211021-A
    CLEAR_MASK(EC_Flag2, pdchgcur_step1);
	CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	CLEAR_MASK(EC_Flag2, pdchgcur_step4);
	CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230828-A
	CHGCUR_STEP_cnt2 = 0;
	//981004-230707-A-S
	CLEAR_MASK(EC_Flag6, PD_60W);
	CLEAR_MASK(EC_Flag6, PD_65W);
	CLEAR_MASK(EC_Flag6, PD_80W);
	CLEAR_MASK(EC_Flag6, PD_100W);
	//981004-230707-A-E
    CLEAR_MASK(POWER_FLAG11, dual_ac2); //EC RAM 0x211 bit5			  
	dual_ac_cnt = 0;	
	if (AC_IN_L)
    {
	  if (!PD_ADAPTER_IN) //Low active	   
      {
        H_PROCHOT_L = 0; //981004-220224-M from 1 
        dGPU_HOLD_EC_RST_L = 1;
        WTDP4 = 90; //981004-220929-M from 15		
	    BAT_OPTION = 0x4DF9;
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION);		
        //Enable_pd_adapter();
        //SET_MASK(POWER_FLAG3, enable_pd_ac); //EC RAM 0x203 bit1		
		SET_MASK(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
		//SET_MASK(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6
		ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
		PD_Adapter_setting();
	    //CLEAR_MASK(POWER_FLAG10, scion_ac_in); 
        SCI_on_AC_in_cnt = 0;
       //SET_MASK(POWER_FLAG1, adapter_in); //201 BIT0	   
       //AC_PRESENT = 1;
       patchACout = 0; //981004-211021-A
       Fullchgcnt =0; //981004-211021-A   	   
	 }
	 else
     {		 
		BAT_OPTION = 0x49F1;
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION );		
		if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
        {        
           if (IS_MASK_CLEAR(ProcsH, ProcsH_scion20sec)) //992022-140218-A patch for Max request
           {       
             H_PROCHOT_L = 0; //dCPU
             //WTDP4 = 15; //981004-221005-M	 
             SET_MASK(ProcsH, ProcsH_acout); 
           }			
        }
		
        dGPU_HOLD_EC_RST_L = 1; //dGPU 	       	    	    
		//ProcessDischarge(); //981004-221005-R
		BAT_OPTION = 0x4DF9;
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION); 
		Disable_pd_adapter();
		#if 0
		if (SystemIsS3)
	    {
		   EC_S3_DDR5_EN = 1;
	       Delay1MS(1);	
	       USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0
           USB_EN_EC = 0; //Cut Standard USB port power (GPIO F7)//981004-210611-M from 0 
	    }
	    if (SystemIsS4)
	    {	  
	       if (IS_MASK_CLEAR(POWER_FLAG9, rtc_wake_support)) //EC RAM 209 bit 4
           {	 	     		    
              USB_V5A_EN = 1; //USB_PWR_EN //981004-210611-M from 0 
              USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7) //981004-210611-M from 0        
           }
           else
           {	       
              USB_V5A_EN = 1; //USB_PWR_EN 
              USB_EN_EC = 1; //Cut Standard USB port power (GPIO F7)
           }	  
	    }		
	    #endif
	CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
    CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
    CLEAR_MASK(EC_Flag4, nv_db20_lv2);
    CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	CLEAR_MASK(EC_Flag4, nv_db20_lv4);	
	if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
    {	
       if (NVDeventStatus3 == 0) //981004-221123-A
       {		
           NVDeventStatus = 0x0A;
       }		   
    }
    else
    {
		NV_DB20_SUPPORT(); //981004-221025-A
	}		
    
    if (IS_MASK_SET(POWER_FLAG2, sci_on) && (SLP_S3_L))  //in Win OS and S0
	{
        //H_PROCHOT_L = 1;
		//ECQEvent(SCI_PD_ACOUT, SCIMode_ACPI_SMBus); //0X91 //981004-210224-R
		if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
        {	
             ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA
        }			 
	}
	
    //981004-221005-A-S	
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
    //981004-221005-A-E
		
	//Delay1MS(50);
    //AC_PRESENT = 0;
	
	//CLEAR_MASK(POWER_FLAG3, ac_present);						
    CLEAR_MASK(POWER_FLAG10, scion_ac_in); //992022-140904-A
	//CLEAR_MASK(POWER_FLAG6, dual_ac_out); //EC RAM 0x206 bit2 //981004-201224-A	
    SCI_on_AC_in_cnt = 0; //992022-140904-A
	AC_boost_Status = 0; //981004-151008-A
	AC_boost_cnt1 = 0; //981004-151001-A
	AC_boost_cnt2 = 0; //981004-151001-A	
	BAT100CNT = 0;    
    CLEAR_MASK(POWER_FLAG4, bat_cap_first_chk); //981004-170412-A
	CLEAR_MASK(POWER_FLAG4, bat_cap_downgrade); //981004-170412-A
    BAT_FIRST_CHK_cnt = 0; //981004-170412-A
    BAT_DOWNGRADE_cnt = 0; //981004-170412-A
    BAT_FIRST_CHK2_cnt = 0; //981004-170717-A
	//CLEAR_MASK(POWER_FLAG5, bat_cap_first_chk2); //981004-181107-R	
    CLEAR_MASK(POWER_FLAG6, sv_thrt_on); //981004-190329-A
	//981004-200923-A-S
	//CLEAR_MASK(EC_Flag2, pdacin_chgcur);	
	CHGCUR_STEP_cnt2 = 0;	
	//BAT_CHGCURR = 0x0004; //0.512+0.128 = 0.64A (Target : 0.637A )
	//BAT_INCURR = 0x0004; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008
	//BAT_INCURR = 0x8002;  //981004-230731-M from 0x0004
	if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	{
 	   //BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
	   BAT_CHGCURR = 0x0001; //0.256A //981004-230828-M from 0x8002
	}
	else
	{
	   	BAT_CHGCURR = 0x0001; //0.256A
        //BAT_CHGVOL = 0x1030; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)
	} 
    BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V) //981004-230828-A	
	//CLEAR_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
    //981004-210224-A-S
	CLEAR_MASK(POWER_FLAG1, adapter_in);
	ECQEvent(SCI_ADAPTEROUT, SCIMode_ACPI_SMBus); //0X61
	Delay1MS(50);				  
    AC_PRESENT = 0;
	CLEAR_MASK(EC_Flag7, PD1_CHARGE); //EC RAM 0x339 bit2
    //981004-210224-A-E
	 }
	}
    else
    {
		BAT_OPTION = 0x4DF9;
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
        SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION); 
		Disable_pd_adapter();
		//SET_MASK(POWER_FLAG6, win_adapter_in); //206 BIT0
        //981004-210224-A-S
		SET_MASK(POWER_FLAG1, adapter_in); //201 BIT0
		ECQEvent(SCI_ADAPTERIN, SCIMode_ACPI_SMBus); //0x60
		Delay1MS(50);				  
        AC_PRESENT = 1;
        //981004-210224-A-E
	}	 
 	//AC_PRESENT = 0;
    CLEAR_MASK(EC_Flag5, BAT_1C_CHG); //EC RAM 0x389 bit6 //981004-220419-A	
	FAST_CHG_CNT1 = 0; //981004-230925-A
	FAST_CHG_CNT2 = 0; //981004-230925-A
	CHG_TEMP1 = 0; //981004-230925-A
	CHG_TEMP2 = 0; //981004-230925-A
	CHG_TEMP3 = 0; //981004-230925-A
	CHG_TEMP6 = 0; //981004-230925-A
	CHG_TEMP7 = 0; //981004-230925-A
	CLEAR_MASK(POWER_FLAG1, dp_attached); //981004-231116-A
	xTIPD1_pd_mV = 0;
    xTIPD1_pd_mA = 0;
    xTIPD1_pd_watt2 = 0;
	CLEAR_MASK(EC_Flag7, PD_COMPARE); //EC RAM 0x339 bit1
	CLEAR_MASK(EC_Flag7, PD2_CHARGE); //EC RAM 0x339 bit3
}
//981004-210118-A-E

//-----------------------------------------------------------------------------
//power button was pressed
//-----------------------------------------------------------------------------
void PSWPressed(void)
{      
    //981004-210804-A-S 
    #if 1   
    if (!LID_L)
	{			  
        EC_CLR_LATCH = 1;
		//GPIO_Write(87,1);		
      //  return;
    } 
    #endif	
    //981004-210804-A-E   
	#if 1
    if (IS_BIT_SET(POWER_FLAG3, power_on_patch))	
    {        	
        EC_CLR_LATCH = 1;	
		//GPIO_Write(87,1);			
        //return;
    } 
    #endif	
	
    //981004-210804-R-S
	#if 0
	if ((IS_BIT_CLR(POWER_FLAG1, power_on)) && (AC_IN_L) && (RMCAP_TEMP <= BATCAP10)) 		
    {             		   
	   //if (IS_BIT_SET(POWER_FLAG11, pd_adapter_in)) //203 bit1
	     if (!PD_ADAPTER_IN) //Low active	   
         { 
           bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RMcap, &BAT_RMCAP, SMBus_NoPEC);		 
           EC_CLR_LATCH = 1;
		   EC_3A = 1;
		   EC_EN_V5A = 1;   
           USB_V5A_EN = 1; 
           USB_EN_EC = 1; 	
           //BIT_SET(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3
           //PD_ACIn();
		   S4_PD_ACTIVE(); //To get PD adapter Watt	
           SystemState = SYSTEM_S0_S5; 		              		   
           //return;
	     }      		 
	}
	#endif
	//981004-210804-R-E
 
	
	BIT_SET(POWER_FLAG1, wait_PSW_off);
    PSW_COUNTER = T_PSWOFF;		        // initialize counter	
    switch (SystemState)    
    {
		case SYSTEM_G3:
        case SYSTEM_S4:		
        case SYSTEM_S5 :
            PSW_COUNTER = T_PSWOFF;		    // initialize counter
            EC_3A = 1;
			///G3_S5_PS();
            Oem_TriggerS4S0();
			///S5_S0_PS();
            break;
            
        case SYSTEM_S3 :
        case SYSTEM_S0 :
            PWR_PULSE_L = 0;
			//PM_PWRBTN_EC_LOW();
            //PSW_COUNTER = T_PSWOFF;			// initialize counter
	          //PulseSBPowerButton();            		
            break;
			
        default :
            break;
    }
}

//-----------------------------------------------------------------------------
//power button was released
//-----------------------------------------------------------------------------
void PSWReleased(void)
{
    BIT_CLR(POWER_FLAG1, wait_PSW_off);
    PSW_COUNTER = 0;				        // reset counter
    PWR_PULSE_L = 1;
	//PM_PWRBTN_EC_HIGH();
}

//-----------------------------------------------------------------------------
//power button was overrided
//-----------------------------------------------------------------------------
void PSWOverrided(void)
{       	
    //BIT_CLR(POWER_FLAG5, bios_cf9); //981004-130723-R
    if (IS_BIT_SET(POWER_FLAG1, wait_PSW_off))	// power button was pressed	
    {	
	    EC_CLR_LATCH = 1;	
		//GPIO_Write(87,1);		
		BIT_CLR(POWER_FLAG5, bios_cf9); //981004-130723-A 
		
        if (PSW_COUNTER != 0 )	
        {									 
            PSW_COUNTER--;		        // PSW_COUNTER count down

            if (PSW_COUNTER == 0)		    // time out
			{
               //BIT_SET(POWER_FLAG1, enter_S3);//981004-160421-A
               BIT_SET(POWER_FLAG1, enter_S4);               
			   Oem_TriggerS0S4(3);
			   BIT_SET(POWER_FLAG3, power_on_patch);//203 bit1 //981004-210401-A
			}	
        } 									   
    } 	
}

//-----------------------------------------------------------------------------
// battery 1 in function
//-----------------------------------------------------------------------------
void Battery1In(void)
{
    if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
       //  return;
    }	
   // ConfigBatIn();
	//ConfigCharger();
   // ProcessCharge();

    if (IS_BIT_SET(POWER_FLAG2, sci_on))
       // ECQEvent(SCI_BATIN, SCIMode_ACPI_SMBus);
		QeventSend(SCI_BATIN);
	if ((!AC_IN_L) && (IS_BIT_CLR(EC_Flag1, acin_chgcur))) //981004-230510-A
	{
		BIT_SET(EC_Flag1, acin_chgcur);	
	}	

    #if 0
    BAT1_FailCause = 0x00;
    SetBAT1CtrlStep(BAT_Step_ID);
    #endif
}

//-----------------------------------------------------------------------------
// battery 1 out function
//-----------------------------------------------------------------------------
void Battery1Out(void)
{
	BIT_CLR(EC_Flag4, old_99w); //981004-230510-A
	
	if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }	
    ConfigBatOut();

    if (IS_BIT_SET(POWER_FLAG2, sci_on))
        //ECQEvent(SCI_BATOUT, SCIMode_ACPI_SMBus);
		QeventSend(SCI_BATOUT);

    #if 0
    BAT1_FailCause = 0x00;
    BAT1_PlugOutClrVariables();
    SetBAT1CtrlStep(BAT_Step_Out);
    #endif
}

void LidOpen(void)
{
    BIT_SET(POWER_FLAG2, lid_open); 
    //DCR5 = BrightCtrl(BR_Level);
	if (GetSlp_S3) //981004-220928-A
	{	
       //GPIO_Write(84,1);
       EC_BKLOUT = 1; //GPIO J1 GPIO084
	   //GPIO_Write(102,1);
       DDS_PANEL_RST = 1;//GPIO H3 GPIO102
	}   
    BIT_CLR(POWER_FLAG9, lcd_off); //981004-170405-A
    //DCR6 = KBbclCtrl(KB_Level); //981004-200410-R
	
	//981004-131203-A-S
    #if 1 
	//if (IS_BIT_SET(POWER_FLAG1, power_on) && IS_BIT_SET(POWER_FLAG2, SLP_S3_ON)) //981004-121225-M
	if (SystemState == SYSTEM_S0)
    {	
	    //GPCRA4 = OUTPUT+PULL_DW; //981004-220719-M from OUTPUT+PULL_DW
		GPIO[27].GCR_b->DIR = 1;
		GPIO[27].GCR_b->PULLDWEN = 1;
        if ((!AC_IN_L) || (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))
		{	
	        //981004-240529-A-S
		    if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3
			{
                PWR_LED2_L = 0;
				///SET_GPO_KSO6_HI(); //KSOLGOENR 0X1D0E BIT6 => 1 //HDD LED
                GPIO_Set_IO(45,1);
	            GPIO_Write(45,1);
			}
            //981004-240529-A-E			
		}
        else
        {
			PWR_LED2_L = 1;
		}
        //981004-220729-M-E			    
		USB_KBD_PWR = 1; //981004-221014-A
		//SET_GPO_KSO7_HI(); //SET_MASK(KSOL, BIT7)//981004-231002-A
    }		
   #endif
   //981004-131203-A-E
	
    if (IS_BIT_SET(POWER_FLAG1, enter_S3))   
	{
        //GPIO_Write(114,0);
        PWR_PULSE_L = 0;
        _Delay_1ms(20);//_Delay_1ms(20); //981004-130328-M from 80
        //GPIO_Write(114,1);
        PWR_PULSE_L = 1;               
	}                                   
    if (IS_BIT_SET(POWER_FLAG2, sci_on))
	{
	    //SET_MASK(POWER_FLAG13, q_70); //981004-151117-A
        //ECQEvent(SCI_LID_CHANGE, SCIMode_ACPI_SMBus);  //0x70
		QeventSend(SCI_LID_CHANGE); 		
    }		
    //IER1 |= 0x08; //Raymond need to check how to enable int
    Lid_close_cnt =0; //981004-170405-A	
}

void LidClose(void)
{
    BIT_CLR(POWER_FLAG2, lid_open);
	
    //981004-180308-M-S	
   // if (IS_BIT_CLR(POWER_FLAG2, sci_on))
	//{	
      // GPIO_Write(84,0);
      EC_BKLOUT = 0; 
	//}
	//981004-180308-M-E
	
    BIT_SET(POWER_FLAG9, lcd_off); //981004-170405-A
	//DCR6 = 0x00; //981004-190801-A (keyboard backlight)
	PWM_Set_Duty(6,0);
    //KBlightcnt = 0x00; //992022-140402-R//981004-131125-A (keyboard backlight)
    //KBlightcnt1 = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)	
    //GPCRA4 = OUTPUT+PULL_DW; //981004-220719-M from OUTPUT+PULL_UP
	GPIO[27].GCR_b->DIR = 1;
	GPIO[27].GCR_b->PULLDWEN = 1;
    //GPIO_Write(27,1);
    PWR_LED2_L = 1; //981004-220719-M
    GPIO_Set_IO(45,1);
	GPIO_Write(45,0);		
    //IER1 &= 0xF7; // Raymond need to check how to enable int
	//GPIO_Write(95,0);
    USB_KBD_PWR = 0; //981004-220916-A GPIOF3 GPIO095
	//SET_GPO_KSO7_LO(); //CLEAR_MASK(KSOL, BIT7)  //KSO7//981004-221104-A
    GPIO_Set_IO(46,1);
	GPIO_Write(46,0);
	//Raymond need to check KSO7 with will		
	
    if (IS_BIT_SET(POWER_FLAG1, enter_S3))
       return;	  

    if (IS_BIT_SET(POWER_FLAG2, sci_on))
    {
        //ECQEvent(SCI_LID_CHANGE, SCIMode_ACPI_SMBus);  //0x70 
		QeventSend(SCI_LID_CHANGE);
    }		

}

void SmartKeyOn(void)
{
    //981004-140708-R-S
    #if 0
    if (INSTON_L != 0 || POWER_FLAG1&0x08)
        return;
	 

    if (IS_BIT_SET(POWER_FLAG2, sci_on)) 
    {      

        if (IS_BIT_SET(POWER_FLAG1, enter_S3))
            return;
				  
        if (!LID_L)
        {	     		
            return;        
        }
		//ECQEvent(SCI_SMART, SCIMode_ACPI_SMBus); //0x64
		QeventSend(SCI_SMART);		
    }
    else
    {
        if (IS_BIT_SET(POWER_FLAG1, power_on))
            return;

         if (AC_IN_L)                          // delay for lid signal ready
               _Delay_1ms(255); 
			  
         if (!LID_L)
        {	     
            EC_CLR_LATCH = 1;			
            return;        
        }		
       	
        //EC_EN_V5A = 1;
		//USB_V5A_EN = 1; 
		//USB_EN_EC = 1; 
        //EC_CLR_LATCH = 1;				
        //RSMRST_L = 1; //981004-120914-A for Rapid start resume failure (DC=>AC mode)					
        BIT_CLR(POWER_FLAG5, bios_cf9); //981004-120726-A
        //PWSeqStep = 0x01;
		Oem_TriggerS4S0();
        //BIT_SET(POWER_FLAG3, q2l_on);       
    }
	#endif
	//981004-140708-R-E
}

//981004-150727-R-S
#if 0
void HDMIOn(void)
{    
	if ((IS_BIT_SET(POWER_FLAG2, sci_on)) && (IS_BIT_CLR(POWER_FLAG1, enter_S3)) ) 
    {                      
        BIT_SET(POWER_FLAG6, hdmi_in);                		  
		//ECQEvent(SCI_HDMI, SCIMode_ACPI_SMBus); //0x79
		QeventSend(SCI_HDMI);
    }   
}

void HDMIOff(void)
{  
    if ((IS_BIT_SET(POWER_FLAG2, sci_on)) && (IS_BIT_CLR(POWER_FLAG1, enter_S3)) ) 
    {                      
        BIT_CLR(POWER_FLAG6, hdmi_in);                				  
		//ECQEvent(SCI_HDMI, SCIMode_ACPI_SMBus); //0x79
		QeventSend(SCI_HDMI);
    }	
}
#endif
//981004-150727-R-E


//981004-161226-R-S
#if 0
/* ----------------------------------------------------------------------------
 * FUNCTION: Check USB charge
 * ------------------------------------------------------------------------- */
void CHECKUSBCHARGE(void)
{     
    
	if (IS_BIT_SET(POWER_FLAG7, usb_charge_s4))
    {
		DoUSBCharge();
    }
    else 
    { 
	    NoUSBCharge();
    }
	
}
//981004-161226-R-E

/* ----------------------------------------------------------------------------
 * FUNCTION: Check Battery capacity
 * ------------------------------------------------------------------------- */
void USB_CHARGE_S5(void)
{
   
   
}

//981004-161226-R-S Remove UCF support
/* ----------------------------------------------------------------------------
 * FUNCTION: Do USB charge
 * ------------------------------------------------------------------------- */
void DoUSBCharge(void)
{

    USB_CHG_EN_D = 1;
    USB_CHG_EN_CLK = 0;	
	USB_CHG_EN_CLK = 0;
	USB_CHG_EN_CLK = 1;
	USB_CHG_EN_CLK = 1;
	USB_CHG_EN_CLK = 0;
	USB_CHG_EN_CLK = 0;
	
}

/* ----------------------------------------------------------------------------
 * FUNCTION: No USB charge
 * ------------------------------------------------------------------------- */
void NoUSBCharge(void)
{
   
    USB_CHG_EN_D = 0;
    USB_CHG_EN_CLK = 0;	
	USB_CHG_EN_CLK = 0;
	USB_CHG_EN_CLK = 1;
	USB_CHG_EN_CLK = 1;
	USB_CHG_EN_CLK = 0;
	USB_CHG_EN_CLK = 0;
   
}
//981004-161226-R-E
 #endif	
/* ----------------------------------------------------------------------------
 * FUNCTION: Check Adapter
 * ------------------------------------------------------------------------- */
void Check_Adapter(void)
{   	
	if ((IS_BIT_CLR(POWER_FLAG1, power_on)) && (IS_BIT_CLR(POWER_FLAG5, bios_cf9))) //981004-120810-M //EC RAM 205 bit0
    {	    
		//if ((AC_IN_L) || (BAT_IN_L))
        //if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
        if (((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) ||(BAT_IN_L)) //battery mode	
		{		
           patchACout++; //981004-130724-A
            Fullchgcnt =0; //992022-140403-A
		   if (patchACout == 0x3C) //981004-210312-M
           {
               GPIO_Write(87,0);//EC_CLR_LATCH = 0;
		       _Delay_1ms(250);
			   _Delay_1ms(250);
			   _Delay_1ms(250);
			   _Delay_1ms(250);
			   _Delay_1ms(250);
			   _Delay_1ms(250);
			   _Delay_1ms(250);
			   _Delay_1ms(250);
		       GPIO_Write(87,1);//EC_CLR_LATCH = 1;
           }			   
           if (patchACout >= 0x78) //981004-130724-A 60 sec. to cut off EC power from 0x78
           {                		                                 
            //   if (IS_BIT_CLR(POWER_FLAG12, tbt_pwr_on)) //20C bit5 thunderbolt power off //981004-230717-M
            //   {
				  //if (PD_ADAPTER_IN) //No Type-C device
				  //if (IS_BIT_CLR(POWER_FLAG11, pd_chargable)) //EC RAM 0x211 bit7
                  //{				  
				     //GPIO_Write(61,0);
                     TBT_POWER = 0;//GPIO C5 GPIO061
                     _Delay_1ms(1);				  
                    // GPIO_Write(126,0);
                    TBT_SWITCH = 0;//GPIO C6 GPIO126
	                 _Delay_1ms(1);
	                 //GPIO_Write(126,1);
                     TBT_SWITCH = 1;
					 
				  //}	 
               //} 
		   //   }			   
			   _Delay_1ms(250);		   
               patchACout = 0; 				   
               EC_3A = 0;  			
	           RSMRST_L = 0; //GPIOH0 GPIO099
				//5571 register
//               if (ECHIPVER >= _CHIP_EX) //981004-230425-A
//               {    
//                   SET_MASK(ESGCTRL2, F_ESPIIPG);
//               }   
		       EC_EN_V5A = 0;
		   }	   
		}
		else
		{
		   EC_EN_V5A = 1;		   
           patchACout = 0; //981004-130724-A		   
		   if (IS_BIT_SET(POWER_FLAG12, bat_full) || (IS_BIT_SET(BAT_ALARM1, FullyChg))) //981004-181123-M
		   {
		      Fullchgcnt++;
			  if (Fullchgcnt == 0x3C) //981004-210312-M
              {
                 GPIO_Write(87,0);//EC_CLR_LATCH = 0;
		         _Delay_1ms(250);
			     _Delay_1ms(250);
			     _Delay_1ms(250);
			     _Delay_1ms(250);
				 _Delay_1ms(250);
			     _Delay_1ms(250);
			     _Delay_1ms(250);
			     _Delay_1ms(250);
		         GPIO_Write(87,1);//EC_CLR_LATCH = 1;
              }	
              if (Fullchgcnt >= 0x78) //992022-140403-M from 78 //992022-140124-M from 5, BIOS need to do fully reset when on/off GPU, it's a patch for BIOS that to enter 0.5w after 1 min. 
			  {	
                #if 0			  
                if (IS_BIT_CLR(POWER_FLAG12, tbt_pwr_on)) //20C bit5 thunderbolt power off //981004-230717-M
                {
				   //if (PD_ADAPTER_IN) //No Type-C device
				   //if (IS_BIT_CLR(POWER_FLAG11, pd_chargable)) //EC RAM 0x211 bit7
                   //{				  
				     GPIO_Write(61,0);//TBT_POWER = 0;
                     _Delay_1ms(1);				  
                     GPIO_Write(126,0);//TBT_SWITCH = 0;
	                 _Delay_1ms(1);
	                 GPIO_Write(126,1);//TBT_SWITCH = 1;
					 
				  //}	 
                }
                #endif                
				_Delay_1ms(250);
			    EC_3A = 0; //981004-141020-A  			
	            RSMRST_L = 0; //981004-141020-A	
//                if (ECHIPVER >= _CHIP_EX) //981004-230425-A
//                {    
//                    SET_MASK(ESGCTRL2, F_ESPIIPG);
//                }       
                EC_EN_V5A = 0;				            				
			  }            
		   }
		   else
           {
              Fullchgcnt =0;
           }
           //981004-130108-M-E		   
		}
    }	
	
}
//981004-210225-A-S
void S4_PD_ACTIVE(void)
{
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
     _Delay_1ms(250);
	 _Delay_1ms(250);
     _Delay_1ms(250);	
     pd_ti_get_active_PDO(); //To get PD adapter Watt //Raymond will implement this function in PD UPDATE
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 _Delay_1ms(250);
	 if (xTIPD1_pd_watt > 60)			  	  
	 {                  
				  BIT_SET(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4
				  //BIT_SET(POWER_FLAG6, win_adapter_in); //206 BIT0
				  BIT_SET(POWER_FLAG1, adapter_in); //201 BIT0 //981004-210224-A				  
				  BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A )
				  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
				  SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
				  //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
                  BAT_INCURR = 0x8000; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008
				  //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
                  //BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt /981004-220927-M
                  //BAT_INCURR = 0x0009; //2.048++0.256 = 2.304A (2.304*2 = 4.608A) //84 Watt //981004-210824-M	
                  //BAT_INCURR = 0x0005; //1.024+0.256 = 1.28A (1.28*2 = 2.56A) //84Watt /981004-220927-M		
				  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);                  	
		          SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_InCurr,&BAT_INCURR);
		 ////PD_Adapter_setting();	  				  					  
				  //Enable_pd_adapter(); // Raymond will implement this on PD UPDATE
			      //GPIO_Write(28,1);
                  H_PROCHOT_L = 1; 
                  //GPIO_Write(105,0);
                  dGPU_HOLD_EC_RST_L = 0;
				  _Delay_1ms(50); //981004-210224-A
				  //GPIO_Write(97,1);
                  AC_PRESENT = 1;
    }
    else
    {
                  BIT_CLR(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4
				  //BIT_CLR(POWER_FLAG6, win_adapter_in); //206 BIT0
				  BIT_CLR(POWER_FLAG1, adapter_in); //981004-210224-A
				  //BIT_CLR(POWER_FLAG11, acout_pdin); //EC RAM 0x211 bit6
                  //GPIO_Write(28,0);
                  H_PROCHOT_L = 0; 
                  //GPIO_Write(105,1);
                  dGPU_HOLD_EC_RST_L = 1;				  
                  BAT_OPTION = 0x4DF9;
                  //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);   				  
				  SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
				// Disable_pd_adapter(); //Raymond will implement this function on PD UPDATE	
                  _Delay_1ms(50); //981004-210224-A				  
                  //GPIO_Write(97,0);
                  AC_PRESENT = 0;
                  //981004-230707-A-S
	              BIT_CLR(EC_Flag6, PD_60W);
	              BIT_CLR(EC_Flag6, PD_65W);
	              BIT_CLR(EC_Flag6, PD_80W);
	              BIT_CLR(EC_Flag6, PD_100W);
	              //981004-230707-A-E		
    }
	WTDP = 1; 
	WTDP2 = 1; 
    WTDP4 = 1;    
}	
//981004-210225-A-E
#endif
// ----------------------------------------------------------------------------
// Device insert/remove debounce routine.
// input:   device_id
// ----------------------------------------------------------------------------
const struct sDebounce Debounce_TBL[] = 
{    //reg          flag           counter          time                 press       release      nochange
    {&POWER_FLAG1, wait_PSW_off, &DEBOUNCE_CONT1,  T_PSW_DEBOUNCE,    PSWPressed, PSWReleased, PSWOverrided},
	//{&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT2,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent},
	//{&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT3,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent},
	//{&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT4,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent},
	//{&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT5,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent},
    //{&POWER_FLAG1, adapter_in,   &DEBOUNCE_CONT2,  T_AC_DEBOUNCE,     AdapterIn,  AdapterOut,  NullEvent},
    {&POWER_FLAG6, win_adapter_in,&DEBOUNCE_CONT2,  T_AC_DEBOUNCE,     AdapterIn,  AdapterOut,  NullEvent}, //981004-210224-M	
    {&BAT_STATUS,  BAT_IN,        &DEBOUNCE_CONT3, T_BAT_DEBOUNCE,    Battery1In, Battery1Out, NullEvent}, 
    {&POWER_FLAG2, lid_open,     &DEBOUNCE_CONT4,  T_LID_DEBOUNCE,    LidOpen,    LidClose,    NullEvent}, 
   {&POWER_FLAG11, pd_adapter_in, &DEBOUNCE_CONT5, T_PDAC_DEBOUNCE,   PD_ACIn,    PD_ACOut,    NullEvent}, //981004-210114-A
    {&POWER_FLAG8, pd_adapter_in2, &DEBOUNCE_CONT6, T_PDAC_DEBOUNCE,   PD_ACIn2,    PD_ACOut2,    NullEvent}, //981004-240617-A 	
    //{&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT6,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent}, 
    //{&POWER_FLAG3, inst_sw,      &DEBOUNCE_CONT7,  T_SMRT_DEBOUNCE,   SmartKeyOn, NullEvent,   NullEvent}, //981004-140708-M
    {&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT7,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent}, 
    {&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT8,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent}, 
    {&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT9,  T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent}, 
    {&EVT_STATUS1, DummyFlag,    &DEBOUNCE_CONT10, T_EXTEVT_DEBOUNCE, NullEvent,  NullEvent,   NullEvent}, 
};
// ----------------------------------------------------------------------------
// EventManager function
//
// Note : 
//	If want to call the function of status not change, please set nochange_func = 1
// ----------------------------------------------------------------------------

void EventManager(uint8_t device_id) 
{
    uint8_t new_state, old_state;
    uint8_t device_flag;
    //BYTE do_nochange_func = 0x00;

    switch (device_id)	
    {
        case 0 :     							
            new_state = !PWRSW_L;//!PWRSW_L;
            break;
			
        case 1 :     							
            new_state = !AC_IN_L;
		//new_state=0;
            break;
			
        case 2 :
            new_state = !BAT_IN_L;
		//new_state=0;
            break;
			
        case 3 :
            new_state = LID_L; 
		//new_state=0;
            break;
			
        case 4 :  
           new_state = !PD_ADAPTER_IN; //981004-210118-A	
//new_state=0;		
            break;

        case 5 :
            new_state = 0x00;
            break;
			
		case 6:
            new_state = 0x00;
            break;
			
		case 7:
            new_state = 0x00;
            break;

        case 8:
            new_state = 0x00;
            break;

        case 9:
            //new_state = EC_HDMI_PD; //981004-130520-R
			new_state = 0x00;
            break;				
	
        default :
            new_state = 0x00;
            break;
    }

    Tmp_XPntr = Debounce_TBL[device_id].REG;
    Tmp_XPntr1 = Debounce_TBL[device_id].Counter;
    device_flag = Debounce_TBL[device_id].Flag;
    old_state = ((*Tmp_XPntr & device_flag) != 0x00);

    if (new_state != old_state)	
    {		 
        if ((*Tmp_XPntr1) == 0x00)	
            (*Tmp_XPntr1) = Debounce_TBL[device_id].Time;	
        else 
        {	
            (*Tmp_XPntr1)--;

            if ((*Tmp_XPntr1) == 0)	
            {
                if (new_state)	
                {
                    (Debounce_TBL[device_id].press)();
                    *Tmp_XPntr |= device_flag;
                }
                else
                {
                    (Debounce_TBL[device_id].release)();
                    *Tmp_XPntr &= (~device_flag);
                }
            }
        }
    }
    else
    {
        *Tmp_XPntr1 = 0x00;
        (Debounce_TBL[device_id].nochange)();
    }
    //else                    // consult ITE
    //    *Tmp_XPntr1 = 0x00;	
	  //
    //(Debounce_TBL[device_id].nochange)();
}


