#include "RTK_Include.h"

/******************************************************************************/
/** Service ACPI command
 * input: service bit
*******************************************************************************/
void HOOK_64PORT(void)
{
	//RAM_debug(0x64);
	//RAM_debug(KbcCmd);

	 switch(KbcCmd)
    {
		case 0xB0:
        KBC_B0CMD();
        break;
		case 0xB1:
        KBC_B1CMD();
        break;
        default:
        break;
    }
}

//-----------------------------------------------------------------------
// Handle command 80 - 
//----------------------------------------------------------------------- 
void KBC_80CMD(void)
{
	//SetHandleCmdData(1);
	KbcDLen = 1;
}

//-----------------------------------------------------------------------
// Handle command 81 - 
//-----------------------------------------------------------------------
void KBC_81CMD(void)
{
	//SetHandleCmdData(2);
	KbcDLen = 2;
}

//-----------------------------------------------------------------------
// Handle command 91 - 
//-----------------------------------------------------------------------
void KBC_91CMD(void)
{
	//EC_AMP_MUTE_L = 0; 	
}

//-----------------------------------------------------------------------
// Handle command 92 - 
//-----------------------------------------------------------------------
void KBC_92CMD(void)
{
	//EC_AMP_MUTE_L = 1; 	
}

//-----------------------------------------------------------------------
// Handle command 94 - 
//-----------------------------------------------------------------------
void KBC_94CMD(void)
{
   // RamProgram(0x64);	// For AMI BISO flash utility
}


void KBC_B0CMD(void)
{
	BIT_SET(POWER_FLAG2, sci_on);
	
	if (IS_BIT_CLR(POWER_FLAG5, Linux_fanon)) //205 BIT6
	{           
	     BIT_CLR(POWER_FLAG6, adjustfan);
	}
	Kbcwritedata(0xFA);
	
	      //981004-140505-M-S
    if (IS_BIT_SET(BAT_STATUS, BAT_IN))
    {	
        ConfigBatIn(); 
        if(IS_BIT_CLR(POWER_FLAG13, fixBattery))	//981004-150525-A Fix Battery no charge when shipmode wakeup.60.8w "Model : GAG-K40"		
             ConfigCharger(); //981004-150212-A
//        ECQEvent(SCI_BATIN, SCIMode_ACPI_SMBus); //For sometime unable to detect battery under OS 
		QeventSend(SCI_BATIN);
        //bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_CycleCount, &BAT_CYCLECNT, SMBus_NoPEC);	//981004-141230-A for reading cycle count
	    SMBUS_RW_W(0,ReadWord,SmartBat_Addr,BATCmd_CycleCount,&BAT_CYCLECNT);
        //BAT_INCURR = 0x0016; //4.096+1.024+0.512 = 5.632A (5.632*2 = 11.264A) (226 Watt)
        //BAT_INCURR = 0x0013; //4.096+0.512+0.256 = 4.864A (4.864*4 = 19.456A) (2.5 Ohm , 4*) //981004-170224-M
        //BAT_INCURR = 0x0016; //4.096+1.024+0.512 = 5.632A (5.632*2 = 11.264A) (226 Watt)
        //BAT_INCURR = 0x8016; //4.096+1.024+0.512+0.128 = 5.76A (5.76*2 = 11.52A) //981004-180301-M from 0x0016
        //if (IS_MASK_CLEAR(POWER_FLAG11, pd_ac_over65w)) //EC RAM 0x211 bit4
		ConfigACLIMIT(); //981004-230707-A
		#if 0
		if (!AC_IN_L())//if (!AC_IN_L)
	    {           
			//BAT_INCURR = 0x0018; //4.096+2.048 = 6.144A (6.144*2 = 12.288A) //232.8Watt //981004-201027-M from 0x0018
		    BAT_INCURR = 0x0017; //4.096+1.024+0.512+0.128 = 5.76A (5.76*2 = 11.52A) //981004-210322-M
			//BAT_INCURR = 0x8016; //4.096+1.024+0.512+0.128 = 5.76A (5.76*2 = 11.52A) //981004-210322-M
        }
        else
        {
           //if (!PD_ADAPTER_IN)   /* PD adapter */
           //{
		     //BAT_INCURR = 0x8006; //1.024+0.512+0.128 = 1.664A (1.664*2 = 3.328A) //60 Watt
               BAT_INCURR = 0x0008; //2.048 = 2.048A (2.048*2 = 4.096A) //80 Watt //981004-210322-M			 
	       //}
        }
		#endif
        //BAT_INCURR = 0x8019; //4.096+2.048+0.256 +0.128 = 6.528A (6.528*2 = 13.056A) //981004-190318-M from 0x0019		
    //981004-1607046-R-E
	}	
       //981004-140505-M-E

   	//SET_MASK(POWER_FLAG3, ps2_on); //981004-220706-R         
    //EC_AMP_MUTE_L = 1; //981004-131220-A from 1 //MUTE	
	//EC_AMP_MUTE_HIGH;//GPIO_Write(18,1);
	EC_AMP_MUTE_L = 0;//EC_AMP_MUTE_LOW;
	
	//981004-180731-R-S
	#if 0
    if (IS_MASK_SET(POWER_FLAG1, bt_on)) //981004-180731-R        
        BT_LED = 1;
	
	if (IS_MASK_SET(POWER_FLAG2, wlan_on)) //981004-180731-R
        WLAN_LED = 1; //981004-130910-A	
    #endif
    //981004-180731-R-E		
    
	//CLEAR_MASK(POWER_FLAG3, q2l_on);  
 	//CLEAR_MASK(POWER_FLAG3, img_on); //981004-220706-R
	
	//981004-231017-R-S
	#if 0		
	BIT_CLR(POWER_FLAG8, f2_press); 
    BIT_CLR(POWER_FLAG8, f9_press); 
	BIT_CLR(POWER_FLAG8, f12_press); 
	BIT_CLR(POWER_FLAG8, f10_press);
    #endif
    //981004-231017-R-E 
	 	   	
    //CLEAR_MASK(POWER_FLAG10, win_key_disable); //981004-200724-R for windows key default is on 
    //Scanner_Table_Pntr = &Rc_ROM_Tables; //981004-200724-R for windows key default is on //IS_MASK_SET(POWER_FLAG8, win_key_disable) ? (&Rc_ROM_Tables1) : (&Rc_ROM_Tables); -130614-A for smartmanager to disable windows key
    //GPIO_D4_CTRL = INPUT; //To prevent S3 resuming then BT loss //981004-120911-A (SMI)
	//GPCRD4 = INPUT;
	//GPIO_Set_IO(13,0);
   //981004-131030-A-S always pstate when discharging
     if ((IS_MASK_SET(POWER_FLAG1, adapter_in)) || (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w)) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2)))
	{
        BIT_CLR(POWER_FLAG4, bat30_on);
	}	
    //else //981004-140505-R
        //SET_MASK(POWER_FLAG4, bat30_on);  //always pstate when discharging
    
    //ECQEvent(SCI_BAT30ON, SCIMode_ACPI_SMBus); //981004-131111-R
    AmpHigh_flag = 0x00;  //981004-140505-A patch for Max request
    AmpHighcnt = 0x00; //981004-140505-A patch for Max request
    //AmpHighRecovercnt = 0x0000; //981004-180717-R
	//CLEAR_MASK(POWER_FLAG3, bat_temp_65); //EC RAM 0x203 BIT 6 //981004-140904-R
	
//	BAT_CAP_for_Devent = 0x00; //992022-140904-A
//    Runtime_BAT_CAP_for_Devent_flag = 0x00; //992022-140904-A
    BIT_SET(POWER_FLAG10, sci_on_20sec); //992022-140904-A
    Sci_on_20sec_cnt = 0; //981004-210325-A
    BIT_SET(ProcsH, ProcsH_scion20sec); 
	ProcsH_scion_cnt = 0; //981004-210325-A
	if (IS_BIT_CLR(POWER_FLAG4, resume_from_s3)) //981004-140513-A
    {
        BIT_CLR(ProcsH, ProcsH_acout);
	}	   
    BIT_CLR(POWER_FLAG7, dgpu_9Aon); //981004-140505-A 
    BIT_CLR(POWER_FLAG4, pstate_off); //981004-140505-A    
    //DCR5 = 0x00; //981004-131111-A //981004-140505-R
	//H_PROCHOT_L = AC_IN_L ? 0 : 1; //981004-140505-A //Enable Processor hot

	//if (AC_IN_L) //battery mode //981004-131202-M for power saving mode
	//if ((AC_IN_L) && (PD_ADAPTER_IN)) //battery mode
	//if ((AC_IN_L()) &&(IS_BIT_CLR(POWER_FLAG11, pd_ac_over65w))) //EC RAM 0x211 bit4  
	if (!AC_IN_L)
	{	   
	  //H_PROCHOT_LOW; //Normal 
	   H_PROCHOT_L = 0; 
	  //dGPU_HOLD_EC_RST_HIGH();
	  dGPU_HOLD_EC_RST_L =1;
	  WTDP4 = 246;

	}
	else
	{	  
      if ((PD_ADAPTER_IN) && (PD_ADAPTER_IN2)) //981004-221005-M
        {
		    if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(POWER_FLAG4, pstate_off)) && (IS_BIT_CLR(AmpHigh_flag, AmpHigh)) )
			{	
		        //H_PROCHOT_HIGH; 
				H_PROCHOT_L = 1; //Normal
			}
            else
			{
				//H_PROCHOT_LOW; 
				H_PROCHOT_L = 0; //dCPU
			}	           				
		    //dGPU_HOLD_EC_RST_HIGH();
			dGPU_HOLD_EC_RST_L = 1; //dGPU
            //if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-R
            //{
                WTDP4 = 40;
            //}		   
        }
        else
		{
			if (IS_MASK_SET(POWER_FLAG11, pd_ac_over65w) || (IS_MASK_SET(POWER_FLAG8, pd_ac_over65w2))) //EC RAM 0x211 bit4
	        {
				//H_PROCHOT_LOW; 
				H_PROCHOT_L = 0; //Normal
				//dGPU_HOLD_EC_RST_HIGH(); 
				dGPU_HOLD_EC_RST_L = 1; //Normal
				WTDP4 = 45;
	        }
			else
			{
				if ((IS_BIT_CLR(POWER_FLAG10, gtx970_bat_low)) && (IS_BIT_CLR(POWER_FLAG4, pstate_off)) && (IS_BIT_CLR(AmpHigh_flag, AmpHigh)) )
			    {	
		            //H_PROCHOT_HIGH; 
					H_PROCHOT_L = 1; //Normal
			    }
                else
			    {
				    //H_PROCHOT_LOW; 
					H_PROCHOT_L = 0; //dCPU
			    }	           				
				//dGPU_HOLD_EC_RST_HIGH(); 
				dGPU_HOLD_EC_RST_L = 1; //dGPU
				//if (IS_MASK_CLEAR(POWER_FLAG7, PPAB_ON)) //EC RAM 0x207 bit2 //981004-221228-R
                //{
                    WTDP4 = 40;
                //}					
			}	
		}		
		//WTDP4 = 40;
	  
	}
	BIT_CLR(POWER_FLAG4, resume_from_s3);
    BIT_CLR(POWER_FLAG4, resume_from_s4);	  
	
	
	    
	AC_boost_Status = 0; //981004-151001-A
	AC_boost_cnt1 = 0; //981004-151001-A
	AC_boost_cnt2 = 0; //981004-151001-A
	BIT_CLR(POWER_FLAG4, bat_cap_first_chk); //981004-170412-A
	BIT_CLR(POWER_FLAG4, bat_cap_downgrade); //981004-170412-A
    BAT_FIRST_CHK_cnt = 0; //981004-170412-A
    BAT_DOWNGRADE_cnt = 0; //981004-170412-A 
	
	BIT_CLR(POWER_FLAG3, adapter_overtemp); //981004-210325-A
	
    //981004-181030-R-S
	#if 0
	bRWSMBus(SMbusCh1, SMbusRW, SmartBat_Addr, BATCmd_FCcap, &BAT_LFCCAP, SMBus_NoPEC);
	BAT_LFCCAP2 = (BAT_LFCCAP<<8)|(BAT_LFCCAP>>8);
	if (IS_MASK_SET(EC_Flag4, old_99w)) //981004-230510-A
	{
      if (BAT_LFCCAP2 < 3257) //6514 * 0.5 = 3257
	  {
	     ECQEvent(SCI_BAT_AGING2, SCIMode_ACPI_SMBus); //0x95
	  }	
	  else if (BAT_LFCCAP2 < 4886) //6514 * 0.75 = 4886
  	  {
	     ECQEvent(SCI_BAT_AGING1, SCIMode_ACPI_SMBus); //0x94
      }
	  BAT_LFCCAP = 0x7219;
	}
	else
	{  
	  if (BAT_LFCCAP2 < 3820) //7640 * 0.5 = 3820
  	  {
	     ECQEvent(SCI_BAT_AGING2, SCIMode_ACPI_SMBus); //0x95
	  }	
	  else if (BAT_LFCCAP2 < 5730) //7640 * 0.75 = 5730
 	  {
	     ECQEvent(SCI_BAT_AGING1, SCIMode_ACPI_SMBus); //0x94
  	  }	  
	}  
	 
	BAT_Aging_cnt = 0;
	#endif	
	//981004-181030-R-E	
}

//-----------------------------------------------------------------------
// Handle command B1 
//-----------------------------------------------------------------------
void KBC_B1CMD(void)
{
     //CLEAR_MASK(POWER_FLAG2, sci_on);
	BIT_CLR(POWER_FLAG2, sci_on);
    //ResponseKBData(0xFA); //981004-121003-R
}
//981004-130115-A-E

//-----------------------------------------------------------------------
// Handle command B4 - Phoenix flash command for SPI rom
//-----------------------------------------------------------------------
void KBC_B4CMD(void)
{
    //RamProgram(0x64);
}

//-----------------------------------------------------------------------
// Handle command D8 - 
//-----------------------------------------------------------------------
void KBC_D8CMD(void)
{
   // RamProgram(0x64);
}

//-----------------------------------------------------------------------
// Handle command D9 - 
//-----------------------------------------------------------------------
void KBC_D9CMD(void)
{
	//SetHandleCmdData(1);
	KbcDLen = 1;
}

//-----------------------------------------------------------------------
// Handle command DD - 
//-----------------------------------------------------------------------
void KBC_DDCMD(void)
{
   // RamProgram(0x64);
}


void HOOK_60PORT(void)
{
	//RAM_debug(0x60);
	//RAM_debug(KbcData);

	    switch(KbcCmd)
    {	
		case 0x80:
            KBC_80DATA();
            break;
		case 0x81:
            KBC_81DATA();
            break;		    
        case 0xB0:
            KBC_B0DATA();
            break;
		case 0xD9:
            KBC_D9DATA();
            break;
        default:
        break;
    }
}

//-----------------------------------------------------------------------
// Process command data 80 - 
//-----------------------------------------------------------------------
void KBC_80DATA(void)
{
	//Raymond20230801 need to modify Hook_ReadMapECSpace
	//ResponseKBData(Hook_ReadMapECSpace(KBHIData));
	//Kbcwritedata(Hook_ReadMapECSpace(KBHIData));
}

//-----------------------------------------------------------------------
// Process command data 81 - 
//-----------------------------------------------------------------------
void KBC_81DATA(void)
{
	//Raymond20230801 need to modify Hook_ReadMapECSpace
	#if 0
  	if (KBHIStep == 2)
	{
     	//KBHIData1=KBHIData;  	// address
		KBHIData1 = KBC_Read();
	}
	else
	{
		//Hook_WriteMapECSpace(KBHIData1,KBHIData);
		Hook_WriteMapECSpace(KBHIData1,KBC_Read());
 	}
	#endif
}

//-----------------------------------------------------------------------
// Process command data D9 - 
//-----------------------------------------------------------------------
#if 0
void SendVerFunction(BYTE code* cpntr)
{
    BYTE index;
    index = 0x00;
    
    while(1)
    {
        if(*cpntr=='$')
        {
            Data_To_Host(*cpntr);
            break;
        }
        else
        {
            Data_To_Host_nWait(*cpntr);
        }
        cpntr++;

        index++;
        if(index>32)
        {
            break;
        }
    }
}
#endif
void KBC_D9DATA(void)
{
//    BYTE index;
//    index=0x00;

//    switch(KBHIData)
//    {
//        case 1:         // 1: revision desciption
//            SendVerFunction(P_rev);   
//            break;
//            
//        case 2:         // 2: platform information
//            SendVerFunction(P_model);         
//            break;            
//    
//        case 3:         // 3: last updated date
//            SendVerFunction(P_date);                
//            break;

//        case 4:         // 4: internal revision
//            Data_To_Host_nWait(P_digit[0]);
//            Data_To_Host(P_digit[1]);
//            break;

//        default:
//            break;
//    }
}


void KBC_B0DATA(void)
{

}