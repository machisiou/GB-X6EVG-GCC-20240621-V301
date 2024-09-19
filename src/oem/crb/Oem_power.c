#include <stdint.h>
#include "system/Memory.h"
#include "system/peripheral.h"
#include "oem/crb/Oem_power.h"
#include "oem/crb/Oem_timer.h"
#include "hal/PerVW.h"
#include "hal/GPIO.h"
#include "RTK_Include.h"
#if 0
//-----------------------------------------------------------------------------
//  The variable of Sx -> S0
//-----------------------------------------------------------------------------
void SX_S0CommVar(void)
{
	//SysPowState = SYSTEM_S0;
	SystemState = SYSTEM_S0;
	InitDevice();
	///ResetSCIEvent();

	CheckPowerStateIndex = 0x00;
	///Enable port80 
}
//-----------------------------------------------------------------------------
//  The OEM variable of S0 -> Sx
//-----------------------------------------------------------------------------
void OEM_S0_SXCommVar(void)
{
	CheckPowerStateIndex = 0x00; //981004-130116-A
    BIT_CLR(SYS_MISC1,ACPI_OS); //981004-130116-A
		
	//981004-130116-M-S
	PCH_PWROK = 0;
    ALL_SYS_PWRGD = 0;
	//KBRST_L = 0; //981004-220615-R
    EC_AMP_MUTE_L = 0; //981004-210720-M from 1
	BIT_CLR(POWER_FLAG2, fan_on);
	//CLEAR_MASK(POWER_FLAG10, fullspeed_fan); //981004-190813-S to S3
	//CLEAR_MASK(POWER_FLAG8, smart_cooling_on); //981004-190813-S to S3
	//CLEAR_MASK(POWER_FLAG9, super_quiet); //981004-190813-S to S3
	BIT_CLR(POWER_FLAG4, resume_from_s3); //981004-190612-A   
    BT_EN = 0;
	//WLAN_EN = 0; //981004-180731-R
	//BT_LED = 0; //981004-180731-R		
	//WLAN_LED_EN = 0; //981004-180731-R
    //WLAN_LED = 0; //981004-180731-R
    //HD_LED = 0; //981004-180731-R
    FanDACLevel = 0;	
	PWM_Set_Duty(0,0);//DCR0 = 0x00;
	PWM_Set_Duty(3,0);//DCR3 = 0x00; //981004-140930-A
    //DCR6 = 0x00; //981004-200724-R
   
   //981004-211119-A-S	
    //Thermal_IC_CNT3 = 0; //981004-221130-R
	//Thermal_IC_CNT1 = 0; //981004-221130-R
    //CLEAR_MASK(POWER_FLAG7, Thermal_IC_hot1); //981004-221130-R
    //981004-211119-A-E
    
	//981004-211208-A-S
	#if 0
    Learn_mode_CNT1 = 0;
	Learn_mode_CNT3 = 0;
	Learn_mode_CNT5 = 0;
	Learn_mode_CNT2 = 0;
	Learn_on_CNT = 0;
    BIT_CLR(EC_Flag5, learn_mode0);
	BIT_CLR(EC_Flag5, learn_mode1);
	BIT_CLR(EC_Flag5, learn_mode2);
	BIT_CLR(EC_Flag5, learn_on1);
	BIT_CLR(EC_Flag5, learn_on2);
	#endif
    //981004-211208-A-E	
	
	//981004-190318-M-S
    if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w))
	{
		WTDP = 157; //981004-230915-M
	    WTDP2 = 157;
	    WTDP4 = 246; //i7 CPU
	}
	else
	{
		WTDP = 157; //981004-230915-M
	    WTDP2 = 157;
	    WTDP4 = 246; //i9 CPU
    }			
    //981004-190318-M-E
    //KBlightcnt = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)	
    //KBlightcnt1 = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)
    //KB_BR_Level = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)
	FINAL_TEMP2 = 0;
    PECI_CPU_temp = 0; //981004-150414-A
    GPU_TMPR = 0; //981004-150414-A
	//GPU_TMPR2 = 0; //981004-180712-R
    FANLVDNCNT =0; //981004-131203-A
    FANLVDNCNT1 =0; //981004-131203-A	
	FanLevelTemp = 0; //981004-201105-A 
    FanUpCNT0 = 0; //981004-201105-A  
    FanDnCNT0 = 0; //981004-201105-A
    FanUpCNT3 = 0; //981004-201105-A   
    FanDnCNT3 = 0; //981004-201105-A 
	FanLevelTemp2 = 0; //981004-201105-A 	
    CCD_EN = 1;   	
	//BIT_CLR(KBHISR,SYSF); //981004-130116-A
    //Ccb42_SYS_FLAG=0;  //981004-130116-A      		
	BIT_CLR(POWER_FLAG2, SLP_S3_ON); //981004-121225-A
	//CLEAR_MASK(POWER_FLAG9, lcd_off); //981004-130314-M
	//Boot_bobocnt =0; //981004-130416-A
	BIT_SET(POWER_FLAG9, lcd_off); //981004-170405-A
	EC_BKLOUT = 0; //981004-130506-A
	Lid_close_cnt =0; //981004-170405-A
    Sci_on_20sec_cnt = 0; //981004-150810-A

    //GPCRA4 = OUTPUT+PULL_DW; //981004-201223-M from OUTPUT+PULL_DW	

    PWR_LED2_L = 1; //981004-210104-M 	
    
    //981004-210617-A-S
    #if 1    
	//To shutdown Light sensor	
    LSCTRL = 0x00; //981004-150821-M for LTR-F216A Light sensor	
    //(bRWSMBus(SMbusChB, SMbusWB, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); //(EC RAM : 0x28F)
	SMBUS_RW_B(1, WriteByte,LightSensorAddr,CONTROL,&LSCTRL);
    #endif
	
	//Thermal_IC_ShutDn = 0x01; //981004-231108-R
	//(bRWSMBus(SMbusCh4, SMbusWB, Thermal1_Addr, Thermal1_Config, &Thermal_IC_ShutDn , SMBus_NoPEC)); //981004-231108-R   		
    //981004-211117-A-E
	
	BIT_CLR(POWER_FLAG4, bat_cap_first_chk); //981004-170412-A
	BIT_CLR(POWER_FLAG4, bat_cap_downgrade); //981004-170412-A
    BAT_FIRST_CHK_cnt = 0; //981004-170412-A
    BAT_DOWNGRADE_cnt = 0; //981004-170412-A
   
    FAN_TEMPUP_cnt = 0;
    FAN_TEMPDN_cnt = 0;	
	
	//Heavy_Load_cnt = 0; //981004-181107-R
	
	//GPCRH1 = ALT; //981004-221202-M from INPUT SMBUS D
	GPIO_Func_Mode(100,1);
	//GPCRH2 = ALT; //981004-221202-M from INPUT SMBUS D
	GPIO_Func_Mode(101,1);
	//FAKE_ACOUT_CNT = 0;	//981004-181128-A
	//FAKE_ACOUT_CNT2 = 0;	//981004-181128-A
	//BIT_CLR(POWER_FLAG6, ECRAM_80patch); //981004-181216-A
    //BIT_CLR(POWER_FLAG9, os_read_ecram_on); //981004-181216-A	
    BIT_CLR(POWER_FLAG2, LED_TEST_ON); //981004-190109-A	
	BIT_CLR(POWER_FLAG6, sv_thrt_on);//981004-190329-A //EC RAM 206 bit 7
	BIT_CLR(POWER_FLAG5, Linux_fanon);//981004-200108-A
	//981004-19090801-R-S
	//GPU_OC(0);//LV0 //981004-220330-R
	
	//981004-220923-R-S
	#if 0
    //GPU_TEMP_CNT1 = 0; 
	//BIT_CLR(POWER_FLAG13, GPU_temp_80); //EC RAM 20D bit 4
	//GPU_TEMP_CNT2 = 0;
	//CLEAR_MASK(POWER_FLAG13, GPU_temp_85); //EC RAM 20D bit 5
	#endif
	//981004-220923-R-E
	
	//981004-190801-R-E
    //BIT_CLR(POWER_FLAG6, bat_led_on); //981004-200724-R	
	
	//981004-221025-A-S
	BIT_CLR(EC_Flag4, nv_db20_lv0); 
    BIT_CLR(EC_Flag4, nv_db20_lv1); 
    BIT_CLR(EC_Flag4, nv_db20_lv2);
    BIT_CLR(EC_Flag4, nv_db20_lv3);
	BIT_CLR(EC_Flag4, nv_db20_lv4);
    //981004-221025-A-E	
			
    //981004-231002-A-S
	//BIT_CLR(KSOH1, BIT0); //KSO 8 //SD_RST_AUX
	//BIT_CLR(KSOH1, BIT1); //KSO 9 //EC_SSDA_PWR_EN
	//BIT_CLR(KSOH1, BIT2); //KSO 10 //EC_SSDB_PWR_EN
	//BIT_CLR(KSOH1, BIT3); //KSO 11 //EC_WLAN_PWR_EN
	//BIT_CLR(KSOH1, BIT4); //KSO 12 //EC_KBLED_EN
	//BIT_CLR(KSOH1, BIT5); //KSO 13 //EC_LBLED_EN
	//981004-231002-A-E
	//SET_GPO_KSO12_LO(); //981004-231017-A //EC_KBLED_EN
	//SET_GPO_KSO13_LO(); //981004-231017-A //EC_LBLED_EN
	//SET_GPO_KSO0_LO(); //981004-231120-A PER EE request	
}

//-----------------------------------------------------------------------------
//  The variable of S0 -> Sx
//-----------------------------------------------------------------------------
void S0_SXCommVar(void)
{
#ifdef PECI_Support
///    PECI_ClearPSTVariables();
#endif
    
#if TouchPad_only
    //PowerOffClearTPPendingData();
#endif        

    //InitSMBus(); //981004-120103-R

    OEM_S0_SXCommVar();
}
static const uint32_t G3_S5_PStbl[] =
{
//	pin num, delay time
//	255,	1,			// delay 20ms
	87,		0,			// on EC_EN_V5A
	122,	0,			// on 3.3A_EN
	96,		0,			// on USB_V5A_EN
	121,	1,			// on USB_EN_EC
	114,	100,				//AC_Present
	//38,0,				//dGPU_HOLD_EC_RST_L
	86,		0,			// on EC_CLR_LATCH
	255,	100,			// delay 1ms
};

void G3_S5_PS(void)
{
	uint8_t index;
	debug0=0xFF;
	ESPI->ESPICFG = 0x0000000F;

	#if 1
	//_Delay_1ms(85);
	for(index=0;index<(sizeof(G3_S5_PStbl)>>2);) {
		if(G3_S5_PStbl[index] == 0xFF) {
			index++;
			_Delay_1ms((uint8_t)G3_S5_PStbl[index++]);
		}
		else if(G3_S5_PStbl[index] != 0xFE){
			GPIO_Write(G3_S5_PStbl[index++],1);
			_Delay_1ms((uint8_t)G3_S5_PStbl[index++]);
		}else {
			index++;
			while(!GPIO_Read(G3_S5_PStbl[index])) {}
			index++;
		}
	}
	#endif
	#if 0 
	EC_CLR_LATCH = 0;//EC_CLR_LATCH_HIGH();//GPIO_Write(87,1);
	//_Delay_1ms(10);
	EC_EN_V5A = 1;// EC_EN_V5A_HIGH();// GPIO_Write(122,1);
//	_Delay_1ms(10);
	USB_V5A_EN = 1;//GPIO_Write(96,1);
	USB_EN_EC = 1;//GPIO_Write(121,1);
//	_Delay_1ms(10);
	AC_PRESENT = 1;//AC_PRESENT_HIGH();//GPIO_Write(97,1);
	PWR_PULSE_L = 1;//PM_PWRBTN_EC_HIGH();//GPIO_Write(114,1);
	_Delay_1ms(10);
	//EC_S3_DDR5_EN = 0;//EC_S3_DDR5_EN_LOW();
	while(!VCCIO_PWRGD());
	RSMRST_L = 1; //RSMRST_HIHG();
	// VW
//	ESPI->EVSTS = 0x00003FFFA;
#endif
	
//	debug0=0x01;
	// Check if VW Enable
	while(!GetVWEnable) {}
//	debug0=0x02;

	VW_Set_Index(0x05, 0x99);	/* Set boot load down */
	while(!GetSus_warn) {}
	VW_Set_Index(0x40, 0x11);	/* Set Sus_ack */
//	debug0=0x03;
	SystemState = SYSTEM_S5;
	//PM_PWRBTN_EC_LOW();
	PWR_PULSE_L = 0;	
	#if SUPPORT_GBITEM_23		
	if(IS_BIT_SET(POWER_FLAG13, HDA_SDO_BIOS))  
    {
        //HDA_SDO = 1; 
		GPIO_Write(128,1);
    }
	BIT_CLR(POWER_FLAG13, Flash_ME_ON); 	
	#endif
	
	BIT_CLR(POWER_FLAG1, enter_S4); 
    BIT_CLR(POWER_FLAG1, enter_S3); 	
	BIT_SET(POWER_FLAG2, SLP_S4_ON);
    BIT_SET(POWER_FLAG2, SLP_S3_ON);
	BIT_SET(POWER_FLAG7, PPAB_ON); //EC RAM 0x207 bit2 //981004-221025-A //981004-221228-A
	patchACout = 0;		
	_Delay_1ms(100);
	//PM_PWRBTN_EC_HIGH();
	PWR_PULSE_L = 1;
}

void S5_S0_PS(void)
{
	//SystemState = SYSTEM_S5S0;

	//GPIO_Write(22,1);			// PWR_LED
	// re-check VW ready and suswarm
	//	GPIO_Write(114,0);
	//_Delay_1ms(50);
//	GPIO_Write(114,1);
	while(!GetVWEnable) {}
	while(!GetSus_warn) {}
	//GPIO_Write(114,0);			// PM_PWRBTN press
	//_Delay_1ms(30);


	//while(!GetSlp_S5) {}		// wait VW SLP_S4
	//GPIO_Write(89,1);			// on SUSC_EC
	//GPIO_Write(34,1);			// on SUSC_EC
	//GPIO_Write(90,1);			// on 1P05V
	//GPIO_Write(35,1);			// on 1P05V
	BIT_CLR(POWER_FLAG1, enter_S4); 
    BIT_CLR(POWER_FLAG1, enter_S3); 	
	BIT_SET(POWER_FLAG2, SLP_S4_ON);
    BIT_SET(POWER_FLAG2, SLP_S3_ON);
	BIT_SET(POWER_FLAG7, PPAB_ON); //EC RAM 0x207 bit2 //981004-221025-A //981004-221228-A
	while(!GetSlp_S3) {}		// wait VW SLP_S3
		
	//GPIO_Write(114,1);			// PM_PWRBTN release	
	SetSCIHigh;					// set SCI high
	SetSMIHigh;					// set SMI high
	VW_Set_Index(0x00, 0x80);	
			/* Set Sus_ack */
	//_Delay_1ms(5);

	_Delay_1ms(21);
	GPIO_Write(116,1);			// ALL_SYSTEM_PWRGD	
	//while(!GPIO_Read(76)) {}	// wait ALL_SYSTEM_PWRGD
	SetRCINHigh;				// set RCIN_L = 1
	//_Delay_1ms(1);

	while(!GPIO_Read(117)) {}	// wait IMVP9P1_PWRGD
			
	GPIO_Write(19,1);
	//_Delay_1ms(1);
	//GPIO_Write(104,1);			// on PM_PWROK
	_Delay_1ms(100);
	//GPIO_Write(105,1);			// on PM_SYSPWROK
	GPIO_Write(125,1);			// on PM_SYSPWROK
	while(!GetPLTRST) {}		// wait VW PLTRST
	//GPIO_Write(1,1);			// on LCD_BACKOFF
	//GPIO_Write(30,1);			// on OP_SD
	
	#if SUPPORT_DEBUG_CARD
	INIT_TM1650();
	#endif
	//dGPU_HOLD_EC_RST_LOW();
	dGPU_HOLD_EC_RST_L = 0;
	if ((AC_IN_L) &&(IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4  //battery mode	
	{	   
	   //H_PROCHOT_HIGH; //981004-210401-M from 0
	   H_PROCHOT_L = 1;
	}
	else
	{	  
      //H_PROCHOT_LOW; //981004-210401-M from 1  
	  H_PROCHOT_L = 0;    
	}

	WTDP4 = 20; //981004-210401-A
	//pd1_ti_check_version(); //981004-210611-A Raymond will implement this function
    BIT_CLR(EC_Flag2, pdchgcur_step1); //981004-230621-A-S
	BIT_CLR(EC_Flag2, pdchgcur_step2);
	BIT_CLR(EC_Flag2, pdchgcur_step3);
	BIT_CLR(EC_Flag2, pdchgcur_step4);
	CHGCUR_STEP_cnt2 = 0; //981004-230621-A-E
	SMBSW_RST_HIGH;	
	GPIO_Write(45,1);
	SystemState = SYSTEM_S0;
	GPIO_Write(27,0);
	
	 SCI_Event_In_Index = 0;
    SCI_Event_Out_Index = 0;
	InitDevice();

}

void S0_S5_PS(void)
{
	#if SUPPORT_GBITEM_23	
	if(IS_BIT_CLR(POWER_FLAG13, Flash_ME_ON)) //981004-181221-M  
    {
		ME_CNT = 0;   
        HDA_SDO = 0;
        BIT_CLR(POWER_FLAG13, HDA_SDO_BIOS);
    }
	#endif
	
	SystemState = SYSTEM_S5;
	S0_SXCommVar();

	///IER1 &= 0xF7; 
	GPU_TMPR = 0;
	BIT_CLR(POWER_FLAG1, power_on);	
	BIT_CLR(POWER_FLAG4, pstate_off); 		
    BIT_CLR(POWER_FLAG7, dgpu_9Aon); //981004-120425-A    
	//PollingGP12 = 0; //981004-131111-A //981004-150417-R    
    //BIT_CLR(POWER_FLAG8, f2_press); //981004-120911-A
    //BIT_CLR(POWER_FLAG8, f9_press); //981004-120911-A
	//BIT_CLR(POWER_FLAG8, f12_press); //981004-120911-A	
	//BIT_CLR(POWER_FLAG8, f10_press); //981004-121017-A
    POWER_FLAG2 = POWER_FLAG2 & 0xCF; //Clear throttling on and SCI on /981004-210312-M
    //POWER_FLAG2 = POWER_FLAG2 & 0xDF; //Clear throttling on //981004-210127-A-M from 0xCF
	///CLEAR_MASK(KBHISR,SYSF);	        
    BIT_SET(POWER_FLAG1, enter_S4);
	//SET_MASK(POWER_FLAG3, S5_normal_shutdn); //981004-150417-R
	//DoUSBCharge(); //981004-130506-A
    BIT_CLR(POWER_FLAG2, SLP_S4_ON);	
    NVDeventStatus = 0x01; //992022-140904-A
    //NVcnt1 = 0x00; //981004-151019-R
    //NVcnt2 = 0x00; //981004-151019-R
	///Timer5msCnt = 0;
	//GPIO[25]. = output + pulldown

	GPIO_Set_IO(25,1);
	GPIO_Config(25,0,0,1);

	BAT_LED_L = 1;//BAT_LED_HIGH;
	//GPIO[27]. = output + pulldown
	GPIO_Set_IO(27,1);
	GPIO_Config(27,0,0,1);
	PWR_LED2_L = 1;//PWR_LED2_HIGH;
	GPIO_Set_IO(92,0);
	GPIO_Config(92,0,0,1);
	GPIO_Set_IO(93,0);
	GPIO_Config(93,0,0,1);
	///ZTIER = 0x00;
    BIT_CLR(ProcsH, ProcsH_scion20sec);  //992022-130731-A patch for Max request
    ProcsH_scion_cnt = 0;  //981004-131030-A patch for Max request

    BIT_CLR(POWER_FLAG10, scion_ac_in); //992022-140904-A
    SCI_on_AC_in_cnt = 0; //992022-140904-A

    BIT_CLR(POWER_FLAG10, sci_on_20sec); //992022-140904-A
    Sci_on_20sec_cnt = 0; //992022-140904-A
	
	//EC_S3_DDR5_EN = 1;//EC_S3_DDR5_EN_HIGH();
	USB_EN_EC = 0;
	USB_V5A_EN = 0;
	DDS_PANEL_RST = 0;//EC_S3_DDR5_EN_LOW();

	if ((AC_IN_L) && (IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))) //battery mode
    {	
        //EC_EN_V5A = 0; //981004-130724-R To let 0.5Watt routine cut EC power     
	    if (IS_BIT_SET(POWER_FLAG5, bios_cf9))
   	    {    
           //EC_EN_V5A_HIGH();
		   EC_EN_V5A = 1; //EC_EN_V5A            	   
           //PWR_LED_L = 0; //981004-180731-R            			   
        PWR_LED2_L = 0; //  PWR_LED2_LOW;// ; //981004-220719-M		   
        } 
	}
	else
	{
	  //EC_EN_V5A_HIGH();
	  EC_EN_V5A = 1; //EC_EN_V5A	 
	  if (IS_BIT_SET(POWER_FLAG5, bios_cf9))
   	  {         
         //PWR_LED_L = 0; //981004-180731-R         	 
        PWR_LED2_L = 0 ; //PWR_LED2_LOW;//; //981004-220719-M		 
      }    
	}
	
	
#if 1
	if(IS_BIT_CLR(POWER_FLAG13, Flash_ME_ON)) //981004-181221-M  
    {
		ME_CNT = 0;   
        //GPIO_Write(128,1);
		HDA_SDO = 0;
        BIT_CLR(POWER_FLAG13, HDA_SDO_BIOS);
    }
	#endif
    //981004-181205-S-E
	
    SHIP_MODE_cnt = 0; //981004-190116-A
	BIT_CLR(POWER_FLAG3, ship_mode); //981004-190116-A	
	
	//981004-200410-A-S
    FanRPM1=0x00; 
	FanRPM2=0x00;
    //981004-200410-A-E
	
	//981004-230621-A-S	
	BIT_CLR(EC_Flag2, pdchgcur_step1);
	BIT_CLR(EC_Flag2, pdchgcur_step2);
	BIT_CLR(EC_Flag2, pdchgcur_step3);
	BIT_CLR(EC_Flag2, pdchgcur_step4);
	BIT_CLR(EC_Flag2, pdchgcur_step5);
	CHGCUR_STEP_cnt2 = 0;
	//981004-230621-A-E
	
	if (!PD_ADAPTER_IN)	
    {
	   BIT_CLR(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4 //981004-230621-A
	   BIT_CLR(POWER_FLAG11, pd_chargable); //981004-230621-A
       //981004-230707-A-S
	   BIT_CLR(EC_Flag6, PD_60W);
	   BIT_CLR(EC_Flag6, PD_65W);
	   BIT_CLR(EC_Flag6, PD_80W);
	   BIT_CLR(EC_Flag6, PD_100W);
	   //981004-230707-A-E	   	   
	   BAT_CHGCURR = 0x8002; //0.512+0.128 = 0.64A (Target : 0.637A ) //981004-230621-A	
       BIT_SET(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3		 
    } 
	//RSMRST_L = 0;
	//981004-210312-R-S
	#if 0
	if (IS_BIT_CLR(POWER_FLAG2, sci_on))
	{
		BIT_SET(POWER_FLAG3, power_on_patch);//203 bit1
    }
	else
	{
        BIT_CLR(POWER_FLAG2, sci_on);
    }
	#endif
    //981004-210312-R-E	
	BIT_CLR(POWER_FLAG12, EC_modern_stby); //981004-200721-A
	DDS_PWM = 0;
	DDS_PWM_SWITCH = 0;
	GPIO_Set_IO(27,1);
	GPIO_Set_IO(21,0);
	//981004-220916-A-S per EE request
	//KSO7GOEN = 0;
	//CLEAR_MASK(KSOLGOENR, KSO7GOEN);
	///SET_GPO_KSO7_LO(); //CLEAR_MASK(KSOL, BIT7)  //KSO7 Raymond will ask will
	//SMBSW_RST_LOW;//SMBSW_RST_L = 0;
	USB_KBD_PWR = 0;
	//981004-220916-A-E	
}

void S3_S0_PS(void)
{
	//DoUSBCharge(); 
    USB_V5A_EN = 1;
	USB_EN_EC = 1; //981004-200410-A
	EC_EN_V5A = 1;
	//EC_EN_V5A_HIGH();
	
	BIT_SET(POWER_FLAG4, resume_from_s3);
	BIT_CLR(POWER_FLAG1, enter_S3);
   // BIT_CLR(KBHISR, BIT2);
	
	//GPIO[25]. = output + pulldown
	BAT_LED_L = 1;//BAT_LED_HIGH;
	//GPIO[27]. = output + pulldown
	PWR_LED2_L = 0 ; //PWR_LED2_LOW;	
	ALL_SYS_PWRGD = 1;//ALL_SYSTEM_PWRGD_HIGH();
	_Delay_1ms(1);
	PCH_PWROK = 1;//EC_PCH_PWROK_HIGH();
    _Delay_1ms(4);
	EC_S3_DDR5_EN = 0;//EC_S3_DDR5_EN_LOW(); //981004-210818-A
	_Delay_1ms(95); //981004-210818-M  
    EC_SYS_PWROK_HIGH();//981004-211217-M from PCH_PWROK	
	
	SystemState = SYSTEM_S0;
	//EC_BKL_DIS();
//	KBRST_L = 0; //981004-200410-R 
//    EC_AMP_MUTE_L = 0; //981004-210720-M from 1
//	CLEAR_MASK(POWER_FLAG2, fan_on);
//	EC_S3_DDR5_EN = 1; //981004-210818-A
//    _Delay_1ms(10); //981004-210818-A
//	GPIO_Write(114,0) = 0; //981004-210818-M from 1	 
//    USB_EN_EC = 0; //981004-210818-M from 1	

	BIT_CLR(ProcsH, ProcsH_acout);
    ProcsH_cnt =0;
    BIT_CLR(ProcsH, ProcsH_scion20sec);
    ProcsH_scion_cnt = 0;    
    //H_PROCHOT_L = AC_IN_L ? 1 : 0; //981004-201021-M 
	if ((AC_IN_L) &&(IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4  //battery mode
	{	   
       if ((IS_BIT_SET(POWER_FLAG4, resume_from_s3)))
       {	   
	        //dGPU_HOLD_EC_RST_HIGH();
			dGPU_HOLD_EC_RST_L = 1;
	   }	
	}
	else
	{
      //dGPU_HOLD_EC_RST_LOW();
	  dGPU_HOLD_EC_RST_L = 0;	  
	}
    //dGPU_HOLD_EC_RST_L = AC_IN_L ? 1 : 0;
    //981004-170629-M-E	
    //H_PROCHOT_L = AC_IN_L ? 0 : 1;
	if ((AC_IN_L) &&(IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4  
	{	   
	   //H_PROCHOT_HIGH;
	   H_PROCHOT_L = 1; //981004-210401-M from 0
	}
	else
	{	  
      //H_PROCHOT_LOW;
	  H_PROCHOT_L = 0; //981004-210401-M from 1	  
	  
	}
    WTDP4 = 20; //981004-210401-A 
	
	KBC_B0CMD();//OEM_Cmd_B0();
}

void S0_S3_PS(void)
{
	//981004-130116-M-S
	BIT_SET(POWER_FLAG1, enter_S3);	 
//    H_PROCHOT_L = AC_IN_L ? 1 : 0; //981004-140505-A //Disable Processor hot
    if ((AC_IN_L) &&(IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4 
	{	   
	   H_PROCHOT_L = 1;
	}
	else
	{	  
	  H_PROCHOT_L = 0;
	}
    WTDP4 = 20; //981004-210401-A

	GPIO_Func_Mode(25,1);
	PWM_Set_Duty(2,0);
	//GPCRA4 = ALT; //981004-210104-R per SPEC

	GPIO_Func_Mode(27,1);
	//DCR4 = 0x00; //981004-181011-R per SPEC
	PWM_Set_Duty(4,0);
	//PWR_LED2 = 0; //981004-210104-M 					setting power led2 to 0x00
    S0_S3Variable();
    //981004-130116-M-E
	
}

void S0_S3Variable(void)
{
	SystemState = SYSTEM_S3;
	//EC_S3_DDR5_EN_HIGH();
	EC_S3_DDR5_EN = 1;
	_Delay_1ms(20); //981004-211020-M from 1
	//USB_EN_EC_LOW();
	USB_V5A_EN = 0; //981004-210611-M from 0
	//USB_V5A_EN_LOW();
	USB_EN_EC = 0; //981004-210611-M from 0 Cut Standard USB port power (GPIO F7)
    //SET_GPO_KSO7_LO();  	
}

void Oem_SysPowerContrl(void)
{
	if(!(SystemState & 0xf0))
		CheckPowerState();
	switch (SystemState)
    {
        case SYSTEM_S5S0:
			G3_S5_PS();
            S5_S0_PS();
            break;

        case SYSTEM_S0S5:
            S0_S5_PS();
            break;

        case SYSTEM_S3S0:
            S3_S0_PS();
            break;

        case SYSTEM_S0S3:		    
            S0_S3_PS();
            break;

//        case SYSTEM_EC_WDTRST:
//            InternalWDTNow();
//            break;

        default:
            break;
    }
}

void DoPowerStatus(void)
{
    uint8_t presentstatus;
    static uint8_t SysStatusChange; 

    presentstatus = (POWER_FLAG2&(SLP_S3_ON+SLP_S4_ON));

    if (PowerStatusBK != presentstatus)      // To make sure all SLP is checked.
    {
        PowerStatusBK = presentstatus;
        SysStatusChange = 1;
        return;
    }

    if (!SysStatusChange)
        return;

    //switch (POWER_FLAG2 & (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON)) 
    switch (presentstatus)
    {
        case 0: 	                        // goto S5
            switch (SystemState) 
            {
                case SYSTEM_S0 :                    				
                    Oem_TriggerS0S4(0x01); //SC_S0SLPOff
                    break;
                                        
                case SYSTEM_S3 :
                    Oem_TriggerS0S4(0x02); //SC_S3S4SLPOff
                    break;           
            }
           	break;

        //case (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON): // goto S0
        case (SLP_S3_ON+SLP_S4_ON):
            switch (SystemState) 
            {
                case SYSTEM_S3 :
                    Oem_TriggerS3S0();
                    break;
                    
                case SYSTEM_S5 :
                    Oem_TriggerS4S0();
                    break;
            }

            break;            

        //case (SLP_S4_ON+SLP_S5_ON):             // goto S3
        case (SLP_S4_ON):
            switch (SystemState) 
            {
                case SYSTEM_S0 :
                    Oem_TriggerS0S3(0x30);
                    break;
            }
            break;
    }

    SysStatusChange = 0;
}

void CheckPowerState(void)
{
    switch (CheckPowerStateIndex)
    {
        case 0:
            GetSlp_S3 ? BIT_SET(POWER_FLAG2, SLP_S3_ON):BIT_CLR(POWER_FLAG2, SLP_S3_ON);
            CheckPowerStateIndex ++;
            break;

        case 1:
            GetSlp_S4 ? BIT_SET(POWER_FLAG2, SLP_S4_ON):BIT_CLR(POWER_FLAG2, SLP_S4_ON);
            CheckPowerStateIndex ++;
            break;
            
        case 2:
            DoPowerStatus();
            CheckPowerStateIndex = 0x00;
            break;

        default:
            CheckPowerStateIndex = 0x00;
            break;
    }
}
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S3(uint8_t causecode)
{
    if(SystemState==SYSTEM_S0)
        return;
    
    ShutDnCause = causecode;		// setup shutdown case
    SystemState = SYSTEM_S0S3;
    //PWSeqStep = 1;
    PowSeqDelay = 0x00;
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S4(uint8_t causecode)
{
    if(SystemState==SYSTEM_S5)
        return;
    
    ShutDnCause = causecode;		// setup shutdown case
    SystemState = SYSTEM_S0S5;
    //PWSeqStep = 1;
    PowSeqDelay = 0x00;
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS3S0(void)
{
    if (SystemState==SYSTEM_S0)
        return;
    
    SystemState = SYSTEM_S3S0;
    
    PowSeqDelay = 0x00;
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS4S0(void)
{
    if (SystemState==SYSTEM_S0)
        return;
    
    SystemState = SYSTEM_S5S0;
	
    //PWSeqStep = 1;
    PowSeqDelay = 0x00;
}

void InitDevice(void)
{

    //981004-180731-R-S 
    #if 0  
    if (IS_MASK_SET(POWER_FLAG2, wlan_on) && (IS_MASK_SET(POWER_FLAG2, sci_on)))
	{        
        WLAN_LED = 1;			         	
    }
    else
    {	   
        WLAN_LED = 0;
    }
    #endif
    //981004-180731-R-E
	
	WLAN_EN = 1; 
	
	//981004-191001-M-S
    //CCD_EN = IS_MASK_SET(POWER_FLAG1, ccd_on) ? 1 : 0;
	BIT_SET(POWER_FLAG1, ccd_on);
    CCD_EN = 1;
    //981004-191001-M-E 
    ///KSOLGOENR |= KSO0GOEN; //Set KSO0 GPIO function to high (0X1D0E) //981004-220629-A	
	    
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
    BIT_SET(POWER_FLAG1, bt_on); 
    BT_EN = 1;             
    //981004-191001-M-E	
   
	BIT_SET(POWER_FLAG6, adjustfan);
	FanRPM1=0x39; //981004-200410-M from 0x5D
	FanRPM2=0x39; //981004-200410-M from 0x5D 
	
    //HD_LED = 1; //981004-180731-R	
    EC_AMP_MUTE_L =0; //981004-210720-M from 1  
    BIT_CLR(POWER_FLAG9, lcd_off);
	//EC_BKLOUT = 1;
	GPIO_Write(84,1); 	
    DDS_PANEL_RST = 1; //981004-231002-A 	
    patchACout = 0; 
    Fullchgcnt =0; 
    
	//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
	if ((AC_IN_L) && (IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w)) && (IS_BIT_CLR(POWER_FLAG7, PPAB_ON))) //battery mode
	{	   
	   NVDeventStatus = 0x0A; //981004-201021-M from 0 to prevent system shutdown
	}
	else if (!AC_IN_L)
	{	  
       NVDeventStatus = 0x01; //981004-201021-M from 1 to prevent system shutdown     
	}
	else if (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))
	//else if (!PD_ADAPTER_IN)	
    {
       //ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
	   QeventSend(SCI_NV_DB);
       PD_Adapter_setting();		 
    } 
    //NVDeventStatus = AC_IN_L ? 0x0A : 0x01;
    USB_KBD_PWR = 1; //981004-221014-A	
    	
	//981004-210705-A-S
	#if 0
    LSCTRL = 0x02; //Active mode (EC RAM : 0x28F) 	
    //(bRWSMBus(SMbusChB, SMbusWB, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); 
	SMBUS_RW_B(1,WriteByte,LightSensorAddr, CONTROL, &LSCTRL);
    _Delay_1ms(10);//Delay1MS(10);
    //(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_L, &LS_DATA_L, SMBus_NoPEC));
	SMBUS_RW_B(2,ReadByte,LightSensorAddr, DATAREAD_L, &LS_DATA_L);
	//(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_M, &LS_DATA_M, SMBus_NoPEC));
	SMBUS_RW_B(2,ReadByte,LightSensorAddr, DATAREAD_M, &LS_DATA_M);    
	//(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_H, &LS_DATA_H, SMBus_NoPEC));
	SMBUS_RW_B(2,ReadByte,LightSensorAddr, DATAREAD_H, &LS_DATA_H);
	//(bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); //981004-210705-A
	SMBUS_RW_B(2,ReadByte,LightSensorAddr, DATAREAD_H, &LSCTRL);
    Lux_TEMP = ((LS_DATA_H<<16) | (LS_DATA_M<<8) | (LS_DATA_L)); //981004-210705-M	
	#endif
    //981004-210705-A-S
	         
    BIT_SET(POWER_FLAG1, power_on);
	//SET_MASK(POWER_FLAG3, ps2_on);         
	BIT_SET(POWER_FLAG2, lid_open);                                                                            
    BIT_SET(POWER_FLAG6, GPU_on);              
    ///IER1 |= 0x08; // enable KSI interrupt
	BIT_CLR(POWER_FLAG5, bios_cf9);

	//TI_FW_CHECK(); //981004-211119-A
	//SET_TEMP_NCT7802(); //981004-220803-A
	//Mode_SEL = 0x6A; //REG : 0x22 =>  Thermistor mode //981004-220803-M from 0x0A
    //bRWSMBus(SMbusCh1, SMbusWB, NCT7802YAddr, NCT_MODE_SEL, &Mode_SEL ,  SMBus_NoPEC);
	BAT_OPTION3 = 0x4402; //981004-221013-M from 0x4412 to adjust ACDET deglitch time to 150ms//BQ24780s to enable Boost mode
    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option3, &BAT_OPTION3 ,  SMBus_NoPEC); //981004-220803-A
	SMBUS_RW_W(0,WriteWord,Charger_Addr, CHGCmd_Option3, &BAT_OPTION3);
	//981004-231108-A-S
	NCT7601_CH1_On = 0xFF;
	//bRWSMBus(SMbusCh1, SMbusWB, Thermal1_Addr, Thermal1_CH1_Enable, &NCT7601_CH1_On , SMBus_NoPEC); //Thermal IC NCT7601Y
	SMBUS_RW_B(0,WriteByte,Thermal1_Addr, Thermal1_CH1_Enable, &NCT7601_CH1_On);    
	NCT7601_Start = 0x01;
    //bRWSMBus(SMbusCh1, SMbusWB, Thermal1_Addr, Thermal1_Config, &NCT7601_Start , SMBus_NoPEC); //Thermal IC NCT7601Y
	SMBUS_RW_B(0,WriteByte,Thermal1_Addr, Thermal1_Config, &NCT7601_Start);
	//981004-231108-A-E
	
	///SET_GPO_KSO7_HI(); //SET_MASK(KSOL, BIT7) //981004-221111-A
    KSO7_CNT = 0; //981004-221111-A		
	#if 0 //981004-231030-R
	bRSMBusBlock(SMbusCh1, SMbusRBK, SmartBat_Addr, C_Dname , &BAT_DEVNAME); //981004-220510-A     
	if ((BAT_DEVNAME == 0x4741472D)) //4 Cell => 0x4741472D //Old 99Watt //981004-220510-A
    {	    
        SET_MASK(EC_Flag4, old_99w); //0x388 BIT5		
    }
    else //New : 0x4741442D not 0X47414B34 
    {	          	        
        CLEAR_MASK(EC_Flag4, old_99w);        		
    }
	#endif
   /// SET_GPO_KSO12_HI(); //981004-231017-A //EC_KBLED_EN
	///SET_GPO_KSO13_HI(); //981004-231017-A //EC_LBLED_EN	
	///SET_GPO_KSO0_HI(); //981004-231120-A PER EE request
}
#endif

#if 1

//-----------------------------------------------------------------------------
//  The variable of Sx -> S0
//-----------------------------------------------------------------------------
void SX_S0CommVar(void)
{
    SysPowState = SYSTEM_S0;
	InitDevice(); 
    ResetSCIEvent();
    
    CheckPowerStateIndex = 0x00;
    //InitSMBus(); 
	//981004-18712-A-S	
#if ITE_CHIP_IT557X

	// Enable P80 P81
    ///SPCTRL1 |= (BIT7 + BIT6 + BIT3);
    //SET_MASK(SPCTRL1, BIT7);  //P80LEN);  /* P80L enable  */
    //SET_MASK(SPCTRL1, BIT6);  //P80LEN);  /* P80L enable  */
    //SET_MASK(SPCTRL1, BIT3);  //ACP81);   /* Accept Port 81h cycle */
#else
	#if 1	//IT8587
	SPCTRL1 |= (BIT7);			//Enabled Port80 Decode to BRAM
    #else	//IT8987E/8991E
	SPCTRL1 |= (BIT7+BIT3);		//Enabled Port80/81 Decode to BRAM
    #endif    
	//981004-180712-A-E
#endif
}


//-----------------------------------------------------------------------------
//  The OEM variable of S0 -> Sx
//-----------------------------------------------------------------------------
void OEM_S0_SXCommVar(void)
{
    CheckPowerStateIndex = 0x00; //981004-130116-A
    CLEAR_MASK(SYS_MISC1,ACPI_OS); //981004-130116-A
		
	//981004-130116-M-S
	//PCH_PWROK = 0; //981004-240507-R
    ALL_SYS_PWRGD = 0;
	//KBRST_L = 0; //981004-220615-R
    EC_AMP_MUTE_L = 0; //981004-210720-M from 1
	CLEAR_MASK(POWER_FLAG2, fan_on);
	//CLEAR_MASK(POWER_FLAG10, fullspeed_fan); //981004-190813-S to S3
	//CLEAR_MASK(POWER_FLAG8, smart_cooling_on); //981004-190813-S to S3
	//CLEAR_MASK(POWER_FLAG9, super_quiet); //981004-190813-S to S3
	CLEAR_MASK(POWER_FLAG4, resume_from_s3); //981004-190612-A   
    BT_EN = 0;
	//WLAN_EN = 0; //981004-180731-R
	//BT_LED = 0; //981004-180731-R		
	//WLAN_LED_EN = 0; //981004-180731-R
    //WLAN_LED = 0; //981004-180731-R
    //HD_LED = 0; //981004-180731-R
    FanDACLevel = 0;	
	DCR0 = 0x00;
	DCR3 = 0x00; //981004-140930-A
    //DCR6 = 0x00; //981004-200724-R
   
   //981004-211119-A-S	
    //Thermal_IC_CNT3 = 0; //981004-221130-R
	//Thermal_IC_CNT1 = 0; //981004-221130-R
    //CLEAR_MASK(POWER_FLAG7, Thermal_IC_hot1); //981004-221130-R
    //981004-211119-A-E
    
	//981004-211208-A-S
	#if 0
    Learn_mode_CNT1 = 0;
	Learn_mode_CNT3 = 0;
	Learn_mode_CNT5 = 0;
	Learn_mode_CNT2 = 0;
	Learn_on_CNT = 0;
    CLEAR_MASK(EC_Flag5, learn_mode0);
	CLEAR_MASK(EC_Flag5, learn_mode1);
	CLEAR_MASK(EC_Flag5, learn_mode2);
	CLEAR_MASK(EC_Flag5, learn_on1);
	CLEAR_MASK(EC_Flag5, learn_on2);
	#endif
    //981004-211208-A-E	
	
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
    //KBlightcnt = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)	
    //KBlightcnt1 = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)
    //KB_BR_Level = 0x00; //992022-140402-R //981004-131125-A (keyboard backlight)
	FINAL_TEMP2 = 0;
    PECI_CPU_temp = 0; //981004-150414-A
    GPU_TMPR = 0; //981004-150414-A
	//GPU_TMPR2 = 0; //981004-180712-R
    FANLVDNCNT =0; //981004-131203-A
    FANLVDNCNT1 =0; //981004-131203-A	
	FanLevelTemp = 0; //981004-201105-A 
    FanUpCNT0 = 0; //981004-201105-A  
    FanDnCNT0 = 0; //981004-201105-A
    FanUpCNT3 = 0; //981004-201105-A   
    FanDnCNT3 = 0; //981004-201105-A 
	FanLevelTemp2 = 0; //981004-201105-A 	
    CCD_EN = 1;   	
	///CLEAR_MASK(KBHISR,SYSF); //981004-130116-A
	CLEAR_MASK(KBC->STS,SYSF); //981004-130116-A
	
    ///Ccb42_SYS_FLAG=0;  //981004-130116-A     
	CLEAR_MASK(KCCB42,Ccb42_SYS_FLAG); 		
	CLEAR_MASK(POWER_FLAG2, SLP_S3_ON); //981004-121225-A
	//CLEAR_MASK(POWER_FLAG9, lcd_off); //981004-130314-M
	//Boot_bobocnt =0; //981004-130416-A
	SET_MASK(POWER_FLAG9, lcd_off); //981004-170405-A
	EC_BKLOUT = 0; //981004-130506-A
	Lid_close_cnt =0; //981004-170405-A
    Sci_on_20sec_cnt = 0; //981004-150810-A

    //GPCRA4 = OUTPUT+PULL_DW; //981004-201223-M from OUTPUT+PULL_DW
	GPIO_Set_IO(27,1);
	GPIO_Config(27,0,0,1);
    PWR_LED2_L = 1; //981004-210104-M 	
    
    //981004-210617-A-S
    #if 1    
	//To shutdown Light sensor	
    LSCTRL = 0x00; //981004-150821-M for LTR-F216A Light sensor	
    (bRWSMBus(SMbusChB, SMbusWB, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); //(EC RAM : 0x28F)
    #endif
	
	//Thermal_IC_ShutDn = 0x01; //981004-231108-R
	//(bRWSMBus(SMbusCh4, SMbusWB, Thermal1_Addr, Thermal1_Config, &Thermal_IC_ShutDn , SMBus_NoPEC)); //981004-231108-R   		
    //981004-211117-A-E
	
	CLEAR_MASK(POWER_FLAG4, bat_cap_first_chk); //981004-170412-A
	CLEAR_MASK(POWER_FLAG4, bat_cap_downgrade); //981004-170412-A
    BAT_FIRST_CHK_cnt = 0; //981004-170412-A
    BAT_DOWNGRADE_cnt = 0; //981004-170412-A
   
    FAN_TEMPUP_cnt = 0;
    FAN_TEMPDN_cnt = 0;	
	
	//Heavy_Load_cnt = 0; //981004-181107-R
	
	//GPCRH1 = ALT; //981004-221202-M from INPUT SMBUS D
	//GPCRH2 = ALT; //981004-221202-M from INPUT SMBUS D

	GPIO_Func_Mode(100,1);
	GPIO_Func_Mode(101,1);

	//FAKE_ACOUT_CNT = 0;	//981004-181128-A
	//FAKE_ACOUT_CNT2 = 0;	//981004-181128-A
	//CLEAR_MASK(POWER_FLAG6, ECRAM_80patch); //981004-181216-A
    //CLEAR_MASK(POWER_FLAG9, os_read_ecram_on); //981004-181216-A	
    CLEAR_MASK(POWER_FLAG2, LED_TEST_ON); //981004-190109-A	
	CLEAR_MASK(POWER_FLAG6, sv_thrt_on);//981004-190329-A //EC RAM 206 bit 7
	CLEAR_MASK(POWER_FLAG5, Linux_fanon);//981004-200108-A
	//981004-19090801-R-S
	//GPU_OC(0);//LV0 //981004-220330-R
	
	//981004-220923-R-S
	#if 0
    //GPU_TEMP_CNT1 = 0; 
	//CLEAR_MASK(POWER_FLAG13, GPU_temp_80); //EC RAM 20D bit 4
	//GPU_TEMP_CNT2 = 0;
	//CLEAR_MASK(POWER_FLAG13, GPU_temp_85); //EC RAM 20D bit 5
	#endif
	//981004-220923-R-E
	
	//981004-190801-R-E
    //CLEAR_MASK(POWER_FLAG6, bat_led_on); //981004-200724-R	
	USB_KBD_PWR = 0; //981004-240506-A	
	
	//981004-221025-A-S
	CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
    CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
    CLEAR_MASK(EC_Flag4, nv_db20_lv2);
    CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	CLEAR_MASK(EC_Flag4, nv_db20_lv4);
    //981004-221025-A-E	
			
    //981004-231002-A-S
	///CLEAR_MASK(KSOH1, BIT0); //KSO 8 //SD_RST_AUX
	///CLEAR_MASK(KSOH1, BIT1); //KSO 9 //EC_SSDA_PWR_EN
	///CLEAR_MASK(KSOH1, BIT2); //KSO 10 //EC_SSDB_PWR_EN
	///CLEAR_MASK(KSOH1, BIT3); //KSO 11 //EC_WLAN_PWR_EN
	///CLEAR_MASK(KSOH1, BIT4); //KSO 12 //EC_KBLED_EN
	///CLEAR_MASK(KSOH1, BIT5); //KSO 13 //EC_LBLED_EN
	//981004-231002-A-E
	///SET_GPO_KSO12_LO(); //981004-231017-A //EC_KBLED_EN
	///SET_GPO_KSO13_LO(); //981004-231017-A //EC_LBLED_EN
	///SET_GPO_KSO0_LO(); //981004-231120-A PER EE request
	///SET_GPO_KSO6_LO(); //KSOLGOENR 0X1D0E BIT6 => 0 //HDD LED //981004-240529-A
	///SET_GPO_KSO3_LO(); //DMIC SEL
	GPIO_Set_IO(41,1);
	GPIO_Set_IO(44,1);
	GPIO_Set_IO(47,1);
	GPIO_Set_IO(56,1);
	GPIO_Set_IO(57,1);
	GPIO_Write(41,0);
	GPIO_Write(44,0);
	GPIO_Write(47,0);
	GPIO_Write(56,0);
	GPIO_Write(57,0);
}

//-----------------------------------------------------------------------------
//  The variable of S0 -> Sx
//-----------------------------------------------------------------------------
void S0_SXCommVar(void)
{
#ifdef PECI_Support
    ///PECI_ClearPSTVariables();
#endif
    
#if TouchPad_only
   /// PowerOffClearTPPendingData();
#endif        

    //InitSMBus(); //981004-120103-R

    OEM_S0_SXCommVar();
}


//-----------------------------------------------------------------------------
//  The variable of S0 -> S4
//-----------------------------------------------------------------------------
void S0_S4Variable(void)
{
    SysPowState = SYSTEM_S4;    	
	
    //981004-131213-A-S
    if (IS_MASK_SET(POWER_FLAG6, BIOS_flash_ok))
    {
        ///FLHCTRL3R = 0x18;/// Flash control
        Delay1MS(250); 
        //ETWCFG = 0x20;   //981004-131213-R For UCF2 BIOS mirror code and IU flash
        //EWDKEYR = 0xFF;  //981004-131213-R For UCF2 BIOS mirror code and IU flash
        //CLEAR_MASK(POWER_FLAG5, BIOS_flash);
        //while(1);        //981004-131213-R For UCF2 BIOS mirror code and IU flash
        ///main();            //981004-131213-A For UCF2 BIOS mirror code and IU flash
        return;            //981004-131213-A For UCF2 BIOS mirror code and IU flash
    }
    //981004-131213-A-E
    //S4_STATUS();
	S0_SXCommVar(); //981004-130114-A
	
	//981004-121122-A-S
	///IER1 &= 0xF7;/// Clear CIR, WKO[25],WKINTC,WKO[26],KBM Scan INT,SMBUSB, SMBUSA, ADC
    //CORE_PMFLAG_S3 = 0;
    //CPU_TMPR = 0;
	GPU_TMPR = 0;  
    CLEAR_MASK(POWER_FLAG1, power_on);	
	CLEAR_MASK(POWER_FLAG4, pstate_off); 		
    CLEAR_MASK(POWER_FLAG7, dgpu_9Aon); //981004-120425-A    
	//PollingGP12 = 0; //981004-131111-A //981004-150417-R 
    //981004-231017-R-S
    #if 0	
    CLEAR_MASK(POWER_FLAG8, f2_press); //981004-120911-A
    CLEAR_MASK(POWER_FLAG8, f9_press); //981004-120911-A
	CLEAR_MASK(POWER_FLAG8, f12_press); //981004-120911-A	
	CLEAR_MASK(POWER_FLAG8, f10_press); //981004-121017-A
	#endif
	//981004-231017-R-E
    POWER_FLAG2 = POWER_FLAG2 & 0xCF; //Clear throttling on and SCI on /981004-210312-M
    //POWER_FLAG2 = POWER_FLAG2 & 0xDF; //Clear throttling on //981004-210127-A-M from 0xCF	
    //CLEAR_MASK(KBHISR,SYSF);
	CLEAR_MASK(KBC->STS,SYSF); //981004-130116-A	        
    SET_MASK(POWER_FLAG1, enter_S4);
	//SET_MASK(POWER_FLAG3, S5_normal_shutdn); //981004-150417-R
	//DoUSBCharge(); //981004-130506-A
    CLEAR_MASK(POWER_FLAG2, SLP_S4_ON);	
    NVDeventStatus = 0x01; //992022-140904-A
    //NVcnt1 = 0x00; //981004-151019-R
    //NVcnt2 = 0x00; //981004-151019-R
    ///Timer5msCnt = 0;	
	///GPCRA2 = OUTPUT+PULL_DW; //981004-210104-M from GPCRA1
	GPIO_Set_IO(25,1);
	GPIO_Config(25,0,0,1);
    //PWR_LED_L = 1; //981004-180731-R
    BAT_LED_L = 1; //981004-210104-M 	
    //GPCRA4 = OUTPUT+PULL_DW; //981004-220719-M from OUTPUT+PULL_UP	
	GPIO_Set_IO(27,1);
	GPIO_Config(27,0,0,1);
    PWR_LED2_L = 1; //981004-220719-M 	 	        	 	   
    //GPCRF0 = INPUT+PULL_DW; //981004-190401-A to prevent current leakage to eDP 8625
    //GPCRF1 = INPUT+PULL_DW; //981004-190401-A to prevent current leakage to eDP 8625
	GPIO_Set_IO(92,0);
	GPIO_Config(92,0,0,1);
	GPIO_Set_IO(93,0);
	GPIO_Config(93,0,0,1);	 	
   /// ZTIER = 0x00; //981004-191125-S from S3/S4 for power LED breathing under S3
    SYS_CLKPWR_PWM4(disable);
    //PS2_PowerOff(); //981004-220615-R
    CLEAR_MASK(ProcsH, ProcsH_scion20sec);  //992022-130731-A patch for Max request
    ProcsH_scion_cnt = 0;  //981004-131030-A patch for Max request
//	GPU_ON = 0; //981004-131219-A
    CLEAR_MASK(POWER_FLAG10, scion_ac_in); //992022-140904-A
    SCI_on_AC_in_cnt = 0; //992022-140904-A

    CLEAR_MASK(POWER_FLAG10, sci_on_20sec); //992022-140904-A
    Sci_on_20sec_cnt = 0; //992022-140904-A
	
	//EC_S3_DDR5_EN = 1; //981004-230912-R
    //Delay1MS(10); //981004-230912-R
	USB_V5A_EN = 0; //981004-210611-M from 0	 
    USB_EN_EC = 0; //981004-210611-M from 0
	DDS_PANEL_RST = 0; //981004-231002-A
	  
	//981004-150602-A-E
		
		
    //if (AC_IN_L)
	//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
    if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
    {	
        //EC_EN_V5A = 0; //981004-130724-R To let 0.5Watt routine cut EC power     
	    if (IS_MASK_SET(POWER_FLAG5, bios_cf9))
   	    {    
           EC_EN_V5A = 1; //EC_EN_V5A            	   
           //PWR_LED_L = 0; //981004-180731-R
           if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
	       { 		   
               PWR_LED2_L = 0; //981004-220719-M
           }			   
        } 
	}
	else
	{
	  EC_EN_V5A = 1; //EC_EN_V5A	 
	  if (IS_MASK_SET(POWER_FLAG5, bios_cf9))
   	  {         
         //PWR_LED_L = 0; //981004-180731-R         	 
         if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
	     { 		   
            PWR_LED2_L = 0; //981004-220719-M
         }		 
      }    
	}
	//CLEAR_MASK(POWER_FLAG10, win_key_disable); //981004-220216-R
    //Scanner_Table_Pntr = &Rc_ROM_Tables; //981004-220216-R
	
	//981004-181205-S-S shift from S0 per BIOS request
	#if 1
	if(IS_MASK_CLEAR(POWER_FLAG13, Flash_ME_ON)) //981004-181221-M  
    {
		ME_CNT = 0;   
        HDA_SDO = 0;
        CLEAR_MASK(POWER_FLAG13, HDA_SDO_BIOS);
    }
	#endif
    //981004-181205-S-E
	
    SHIP_MODE_cnt = 0; //981004-190116-A
	CLEAR_MASK(POWER_FLAG3, ship_mode); //981004-190116-A	
	
	//981004-200410-A-S
    FanRPM1=0x00; 
	FanRPM2=0x00;
    //981004-200410-A-E
	
	//981004-230621-A-S	
	CLEAR_MASK(EC_Flag2, pdchgcur_step1);
	CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	CLEAR_MASK(EC_Flag2, pdchgcur_step4);
	CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230828-A
	CHGCUR_STEP_cnt2 = 0;
	//981004-230621-A-E
	
	if (!PD_ADAPTER_IN)	
    {
	   CLEAR_MASK(POWER_FLAG11, pd_ac_over65w); //EC RAM 0x211 bit4 //981004-230621-A
	   //CLEAR_MASK(POWER_FLAG11, pd_chargable); //981004-230621-A
       //981004-230707-A-S
	   CLEAR_MASK(EC_Flag6, PD_60W);
	   CLEAR_MASK(EC_Flag6, PD_65W);
	   CLEAR_MASK(EC_Flag6, PD_80W);
	   CLEAR_MASK(EC_Flag6, PD_100W); //981004-230731-M
	   //981004-230707-A-E	   	   	   
       BAT_CHGCURR = 0x0001; //0.256A //981004-230731-M from 0x8002	   
       SET_MASK(POWER_FLAG11, check_pd_ac_chg); //EC RAM 0x211 bit3		 
    } 
	if (!PD_ADAPTER_IN2)	
    {
	   CLEAR_MASK(POWER_FLAG8, pd_ac_over65w2); //EC RAM 0x208 bit1 
	   CLEAR_MASK(EC_Flag6, PD_60W);
	   CLEAR_MASK(EC_Flag6, PD_65W);
	   CLEAR_MASK(EC_Flag6, PD_80W);
	   CLEAR_MASK(EC_Flag6, PD_100W); //981004-230731-M   	   	   
       BAT_CHGCURR = 0x0001; //0.256A //981004-230731-M from 0x8002	   
       SET_MASK(POWER_FLAG8, check_pd_ac_chg2); //EC RAM 0x208 bit1		 
    } 
	RSMRST_L = 0;
	//981004-210312-R-S
	#if 0
	if (IS_MASK_CLEAR(POWER_FLAG2, sci_on))
	{
		SET_MASK(POWER_FLAG3, power_on_patch);//203 bit1
    }
	else
	{
        CLEAR_MASK(POWER_FLAG2, sci_on);
    }
	#endif
    //981004-210312-R-E	
	CLEAR_MASK(POWER_FLAG12, EC_modern_stby); //981004-200721-A
	DDS_PWM = 0; //981004-230906-A
	DDS_PWM_SWITCH = 0; //981004-230906-A
	///GPCRA7 = OUTPUT; //981004-231218-M
	GPIO_Set_IO(31,1);
	///GPCRD3 = INPUT; //981004-230906-A
	GPIO_Set_IO(21,0);
	//SET_GPO_KSO7_LO(); //CLEAR_MASK(KSOL, BIT7)  //KSO7 //981004-231002-A
	GPIO_Set_IO(48,1);
	GPIO_Write(48,0);
	//SMBSW_RST_L = 0; //981004-231002-A
	USB_KBD_PWR = 0; //981004-220916-A
}

//-----------------------------------------------------------------------------
// The variable of S0 -> S3
//-----------------------------------------------------------------------------
void S0_S3Variable(void)
{
	SysPowState = SYSTEM_S3;
	EC_S3_DDR5_EN = 1;
	Delay1MS(20); //981004-211020-M from 1
	USB_V5A_EN = 0; //981004-210611-M from 0
	USB_EN_EC = 0; //981004-210611-M from 0 Cut Standard USB port power (GPIO F7)  	
	S0_SXCommVar();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS3S0(void)
{
    if (SystemIsS0)
        return;
    
    SysPowState = SYSTEM_S3_S0;
    
    PowSeqDelay = 0x00;
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS4S0(void)
{
    if (SystemIsS0)
        return;
    
    SysPowState = SYSTEM_S4_S0;
	
    //PWSeqStep = 1;
    PowSeqDelay = 0x00;
}

//981004-130116-M-S
//----------------------------------------------------------------------------
// S5 to S0 sequnce
//----------------------------------------------------------------------------
void Oem_S4S0Sequence(void)
{
    ///SET_MASK(FLHCTRL3R, BIT(0)); //981004-200428-A
    EC_CLR_LATCH = 1;
    EC_EN_V5A = 1;
    USB_V5A_EN = 1; 
    USB_EN_EC = 1;
	
	//981004-210825-R-S Benny decide
	#if 0	
    if ((AC_IN_L) && (!PD_ADAPTER_IN) && (!BAT_IN_L)) 		
    {             		   	   	     
       ConfigBatIn();
	   RMCAP_TEMP = (BAT_RMCAP<<8) | (BAT_RMCAP>>8); 
       if ((RMCAP_TEMP <= BATCAP10))
       {		   
	      S4_PD_ACTIVE(); //To get PD adapter Watt	
          SysPowState = SYSTEM_S0_S4; 		              		   
          return;
       }		  
	}
    #endif 
    //981004-210825-R-E
	
    ///GPCRH1 = ALT;
	///GPCRH2 = ALT;
	GPIO_Func_Mode(100,1);
	GPIO_Func_Mode(101,1);
    //Delay1MS(250); //981004-200428-A //981004-200527-R
    //Delay1MS(100); //981004-200428-A //981004-200527-R
    ///RSTS = 0x44;   //981004-200428-A //SUPPORT_INTERFACE_eSPI	
    PWR_PULSE_L = 1;   
	Delay1MS(20); //981004-200428-R //981004-200527-A
    EC_S3_DDR5_EN = 0; //981004-210818-A
    Delay1MS(80); //981004-211029-A per EE request	ONLY for AORUS 15X/17X series
    RSMRST_L = 1; 
   /// if (ECHIPVER >= _CHIP_EX) //981004-231214-A
    {
      ///  CLEAR_MASK(ESGCTRL2, F_ESPIIPG);
    }
   /// VWCTRL2 |= F_DSW_PWROK_SOURCE; //981004-200428-A
    Delay1MS(100);    	
	PWR_PULSE_L = 0;		
	if(IS_MASK_SET(POWER_FLAG13, HDA_SDO_BIOS))  
    {
        HDA_SDO = 1; 
    }
	CLEAR_MASK(POWER_FLAG13, Flash_ME_ON); 	
	//GPCRA2 = OUTPUT+PULL_DW; //981004-210104-M from ALT
	GPIO_Set_IO(25,1);
	GPIO_Config(25,0,0,1);   
	//PWR_LED_L = 0; //981004-210104-R   
	//GPCRA7 = ALT; //981004-230914-A
	DDS_PWM = 0; //981004-231218-A
	///GPCRD3 = OUTPUT; //981004-230914-A
	GPIO_Set_IO(21,1);
    ///GPCRA4 = OUTPUT+PULL_DW; //981004-220719-M from OUTPUT+PULL_UP
	GPIO_Set_IO(27,1);
	GPIO_Config(27,0,0,1); 
	if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
	{ 		   
        PWR_LED2_L = 0; //981004-220719-M
    }	
    Delay1MS(50); // instead of power button,like RTC wake up or hitting //981004-200611-A for press power button shortly
	CLEAR_MASK(POWER_FLAG1, enter_S4); 
    CLEAR_MASK(POWER_FLAG1, enter_S3); 	
	SET_MASK(POWER_FLAG2, SLP_S4_ON);
    SET_MASK(POWER_FLAG2, SLP_S3_ON);
	SET_MASK(POWER_FLAG7, PPAB_ON); //EC RAM 0x207 bit2 //981004-221025-A //981004-221228-A
	patchACout = 0; 
	InitPWM(); 
	Delay1MS(5);	
	    
	#if 1
	do
        {
          if (PWRSW_L)
          {
              PWR_PULSE_L = 1;
           }
#if SUPPORT_INTERFACE_eSPI
        service_eSPI_handshake();   //SUPPORT_INTERFACE_eSPI //981004-200428-A
#endif
	} while (!SLP_S3_L);
    #endif	
	//981004-231002-A-S
	//SET_MASK(KSOH1, BIT4); //KSO 12 //EC_KBLED_EN
    //SET_MASK(KSOH1, BIT5); //KSO 13 //EC_LBLED_EN
	GPIO_Set_IO(56,1);
	GPIO_Set_IO(57,1);
	GPIO_Write(56,1);
	GPIO_Write(57,1);
    //981004-231002-A-E
	
	///InitSio();
	//PS2_PowerOn(); //981004-220615-R      
    Delay1MS(5); //981004-240424-M from 10
	//981004-231002-A-S
	//SET_MASK(KSOH1, BIT0); //KSO 8 //SD_RST_AUX
	//SET_MASK(KSOH1, BIT1); //KSO 9 //EC_SSDA_PWR_EN
	//SET_MASK(KSOH1, BIT2); //KSO 10 //EC_SSDB_PWR_EN
	//SET_MASK(KSOH1, BIT3); //KSO 11 //EC_WLAN_PWR_EN
	GPIO_Set_IO(48,1);
	GPIO_Set_IO(48,1);
	GPIO_Write(49,1);
	GPIO_Write(49,1);
	GPIO_Set_IO(50,1);
	GPIO_Set_IO(50,1);
	GPIO_Write(55,1);
	GPIO_Write(55,1);
	//981004-231002-A-E
	
	Delay1MS(4); //981004-240424-A
	Delay1MS(12); //981004-200611-A
	//KBRST_L = 1; //981004-220615-R
    ALL_SYS_PWRGD = 1;
	//Delay1MS(1); //981004-240424-R
	while (!IMVP_VR_READY); //981004-150519-M Rename by H/W request
    //Delay1MS(255); //981004-150423-R
    //Delay1MS(61); //981004-150423-R
    //Delay1MS(5); //981004-150423-R
	Delay1MS(99); //981004-150430-A        
    //PCH_PWROK = 1; //EC_ICH_PWROK //981004-240507-R
	
	//981004-220330-M-S
	if (!DEBUG_CARD_L)
	{
	    INIT_TM1650();
	}
    //981004-220330-M-E
	
	//981004-181205-R-S shift to S4 per BIOS request
	#if 0
	if(IS_MASK_SET(POWER_FLAG13, HDA_SDO_BIOS))  
    {
		ME_CNT = 0;   
        HDA_SDO = 0;
        CLEAR_MASK(POWER_FLAG13, HDA_SDO_BIOS);
    }
	#endif
    //981004-181205-R-E
	
    //981004-200410-R-S per EE request
    #if 0	
	USB_EN_EC = 1; 	
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	USB_EN_EC = 0;
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	USB_EN_EC = 1;
	#endif
	//981004-200410-R-E
		
	//981004-221005-M-S
	if (!AC_IN_L) //981004-221005-M	
	{
		H_PROCHOT_L = 0; //Normal
        dGPU_HOLD_EC_RST_L = 1; //Normal
		WTDP4 = 246; //981004-221005-A 
    }
    else
    {
		if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2)) //981004-221005-M
        {
		   H_PROCHOT_L = 1; //Normal
		   dGPU_HOLD_EC_RST_L = 1; //dGPU
           WTDP4 = 40;		   
        }
        else
		{
			if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) //EC RAM 0x211 bit4
	        {
				H_PROCHOT_L = 0; //Normal
				dGPU_HOLD_EC_RST_L = 1; //Normal
				WTDP4 = 45;
	        }
			else
			{
				H_PROCHOT_L = 1; //Normal
				dGPU_HOLD_EC_RST_L = 1; //dGPU
				if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                {
                   WTDP4 = 40;				
			    }
            }				
		}		
		//WTDP4 = 40;
	}
	//981004-221005-M-E
    
	pd1_ti_check_version(); //981004-211206-A
	//PDFW_GetVersion(); //981004-211117-A
	//S0_STATUS();	
	
	CLEAR_MASK(EC_Flag2, pdchgcur_step1); //981004-230621-A-S
	CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	CLEAR_MASK(EC_Flag2, pdchgcur_step4);
	CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230828-A
	CHGCUR_STEP_cnt2 = 0; //981004-230621-A-E
	
	//CLEAR_MASK(KSOLGPODR, KSO7ODEN); //Set KSO7 as push-pull //981004-231002-A

	GPIO_Set_IO(48,1);
	GPIO_Config(48,0,0,0);

	//SMBSW_RST_L = 1; //981004-231002-A
	if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A 
    {
	   ///SET_GPO_KSO6_HI(); //KSOLGOENR 0X1D0E BIT6 => 1 //HDD LED
	   GPIO_Set_IO(45,1);
	   GPIO_Write(45,1);
    }	   
	///SET_GPO_KSO4_HI(); //981004-231002-A
	GPIO_Set_IO(47,1);
	GPIO_Write(47,1);
	//981004-231212-A-S
	Clear_Ti_SmartAmp();
    Delay1MS(10); 
	//Init_Ti_SmartAmp(); 
	Delay1MS(255);
	Read_Ti_SmartAmp();
    //981004-231212-A-E
	 
//    H_PROCHOT_L = AC_IN_L ? 0 : 1; //981004-140505-A //Enable Processor hot	
    //EC_AMP_MUTE_L = 0; //981004-130412-A for DOS to mute	
	#if 0
    EC_AMP_MUTE_L = 1;
    WLAN_EN = 1;
    PCIE2_PWREN_L = 0;
    InitSio();
	#endif
    //Delay1MS(10);
    SX_S0CommVar();
}


//----------------------------------------------------------------------------
// S3 to S0 sequnce
//----------------------------------------------------------------------------
void Oem_S3S0Sequence(void)
{
    EC_EN_V5A = 1;
	//DoUSBCharge(); 
    USB_V5A_EN = 1;	
	USB_EN_EC = 1; //981004-200410-A
	
	//EN_5V_TBT = 1; //981004-200410-R
	///GPCRH1 = ALT;//981004-181107-A SMBUS D
	///GPCRH2 = ALT;//981004-181107-A SMBUS D
	GPIO_Func_Mode(100,1);
	GPIO_Func_Mode(101,1);
//	EC_WAKE_SCI_L = 0;
	//981004-121221-A-S
	SET_MASK(POWER_FLAG4, resume_from_s3);
	//Load_EXTimer2(); //981004-130412-A to unmute
    CLEAR_MASK(POWER_FLAG1, enter_S3);
    ///CLEAR_MASK(KBHISR, BIT2);
	CLEAR_MASK(KBC->STS,SYSF); //981004-130116-A
    //PWM1LHE = 0x00;	//981004-130410-A
	///GPCRA2 = OUTPUT+PULL_DW; //981004-210104-M from ALT
	GPIO_Set_IO(25,1);
	GPIO_Config(25,0,0,1); 		
    //PWR_LED_L = 0; //981004-210104-R
    BAT_LED_L = 1; //981004-210104-M	
    ///GPCRA4 = OUTPUT+PULL_DW; //981004-220719-A per SPEC
	GPIO_Set_IO(27,1);
	GPIO_Config(27,0,0,1); 
    if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
	{ 		   
        PWR_LED2_L = 0; //981004-220719-M
    }	 	
	//if (IS_MASK_SET(POWER_FLAG1, bt_on)) //981004-180731-R                      
			 //BT_LED = 1; //981004-180731-R
    //981004-230825-A-S
	///SET_MASK(KSOH1, BIT4); //KSO 12 //EC_KBLED_EN
    ///SET_MASK(KSOH1, BIT5); //KSO 13 //EC_LBLED_EN
	GPIO_Set_IO(56,1);
	GPIO_Set_IO(57,1);
	GPIO_Write(56,1);
	GPIO_Write(57,1);
    //981004-121221-A-E			 
    Delay1MS(4); //981004-240424-M from 10
	//981004-231002-A-S
	///SET_MASK(KSOH1, BIT0); //KSO 8 //SD_RST_AUX
	///SET_MASK(KSOH1, BIT1); //KSO 9 //EC_SSDA_PWR_EN
	///SET_MASK(KSOH1, BIT2); //KSO 10 //EC_SSDB_PWR_EN
	///SET_MASK(KSOH1, BIT3); //KSO 11 //EC_WLAN_PWR_EN
	GPIO_Set_IO(48,1);
	GPIO_Set_IO(48,1);
	GPIO_Write(49,1);
	GPIO_Write(49,1);
	GPIO_Set_IO(50,1);
	GPIO_Set_IO(50,1);
	GPIO_Write(55,1);
	GPIO_Write(55,1);
	//981004-231002-A-E
	Delay1MS(12); //981004-240424-M from 6
	InitPWM(); //981004-121122-A
	//KBRST_L = 1; //981004-220615-R
	//A20G_L = 1; //981004-150831-R // power button very soon after power off    
    ALL_SYS_PWRGD = 1;
    //Delay1MS(255); //981004-150423-R
    //Delay1MS(61); //981004-150423-R
    Delay1MS(4); //981004-150423-R
	EC_S3_DDR5_EN = 0; //981004-210818-A
	Delay1MS(95); //981004-150430-A  
    //PCH_PWROK = 1; //EC_ICH_PWROK //981004-240507-R	
	//CLEAR_MASK(POWER_FLAG11, bat80_qevent); //981004-150421-R
	//CLEAR_MASK(POWER_FLAG11, bat60_qevent); //981004-150421-R
	//CLEAR_MASK(POWER_FLAG11, bat40_qevent); //981004-150421-R
	//981004-200410-R-S per EE request
    #if 0    	
	USB_EN_EC = 1; 
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	USB_EN_EC = 0;
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	Delay1MS(255);
	USB_EN_EC = 1;
	#endif
	//981004-200410-R-E

    
    CLEAR_MASK(ProcsH, ProcsH_acout);
    ProcsH_cnt =0;
    CLEAR_MASK(ProcsH, ProcsH_scion20sec);
    ProcsH_scion_cnt = 0;    
    //H_PROCHOT_L = AC_IN_L ? 1 : 0; //981004-201021-M

    //981004-221005-R-S	
	#if 0
	if ((AC_IN_L) &&(IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4  //battery mode
	{	   
       if ((IS_MASK_SET(POWER_FLAG4, resume_from_s3)))
       {	   
	        dGPU_HOLD_EC_RST_L = 1;
	   }	
	}
	else
	{
      dGPU_HOLD_EC_RST_L = 0;	  
	}
    //dGPU_HOLD_EC_RST_L = AC_IN_L ? 1 : 0;
    //981004-170629-M-E	
    //H_PROCHOT_L = AC_IN_L ? 0 : 1;
	if ((AC_IN_L) &&(IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4  
	{	   
	   H_PROCHOT_L = 1; //981004-210401-M from 0
	}
	else
	{	  
      H_PROCHOT_L = 0; //981004-210401-M from 1	  
	  
	}
    WTDP4 = 20; //981004-210401-A
    #endif	
	//981004-221005-R-E
	
    SX_S0CommVar();
	///OEM_Cmd_B0();
    KBC_B0CMD(); 
}
//981004-130116-M-E

void DoPowerStatus(void)
{
    BYTE presentstatus;
    static bit SysStatusChange; 

    presentstatus = (POWER_FLAG2&(SLP_S3_ON+SLP_S4_ON));

    if (PowerStatusBK != presentstatus)      // To make sure all SLP is checked.
    {
        PowerStatusBK = presentstatus;
        SysStatusChange = 1;
        return;
    }

    if (!SysStatusChange)
        return;

    //switch (POWER_FLAG2 & (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON)) 
    switch (presentstatus)
    {
        case 0: 	                        // goto S5
            switch (SysPowState) 
            {
                case SYSTEM_S0 :                    				
                    Oem_TriggerS0S4(SC_S0SLPOff);
                    break;
                                        
                case SYSTEM_S3 :
                    Oem_TriggerS0S4(SC_S3S4SLPOff);
                    break;           
            }
           	break;

        //case (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON): // goto S0
        case (SLP_S3_ON+SLP_S4_ON):
            switch (SysPowState) 
            {
                case SYSTEM_S3 :
                    Oem_TriggerS3S0();
                    break;
                    
                case SYSTEM_S4 :
                    Oem_TriggerS4S0();
                    break;
            }

            break;            

        //case (SLP_S4_ON+SLP_S5_ON):             // goto S3
        case (SLP_S4_ON):
            switch (SysPowState) 
            {
                case SYSTEM_S0 :
                    Oem_TriggerS0S3(0x30);
                    break;
            }
            break;
    }

    SysStatusChange = 0;
}

//------------------------------------------------------------------------------
void CheckPowerState(void)
{
    switch (CheckPowerStateIndex)
    {
        case 0:
            SLP_S3_L ? SET_MASK(POWER_FLAG2, SLP_S3_ON):CLEAR_MASK(POWER_FLAG2, SLP_S3_ON);
            CheckPowerStateIndex ++;
            break;

        case 1:
            SLP_S4_L ? SET_MASK(POWER_FLAG2, SLP_S4_ON):CLEAR_MASK(POWER_FLAG2, SLP_S4_ON);
            CheckPowerStateIndex ++;
            break;
            
        case 2:
            DoPowerStatus();
            CheckPowerStateIndex = 0x00;
            break;

        default:
            CheckPowerStateIndex = 0x00;
            break;
    }
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S3(BYTE causecode)
{
    if(SystemIsS3)
        return;
    
    ShutDnCause = causecode;		// setup shutdown case
    SysPowState = SYSTEM_S0_S3;
    //PWSeqStep = 1;
    PowSeqDelay = 0x00;
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S4(BYTE causecode)
{
    if(SystemIsS4)
        return;
    
    ShutDnCause = causecode;		// setup shutdown case
    SysPowState = SYSTEM_S0_S4;
    //PWSeqStep = 1;
    PowSeqDelay = 0x00;
}


//-----------------------------------------------------------------------------
// process POWER OFF sequence
// entry: 	1¡Bpower shutdown case
//			2¡BS5 off or not
// Shutdown cause:
//	1:	0x8A command of 66 port
// 	2:	0x8B command of 66 port
//	3:	4secs Overrided
// 	4:	HWPG low
//	5:	0x8C command of 66 port
// 	6:	0x8D command of 66 port
//	7:	temperature to high
// 	8:
//	9:	Init. thermal chip fail
// 	10:	Check SLP // S0 -> S4
//	11:	Check SLP // S3 -> S5
// 	12:	Check SLP // S0 -> S5

//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// S0 to S3 sequence
//----------------------------------------------------------------------------
void Oem_S0S3Sequence(void)
{
    //981004-130116-M-S
    SET_MASK(POWER_FLAG1, enter_S3);	    
	//DCR5 = 0xE5; 
//    H_PROCHOT_L = AC_IN_L ? 1 : 0; //981004-140505-A //Disable Processor hot
    if (!AC_IN_L) //981004-221005-M	
	{	   
	   H_PROCHOT_L = 0; //Normal	   
	}
	else
	{
        if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2)) //981004-221005-M
        {		  
           H_PROCHOT_L = 1; //Normal
        }
        else
		{
			if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) //EC RAM 0x211 bit4
	        {
		          H_PROCHOT_L = 0; //Normal
	        }
			else
			{
				  H_PROCHOT_L = 1; //Normal
			}	
		}	
      		  
	}	
	WTDP4 = 40; //981004-221005-M from 20	
    //GPIO_A2_CTRL = ALT;
    ///GPCRA2 = ALT; //981004-210104-M from GPCRA1
	GPIO_Set_IO(25,1);
	GPIO_Config(25,0,0,1); 		       
	DCR2 = 0x00; //981004-210104-M from 0xE5
	///GPCRA4 = ALT; //981004-220719-A per SPEC
	GPIO_Set_IO(27,1);
	GPIO_Config(27,0,0,1); 	
	DCR4 = 0x00; //981004-220719-A per SPEC
	PWR_LED2_L = 1; //981004-220719-M 
    S0_S3Variable();
    //981004-130116-M-E
		
}



//-----------------------------------------------------------------
// S0 to S5 sequnce
//-----------------------------------------------------------------
void Oem_S0S4Sequence(void)
{   
    //Oem_S0S3Sequence(); //981004-130114-R
    S0_S4Variable();
    if (IS_MASK_SET(POWER_FLAG15, BAT_CUSTOM)) //981004-240422-A-S
    {
        ///BRAM2[0x20] = BAT_CHG_END;
        ///BRAM2[0x21] = POWER_FLAG15;
	    ///Do_SPI_Write_Status(SPIStatus_UnlockAll);
	    ///Do_SPI_Write_Enable();
        ////* Erase 1K 0x01F000~0x01F3FF. */
	    ///Do_SPI_Erase(SPICmd_SectorErase,
        ///            _EFLASH_NV_ADDRH,
        ///            _EFLASH_NV_ADDRM,
        ///            _EFLASH_NV_ADDRL);
	    ///Do_SPI_Write_Enable();
	    ///Do_SPI_Write_256Bytes(&BRAM2[0],
        ///                    _EFLASH_NV_ADDRH,
        ///                    _EFLASH_NV_ADDRM,
        ///                    _EFLASH_NV_ADDRL);
	    ///Do_SPI_Write_Disable();
    } //981004-240422-A-E
}

/* ----------------------------------------------------------------------------
 * FUNCTION: check Enter Deep Sleep mode
 *      Timer base : 500 ms
 * ------------------------------------------------------------------------- */
BYTE CheckEnterDeepSleep(void)
{
	BYTE result;
	result = 0x00;
    
    if(SystemIsS0)		                        // if system in S0
        result = 0x01;	
    if(SystemIsS3)		                        // if system in S3
        result = 0x01;	
    //if(IS_MASK_SET(POWER_FLAG1,adapter_in))		// AC power exist
	if ((IS_MASK_SET(POWER_FLAG1, adapter_in)) || (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))
        result = 0x01;	
    if(IS_MASK_SET(POWER_FLAG1,wait_PSW_off))	// power switch pressed
        result = 0x01;	

	if(result == 0x00)
	{
		if(DeepSleepCunt<10)        // Delay 5000 ms for EC deep sleep mode
		{
			DeepSleepCunt++;
			result = 0x02;
		}
		else
		{
			result = 0x00;
			DeepSleepCunt = 0x00;
		}
	}
    else
    {
        DeepSleepCunt = 0x00;
    }

	switch(result)
	{
		case 0:
			return(1);
			break;

		case 1:
			DeepSleepCunt=0x00;
			return(0);
			break;

		case 2:
			return(0);
			break;
	}
    return(0);
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Enter Deep Sleep mode
 * ------------------------------------------------------------------------- */
void EnterDeepSleep(void)
{
	#if 0
	IER0=0x00;				
	IER1=0x00;
	IER2=0x00;
	IER3=0x00;
	IER4=0x00;

	DisableAllInterrupt();

							// Disable module
	DisableADCChannel();	// Disable ADC
	DACPWRDN=0x3F;			// Disable DAC		

	KSOL = 0xFF;
	KSOH1 = 0xFF;
	KSOH2 = 0xFF;
	
	//*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************
	GPCRD0 = ALT;			// SUSB to alternate pin	
	//GPCRD1 = ALT;			// ACIN to alternate pin
	GPCRE4 = ALT;			// pwrsw to alternate pin
	GPCRE5 = ALT;			// NOVO Button to alternate pin  
	//*************************************************************************

	CGCTRL1R = 0xFF;
	CGCTRL2R = 0xFF;
	CGCTRL3R = 0xFF;

	//*************************************************************************
	// Set WUC interrupt function
	//*************************************************************************
   	WUENR2 = 0x23;      	// Wake-up enable WU25 for pwrsw
                           	// Wake-up enable WU20 for SUSB
                           	// Wake-up enable WU21 for acin

  	WUEMR2 = 0x20;      	// Wake-up Falling-edge WU25 for pwrsw
                            // Wake-up Rising-edge WU20 for SUSB
                            // Wake-up Rising-edge WU21 for ACIN

	WUENR4 = 0x01;         	// Wake-up enable WU40 for NOVO Button
   	WUEMR4 = 0x01;         	// Wake-up Edge WU40 for NOVO	 

   	IER0 |= (Int_WKO20+Int_WKINTAD);    // enable int 1 for  SUSB
   							            // enable int 5 for  NOVO button	
   	IER1 |= Int_WKO25;	    // enable int 14 for  pwrsw
	IER3 |= Int_WKO21;	    // enable int 31 for  ACIN

   	ISR0 = (Int_WKO20+Int_WKINTAD);     // clear int 1 for  SUSB
   							            // clear int 5 for  NOVO button	
   	ISR1 = Int_WKO25;	    // clear int 14 for  pwrsw
	ISR3 = Int_WKO21;	    // clear int 31 for  ACIN
	//*************************************************************************

	WUESR1 = 0xFF;			// clear wakeup status
	WUESR2 = 0xFF;
	WUESR3 = 0xFF;
	WUESR4 = 0xFF;

	_nop_();
	_nop_();

	EnableAllInterrupt();
	PLLCTRL = 1;
	PCON =2 ;             	// enter sleep mode

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	WUENR1 = 0x00;	
	WUENR2 = 0x00;	
	WUENR3 = 0x00;	
	WUENR4 = 0x00;	

	IER0=0x00;				
	IER1=0x00;
	IER2=0x00;
	IER3=0x00;
	IER4=0x00;

	//*************************************************************************
	//
	//*************************************************************************	
	GPCRD0 = INPUT;			// SUSB to alternate pin	
	//GPCRD1 = INPUT;			// ACIN to alternate pin
	GPCRE4 = INPUT;			// pwrsw to alternate pin
	GPCRE5 = INPUT;			// NOVO Button to alternate pin  
	//*************************************************************************

	WUESR1 = 0xff;
	WUESR2 = 0xff;
	WUESR3 = 0xff;
	WUESR4 = 0xff;

	CGCTRL1R = 000;
	CGCTRL2R = 0x00;
	CGCTRL3R = 0x00;
    
#if ADCFuncSupport  
	EnableADCChannel();		// enable ADC	
#endif	

	DACPWRDN=0x00;			// enable DAC	
	Enable_Any_Key_Irq();	// Enable Keyboard
	Init_Timers();

	#endif
}


//-----------------------------------------------------------------------------
// Handle System Power Control
// Called by service_1mS -> Timer1msEvent -> Hook_Timer1msEvent
//-----------------------------------------------------------------------------
void Oem_SysPowerContrl(void)
{
    // Check if delay doing PowerSeq is needed.
    if (DelayDoPowerSeq != 0x00)
    {
        DelayDoPowerSeq--;

        if (DelayDoPowerSeq != 0x00)
            return;
    }

    //if ((SystemIsS0) || (SystemIsS3) || (SystemIsS4))
    if (SysPowState & 0xF0)
        CheckPowerState();

    // Check current System PowerState to see what should we do.
    switch (SysPowState)
    {
        case SYSTEM_S4_S0:
            Oem_S4S0Sequence();
            break;

        case SYSTEM_S3_S0:
            Oem_S3S0Sequence();
            break;

        case SYSTEM_S0_S3:
            Oem_S0S3Sequence();
            break;

        case SYSTEM_S0_S4:		    
            Oem_S0S4Sequence();
            break;

        case SYSTEM_EC_WDTRST:
            InternalWDTNow();
            break;

        default:
            break;
    }
}


void CheckResetSource(void)
{
    switch(RSTStatus&0x03)
    {
        case 0:
        case 1:
            if(GPIO_ReadIOType(22) == 0)//if (GPCRA0 == 0x84)
                ShutDnCause = SC_ECColdBoot;
            else
                ShutDnCause = SC_EC_0x0000;
            break;
            
        case 2:
            if(GPIO_ReadIOType(22) == 0)//if (GPCRA0 == 0x84)
                ShutDnCause = SC_IntWatchDog;
            else
                ShutDnCause = SC_EC_0x0000;
            break;         

        case 3:
            if(GPIO_ReadIOType(22) == 0)//if (GPCRA0 == 0x84)
                ShutDnCause = SC_ExtWatchDog;
            else
                ShutDnCause = SC_EC_0x0000;
            
            break;
    }
}

//-----------------------------------------------------------------------------
// The function of pulsing S.B. power button 100ms
//-----------------------------------------------------------------------------
void PulseSBPowerButton(void)
{
    PWR_PULSE_L = 0;
    SBSWReleaseCunt = 20;   // decrease timer base is 10ms total time 200ms
}

//-----------------------------------------------------------------------------
// The function of releasing S.B. power button
//-----------------------------------------------------------------------------
void CheckSBPowerButton(void)
{
    if (SBSWReleaseCunt != 0x00)
    {
        SBSWReleaseCunt--;

        if (SBSWReleaseCunt == 0x00)
			    PWR_PULSE_L = 1;
    }
}

void InitPWM(void)
{
   ///這邊作為LED FAN inital PWM的地方
   
   /// ZTIER = 0x00;
	///PCSSGL = 0x00; //Select Channel 3 to choose C0CPRS as Prescaler divider ---0x180C //981004-131113-A
	///PCSSGH = 0xE5; //Select Channel 5 to choose C4CPRS as Prescaler divider ---0x180D // from 0xE1	   
	///PCFSR = 0x8F;//prescaler clock freq selects EC clock (about 9.2MHz) ---0x180B for all Group 
    //PCFSR = 0x8B; //981004-130410-M	
    ///C0CPRS = 0x01; //PWM input clock is divided by 1 ---0x1800//0xB2 (from 200 to 20K Hz) for fan (PWM0)    
	//PWM_C4CPRS = 0x28; //PWM input clock is divided by 40 ---0x1800// 0x23 (1000 Hz) for brightness (PWM5)
    //PWM_C4CPRS = 0xC7; //PWM input clock is divided by 199 ---0x1800// 0x28 (200 Hz) for brightness (PWM5)
    ///C4CPRS = 0x4F; //PWM input clock is divided by 79 ---0x1800  // 0xC7 (500 Hz) for brightness (PWM5)
    //C6CPRS = 0x01; //PWM input clock is divided by 1 ---0x1800//0xB2 (from 200 to 20K Hz) for fan (PWM6) 
    //C6CPRS = 0x28; //PWM input clock is divided by 40 ---0x1800//0xB2 (1K Hz) 
    //C6CPRS = 0x4F; //PWM input clock is divided by 79 ---0x1800//0xB2 (500 Hz)
    ///C6CPRS = 0xC7; //PWM input clock is divided by 199 ---0x182B//0xB2 (200 Hz) //981004-140609-M for some keyboard backlight is too bright 
    //C7CPRS = 0x4F; //PWM input clock is divided by 79 ---0x182D  // 0xC7 (500 Hz) for brightness (PWM7)	
	///C7CPRS = 0x28; //PWM input clock is divided by 40 ---0x182D  // 0xC7 (1000 Hz) for brightness (PWM7) (PWM Control frequency)	
    ///CTR = 0xE5; //prescaler output clock is divided by 229 ---0x1801    
    //DCR6 = KBbclCtrl(KB_Level); //981004-200410-R
    
	EC_BKLOUT = 1; //981004-130107-A	
    ///ZTIER = 0x02;                        //Enable PWM clock counter 

    //IPOLR3 &= 0x7F; //981004-121227-A for GC6 interrupt initiation
//    IER3 |= 0x80; //981004-121227-A	for GC6 interrupt initiation  	
	
}

void InitDevice(void)
{

    //981004-180731-R-S 
    #if 0  
    if (IS_MASK_SET(POWER_FLAG2, wlan_on) && (IS_MASK_SET(POWER_FLAG2, sci_on)))
	{        
        WLAN_LED = 1;			         	
    }
    else
    {	   
        WLAN_LED = 0;
    }
    #endif
    //981004-180731-R-E
	
	WLAN_EN = 1; 
	
	//981004-191001-M-S
    //CCD_EN = IS_MASK_SET(POWER_FLAG1, ccd_on) ? 1 : 0;
	SET_MASK(POWER_FLAG1, ccd_on);
    CCD_EN = 1;
    //981004-191001-M-E 
    //KSOLGOENR |= KSO0GOEN; //Set KSO0 GPIO function to high (0X1D0E) //981004-220629-A
    GPIO_Set_IO(41,1);
    GPIO_Write(41,1);
	    
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
   
	SET_MASK(POWER_FLAG6, adjustfan);
	FanRPM1=0x39; //981004-200410-M from 0x5D
	FanRPM2=0x39; //981004-200410-M from 0x5D 
	
    //HD_LED = 1; //981004-180731-R	
    EC_AMP_MUTE_L =0; //981004-210720-M from 1  
    CLEAR_MASK(POWER_FLAG9, lcd_off);
	EC_BKLOUT = 1; 	
    DDS_PANEL_RST = 1; //981004-231002-A 	
    patchACout = 0; 
    Fullchgcnt =0; 
    
	//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
	if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) && (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) && (IS_MASK_CLEAR(POWER_FLAG8, pd_ac_over65w2))) //battery mode
	{	   
	   NVDeventStatus = 0x0A; //981004-201021-M from 0 to prevent system shutdown
	}
	else if (!AC_IN_L)
	{	  
       NVDeventStatus = 0x01; //981004-201021-M from 1 to prevent system shutdown     
	}
	else if ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) 
	//else if (!PD_ADAPTER_IN)	
    {
       ECQEvent(SCI_NV_DB, SCIMode_ACPI_SMBus);  //0xDB
       PD_Adapter_setting();		 
    } 
    //NVDeventStatus = AC_IN_L ? 0x0A : 0x01;
    USB_KBD_PWR = 1; //981004-221014-A	
    	
	//981004-210705-A-S
	#if 1
    LSCTRL = 0x02; //Active mode (EC RAM : 0x28F) 	
    //(bRWSMBus(SMbusChB, SMbusWB, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC));
    SMBUS_RW_B(SMbusChB, WriteByte, LightSensorAddr, CONTROL, &LSCTRL); 
    Delay1MS(10);
    // (bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_L, &LS_DATA_L, SMBus_NoPEC));
	// (bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_M, &LS_DATA_M, SMBus_NoPEC));    
	// (bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, DATAREAD_H, &LS_DATA_H, SMBus_NoPEC));
	// (bRWSMBus(SMbusChB, SMbusRB, LightSensorAddr, CONTROL, &LSCTRL, SMBus_NoPEC)); //981004-210705-A

    SMBUS_RW_B(SMbusChB, ReadByte, LightSensorAddr, DATAREAD_L, &LS_DATA_L);
    SMBUS_RW_B(SMbusChB, ReadByte, LightSensorAddr, DATAREAD_M, &LS_DATA_M);
    SMBUS_RW_B(SMbusChB, ReadByte, LightSensorAddr, DATAREAD_H, &LS_DATA_H);
    SMBUS_RW_B(SMbusChB, ReadByte, LightSensorAddr, CONTROL, &LSCTRL);
    Lux_TEMP = ((LS_DATA_H<<16) | (LS_DATA_M<<8) | (LS_DATA_L)); //981004-210705-M	
	#endif
    //981004-210705-A-S
	         
    SET_MASK(POWER_FLAG1, power_on);
	//SET_MASK(POWER_FLAG3, ps2_on);         
	SET_MASK(POWER_FLAG2, lid_open);                                                                            
    SET_MASK(POWER_FLAG6, GPU_on);              
    ///IER1 |= 0x08; // enable KSI interrupt
	CLEAR_MASK(POWER_FLAG5, bios_cf9);

	TI_FW_CHECK(); //981004-211119-A
	//SET_TEMP_NCT7802(); //981004-220803-A
	//Mode_SEL = 0x6A; //REG : 0x22 =>  Thermistor mode //981004-220803-M from 0x0A
    //bRWSMBus(SMbusCh1, SMbusWB, NCT7802YAddr, NCT_MODE_SEL, &Mode_SEL ,  SMBus_NoPEC);
	BAT_OPTION3 = 0x4402; //981004-221013-M from 0x4412 to adjust ACDET deglitch time to 150ms//BQ24780s to enable Boost mode
    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option3, (uint8_t*)&BAT_OPTION3 ,  SMBus_NoPEC); //981004-220803-A
	SMBUS_RW_W(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option3, &BAT_OPTION3);
	//981004-231108-A-S
	NCT7601_CH1_On = 0xFF;
	//bRWSMBus(SMbusCh1, SMbusWB, Thermal1_Addr, Thermal1_CH1_Enable, &NCT7601_CH1_On , SMBus_NoPEC); //Thermal IC NCT7601Y 
     SMBUS_RW_B(SMbusCh1, SMbusWB, Thermal1_Addr, Thermal1_CH1_Enable, &NCT7601_CH1_On);  
	NCT7601_Start = 0x01;
    //bRWSMBus(SMbusCh1, SMbusWB, Thermal1_Addr, Thermal1_Config, &NCT7601_Start , SMBus_NoPEC); //Thermal IC NCT7601Y
    SMBUS_RW_B(SMbusCh1, SMbusWB, Thermal1_Addr, Thermal1_Config, &NCT7601_Start);
	//981004-231108-A-E
	
	///SET_GPO_KSO7_HI(); //SET_MASK(KSOL, BIT7) //981004-221111-A
    GPIO_Set_IO(48,1);
    GPIO_Write(48,1);
    KSO7_CNT = 0; //981004-221111-A		
	#if 0 //981004-231030-R
	bRSMBusBlock(SMbusCh1, SMbusRBK, SmartBat_Addr, C_Dname , &BAT_DEVNAME); //981004-220510-A     
	if ((BAT_DEVNAME == 0x4741472D)) //4 Cell => 0x4741472D //Old 99Watt //981004-220510-A
    {	    
        SET_MASK(EC_Flag4, old_99w); //0x388 BIT5		
    }
    else //New : 0x4741442D not 0X47414B34 
    {	          	        
        CLEAR_MASK(EC_Flag4, old_99w);        		
    }
	#endif
    ///SET_GPO_KSO12_HI(); //981004-231017-A //EC_KBLED_EN
	///SET_GPO_KSO13_HI(); //981004-231017-A //EC_LBLED_EN	
	///SET_GPO_KSO0_HI(); //981004-231120-A PER EE request
	///SET_GPO_KSO3_HI(); //DMIC SEL
    GPIO_Set_IO(56,1);
    GPIO_Write(56,1);
    GPIO_Set_IO(57,1);
    GPIO_Write(57,1);
    GPIO_Set_IO(41,1);
    GPIO_Write(41,1);
    GPIO_Set_IO(44,1);
    GPIO_Write(44,1);
}

//981004-200410-R-S
#if 0
BYTE KBbclCtrl(BYTE level) 
{
    switch (level)
    {
        case 0x00:
            return(0x00);
            
        case 0x01:
            return(0x0F); 
            
        case 0x02:
            return(0x33); 

        default:
            return(0x00);
    }      
#endif
//981004-200410-R-E

//981004-180712-A-S
//-----------------------------------------------------------------------------
void INIT_TM1650(void)
{
#if 0   
    I2C_WR_BUFFER[0] = 0x41;    //Brightness = 4,
    I2C_WriteStream(SMbusCh5, 0x48, &I2C_WR_BUFFER[0], 1);
    I2C_WR_BUFFER[0] = 0x3F;
    I2C_WriteStream(SMbusCh5, 0x68, &I2C_WR_BUFFER[0], 1);
    I2C_WR_BUFFER[0] = 0x06;
    I2C_WriteStream(SMbusCh5, 0x6A, &I2C_WR_BUFFER[0], 1);
    I2C_WR_BUFFER[0] = 0x5B;
    I2C_WriteStream(SMbusCh5, 0x6C, &I2C_WR_BUFFER[0], 1);
    I2C_WR_BUFFER[0] = 0x4F;
    I2C_WriteStream(SMbusCh5, 0x6E, &I2C_WR_BUFFER[0], 1);

    Last_P81HDR = P81HDR;
    Last_P80HDR = P80HDR;

    bRWSMBus(SMbusCh5, SMbusSBC, 0x48,
                0x59, &I2C_WR_BUFFER[0], 0);

    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[P80HDR & 0x0F];
    bRWSMBus(SMbusCh5, SMbusSBC, 0x68,
                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[(P80HDR >> 4) & 0x0F];
    bRWSMBus(SMbusCh5, SMbusSBC, 0x6A,
                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[P81HDR & 0x0F];
    bRWSMBus(SMbusCh5, SMbusSBC, 0x6C,
                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
    I2C_WR_BUFFER[0] = 0x0F;    //LED7s_TABLE[(P81HDR >> 4) & 0x0F];
    bRWSMBus(SMbusCh5, SMbusSBC, 0x6E,
                I2C_WR_BUFFER[0], &I2C_WR_BUFFER[0], 0);
#endif
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

//981004-200721-A-S
/*-----------------------------------------------------------------------------
/*****************************************************************************/
/*****************************************************************************/
/*-----------------------------------------------------------------------------
 *-----------+-----------------------------------------------------------------
 * @function | Service for Windows Modern Standby
 *-----------+-----------------------------------------------------------------
 * @model    | Notebook Computer Embedded Controller Firmware
 * @version  | 1.0.0.0
 * @author   | Michael.Kuo@ite.com.tw
 * @note     | Copyright(c)201-2020, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
/*****************************************************************************/
/*****************************************************************************/
/*-----------------------------------------------------------------------------
 * @fn         InitEntry_DeepSleep
 * @details    Initialize the chip setting before enter the DeepSleep.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitEntry_DeepSleep(void)
{
    Oem_S0S3Sequence(); //981004-200721-A
}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_DeepSleep
 * @details    Initialize the chip setting after exit the DeepSleep.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitExit_DeepSleep(void)
{
   Oem_S3S0Sequence(); //981004-200721-A
}

/*-----------------------------------------------------------------------------
 * @fn         CheckCanGo_AthenaIdle
 * @details    Check the status can switch to Athena idle mode.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void CheckCanGo_AthenaIdle(void)
{


}

/*-----------------------------------------------------------------------------
 * @fn         InitEntry_AthenaIdle
 * @details    Initialize the chip setting before enter the Athena idle.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitEntry_AthenaIdle(void)
{


}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_AthenaIdle
 * @details    Initialize the chip setting after exit Athena idle.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitExit_AthenaIdle(void)
{


}

/*-----------------------------------------------------------------------------
 * @fn         InitEntry_ModernStandby
 * @details    Initialize the chip setting before enter the ModernStandby.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitEntry_ModernStandby(void)
{
    /**
     * @brief  Enable Lid wake up before entry Modern Standby.
     */
    if (IS_LID_SW_CLOSE())
    {
        xMSBY_EnLidOpenWake = 1;
        /* Lid State (Lid Open = 1) */
        CLEAR_MASK(xEC_PWER, F_PWER_LSTE);
    }
    /**
     * @brief  Turns-off PECI, pull Low is better.
     */
    ///GPCRF6 = OUTPUT;
    GPIO_Set_IO(120,1);
    ///PECI_EC_LO();
    GPIO_Write(120,0);
    /**
     * @brief  Turns-off ADC/PWM clock.
     */
    ///CLEAR_MASK(ADCCFG, ADCEN);
    ADC->CTRL_b.EN = 0;
    ///CLEAR_MASK(ZTIER, BIT1);
    SYS_CLKPWR_PWM4(disable);
    //DCR0 = 0;   /* Fan Off */ //981004-200721-R
	#if 0
	DCR3 = 0;   /* Fan Off */ //981004-200721-A
	//981004-220916-A-S
	SET_MASK(POWER_FLAG12, EC_modern_stby); 	
	PWR_LED2_L = 1; 
	USB_KBD_PWR = 0;
	#endif
	//981004-220916-A-S
    xMSBY_ExitKey = 0;
    wMSBY_SLP_S0_HiT = 0;
}

/*-----------------------------------------------------------------------------
 * @fn         InitExit_ModernStandby
 * @details    Initialize the chip setting after exit the ModernStandby.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitExit_ModernStandby(void)
{
    /* Enable ADC */
    ///SET_MASK(ADCCFG, ADCEN);
    ADC->CTRL_b.EN = 1;
    /* Enable PWM */
    ///SET_MASK(ZTIER, BIT1);
    SYS_CLKPWR_PWM4(enable);
    //DCR0 = 0x50; //981004-200721-R
	#if 0
	DCR3 = 0x50; //981004-200721-A
	//981004-220916-A-S	
	if (IS_MASK_CLEAR(POWER_FLAG8, ALL_LED_OFF)) //EC RAM 0x208 bit3 //981004-240529-A
	{ 		   
        PWR_LED2_L = 0; //981004-220719-M
    }	
	USB_KBD_PWR = 1;
	CLEAR_MASK(POWER_FLAG12, EC_modern_stby); //981004-200721-A
	#endif
	//981004-220916-A-S
    ///Init_Timers();
    ///SET_MASK(IER3, Int_EXTimer);
    ///CLEAR_MASK(IER1, Int_WKO25);    //Power button INT
    ///CLEAR_MASK(IER0, Int_WKINTAD);  //eSPI INT
    ///Init_PECI();
	CLEAR_MASK(POWER_FLAG12, EC_modern_stby); //981004-200721-A
}

/*-----------------------------------------------------------------------------
 * @fn         SET_ExitMS
 * @details    Set exit ModernStandby with Exit Code.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void SET_ExitMS(BYTE ExitCode, BYTE ExitTsec)
{
    xMSBY_ExitKey = ExitCode;
    xMSBY_ServiceKey = 0xFF;
    wMSBY_EnterDelay = ExitTsec * 1000;
}

/*-----------------------------------------------------------------------------
 * @fn         InitSleep_ModernStandby
 * @details    Initialize the chip setting before enter the Chip power down.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitSleep_ModernStandby(void)
{
    #if 0
    ///DisableAllInterrupt();
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    /**
     * @brief  Clear PowerDownRejectTag for check interrupt comes out when
     *         doing the enable step.
     */
    F_PowerDownRejectTag = 0;
    /**
     * @brief  Setting 2 sec wakeup timer for service ModernStandby.
     */
    /* Prescaler 32.768KHz, count 65535 = 2s. */

    //981004-210628-M-S
    ET2PSR = 0x00;   // Prescaler 32.768K HZ //981004-200721-R
	//ET2PSR = 0x02; // SELECT 32 Hz //0x1F0A //981004-200721-A
	ET2CNTLH2R = 0x01; //0x1F0E //981004-210623-M from 0x00
	ET2CNTLHR = 0x00; // 0x1F0B
	ET2CNTLLR = 0x00; //0x1F0C (2 seconds) //(0x010000/32768 = 2) //981004-200721-A Refer to CORE_TIMERS
    //981004-210628-M-E    
   
    //ET2CNTLLR = 0x80; // 0x1F0C //981004-200721-R

    ISR7 = BIT2;            // Write to clear external timer 2 interrupt
    SET_MASK(IER7, BIT2);   // Enable external timer 2 interrupt

#if 1
    WUC_Enable_WUx_Interrupt(WU25, WUC_Falling, Wake_Up_Enable);
    SET_MASK(IER1, Int_WKO25);      //PWRSW@GPE.4

    /**
     * @brief  Latest enable important Host eSPI/LPC Bus interrupt.
     */
    SET_MASK(IER3, Int_KBCIBF);     //REG@1107.0
    SET_MASK(IER3, Int_PMCIBF);     //REG@1107.1
    WUC_Enable_WUx_Interrupt(WU42, WUC_Falling, Wake_Up_Enable); //P92 eSPI
    ISR0 = Int_WKINTAD;  //REG@1100.5
    SET_MASK(IER0, Int_WKINTAD);  //REG@1104.5 LPC|eSPI
	
	SET_MASK(POWER_FLAG12, EC_modern_stby); //981004-200721-A
#endif
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         InitWake_ModernStandby
 * @details    Initialize the chip setting after exit the Chip power down.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void InitWake_ModernStandby(void)
{
    #if 0
    DisableAllInterrupt();
    CLEAR_MASK(IER7, BIT2); // Disable external timer 2 interrupt
    /* Prescaler 32.768KHz, count 65535 = 2s. */
    //ET2PSR = 0x00;   // Prescaler 32.768K HZ //981004-200721-R
	ET2PSR = 0x02; // SELECT 32 Hz //0x1F0A //981004-200721-A
	ET2CNTLLR = 0x40; //0x1F0C (2 seconds) //(0x0040/32 = 2) //981004-200721-A Refer to CORE_TIMERS
    ET2CNTLH2R = 0x00; //0x1F0E
    ET2CNTLHR = 0x00; // 0x1F0B
    //ET2CNTLLR = 0x80; // 0x1F0C //981004-200721-R

    ISR7 = BIT2;            // Write to clear external timer 2 interrupt
    SET_MASK(IER7, BIT2);   // Enable external timer 2 interrupt

    Init_Timers();
    #endif
}

/*-----------------------------------------------------------------------------
 * @fn         CheckCanGo_ModernStandby
 * @details    Check the status can switch to Modern Standby mode.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void CheckCanGo_ModernStandby(void)
{
	#if 0
    if (IS_EC_PWRSW_DN() || (VWIDX2 != 0x77))   //0x77 = S0 (ModernStadby is S0iX)
    {
        return;
    }	
    //if (IS_MASK_CLEAR(SystemFlag1, F_ACPI_MODE))
    //{
        //return;
    //}
	if (IS_MASK_CLEAR(POWER_FLAG2, sci_on))
    {
        return;
    }	
    if (wMSBY_EnterDelay > 0)
    {
        wMSBY_EnterDelay--;
        return;
    }
    /**
     * @brief  Check SLP_S0# keep low 2 sec
     */
    if (IS_SLP_S0_CS_HI())
    {
        wMSBY_SLP_S0_LoT = 0;
        return;
    }
    if (wMSBY_SLP_S0_LoT < 2000)
    {
        wMSBY_SLP_S0_LoT++;
        return;
    }
    xMSBY_Mode = _EC_MODERN_STANDBY;
	#endif
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_CheckLidStatus
 * @details    Check Lid Stats in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_CheckLidStatus(void)
{
    if (IS_LID_SW_CLOSE())
    {
        xMSBY_EnLidOpenWake = 1;
        /* Lid State (Lid Closed = 0) */
        CLEAR_MASK(xEC_PWER, F_PWER_LSTE);
    }
    else
    {
        /* Lid State (Lid Open = 1) */
        SET_MASK(xEC_PWER, F_PWER_LSTE);
        if (xMSBY_EnLidOpenWake > 0)
        {
            SET_ExitMS(0x1D, 4);            
            //ECQEvent(SCI_LIDOPEN, SCIMode_ACPI_SMBus);
			SET_MASK(POWER_FLAG2, lid_open); //981004-200708-A
			ECQEvent(SCI_LID_CHANGE, SCIMode_ACPI_SMBus);  //0x70 //981004-200708-A
            ///OEM_ACPI_Gen_Int();
            ACPI_SCI_OUT(ACPISCI);
        }
    }
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_DeviceContrlA
 * @details    Device Control in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_DeviceContrlA(void)
{
#if 0
    /**
     * @brief  Process Intel RVP Debug LED.
     */
    if ((Last_P81HDR != P81HDR) || (Last_P80HDR != P80HDR))
    {
//        Process_DebugCodeLED();
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetBatteryStatus
 * @details    Get Battery status in ModernStandby wakeup service.
 * @upstream - By call - Sleep Duty: 2sec
 * @ingroup    ModernStandby
 */
void HookMS_GetBatteryStatus(void)
{
    xMSBY_GetBatteryStep++;
    if (xMSBY_GetBatteryStep == 1)
    {
        //bRWSMBus(SMbusCh1, SMbusRW, _SMB_BatteryAddr,
        //            _CMD_RemainingCapacity,
        //            &I2C_RD_BUFFER[0],
        //            0);
        //BAT1_RemainingCapacity = (I2C_RD_BUFFER[1] << 8) +
        //                          I2C_RD_BUFFER[0];
        //xEC_B1RC  = I2C_RD_BUFFER[0];
        //xEC_B1RCH = I2C_RD_BUFFER[1];
		
		//981004-200708-A-S
		(bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RMcap, (uint8_t*)&BAT_RMCAP, SMBus_NoPEC));
		BAT_RMCAP = (BAT_RMCAP<<8)|(BAT_RMCAP>>8); 
		RMCAP_TEMP2 = BAT_RMCAP;
		if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-220510-A
	    {
		   FCC_Ratio = Check_FCC_Ratio1(); 			
           BAT_RMCAP3 = BAT_RMCAP * FCC_Ratio; 			
           BAT_RMCAP = BAT_RMCAP * FCC_Ratio;
		} 
		else
		{
		   BAT_RMCAP = BAT_RMCAP;	
		}
        BAT_RMCAP = (BAT_RMCAP<<8)|(BAT_RMCAP>>8); //981004-231002-A
        RMCAP_TEMP = (BAT_RMCAP<<8)|(BAT_RMCAP>>8); //981004-231002-A
       
		//981004-200708-A-E
    }
    else if (xMSBY_GetBatteryStep == 2)
    {
        //bRWSMBus(SMbusCh1, SMbusRW, _SMB_BatteryAddr,
        //            _CMD_FullChargeCapacity,
        //            &I2C_RD_BUFFER[0],
        //            0);
        //BAT1_FullChargeCapacity = (I2C_RD_BUFFER[1] << 8) +
        //                           I2C_RD_BUFFER[0];
        //xEC_B1FC  = I2C_RD_BUFFER[0];
        //xEC_B1FCH = I2C_RD_BUFFER[1];
		
		//981004-200708-A-S
		//Ship mode
        if (RMCAP_TEMP < 75) //7640*0.005 = 38 //981004-221005-M from 64
        { 	     
          BAT_CHGCURR = 0x0000; 
          BAT_CHGVOL = 0x0000;
          BAT_INCURR = 0x0000; 
          BAT_OPTION = 0x49F1; //Battery only setting + Inhibit charging for BQ24780 from 0x48F1 default + BIT0 =>  Inhibit charging (POR : 0x48F1+BI0= 0x49F1) 
	
          bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, (uint8_t*)&BAT_CHGCURR , SMBus_NoPEC);
          bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage,  (uint8_t*)&BAT_CHGVOL , SMBus_NoPEC);
          bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,   (uint8_t*)&BAT_INCURR ,  SMBus_NoPEC);    
          bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,   (uint8_t*)&BAT_OPTION ,  SMBus_NoPEC); 
		  
          Ship_mode = 0x1000;       
          bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access,  (uint8_t*)&Ship_mode, SMBus_NoPEC);
          Delay1MS(250);        
          bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access,  (uint8_t*)&Ship_mode, SMBus_NoPEC);
          for(ITempB01=0x00;ITempB01<20;ITempB01++)	//240us loop
          {
              Delay1MS(250);         		
          }
        }
		//981004-200708-A-E
    }
    else
    {
        xMSBY_GetBatteryStep = 0;
    }
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetThermalStatus
 * @details    Get thermal status in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_GetThermalStatus(void)
{
    xMSBY_GetThermalStep++;
    if (xMSBY_GetThermalStep == 1)
    {
		//Init_PECI();
        //ReadCPUTemp();
		(bRWSMBus(SMbusChB, SMbusRB, GPUThermalAddr2, RLTS, &GPU_TMPR, SMBus_NoPEC)); //981004-210622-A
        vMoniterTemprature(); //981004-210622-A		
		///GPCRF6 = OUTPUT;
        GPIO_Set_IO(120,1);
        ///PECI_EC_LO();
    }
    else if (xMSBY_GetThermalStep == 2)
    {

    }
    else
    {
        xMSBY_GetThermalStep = 0;
    }
}

/*-----------------------------------------------------------------------------
 * @fn         HookMS_GetThermalStatus
 * @details    Get thermal status in ModernStandby wakeup service.
 * @upstream - By call
 * @ingroup    ModernStandby
 */
void HookMS_CheckExitCondition(void)
{
    #if 0
    if (IS_EC_PWRSW_DN())
    {
        SET_ExitMS(0xBB, 2);
        return;
    }
	#if 0
    if (IS_ADAPTER_IN())
    {
        SET_ExitMS(0xAC, 8);
        return;
    }
	#endif
    if (IS_GPI_KEYDN_WIN())
    {
        SET_ExitMS(0xD1, 8);
        return;
    }
#if 1   // 0:The test not with platform
    if (VWIDX2 != 0x77)
    {
        SET_ExitMS(0x77, 20);
        return;
    }
#endif
#endif
}

/*-----------------------------------------------------------------------------
 * @fn         Hook_ModernStandbyService1ms
 * @details    Do the 1ms service steps after Wake from Modern Standby.
 * @upstream - By call
 * @ingroup    ModernStandby
 * @retval     End of service (enter power down) -> xMSBY_ServiceKey = 0
 * @retval     Keep in ModernStandby -> xMSBY_ExitKey = 0
 */
void Hook_ModernStandbyService1ms(void)
{
    #if 0	
    if (xMSBY_SleepDelay > 0)
    {
        xMSBY_SleepDelay--;
    }
    switch(xMSBY_ServiceKey)
    {
    case 0:
        HookMS_CheckLidStatus();
        xMSBY_ServiceKey++;
        break;

    case 1:
        HookMS_DeviceContrlA();
        xMSBY_ServiceKey++;
        break;

    case 2:
        //HookMS_GetBatteryStatus(); //981004-220916-R
        xMSBY_ServiceKey++;
        break;

    case 3:
        //HookMS_GetThermalStatus(); //981004-220916-R
        xMSBY_ServiceKey++;
        break;

    case 4:
        HookMS_CheckExitCondition();
        xMSBY_ServiceKey++;
        break;

    default:
        if (IS_SLP_S0_CS_HI())
        {
            if (wMSBY_SLP_S0_HiT < 1000)    /* Detect SLP_S0# Hi 1sec */
            {
                wMSBY_SLP_S0_HiT++;
            }
            else
            {
                SET_ExitMS(0x51, 4);
            }
        }
        else
        {
            wMSBY_SLP_S0_HiT = 0;
            xMSBY_ServiceKey = 0xFF;    /* GoTo Sleep */
        }
        break;
    }
	#endif
}

/*-----------------------------------------------------------------------------
 * @fn         Hook_ModernStandbyService
 * @details    Do the loop service after Wake from Modern Standby.
 * @upstream - By call
 * @ingroup    ModernStandby
 * @retval     End of service (enter power down) -> xMSBY_ServiceKey = 0
 * @retval     Keep in ModernStandby -> xMSBY_ExitKey = 0
 */
void Hook_ModernStandbyService(void)
{
    xMSBY_ServiceKey = 0;
    while(1)
    {
		//981004-200721-A-S
        if (xEC_CMDR > 0)
        {
            Hook_Intel_Cmd();
        }
		//981004-200721-A-E
        /**
        * @brief  ACK eSPI Bus hand shake.
        */
        EC_ACK_eSPI_Reset();
        /**
        * @brief  Process Host Command/Data and setting 20ms delay into
        *         power down for quickly response next command.
        */
        ///if (IS_MASK_SET(KBHISR, P_IBF))

        #if 0
        if(IS_MASK_SET(KBC->STS,P_IBF))
        {
            service_pci1();
            xMSBY_SleepDelay = 10;  /* Host command/data delay 10ms */
            continue;
        }
        if (IS_MASK_SET(PM1STS, P_IBF))
        {
            SetTotalBurstTime();
            service_pci2f();
            xMSBY_SleepDelay = 10;  /* Host command/data delay 10ms */
            continue;
        }
        if (F_Service_MS_1 != 0x00)
        {
            F_Service_MS_1 = 0;
            Hook_ModernStandbyService1ms();
            service_Low_LVEvent();
        }
        if ((xMSBY_ExitKey != 0x00) ||
            (xMSBY_ServiceKey == 0xFF))
        {
            break;
        }
        EnableModuleInterrupt();
        xMSBY_DozeCounter++;
        PCON = 1;       // enter idle mode
        /* Wake-up Delay */
        _nop_();        /* 1st // Repeat "nop" eight times immediately */
        _nop_();        /* 2nd // for internal bus turn-around. */
        _nop_();        /* 3rd */
        _nop_();        /* 4th */
        _nop_();        /* 5th */
        _nop_();        /* 6th */
        _nop_();        /* 7th */
        _nop_();        /* 8th */
        #endif
    }
}
//981004-200721-A-E


//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * End of OEM_POWER.C */

#endif