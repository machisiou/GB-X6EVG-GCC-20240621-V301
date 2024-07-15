#include <stdint.h>
#include "system/Memory.h"
#include "system/peripheral.h"
#include "oem/crb/Oem_power.h"
#include "oem/crb/Oem_timer.h"
#include "hal/PerVW.h"
#include "hal/GPIO.h"
#include "RTK_Include.h"
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
	122,	0,			// on EC_EN_V5A
	0,		0,			// on 3.3A_EN
	96,		0,			// on USB_V5A_EN
	121,	0,			// on USB_EN_EC
	97,		0,				//AC_Present
	//38,0,				//dGPU_HOLD_EC_RST_L
	87,		0,			// on EC_CLR_LATCH

	114,	1,			// on PM_PWRBTN
	255,	20,			// delay 20ms
	86,		1,			// on RSMRST
	//99,			1,		//RSMRST 
	255,	100,			// delay 1ms
};

void G3_S5_PS(void)
{
	uint8_t index;
	debug0=0xFF;
	//ESPI->ESPICFG = 0x0000000F;

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
	ESPI->ESPICFG = 0x0000000F;
	
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
	_Delay_1ms(1);
	//GPIO_Write(104,1);			// on PM_PWROK
	_Delay_1ms(98);
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
	EC_BKLOUT = 1; 	
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
	#if 1
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

	TI_FW_CHECK(); //981004-211119-A
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