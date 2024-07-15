/**
 * @file Oem_battery.c
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "RTK_Include.h"

#if 1
//981004-151217-M-S Fix Battery no charge when shipmode wakeup.60.8w "Model : GAG-K40"    
void Fix_Battery_Abnormal(void)//Note: shipmode wake-up possibility no charge current. 
{	
    //if ((Wait_BAT_cnt++ >=2) && (Wait_BAT_cnt++ <=3) )
	if (Wait_BAT_cnt++ ==3) //981004-151217-M
	{        
	    BAT_OPTION2 = 0x12E6; //981004-200610-M  from 0x12C1 for BQ24780S (RSNS_RATIO (1:2) & EN_PMON) P27
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option2, &BAT_OPTION2 ,  SMBus_NoPEC); //992022-151027-A
		SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option2,&BAT_OPTION2);   	
	}
	else if (Wait_BAT_cnt++ >=4)
	{  //10sec
		//ConfigCharger();
       //981004-171107-M-S
	  if (IS_BIT_CLR(POWER_FLAG15, BAT_CUSTOM))	
	  {	
          if (IS_BIT_CLR(POWER_FLAG12, bat_full))		
          {
             BAT_OPTION = 0x4CF9;           		 
          }
          else
          {
            BAT_OPTION = 0x4DF9;
          }
	  }	
	  else
	  {
	      if (IS_BIT_CLR(POWER_FLAG4, bat_custom_end))		
          {
             BAT_OPTION = 0x4CF9;
			 BAT_LED_L = 0;	//981004-240425-A              			 
          }
          else
          {
            BAT_OPTION = 0x4DF9;
			BAT_LED_L = 1;	//981004-240425-A
          }
	  }
     //981004-171107-M-E
        BAT_OPTION3 = 0x4402; //981004-220824-R //bq24780 not support 0x37h command
		SMBUS_RW_W(0,5,Charger_Addr,CHGCmd_Option3,&BAT_OPTION3);
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option3, &BAT_OPTION3 ,  SMBus_NoPEC); //981004-220803-A 
        BAT_OPTION2 = 0x12E6; //981004-200610-M  from 0x12C1 for BQ24780S (RSNS_RATIO & EN_PMON) P27	
        //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); //981004-151002-A
	    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option2, &BAT_OPTION2 ,  SMBus_NoPEC); //992022-151027-A
		SMBUS_RW_W(0,5,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
		SMBUS_RW_W(0,5,Charger_Addr,CHGCmd_Option2,&BAT_OPTION2);    	  
		BIT_CLR(POWER_FLAG13, fixBattery);
		Wait_BAT_cnt = 0;
	}
}
//981004-171107-A-S
uint8_t BAT_CUSTOMIZE_CHECK(int sel_item)
{
	
	uint8_t bBAT_CUSTOMIZE =IS_BIT_SET(POWER_FLAG15, BAT_CUSTOM);
	uint16_t BAT_TMP = 0x00;
	  
    if (!bBAT_CUSTOMIZE)
    {
		BAT_CHG_START = 0;
		BAT_CHG_END = 97;
	}
    else //981004-240425-A-S
	{	
      if (IS_MASK_CLEAR(POWER_FLAG4, bat_custom_end))		
      {             
          BAT_LED_L = 0;	  
      }
      else
      {           
		  BAT_LED_L = 1;
      } //981004-240425-A-E
    }	  
    //981004-220901-M
    if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2)) && (IS_MASK_CLEAR(POWER_FLAG3, ship_mode)) && (!xITEPD_FlashUtilityEnable)) //EC RAM 0x389 bit0/1/2 //981004-231128-M
    { 
	 if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-230510-A
	 {    	
	    switch(sel_item)
	    {
			case 1:
					if (BAT_RMCAP >= 6319 ) //6514*0.97 = 6319 //981004-200909-M   
					{						
						if ((IS_MASK_CLEAR(POWER_FLAG12, bat_full)) && (IS_MASK_SET(POWER_FLAG1, adapter_in) && !bBAT_CUSTOMIZE))
						{
							BAT_RMCAP = 6514; //981004-200909-M
							BIT_CLR(BAT_STATUS, CHARGE);					
							BIT_SET(POWER_FLAG7, bat_cap97);
							BIT_CLR(POWER_FLAG12, bat_100); 								   										
						}				
					}
			break;
			case 2:
					if (IS_BIT_CLR(POWER_FLAG1, enter_S3))
					{		  
						if ((IS_BIT_SET(POWER_FLAG12, bat_full)) && (RMCAP_TEMP >= BATCAP98))               
						{			        
							//if (IS_BIT_SET(POWER_FLAG1, adapter_in))
							if ((IS_BIT_SET(POWER_FLAG1, adapter_in)) || (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)))	
							{
								BAT_RMCAP = BAT_LFCCAP;
								RMCAP_TEMP = LFCCAP_TEMP;						 
							}		   
						} 
					}	           
					else if (SLP_S4_L)
					{ 													 		     	
						//if (IS_BIT_SET(POWER_FLAG1, adapter_in))
						EC_S3_DDR5_EN = 1;
                        if ((IS_BIT_SET(POWER_FLAG1, adapter_in)) || (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)))						
						    BatPollingStep++;   		
						//else if (IS_BIT_CLR(POWER_FLAG1, usb_charge_s3)) //981004-180717-R
						    //BatPollingStep++;   														
						USB_V5A_EN = 0; //USB_PWR_EN //981004-210818-M from 1
						USB_EN_EC = 0; //981004-210818-M from 1
					}
			break;
			case 3:
				 //981004-211208-M-S
				if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2 
                {	
					if ((BAT_RMCAP3 < ((float)(BAT_CHG_END)/100)*6514)) //981004-200909-M 
					{ 
						//if (IS_BIT_CLR(BAT_STATUS, CHARGE))
						//{                            					
							BAT_OPTION = 0x4CF9;
							BIT_SET(BAT_STATUS, CHARGE);
                            BIT_CLR(BAT_STATUS, DISCHARGE);							
						//}
                        BIT_CLR(POWER_FLAG4, bat_custom_end);						
				    }                    
					else 
					{										   
						BIT_CLR(BAT_STATUS, CHARGE); 		
						BIT_SET(BAT_STATUS, DISCHARGE);														
						BAT_OPTION = 0x4DF9;
                        BIT_SET(POWER_FLAG4, bat_custom_end);						
					}
				}
				else
				{
					BAT_OPTION = 0x6CF9;
				}
					//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
					SMBUS_RW_W(0,5,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
				break;
				case 4:
						if(!bBAT_CUSTOMIZE)
						    break;																
						//if (RMCAP_TEMP >= 6188) //6514*95% = 6188 //981004-200909-M
						if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
                        {
							if (IS_BIT_SET(POWER_FLAG4, bat_custom_end))
							{                            				
							BAT_OPTION = 0x4DF9;                             						
							}
					    	else
							{ 						    
								BAT_OPTION = 0x4CF9;                            						
								BIT_CLR(POWER_FLAG12, bat_full);
								BIT_CLR(POWER_FLAG12, bat_100); 
								BIT_CLR(POWER_FLAG7, bat_cap97); 
							}
						}
						else
						{
							BAT_OPTION = 0x6CF9;
						}
                        CheckChargerSetting();						
				break;
													
				default:									
			break;
					
	   }
	 }
     else //981004-230510-A
     {
		switch(sel_item)
	    {
			case 1:
					//if (BAT_RMCAP >= 7410 ) //7640*0.97 = 7410 //981004-220615-M 
                    if (BAT_RMCAP >= BATCAP97)					
					{						
						if ((IS_BIT_CLR(POWER_FLAG12, bat_full)) && (IS_BIT_SET(POWER_FLAG1, adapter_in) && !bBAT_CUSTOMIZE))
						{
							//BAT_RMCAP = 7640; //981004-220615-M
							//BAT_RMCAP = BAT_LFCCAP;
							BAT_RMCAP = LFCCAP_TEMP;
							BIT_CLR(BAT_STATUS, CHARGE);					
							BIT_SET(POWER_FLAG7, bat_cap97);
							BIT_CLR(POWER_FLAG12, bat_100); 								   										
						}				
					}
			break;
			case 2:
					if (IS_BIT_CLR(POWER_FLAG1, enter_S3))
					{		  
						if ((IS_BIT_SET(POWER_FLAG12, bat_full)) && (RMCAP_TEMP >= BATCAP98))               
						{			        
							//if (IS_BIT_SET(POWER_FLAG1, adapter_in))
							if ((IS_BIT_SET(POWER_FLAG1, adapter_in)) || (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)))	
							{
								BAT_RMCAP = BAT_LFCCAP;
								RMCAP_TEMP = LFCCAP_TEMP;						 
							}		   
						} 
					}	           
					else if (SLP_S4_L)
					{ 													 		     	
						//if (IS_BIT_SET(POWER_FLAG1, adapter_in))
						EC_S3_DDR5_EN = 1;					
                        if ((IS_BIT_SET(POWER_FLAG1, adapter_in)) || (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)))						
						    BatPollingStep++;   		
						//else if (IS_BIT_CLR(POWER_FLAG1, usb_charge_s3)) //981004-180717-R
						    //BatPollingStep++;   														
						USB_V5A_EN = 0; //USB_PWR_EN //981004-210611-M from 0
						USB_EN_EC = 0; //981004-210611-M from 0
					}
			break;
				 case 3:
				 //981004-211208-M-S
				  if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2 
                 {					 	
					//if ((BAT_RMCAP3 < ((float)(BAT_CHG_END)/100)*7640)) //981004-230417-M //LFCCAP_TEMP
					if (((BAT_RMCAP3) < ((float)(BAT_CHG_END)/100)* (LFCCAP_TEMP)))
					{ 
						//if (IS_BIT_CLR(BAT_STATUS, CHARGE))
						//{                            					
							BAT_OPTION = 0x4CF9;
							BIT_SET(BAT_STATUS, CHARGE);
                            BIT_CLR(BAT_STATUS, DISCHARGE);							
						//}
                        BIT_CLR(POWER_FLAG4, bat_custom_end);						
				    }                    
					else 
					{										   
						BIT_CLR(BAT_STATUS, CHARGE); 		
						BIT_SET(BAT_STATUS, DISCHARGE);														
						BAT_OPTION = 0x4DF9;
                        BIT_SET(POWER_FLAG4, bat_custom_end);						
					}
				 }
				 else
				 {
					BAT_OPTION = 0x6CF9;
				 }
                 			 
					//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
					SMBUS_RW_W(0,5,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
				break;
				case 4:
						if(!bBAT_CUSTOMIZE)
						    break;																
						if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
                        {							
						  if (IS_BIT_SET(POWER_FLAG4, bat_custom_end))
						  {                            				
							  BAT_OPTION = 0x4DF9;                             						
						  }
					      else
						  { 						    
							  BAT_OPTION = 0x4CF9;                            						
							  BIT_CLR(POWER_FLAG12, bat_full);
							  BIT_CLR(POWER_FLAG12, bat_100); 
							  BIT_CLR(POWER_FLAG7, bat_cap97); 
						  }
						}
						else
						{
							BAT_OPTION = 0x6CF9;
						}										
                        CheckChargerSetting();						
			break;
													
				default:									
			break;
					
	   }	
	 }		 
	  return (IS_BIT_SET(POWER_FLAG15, BAT_CUSTOM))? 1:0;
	}
}
//981004-171107-A-E								

//981004-171107-A-S									
void BAT_STD_CHECK(void)
{
  if (IS_BIT_SET(EC_Flag4, old_99w)) //981004-230510-A
  {	
	if (BAT_RMCAP >= ((BAT_CHG_END)/100)*6514) //981004-200909-M
	{
	   #if 0
	   if ((IS_BIT_CLR(POWER_FLAG4, bat_custom_end)) ) 
	   {
	      if ((IS_BIT_SET(POWER_FLAG2, sci_on)) && (SLP_S3_L))
		  {
	         BIT_SET(POWER_FLAG4, bat_custom_end); //EC RAM 204 BIT1
		     ECQEvent(SCI_BAT_CUSTOM, SCIMode_ACPI_SMBus); //0x9F
		  }	 
	   }
	   #endif
	}
    //981004-171114-M-E	
	else
	{
		if (RMCAP_TEMP >= 6188) //6514*95% = 6188 //981004-200909-M
		{					   
			if ((IS_BIT_SET(POWER_FLAG12, bat_100)) && (IS_BIT_SET(POWER_FLAG1, adapter_in)))
			{
				BAT_RMCAP = 6514; //981004-200909-M
			}
	    }
		BIT_CLR(POWER_FLAG4, bat_custom_end);//981004-171114-A //EC RAM 204 BIT1
	}          											
	if ((IS_BIT_CLR(POWER_FLAG1, adapter_in) && (BAT_RMCAP >= 6514))) //981004-200909-M
	{
		BAT_RMCAP = 6514; //981004-200909-M
	}
  }
  else
  {
	if ((BAT_RMCAP) >= ((BAT_CHG_END)/100 * (LFCCAP_TEMP)))
	{
	   #if 0
	   if ((IS_BIT_CLR(POWER_FLAG4, bat_custom_end)) ) 
	   {
	      if ((IS_BIT_SET(POWER_FLAG2, sci_on)) && (SLP_S3_L))
		  {
	         BIT_SET(POWER_FLAG4, bat_custom_end); //EC RAM 204 BIT1
		     ECQEvent(SCI_BAT_CUSTOM, SCIMode_ACPI_SMBus); //0x9F
		  }	 
	   }
	   #endif
	}
    //981004-171114-M-E	
	else
	{
		//if (RMCAP_TEMP >= 7258) //7640*95% = 7258 //981004-230417-M //LFCCAP_TEMP
		if (RMCAP_TEMP >= BATCAP95)
		{					   
			if ((IS_BIT_SET(POWER_FLAG12, bat_100)) && (IS_BIT_SET(POWER_FLAG1, adapter_in)))
			{
				//BAT_RMCAP = 7640; //981004-220615-M
				BAT_RMCAP = BAT_LFCCAP; //981004-230428-M
			}
	    }
		BIT_CLR(POWER_FLAG4, bat_custom_end);//981004-171114-A //EC RAM 204 BIT1
	}
  }	  
}
//981004-171107-A-E

void BatLfcCapCal(void)
{
    if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }	
	//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_DCap, &New_DSNCAP, SMBus_NoPEC);
	SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_DCap,&New_DSNCAP);
	
	//bRSMBusBlock(SMbusCh1, SMbusRBK, SmartBat_Addr, C_Dname , &BAT_NEWDEVNAME); //981004-130819-A 

	SMBUS_RW_BLK(0,ReadBlock,SmartBat_Addr,C_Dname, &BAT_NEWDEVNAME);
		
	if ((New_DSNCAP != BAT_DSNCAP) || (BAT_NEWDEVNAME != BAT_DEVNAME)) //981004-130819-M
	//if (New_DSNCAP != BAT_DSNCAP)
    {	
		BAT_DSNCAP = New_DSNCAP;
		BAT_DEVNAME = BAT_NEWDEVNAME; 
		
		//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_DVolt, &BAT_DSNVTG, SMBus_NoPEC);
		SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_DVolt,&BAT_DSNVTG);
		//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RCalarm, &BAT_DSNCAPWN, SMBus_NoPEC);
		SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_RCalarm,&BAT_DSNCAPWN);
		//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_Current, &BAT_PRSNTRATE, SMBus_NoPEC);
		SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_Current,&BAT_PRSNTRATE);
        if(IS_BIT_CLR(POWER_FLAG13, fixBattery))	//981004-151217-A	
        ConfigCharger();						
    }
  
}

//-----------------------------------------------------------------
// Polling battery data function
//-----------------------------------------------------------------
void PollingBatteryData(void)
{ 
    if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }		 
    if (IS_BIT_CLR(BAT_STATUS, BAT_IN))
        return;
			
   if (IS_BIT_SET(EC_Flag4, old_99w))
   {	
    switch (BatPollingStep & 0x03)
    {
        case 0x00:
		
	        //981004-171106-M-S to prevent the loss of reading battery capacity 	
            //if (!bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RMcap, &BAT_RMCAP, SMBus_NoPEC))
			if(!SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_RMcap,&BAT_RMCAP))
			{			  
			   BatPollingStep = 0;   
               return;
			} 
            //981004-171106-M-E			
			//BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922; 
			RMCAP_TEMP2 = BAT_RMCAP;
			FCC_Ratio = Check_FCC_Ratio1(); //98100-160909-A
			//BAT_RMCAP = BAT_RMCAP * 1.14; //981004-160909-R from 1.1
            BAT_RMCAP3 = (uint16_t)(BAT_RMCAP * FCC_Ratio); //98100-160922-A				
            BAT_RMCAP = (uint16_t)(BAT_RMCAP * FCC_Ratio); //98100-160909-A
									
			if(BAT_CUSTOMIZE_CHECK(1))
			{   
				BAT_STD_CHECK();
			}	
			//BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922;
			//RMCAP_TEMP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8);//Raymond0922
			RMCAP_TEMP = BAT_RMCAP;
			BAT_CUSTOMIZE_CHECK(2);							
        
            break;

        case 0x01:
			//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_Volt, &BAT_PRSNTVOL, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_Volt,&BAT_PRSNTVOL);		
            
            break;

        case 0x02:		    
            //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, C_temp, &BAT_TEMPER, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmartBat_Addr,C_temp,&BAT_TEMPER);
                     		   
			//TEMPER_TEMP = (uint16_t)(BAT_TEMPER<<8) | (BAT_TEMPER>>8);Raymond20230925
		TEMPER_TEMP = BAT_TEMPER;
			
            CheckChargerSetting(); //981004-171107-A
						
			if ((!AC_IN_L) || ((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))))
			{			    		        		
				if (IS_BIT_CLR(POWER_FLAG12, bat_full))
			    {
					if (IS_BIT_CLR(POWER_FLAG10, scion_ac_in)) 
					{
						;
                    }						
					if (RMCAP_TEMP < 6319) //6514*0.97 = 6319-------------ITEM(2)S //981004-200909-M
					{
						if (IS_BIT_SET(POWER_FLAG7, bat_cap97))
						{
							BIT_CLR(POWER_FLAG7, bat_cap97); 
						}						
					}
				}		
				else //if (IS_BIT_SET(BAT_ALARM1, FullyChg))
				{ 														
					BAT_CUSTOMIZE_CHECK(4);	//981004-171107-A													
                    //981004-180312-A-S for power leakage may reach below 95%
                    if (RMCAP_TEMP < 6188) //6514*95% = 6188 //981004-200909-M 
					{					    
                        if ((IS_MASK_CLEAR(POWER_FLAG15, BAT_CUSTOM)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) 
                        {							
						    BAT_OPTION = 0x4CF9;
						}
						else if ((IS_MASK_SET(EC_Flag5, learn_mode0)) || (IS_MASK_SET(EC_Flag5, learn_mode1)) || (IS_MASK_SET(EC_Flag5, learn_mode2))) 
	                    {
		                   BAT_OPTION = 0x6CF9; 		  
	                    }							
                        if (IS_BIT_CLR(BAT_ALARM1, FullyChg)) //981004-220912-A
                        {							
						   BIT_CLR(POWER_FLAG12, bat_full);
						   BIT_CLR(POWER_FLAG12, bat_100); 
						   BIT_CLR(POWER_FLAG7, bat_cap97);
                        }						   
					}
                    //981004-180312-A-E 					
				}				 
				    //BAT_CHGVOL = testW0;
					//BAT_CHGCURR = testW1;
					//BAT_INCURR = testW2;
					//BAT_LFCCAP = 0x7219; //6514 //981004-200909-M 
				BAT_LFCCAP = 0x1972; ///Raymond 
			}			
			else 
			{
				if (IS_BIT_SET(POWER_FLAG12, bat_full))
				{
						//if (RMCAP_TEMP < 3029) //4030*95% = 3029
					if (RMCAP_TEMP < 6188) //4030*95% = 3828 //981004-200909-M 
					{
					    //BAT_CHGVOL = 0x6042; //16.992V	(16.384+0.512+0.64+0.32 = 16.992) //981004-171107-R 
                        if (IS_BIT_CLR(POWER_FLAG15, BAT_CUSTOM)) 
                        {							
						    BAT_OPTION = 0x4CF9;
						}	
						if (IS_BIT_CLR(BAT_ALARM1, FullyChg)) //981004-220912-A
                        {	
						    BIT_CLR(POWER_FLAG12, bat_full);
						    BIT_CLR(POWER_FLAG12, bat_100); 
						    BIT_CLR(POWER_FLAG7, bat_cap97);
                        }							
					}
				}																					
				else
				{				                				
					if (RMCAP_TEMP < 6319) //6514*0.97 = 6319 //981004-200909-M
					{
					    if (IS_BIT_SET(POWER_FLAG7, bat_cap97))
						{
							BIT_CLR(POWER_FLAG7, bat_cap97); 
						}						
					}
				}																		   
			} 
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Voltage,&BAT_CHGVOL);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_InCurr,&BAT_INCURR);		
		    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);		
		    
			if ((!AC_IN_L) || ((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))))
			{
			if (!AC_IN_L)		
            {
				if (IS_BIT_SET(POWER_FLAG7, PPAB_ON)) //981004-230131-A
                {
					BIT_SET(EC_Flag5, AC_PPAB_ON);
					if (IS_BIT_SET(EC_Flag3, DC_PPAB_OFF))
					{
						//BIT_SET(EC_Flag5, AC_PPAB_ON);
						BIT_CLR(EC_Flag3, DC_PPAB_OFF); 
						
					}	
				}
                else
                {
					BIT_CLR(EC_Flag5, AC_PPAB_ON);
					
				}					
                //981004-181107-M-S				
                #if 0		
                if (RMCAP_TEMP <= (BATCAP10>>1)) //5%
				{
					BIT_SET(POWER_FLAG12, ac_bat10);
					WTDP = 20;
					WTDP2 = 45;
					WTDP4 = 90; //981004-180301-M from 27 
				}					
				else
				{
					if ((AC_boost_Status == 0) && (IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) ) 
				    {
					    //981004-190530-M-S
                        if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w))
				        {
				            WTDP = 157;
			                WTDP2 = 157;
			                WTDP4 = 246; //i7 CPU; //i7 CPU
				        }
				        else
				        {
                            WTDP = 157;
			                WTDP2 = 157;
			                WTDP4 = 246; //i9 CPU
                        }			
                        //981004-190530-M-E
                    }						   
					BIT_CLR(POWER_FLAG12, ac_bat10);
				}
                #endif
				//if ((IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) && (IS_BIT_CLR(POWER_FLAG10, scion_ac_in))) //981004-200210-M
				//if ((IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) && (IS_BIT_CLR(POWER_FLAG10, scion_ac_in)) && (IS_BIT_CLR(POWER_FLAG3, adapter_overtemp))) //981004-210324-M
				if ((IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)) && (IS_MASK_CLEAR(POWER_FLAG10, scion_ac_in)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //981004-211123-M
				{			    
                   if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w))
				   {
					 if  ((IS_MASK_CLEAR(EC_Flag4, GPU_temp_75)) && (NVDeventStatus2 == 0)) //981004-221228-M
					 {	 
				       WTDP = 157;
					 }  
	                   WTDP2 = 157;
	                   WTDP4 = 246; //i7 CPU
				   }
				   else
				   {
                       if  ((IS_MASK_CLEAR(EC_Flag4, GPU_temp_75)) && (NVDeventStatus2 == 0)) //981004-221228-M
					   {	 
				         WTDP = 157;
					   }  
	                   WTDP2 = 157;
	                   WTDP4 = 246; //i9 CPU
                   }			                
				}
				//981004-200210-A-S
                else if (IS_BIT_SET(POWER_FLAG6, sv_thrt_on))
				{	
                   if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(POWER_FLAG4, pstate_off)) && (IS_BIT_CLR(AmpHigh_flag, AmpHigh)) )
			       {
			          if (NVDeventStatus <= 7)
				      {			       
				          if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
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
			}
				//981004-220811-A-S for 1C charge
				
					if ((TEMPER_TEMP <= LOW_TEMPER) || (TEMPER_TEMP >= HIGH_TEMPER)) //(15 Lower or 45 Higher Celsius degree) //981004-220419-M from 15/45
	                {  		    
                       CHG_TEMP2 = 0; //981004-230925-A
					   CHG_TEMP3 = 0; //981004-230925-A
                       CHG_TEMP1++;
                       if (CHG_TEMP1 >= 5)
                       {
                          CHG_TEMP1 = 0; //981004-230925-A						   
                          BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A (Target : 1271mA )
						  //981004-230621-A-S
						  CLEAR_MASK(EC_Flag1, chgcur_step1);
	                      CLEAR_MASK(EC_Flag1, chgcur_step2);
	                      CLEAR_MASK(EC_Flag1, chgcur_step3);
	                      CLEAR_MASK(EC_Flag1, chgcur_step4);
	                      CLEAR_MASK(EC_Flag1, chgcur_step5); 
	                      CHGCUR_STEP_cnt = 0;
						  //981004-230621-A-E
						  
						  //981004-230828-A-S
                          CLEAR_MASK(EC_Flag2, pdchgcur_step1);
	                      CLEAR_MASK(EC_Flag2, pdchgcur_step2);
	                      CLEAR_MASK(EC_Flag2, pdchgcur_step3);
	                      CLEAR_MASK(EC_Flag2, pdchgcur_step4);
	                      CLEAR_MASK(EC_Flag2, pdchgcur_step5); //981004-230828-A
	                      CHGCUR_STEP_cnt2 = 0;
                          //981004-230828-A-E
					   }						  
	                }
                    else
                    {				
					   if ((IS_MASK_SET(EC_Flag1, chgcur_step5)) || (IS_MASK_SET(EC_Flag2, pdchgcur_step4))) //981004-230828-M
				       {
						 if ((TEMPER_TEMP > LOW_TEMPER) && (TEMPER_TEMP < 2980)) //(16~24) 
                         {						 
						    BIT_CLR(EC_Flag5, BAT_1C_CHG); //EC RAM 0x389 bit6
                            BAT_CHGCURR = 0x800C; //3.2A		
						 }
                         else //(25~44)
                         {							 
                            if (RMCAP_TEMP <= BATCAP50) //981004-221209-M
			                {
							  if (TEMP_TR8 >= 80) //981004-230217-A
	                          {
		                          BIT_SET(EC_Flag5, TR8_heat_CHG);		                          
	                          }
                              if ((TEMP_TR8 <= 55) && (IS_BIT_SET(EC_Flag5, TR8_heat_CHG)))
                              {
		                          BIT_CLR(EC_Flag5, TR8_heat_CHG);		                          
	                          }			
							  if ((IS_BIT_CLR(EC_Flag5, TR8_heat_CHG)))   
        	                  {			                   
                                if ((RMCAP_TEMP) <= (BATCAP35)) //BATCAP30 = 1954 //981004-221209-A
							    {		 						        
						            BAT_CHGCURR = 0x0018; //4.096+2.048 = 6.144A
								
                                }
                                else
                                {
									BAT_CHGCURR = 0x8011; //4.096+0.256+0.128 = 4.48A
									
								}
                                BIT_SET(EC_Flag5, BAT_1C_CHG); //EC RAM 0x389 bit6
		                      }
                              else
                              {
								  BAT_CHGCURR = 0x800C;	//3.2A								  
							  }								  
                            }
                            else
                            {						      
						      BIT_CLR(EC_Flag5, BAT_1C_CHG); //EC RAM 0x389 bit6
                              BAT_CHGCURR = 0x800C;	//3.2A					
					        }
						 }	
					   }
                    }					   
					//981004-220811-A-E for 1C charge 
			   }				 
                //981004-200210-A-E
			 #if 1	
			 if ((!AC_IN_L) || ((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))))
			 {	
			    if (IS_BIT_SET(BAT_STATUS, CHARGE))
			    {
                   if ((IS_MASK_CLEAR(POWER_FLAG2, LED_TEST_ON)) && (IS_MASK_CLEAR(POWER_FLAG15, BAT_CUSTOM))) //981004-240425-M
				  //if (IS_BIT_CLR(POWER_FLAG2, LED_TEST_ON)) //981004-201106-M 
                  {				  
					if (IS_BIT_CLR(POWER_FLAG7, bat_cap97)) 
                    {
                        BAT_LED_L = 0;
						//GPIO_Write(25,0);
                    }
					else
					{
					    BAT_LED_L = 1;
						//GPIO_Write(25,1);
					}
                  }					
					   if ((IS_BIT_CLR(POWER_FLAG4, bat_cap_first_chk)) && (IS_BIT_CLR(POWER_FLAG4, bat_cap_downgrade)) && (IS_BIT_SET(POWER_FLAG2, sci_on))) 
                       {
                           RMCAP_FIRST_CHK = RMCAP_TEMP;
						   BIT_SET(POWER_FLAG4, bat_cap_first_chk);
                       }                     				   
				}                   					
                else 
				{
                  //if (IS_BIT_CLR(POWER_FLAG1, enter_S3)) //981004-180731-A
                  //{				
                       BAT_LED_L = 1;
				  //}	   
				    BIT_CLR(POWER_FLAG4, bat_cap_first_chk); 
                } 
			 }
			 #endif
			 #if 0            		
			if (IS_MASK_CLEAR(POWER_FLAG2, LED_TEST_ON)) 
            {               				
               if (((!AC_IN_L) || ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)))) && (RMCAP_TEMP < BATCAP95))
			   {
                   BAT_LED_L = 0;				   
               }
			   else
			   {
			       BAT_LED_L = 1;				   
		       }  
   			}
			#endif	
			#if 0
			else if (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))
			{
               if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	           {	 
	               if (IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) //981004-151204-A
	               {
		              WTDP = 35;
                      WTDP2 = 45;	
	                  WTDP4 = 90; //0xD3
	               }
               }	
               else //i9 CPU
               {
                   if (IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) //981004-151204-A
	               {
		             WTDP = 35;
                     WTDP2 = 45;	
	                 WTDP4 = 90; //0xD3
	               }   
	           }
            }		
            #endif			
               
            if (IS_BIT_SET(POWER_FLAG1, enter_S3))
			{
				BatPollingStep++;   
                return;
			}				    
            //bRWSMBus(SMbusCh1, SMbusRW, SmBat_Addr, C_current, &BAT_RATETEMP, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmBat_Addr,C_current,&BAT_RATETEMP);
			
            //if (IS_BIT_SET(POWER_FLAG1, adapter_in))
			if ((IS_BIT_SET(POWER_FLAG1, adapter_in)) || (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)))	
			{
            	if ((BAT_RATETEMP & 0x0080) == 0)
                {                   
				   OLD_PRSNTRATE = BAT_RATETEMP;
				   BAT_PRSNTRATE = BAT_RATETEMP;
                }				               
				//if ((AC_boost_Status > 0) || (BAT_PRSNTRATE & 0x0080))
                //if ((BAT_PRSNTRATE & 0x0080))
				else
				{				   
					BAT_PRSNTRATE = OLD_PRSNTRATE; //Battery leakage
				}				
				//PRSNTRATE_TEMP2 = (uint16_t)((BAT_PRSNTRATE<<8)|(BAT_PRSNTRATE>>8)); //981004-151002-A
				PRSNTRATE_TEMP2 = BAT_PRSNTRATE;
				//981004-181107-R-S
				#if 0							
                if (((BAT_RATETEMP & 0x0080) == 0) && (PRSNTRATE_TEMP2 >= 2700) && ((RMCAP_TEMP >= BATCAP10) && (RMCAP_TEMP <= BATCAP60)))
                {
                    if ((IS_BIT_CLR(POWER_FLAG5, bat_cap_first_chk2)) && (IS_BIT_SET(POWER_FLAG2, sci_on))) 
                    { 
					    RMCAP_FIRST_CHK2 = RMCAP_TEMP;
						BAT_FIRST_CHECK2_10CHK = RMCAP_FIRST_CHK2 * 1.1;
						BIT_SET(POWER_FLAG5, bat_cap_first_chk2);
					} 
					BAT_FIRST_CHK2_cnt++;
					if (RMCAP_TEMP >= (BAT_FIRST_CHECK2_10CHK))
					{
					    if (BAT_FIRST_CHK2_cnt <= 75) //5 Minutes (4*75 = 300 seconds= 5 Minutes)
						{
						   BAT_FIRST_CHK2_cnt = 0;
						   BIT_CLR(POWER_FLAG5, bat_cap_first_chk2);
						   ECQEvent(SCI_BAT_AGING2, SCIMode_ACPI_SMBus); //0x95
						}
					}					
                }
				else
				{
				   BAT_FIRST_CHK2_cnt = 0;
				   BIT_CLR(POWER_FLAG5, bat_cap_first_chk2);
				}               
                #endif
				//981004-181107-R-E					
                				
			}           		
            else
            {
                //BAT_RATETEMP = (uint16_t)(~((BAT_RATETEMP<<8)|(BAT_RATETEMP>>8)-1));
                //BAT_PRSNTRATE =(uint16_t) (BAT_RATETEMP<<8)|(BAT_RATETEMP>>8);
				BAT_RATETEMP = (~(BAT_RATETEMP-1));
				BAT_PRSNTRATE = BAT_RATETEMP;
            }            
            break;

        case 0x03:		    			
		    BAT_INFO_STEP++;
            if (BAT_INFO_STEP >= 0x0F)
			{
			    BAT_INFO_STEP = 0;
                BatLfcCapCal();				
			}            	
			
            //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_BatStatus, &BAT_ALARM1, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_BatStatus,&BAT_ALARM1);
            if ((BAT_ALARM1) && (!BAT_DSNCAP)) //992022-130530-A Fix Bat. led not on after ship mode then AC in
                ConfigBatIn(); //992022-130530-A Fix Bat. led not on after ship mode then AC in
            break;    
    }        
    BatPollingStep++;
   }
   else //New Battery
   {
	switch (BatPollingStep & 0x03)
    {
        case 0x00:
		
	        //981004-171106-M-S to prevent the loss of reading battery capacity 	
            //if (!bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RMcap, &BAT_RMCAP, SMBus_NoPEC))
			if(!SMBUS_RW_W(0, ReadWord, SmartBat_Addr, BATCmd_RMcap, &BAT_RMCAP))
			{			  
			   BatPollingStep = 0;   
               return;
			} 
            //981004-171106-M-E			
			//BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922; 
			RMCAP_TEMP2 = BAT_RMCAP;
			//FCC_Ratio = Check_FCC_Ratio1(); //98100-160909-A			
            //BAT_RMCAP3 = BAT_RMCAP * FCC_Ratio; //98100-160922-A
            BAT_RMCAP3 = BAT_RMCAP;			
            //BAT_RMCAP = BAT_RMCAP * FCC_Ratio; //98100-160909-A
			BAT_RMCAP =(uint16_t) BAT_RMCAP;
									
			if(BAT_CUSTOMIZE_CHECK(1))
			{   
				BAT_STD_CHECK();
			}	
			//BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922;
			//RMCAP_TEMP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8);//Raymond0922
			RMCAP_TEMP = BAT_RMCAP;
			BAT_CUSTOMIZE_CHECK(2);							
        //981004-231218-M-S 
			if (IS_MASK_CLEAR(POWER_FLAG2, LED_TEST_ON)) 
            {	     
              if ((AC_IN_L) && (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w))) //battery mode
              {				
                if ((RMCAP_TEMP <= BATCAP20))
			    {
                    BAT_LED_L = ~BAT_LED_L;
                }
				else //981004-231221-A
				{	
                    BAT_LED_L = 1;
				}	
				BAT_FULL_L = 1;
		      }
			}
			//981004-231218-M-E
            break;

        case 0x01:
			//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_Volt, &BAT_PRSNTVOL, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_Volt,&BAT_PRSNTVOL);	

			if (IS_BIT_CLR(EC_Flag4, old_99w))
	        {
               //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, C_ChargingCurrent, &GAUGE_CURRENT, SMBus_NoPEC); //0x14
				SMBUS_RW_W(0,ReadWord,SmBat_Addr,C_ChargingCurrent,&GAUGE_CURRENT);
               //GAUGE_CURRENT = (uint16_t)(GAUGE_CURRENT<<8) | (GAUGE_CURRENT>>8);
				
              // bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, C_ChargingVoltage, &GAUGE_VOLTAGE, SMBus_NoPEC); //0x15
				SMBUS_RW_W(0,ReadWord,SmBat_Addr,C_ChargingVoltage,&GAUGE_VOLTAGE);
               //GAUGE_VOLTAGE =(uint16_t) (GAUGE_VOLTAGE<<8) | (GAUGE_VOLTAGE>>8);
            }
			
            break;

        case 0x02:		    
            //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, C_temp, &BAT_TEMPER, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmBat_Addr,C_temp,&BAT_TEMPER);    		   
			//TEMPER_TEMP =(uint16_t) (BAT_TEMPER<<8) | (BAT_TEMPER>>8);//Raymond20230925
		
			TEMPER_TEMP = BAT_TEMPER;
            CheckChargerSetting(); //981004-171107-A
			//981004-230825-A-S
			#if 0 //981004-231218-R-S
			if (((!AC_IN_L) || ((IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)))) && (RMCAP_TEMP >= BATCAP95))
			{
                BAT_FULL_L = 0;
            }
            else
            {
				BAT_FULL_L = 1;
			}
            #endif //981004-231218-R-E			
            //981004-230825-A-E

			if ((!AC_IN_L) || ((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))))
			{			    		        		
				if (IS_BIT_CLR(POWER_FLAG12, bat_full))
			    {
					if (IS_BIT_CLR(POWER_FLAG10, scion_ac_in)) 
					{
						;
                    }						
					//if (RMCAP_TEMP < 7410) //7640*0.97 = 7410 //981004-230417-M
					if (RMCAP_TEMP < BATCAP97)
					{
						if (IS_BIT_SET(POWER_FLAG7, bat_cap97))
						{
							BIT_CLR(POWER_FLAG7, bat_cap97); 
						}						
					}
				}		
				else //if (IS_BIT_SET(BAT_ALARM1, FullyChg))
				{ 														
					BAT_CUSTOMIZE_CHECK(4);	//981004-171107-A													
                    //981004-180312-A-S for power leakage may reach below 95%				 
                    //if (RMCAP_TEMP < 7258) //7640*95% = 7258 //981004-230417-M
					if (RMCAP_TEMP < BATCAP95)
					{					    
                        if ((IS_MASK_CLEAR(POWER_FLAG15, BAT_CUSTOM)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2) //EC RAM 0x389 bit0 //981004-211208-M 
                        {							
						    BAT_OPTION = 0x4CF9;
						}
                        else if ((IS_MASK_SET(EC_Flag5, learn_mode0)) || (IS_MASK_SET(EC_Flag5, learn_mode1)) || (IS_MASK_SET(EC_Flag5, learn_mode2))) 
	                    {
		                   BAT_OPTION = 0x6CF9; 		  
	                    }
                        if (IS_MASK_CLEAR(BAT_ALARM1, FullyChg)) //981004-220912-A
                        {							
						   CLEAR_MASK(POWER_FLAG12, bat_full);
						   CLEAR_MASK(POWER_FLAG12, bat_100); 
						   CLEAR_MASK(POWER_FLAG7, bat_cap97);
                        }						   
					}
                    //981004-180312-A-E 					
				}				 
				    //BAT_CHGVOL = testW0;
					//BAT_CHGCURR = testW1;
					//BAT_INCURR = testW2;
					//BAT_LFCCAP = 0xD81D; //7640 //981004-230417-R 
			}			
			else 
			{
				if (IS_BIT_SET(POWER_FLAG12, bat_full))
				{						
					//if (RMCAP_TEMP < 7258) //7640*95% = 7258 //981004-230417-M
					if (RMCAP_TEMP < BATCAP95) 
					{					    
                        if (IS_BIT_CLR(POWER_FLAG15, BAT_CUSTOM)) 
                        {							
						    BAT_OPTION = 0x4CF9;
						}	
						if (IS_BIT_CLR(BAT_ALARM1, FullyChg)) //981004-220912-A
                        {	
						    BIT_CLR(POWER_FLAG12, bat_full);
						    BIT_CLR(POWER_FLAG12, bat_100); 
						    BIT_CLR(POWER_FLAG7, bat_cap97);
                        }							
					}
				}																					
				else
				{				                				
					//if (RMCAP_TEMP < 7410) //7640*0.97 = 7410 //981004-230417-M
					if (RMCAP_TEMP < BATCAP97)
					{
					    if (IS_BIT_SET(POWER_FLAG7, bat_cap97))
						{
							BIT_CLR(POWER_FLAG7, bat_cap97); 
						}						
					}
				}																		   
			}

			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Voltage,&BAT_CHGVOL);		
		    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_InCurr,&BAT_INCURR);

			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);    
		    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC); 
		    
            if (!AC_IN_L)
			//if ((!AC_IN_L) || ((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))))	
            {
				if (IS_BIT_SET(POWER_FLAG7, PPAB_ON)) //981004-230131-A
                {
					BIT_SET(EC_Flag5, AC_PPAB_ON);
					if (IS_BIT_SET(EC_Flag3, DC_PPAB_OFF))
					{
						//BIT_SET(EC_Flag5, AC_PPAB_ON);
						BIT_CLR(EC_Flag3, DC_PPAB_OFF); 
						
					}	
				}
                else
                {
					BIT_CLR(EC_Flag5, AC_PPAB_ON);
					
				}					
                //981004-181107-M-S				
                #if 0		
                if (RMCAP_TEMP <= (BATCAP10>>1)) //5%
				{
					BIT_SET(POWER_FLAG12, ac_bat10);
					WTDP = 20;
					WTDP2 = 45;
					WTDP4 = 90; //981004-180301-M from 27 
				}					
				else
				{
					if ((AC_boost_Status == 0) && (IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) ) 
				    {
					    //981004-190530-M-S
                        if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w))
				        {
				            WTDP = 157;
			                WTDP2 = 157;
			                WTDP4 = 246; //i7 CPU; //i7 CPU
				        }
				        else
				        {
                            WTDP = 157;
			                WTDP2 = 157;
			                WTDP4 = 246; //i9 CPU
                        }			
                        //981004-190530-M-E
                    }						   
					BIT_CLR(POWER_FLAG12, ac_bat10);
				}
                #endif
				//if ((IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) && (IS_BIT_CLR(POWER_FLAG10, scion_ac_in)) && (IS_BIT_CLR(EC_Flag5, learn_mode0)) && (IS_BIT_CLR(EC_Flag5, learn_mode1)) && (IS_BIT_CLR(EC_Flag5, learn_mode2))) //981004-221123-R
				if ((IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)) && (IS_MASK_CLEAR(POWER_FLAG10, scion_ac_in)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //981004-221123-R
				//if (IS_BIT_CLR(POWER_FLAG10, scion_ac_in)) //981004-221123-M
				{			    
                   if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w))
				   {
					   if((IS_BIT_CLR(EC_Flag4, GPU_temp_75)) && (NVDeventStatus2 == 0)) //981004-221123-A
					   {	   
				          WTDP = 157;
					   }	  
	                   WTDP2 = 157;
	                   WTDP4 = 246; //i7 CPU
				   }
				   else
				   {
					   if  (NVDeventStatus2 == 0) 
					   {
                          WTDP = 157;
					   }	  
	                   WTDP2 = 157;
	                   WTDP4 = 246; //i9 CPU
                   }			                
				}
				//981004-200210-A-S
                else if (IS_BIT_SET(POWER_FLAG6, sv_thrt_on))
				{	
                   if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(POWER_FLAG4, pstate_off)) && (IS_BIT_CLR(AmpHigh_flag, AmpHigh)) )
			       {
			          if (NVDeventStatus <= 7)
				      {			       
				          if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
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
			   }				 
                //981004-200210-A-E

			//981004-231218-M-S
			if ((IS_MASK_CLEAR(POWER_FLAG2, LED_TEST_ON)) && (IS_MASK_CLEAR(POWER_FLAG15, BAT_CUSTOM))) //981004-240425-M 
            { 	
			 if ((!AC_IN_L) || ((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))))
			 {
				 if ((RMCAP_TEMP >= BATCAP95))
			     {
                     BAT_LED_L = 1;
					 BAT_FULL_L = 0;                     					 
					 if (RMCAP_TEMP >= BATCAP99)
					 {
						BAT_FULL_L = 1;                         						
					 }	 
                 }
                 else
                 {
				    BAT_LED_L = 0;
					BAT_FULL_L = 1;                    					
			     }

				 #if 0	
			    if (IS_BIT_SET(BAT_STATUS, CHARGE))
			    {
                  if (IS_BIT_CLR(POWER_FLAG1, enter_S3) && (IS_BIT_CLR(POWER_FLAG2, LED_TEST_ON))) //981004-190109-M
				  //if (IS_BIT_CLR(POWER_FLAG2, LED_TEST_ON)) //981004-201106-M 
                  {				  
					if (IS_BIT_CLR(POWER_FLAG7, bat_cap97)) 
                    {
                        BAT_LED_L = 0;
						//GPIO_Write(25,0);
                    }
					else
					{
					    BAT_LED_L = 1;
						//GPIO_Write(25,1);
					}
                  }					
					   if ((IS_BIT_CLR(POWER_FLAG4, bat_cap_first_chk)) && (IS_BIT_CLR(POWER_FLAG4, bat_cap_downgrade)) && (IS_BIT_SET(POWER_FLAG2, sci_on))) 
                       {
                           RMCAP_FIRST_CHK = RMCAP_TEMP;
						   BIT_SET(POWER_FLAG4, bat_cap_first_chk);
                       }                     				   
				}                   					
                else 
				{
                  if (IS_BIT_CLR(POWER_FLAG1, enter_S3)) //981004-180731-A
                  {				
                       //BAT_LED_L = 1;
					  GPIO_Write(25,1);
				  }	   
				    BIT_CLR(POWER_FLAG4, bat_cap_first_chk); 
                }
				#endif 
			 }
			 else
			 {
				 if ((RMCAP_TEMP <= BATCAP20))
			     {
                     BAT_LED_L = ~BAT_LED_L;
                 }
				 else //981004-231221-A
				 {
					BAT_LED_L = 1; 
				 } 	 
                 BAT_FULL_L = 1;
			 }
			}	
			#if 0
			else if (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w))
			{
               if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
	           {	 
	               if (IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) //981004-151204-A
	               {
		              WTDP = 35;
                      WTDP2 = 45;	
	                  WTDP4 = 90; //0xD3
	               }
               }	
               else //i9 CPU
               {
                   if (IS_BIT_CLR(POWER_FLAG6, sv_thrt_on)) //981004-151204-A
	               {
		             WTDP = 35;
                     WTDP2 = 45;	
	                 WTDP4 = 90; //0xD3
	               }   
	           }
            }		
            #endif			
               
            if (IS_BIT_SET(POWER_FLAG1, enter_S3))
			{
				BatPollingStep++;   
                return;
			}				    
            //bRWSMBus(SMbusCh1, SMbusRW, SmBat_Addr, C_current, &BAT_RATETEMP, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,Charger_Addr,C_current,&BAT_RATETEMP);
			
            //if (IS_BIT_SET(POWER_FLAG1, adapter_in))
			if ((IS_BIT_SET(POWER_FLAG1, adapter_in)) || (IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)))	
			{
            	if ((BAT_RATETEMP & 0x0080) == 0)
                {                   
				   OLD_PRSNTRATE = BAT_RATETEMP;
				   BAT_PRSNTRATE = BAT_RATETEMP;
                }				               
				//if ((AC_boost_Status > 0) || (BAT_PRSNTRATE & 0x0080))
                //if ((BAT_PRSNTRATE & 0x0080))
				else
				{				   
					BAT_PRSNTRATE = OLD_PRSNTRATE; //Battery leakage
				}				
				//PRSNTRATE_TEMP2 = (uint16_t)((BAT_PRSNTRATE<<8)|(BAT_PRSNTRATE>>8)); //981004-151002-A
				PRSNTRATE_TEMP2 = BAT_PRSNTRATE;
				//981004-181107-R-S
				#if 0							
                if (((BAT_RATETEMP & 0x0080) == 0) && (PRSNTRATE_TEMP2 >= 2700) && ((RMCAP_TEMP >= BATCAP10) && (RMCAP_TEMP <= BATCAP60)))
                {
                    if ((IS_BIT_CLR(POWER_FLAG5, bat_cap_first_chk2)) && (IS_BIT_SET(POWER_FLAG2, sci_on))) 
                    { 
					    RMCAP_FIRST_CHK2 = RMCAP_TEMP;
						BAT_FIRST_CHECK2_10CHK = RMCAP_FIRST_CHK2 * 1.1;
						BIT_SET(POWER_FLAG5, bat_cap_first_chk2);
					} 
					BAT_FIRST_CHK2_cnt++;
					if (RMCAP_TEMP >= (BAT_FIRST_CHECK2_10CHK))
					{
					    if (BAT_FIRST_CHK2_cnt <= 75) //5 Minutes (4*75 = 300 seconds= 5 Minutes)
						{
						   BAT_FIRST_CHK2_cnt = 0;
						   BIT_CLR(POWER_FLAG5, bat_cap_first_chk2);
						   ECQEvent(SCI_BAT_AGING2, SCIMode_ACPI_SMBus); //0x95
						}
					}					
                }
				else
				{
				   BAT_FIRST_CHK2_cnt = 0;
				   BIT_CLR(POWER_FLAG5, bat_cap_first_chk2);
				}               
                #endif
				//981004-181107-R-E					
                				
			}           		
            else
            {
                //BAT_RATETEMP = (uint16_t)(~((BAT_RATETEMP<<8)|(BAT_RATETEMP>>8)-1));
                //BAT_PRSNTRATE =(uint16_t)(BAT_RATETEMP<<8)|(BAT_RATETEMP>>8);
				BAT_RATETEMP = (~(BAT_RATETEMP-1));
				BAT_PRSNTRATE = BAT_RATETEMP;
            }            
            break;

        case 0x03:		    			
		    BAT_INFO_STEP++;
            if (BAT_INFO_STEP >= 0x0F)
			{
			    BAT_INFO_STEP = 0;
                BatLfcCapCal();				
			}            	
			
            //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_BatStatus, &BAT_ALARM1, SMBus_NoPEC);
			SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_BatStatus,&BAT_ALARM1);		
            //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, &BAT_LFCCAP, SMBus_NoPEC); //981004-230510-A
			SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_FCcap,&BAT_LFCCAP);
	        //LFCCAP_TEMP = (BAT_LFCCAP<<8)|(BAT_LFCCAP>>8); //981004-230428-A
            FCC_PERCENTAGE(); //981004-230605-A			
			
            if ((BAT_ALARM1) && (!BAT_DSNCAP)) //992022-130530-A Fix Bat. led not on after ship mode then AC in
                ConfigBatIn(); //992022-130530-A Fix Bat. led not on after ship mode then AC in
            break;    
    }    
   }	   
    BatPollingStep++;
}

//-----------------------------------------------------------------
// Config Battery In
//-----------------------------------------------------------------
void ConfigBatIn(void)
{
    //float FCC_Ratio; //981004-160909-A
	if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }
    //bRSMBusBlock(SMbusCh1, SMbusRBK, SmartBat_Addr, C_Dname , &BAT_DEVNAME);
	SMBUS_RW_BLK(0,ReadBlock,SmartBat_Addr,C_Dname,&BAT_DEVNAME);
	#if 0	
	if (((BAT_DEVNAME == 0x2D474147) /*&& (BAT_DEVNAME2== 0x2D47)*/)) //4 Cell => 0x4741472D //Old 99Watt //981004-230505-A //0X47414B34 => New battery
    {	    
        BIT_SET(EC_Flag4, old_99w); //0x388 BIT5		
    }
    else 	 
    {	          	        
        BIT_CLR(EC_Flag4, old_99w);       		
    }	
	#endif
  if (IS_BIT_SET(EC_Flag4, old_99w))
  {	
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_DCap, &BAT_DSNCAP, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_DCap,&BAT_DSNCAP);
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, &BAT_LFCCAP, SMBus_NoPEC); //981004-151002-R
   // bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_DVolt, &BAT_DSNVTG, SMBus_NoPEC);
	   SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_DVolt,&BAT_DSNVTG);
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RCalarm, &BAT_DSNCAPWN, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_RCalarm,&BAT_DSNCAPWN);
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RMcap, &BAT_RMCAP, SMBus_NoPEC);
	   SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_RMcap,&BAT_RMCAP);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_Current, &BAT_PRSNTRATE, SMBus_NoPEC);
	   SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_Current,&BAT_PRSNTRATE);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_BatStatus, &BAT_ALARM1, SMBus_NoPEC);
	SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_BatStatus,&BAT_ALARM1);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_CycleCount, &BAT_CYCLECNT, SMBus_NoPEC);	//981004-141230-A for reading cycle count
	SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_CycleCount,&BAT_CYCLECNT);
    //bRSMBusBlock(SMbusCh1, SMbusRBK, SmartBat_Addr, C_Dname , &BAT_DEVNAME); 	  
	SMBUS_RW_BLK(0,ReadBlock,SmartBat_Addr,C_Dname,&BAT_NEWDEVNAME);		
	//BAT_LFCCAP = 0x7219; //6514 //981004-200909-M	
	  BAT_LFCCAP = 0x1972; //Raymond0922
    //BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922; 
	RMCAP_TEMP2 = BAT_RMCAP;
	FCC_Ratio = Check_FCC_Ratio1(); 			 
    BAT_RMCAP = (uint16_t)(BAT_RMCAP * FCC_Ratio);  
	if (BAT_RMCAP >= 0x1972) //981004-200909-M 
    {
	    BAT_RMCAP = 0x1972; //981004-200909-M
	}
	//BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922;
   // LFCCAP_TEMP = (uint16_t)(BAT_LFCCAP<<8)|(BAT_LFCCAP>>8); //Raymond0922
	LFCCAP_TEMP = BAT_LFCCAP;
    DSNCAPLW_TEMP = LFCCAP_TEMP>>5;
    //BAT_DSNCAPLW = (uint16_t)(DSNCAPLW_TEMP<<8)|(DSNCAPLW_TEMP>>8);
	BAT_DSNCAPLW = DSNCAPLW_TEMP;
    BATCAP90 =(uint16_t)(LFCCAP_TEMP*0.9);
	BATCAP99 = (uint16_t)LFCCAP_TEMP*0.985; //981004-231218-A
    BATCAP98 = (uint16_t)(LFCCAP_TEMP*0.975);
	BATCAP97 = (uint16_t)(LFCCAP_TEMP*0.965); //981004-230505-A
    BATCAP10 = (uint16_t)(LFCCAP_TEMP - BATCAP90);
    BATCAP95 = (uint16_t)(LFCCAP_TEMP - (BATCAP10>>1));
    //BATCAP15 = BATCAP10 + (BATCAP10>>1); //981004-221004-R
	BATCAP20 = (uint16_t)(LFCCAP_TEMP* 0.2); 
	BATCAP25 = (uint16_t)(LFCCAP_TEMP* 0.25); //981004-221004-A
	BATCAP30 = (uint16_t)(LFCCAP_TEMP* 0.3); 
	BATCAP35 = (uint16_t)(LFCCAP_TEMP* 0.35); 
	BATCAP40 = (uint16_t)(LFCCAP_TEMP* 0.4); 
    BATCAP50 = (uint16_t)(LFCCAP_TEMP* 0.5);
    //BATCAP55 = LFCCAP_TEMP* 0.55; //981004-221007-A	
    BATCAP60 = (uint16_t)(LFCCAP_TEMP - BATCAP40);//981004-221007-R 
    BATCAP80 = (uint16_t)(LFCCAP_TEMP - BATCAP20); 
	//BATCAP75 = LFCCAP_TEMP - BATCAP15 - BATCAP10; //981004-221004-R
    BAT_PWRUNT = 0x01;
    BAT_TECH = 0x01;
    BAT_GRANUL1 = 0x0000;   
    BAT_GRANUL2 = 0x0000;   
    //BAT_OEMINFO1 = 0x4742;
    //BAT_OEMINFO2 = 0x5420;
  }
  else
  {
	//bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_DCap, &BAT_DSNCAP, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_DCap,&BAT_DSNCAP);
   // bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, &BAT_LFCCAP, SMBus_NoPEC); //ADD
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_FCcap,&BAT_LFCCAP);  
   // bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_DVolt, &BAT_DSNVTG, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_DVolt,&BAT_DSNVTG);		  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RCalarm, &BAT_DSNCAPWN, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_RCalarm,&BAT_DSNCAPWN);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_RMcap, &BAT_RMCAP, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_RMcap,&BAT_RMCAP);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_Current, &BAT_PRSNTRATE, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_Current,&BAT_PRSNTRATE);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_BatStatus, &BAT_ALARM1, SMBus_NoPEC);
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_BatStatus,&BAT_ALARM1);	  
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_CycleCount, &BAT_CYCLECNT, SMBus_NoPEC);	//981004-141230-A for reading cycle count
	  SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_CycleCount,&BAT_CYCLECNT);
	
			
	//BAT_LFCCAP = 0xD81D; //7640 //981004-230417-R	
    //BAT_RMCAP = (uint16_t)(BAT_RMCAP<<8)|(BAT_RMCAP>>8) //Raymond0922; 
	RMCAP_TEMP2 = BAT_RMCAP;
	//FCC_Ratio = Check_FCC_Ratio1(); //981004-230417-R			 
    //BAT_RMCAP = BAT_RMCAP * FCC_Ratio; //981004-230417-R
    BAT_RMCAP = (uint16_t)BAT_RMCAP;
    #if 0	
	if (BAT_RMCAP >= 0x1DD8) //981004-230417-R	
    {
	    BAT_RMCAP = 0x1DD8; //981004-220615-M
	}
	#endif
	//BAT_RMCAP = (uint16_t)((BAT_RMCAP<<8)|(BAT_RMCAP>>8));
	FCC_PERCENTAGE(); //981004-230605-A
	
	//981004-230510-R-S
	#if 0
	//BATCAP17 = LFCCAP_TEMP* 0.17; //981004-221028-R
	BATCAP20 = LFCCAP_TEMP* 0.2; 
	BATCAP30 = LFCCAP_TEMP* 0.3;
    BATCAP35 = LFCCAP_TEMP* 0.35; //981004-221209-A	
	BATCAP40 = LFCCAP_TEMP* 0.4; 
    BATCAP50 = LFCCAP_TEMP* 0.5; 
    BATCAP60 = LFCCAP_TEMP - BATCAP40; 
    BATCAP80 = LFCCAP_TEMP - BATCAP20; 
	BATCAP75 = LFCCAP_TEMP - BATCAP15 - BATCAP10;
    #endif
    //981004-230510-R-E
    BAT_PWRUNT = 0x01;
    BAT_TECH = 0x01;
    BAT_GRANUL1 = 0x0000;   
    BAT_GRANUL2 = 0x0000;   
    //BAT_OEMINFO1 = 0x4742;
    //BAT_OEMINFO2 = 0x5420;		  
  }	   
}


//-----------------------------------------------------------------
// Config A Battery Out
//-----------------------------------------------------------------
    
void ConfigBatOut(void)
{
	if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }	
        BAT_STATUS = 0x00;
        BAT_ALARM1 = 0x00;
        BAT_PRSNTRATE = 0x00;
		BAT_OPTION = 0x49F1; //Battery only setting + Inhibit charging
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
		SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
		//if (IS_BIT_CLR(POWER_FLAG1, enter_S3)) //981004-180731-A
        //{
		    BAT_LED_L = 1;
			//GPIO_Write(25,1);
		//}	
        BIT_CLR(POWER_FLAG4, pstate_off);
        BIT_CLR(POWER_FLAG12, bat_full); //981004-180412-A
		//BAT_LFCCAP = 0x0000;
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
		BIT_CLR(EC_Flag4, old_99w); //981004-230510-A
}



//-----------------------------------------------------------------
// The functioin of processing discharge
//-----------------------------------------------------------------
void ProcessDischarge(void)
{

    if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }	
  
 if ((IS_BIT_CLR(POWER_FLAG1, adapter_in)) && (IS_BIT_SET(BAT_STATUS, BAT_IN)) && (IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w)))  
 {     
      //Ship mode
      if (RMCAP_TEMP < 75) //7640 * 0.01 = 75 //981004-230510-M from 0x75
      { 	     
          BAT_CHGCURR = 0x0000; 
          BAT_CHGVOL = 0x0000;
          BAT_INCURR = 0x0000; 
          BAT_OPTION = 0x49F1; //Battery only setting + Inhibit charging for BQ24780 from 0x48F1 default + BIT0 =>  Inhibit charging (POR : 0x48F1+BI0= 0x49F1) 

			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
		  SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
		  SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Voltage,&BAT_CHGVOL);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);
		  SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_InCurr,&BAT_INCURR);	
		    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
		  SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
		  
           
			Ship_mode = 0x1000;       
          //bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
		  SMBUS_RW_W(0,WriteWord,SmartBat_Addr,BATCmd_access,&Ship_mode);
          //Delay1MS(250); 
			_Delay_1ms(250);		  
         // bRWSMBus(SMbusCh1, SMbusWW, SmartBat_Addr, BATCmd_access, &Ship_mode, SMBus_NoPEC);
		  SMBUS_RW_W(0,WriteWord,SmartBat_Addr,BATCmd_access,&Ship_mode);
//          for(ITempB01=0x00;ITempB01<20;ITempB01++)	//240us loop
//          {
//              Delay1MS(250);         		
//          }
			_Delay_1ms(5000);
      }    
        if (IS_BIT_CLR(BAT_STATUS, DISCHARGE))
        {	            		
            BIT_SET(BAT_STATUS, DISCHARGE);
            BIT_CLR(BAT_STATUS, CHARGE);
        }
		
		//RMCAP_TEMP = (uint16_t)((BAT_RMCAP<<8) | (BAT_RMCAP>>8)); //Raymond0922
		RMCAP_TEMP = BAT_RMCAP;
   
  if (IS_BIT_SET(POWER_FLAG2, sci_on))
  {	
    if (IS_BIT_CLR(POWER_FLAG1, enter_S3))
    {	                 
              //BQ24780 battery only setting		  
              if (BAT_OPTION != 0x49F1)
			  {
			    BAT_OPTION = 0x49F1;
				//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
				SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);				  
			  }
              
        if (IS_BIT_CLR(ProcsH, ProcsH_scion20sec)) //3A2 BIT1
        {
            if (IS_BIT_SET(ProcsH, ProcsH_acout)) //3A2 BIT0
            {
                ProcsH_cnt++; //3A1
                //dGPU_HOLD_EC_RST_L = 1; //981004-200724-A
                if (ProcsH_cnt == 2)  // sec.3				
                {
				  if (IS_BIT_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                  {
					BIT_CLR(EC_Flag4, nv_db20_lv0); 
                    BIT_CLR(EC_Flag4, nv_db20_lv1); 
                    BIT_CLR(EC_Flag4, nv_db20_lv2);
                    BIT_CLR(EC_Flag4, nv_db20_lv3);
	                BIT_CLR(EC_Flag4, nv_db20_lv4);
                    NV_DB20_SUPPORT();
				  }		
                }				
                if (ProcsH_cnt == 3)  // sec.3 
                {
			       if (PD_ADAPTER_IN) //981004-221005-M
				   {	
					  H_PROCHOT_L = 1; //Normal 
				   }
                   else
                   {
					  H_PROCHOT_L = 1; //Normal
				   }                   	 					
                }
				if (ProcsH_cnt >= 5)  // sec.5 
                {	
                    if (PD_ADAPTER_IN) //981004-221005-M
					{				
					    dGPU_HOLD_EC_RST_L = 0;//Normal 
                    }
                     else
                    {
						dGPU_HOLD_EC_RST_L = 0;//Normal
					}					
                    ProcsH_cnt =0;
                    BIT_CLR(ProcsH, ProcsH_acout); //3A2 BIT0
					BIT_CLR(POWER_FLAG10, gtx970_bat_low); //981004-220302-A
                }
            }            
        //-------------------------------------------------
       
            if ((IS_BIT_CLR(ProcsH, ProcsH_acout)) && (IS_BIT_CLR(AmpHigh_flag, AmpHigh))) //992022-140923-M //992022-140218-A for Processor Hot patch by Max request
            {
                //for DGPU
                if (RMCAP_TEMP <= BATCAP50) 
                {
				  if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                  {	 
                    if (IS_BIT_CLR(POWER_FLAG4, bat30_on)) 
                    {		   
                        BIT_SET(POWER_FLAG4, bat30_on); 
                        //981004-200130-M-S
						if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
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
                 if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                 { 
                    if (RMCAP_TEMP <= BATCAP25)
                    {
                     	if (PD_ADAPTER_IN)
					    {
                            H_PROCHOT_L = 0; //dCPU //981004-220928-M 
                            dGPU_HOLD_EC_RST_L = 1; //dGPU
					    }
                        else
                        {
						    H_PROCHOT_L = 0; //dCPU //981004-220928-M 
                            dGPU_HOLD_EC_RST_L = 1; //dGPU
						}
                        WTDP = 15;
                        WTDP2 = 45;	
                        WTDP4 = 90;	  
                            if (IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low))
                            {
								#if 0
								if (PD_ADAPTER_IN)
					            {
                                   H_PROCHOT_L = 0; //dCPU //981004-220928-M 
                                   dGPU_HOLD_EC_RST_L = 1; //dGPU
								}
                                else
                                {
									H_PROCHOT_L = 0; //dCPU //981004-220928-M 
                                    dGPU_HOLD_EC_RST_L = 1; //dGPU
								}
                                #endif			
                                BIT_SET(POWER_FLAG10, gtx970_bat_low);
								//ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA //981004-141014-A
								QeventSend(SCI_NV_DA);
                                if (NVDeventStatus3 == 0) //981004-221123-A
                                {
                                   if (IS_BIT_CLR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                                   {									
                                       NVDeventStatus = 0x0A; //981004-141014-A
								   }	   
                                }								   
                                //981004-200130-M-S
						        //if (IS_BIT_CLR(POWER_FLAG10, ac_current_180w)) //i7 CPU
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
                    else
                    {
                            BIT_CLR(POWER_FLAG10, gtx970_bat_low);
                    }
				 }                   
                }
                else  
                {
					if (IS_BIT_CLR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2
                    {	
                         BIT_CLR(POWER_FLAG4, bat30_on); //992022-130423-M
					}	 
                    if (IS_BIT_SET(POWER_FLAG6, ac_to_dc))		 
                    {		   
                        BIT_CLR(POWER_FLAG6, ac_to_dc);
                        //ECQEvent(SCI_BAT30ON, SCIMode_ACPI_SMBus); //0x65 //981004-221228-R                       
                    }	   
                }	   	                  
            }
        }       

    }
  }	

#if 0
  if (SystemIsS4)
  {
      BAT_LED_L = 1;
  }
  else if (IS_MASK_CLEAR(POWER_FLAG1, enter_S3) && (IS_MASK_CLEAR(POWER_FLAG2, LED_TEST_ON)))        	
  {
      if (RMCAP_TEMP <= BATCAP10)
      {        	  
            BAT_LED_L = ~BAT_LED_L; 			
      }
      else
      {          	  
           BAT_LED_L = 1;		  
      }
  }
  #endif
  
  //981004-231218-R-S
  #if 0 
  if (IS_MASK_CLEAR(POWER_FLAG2, LED_TEST_ON))
  {	  
    if (RMCAP_TEMP <= BATCAP20) //981004-231204-M from BATCAP10
    {        	  
        BAT_LED_L = ~BAT_LED_L; 			
    }
    else
    {          	  
       BAT_LED_L = 1;		  
    }
	BAT_FULL_L = 1; //981004-231204-A
  }	
  #endif
  //981004-231218-R-E     
 
	
  #if 1
  if (IS_BIT_SET(POWER_FLAG2, sci_on) && (IS_BIT_CLR(POWER_FLAG1, enter_S3))) //992022-140904-M //992022-130423-M //981004-120425-M
  {	
      if ((IS_BIT_CLR(ProcsH, ProcsH_scion20sec)) && (IS_BIT_CLR(ProcsH, ProcsH_acout))) //992022-140218-A for Processor Hot patch by Max request
      {
          
          if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(AmpHigh_flag, AmpHigh))) //992022-140923-M
          {		      
              if ((TEMPER_TEMP > 3280) && IS_BIT_CLR(POWER_FLAG4, pstate_off) ) //50 degree //981004-190308-M from 3180(45 degree)
              { 
 					SET_MASK(POWER_FLAG4, pstate_off);
                  	if (PD_ADAPTER_IN) //981004-221005-M
			      	{
                     	H_PROCHOT_L = 0; //dCPU 
                      	dGPU_HOLD_EC_RST_L = 1; //dGPU
				  	}
                  	else
                  	{
					  	H_PROCHOT_L = 0; //dCPU 
                      	dGPU_HOLD_EC_RST_L = 1; //dGPU
				  	}					  
                  if (IS_BIT_CLR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-A
                  {				  
                     // ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA 
					  QeventSend(SCI_NV_DA);
					  if (NVDeventStatus3 == 0) //981004-221123-A
                      {	                			  
                          NVDeventStatus = 0x0A;
					  }	                			                    
					  WTDP = 15;
                      WTDP2 = 45;
					  WTDP4 = 90;	                        
				  }
                 			  
              }
         
              if ((TEMPER_TEMP < 3260) && IS_MASK_SET(POWER_FLAG4, pstate_off) ) //53 degree //981004-230831-M from 47
              {                  
                  CLEAR_MASK(POWER_FLAG4, pstate_off);
                  if (PD_ADAPTER_IN) //981004-221005-M
			      {
                      H_PROCHOT_L = 1; //Normal 
                      dGPU_HOLD_EC_RST_L = 0; //Normal
				  }
                  else
                  {
					  H_PROCHOT_L = 1; //Normal 
                      dGPU_HOLD_EC_RST_L = 0; //Normal
				  }
                  //if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-R
                  //{				  
				     WTDP4 = 90; //981004-210401-A
				  //} 
              }				
          }
           if (IS_MASK_SET(AmpHigh_flag, AmpHigh))
          {
              AmpHighcnt++;			 
              if (AmpHighcnt >= 0x02) 
              {
                  if (PD_ADAPTER_IN) //981004-221005-M
			      {
                      H_PROCHOT_L = 1; //Normal 
                      dGPU_HOLD_EC_RST_L = 0; //Normal
				  }
                  else
                  {
					  H_PROCHOT_L = 1; //Normal 
                      dGPU_HOLD_EC_RST_L = 0; //Normal
				  }	
				  //if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-R
                  //{	
				      WTDP4 = 90; //981004-210401-A
				 // }
                  if (IS_MASK_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-A
                  {
				     CLEAR_MASK(EC_Flag4, nv_db20_lv0); 
                     CLEAR_MASK(EC_Flag4, nv_db20_lv1); 
                     CLEAR_MASK(EC_Flag4, nv_db20_lv2);
                     CLEAR_MASK(EC_Flag4, nv_db20_lv3);
	                 CLEAR_MASK(EC_Flag4, nv_db20_lv4);
					 NV_DB20_SUPPORT();
				  }					  
				  AmpHighcnt = 0;
                  CLEAR_MASK(AmpHigh_flag, AmpHigh);
                  CLEAR_MASK(POWER_FLAG4, bat30_on);
                  CLEAR_MASK(POWER_FLAG4, pstate_off);
                  CLEAR_MASK(POWER_FLAG10, gtx970_bat_low);				
              }
              return;
          } 
               
          //if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(POWER_FLAG4, pstate_off))) //981004-221025-M
		  if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(POWER_FLAG4, pstate_off)) && (IS_BIT_CLR(POWER_FLAG7, PPAB_ON))) //981004-221228-M
          {	                		
			if (IS_BIT_CLR(AmpHigh_flag, AmpHigh))
            {
             if (IS_BIT_SET(EC_Flag4, old_99w))
	         {				
			  if (((RMCAP_TEMP >= BATCAP80) && (PRSNTRATE_TEMP > 6500)) || ((RMCAP_TEMP < BATCAP80) && (RMCAP_TEMP >= BATCAP50) && (PRSNTRATE_TEMP > 6500)) 
			  || ((RMCAP_TEMP < BATCAP50) && (PRSNTRATE_TEMP > 5250))) 
			  {
			      BIT_SET(POWER_FLAG7, dgpu_9Aon);                  			  
			  }
			  else
			  {
			      BIT_CLR(POWER_FLAG7, dgpu_9Aon);                 			  
			  }
             }
			 else
		     {
			  if (((RMCAP_TEMP >= BATCAP50) && (PRSNTRATE_TEMP > 8000)) || ((RMCAP_TEMP < BATCAP50) && (PRSNTRATE_TEMP > 7000))) //981004-221005-M
			  {
			      BIT_SET(POWER_FLAG7, dgpu_9Aon);                  			  
			  }
			  else
			  {
			      BIT_CLR(POWER_FLAG7, dgpu_9Aon);                 			  
			  }			  	 
			 }		 
            			 
			}  
          }
      }				      
  }
  #endif
   if (IS_BIT_SET(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-A
   {
      NV_DB20_SUPPORT(); //981004-221025-A 
	  BIT_SET(POWER_FLAG7, PPAB_ON2); //EC RAM 0x207 bit0
      BIT_CLR(EC_Flag3, DC_PPAB_OFF); //981004-230131-A	  
   }
   else
   {
	  BIT_SET(EC_Flag3, DC_PPAB_OFF); //981004-230131-A
	  if (IS_BIT_SET(POWER_FLAG7, PPAB_ON2)) //EC RAM 0x207 bit0
	  {
		  BIT_CLR(POWER_FLAG7, PPAB_ON2); //EC RAM 0x207 bit0
		  //ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA
		  QeventSend(SCI_NV_DA);
		  if (NVDeventStatus3 == 0) //981004-221123-A
          {	
		      NVDeventStatus = 0x0A;
		  }	  
          BIT_CLR(EC_Flag4, nv_db20_lv0); 
          BIT_CLR(EC_Flag4, nv_db20_lv1); 
          BIT_CLR(EC_Flag4, nv_db20_lv2);
          BIT_CLR(EC_Flag4, nv_db20_lv3);
	      BIT_CLR(EC_Flag4, nv_db20_lv4);		  
	  }
	  if (IS_BIT_SET(EC_Flag5, AC_PPAB_ON)) //EC RAM 0x389 bit7 //981004-230131-A
      {
		  BIT_SET(EC_Flag3, DC_PPAB_OFF); 
		  //ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus); //0xDA
		  QeventSend(SCI_NV_DA);
		  BIT_CLR(EC_Flag5, AC_PPAB_ON); //EC RAM 0x389 bit7
          if (NVDeventStatus3 == 0) 
          {			   
              NVDeventStatus = 0x0A;			  
          }							 		     
	  }			
   }	   
 }   
}

//-----------------------------------------------------------------
// The functioin of processing Charge
//-----------------------------------------------------------------
void ProcessCharge(void)
{
    if (IS_BIT_SET(POWER_FLAG3, ship_mode) || (xITEPD_FlashUtilityEnable)) //981004-220901-A
    {
         return;
    }	
    if (((IS_BIT_SET(POWER_FLAG1, adapter_in)) && (IS_BIT_SET(BAT_STATUS, BAT_IN))) || (((IS_BIT_SET(POWER_FLAG11, pd_ac_over65w)) && (IS_BIT_SET(BAT_STATUS, BAT_IN)))))
    {
      if (IS_BIT_SET(EC_Flag4, old_99w)) //981004-230510-A
	  {		
        //981004-171107-M-S	
		if(BAT_CUSTOMIZE_CHECK(0))
		{	
			 BAT_CUSTOMIZE_CHECK(3);
		}
		else
		{
			if ((BAT_RMCAP3 < 6514)) //981004-200909-M 
			{ 
				BAT100CNT = 0; 			
				//if (IS_BIT_CLR(BAT_STATUS, CHARGE)) //981004-171107-R
				//{						  
					if ((IS_BIT_CLR(POWER_FLAG12, bat_full)) && (IS_BIT_CLR(POWER_FLAG7, bat_cap97))) 
					{
						BIT_SET(BAT_STATUS, CHARGE);
					}
				//}
				//981004-211208-M-S	
			  if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
              {					
				if (IS_MASK_CLEAR(POWER_FLAG12, bat_full))
				{
				    BAT_OPTION = 0x4CF9;
                }
                else
                {
                    BAT_OPTION = 0x4DF9;                   				
                }
			  }
              else
	          {
		            BAT_OPTION = 0x6CF9; 		  
	          }	  				  
              //981004-211208-M-E
				
			    //981004-181123-M-S
                //if (IS_BIT_SET(BAT_STATUS, CHARGE))
				//{						
                  //if ((RMCAP_TEMP >= BATCAP90))
				  if ((RMCAP_TEMP > BATCAP95)) //981004-230614-M	  
			      {
			         if (IS_MASK_SET(BAT_ALARM1, FullyChg))
				    {
					   if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
                      {	
				        if (IS_MASK_CLEAR(POWER_FLAG12, bat_full))				
                        {					
                           //BAT_RMCAP = 6514; 						   
						   BAT_RMCAP = BAT_LFCCAP;//981004-220912-M	                           						   
						   SET_MASK(POWER_FLAG12, bat_full);
						   CLEAR_MASK(BAT_STATUS, CHARGE); 						
						   if (IS_MASK_CLEAR(POWER_FLAG7, bat_cap97))
						   {
						     SET_MASK(POWER_FLAG12, bat_100);
						   }						
					    }					    
                        BAT_OPTION = 0x4DF9; 					
					  }
                      else
                      {
						BAT_OPTION = 0x6CF9;   
					  }						  
				    }
			      }
			    //}				
			    //981004-181123-A-E
            }                    		
            else //if ((PRSNTRATE_TEMP2 < 100)) //981004-151019-M 		
            {
		    //if ((BAT_RATETEMP & 0x0080) == 0 && (AC_boost_Status == 0) && (IS_BIT_CLR(POWER_FLAG3, Trickle_Chg_ON))) //981004-160822-M
			//{
		    //if ((PRSNTRATE_TEMP2 < 100))
			//{
			    BAT100CNT++;				
				if (BAT100CNT >= 10) //981004-171106-M from 2
				{
				   if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2 
                   {		 				    if (IS_MASK_CLEAR(POWER_FLAG12, bat_full)) //981004-160108-A
					//if (IS_MASK_CLEAR(POWER_FLAG12, bat_100)) //981004-160108-R
                    {					
                        //BAT_RMCAP = 6514; //981004-200909-M
                        BAT_RMCAP = BAT_LFCCAP;//981004-220912-M 						
						SET_MASK(POWER_FLAG12, bat_full);
						CLEAR_MASK(BAT_STATUS, CHARGE); 
						if (IS_MASK_CLEAR(POWER_FLAG7, bat_cap97))
						{
						    SET_MASK(POWER_FLAG12, bat_100);
						}						
					}					    
                    BAT_OPTION = 0x4DF9; 		                    
					BAT100CNT = 0;
				
				   }
				   else
				   {
					  BAT_OPTION = 0x6CF9;
				   }	   
             				   
				}			
            }
			BIT_CLR(BAT_STATUS, DISCHARGE); 
            //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
        }

        //981004-181107-R-S
		#if 0
        if (IS_BIT_SET(POWER_FLAG5, bat_chg_current_chk)) 
        { 
            if ((PRSNTRATE_TEMP2 <= 2700)) //Under Heavy loading
			{
			    Heavy_Load_cnt++;
				if (Heavy_Load_cnt >= 20)
				{
				    Heavy_Load_cnt = 0;
					ECQEvent(SCI_HEAVY_LOAD, SCIMode_ACPI_SMBus);  //0x69 
				}
			}
        }
		#endif
        //981004-181107-R-E		
       
		if (!SLP_S4_L)
		{
		    if (RMCAP_TEMP <= (BATCAP10>>3))
            {
                ConfigCharger();  
            }
		}	       
	}
	else
	{
	          //981004-171107-M-S	
		if(BAT_CUSTOMIZE_CHECK(0))
		{	
			 BAT_CUSTOMIZE_CHECK(3);
		}
		else
		{
			//if ((BAT_RMCAP3 < 7640)) //981004-230417-M //LFCCAP_TEMP
			#if 0
			if (BAT_RMCAP3 < LFCCAP_TEMP)
			{ 
				BAT100CNT = 0; 			
				//if (IS_BIT_CLR(BAT_STATUS, CHARGE)) //981004-171107-R
				//{						  
					if ((IS_BIT_CLR(POWER_FLAG12, bat_full)) && (IS_BIT_CLR(POWER_FLAG7, bat_cap97))) 
					{
						BIT_SET(BAT_STATUS, CHARGE);
					}
				//}
				
			  //981004-211208-M-S	
			  if ((IS_BIT_CLR(EC_Flag5, learn_mode0)) && (IS_BIT_CLR(EC_Flag5, learn_mode1)) && (IS_BIT_CLR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
              {					
				if (IS_BIT_CLR(POWER_FLAG12, bat_full))
				{
				    BAT_OPTION = 0x4CF9;
                }
                else
                {
                    BAT_OPTION = 0x4DF9;                   				
                }
			  }
              else
	          {
		            BAT_OPTION = 0x6CF9; 		  
	          }	  				  
              //981004-211208-M-E           		
				
			    //981004-181123-M-S
                //if (IS_BIT_SET(BAT_STATUS, CHARGE))
				//{						
                  if ((RMCAP_TEMP >= BATCAP90))
			      {
			        if (IS_BIT_SET(BAT_ALARM1, FullyChg))
				    {
					   if ((IS_BIT_CLR(EC_Flag5, learn_mode0)) && (IS_BIT_CLR(EC_Flag5, learn_mode1)) && (IS_BIT_CLR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
                      {	
				        if (IS_BIT_CLR(POWER_FLAG12, bat_full))				
                        {					
                           //BAT_RMCAP = 7640; 						   
						   BAT_RMCAP = BAT_LFCCAP; //981004-230417-M //LFCCAP_TEMP	                           						   
						   BIT_SET(POWER_FLAG12, bat_full);
						   BIT_CLR(BAT_STATUS, CHARGE); 						
						   if (IS_BIT_CLR(POWER_FLAG7, bat_cap97))
						   {
						     BIT_SET(POWER_FLAG12, bat_100);
						   }						
					    }					    
                        BAT_OPTION = 0x4DF9; 					
					  }                      				  
				    }
			      }
			    //}				
			    //981004-181123-A-E
            }                    		
            else //if ((PRSNTRATE_TEMP2 < 100)) //981004-151019-M 		
            {
		    //if ((BAT_RATETEMP & 0x0080) == 0 && (AC_boost_Status == 0) && (IS_BIT_CLR(POWER_FLAG3, Trickle_Chg_ON))) //981004-160822-M
			//{
		    //if ((PRSNTRATE_TEMP2 < 100))
			//{
			     BAT100CNT++;				
				if (BAT100CNT >= 10) //981004-171106-M from 2
				{
				   if ((IS_BIT_CLR(EC_Flag5, learn_mode0)) && (IS_BIT_CLR(EC_Flag5, learn_mode1)) && (IS_BIT_CLR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2 
                   {		 				   
				    if (IS_BIT_CLR(POWER_FLAG12, bat_full)) //981004-160108-A
					//if (IS_BIT_CLR(POWER_FLAG12, bat_100)) //981004-160108-R
                    {					
                        //BAT_RMCAP = 7640; //981004-200909-M
                        BAT_RMCAP = BAT_LFCCAP; //981004-230417-M //LFCCAP_TEMP 						
						BIT_SET(POWER_FLAG12, bat_full);
						BIT_CLR(BAT_STATUS, CHARGE); 
						if (IS_BIT_CLR(POWER_FLAG7, bat_cap97))
						{
						    BIT_SET(POWER_FLAG12, bat_100);
						}						
					}					    
                    BAT_OPTION = 0x4DF9; 		                    
					BAT100CNT = 0;
				
				   }
				   else
				   {
					  BAT_OPTION = 0x6CF9;
				   }	   
             				   
				}			
            }
			#endif
			
			//New start //981004-230427-M
			if ((IS_BIT_CLR(POWER_FLAG12, bat_full)) && (IS_BIT_CLR(POWER_FLAG7, bat_cap97))) 
		    {
				BIT_SET(BAT_STATUS, CHARGE);
		    }											  								
			if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
            {					
				if (IS_MASK_CLEAR(POWER_FLAG12, bat_full))
				{
				    BAT_OPTION = 0x4CF9;
                }
                else
                {
                    BAT_OPTION = 0x4DF9;                   				
                }
			}
            else
	        {
		        BAT_OPTION = 0x6CF9; 		  
	        }			          
            if (IS_BIT_SET(BAT_ALARM1, FullyChg))
		    {			   	
				if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
                {	
				    if (IS_MASK_CLEAR(POWER_FLAG12, bat_full))				
                    {					                           					   
						//BAT_RMCAP = BAT_LFCCAP; //981004-230417-M //LFCCAP_TEMP	                           						   
						SET_MASK(POWER_FLAG12, bat_full);
						CLEAR_MASK(BAT_STATUS, CHARGE); 						
						if (IS_MASK_CLEAR(POWER_FLAG7, bat_cap97))
						{
						     SET_MASK(POWER_FLAG12, bat_100);
						}						
					}					    
                    BAT_OPTION = 0x4DF9; 					
			    }
                else
                {
				    BAT_OPTION = 0x6CF9;   
			    }					
			   					  
			}			
			BIT_CLR(BAT_STATUS, DISCHARGE); 
            //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
        }

        //981004-181107-R-S
		#if 0
        if (IS_BIT_SET(POWER_FLAG5, bat_chg_current_chk)) 
        { 
            if ((PRSNTRATE_TEMP2 <= 2700)) //Under Heavy loading
			{
			    Heavy_Load_cnt++;
				if (Heavy_Load_cnt >= 20)
				{
				    Heavy_Load_cnt = 0;
					ECQEvent(SCI_HEAVY_LOAD, SCIMode_ACPI_SMBus);  //0x69 
				}
			}
        }
		#endif
        //981004-181107-R-E		
       
		if (!SLP_S4_L)
		{
		    if (RMCAP_TEMP <= (BATCAP10>>3))
            {
                ConfigCharger();  
            }
		}
        //981004-220510-A-S					
        if ((IS_MASK_CLEAR(POWER_FLAG3, ship_mode)) && (IS_MASK_CLEAR(EC_Flag5, fix_ac_voltage)) && (!xITEPD_FlashUtilityEnable)) //0X203 BIT6 / 0X389 BIT 6 //981004-231128-M
	    {			
			//SetBatCHGCurrent(); 
			SetBatCHGVoltage();
			//if (TEMP_TR8 >= 70) //981004-240111-M-S
			if (TEMP_TR7 >= 78)
	        {
		        SET_MASK(EC_Flag5, TR8_heat_CHG2);               				
	        }
            if ((TEMP_TR7 <= 57) && (IS_MASK_SET(EC_Flag5, TR8_heat_CHG2)))
            {
		        CLEAR_MASK(EC_Flag5, TR8_heat_CHG2);               				
	        }
            if ((IS_MASK_CLEAR(EC_Flag5, TR8_heat_CHG2)))   
        	{
				SetBatCHGCurrent();                
            }
            else
            {
				//BAT_CHGCURR = 0x800C;	//3.2A
				BAT_CHGCURR = 0x0004;	//1.024A				
			}				
	    } 	
	}	
  }	
}

void ConfigCharger(void)
{    
    //981004-171107-M-S	                              														
	CheckChargerSetting(); //981004-171107-A
	ConfigACLIMIT(); //981004-230707-A
	
    //BAT_INCURR = 0x0016; //4.096+1.024+0.512 = 5.632A (5.632*2 = 11.264A) (226 Watt)
	//BAT_INCURR = 0x0013; //4.096+0.512+0.256 = 4.864A (4.864*4 = 19.456A) (2.5 Ohm , 4*) //981004-170224-M
	//BAT_INCURR = 0x0015; //4.096+1.024+0.256 = 5.376A (5.376*4 = 21.504A) (2.5 Ohm , 4*) //981004-170822-M (373 Watt)
     //BAT_INCURR = 0x0016; //4.096+1.024+0.512 = 5.632A (5.632*2 = 11.264A) (226 Watt)
    //BAT_INCURR = 0x8016; //4.096+1.024+0.512+0.128 = 5.76A (5.76*2 = 11.52A) 
    //BAT_INCURR = 0x0019; //4.096+2.048+0.256 = 6.4A (6.4*2 = 12.8A) //234.8 Watt
    //BAT_INCURR = 0x0018; //4.096+2.048= 6.144A (6.144*2 = 12.288A) //240.6 Watt //981004-200923-M from 0x0019
	//if (IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w)) //EC RAM 0x211 bit4
	
    //BAT_INCURR = 0x8019; //4.096+2.048+0.256 +0.128 = 6.528A (6.528*2 = 13.056A) //981004-190318-M from 0x0019
    //BAT_INCURR = 0x801F;	
    //981004-1607046-M-E
	
	//BAT_OPTION = IS_BIT_CLR(BAT_ALARM1, FullyChg) ? 0x4CF9 : 0x4DF9; //If fully charged,turn off charging function (BIT 0) //981004-150615-M	

    //981004-171107-M-S	
	    //981004-211208-M-S
    if ((IS_MASK_CLEAR(EC_Flag5, learn_mode0)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode1)) && (IS_MASK_CLEAR(EC_Flag5, learn_mode2))) //EC RAM 0x389 bit0/1/2
    {
	if (IS_BIT_CLR(POWER_FLAG15, BAT_CUSTOM))	
	{	
        if (IS_BIT_CLR(POWER_FLAG12, bat_full))		
        {
           BAT_OPTION = 0x4CF9;             		   
        }
        else
        {
          BAT_OPTION = 0x4DF9;		  
        }
	}	
	else
	{
	    if (IS_BIT_CLR(POWER_FLAG4, bat_custom_end))		
        {
           BAT_OPTION = 0x4CF9;            		   
        }
        else
        {
          BAT_OPTION = 0x4DF9;
		  BAT_LED_L = 1; //981004-240425-A 		  
        }
	}
	}
	else
	{
		BAT_OPTION = 0x6CF9; 
	}
    //981004-171107-M-E
	
    BAT_OPTION2 = 0x12E6; //981004-200610-M  from 0x12C1 for BQ24780S (RSNS_RATIO & EN_PMON) P27
		//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_ChgCurr, &BAT_CHGCURR , SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_ChgCurr,&BAT_CHGCURR);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Voltage, &BAT_CHGVOL , SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Voltage,&BAT_CHGVOL);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_InCurr,  &BAT_INCURR ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_InCurr,&BAT_INCURR);		
		    //bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option,  &BAT_OPTION ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option,&BAT_OPTION);
			//bRWSMBus(SMbusCh1, SMbusWW, Charger_Addr, CHGCmd_Option2, &BAT_OPTION2 ,  SMBus_NoPEC);
			SMBUS_RW_W(0,WriteWord,Charger_Addr,CHGCmd_Option2,&BAT_OPTION2);		
}
//981004-130819-M-E
//981004-230707-A-S
void ConfigACLIMIT(void)
{     
    if (!AC_IN_L)
	{
        BAT_INCURR = 0x0018; //4.096+2.048 = 6.144A (6.144*2 = 12.288A) //232.8Watt //981004-220915-M from 0x8015
		//BAT_INCURR = 0x0017; //4.096+1.024++0.512+0.256 = 5.888A (5.888*2 = 11.776A) //232.8Watt //981004-210322-M
        //BAT_INCURR = 0x801C; //4.096+2.048+1.024++0.128 = 7.296A (7.296*2 = 14.592A) //232.8Watt //981004-220927-M
		//BAT_INCURR = 0x8015; //4.096+1.024+0.256+0.128 = 5.504A (5.504*2 = 10.108A) //274.2Watt /981004-220927-R
    }
    else
    {
       if (IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))   
       {
		  BAT_INCURR = 0x0004; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt //981004-230707-M from 0x0008  
		 //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
         //BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt /981004-220927-M
        //BAT_INCURR = 0x0009; //2.048++0.256 = 2.304A (2.304*2 = 4.608A) //84 Watt //981004-210824-M
        //BAT_INCURR = 0x0005; //1.024+0.256 = 1.28A (1.28*2 = 2.56A) //84Watt /981004-220927-R          	
	   }
	   else
	   {	   
	      if (IS_BIT_SET(EC_Flag6, PD_60W))
	      {
		      BAT_INCURR = 0x0004; //1.024 => 2.048A (1.024*2 = 2.048A) //40 Watt		      
	      }
          if (IS_BIT_SET(EC_Flag6, PD_65W))
	      {
		      BAT_INCURR = 0x8004; 		      
	      }
          if (IS_BIT_SET(EC_Flag6, PD_80W))
	      {
		      BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt 		      
	      }	
          if (IS_BIT_SET(EC_Flag6, PD_100W))
	      {
		      BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt 		      
	      }	
       }		  
    }


}
//981004-230707-A-E

//981004-180731-R-S
#if 0
//-----------------------------------------------------------------
// Showing remain capacity with LEDs
//-----------------------------------------------------------------
uint8_t OEM_ShowRmCap(void)
{
    //WORD LFCCAP, RMCAP; //981004-130104-R 
    float RMCAP0, RMCAP1, RMCAP2, RMCAP3, RMCAP4; //981004-160909-A
    uint8_t cnt=0, cnt2=0, quit=1; //981004-140505-A
	
	WDTCON = 0x01; //P150 bit0 : WD timer reset bit1 : WD timer Disable
    
    while (!bRWSMBus(SMbusChA, SMbusRW, SmBat_Addr, C_RMcap, &BAT_RMCAP, SMBus_NoPEC))
        if (cnt2++ == 0x10)
            break;
    //981004-140505-A-E fix battery check reading wrong after ship mode

	BAT_RMCAP = (BAT_RMCAP<<8)|(BAT_RMCAP>>8); 
	RMCAP_TEMP2 = BAT_RMCAP;
	FCC_Ratio = Check_FCC_Ratio1(); //98100-160909-A //74Watt	
	//BAT_RMCAP = BAT_RMCAP * 1.14; //981004-160909-R from 1.1			 
    BAT_RMCAP = BAT_RMCAP * FCC_Ratio; //98100-160909-A			
	if (BAT_RMCAP >= 0x1972) //981004-200909-M 
	{
	    BAT_RMCAP = 0x1972; //981004-200909-M
	}
	BAT_RMCAP = (BAT_RMCAP<<8)|(BAT_RMCAP>>8);
	BAT_LFCCAP = 0x7219; //6514 //981004-200909-M		
    LFCCAP = ((BAT_LFCCAP<<8) | (BAT_LFCCAP>>8)); 
    RMCAP = (BAT_RMCAP<<8) | (BAT_RMCAP>>8);
    //981004-140505-A-S fix battery check reading wrong after ship mode
    if (!LFCCAP)
        LFCCAP = 0xFFFF;
    //981004-140505-A-E fix battery check reading wrong after ship mode

    RMCAP0 = LFCCAP * 0.1; 
    RMCAP1 = LFCCAP * 0.3; 
    RMCAP2 = LFCCAP * 0.5; 
    RMCAP3 = LFCCAP * 0.7; 
    RMCAP4 = LFCCAP * 0.9; 

    WLAN_LED_EN = 1;
    BT_LED = 0; 
    WLAN_LED = 0;
    HD_LED = 0;
    BAT_LED_L = 1; 
    PWR_LED_L = 1; 
    PWR_LED2_L = 1; //981004-220719-M	

    if (RMCAP > RMCAP4)
    {        
		BT_LED = 1; 
        Delay1MS(255); //981004-160104-M
        WLAN_LED = 1;
        Delay1MS(255);//981004-160104-M
        HD_LED = 1;
        Delay1MS(255);//981004-160104-M
        BAT_LED_L = 0; 
        Delay1MS(255);//981004-160104-M
        PWR_LED_L = 0;     	
    }
    else if (RMCAP > RMCAP3)
    {        
		BT_LED = 1; 
        Delay1MS(255);//981004-160104-M
        WLAN_LED = 1;
        Delay1MS(255);//981004-160104-M
        HD_LED = 1;
        Delay1MS(255);//981004-160104-M
        BAT_LED_L = 0; 
    }
    else if (RMCAP > RMCAP2)
    {     
	   BT_LED = 1; 
       Delay1MS(255);//981004-160104-M
       WLAN_LED = 1;
       Delay1MS(255);//981004-160104-M
       HD_LED = 1;
    }
    else if (RMCAP > RMCAP1)
    {       
		BT_LED = 1; 
        Delay1MS(255);//981004-160104-M
        WLAN_LED = 1;
    }
    else if (RMCAP > RMCAP0)        
		BT_LED = 1; 
    else
    {
        if (FUC_EN_L)
            quit <<= 1;

        while (cnt < SHOWTIME && ~(quit | 0xFB))
        {
            cnt++;
           BT_LED = ~BT_LED; 
            Delay1MS(255);//981004-160104-M

            if ((FUC_EN_L && quit==1) || (!FUC_EN_L && quit==2))
                quit <<= 1;
        }

        return (0);
    }

    return (SHOWTIME);
}
#endif
//981004-180731-R-E

//----------------------------------------------------------------------------
// The Smart charge control function
//----------------------------------------------------------------------------
float Smartcharge(uint8_t Charge)
{
    switch (Charge)
    {
        case 0:
            //return(CAP0);			
			return(BATCAP30);

        case 1:		             
            return(BATCAP30); 			

        case 2:          	             
			return(BATCAP40); 

        case 3:		              
            return(BATCAP50); 		
        		
        default:		 
            //return(CAP0);			
			return(BATCAP30);
    }
}

float Check_FCC_Ratio1(void)
{
    //float FCC_Ratio; 
	
    //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, &BAT_LFCCAP, SMBus_NoPEC);
	SMBUS_RW_W(0,ReadWord,SmBat_Addr,BATCmd_FCcap,&BAT_LFCCAP);
	//BAT_LFCCAP2 =(uint16_t)(BAT_LFCCAP<<8)|(BAT_LFCCAP>>8);
	BAT_LFCCAP2	= BAT_LFCCAP;
    FCC_Ratio = (float)6514/BAT_LFCCAP2; //981004-200909-M
    //BAT_LFCCAP = 0x7219; //6514	//981004-200909-M
	BAT_LFCCAP = 0x1972; //Raymond0922
	
	//981004-190327-A-S
    if (FCC_Ratio < 1)
	{
	    FCC_Ratio = 1;

	}	
	//981004-190327-A-E
	
	//981004-181107-R-S Per Max REQUEST
	#if 0
	if (IS_BIT_SET(POWER_FLAG12, BAT_QUALITY)) //981004-190906-M
	{
	    if (FCC_Ratio < 1.07)
	    {
	        FCC_Ratio = 1.07;
	    }
	}	
	else
	{
	    if (FCC_Ratio < 1.14)
	    {
	        FCC_Ratio = 1.14;
	    }
	}
    #endif	
	//981004-181107-R-E
	
	return FCC_Ratio;
}

//981004-181107-M-S
void CheckChargerSetting(void)
{	                                                         														
    //981004-200923-R-S to OEM_MAIN.C
    #if 0	
	if ((TEMPER_TEMP <= LOW_TEMPER) || (TEMPER_TEMP >= HIGH_TEMPER)) //(15 Lower or 50 Higher Celsius degree) //981004-171107-M from 10/40
	{  		    
        //BAT_CHGCURR = 0x8004; //1.024+0.128 = 1.152A (Target : 1.2A )	
        //BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A (Target : 1.278A ) //981004-200923-M from 0x8004 		
	}			
    else
    {             					
        //BAT_CHGCURR = 0xC00B; //2.048+0.512+0.256+0.128+0.064 = 3.008A 
        //BAT_CHGCURR = 0x000C; //2.048+1.024 = 3.072A 
        //BAT_CHGCURR = 0x800C; //2.048+1.024+0.128 = 3.2A 
        //BAT_CHGCURR = 0x400C; //2.048+1.024+0.064= 3.136A //981004-200115-M per MAX req (3.118A)		
    }																																												
    #endif	
    //981004-200923-R-E
   if (IS_BIT_SET(EC_Flag4, old_99w)) //981004-230510-A
   {
    if ((TEMPER_TEMP >= HIGH_TEMPER)) 
	{					
	    BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)		
	}	
	//981004-190327-M-S
    else
    {	   
       //if ((IS_BIT_SET(POWER_FLAG12, BAT_QUALITY)) && (BAT_CYCLECNT <= 30)) //EC RAM 20C bit 1 //981004-190906-M from POWER_FLAG15
	   //if ((IS_BIT_SET(POWER_FLAG12, BAT_QUALITY)) && (IS_BIT_SET(POWER_FLAG7, bat_100hrs))) //EC RAM 20C bit 1 + 207 BIT 5 //981004-191122-M
	   if (IS_BIT_SET(POWER_FLAG12, BAT_QUALITY)) //EC RAM 20C bit 1 //981004-201203-M
	   {
          //BAT_CHGVOL = 0xC043; // 16.384+0.512+0.256+0.128+0.064 = 17.344V (Target => 17.35V)
		  //BAT_CHGVOL = 0x2044; // 16.384+1.024+0.032 = 17.44V (Target => 17.35V) 
		  //BAT_CHGVOL = 0x1044; // 16.384+1.024+0.016 = 17.424V (Target => 17.35V) 
		  //BAT_CHGVOL = 0x8043; // 16.384+0.512+0.256+0.128 = 17.28V (Target => 17.2V)
          //BAT_CHGVOL = 0x6043; // 16.384+0.512+0.256+0.064 + 0.032 = 17.248V (Target => 17.191V) 
          BAT_CHGVOL = 0x5043; // 16.384+0.512+0.256+0.064 + 0.016 = 17.232V (Target => 17.189V) 		  
       }   
       else
       {		   
	      BAT_CHGVOL = 0x6042; // 16.384+0.512+0.64+0.32 = 16.992V (Target => 17V Actually => 16.945) //981004-210322-M 
		  //BAT_CHGVOL = 0x8042; // 16.384+0.512+0.128 = 17.024V (Target => 16.989V) //981004-191126-M per Max request
       }
	}
   }	
    //981004-190327-M-E	
	
    if (IS_BIT_CLR(POWER_FLAG15, BAT_CUSTOM)) 	
	{ 
        BIT_CLR(POWER_FLAG4, bat_custom_end); 		
    }
}
//981004-220510-A-S
void SetBatCHGCurrent(void)
{
	if (GAUGE_CURRENT == 0)
    {
		GAUGE_CURRENT_CNT1++;
		if (GAUGE_CURRENT_CNT1 >= 3)
		{	
		    BAT_CHGCURR = 0;
		}	
	}
    else
    {
		 GAUGE_CURRENT_CNT1 = 0;
	}
    if (GAUGE_CURRENT == 256)
    {
		GAUGE_CURRENT_CNT2++;
		if (GAUGE_CURRENT_CNT2 >= 3)
		{	
		    BAT_CHGCURR = 0x0001; //0.256A
		}	
	}
    else
    {
		 GAUGE_CURRENT_CNT2 = 0;
	}    
    if (GAUGE_CURRENT == 1275)
    {
		GAUGE_CURRENT_CNT3++;
		if (GAUGE_CURRENT_CNT3 >= 3)
		{	
		    //BAT_CHGCURR = 0xE008; //2.048++0.128+0.064+0.032 = 2.262A
			//BAT_CHGCURR = 0x0005; //1.024+0.256 = 1.28A(Target : 1.275A)
			BAT_CHGCURR = 0xC004; //1.024+0.128+0.064 = 1.216A(Target : 1.275A)
		}	
	}
    else
    {
		 GAUGE_CURRENT_CNT3 = 0;
	}	
    if (GAUGE_CURRENT == 1913)
    {
		GAUGE_CURRENT_CNT4++;
		if (GAUGE_CURRENT_CNT4 >= 3)
		{	
		    //BAT_CHGCURR = 0xC00E; //1.024+0.512+0.256+0.128+= 3.776A
			//BAT_CHGCURR = 0x8007; //1.024+0.512+0.256+0.128+= 1.92A (Target : 1.913A)
			BAT_CHGCURR = 0x4007; //1.024+0.512+0.256+0.064+= 1.858A (Target : 1.913A)
		}	
	}
    else
    {
		 GAUGE_CURRENT_CNT4 = 0;
	}	
    if (GAUGE_CURRENT == 3188)
    {
		GAUGE_CURRENT_CNT5++;
		if (GAUGE_CURRENT_CNT5 >= 3)
		{	
		    //BAT_CHGCURR = 0xC011; //4.096+0.256+0.128+0.064 = 4.544A
			BAT_CHGCURR = 0x400C; //2.048+1.024+0.064 = 3.136A (Target : 3.188A)
		}	
	}
    else
    {
		 GAUGE_CURRENT_CNT5 = 0;
	}	
	if (GAUGE_CURRENT == 7650)
    {
		GAUGE_CURRENT_CNT6++;
		if (GAUGE_CURRENT_CNT6 >= 3)
		{	
		    //BAT_CHGCURR = 0x401F; //4.096+2.048+1.024+0.512+0.256+0.064 = 8.0A
			//BAT_CHGCURR = 0x4019; //4.096+2.048+0.256+0.064 = 6.464A 
			BAT_CHGCURR = 0xC018; //4.096+2.048+0.128+0.064 = 6.336A //981004-230612-M 
			//BAT_CHGCURR = 0xC01D; //4.096+2.048+1.024+0.256+0.128+0.064 = 7.616A (Target : 7.65A) //981004-230612-R
			//BAT_CHGCURR = 0x4017; //4.096+1.024+0.512+0.256+0.064 = 5.952A
            //BAT_CHGCURR = 0x8015; //4.096+1.024+0.256+0.128 = 5.504A
            //BAT_CHGCURR = 0x8013; //4.096+0.512+0.256+0.128 = 4.992A //981004-221207-M 			
		}	
	}
    else
    {
		 GAUGE_CURRENT_CNT6 = 0;
	}
	#if 0
    if ((GAUGE_CURRENT != 0) && (GAUGE_CURRENT != 256) && (GAUGE_CURRENT != 1275) && (GAUGE_CURRENT != 1913) && (GAUGE_CURRENT != 3188) && (GAUGE_CURRENT != 7650))
    {
		BAT_CHGCURR = 0x0001; //0.256A
	}
	#endif		
}

void SetBatCHGVoltage(void)
{
	if (GAUGE_VOLTAGE == 0)
    {
		GAUGE_VOLTAGE_CNT1++;
		if (GAUGE_VOLTAGE_CNT1 >= 3)
		{	
		    BAT_CHGVOL = 0;
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT1 = 0;
	}
    if (GAUGE_VOLTAGE == 15800)
    {
		GAUGE_VOLTAGE_CNT7++;
		if (GAUGE_VOLTAGE_CNT7 >= 3)
		{	
		    //BAT_CHGVOL = 0x402E; //8.192+2.048+1.024+0.512+0.064 = 12.840V (Target => 12.85V)
			BAT_CHGVOL = 0xB03D; //8.192+4.096+2.048+1.024+0.256+0.128+0.032+0.016 = 15.792V (Target => 15.8V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT7 = 0;
	}	
    if (GAUGE_VOLTAGE == 16000)
    {
		GAUGE_VOLTAGE_CNT8++;
		if (GAUGE_VOLTAGE_CNT8 >= 3)
		{	
		    //BAT_CHGVOL = 0xE02E; //8.192+2.048+1.024+0.512++0.128+0.064+0.032 = 12.0000V (Target => 12V)
			BAT_CHGVOL = 0x803E; //8.192+4.096+2.048+1.024+0.512+0.128 = 16V (Target => 16V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT8 = 0;
	}	
    if (GAUGE_VOLTAGE == 16200)
    {
		GAUGE_VOLTAGE_CNT9++;
		if (GAUGE_VOLTAGE_CNT9 >= 3)
		{	
		    //BAT_CHGVOL = 0x702F; //8.192+2.048+1.024+0.512++0.256+0.064+0.032+0.016 = 12.144V (Target => 12.15V)
			BAT_CHGVOL = 0x403F; //8.192+4.096+2.048+1.024+0.512+0.256+0.064 = 16.192V (Target => 16.2V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT9 = 0;
	}		
	if (GAUGE_VOLTAGE == 16400)
    {
		GAUGE_VOLTAGE_CNT2++;
		if (GAUGE_VOLTAGE_CNT2 >= 3)
		{	
		    //BAT_CHGVOL = 0x1030; // 8.192+4.096+0.016 = 12.304V (Target => 12.3V)
			BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT2 = 0;
	}	
	if (GAUGE_VOLTAGE == 17320)
    {
		GAUGE_VOLTAGE_CNT3++;
		if (GAUGE_VOLTAGE_CNT3 >= 3)
		{	
		    //BAT_CHGVOL = 0x6032; // 8.192+4.096+0.512+0.064+0.032 = 12.896V (Target => 12.9V)
			BAT_CHGVOL = 0xA043; // 16.384+0.512+0.256+0.128+0.032 = 17.312V (Target => 17.32V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT3 = 0;
	}
	if (GAUGE_VOLTAGE == 17520)
    {
		GAUGE_VOLTAGE_CNT4++;
		if (GAUGE_VOLTAGE_CNT4 >= 3)
		{	
		    //BAT_CHGVOL = 0x0033; // 8.192+4.096+0.512+0.256 = 13.056V (Target => 13.05V)
			BAT_CHGVOL = 0x7044; // 16.384+1.024+0.064+0.032+0.016 = 17.52V (Target => 17.52V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT4 = 0;
	}
	if (GAUGE_VOLTAGE == 17720)
    {
		GAUGE_VOLTAGE_CNT5++;
		if (GAUGE_VOLTAGE_CNT5 >= 3)
		{	
		    //BAT_CHGVOL = 0x9033; // 8.192+4.096+0.512+0.256 +0.128+0.016 = 13.2V (Target => 13.2V)
			BAT_CHGVOL = 0x3045; // 16.384+1.024+0.256+0.032+0.016 = 17.712V (Target => 17.72V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT5 = 0;
	}
	if (GAUGE_VOLTAGE == 17920)
    {
		GAUGE_VOLTAGE_CNT6++;
		if (GAUGE_VOLTAGE_CNT6 >= 3)
		{	
		    //BAT_CHGVOL = 0x2034; // 8.192+4.096+1.024+0.032 = 13.344V (Target => 13.5V)
			BAT_CHGVOL = 0x0046; // 16.384+1.024+0.512 = 17.92V (Target => 17.92V)
		}	
	}
    else
    {
		GAUGE_VOLTAGE_CNT6 = 0;
	}
	#if 0
	if ((GAUGE_VOLTAGE != 0) && (GAUGE_VOLTAGE != 15800) && (GAUGE_VOLTAGE != 16000) && (GAUGE_VOLTAGE != 16200) && (GAUGE_VOLTAGE != 16400) && (GAUGE_VOLTAGE != 17320) && (GAUGE_VOLTAGE != 17520) && (GAUGE_VOLTAGE != 17720) && (GAUGE_VOLTAGE != 17920))
    {
	    BAT_CHGVOL = 0x1040; // 16.384+0.016 = 16.4V (Target => 16.4V)
    }
	#endif	
}
//981004-220510-A-E

//981004-221025-A-S
void NV_DB20_SUPPORT(void)
{
     if ((RMCAP_TEMP > BATCAP80))		 
     {       
        //WTDP = 20; //981004-221228-R
	    //WTDP2 = 20; //981004-221228-R
        WTDP4 = 90;	        		
        if (IS_BIT_CLR(EC_Flag4, nv_db20_lv0)) //EC RAM 388 bit0
		{
            BIT_SET(EC_Flag4, nv_db20_lv0); //EC RAM 388 bit0
            BIT_CLR(EC_Flag4, nv_db20_lv1); 
            BIT_CLR(EC_Flag4, nv_db20_lv2);
            BIT_CLR(EC_Flag4, nv_db20_lv3);
			BIT_CLR(EC_Flag4, nv_db20_lv4);
            //ECQEvent(SCI_DB20_0, SCIMode_ACPI_SMBus); //0x83
			QeventSend(SCI_DB20_0);			
		}
     }
	 else if ((RMCAP_TEMP > BATCAP60))	 	 
     {        
        //WTDP = 18; //981004-221228-R
	    //WTDP2 = 18; //981004-221228-R
        WTDP4 = 90;		 		
        if (IS_BIT_CLR(EC_Flag4, nv_db20_lv1)) //EC RAM 388 bit1
		{
            BIT_SET(EC_Flag4, nv_db20_lv1); //EC RAM 388 bit1
            BIT_CLR(EC_Flag4, nv_db20_lv0); 
            BIT_CLR(EC_Flag4, nv_db20_lv2);
            BIT_CLR(EC_Flag4, nv_db20_lv3);
			BIT_CLR(EC_Flag4, nv_db20_lv4);
           // ECQEvent(SCI_DB20_1, SCIMode_ACPI_SMBus); //0x84
			QeventSend(SCI_DB20_1);			
		}
     }
	 else if ((RMCAP_TEMP > BATCAP40))     	 
     {        
        //WTDP = 18; //981004-221228-R
	    //WTDP2 = 18; //981004-221228-R
        WTDP4 = 90;		 		
        if (IS_BIT_CLR(EC_Flag4, nv_db20_lv2)) //EC RAM 388 bit2
		{
            BIT_SET(EC_Flag4, nv_db20_lv2); //EC RAM 388 bit2
            BIT_CLR(EC_Flag4, nv_db20_lv0); 
            BIT_CLR(EC_Flag4, nv_db20_lv1);
            BIT_CLR(EC_Flag4, nv_db20_lv3);
			BIT_CLR(EC_Flag4, nv_db20_lv4);
            //ECQEvent(SCI_DB20_2, SCIMode_ACPI_SMBus); //0x85
			QeventSend(SCI_DB20_2);			
		}
     }
     else if ((RMCAP_TEMP > BATCAP20))     	 
     {        
        //WTDP = 15; //981004-221228-R
	    //WTDP2 = 15; //981004-221228-R
        WTDP4 = 90;		 		
        if (IS_BIT_CLR(EC_Flag4, nv_db20_lv3)) //EC RAM 388 bit3
		{
            BIT_SET(EC_Flag4, nv_db20_lv3); //EC RAM 388 bit3
            BIT_CLR(EC_Flag4, nv_db20_lv0); 
            BIT_CLR(EC_Flag4, nv_db20_lv1);
            BIT_CLR(EC_Flag4, nv_db20_lv2);
			BIT_CLR(EC_Flag4, nv_db20_lv4);
            //ECQEvent(SCI_DB20_3, SCIMode_ACPI_SMBus); //0x86
			QeventSend(SCI_DB20_3);
		}
     }		 
	 else  
     {		        
        //WTDP = 15; //981004-221228-R
	    //WTDP2 = 15; //981004-221228-R
        WTDP4 = 90;       		
        if (IS_BIT_CLR(EC_Flag4, nv_db20_lv4)) //EC RAM 388 bit4
		{
            BIT_SET(EC_Flag4, nv_db20_lv4); //EC RAM 388 bit4
            BIT_CLR(EC_Flag4, nv_db20_lv0); 
            BIT_CLR(EC_Flag4, nv_db20_lv1);
            BIT_CLR(EC_Flag4, nv_db20_lv2);
			BIT_CLR(EC_Flag4, nv_db20_lv3);
            //ECQEvent(SCI_DB20_4, SCIMode_ACPI_SMBus); //0x87
			QeventSend(SCI_DB20_4);			
		}
     }	 
}
//981004-221025-A-E

//981004-230510-A-S
void FCC_PERCENTAGE(void)
{
	//LFCCAP_TEMP = (uint16_t)(BAT_LFCCAP<<8)|(BAT_LFCCAP>>8);
	LFCCAP_TEMP = BAT_LFCCAP;
    DSNCAPLW_TEMP = LFCCAP_TEMP>>5;
    //BAT_DSNCAPLW = (uint16_t)(DSNCAPLW_TEMP<<8)|(DSNCAPLW_TEMP>>8); 
	BAT_DSNCAPLW = DSNCAPLW_TEMP;
    BATCAP90 = (uint16_t)(LFCCAP_TEMP*0.9);
	BATCAP99 = (uint16_t)LFCCAP_TEMP*0.985; //981004-231218-A
    BATCAP98 = (uint16_t)(LFCCAP_TEMP*0.975);
	BATCAP97 = (uint16_t)(LFCCAP_TEMP*0.965);
    BATCAP10 = (uint16_t)(LFCCAP_TEMP - BATCAP90);
    BATCAP95 = (uint16_t)(LFCCAP_TEMP - (BATCAP10>>1));
    //BATCAP15 = BATCAP10 + (BATCAP10>>1); //981004-221004-R
	BATCAP20 = (uint16_t)(LFCCAP_TEMP* 0.2); 
	BATCAP25 = (uint16_t)(LFCCAP_TEMP* 0.25); //981004-221004-A
	BATCAP30 = (uint16_t)(LFCCAP_TEMP* 0.3);
    BATCAP35 = (uint16_t)(LFCCAP_TEMP* 0.35); //981004-230614-A	
	BATCAP40 = (uint16_t)(LFCCAP_TEMP* 0.4); 
    BATCAP50 = (uint16_t)(LFCCAP_TEMP* 0.5);
    //BATCAP55 = LFCCAP_TEMP* 0.55; //981004-221007-A	
    BATCAP60 = (uint16_t)(LFCCAP_TEMP - BATCAP40);//981004-221025-A 
    BATCAP80 = (uint16_t)(LFCCAP_TEMP - BATCAP20); 
	BATCAP70 = (uint16_t)(LFCCAP_TEMP - BATCAP30); //981004-230413-A
    BATCAP75 = (uint16_t)(LFCCAP_TEMP - BATCAP25); //981004-230413-A
		
    	
}
//981004-230510-A-E	

#endif