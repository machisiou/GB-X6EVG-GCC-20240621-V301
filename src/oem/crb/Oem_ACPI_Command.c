#include "RTK_Include.h"

//----------------------------------------------------------------------------
// Handle OEM ACPI command
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Handle ACPI commands 5x.
//----------------------------------------------------------------------------
void OEM_ACPI_Cmd_50(void)
{
    //PM1Step = 0x01; //981004-150417-R
}
void OEM_ACPI_Cmd_50Data(void)
{
    //if (PM1Step == 1)
        //PM1Data ? SET_MASK(POWER_FLAG2, DSLP_EN) : CLEAR_MASK(POWER_FLAG2, DSLP_EN); //981004-150417-R
}

//----------------------------------------------------------------------------
// Handle OEM ACPI command 8x.
//----------------------------------------------------------------------------

//Read A Battery Data
void OEM_ACPI_Cmd_60(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x02; //981004-130401-M
}

//Read B Battery Data
void OEM_ACPI_Cmd_61(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x02; //981004-130401-M
}

//981004-131011-A-S //Disable Fn Key
void OEM_ACPI_Cmd_62(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01; 
}
//981004-131011-A-E

//981004-131011-A-S //Disable Bluetooth Key
void OEM_ACPI_Cmd_63(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01; 			
}

//981004-131230-A-S for BIOS to turn off sound under S3/S4/S5 mode
void OEM_ACPI_Cmd_64(void)
{
    EC_AMP_MUTE_L = 0; //981004-210720-M from 1 //for BIOS to turn off sound under S3/S4/S5 mode
}
//981004-131225-A-E

//992022-140328-A-S for SmartManager turn off WIFI and BT led
void OEM_ACPI_Cmd_65(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01; 
}

//For SmartManager turn on/off BT LED
void OEM_ACPI_Cmd_66(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01; 
}
//992022-140328-A-E for SmartManager turn off WIFI and BT led

void OEM_ACPI_Cmd_70(void)
{
    SendFromAcpi(0x00); //981004-141007-A or BIOS will wait for a long time    
}

void OEM_ACPI_Cmd_71(void)
{
    //SET_MASK(POWER_FLAG3, img_on); //981004-220706-R	  
}

void OEM_ACPI_Cmd_75(void)
{    
    SET_MASK(POWER_FLAG5, bios_cf9);    
}

void OEM_ACPI_Cmd_76(void)
{
    CLEAR_MASK(POWER_FLAG5, bios_cf9);   
}

void OEM_ACPI_Cmd_77(void)
{    
    //SET_MASK(POWER_FLAG9, f2_press_skip); //981004-231017-R-S
    //CLEAR_MASK(POWER_FLAG8, f2_press); //981004-231017-R-S		
}

void OEM_ACPI_Cmd_78(void)
{
    #if 0
    BYTE i;
	for (i=0; i<20; i++)		// Check F9 key SCAN CODE 06.
    {	
       simple_code(0x01, MAKE_EVENT);  //F9 scan code
       simple_code(0x01, BREAK_EVENT);
       F_Service_KEY = 1;
	   Delay1MS(100);
	}
    #endif 	  
}

void OEM_ACPI_Cmd_79(void)
{
	//981004-231017-R-S
	#if 0
    simple_code(0x1C, MAKE_EVENT);  //A scan code
    simple_code(0x1C, BREAK_EVENT);
    F_Service_KEY = 1;
    CLEAR_MASK(POWER_FLAG8, f2_press); //981004-120911-A
    CLEAR_MASK(POWER_FLAG8, f9_press); //981004-120911-A
	CLEAR_MASK(POWER_FLAG8, f12_press); //981004-120911-A	
    CLEAR_MASK(POWER_FLAG8, f10_press); //981004-121017-A	
	Delay1MS(100);
	#endif
    //981004-231017-R-E	
}

//981004-130517-A-S //USB Charge for S3
void OEM_ACPI_Cmd_7A(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

//USB Charge for S4
void OEM_ACPI_Cmd_7B(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}
//981004-130517-A-E

//981004-131219-A-S
void OEM_ACPI_Cmd_7C(void) //GPU ON/OFF
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}
//981004-131219-A-E

void OEM_ACPI_Cmd_80(void)
{
   
}

void OEM_ACPI_Cmd_81(void)
{
    
}

void OEM_ACPI_Cmd_82(void)
{
   // ECCheckBurstMode = 1;
}

void OEM_ACPI_Cmd_83(void)
{
    //ECCheckBurstMode = 0;
}

void OEM_ACPI_Cmd_84(void)


{
    ITempB05 = 0x00;

    if (SCI_Event_Out_Index != SCI_Event_In_Index)
    {  
        ITempB05 = SCI_Event_Buffer[SCI_Event_Out_Index];
        SCI_Event_Out_Index++;

        if (SCI_Event_Out_Index >= EVENT_BUFFER_SIZE) 
           	SCI_Event_Out_Index = 0;

        if (SCI_Event_Out_Index == SCI_Event_In_Index)
            CLEAR_MASK(PM1STS,SCIEVT);

        SendFromAcpi(ITempB05);
    }
    else
	{
        CLEAR_MASK(PM1STS,SCIEVT);
		//SendFromAcpi(0x00); //981004-130605-R to prevent scancode may not be issued
	}	
}

void OEM_ACPI_Cmd_86(void)


{
    SET_MASK(SYS_MISC1,ACPI_OS);
}

void OEM_ACPI_Cmd_87(void)


{
    CLEAR_MASK(SYS_MISC1,ACPI_OS);
}
//981004-130516-A-S for Smart connect EC timer
void OEM_ACPI_Cmd_88(void)
{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}
//981004-130516-A-E

//Turn off system and then Turn on
void OEM_ACPI_Cmd_8C(void)

{
    //vTurnOffPower();
	#if 0
    Oem_S0S4Sequence();	
    Delay1MS(200);
    //PWSeqStep=1;
	Oem_S4S0Sequence();
	#endif
}

void OEM_ACPI_Cmd_8E(void)


{
	//SET_MASK(UtilityFlag, SMBusDebug); //981004-150417-R
}

void OEM_ACPI_Cmd_8F(void)


{
	//CLEAR_MASK(UtilityFlag, SMBusDebug); //981004-150417-R
}

//981004-180717-A-S //Check battery aging status
void OEM_ACPI_Cmd_90(void)
{ 
    #if 1
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, BAT_LFCCAP, SMBus_NoPEC);
    SMBUS_RW_W(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, &BAT_LFCCAP);
	BAT_LFCCAP2 = (BAT_LFCCAP<<8)|(BAT_LFCCAP>>8);
    //981004-200909-M-S
	if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-230510-A
  	{
      if (BAT_LFCCAP2 < 2932) //6514 * 0.5 * 0.9 = 2932 //981004-181003-M from 3100
	  {
	    //ECQEvent(SCI_BAT_AGING2, SCIMode_ACPI_SMBus); //0x92
		//SendFromAcpi(0x02);
		SET_MASK(POWER_FLAG11, bat_repair); //981004-181030-M
	}	
	else if (BAT_LFCCAP2 < 4397) //6514 * 0.75 * 0.9 = 4397 //981004-181003-M from 4650
	{
	    //ECQEvent(SCI_BAT_AGING1, SCIMode_ACPI_SMBus); //0x91
		//SendFromAcpi(0x01);
		SET_MASK(POWER_FLAG11, bat_aging); //981004-181030-M
	}
	else
	{
	    //ECQEvent(SCI_BAT_AGING0, SCIMode_ACPI_SMBus); //0x90
	    //SendFromAcpi(0x00);
		SET_MASK(POWER_FLAG11, bat_normal); //981004-181030-M
	  }
	  BAT_LFCCAP = 0x7219;
	}
	else //981004-230510-A
	{		
	   if (BAT_LFCCAP2 < 2797) //6215 * 0.5 * 0.9 = 2797 //981004-231215-M 
	   {
	    //ECQEvent(SCI_BAT_AGING2, SCIMode_ACPI_SMBus); //0x92
		//SendFromAcpi(0x02);
		  SET_MASK(POWER_FLAG11, bat_repair); //981004-181030-M
	   }	
	//else if (BAT_LFCCAP2 < 5157) //7640 * 0.75 * 0.9 = 5157 //981004-220615-M from 4397 //981004-230417-M //LFCCAP_TEMP
	   else if (BAT_LFCCAP2 < 4195) //6215 * 0.75 * 0.9 = 4195 //981004-231215-M
	   {
	    //ECQEvent(SCI_BAT_AGING1, SCIMode_ACPI_SMBus); //0x91
		//SendFromAcpi(0x01);
		   SET_MASK(POWER_FLAG11, bat_aging); //981004-181030-M
	   }
       else
	   {
	    //ECQEvent(SCI_BAT_AGING0, SCIMode_ACPI_SMBus); //0x90
	    //SendFromAcpi(0x00);
		   SET_MASK(POWER_FLAG11, bat_normal); //981004-181030-M
	   }
	}
    //981004-200909-M-E
	#endif
}
//981004-180717-A-E

//981004-130421-A-S
void OEM_ACPI_Cmd_91(void)
{
    EC_AMP_MUTE_L = 0; //mute //981004-210720-M from 1
}

void OEM_ACPI_Cmd_92(void)
{
    EC_AMP_MUTE_L = 1; //unmute	
}
//981004-130421-A-E

//981004-130724-A-S for Turbo fan (Full Speed fan)
void OEM_ACPI_Cmd_94(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

//981004-160305-A-S
void OEM_ACPI_Cmd_95(void)
{     
     EC_BKLOUT = ~EC_BKLOUT;	 
}
//981004-160305-A-E
	 
//Read EC RAM 0x300
void OEM_ACPI_Cmd_99(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_9A(void)
{
    
}
//981004-130222-A-E

//981004-130222-A-S for GC6 function
void OEM_ACPI_Cmd_9B(void)
{
    
}
//981004-130222-A-E

//981004-150417-R-S
void OEM_ACPI_Cmd_A0(void)

{
    #if 0
    PCSSGH = 0xE5; //Select Channel 5 to choose C4CPRS as Prescaler divider ---0x180D	  
	PCFSR = 0x8F; //prescaler clock freq selects EC clock (about 9.2MHz) ---0x180B for all Group 
    C0CPRS = 0x01; //PWM input clock is divided by 1 ---0x1800  //20K Hz for fan (PWM0)       	
	CTR = 0xE5; //prescaler output clock is divided by 229 ---0x1801 

    for(ITempB01=0x00;ITempB01<16;ITempB01++)	//240us loop
	{		        
        Delay1MS(250); 
        DCR0 = 0xE5;				
    }
    #endif	
}

void OEM_ACPI_Cmd_A1(void)
{
    #if 0
    PCSSGH = 0xE5; //Select Channel 5 to choose C4CPRS as Prescaler divider ---0x180D	  
	PCFSR = 0x8F; //prescaler clock freq selects EC clock (about 9.2MHz) ---0x180B for all Group 
    C0CPRS = 0x01; //PWM input clock is divided by 1 ---0x1800  //20K Hz for fan (PWM0)       	
	CTR = 0xE5; //prescaler output clock is divided by 229 ---0x1801 

    for(ITempB01=0x00;ITempB01<16;ITempB01++)	//240us loop
	{		        
        Delay1MS(250); 
        DCR0 = 0x00;				
    }
    #endif	
}
//981004-150417-R-E

//981004-151225-R-S to command 95
void OEM_ACPI_Cmd_A5(void)
{
    #if 0
    if (IS_MASK_SET(POWER_FLAG9, lcd_off ))
    {
        EC_BKLOUT = 0;
    }
    else
    {
        EC_BKLOUT = 1;
    }  		
    #endif	
}
//981004-151225-R-E

//981004-130408-A-S for BIOS flash Enter/Exit
void OEM_ACPI_Cmd_A8(void)
{   
    ///EA =0;
    __enable_irq();
	///WDTCON = 0X01; //981004-130627-A
    WDT->CTRL_b.EN = 1;
	SET_MASK(POWER_FLAG5, BIOS_flash); //981004-120606-A
	//981004-150414-A-S
	SET_MASK(POWER_FLAG6, adjustfan);
	FanRPM1=0x39; //981004-200108-M from 0x5D
	FanRPM2=0x39; //981004-200108-M from 0x5D
    DCR0 = FanRPM1;	
    DCR3 = FanRPM2;	
	//981004-150414-A-E
}

//981004-130627-M-S
void OEM_ACPI_Cmd_A9(void)
{
    if (IS_MASK_SET(POWER_FLAG5, BIOS_flash))
    {    
        SET_MASK(POWER_FLAG6, BIOS_flash_ok); //981004-131213-A
        //FLHCTRL3R = 0x18; //981004-131213-R
        //ETWCFG = 0x20; //981004-131213-R
        //EWDKEYR = 0xFF; //981004-131213-R
        CLEAR_MASK(POWER_FLAG5, BIOS_flash);
        //while(1); //981004-131213-R
		//981004-150414-A-S
	    CLEAR_MASK(POWER_FLAG6, adjustfan);
	  	FanRPM1=0x0;
		FanRPM2=0x0;
		//981004-150414-A-E				
    }
}
//981004-130627-M-E

void OEM_ACPI_Cmd_B1(void)

{
    //ACPI_Gen_Int(ACPICmdSCI); //981004-130702-R
	//PM1Step =0x01; //981004-130702-R
}


void OEM_ACPI_Cmd_B2(void)
{
    //981004-180712-R-S
    #if 1
    SET_MASK(POWER_FLAG13, HDA_SDO_BIOS); 
    SET_MASK(POWER_FLAG13, Flash_ME_ON); //981004-181221-A 
	
    PWR_PULSE_L = 0;
    Delay1MS(100); 
    PWR_PULSE_L = 1;
    #endif
	//981004-180712-R-E
}

void OEM_ACPI_Cmd_B3(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

//981004-200721-A-S
void OEM_ACPI_Cmd_B6(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}
//981004-200721-A-E

//981004-140505-A-S for DDR voltage select
void OEM_ACPI_Cmd_BA(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_BB(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_BC(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_BD(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}
//981004-140505-A-E for DDR voltage select

void OEM_ACPI_Cmd_C0(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_C1(void)

{
     
}

//981004-140123-A-S for battery ship mode
void OEM_ACPI_Cmd_C2(void)

{
     //WORD Ship_mode; //981004-150522-R
     
	 //981004-150525-A-S To Disable charging before entering ship mode
     BAT_CHGCURR = 0x0000; 
     BAT_CHGVOL = 0x0000;
     BAT_INCURR = 0x0000; 
     BAT_OPTION = 0x49F1; //Battery only setting + Inhibit charging for BQ24780 from 0x48F1 default + BIT0 =>  Inhibit charging (POR : 0x48F1+BI0= 0x49F1) 
	
     //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
     //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
     //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);    
     //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); 
     SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR);
     SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL );
     SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR );
     SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION );


	//981004-190116-M-S 
	ECQEvent(SCI_SHIP, SCIMode_ACPI_SMBus); //0x43
	SET_MASK(POWER_FLAG3, ship_mode); 
	
	//SysPowState = SYSTEM_S0_S4;
    //981004-190116-M-E
	
	#if 0
	do
    {                            					
	   PWR_PULSE_L = 0;	
	} while (SLP_S4_L);
	
	
    ESS_MPS_5V = 0;   
    USB_V5A_EN = 0; //USB_PWR_EN 
    USB_EN_EC = 0; 
	Delay1MS(250);	
    RSMRST_L = 0; 
    if (ECHIPVER >= _CHIP_EX) //981004-231214-A
    {    
        SET_MASK(ESGCTRL2, F_ESPIIPG);
    }
    EC_3A = 0;
	//EC_ALW_EN = 0; //981004-231002-A
	
	
	Delay1MS(250); 
	Delay1MS(250); 
	Delay1MS(250); 
	Delay1MS(250); 	 
	#endif 
    //981004-171031-M-E

    //981004-190116-R-S	 
	 #if 0
     Ship_mode = 0x1000;
     bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
     Delay1MS(250); 
     bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
       
     for(ITempB01=0x00;ITempB01<20;ITempB01++)	//240us loop
	 {
        Delay1MS(250);         		
     }
	 #endif
    //981004-190116-M-E	 
	 
} 
//981004-140123-A-E

//981004-130227-A-S 
void OEM_ACPI_Cmd_C5(void)
{
    #if 0
    SET_MASK(POWER_FLAG8, dgpu_timer);		
	Load_EXTimer2();	
    #endif	
}
//981004-130227-A-E

//981004-130319-A-S
void OEM_ACPI_Cmd_C6(void)
{
   #if 0
   SET_MASK(POWER_FLAG9, dgpu_timer2);   
   Load_EXTimer2();
   #endif   
}
//981004-130319-A-E

void OEM_ACPI_Cmd_D0(void)

{
    #if 0
    EC_RUNTIME_SCI_L = 0;
	WNCKR = 0x00; 
	WNCKR = 0x00;
    WNCKR = 0x00; 
	EC_RUNTIME_SCI_L = 1;
    #endif	
    while(1);
}

void OEM_ACPI_Cmd_D1(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_D8(void)
{
    #if 0
    EC_EXTSMI_L = 0;
	Delay1MS(1);
	WNCKR = 0x00; 
	WNCKR = 0x00;
    WNCKR = 0x00; 
	EC_EXTSMI_L = 1;
    #endif	
    FanFullOn();
	///RamProgram(0X66);
}
//981004-180724-A-S for NV BSOD issue
void OEM_ACPI_Cmd_D9(void)//170157-180706-R
{
	//if(AC_IN_L)
	if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
    //if ((AC_IN_L) ||(IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4 
	{
		NVDeventStatus = 0x02;
		ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); 
	}
}
//981004-180724-A-E
void OEM_ACPI_Cmd_DA(void)
//992022-130306-A-S for external ROM flash
{
    ///FLHCTRL3R = 0x00;
    ///EC_Indirect_Selection = 0x0F;
}
//992022-130306-A-E

void OEM_ACPI_Cmd_DB(void)

{
     //SET_MASK(POWER_FLAG6, sci_time_delay); //981004-130703-R
	 while ((PM1STS & P_OBF))
                    ;
     SendFromAcpi(0xAA);	 
     Delay1MS(5);
	 
     while ((PM1STS & P_OBF))
                    ;	 
	 SendFromAcpi(0xBB);
	 Delay1MS(5);
	 
     while ((PM1STS & P_OBF))
                    ;	 
	 SendFromAcpi(0xCC);
	 Delay1MS(5);
	 
	 while ((PM1STS & P_OBF))
                    ;	 
	 SendFromAcpi(0xDD);
	 Delay1MS(5);
	 
	while ((PM1STS & P_OBF))
                    ;	 
    ECQEvent(SCI_FLASH, SCIMode_ACPI_SMBus); //0x99 
    //CLEAR_MASK(POWER_FLAG6, sci_time_delay); //981004-130703-R
}

void OEM_ACPI_Cmd_DD(void)
{
	//RamProgram(0X66);
}

void OEM_ACPI_Cmd_DF(void) //992022-130618-A for smart cooling

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E0(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E1(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E2(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E3(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E4(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E5(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E6(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E7(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E8(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_E9(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_EA(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_EB(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_EC(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

void OEM_ACPI_Cmd_ED(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}

//981004-130415-A-S	
void OEM_ACPI_Cmd_EF(void)

{
    ACPI_Gen_Int(ACPICmdSCI);
	PM1Step =0x01;
}
//981004-130415-A-E

//----------------------------------------------------------------------------
// The hook function of 62 port data
//  Note : 
//  PM1Step != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_62Port(BYTE PM1Data)
{
    switch(PM1Data)
    {	
	    case 0x50:
            OEM_ACPI_Cmd_50Data();
            break;
	    case 0x60:
            OEM_ACPI_Cmd_60Data();
            break;
		
        case 0x61:
            OEM_ACPI_Cmd_61Data();
            break;
			
		case 0x62:
            OEM_ACPI_Cmd_62Data(); //981004-131011-A			
            break;

        case 0x63:
            OEM_ACPI_Cmd_63Data(); //981004-131011-A			
            break;				
        case 0x65:
            OEM_ACPI_Cmd_65Data(); //981004-140502-A			
            break;

        case 0x66:
            OEM_ACPI_Cmd_66Data(); //981004-140502-A			
            break;			
		case 0x7A:
            OEM_ACPI_Cmd_7AData(); //981004-130517-A
            break;

        case 0x7B:
            OEM_ACPI_Cmd_7BData(); //981004-130517-A
            break;
        case 0x7C:
            OEM_ACPI_Cmd_7CData(); //981004-131219-A
            break;					
        case 0x88:
            OEM_ACPI_Cmd_88Data(); //981004-130516-A ISCT
            break;				
        case 0x94:
            OEM_ACPI_Cmd_94Data();
            break;			
			
		case 0x99:
            OEM_ACPI_Cmd_99Data();
            break;
			
		case 0x9A:
            OEM_ACPI_Cmd_9AData();
            break;	

        case 0xB1:
            OEM_ACPI_Cmd_B1Data();
            break;
			
        case 0xB3:
            OEM_ACPI_Cmd_B3Data();
            break;
			
//981004-200721-A-S
		case 0xB6:
            OEM_ACPI_Cmd_B6Data();
            break;	
//981004-200721-A-E
			
        //981004-140505-A-S for DDR voltage select
        case 0xBA:
            OEM_ACPI_Cmd_BAData();
            break;

        case 0xBB:
            OEM_ACPI_Cmd_BBData();
            break;

        case 0xBC:
            OEM_ACPI_Cmd_BCData();
            break;

        case 0xBD:
            OEM_ACPI_Cmd_BDData();
            break;
        //981004-140505-A-S for DDR voltage select
		
		case 0xC0:
            OEM_ACPI_Cmd_C0Data();
            break;

        case 0xD1:
            OEM_ACPI_Cmd_D1Data();
            break;

        case 0xDF:
            OEM_ACPI_Cmd_DFData(); //981004-130703-A for smart cooling
            break;				

        case 0xE0:
            OEM_ACPI_Cmd_E0Data();
            break;

        case 0xE1:
            OEM_ACPI_Cmd_E1Data();
            break;
  
        case 0xE2:
            OEM_ACPI_Cmd_E2Data();
            break;
		
        case 0xE3:
            OEM_ACPI_Cmd_E3Data();
            break;
		
		case 0xE4:
            OEM_ACPI_Cmd_E4Data();
            break;
		
        case 0xE5:
            OEM_ACPI_Cmd_E5Data();
            break;

        case 0xE6:
            OEM_ACPI_Cmd_E6Data();
            break;

        case 0xE7:
            OEM_ACPI_Cmd_E7Data();
            break;

        case 0xE8:
            OEM_ACPI_Cmd_E8Data();
            break;

        case 0xE9:
            OEM_ACPI_Cmd_E9Data();
            break;

        case 0xEA:
            OEM_ACPI_Cmd_EAData();
            break;

        case 0xEB:
            OEM_ACPI_Cmd_EBData();
            break;

        case 0xEC:
            OEM_ACPI_Cmd_ECData();
            break;

        case 0xED:
            OEM_ACPI_Cmd_EDData();
            break;
		
        //981004-130415-A-S		
		case 0xEF: 
            OEM_ACPI_Cmd_EFData();
            break;	
        //981004-130415-A-E
		
        default:
        break;
    }
}

//----------------------------------------------------------------------------
// The hook function of 66 port command.
//----------------------------------------------------------------------------
void Hook_66Port(BYTE PM1Cmd)
{
    switch(PM1Cmd)
    {
        case 0x50:
            OEM_ACPI_Cmd_50();
            break;
	    case 0x60:
        OEM_ACPI_Cmd_60();
        break;
		
		case 0x61:
        OEM_ACPI_Cmd_61();
        break;
		
		case 0x62:
        OEM_ACPI_Cmd_62(); //981004-131011-A
        break;
		
		case 0x63:
        OEM_ACPI_Cmd_63(); //981004-131011-A
        break;
		
		case 0x64:
        OEM_ACPI_Cmd_64(); //981004-131225-A to turn off CPU fan
        break;
		
		case 0x65:
            OEM_ACPI_Cmd_65(); //992022-140328-A for SmartManager turn off WIFI and BT led
        break;
		
		case 0x66:
            OEM_ACPI_Cmd_66(); //992022-140328-A for SmartManager turn off WIFI and BT led
        break;
		
		case 0x70:
        OEM_ACPI_Cmd_70();
        break;
		
		case 0x71:
        OEM_ACPI_Cmd_71();
        break;
		
		case 0x75:
        OEM_ACPI_Cmd_75();
        break;
		
		case 0x76:
        OEM_ACPI_Cmd_76();
        break;
		
		case 0x77:
        OEM_ACPI_Cmd_77();
        break;
		
		case 0x78:
        OEM_ACPI_Cmd_78();
        break;
		
		case 0x79:
        OEM_ACPI_Cmd_79();
        break;
		
		case 0x7A:
        OEM_ACPI_Cmd_7A(); //981004-130517-A
        break;
		
		case 0x7B:
        OEM_ACPI_Cmd_7B(); //981004-130517-A
        break;
		
		case 0x7C:
        OEM_ACPI_Cmd_7C(); //981004-131219-A
        break;
		
        case 0x80:
        OEM_ACPI_Cmd_80();
        break;

        case 0x81:
        OEM_ACPI_Cmd_81();
        break;

        case 0x82:
        OEM_ACPI_Cmd_82();
        break;

        case 0x83:
        OEM_ACPI_Cmd_83();
        break;

        case 0x84:
        OEM_ACPI_Cmd_84();
        break;

        case 0x86:
        OEM_ACPI_Cmd_86();
        break;

        case 0x87:
        OEM_ACPI_Cmd_87();
        break;
		
		case 0x88:
        OEM_ACPI_Cmd_88(); //981004-130516-A ISCT
        break;
		
		case 0x8C:
        OEM_ACPI_Cmd_8C();
        break;

        case 0x8E:
        OEM_ACPI_Cmd_8E();
        break;

        case 0x8F:
        OEM_ACPI_Cmd_8F();
        break;
		
		case 0x90:
        OEM_ACPI_Cmd_90();
        break;
		
		case 0x91:
        OEM_ACPI_Cmd_91();
        break;
		
		case 0x92:
        OEM_ACPI_Cmd_92();
        break;
		
		case 0x94:
        OEM_ACPI_Cmd_94();
        break;
		
		//981004-160305-A-S
		case 0x95:
        OEM_ACPI_Cmd_95();
        break;
		//981004-160305-A-E
		
		case 0x99:
        OEM_ACPI_Cmd_99();
        break;
		
		case 0x9A:
        OEM_ACPI_Cmd_9A();
        break;
		
		case 0x9B:
        OEM_ACPI_Cmd_9B();
        break;
		
		case 0xA0:
        OEM_ACPI_Cmd_A0();
        break;

        case 0xA1:
        OEM_ACPI_Cmd_A1();
        break;
		
		case 0xA5:
        OEM_ACPI_Cmd_A5(); //981004-130107-A
        break;
		
		case 0xA8:
        OEM_ACPI_Cmd_A8(); //981004-130408-A
        break;
		
		case 0xA9:
        OEM_ACPI_Cmd_A9(); //981004-130408-A
        break;
		
		case 0xB1:
        OEM_ACPI_Cmd_B1();
        break;
		//981004-160914-A-S
		case 0xB2:
        OEM_ACPI_Cmd_B2();
        break;		
		//981004-160914-E

        case 0xB3:
        OEM_ACPI_Cmd_B3();

//981004-200721-A-S		
		case 0xB6:
        OEM_ACPI_Cmd_B6();
        break;
//981004-200721-A-E

        //981004-140505-A-S for DDR voltage select
        case 0xBA:
            OEM_ACPI_Cmd_BA();
            break;

        case 0xBB:
            OEM_ACPI_Cmd_BB();
            break;

        case 0xBC:
            OEM_ACPI_Cmd_BC();
            break;

        case 0xBD:
            OEM_ACPI_Cmd_BD();
            break;
        //981004-140505-A-E for DDR voltage select
		
		case 0xC0:
        OEM_ACPI_Cmd_C0();
        break;
		
		case 0xC1:
        OEM_ACPI_Cmd_C1();
        break;
		
		case 0xC2: //981004-140123-A
        OEM_ACPI_Cmd_C2();
        break;
		
		case 0xC5:
        OEM_ACPI_Cmd_C5(); //981004-130207-A
        break;
		
		case 0xC6:
        OEM_ACPI_Cmd_C6(); //981004-130207-A
        break;
		
		case 0xD0:
        OEM_ACPI_Cmd_D0();
        break;

        case 0xD1:
        OEM_ACPI_Cmd_D1();
        break;
		
		case 0xD8:
        OEM_ACPI_Cmd_D8();
		break;
    //981004-180724-A-S		
	case 0xD9:
		OEM_ACPI_Cmd_D9();
		break;
    //981004-180724-A-E		
		case 0xDA:
        OEM_ACPI_Cmd_DA(); //992022-130306-A for external ROM flash
        break;
		case 0xDB:
        OEM_ACPI_Cmd_DB();
        break;

        case 0xDD:
        OEM_ACPI_Cmd_DD();
            break;

        case 0xDF:
            OEM_ACPI_Cmd_DF(); //992022-130627-A for smart cooling
            break;
		
		case 0xE0:
        OEM_ACPI_Cmd_E0();
        break;
		
		case 0xE1:
        OEM_ACPI_Cmd_E1();
        break;
       
        case 0xE2:
        OEM_ACPI_Cmd_E2();
        break;
		
		case 0xE3:
        OEM_ACPI_Cmd_E3();
        break;
		
		case 0xE4:
        OEM_ACPI_Cmd_E4();
        break;
		
		case 0xE5:
        OEM_ACPI_Cmd_E5();
        break;
				
		case 0xE6:
        OEM_ACPI_Cmd_E6();
        break;
		
		case 0xE7:
        OEM_ACPI_Cmd_E7();
        break;
		
		case 0xE8:
        OEM_ACPI_Cmd_E8();
        break;
		
		case 0xE9:
        OEM_ACPI_Cmd_E9();
        break;
		
		case 0xEA:
        OEM_ACPI_Cmd_EA();
        break;
		
		case 0xEB:
        OEM_ACPI_Cmd_EB();
		break;
		
		case 0xEC:
        OEM_ACPI_Cmd_EC();
        break;
		
		case 0xED:
        OEM_ACPI_Cmd_ED();
        break;
		
		case 0xEF:
        OEM_ACPI_Cmd_EF();
        break;
        
		
        default:
        break;
    }
}

//----------------------------------------------------------------------------
// Handle the data of ACPI command 
//----------------------------------------------------------------------------
void OEM_ACPI_Cmd_60Data(void)

{
    //if (PM1Step == 1)
	if (PM1Step == 2) //981004-130401-M
    {
        PM1Data1 = PM1Data;  // address
        
        if (!bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, PM1Data1, &test0C, SMBus_NoPEC)) //981004-130328-M from SmbusChA
          test0C = 0x00;
        
        PM1DO = test0C & 0xFF;
      	//PM1Step = 2; //981004-130401-R
    }
    else if (PM1Step == 1)
    {
        //PM1Step = 0; //981004-130401-R
        PM1DO = test0C >> 0x08;
    }             
}

void OEM_ACPI_Cmd_61Data(void)

{
     //if (PM1Step == 1)
	if (PM1Step == 2) //981004-130401-M
    {
        PM1Data1 = PM1Data;  // address
        
        if (!bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, PM1Data1, &test0D, SMBus_NoPEC)) //981004-130328-M from SmbusChC
          test0D = 0x00;
        
        PM1DO = test0D & 0xFF;
      	//PM1Step = 2; //981004-130401-R
    }
    else
    {
        //PM1Step = 0; //981004-130401-R
        PM1DO = test0D >> 0x08;
    }                
}

//981004-180731-R-S
void OEM_ACPI_Cmd_62Data(void) //Disable Fn Key
{ 
    #if 0  	
	if (PM1Step == 1)
    {
       if (PM1Data)                   
        {		               
			SET_MASK(POWER_FLAG10, disable_fn_key);           		
            WLAN_LED = 0; //992022-131030-A
            BT_LED = 0; //992022-131030-A
            
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG10, disable_fn_key);
			//981004-140129-A-S
			if ((BT_EN == 1) && (IS_MASK_CLEAR(POWER_FLAG10, disable_bt_key)))
			{			
                BT_LED = 1;
		    }		 
			if (POWER_FLAG2, wlan_on) //981004-140421-M
			{
		        WLAN_LED = 1; //981004-140418-A
			}	
            //981004-140129-E			
        }
        PM1Step = 0;		
    }
    #endif	
}
//981004-180731-R-E

//981004-180731-R-S
void OEM_ACPI_Cmd_63Data(void) //Disable Bluetooth Key
{ 
    #if 0  	
	if (PM1Step == 1)
    {
       if (PM1Data)                   
        {		               
			SET_MASK(POWER_FLAG10, disable_bt_key); 			
            BT_LED = 0; //981004-140129-A           
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG10, disable_bt_key);			
            BT_LED = 1;	//981004-140129-A		
        }
        PM1Step = 0;		
    }
    #endif	
}
//981004-180731-R-E

void OEM_ACPI_Cmd_65Data(void) //Turn On/Off WiFi LED
{ 

    //981004-180731-R-S 
    #if 0  	
	if (PM1Step == 1)
    {
       if (PM1Data)                   
        {		               
			WLAN_LED = 1; 
			SET_MASK(POWER_FLAG2, wlan_on); //981004-150311-A for C&C to provide the command
        }
        else
        {		               
			WLAN_LED = 0;
			CLEAR_MASK(POWER_FLAG2, wlan_on); //981004-150311-A for C&C to provide the command
        }
        PM1Step = 0;		
    }
    #endif
    //981004-180731-R-E	
}

//981004-180731-R-S
void OEM_ACPI_Cmd_66Data(void) //Turn On/Off BT LED
{
    #if 0   	
	if (PM1Step == 1)
    {
       if (PM1Data)                   
        {            	
			BT_LED = 1;         
        }
        else
        {          
			BT_LED = 0;		
        }
        PM1Step = 0;		
    } 
	 #endif
}
//981004-180731-R-E

void OEM_ACPI_Cmd_7AData(void) //S3 charge for DC mode
{   	
    #if 0  	
	if (PM1Step == 1)
    {
       if (PM1Data)                   
        {		               
	        SET_MASK(POWER_FLAG1, usb_charge_s3); //992022-131216-A for P34R UCF2 EC RAM 201 bit5
        }
        else
        {		               
	        CLEAR_MASK(POWER_FLAG1, usb_charge_s3);	//992022-131216-A for P34R UCF2
        }
        PM1Step = 0;		
    } 
    #endif	
}

void OEM_ACPI_Cmd_7BData(void) //S4 charge for UCF DC mode
{
	//981004-190801-R-S
	#if 0
    if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {		               
	        SET_MASK(POWER_FLAG7, usb_charge_s4); //EC RAM 207 bit2
        }
        else
        {		               
	        CLEAR_MASK(POWER_FLAG7, usb_charge_s4);
        }
        PM1Step = 0;		
    }
    #endif
    //981004-190801-R-E	
}
//981004-130517-A-E

//981004-131219-A-S
void OEM_ACPI_Cmd_7CData(void) //GPU ON/OFF
{
}
//981004-131219-A-E


//981004-130516-A-S for smart connect EC timer
void OEM_ACPI_Cmd_88Data(void)
{
    //981004-170427-R-S 
    #if 0
    if (PM1Step == 1)
    {
        if (PM1Data == 0)
        {		    
            CLEAR_MASK(POWER_FLAG5, ISCT_EC_timer);
			EC_timer = 0;
            Stop_EXTimer2();			
        }
        else
        {		   
            SET_MASK(POWER_FLAG5, ISCT_EC_timer);
			EC_timer = 0;
            Load_EXTimer2();			
        }
        PM1Step = 0;
    }
	#endif
	//981004-170427-R-E
}

//981004-130724-A-S for Turbo fan (Full Speed fan)
void OEM_ACPI_Cmd_94Data(void)
{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {		                
            SET_MASK(POWER_FLAG10, fullspeed_fan);            
        }
        else
        {		    
            CLEAR_MASK(POWER_FLAG10, fullspeed_fan);
        }
        PM1Step = 0;
    }
}
//981004-130724-A-E for Turbo fan (Full Speed fan)
void OEM_ACPI_Cmd_99Data(void)

{
    if (PM1Step == 1)
    {	   
        SendFromAcpi(Hook_ReadMapECSpace2(PM1Data));       
        PM1Step = 0;
    }       
}

void OEM_ACPI_Cmd_9AData(void)

{
}

void OEM_ACPI_Cmd_B1Data(void)

{
   
}

//981004-140904-R-S for power saving mode
void OEM_ACPI_Cmd_B3Data(void)

{
    #if 0
    if (PM1Step == 1)
    {
        if (PM1Data == 0)
        {
            CLEAR_MASK(POWER_FLAG10, power_saving_mode); //BIT 3
		
        }
        else
        {
            SET_MASK(POWER_FLAG10, power_saving_mode); 
        }
        PM1Step = 0;
    }
	#endif
}
//981004-140904-R-E for power saving mode

//981004-200721-A-S
void OEM_ACPI_Cmd_B6Data(void)
{/// 將來改用RTK MS Mode
/// 進入MS MODE 會關 PECI
    if (PM1Step == 1)
    {
        if (PM1Data == 0x2C)
        {
          ///  GPCRF6 = OUTPUT;
          ///  PECI_EC_LO();		    
        }
		else if (PM1Data == 0x2D)
        {
            /* BIOS Exit Modern Standy */
         ///   SET_ExitMS(0x2D, 2);
        ///    Init_PECI();		    
        }
        xEC_CMDR = 0;
		PM1Step = 0;
    }            
}
//981004-200721-A-E

//981004-140505-A-S for DDR voltage select
void OEM_ACPI_Cmd_BAData(void)

{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {
            //VDDR135CH1 = 0; //981004-150423-R
            //VDDR135CH2 = 0; //981004-150423-R
        }
        PM1Step = 0;
    }
}

void OEM_ACPI_Cmd_BBData(void)

{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {
            //VDDR135CH1 = 1; //981004-150423-R
            //VDDR135CH2 = 0; //981004-150423-R		
        }
        PM1Step = 0;
    }
}

void OEM_ACPI_Cmd_BCData(void)

{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {
            //VDDR135CH1 = 0; //981004-150423-R
            //VDDR135CH2 = 1; //981004-150423-R			
        }
        PM1Step = 0;
    }
}

void OEM_ACPI_Cmd_BDData(void)

{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {
            //VDDR135CH1 = 1; //981004-150423-R
            //VDDR135CH2 = 1; //981004-150423-R
        }
        PM1Step = 0;
    }
}
//981004-140505-A-E for DDR voltage select

void OEM_ACPI_Cmd_C0Data(void)

{
    if (PM1Step == 1)
    {
        if (PM1Data == 0)
        {
            CLEAR_MASK(POWER_FLAG6, GPU_on); 
		
        }
        else
        {
            SET_MASK(POWER_FLAG6, GPU_on); 
        }
        PM1Step = 0;
    }
}

void OEM_ACPI_Cmd_D1Data(void)

{
    if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {		               
			SET_MASK(POWER_FLAG9, rtc_wake_support);            		
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG9, rtc_wake_support);          	
        }
        PM1Step = 0;		
    }                  
}

//981004-130703-A-S for smart cooling
void OEM_ACPI_Cmd_DFData(void) 
{
    if (PM1Step == 1)                   
    {         
        if (PM1Data)
        {
            SET_MASK(POWER_FLAG8, smart_cooling_on);
			FanDACLevel = 0; //992022-141112-A
        }
        else
        {
            CLEAR_MASK(POWER_FLAG8, smart_cooling_on);
            CLEAR_MASK(POWER_FLAG6, sv_thrt_on);
            ECQEvent(SCI_SV_THROFF, SCIMode_ACPI_SMBus); //0x97            
           
            //AC_IN_L == 0 ? ECQEvent(SCI_P0, SCIMode_ACPI_SMBus) : ECQEvent(SCI_P1, SCIMode_ACPI_SMBus); //981004-190822-R

            //if (AC_IN_L) //battery mode 
                  
			if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
			//if ((AC_IN_L) ||(IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4 
            {
                switch (NVDeventStatus)
                {                    
                    case 0x02:
                        ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
						//981004-200306-M-S
						if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                    {
						   if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on))) //981004-151204-M  
                           {	
                                       WTDP = 35;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD2
						            }
                                    else
                                    {
									   WTDP = 20;
                                       WTDP2 = 45;	
	                                   WTDP4 = 90; //0xD2  
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
	                                  WTDP4 = 90; //0xD2  
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
                                 ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB								 
				                 PD_Adapter_setting();                                            										
								 break;
						   #endif 
								
                            //992022-140922-M-E
                            default:
                                break;
                        }
            }
            //992022-140905-A-E

            //992022-141030-A-S to fix GPU frequency not recover when disable smartcooling
            else if (!AC_IN_L)//AC mode
            {
                AC_boost_Status = 0x03; //981004-160811-M from 0x05
				AC_boost_cnt1 = 0x00; //981004-150323-A
                AC_boost_cnt2 = 0x00; //981004-150323-A
				
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
			else if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))
			{
               ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
               PD_Adapter_setting();		 
            }		
            //992022-141030-A-E
            
        }
        PM1Step = 0;
    }
}
//981004-130703-A-E

void OEM_ACPI_Cmd_E0Data(void)

{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {		                
			SET_MASK(POWER_FLAG2, wlan_on); //EC RAM 200 OFFSET 2 BIT 6
            WLAN_EN = 1; 
            #if 0			
		    if (IS_MASK_SET(POWER_FLAG2, sci_on))
            {			
                WLAN_LED = 1; //981004-180731-R
			}
            #endif 			
        }
        else
        {		                
			CLEAR_MASK(POWER_FLAG2, wlan_on); 		
            WLAN_EN = 1; 		
            //WLAN_LED = 0;//981004-180731-R
        }
        PM1Step = 0;
    } 
}


void OEM_ACPI_Cmd_E1Data(void)
{
    if (PM1Step == 1)
    {
        if (PM1Data)
        {		    
			SET_MASK(POWER_FLAG1, bt_on); //EC RAM 201 BIT7
            BT_EN = 1;
			//981004-180731-R-S
			#if 0
			if (IS_MASK_SET(POWER_FLAG2, sci_on))
            {              		
                BT_LED = 1;
            }
			#endif
            //981004-180731-R-E			
        }
        else
        {		 
			CLEAR_MASK(POWER_FLAG1, bt_on);
            BT_EN = 0;			
			//BT_LED = 0; //981004-180731-R
        }
        PM1Step = 0;
    }
}

void OEM_ACPI_Cmd_E2Data(void)

{ 
   #if 0
    if (PM1Step == 1)
    {
        if (PM1Data)
        {
            PCIE2_PWREN_L = 0;       //ADD BEN 090422-S for 3.5G power saving
            Delay1MS(200);
            WLAN_DIS2_L = 1;			
//			G35_LED = HIGH;            //981004-090820-R		
            //POWER_FLAG2 |= 0x80;       //3.5G on
			SET_MASK(POWER_FLAG2, pcie2_on);
        }
        else
        {
            WLAN_DIS2_L = 0;
//			G35_LED = LOW;            //981004-090820-R
            Delay1MS(200);
            PCIE2_PWREN_L = 1;
            //POWER_FLAG2 &= 0x7F;       //3.5G off     //ADD BEN 090422-E for 3.5G power saving
			CLEAR_MASK(POWER_FLAG2, pcie2_on);
        }
        PM1Step = 0;
    }
#endif	 
}

//981004-150417-R-S
void OEM_ACPI_Cmd_E3Data(void)

{
    #if 0
    if (PM1Step == 1)
    {
        KB_CODE = PM1Data;
        switch (PM1Data)
        {
            case 1:          //US, T Chinese			 
                Scanner_Table_Pntr = &Rc_ROM_Tables; //0
                break;
            case 2:          //UI==>UK
                Scanner_Table_Pntr = &Rc_ROM_Tables; //4      
                break;
            case 3:          //Japanese
                Scanner_Table_Pntr = &Rc_ROM_Tables; //2
                break;
            case 4:          //Korea
                Scanner_Table_Pntr = &Rc_ROM_Tables; //4      
                break;
            case 5:          //Germany
                Scanner_Table_Pntr = &Rc_ROM_Tables; //4      
                break;
            default:
                break;
        }
        PM1Step = 0;
    } 
    #endif	
}
//981004-150417-R-E

//981004-130117-M-S
void OEM_ACPI_Cmd_E4Data(void)

{
    if (PM1Step == 1)                   
    { 
        //CCD_EN = 1;
        #if 1		
        if (PM1Data)                   
        {		                
			SET_MASK(POWER_FLAG1, ccd_on);
            CCD_EN = 1;		
        }
        else
        {		              
			CLEAR_MASK(POWER_FLAG1, ccd_on);
            CCD_EN = 0;			
        }
		#endif 
        PM1Step = 0;
    }                         
}
//981004-130117-M-E

void OEM_ACPI_Cmd_E5Data(void)

{ 
   
}

void OEM_ACPI_Cmd_E6Data(void)

{
    if (PM1Step == 1)                   
    {                             
        if (PM1Data)                   
        {
            //POWER_FLAG3 |= 0x20;       //Touchpad on			
			//SET_MASK(POWER_FLAG3, ps2_on); //981004-220706-R
            //PSCTL1 = 0x17; //981004-220706-R
        }
        else
        {
            //POWER_FLAG3 &= 0xDF;       //Touchpad off
			//CLEAR_MASK(POWER_FLAG3, ps2_on); //981004-220706-R
            //PSCTL1 = 0x11; //981004-220706-R
        }
        PM1Step = 0;
    }                        
}

//981004-130429-A-S
void OEM_ACPI_Cmd_E7Data(void)

{
    #if 1     
    if (PM1Step == 1)
    {
        USB_CHARGE = PM1Data;		     		
        switch (PM1Data)
        {
            case 0:
            USB_CHARGE = 0;
			break;

            case 1:
            USB_CHARGE = 1;
			break;

            case 2:          
            USB_CHARGE = 2;
			break;

            case 3:
            USB_CHARGE = 3;
			break;
        		
            default:
            USB_CHARGE = 0;
			break;
        }
        PM1Step = 0;
    }
#endif
}
//981004-130429-A-E

void OEM_ACPI_Cmd_E8Data(void)

{
   #if 0
    if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {		   
			SET_MASK(POWER_FLAG4, usb30_on);
            USB30_PWR = 1;		
        }
        else
        {		   
			CLEAR_MASK(POWER_FLAG4, usb30_on);
            USB30_PWR = 0;		
        }
        PM1Step = 0;		
    }
#endif	 
}

void OEM_ACPI_Cmd_E9Data(void)

{
    if (PM1Step == 1)                   
    { 
        if (PM1Data)                   
        {		   		  
			//SET_MASK(POWER_FLAG4, all_mute); //981004-150803-R                
            EC_AMP_MUTE_L = 1; //Mute => Unmute 981004-150803-M from 0 SM to turn off CODEC                     	
        }
        else
        {		   
			//CLEAR_MASK(POWER_FLAG4, all_mute); //981004-150803-R           
            EC_AMP_MUTE_L = 1; //Unmute           				
        }
        PM1Step = 0;		
    }                 
}

 //981004-220216-R-S for smart manager to disable windows key
void OEM_ACPI_Cmd_EAData(void)
{ 
    #if 0  
    if (PM1Step == 1)                   
    { 
        if (PM1Data)                   
        {		   
            SET_MASK(POWER_FLAG10, win_key_disable); //981004-131119-A
            Scanner_Table_Pntr = &Rc_ROM_Tables1;
        }
        else
        {		      
            CLEAR_MASK(POWER_FLAG10, win_key_disable); //981004-131119-A
            Scanner_Table_Pntr = &Rc_ROM_Tables;
        }
        PM1Step = 0;
    } 
    #endif	
}
//981004-220216-R-E

//981004-130506-R-S
void OEM_ACPI_Cmd_EBData(void)

{
    #if 0
    if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {		               
			SET_MASK(POWER_FLAG3, ac_usb_power_off);            		
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG3, ac_usb_power_off);          	
        }
        PM1Step = 0;		
    }
    #endif	
}
//981004-130506-R-E

void OEM_ACPI_Cmd_ECData(void)

{
    #if 0
    if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {		               
			SET_MASK(POWER_FLAG7, usb_charge_s4);			
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG7, usb_charge_s4);			
        }
        PM1Step = 0;		
    } 
	#endif
	
    #if 0
    if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {
           	SET_MASK(POWER_FLAG7, resume_from_rs); 				 	
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG7, resume_from_rs);          	
        }		
        PM1Step = 0;       		
    }
    #endif	
}


void OEM_ACPI_Cmd_EDData(void)
{
   #if 0
   if (PM1Step == 1)                   
    {         
        if (PM1Data)                   
        {		               
			SET_MASK(POWER_FLAG7, rapid_start_on);            		
        }
        else
        {		               
			CLEAR_MASK(POWER_FLAG7, rapid_start_on);          	
        }
        PM1Step = 0;		
    } 
   #endif	
}

//981004-131125-M-S
void OEM_ACPI_Cmd_EFData(void)
{  
    
}
//981004-131125-M-E

//----------------------------------------------------------------------------
// Hook function of ACPI command
//----------------------------------------------------------------------------
void Hook_ACPICommand(void)
{
#if ACPI_Smbus
	OSSMbusComd();		// ACPI SMBus command
#endif	
}

//-------------------------------------------------------------------------------
// parameter "QeventSCI" only, For a pulsed SCI
//------------------------------------------------------------------------------
void OEM_ACPI_Gen_Int(void)
{
    ACPI_Gen_Int(QeventSCI);
}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void ResetSCIEvent(void)
{
    SCI_Event_In_Index = 0;
    SCI_Event_Out_Index = 0;

    #if ACPI_QEventPending
    PD_SCI_Event_In_Index = 0;
    PD_SCI_Event_Out_Index = 0;
    #endif
    
    CLEAR_MASK(PM1STS,SCIEVT);

    CLEAR_MASK(CustomFlags,ECCheckBurstMode);  
}

/* ----------------------------------------------------------------------------
 * FUNCTION: ECQEvent -Setup cause flag for an SCI and start the ACPI_Timer.
 *
 * sci_number = 1 through 255.  The Host uses this number to determine the
 * cause of the SCI.
 * ------------------------------------------------------------------------- */
#if 0
void ECQEvent(BYTE sci_number, BYTE sci_mode)
{    
	
    #if ACPI_QEventPending
    if ((sci_mode==SCIMode_Normal) || (sci_mode==SCIMode_Pending))
    {
        if (sci_mode==SCIMode_Normal)
        {
            if (PD_SCI_Event_In_Index != PD_SCI_Event_Out_Index)
            {
                PendingECQEvent(sci_number);
                return;
            }
        }
    
        if (IS_MASK_SET(PM1STS, P_IBF) || IS_MASK_SET(KBHISR, IBF))
        {
            if (sci_mode == SCIMode_Pending)
            {
                if (PD_SCI_Event_Out_Index == 0x00)
                    PD_SCI_Event_Out_Index = PENDING_BUFFER-1;
                else
                    PD_SCI_Event_Out_Index--;
            }
            else
                PendingECQEvent(sci_number);
            return;
        } 
    }
    #endif
    
    ITempB05 = SCI_Event_In_Index;           //Get the input index.
	SCI_NUM = sci_number;
    ///RamDebug(sci_number);	//DEBUG //981004-140107-A	
    SCI_Event_Buffer[ITempB05] = sci_number; //Put the SCI number in the buffer.
    ITempB05++;                              //Increment the index.

    if (ITempB05 >= EVENT_BUFFER_SIZE) 
        ITempB05 = 0;

  	if (ITempB05 != SCI_Event_Out_Index)  // If the buffer is not full, update the input index.
        SCI_Event_In_Index = ITempB05;
    
    SET_MASK(PM1STS,SCIEVT);
    OEM_ACPI_Gen_Int();
}
#endif
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PendingECQEvent(BYTE sci_number)
{
    BYTE index;
    
    #if ACPI_QEventPending
    
	index = PD_SCI_Event_In_Index; 			    // Get the input index.
	PD_SCI_Event_Buffer[index] = sci_number;    // Put the SCI number in the buffer.
 	index++;    							    // Increment the index. 
 	if(index >= PENDING_BUFFER) 
	{
     	index = 0;
 	}
 											    // If the buffer is not full, update the input index.
  	if(index != PD_SCI_Event_Out_Index) 
	{
   		PD_SCI_Event_In_Index = index;
    }
    #endif
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Get_PendingECQEvent(void)

{
    BYTE sci_number;
    
    #if ACPI_QEventPending
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
	    if (PD_SCI_Event_Out_Index != PD_SCI_Event_In_Index)
	    {  
		    sci_number = PD_SCI_Event_Buffer[PD_SCI_Event_Out_Index];
    	    PD_SCI_Event_Out_Index++;
    	    if(PD_SCI_Event_Out_Index >= PENDING_BUFFER) 
		    {
           	    PD_SCI_Event_Out_Index = 0;
   		    }

            ECQEvent(sci_number, SCIMode_Pending);
	    }
    }
    #endif
}

//----------------------------------------------------------------------------
// Read EC ram Space 
//----------------------------------------------------------------------------
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
    uint8_t* ECPACEP;
	ECPACEP = &((*((unsigned char *)(0x20050400))));
	return *(ECPACEP+MapIndex);
}

//----------------------------------------------------------------------------
// Read EC ram Space 0x300
//----------------------------------------------------------------------------
BYTE Hook_ReadMapECSpace2(BYTE MapIndex)
{
    uint8_t* ECPACEP;
	ECPACEP = &((*((unsigned char *)(0x20050300))));
	return *(ECPACEP+MapIndex);
}

#if 0 //981004-231002-R
void SpecialFunc_01(void)
{

}
#endif

#if 0 //981004-221123-R
//----------------------------------------------------------------------------
// Do hook function when write EC ram Space 
//----------------------------------------------------------------------------
const sECRamSS code asECRamSS[] = 
{	
    {&MISC_FLAG1,    SpecialFunc_01		},		
};
#endif

#if 0 //981004-221123-R
void WriteECRamSpecialFunc(XBYTE *xdptr)        //81 EC write command
{
	BYTE index;
	index=0x00;
	while(index<(sizeof(asECRamSS)/sizeof(sECRamSS)))
	{
		if(xdptr == asECRamSS[index].addr)
		{
			(asECRamSS[index].hookfunc)();
			break;
		}
		index++;
	}
}
#endif

//981004-150422-M-S
//----------------------------------------------------------------------------
// Write EC ram Space 
//----------------------------------------------------------------------------
#if 0
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
	Tmp_XPntr=(ECRAM|MapIndex);
	*Tmp_XPntr = data1;

#if HookFucnofWriteECRam
    WriteECRamSpecialFunc(Tmp_XPntr);
#endif	
}
#endif

//----------------------------------------------------------------------------
// Write EC ram Space 
//----------------------------------------------------------------------------
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
	//992022-140107-M-S
	BYTE data_before;
	BYTE data_offset;
	BYTE device_on;
    static BYTE test_byte = 0;
	uint8_t* ECPACEP;
	ECPACEP = &((*((unsigned char *)(0x20050400))));
		
	data_before = *ECPACEP; //store original ECRAM 
	//data_before = test_byte;
	*ECPACEP = data1; //BIOS write ECRAM
//	test_byte = data1; //BIOS write ECRAM
	
	if (data1 == data_before)
	{
		if (data1 ^ data_before == 0x0D)
		{
		    EC_AMP_MUTE_L = 1; //981004-180926-A
		}	
	    return;
	}
	data_offset = data1 ^ data_before;

	device_on = (data1 & data_offset) ? 1 : 0;
 
	//for smartmanager, that BIOS to write ECRAM to turn on/off devices
	switch(MapIndex) 
	{
			case 0x01: //EC RAM 0x201

									 switch(data_offset)
									 {   
											
											case 0x20:  //EC 201 bit5  Cmd_7A USB CHARGE S3												
												     //device_on ? SET_MASK(POWER_FLAG1,usb_charge_s3):CLEAR_MASK(POWER_FLAG1,usb_charge_s3);				
												         break;		
											
											case 0x40:  //EC 201 bit6  Cmd_E4 CCD
												     CCD_EN = device_on ? 1 : 0;												     											
												         break;

											case 0x80:  //EC 201 bit7  Cmd_E1 BT
											         //device_on ? SET_MASK(POWER_FLAG1, bt_on):CLEAR_MASK(POWER_FLAG1, bt_on);//0x202 bit 7 for BT function
											         if(device_on)
								                     {
												        BT_EN = 1;
			                                               //if (IS_MASK_SET(POWER_FLAG2, sci_on)) //981004-180731-R
                                                              //BT_LED = 1; 
													 }
                                                     else
                                                     {
                                                        BT_EN = 1; //981004-200410-M from 0
			                                            //BT_LED = 0; //981004-180731-R 
                                                     }													 
												        break;

											default:
											break;
									 }
									 
									 break;
		    case 0x02: //EC RAM 0x202

									 switch(data_offset)
									 {
											 case 0x40://EC 202  bit6   Cmd_E0  WIFI
											          
                                                      //For audio to unmute when smartmanager on
													  #if 0
                                                      if ((IS_MASK_SET(Patch, woofer_patch)) && (IS_MASK_CLEAR(POWER_FLAG4, all_mute)))
                                                      {
                                                           EC_AMP_MUTE_L = 1;
                                                           CLEAR_MASK(Patch, woofer_patch);
                                                      } 
                                                      #endif													  
													  if(device_on)
								                      {
												          WLAN_EN = 1; 
                                                          //if (IS_MASK_SET(POWER_FLAG2, sci_on)) 
                                                              //WLAN_LED = 1; //981004-180731-R
													  }
                                                      else
                                                      {
                                                          WLAN_EN = 1; 
                                                          //WLAN_LED = 0; //981004-180731-R
                                                      }	
                                                      EC_AMP_MUTE_L = 1; //981004-180926-A 													  
															break;

											 default:
																 break;
									 }
									 
									 break;
		
			case 0x03: //EC RAM 0x203
				
									 switch(data_offset)
									 {
											 case 0x01://EC 203 BIT0    Cmd_EB  AC USB POWER OFF
													//device_on ? SET_MASK(POWER_FLAG3, ac_usb_power_off):CLEAR_MASK(POWER_FLAG3, ac_usb_power_off);					
															break;     
											 case 0x20://EC 203 BIT5    Cmd_E6  Touch pad											           
													  //device_on ? SET_MASK(POWER_FLAG3, ps2_on):CLEAR_MASK(POWER_FLAG3, ps2_on);																
														///PSCTL1	= device_on ? 0x17:0x11;								
															break;       

											 default:
															break;
									 }
									 
									 break;

			case 0x04: //EC RAM 0x204

									 switch(data_offset)
									 {
											 case 0x02://EC 204 BIT1    Cmd_E9  All_Mute
													  //device_on ? SET_MASK(POWER_FLAG4, all_mute):CLEAR_MASK(POWER_FLAG4, all_mute);    
													  EC_AMP_MUTE_L = device_on ? 0 : 1;
														    break;

											 default:
																 break;
									 }
									 
									 break;
			case 0x05: //EC RAM 0x205
					switch(data_offset)
					{
								default:
								    break;
					}									 
					break;
			case 0x06: //EC RAM 0x206

 	               switch(data_offset)
 	               {
				       case 0x40://EC 206 BIT6    Cmd_C0  GPU_on
							    device_on ? SET_MASK(POWER_FLAG6, GPU_on):CLEAR_MASK(POWER_FLAG6, GPU_on);					
 	                                 break;

 	                   default:
 	                             break;
 	               }
                 
 	               break;
  			case 0x07: //EC RAM 0x207

 	               switch(data_offset)
 	               {

 	                 	case 0x04://EC 207 BIT2    Cmd_7B  usb_charge_s4 
								//device_on ? SET_MASK(POWER_FLAG7, usb_charge_s4):CLEAR_MASK(POWER_FLAG7, usb_charge_s4); //981004-190801-R					
 	                                break;     

 	                    default:
 	                                break;
 	               }
                 
 	               break;
 	        case 0x08: //EC RAM 0x208

 	               switch(data_offset)
 	               {	                
 	                    case 0x40: //EC 208 BIT6    Cmd_DF   Smart Cooling flag On/Off
 	                             if(device_on)
								 {
								    FanDACLevel = 0;									
								 }	
								 else
								 {
									CLEAR_MASK(POWER_FLAG6, sv_thrt_on);
                                    ECQEvent(SCI_SV_THROFF, SCIMode_ACPI_SMBus); //0x97                        
                                    //AC_IN_L == 0 ? ECQEvent(SCI_P0, SCIMode_ACPI_SMBus) : ECQEvent(SCI_P1, SCIMode_ACPI_SMBus); //981004-190822-R

                                    //if (AC_IN_L) //battery mode
									//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
									if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
                                    {
                                        switch (NVDeventStatus)
                                        {                  
                                            case 0x02:
                                                     ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
													 //981004-200306-M-S
													 if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	                                                 {
						                                if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on))) //981004-151204-M  
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
                                 else
                                 {
                                     WTDP = 15; 
									 WTDP2 = 45; 
                                     WTDP4 = 90;
                                 }                                                     										
								 break;
                           
						    #if 0
                            case 0x0B:                                    
                                 ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB								 
				                 PD_Adapter_setting();                                              										
								 break;
						   #endif 
                           default:
                              break;
                         }                                      								
	                    }
					    else if (!AC_IN_L)//AC mode
                        {
                           AC_boost_Status = 0x03; //981004-160811-M from 0x05
				           AC_boost_cnt1 = 0x00; //981004-150323-A
                           AC_boost_cnt2 = 0x00; //981004-150323-A								
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
			           else if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))
			           {
                           ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
                           PD_Adapter_setting();		 
                       }
				}	 	                        	
 	                    default:
 	                             break; 	                       
                    }
 	                break;
								 
		    case 0x09: //EC RAM 0x209

 	               switch(data_offset)
 	               {
				        case 0x08: //EC 209 BIT3    Cmd_95/A5   LVDS ON/OFF								
                                    EC_BKLOUT = device_on ? 0 : 1;	//981004-160305-A                                    								
 	                                break;
									 
 	                    case 0x10: //EC 209 BIT4    Cmd_D1   rtc_wake_support
								 //device_on ? SET_MASK(POWER_FLAG9, rtc_wake_support):CLEAR_MASK(POWER_FLAG9, rtc_wake_support); 															 
 	                                 break;

 	                   default:
 	                             break;
 	               }
                 
 	               break;
			case 0x0A: //EC RAM 0x20A

 	               switch(data_offset)
 	               {

 	                   case 0x01://EC 20A BIT0     Cmd_94   Full speed Fan
								//device_on ? SET_MASK(POWER_FLAG10, fullspeed_fan):CLEAR_MASK(POWER_FLAG10, fullspeed_fan); 															 
 	                                break;
								 
						case 0x02://EC 20A BIT1    Cmd_62   Disable Fn key
								//981004-180731-R-S 
								#if 0
								if(device_on)
								{
								    WLAN_LED = 0; 
                                    BT_LED = 0; 									
								}	
								else
								{
									WLAN_LED = IS_MASK_SET(POWER_FLAG2, wlan_on) ? 1 : 0; 
                                    BT_LED = IS_MASK_SET(POWER_FLAG1, bt_on) ? 1 : 0; 	 
								}
								#endif
								//981004-180731-R-E
								    break;							
						case 0x04://EC 20A BIT2    Cmd_63   Disable bt key
								//981004-180731-R-S
								#if 0
								if(!device_on)
									BT_LED = IS_MASK_SET(POWER_FLAG1, bt_on) ? 1 : 0;
								else
								BT_LED = 0;
                                #endif
                                //981004-180731-R-E								
 	                                break;
                        case 0x80://EC 20A BIT7    Cmd_EA   Disable Windows Key
								//device_on ? SET_MASK(POWER_FLAG10, win_key_disable):CLEAR_MASK(POWER_FLAG10, win_key_disable); 
								 //Scanner_Table_Pntr = device_on ? &Rc_ROM_Tables1:&Rc_ROM_Tables;	//981004-220216-R												
 	                                break;
									
 	                   default:
 	                                break;
 	               }
                 
 	               break;
 	    
            case 0x69: //EC RAM 0x269 for smart charge Cmd_E7
 	   
 	               switch (data1)
 	               {
 	                    case 0:
                            USB_CHARGE = 0;
			                   break;

                        case 1:
                            USB_CHARGE = 1;
			                  break;

                        case 2:          
                           USB_CHARGE = 2;
			                  break;

                        case 3:
                           USB_CHARGE = 3;
			                  break;
        		
                        default:
                           USB_CHARGE = 0;
			                  break;
 	              }								
 	              break; 
			
			//981004-211217-R-S
			#if 0
            case 0xB5: //EC RAM 0x2B5 for GPU overclock
 	   
 	               switch (data1)
 	               {
 	                    case 0:
                            GPU_OC1 = 0; //GPIO D1
							GPU_OC2 = 1; //GPIO D5
							GPU_OC3 = 0; //GPIO E0
							GPU_OC4 = 0; //GPIO E5
			                   break;

                        case 1:
                            GPU_OC1 = 0;
							GPU_OC2 = 0;
							GPU_OC3 = 0;
							GPU_OC4 = 0;
			                   break;

                        case 2:          
                            GPU_OC1 = 1;
							GPU_OC2 = 0;
							GPU_OC3 = 0;
							GPU_OC4 = 0;
			                  break;

                        case 3:
                            GPU_OC1 = 0;
							GPU_OC2 = 0;
							GPU_OC3 = 1;
							GPU_OC4 = 0;
			                  break;
        		        
                        case 4:
                            GPU_OC1 = 0;
							GPU_OC2 = 0;
							GPU_OC3 = 0;
							GPU_OC4 = 1;
			                  break;
							  
                        default:
                            GPU_OC1 = 0;
							GPU_OC2 = 1;
							GPU_OC3 = 0;
							GPU_OC4 = 0;
			                  break;
 	              }								
 	              break;
			#endif	  
            //981004-211217-R-E
                				  
			//981004-161202-A-S
			case 0xA2:
					fanfunc_SET(SetFAN_LV,FAN_ON,FAN_DW);
					FAN_DW =0xff;
						break; 
						
			case 0xA3:	
					fanfunc_READ(ReadFAN_LV);
				    ReadFAN_LV = 0x0f;
			//981004-161202-A-E
						break;
			
            //981004-200721-A-S			
            case 0xB6: //EC RAM 0x2B6
                Hook_Intel_Cmd();
                break;
			//981004-200721-A-E	
				
            case 0xD7: //EC RAM 0x2D7 for smart charge Cmd_EF (Set keyboard backlight 0/2/6)
									//KB_Level= data1; //981004-180712-R
									//DCR6 = KBbclCtrl(KB_Level); //981004-180712-R									
								 
 	               /*
 	               switch (data1)
 	               {
 	                    case 0:
                              KBlightcnt1 = 0x00;
                              KB_BR_Level = 0x00;
                              DCR6 = 0x00;
			                     break;

                        case 2:
                              KBlightcnt1 = 0x01; 
                              KBlightcnt2 = KBlightcnt;
                              KB_BR_Level = 0x01;
                              DCR6 = KBbclCtrl(1);
			                     break;

                        case 6:          
                              KBlightcnt1 = 0x02;
                              KB_BR_Level = 0x02;
                              DCR6 = KBbclCtrl(2);
			                     break;

                        default:
                               KBlightcnt = 0;
							   KB_BR_Level = 0x00;
                               DCR6 = 0x00;
			                     break;
 	              }		
									*/
 	              break;    				  
 	       
		   default:
 	               break;
 	}
  //for smartmanager, that BIOS to write ECRAM to turn on/off devices
	//992022-140107-A-E

#if HookFucnofWriteECRam
    WriteECRamSpecialFunc(Tmp_XPntr);
#endif	
}
//981004-150422-M-E

#if ACPI_Smbus
//----------------------------------------------------------------------------
// process OS SMBus command
//----------------------------------------------------------------------------
// ACPI response to writes to SMBus Protocol register. 
const FUNCT_PTR_B_V code vOSSMbusComd_table[16] =
{								//the low nibble of SMB_PRTC
	DummyFunction,		//0x00	
	DummyFunction,		//0x01
	DummyFunction,		//0x02-Write Quick Command 
	DummyFunction,		//0x03-Read Quick Command
	DummyFunction,		//0x04-Send Byte
	DummyFunction,		//0x05-Receive Byte
	vOSSMbusWBYTE,		//0x06-Write Byte
	vOSSMbusRByte,		//0x07-Read Byte
	vOSSMbusWWord,		//0x08-Write Word
	vOSSMbusRWord,		//0x09-Read Word
	vOSSMbusWBlcok,		//0x0A-Write Block
	vOSSMbusRBlcok,		//0x0B-Read Block
	DummyFunction,		//0x0C-Process Call
	DummyFunction,		//0x0D-Write Block-Read Block Process Call
	DummyFunction,		//0x0E
	DummyFunction		//0x0F
};

void OSSMbusComd(void)
{
	if((SMB_PRTC != 0x00)&&(SMB_ADDR == 0x16))
	{
  		SMB_STS = 0x00;
     	SMB_PRTC &= 0x0F;
      	if((vOSSMbusComd_table[SMB_PRTC])())
      	{
     		SMB_STS = 0x80;
      	}
		else
		{
			SMB_STS = 0x5A;
		}
      	SMB_PRTC = 0x00;
        
        if(IS_MASK_SET(SYS_MISC1,ACPI_OS)) 
        {
            ECQEvent(PowerManagement, SCIMode_ACPI_SMBus);
        }
        else
        {
            ECQEvent(PowerManagement, SCIMode_Force);
        }
  	}
}

BYTE vOSSMbusWBlcok(void)
{
  	return (bRSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vOSSMbusRBlcok(void)
{
  	return (bRSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vOSSMbusRByte(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusRWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusWBYTE(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusWWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

void DummyFunction(void)
{

}
#endif

//981004-200721-A-S
void Hook_Intel_Cmd(void)
{
    if (xEC_CMDR == 0x2C) //EC RAM 0x2B8
    {
        /* BIOS Enter Modern Standy */
        //GPCRF6 = OUTPUT;
        GPIO_Set_IO(120,1);
        //PECI_EC_LO();
        PECI->CTRL_b.EN = 0;
		//981004-230428-A-S		 
	    PWR_LED2_L = 1;
		//SET_GPO_KSO6_LO(); //KSOLGOENR 0X1D0E BIT6 => 0 //HDD LED
        GPIO_Set_IO(47,1);
        GPIO_Write(47,0);
	    if (!LID_L) //981004-230829-M
        {	     			
	       USB_KBD_PWR = 0;
		}
        else
        {
		  USB_KBD_PWR = 1;	
		}			
		SET_MASK(POWER_FLAG12, EC_modern_stby);	    
				
		//SET_GPO_KSO7_HI(); //981004-231002-A
        GPIO_Set_IO(48,1);
        GPIO_Write(48,1);
		SET_MASK(POWER_FLAG6, adjustfan);
	    FanRPM1=0x00;  
	    FanRPM2=0x00;
        if (IS_MASK_CLEAR(POWER_FLAG9, DGPU_Mode)) //981004-231128-A
        {			
		    DDS_PANEL_RST = 0; //GPIO H3 			
        }			
		//981004-230428-A-E
		//SET_GPO_KSO12_LO(); //981004-231017-A //EC_KBLED_EN
        GPIO_Set_IO(56,1);
        GPIO_Write(56,0);
	    //SET_GPO_KSO13_LO(); //981004-231017-A //EC_LBLED_EN
        GPIO_Set_IO(57,1);
        GPIO_Write(57,0);
		//SET_GPO_KSO0_LO(); //981004-231120-A PER EE request
        GPIO_Set_IO(41,1);
        GPIO_Write(41,0);
        //SET_GPO_KSO3_LO(); //DMIC SEL
        GPIO_Set_IO(44,1);
        GPIO_Write(44,0);		
    }
    else if (xEC_CMDR == 0x2D)
    {
        /* BIOS Exit Modern Standy */
       /// SET_ExitMS(0x2D, 2);
      ///  Init_PECI();
		//981004-230428-A-S	     
	    
		//981004-240529-A-S
		if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3
	    {
           PWR_LED2_L = 0;
          // SET_GPO_KSO6_HI(); //KSOLGOENR 0X1D0E BIT6 => 1 //HDD LED
            GPIO_Set_IO(47,1);
            GPIO_Write(47,1);		
        }
		//981004-240529-A-E
		
        if (!LID_L) //981004-230829-M
        {	     			
	       USB_KBD_PWR = 0;
		}
        else
        {
		  USB_KBD_PWR = 1;	
		}			
        //SET_GPO_KSO7_HI(); //981004-221107-A
        GPIO_Set_IO(48,1);
        GPIO_Write(48,1);
		KSO7_CNT = 0; //981004-221111-A
	    CLEAR_MASK(POWER_FLAG12, EC_modern_stby);
		
		
		
		CLEAR_MASK(POWER_FLAG6, adjustfan); 
		FanRPM1=0x39; 
	    FanRPM2=0x39;
		//981004-221028-A-E
		//SET_GPO_KSO12_HI(); //981004-231017-A //EC_KBLED_EN
        GPIO_Set_IO(56,1);
        GPIO_Write(56,1);
		//SET_GPO_KSO13_HI(); //981004-231017-A //EC_LBLED_EN
        GPIO_Set_IO(57,1);
        GPIO_Write(57,1);
		//SET_GPO_KSO0_HI(); //981004-231120-A PER EE request
        GPIO_Set_IO(41,1);
        GPIO_Write(41,1);
		//SET_GPO_KSO3_HI(); //DMIC SEL
        GPIO_Set_IO(44,1);
        GPIO_Write(44,1);
		DDS_PANEL_RST = 1; //GPIO H3 //981004-231128-A
    }
    xEC_CMDR = 0;
}
//981004-200721-A-E


