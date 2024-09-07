#include "system/Type.h"
#include "system/Memory.h"
#include "hal/KBM.h"
#include "system/peripheral.h"
#include "oem/crb/Oem_gpio.h"
#include "oem/crb/Oem_main.h"
#include "oem/crb/Oem_scan.h"
#include "oem/crb/Oem_timer.h"
#include "chip/rts5911/RTS5911.h"
#include "RTK_Include.h"
#ifdef SupportMTLCRB
#include "oem/crb/CRB.h"
#endif

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


	if (xAPP_PD_EnterUpdate > 0x00) //981004-220208-A
    {
		//SET_MASK(EC_Flag5, TI_PD_Flash); //EC RAM 0x389 BIT6
        //service_app_update_ti_pd();
    }
}
/******************************************************************************/
/** 10ms A service routine
*******************************************************************************/
void oem_10msA_service(void)
{

    #if BAT1FuncSupport
    Battey1ControlCenter();
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
}

/******************************************************************************/
/** 100ms C service routine
*******************************************************************************/
void oem_100msC_service(void)
{
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
}

/******************************************************************************/
/** 1second A service routine
*******************************************************************************/
void oem_1SA_service(void)
{

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

}

/******************************************************************************/
/** 1second B service routine
*******************************************************************************/
void oem_1SB_service(void)
{
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