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

	static uint8_t i =0;
	Oem_SysPowerContrl();
	if(i<10)
	{
		EventManager(i++);
	}
	else
	{i=0;}
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
}
/******************************************************************************/
/** 10ms A service routine
*******************************************************************************/
void oem_10msA_service(void)
{
}

/******************************************************************************/
/** 10ms B service routine
*******************************************************************************/
void oem_10msB_service(void)
{
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

void INIT_TM1650(void)
{
	#if 0
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
	
	SMBUS_RW_B(4, 3, 0x48 ,0x59 ,NULL);
	SMBUS_RW_B(4, 3, 0x68 ,0x0F ,NULL);
	SMBUS_RW_B(4, 3, 0x6A ,0x0F ,NULL);
	SMBUS_RW_B(4, 3, 0x6C ,0x0F ,NULL);
	SMBUS_RW_B(4, 3, 0x6E ,0x0F ,NULL);
}

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
				Last_P81HDR = Port81_Get_Data();
				Last_P80HDR = Port80_Get_Data();
			if((Last_P81HDR != Pre_P81) || (Last_P80HDR != Pre_P80))
			{

				/* Update TM1650 when debug code changed */
				Pre_P81 = Last_P81HDR;
				Pre_P80 = Last_P80HDR;
				led = Pre_P80 =(uint8_t)(Pre_P80<<4)|(Pre_P80>>4); //981004-200812-A
				I2C_SMBusModProtocol(3,3,0x48,0,test_val,0);	 		
				I2C_WR_BUFFER[0] = LED7s_TABLE[led & 0x0F]; //981004-200812-M
				I2C_SMBusModProtocol(3,3,0x68,0,I2C_WR_BUFFER,0);
				I2C_WR_BUFFER[0] = LED7s_TABLE[(led >> 4) & 0x0F]; //981004-200812-M
				I2C_SMBusModProtocol(3,3,0x6A,0,I2C_WR_BUFFER,0);
				led = (uint8_t)(Last_P81HDR<<4)|(Last_P81HDR>>4); //981004-200812-A
				I2C_WR_BUFFER[0] = LED7s_TABLE[led & 0x0F]; //981004-200812-M		
				I2C_SMBusModProtocol(3,3,0x6C,0,I2C_WR_BUFFER,0);
				I2C_WR_BUFFER[0] = LED7s_TABLE[(led >> 4) & 0x0F]; //981004-200812-M 		
				I2C_SMBusModProtocol(3,3,0x6E,0,I2C_WR_BUFFER,0);
				
			}
		
		#endif
}
