/**
 * @file Oem_fan.c
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "RTK_Include.h"

//-----------------------------------------------------------------------------
// Smart Fan control
//-----------------------------------------------------------------------------

//981004-190314-M-S X6EVG 2nd generation fan customize
#if 1 //X6EVG
const thermal code tFanDefault2[] = 
{//level  fan-on  fan-off  DACValue
    {0,        00,      0,      0x39},    // Level 0      25% 
    {1,        50,      47,     0x44},    // Level 1      30% 
    {2,        53,      50,     0x50},    // Level 2      35% 
    {3,        56,      53,     0x5B},    // Level 3      40% 
    {4,        59,      56,     0x67},    // Level 4      45% 
    {5,        62,      59,     0x72},    // Level 5      50% 
    {6,        65,      62,     0x7D},    // Level 6      55% 
    {7,        68,      65,     0x89},    // Level 7      60% 
    {8,        71,      68,     0x94},    // Level 8      65% 
  	{9,        74,      71,     0xA0},    // Level 9      70% 
    {10,       77,      74,     0xAB},    // Level 8      75%
    {11,       80,      77,     0xB7},    // Level 7      80% 
    {12,       83,      80,     0xC2},    // Level 8      85% 
  	{13,       86,      83,     0xCE},    // Level 9      90% 
    {14,       89,      86,     0xE5},    // Level 8      100% 
    {15,     0xFE,    0xFE,     0xE5}    // dummy level
};
#endif

const thermal code FanCustomize[] =
{//level  fan-on  fan-off  DACValue
    {0,        00,      0,      0x39},    // Level 0      25% 
    {1,        50,      47,     0x44},    // Level 1      30% 
    {2,        53,      50,     0x50},    // Level 2      35% 
    {3,        56,      53,     0x5B},    // Level 3      40% 
    {4,        59,      56,     0x67},    // Level 4      45% 
    {5,        62,      59,     0x72},    // Level 5      50% 
    {6,        65,      62,     0x7D},    // Level 6      55% 
    {7,        68,      65,     0x89},    // Level 7      60% 
    {8,        71,      68,     0x94},    // Level 8      65% 
  	{9,        74,      71,     0xA0},    // Level 9      70% 
    {10,       77,      74,     0xAB},    // Level 8      75%
    {11,       80,      77,     0xB7},    // Level 7      80% 
    {12,       83,      80,     0xC2},    // Level 8      85% 
  	{13,       86,      83,     0xCE},    // Level 9      90% 
    {14,       89,      86,     0xE5},    // Level 8      100% 
    {15,     0xFE,    0xFE,     0xE5}     // dummy level
};

//981004-231218-M-S 
#if 1
//AutoFan1 - Auto Low (Normal) X6EVG CPU/GPU Normal mode 
const thermal code FanLevel4[] =
{//level  fan-on  fan-off  DACValue
    {0,        00,      0,      0x00},    // Level 0      25% 
    {1,        55,      49,     0x39},    // Level 1      27% 
    {2,        57,      51,     0x44},    // Level 2      29%  
    {3,        59,      53,     0x4B},    // Level 3      31% 
    {4,        61,      56,     0x52},    // Level 4      33%     
    {5,        63,      58,     0x62},    // Level 6      37% 
    {6,        65,      60,     0x6B},    // Level 7      40% 
    {7,        68,      63,     0x7D},    // Level 8      44% 
	{8,        71,      66,     0x8D},    // Level 9      48% 
    {9,        82,      68,     0xA0},    // Level 10     56% 
    {10,       94,      86,     0xDB},    // Level 11     78% 
    {11,       97,      87,     0xE5},    // Level 12     100% 	
    {12,      0xFE,    0xFE,    0xE5}    // dummy level
};
#endif


//981004-211216-M-S
#if 1
//AutoFan2 - CPU FAN + GPU FAN (Gaming mode)
const thermal code FanLevel5[] = 
{//level     fan-on  fan-off   DACValue 
    {0,        00,      0,      0x39},    // Level 0      25% 
    {1,        50,      47,     0x40},    // Level 1      27% 
    {2,        52,      48,     0x46},    // Level 2      29% 
    {3,        54,      50,     0x4B},    // Level 3      31% 
    {4,        56,      52,     0x52},    // Level 4      33% 
    {5,        58,      54,     0x59},    // Level 5      35% 
    {6,        60,      56,     0x62},    // Level 6      37% 
    {7,        62,      58,     0x6B},    // Level 7      40% 
    {8,        64,      60,     0x79},    // Level 8      44% 
	{9,        67,      62,     0x89},    // Level 9      48% 
    {10,       70,      65,     0x94},    // Level 10     52%
    {11,       74,      68,     0xA0},    // Level 11     56% 
    {12,       81,      72,     0xB7},    // Level 12     60% 
    {13,       85,      76,     0xC7},    // Level 13     64% 
    {14,       94,      86,     0xDB},    // Level 14     78% 
    {15,       97,      87,     0xE5},    // Level 15     100% 	
    {16,      0xFE,   0xFE,     0xE5}     // dummy level
};
#endif


const thermal code FanLevel3[] =  //Smart cooling table (Quiet mode)
{//level  fan-on  fan-off  DACValue
    {0,     00,      0,      0x00},    // Level 0 
    {1,	    58,      55,     0x39},    // Level 1 25%
    {2,	    61,      58,     0x44},    // Level 2 28%
    {3,	    65,      61,     0x4B},    // Level 3 31%
    {4,	    70,      65,     0x59},    // Level 4 36%
	{5,	    75,      72,     0x67},    // Level 5 41% 
	{6,	    87,      84,     0x7D},    // Level 6 48% 
	{7,	    97,      87,     0xE5},    // Level 7 100% 
	{8,    0xFE,   0xFE,     0xE5}     // dummy level
};
//981004-231218-M-E
//981004-190731-A-S
const thermal code FanLevel6[] =  //(Super Quiet mode)
{//level  fan-on   fan-off  DACValue
    {0,     00,       0,      0x00},    // Level 0 
    {1,	    58,      55,      0x39},    // Level 1 25%
    {2,	    65,      62,      0x40},    // Level 2 28%
    {3,	    75,      72,      0x46},    // Level 3 31%
    {4,	    80,      77,      0x52},    // Level 4 36%
	{5,    0xFE,   0xFE,      0xE5}     // dummy level
};

//981004-201105-A-S
//AutoFan1 - Auto Low (Normal) X6EVG CPU Whisper mode V0.2
const thermal code FanLevel7[] =
{//level  fan-on  fan-off  DACValue
    {0,        00,      0,      0x00},    // Level 0      00%
    {1,        00,      0,      0x00},    // Level 1      00%
    {2,        00,      0,      0x00},    // Level 2      00%
	{3,        45,      42,     0x39},    // Level 0      25%
    {4,        00,      0,      0x3B},    // Level 1      27%
    {5,        00,      0,      0x40},    // Level 2      28%
    {6,        58,      55,     0x42},    // Level 3      29%
    {7,        00,      0,      0x46},    // Level 4      31%
    {8,        00,      0,      0x49},    // Level 5      33%
    {9,        66,      63,     0x4B},    // Level 6      35%
    {10,       00,      0,      0x4D},    // Level 7      37%
    {11,       00,      0,      0x52},    // Level 8      38%   		
    {12,       74,      71,     0x54},    // Level 9      40%
    {13,       00,      0,      0x59},    // Level 10     42%
    {14,       00,      0,      0x5D},    // Level 11     45%  
    {15,       82,      79,     0x64},    // Level 12     48%
	{16,       00,      0,      0x67},    // Level 13     51%
    {17,       00,      0,      0x69},    // Level 14     53%    	    
    {18,       87,      84,     0x6D},    // Level 15     56%
    {19,       00,      0,      0x6D},    // Level 16    100% //981004-201112-M from 0xE5
    {20,       00,      0,      0x6D},    // Level 17    100% //981004-201112-M from 0xE5   	    
    {21,      0xFE,   0xFE,     0xE5}     // dummy level
};

//AutoFan1 - Auto Low (Normal) X6EVG GPU Normal mode V1.0
const thermal code FanLevel8[] =
{//level  fan-on  fan-off  DACValue
    {0,        00,      0,      0x00},    // Level 0      00%
    {1,        00,      0,      0x00},    // Level 1      00%
    {2,        00,      0,      0x00},    // Level 2      00%
	{3,        45,      42,     0x39},    // Level 0      25%
    {4,        00,      0,      0x3B},    // Level 1      27%
    {5,        00,      0,      0x40},    // Level 2      28%
    {6,        58,      55,     0x42},    // Level 3      29%
    {7,        00,      0,      0x46},    // Level 4      31%
    {8,        00,      0,      0x49},    // Level 5      33%
    {9,        65,      62,     0x4B},    // Level 6      35%
    {10,       00,      0,      0x4D},    // Level 7      37%
    {11,       00,      0,      0x52},    // Level 8      38%   		
    {12,       71,      68,     0x54},    // Level 9      40%
    {13,       00,      0,      0x59},    // Level 10     42%
    {14,       00,      0,      0x5D},    // Level 11     45%  
    {15,       77,      74,     0x64},    // Level 12     48%
	{16,       00,      0,      0x67},    // Level 13     51%
    {17,       00,      0,      0x69},    // Level 14     53%    	    
    {18,       82,      79,     0x6D},    // Level 15     56%
    {19,       00,      0,      0x6D},    // Level 16    100% //981004-201112-M from 0xE5
    {20,       00,      0,      0x6D},    // Level 17    100% //981004-201112-M from 0xE5   	    
    {21,      0xFE,   0xFE,     0xE5}     // dummy level
};
//981004-201105-A-E

//981004-190314-M-E	2019 fan speed rule							

BYTE duty_to_level(BYTE duty,bit type)
{
       if(type == 1)
	   {
		if(duty <=0x3A)return 0;// 25% //981004-190326-A   
	    if(duty <=0x45)return 1;// 30%
        if(duty <=0x51)return 2;// 35%		
	    if(duty <=0x5C)return 3;// 40%
	    if(duty <=0x68)return 4;// 45%	
	    if(duty <=0x73)return 5;// 50%
	    if(duty <=0x7E)return 6;// 55%
	    if(duty <=0x8A)return 7;// 60%
	    if(duty <=0x95)return 8;// 65%
	    if(duty <=0xA1)return 9;// 70%
		if(duty <=0xAC)return 10;// 75%
		if(duty <=0xB8)return 11;// 80%
		if(duty <=0xC3)return 12;// 85%
		if(duty <=0xCF)return 13;// 90%
		if(duty <=0xE5)return 14;// 100% //981004-190326-M from 0xD9
	    //if(duty <=0xE5)return 14;// 100% //981004-190326-R
	  }	   	    
}

void vFanControl2(void) //X5X7+X5Y7 Normal mode differnece
{    

    BYTE CustomMaxLevel_low; //981004-150414-A
	
    FanLevelTemp = FanDACLevel;		
	    
    //981004-150414-A-S		
	if(IS_MASK_SET(POWER_FLAG13, adjustfan2))//140587-150311--new adjustfan2,20d,bit0,-A-S
			CustomMaxLevel_low = duty_to_level(FanRPM2,1);
	else
		    CustomMaxLevel_low  = 0;//140587-150311--new adjustfan2,20d,bit0,-A-E
    //981004-151022-M-S	  
	
	
    if (IS_MASK_SET(POWER_FLAG6, GPU_on)) //0x206 bit 6
    {	    
	    //if (PECI_CPU_temp <= 10)
		if ((PECI_CPU_temp <= 10) || (PECI_CPU_temp & 0x80)) //981004-151109-M
		{
		    PECI_CPU_temp = 10;
		}
		#if 1
		//if (GPU_TMPR <= 5)
		if ((GPU_TMPR <= 5) || (GPU_TMPR & 0x80)) 
		{
		    GPU_TMPR = 5;
		}
		#endif		
		
		FINAL_TEMP1 = ((PECI_CPU_temp) >= GPU_TMPR) ? PECI_CPU_temp : GPU_TMPR;
        //981004-171130-M-E 		
    }
    else
    {
        GPU_TMPR = 0; //992022-141006-A
		//GPU_TMPR2 = 0; //981004-180712-R
		//if (PECI_CPU_temp <= 10)
		if ((PECI_CPU_temp <= 10) || (PECI_CPU_temp & 0x80)) //981004-151109-M
		{
		    PECI_CPU_temp = 10;
		}				
		FINAL_TEMP1 = PECI_CPU_temp;    
    }
	
	//981004-180712-R-S
	#if 0
	if ((GPU_TMPR2 <= 5) || (GPU_TMPR2 & 0x80)) 
	{
		GPU_TMPR2 = 5;
    }
	#endif
	//981004-180712-R-E

    //981004-190314-R-S
    #if 0	
    if ( (PECI_CPU_temp >= 90) && (GPU_TMPR >= 86))
    {
	   FAN_TEMPUP_cnt++;
	   if (FAN_TEMPUP_cnt >=3)
	   {
	       FAN_TEMPUP_cnt = 0; 
           SET_MASK(POWER_FLAG13, adjustfan4);
	   }	   
    }
	else
	{
	   FAN_TEMPUP_cnt = 0;
	}
    if ( (PECI_CPU_temp <= 87) && (GPU_TMPR <= 83))
    {
	   FAN_TEMPDN_cnt++;
	   if (FAN_TEMPDN_cnt >=3)
	   {
	      FAN_TEMPDN_cnt = 0;
          CLEAR_MASK(POWER_FLAG13, adjustfan4);
	   }	  
    }	
    else
	{
	   FAN_TEMPDN_cnt = 0;
	}
	//981004-190314-R-E
	#endif
	
	FINAL_TEMP2 = (FINAL_TEMP1 >= GPU_TMPR) ? FINAL_TEMP1 : GPU_TMPR; 
	
	
	//981004-201105-M-S
	if (IS_MASK_SET(POWER_FLAG6, Whisper_mode)) //EC RAM 206 bit 2
	{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	   //CPU DCR0 fan table	up to Final temp2	
	   if (FanLevelTemp >= 18) //981004-200326-M from 10
       {
           FanLevelTemp = 18;
       }
	   if ((IS_MASK_CLEAR(EC_Flag2, fan_lvup_no)) && (IS_MASK_CLEAR(EC_Flag2, fan_lvdn_no))) //386 BIT0/BIT1
			    {					
			     if (FINAL_TEMP2 >= FanLevel7[FanLevelTemp+3].FanOn) //981004-200326-M
			     {
			        FANLVDNCNT1++;
				    if (FANLVDNCNT1 >= 3) 
				    { 
				      FANLVDNCNT1 =0;
						//SET_MASK(POWER_FLAG5, fan_lvup); 
						SET_MASK(EC_Flag2, fan_lvup_no); //981004-200326-A
			            //FanLevelTemp++; //981004-200326-R
					    if (FanLevelTemp >= 18) //981004-200326-M from 10
                        {
                            FanLevelTemp = 18;
                        }
			        }                                                   		
			     }    
                 else
                 {
                   FANLVDNCNT1 =0;			  
                     //CLEAR_MASK(POWER_FLAG5, fan_lvup); 
					 CLEAR_MASK(EC_Flag2, fan_lvup_no); //981004-200326-A
			         FanUpCNT0 = 0; //981004-200326-A					 
                  }               			 
	           
                 if (FINAL_TEMP2 <= FanLevel7[FanLevelTemp].FanOff)
                 {
                   if (FanLevelTemp == 0x00)
                         ;
			       else
                   {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 5)
				     {
                         FANLVDNCNT =0;
						 SET_MASK(EC_Flag2, fan_lvdn_no); //981004-200326-A //386 bit 1
					     //FanLevelTemp--; //981004-200326-R
                     }				   
                   }              			     
                 }
                 else
                 {
                    FANLVDNCNT =0;				
                    //CLEAR_MASK(POWER_FLAG5, fan_lvdn); 
					CLEAR_MASK(EC_Flag2, fan_lvdn_no); //981004-200326-A
				    FanDnCNT0 = 0;							
                 }
			  }
              //981004-200326-M-E
			  
              if (FanLevelTemp != FanDACLevel)
              {
                  if (FanLevelTemp == 0x00)
                      CLEAR_MASK(POWER_FLAG2, fan_on);
                  else
		          { 
                      SET_MASK(POWER_FLAG2, fan_on);
			          ///ZTIER = 0x02;  
		          }
              }
			  
			  //981004-200326-A-S
			  if (IS_MASK_SET(EC_Flag2, fan_lvup_no))	
		      {
              	if (FanUpCNT0 < 3)
				{
                    FanUpCNT0++;
                    //if ((FanUpCNT0%2) != 0x00)					
	                DCR0 = FanLevel7[FanLevelTemp+FanUpCNT0].DACValue;								
				}
                else
                {
                    FanUpCNT0 = 0;					
				    FanLevelTemp = FanLevelTemp+3;
					CLEAR_MASK(EC_Flag2, fan_lvup_no);
                }
			  }
			  if (IS_MASK_SET(EC_Flag2, fan_lvdn_no))	
		      {
              	if (FanDnCNT0 < 3)
				{
                    FanDnCNT0++;
                    //if ((FanUpCNT0%2) != 0x00)					
	                DCR0 = FanLevel7[FanLevelTemp-FanDnCNT0].DACValue;								
				}
                else
                {
                    FanDnCNT0 = 0;					
				    FanLevelTemp = FanLevelTemp-3;
					CLEAR_MASK(EC_Flag2, fan_lvdn_no);
                }
			  }			
              //DCR3 = FanLevel4[FanLevelTemp].DACValue; //GPU fan Duty //981004-200326-R
              //981004-200326-M-E
			  
			  //981004-200408-A-S
			  if ((FanLevelTemp + FanUpCNT0) == 0x00)
			      DCR0 = 0x00;		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			    //GPU DCR3 fan table up to GPU temp
			    if (FanLevelTemp2 >= 18) //981004-200326-M from 10
                {
                    FanLevelTemp2 = 18;
                }
								
               //981004-200326-M-S Normal mode
			   if (IS_MASK_SET(POWER_FLAG6, GPU_on))
               {                 		   
                if ((IS_MASK_CLEAR(EC_Flag3, fan_lvup_no)) && (IS_MASK_CLEAR(EC_Flag3, fan_lvdn_no))) //387 BIT0/BIT1
			    {					
			      if (GPU_TMPR >= FanLevel8[FanLevelTemp2+3].FanOn) //981004-200326-M
			      {
			        FANLVDNCNT2++;
				    if (FANLVDNCNT2 >= 3) 
				    { 
				      FANLVDNCNT2 =0;
						//SET_MASK(POWER_FLAG5, fan_lvup); 
						SET_MASK(EC_Flag3, fan_lvup_no); //981004-200326-A
			            //FanLevelTemp++; //981004-200326-R
					    if (FanLevelTemp2 >= 18) //981004-200326-M from 10
                        {
                            FanLevelTemp2 = 18;
                        }
			        }                                                   		
			     }    
                 else
                 {
                   FANLVDNCNT2 =0;			  
                     //CLEAR_MASK(POWER_FLAG5, fan_lvup); 
					 CLEAR_MASK(EC_Flag3, fan_lvup_no); //981004-200326-A
			         FanUpCNT3 = 0; //981004-200326-A					 
                  }               			 
	           
                 if (GPU_TMPR <= FanLevel8[FanLevelTemp2].FanOff)
                 {
                   if (FanLevelTemp2 == 0x00)
                         ;
			       else
                   {
                     FANLVDNCNT3++;
				     if (FANLVDNCNT3 >= 5)
				     {
                         FANLVDNCNT3 =0;
						 SET_MASK(EC_Flag3, fan_lvdn_no); //981004-200326-A //386 bit 1
					     //FanLevelTemp--; //981004-200326-R
                     }				   
                   }              			     
                 }
                 else
                 {
                    FANLVDNCNT3 =0;				
                    //CLEAR_MASK(POWER_FLAG5, fan_lvdn); 
					CLEAR_MASK(EC_Flag3, fan_lvdn_no); //981004-200326-A
				    FanDnCNT3 = 0;							
                 }
			  }
              //981004-200326-M-E
			  
			  #if 0
              if (FanLevelTemp2 != FanDACLevel2)
              {
                  if (FanLevelTemp2 == 0x00)
                      CLEAR_MASK(POWER_FLAG2, fan_on);
                  else
		          { 
                      SET_MASK(POWER_FLAG2, fan_on);
			          ZTIER = 0x02;  
		          }
              }
			  #endif
			  
			  //981004-200326-A-S
			  if (IS_MASK_SET(EC_Flag3, fan_lvup_no))	
		      {
              	if (FanUpCNT3 < 3)
				{
                    FanUpCNT3++;
                    //if ((FanUpCNT0%2) != 0x00)					
	                DCR3 = FanLevel8[FanLevelTemp2+FanUpCNT3].DACValue;								
				}
                else
                {
                    FanUpCNT3 = 0;					
				    FanLevelTemp2 = FanLevelTemp2+3;
					CLEAR_MASK(EC_Flag3, fan_lvup_no);
                }
			  }
			  if (IS_MASK_SET(EC_Flag3, fan_lvdn_no))	
		      {
              	if (FanDnCNT3 < 3)
				{
                    FanDnCNT3++;
                    //if ((FanUpCNT0%2) != 0x00)					
	                DCR3 = FanLevel8[FanLevelTemp2-FanDnCNT3].DACValue;								
				}
                else
                {
                    FanDnCNT3 = 0;					
				    FanLevelTemp2 = FanLevelTemp2-3;
					CLEAR_MASK(EC_Flag3, fan_lvdn_no);
                }
			  }			              
              //981004-200326-M-E
			  
			  //981004-200408-A-S
			  if ((FanLevelTemp2 + FanUpCNT3) == 0x00)
			  {	  
			      DCR3 = 0x00;
			  }	  
              //981004-200408-A-E
		}			  
        else
	    {
           DCR3 = 0x00;
           FanLevelTemp2 = 0;               			   
        }	             			  
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	else
	{
      CLEAR_MASK(EC_Flag2, fan_lvup_no);
      CLEAR_MASK(EC_Flag2, fan_lvdn_no);
      CLEAR_MASK(EC_Flag3, fan_lvup_no);
      CLEAR_MASK(EC_Flag3, fan_lvdn_no);	  
	  FanUpCNT0 = 0;  
      FanDnCNT0 = 0;
      FanUpCNT3 = 0;  
      FanDnCNT3 = 0;
	  FanLevelTemp2 = 0;
	  
      if (IS_MASK_CLEAR(POWER_FLAG6, adjustfan)) //206 BIT4
	  {	  
	    if (IS_MASK_CLEAR(POWER_FLAG10, fullspeed_fan)) //20A BIT0
		{
		 if (IS_MASK_CLEAR(POWER_FLAG9, super_quiet)) //981004-190731-A //Super Quiet 0x209 BIT0
	     {	
          if (IS_MASK_CLEAR(POWER_FLAG8, smart_cooling_on)) //981004-141029-A //208 BIT6
	      {
           if(IS_MASK_CLEAR(POWER_FLAG13, adjustfan2)) //20D BIT0 //Fan Customize
           {                          
            if(IS_MASK_CLEAR(POWER_FLAG13, adjustfan3)) //20D BIT7 //10 level fan 
            {       			
		      if (IS_MASK_CLEAR(POWER_FLAG12, autofan)) //20C BIT4 //Auto Low
		      {
			   //if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w)) //X6EVG Normal mode 
	           //{
			    if (FanLevelTemp >= 11) //981004-231122-M from 12
                {
                    FanLevelTemp = 11;
                }
				//981004-181106-M-S
				//981004-201207-M-S Need CPU/GPU to reach the temperature simutaneously
				#if 1
                //if ((FanLevelTemp == 10) || (FanLevelTemp ==11))
				if (FanLevelTemp == 9)	
                {				   
				  //if ((PECI_CPU_temp >= FanLevel4[FanLevelTemp+1].FanOn) && (GPU_TMPR >= FanLevel4[FanLevelTemp+1].FanOn))
				  //if (FINAL_TEMP2 >= FanLevel4[FanLevelTemp+1].FanOn)	
                  if ((PECI_CPU_temp >= 94) && (GPU_TMPR >= 86)) //TEST000 //981004-220113-M					  
			      {
			        FANLVDNCNT1++;
				    if (FANLVDNCNT1 >= 10) //981004-210322-M from 3
				    { 
				      FANLVDNCNT1 =0;
			          FanLevelTemp++;
                      if (FanLevelTemp >= 11) 
                      {
                          FanLevelTemp = 11;
                      }					  
			        }                                                   		
			      }    
                  else
                  {
                      FANLVDNCNT1 =0;			  
                  }  	
				}
				#endif
				else if (FanLevelTemp == 10)	
                {
				  if ((PECI_CPU_temp >= 97) && (GPU_TMPR >= 87)) //TEST000 //981004-220113-M					  
			      {
			        FANLVDNCNT1++;
				    if (FANLVDNCNT1 >= 10) //981004-210322-M from 3
				    { 
				      FANLVDNCNT1 =0;
			          FanLevelTemp++;
                      if (FanLevelTemp >= 11) 
                      {
                          FanLevelTemp = 11;
                      }					  
			        }                                                   		
			      }    
                  else
                  {
                      FANLVDNCNT1 =0;			  
                  }  		
				}	
                else
                {					
			      if (FINAL_TEMP2 >= FanLevel4[FanLevelTemp+1].FanOn)
			      {
			        FANLVDNCNT1++;
				    if (FANLVDNCNT1 >= 3) 
				    { 
				      FANLVDNCNT1 =0;
			          FanLevelTemp++;
					  if (FanLevelTemp >= 11) //981004-231122-M from 12
                      {
                          FanLevelTemp = 11;
                      }
			        }                                                   		
			     }    
                 else
                 {
                   FANLVDNCNT1 =0;			  
                 }
                } 			 	           
				//981004-201207-M-E
				
               if (FINAL_TEMP2 <= FanLevel4[FanLevelTemp].FanOff)
               {
                 if (FanLevelTemp == 0x00)
				 {	 
                       ;
				 }	   
				 else if ((FanLevelTemp == 10) || (FanLevelTemp ==11)) //TEST000
                 {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 10)
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }		
                 }			 
			     else
                 {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 5)
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }				   
                 }              			     
              }
              else
              {
                  FANLVDNCNT =0;				
              }          	   
              if (FanLevelTemp != FanDACLevel)
              {
                  if (FanLevelTemp == 0x00)
                      CLEAR_MASK(POWER_FLAG2, fan_on);
                  else
		          { 
                      SET_MASK(POWER_FLAG2, fan_on);
			          ///ZTIER = 0x02;  
		          }
              }
              DCR3 = FanLevel4[FanLevelTemp].DACValue; //GPU fan Duty //981004-171205-M from DCR0            
		     //} //981004-190326-R
			 
			 //981004-181106-R-S
			 #if 0
			 else //X6EVG normal mode
			 {
			   if(IS_MASK_CLEAR(POWER_FLAG13, adjustfan4)) //20D BIT2 //CPU/GPU temperature is under 90
               { 
			    if (FanLevelTemp >= 11) //981004-180126 from 14
                {
                    FanLevelTemp = 11;
                } 
			    if (FINAL_TEMP2 >= FanLevel[FanLevelTemp+1].FanOn)
			    {
			      FANLVDNCNT1++;
				  if (FANLVDNCNT1 >= 3) 
				  { 
				      FANLVDNCNT1 =0;
			          FanLevelTemp++;
					  if (FanLevelTemp >= 11) //981004-180126 from 14 
                      {
                          FanLevelTemp = 11;
                      }
			      }                 
			   }    
               else
               {
                 FANLVDNCNT1 =0;			  
               }			
	           
               if (FINAL_TEMP2 <= FanLevel[FanLevelTemp].FanOff)
               {
                 if (FanLevelTemp == 0x00)
                       ;
			     else
                 {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 5)
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }				   
                 }              			   
                }
              else
              {
                  FANLVDNCNT =0;								  
              }          	   
              if (FanLevelTemp != FanDACLevel)
              {
                  if (FanLevelTemp == 0x00)
                      CLEAR_MASK(POWER_FLAG2, fan_on);
                  else
		          { 
                      SET_MASK(POWER_FLAG2, fan_on);
			          ZTIER = 0x02;  
		          }
               }
               DCR3 = FanLevel[FanLevelTemp].DACValue; //GPU fan Duty //981004-171102-M from DCR0
			 }
			 else
			 {
			    DCR0 = 0xA0; //Duty 70% //981004-170527-A
		        DCR3 = 0xA0; //Duty 70% //981004-170527-A
		        FanLevelTemp = 8;
			 }
            }
            #endif
            //981004-181106-R-E			
           }
            else //Auto fan High (Gaming mode)
            {
              if (FanLevelTemp >= 15) //981004-231122-M from 13
              {
                 FanLevelTemp = 15;
              }			
              //if (FINAL_TEMP2 >= FanLevel5[FanLevelTemp+1].FanOn)
			
				//if ((FanLevelTemp == 13) || (FanLevelTemp ==14))
				#if 1 //981004-231228-A	
				if (FanLevelTemp == 13)	
				{
				  if ((PECI_CPU_temp >= 94) && (GPU_TMPR >= 86)) //TEST000 					  
			      {	
					 FANLVDNCNT1++;
				     if (FANLVDNCNT1 >= 10) 
				     { 
				         FANLVDNCNT1 =0;
			             FanLevelTemp++;
					     if (FanLevelTemp >= 15) 
                         {
                             FanLevelTemp = 15;
                         }
			         } 
                  }
                  else
                  {
                      FANLVDNCNT1 =0;			  
                  } 				  
				}
				else if (FanLevelTemp == 14)	
                {
				  if ((PECI_CPU_temp >= 97) && (GPU_TMPR >= 87))  					  
			      {
			        FANLVDNCNT1++;
				    if (FANLVDNCNT1 >= 10) //981004-210322-M from 3
				    { 
				      FANLVDNCNT1 =0;
			          FanLevelTemp++;
                      if (FanLevelTemp >= 15) 
                      {
                          FanLevelTemp = 15;
                      }					  
			        }                                                   		
			      }    
                  else
                  {
                      FANLVDNCNT1 =0;			  
                  }
				} 
                #endif				
                else //981004-231228-A
                {
                     if (FINAL_TEMP2 >= FanLevel5[FanLevelTemp+1].FanOn)
                     {						
			           FANLVDNCNT1++;
				       if (FANLVDNCNT1 >= 3) 
				       { 
				          FANLVDNCNT1 =0;
			              FanLevelTemp++;
					      if (FanLevelTemp >= 15) //981004-231122-M from 13
                          {
                            FanLevelTemp = 15;
                          }
			           }
					 }
                     else
                     {
                       FANLVDNCNT1 =0;
                     }						 
				}	//981004-231218-R				 
			   
             			            
              if (FINAL_TEMP2 <= FanLevel5[FanLevelTemp].FanOff)
              {
                 if (FanLevelTemp == 0x00)
				 {	 
                       ;
				 }
                 #if 1 //981004-231218-R				 
				 else if ((FanLevelTemp == 14) || (FanLevelTemp ==15)) 
                 {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 10)
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }		
                 }	
				 #endif
			     else
                 {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 5) 
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }                    			   
                 }			   
              }
              else
              {
                  FANLVDNCNT =0;				  			
              }           	   
              if (FanLevelTemp != FanDACLevel)
              {
                  if (FanLevelTemp == 0x00)
                      CLEAR_MASK(POWER_FLAG2, fan_on);
                  else
		          { 
                      SET_MASK(POWER_FLAG2, fan_on);
			          ///ZTIER = 0x02;  
		          }
              }
              //DCR0 = FanLevel5[FanLevelTemp].DACValue2; //CPU fan Duty //981004-171205-R
              DCR3 = FanLevel5[FanLevelTemp].DACValue; //GPU fan Duty 			  
             }
            
			}
            else //10 level Fan table
            {
              if (FINAL_TEMP2 >= (tFanOn[FanLevelTemp+1]))
			  {
			      FANLVDNCNT1++;
				  if (FANLVDNCNT1 >= 3) 
				  { 
				      FANLVDNCNT1 =0;
			          FanLevelTemp++;
					  if (FanLevelTemp >= 14) //981004-180126 from 10
					      FanLevelTemp = 14; 
			      }
			  }    
              else
              {
                 FANLVDNCNT1 =0;			  
              }			
	         
              if (FINAL_TEMP2 <= (tFanOn[FanLevelTemp]-3))
              {
                 if (FanLevelTemp == 0x00)
                       ;
			     else
                 {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 5)
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }				   
                 }                			   
              }
              else
              {
                  FANLVDNCNT =0;				
              }
              
              if (FanLevelTemp != FanDACLevel)
              {
                  if (FanLevelTemp == 0x00)
                      CLEAR_MASK(POWER_FLAG2, fan_on);
                  else
		          { 
                      SET_MASK(POWER_FLAG2, fan_on);
			          ///ZTIER = 0x02;  
		          }
              }
              DCR3 = tFandw[FanLevelTemp]; //GPU fan Duty //981004-171102-M from DCR0
            }			
		  }
		  
          else //Fan Customize table 
          {	
            if (FINAL_TEMP2 >= FanCustomize[FanLevelTemp+1].FanOn)
			{
			    FANLVDNCNT1++;
				if (FANLVDNCNT1 >= 3) 
				{ 
				    FANLVDNCNT1 =0;
			        FanLevelTemp++;
					if (FanLevelTemp >= 14) //981004-171205-M from 10 
					      FanLevelTemp = 14; 
			    }
				if(CustomMaxLevel_low<=FanLevelTemp)
				{					
					FanLevelTemp=CustomMaxLevel_low;
				}
			}    
            else
            {
               FANLVDNCNT1 =0;			  
            }			
	         
            if (FINAL_TEMP2 <= FanCustomize[FanLevelTemp].FanOff)
            {
               if (FanLevelTemp == 0x00)
                     ;
			   else
               {
                   FANLVDNCNT++;
				   if (FANLVDNCNT >= 5)
				   {
                       FANLVDNCNT =0;
					   FanLevelTemp--;
                   }				   
               }
                		   
				if(CustomMaxLevel_low<=FanLevelTemp)
				{				    
					FanLevelTemp=CustomMaxLevel_low;
				}			  			
               				   
            }
            else
            {
                FANLVDNCNT =0;
						   
				if(CustomMaxLevel_low<=FanLevelTemp)
				{				       
					FanLevelTemp=CustomMaxLevel_low;
				}			   	
               		
            }
              
            if (FanLevelTemp != FanDACLevel)
            {
                if (FanLevelTemp == 0x00)
                    CLEAR_MASK(POWER_FLAG2, fan_on);
                else
		        { 
                    SET_MASK(POWER_FLAG2, fan_on);
			        ///ZTIER = 0x02;  
		        }
            }
            DCR3 = FanCustomize[FanLevelTemp].DACValue; //GPU fan Duty //981004-171102-M from DCR0         
		    //FanRPM1 = DCR0; //System gauge //981004-150806-R
          } //Fan Customize table //981004-150722-A-E		  
         }
           else //Smart cooling table (Quiet mode) 
           {
		    if (FanLevelTemp >=7) //981004-180126 from 4
            {
                FanLevelTemp = 7;
            }	 
            if (FINAL_TEMP2 >= FanLevel3[FanLevelTemp+1].FanOn)
			{
				if ((FanLevelTemp == 5) || (FanLevelTemp ==6)) 
				{
					 FANLVDNCNT1++;
				     if (FANLVDNCNT1 >= 6) 
				     { 
				         FANLVDNCNT1 =0;
			             FanLevelTemp++;
					     if (FanLevelTemp >= 7) 
                         {
                             FanLevelTemp = 7;
                         }
			         }  
			    }
				else
				{	
			        FANLVDNCNT1++;
				    if (FANLVDNCNT1 >= 3) 
				    { 
				       FANLVDNCNT1 =0;
			           FanLevelTemp++;
					   if (FanLevelTemp >= 7) 
                       {
                           FanLevelTemp = 7;
                       }
			        } 
                }					
			}    
            else
            {
               FANLVDNCNT1 =0;
            }				            
            if (FINAL_TEMP2 <= FanLevel3[FanLevelTemp].FanOff)
            {
                if (FanLevelTemp == 0x00)
               	{			   
                     ;
			    }                
			    else if ((FanLevelTemp == 6) || (FanLevelTemp ==7)) 
                {
                     FANLVDNCNT++;
				     if (FANLVDNCNT >= 6)
				     {
                         FANLVDNCNT =0;
					     FanLevelTemp--;
                     }		                 								
				}				
			    else
                {
                   FANLVDNCNT++;
				   if (FANLVDNCNT >= 5)
				   {
                       FANLVDNCNT =0;
					   FanLevelTemp--;
                   }				   
               }			   
            }
            else
            {
                FANLVDNCNT =0;
            }           	   
            if (FanLevelTemp != FanDACLevel)
            {
                if (FanLevelTemp == 0x00)
                    CLEAR_MASK(POWER_FLAG2, fan_on);
                else
		        { 
                    SET_MASK(POWER_FLAG2, fan_on);
			        ///ZTIER = 0x02;  
		        }
            }
            DCR3 = FanLevel3[FanLevelTemp].DACValue; //GPU fan Duty //981004-171102-M from DCR0
           } //981004-141029-A-E
		 }
         else //Super Quiet mode //981004-190731-A-S
         {			
            if (FanLevelTemp >=4) 
            {
                FanLevelTemp = 4;
            }	 
            if (FINAL_TEMP2 >= FanLevel6[FanLevelTemp+1].FanOn)
			{
			    FANLVDNCNT1++;
				if (FANLVDNCNT1 >= 3) 
				{ 
				    FANLVDNCNT1 =0;
			        FanLevelTemp++;
			    } 	
			}    
            else
            {
               FANLVDNCNT1 =0;
            }				            
            if (FINAL_TEMP2 <= FanLevel6[FanLevelTemp].FanOff)
            {
               if (FanLevelTemp == 0x00)	
                     ;
			   else
               {
                   FANLVDNCNT++;
				   if (FANLVDNCNT >= 5)
				   {
                       FANLVDNCNT =0;
					   FanLevelTemp--;
                   }				   
               }			   
            }
            else
            {
                FANLVDNCNT =0;
            }           	   
            if (FanLevelTemp != FanDACLevel)
            {
                if (FanLevelTemp == 0x00)
                    CLEAR_MASK(POWER_FLAG2, fan_on);
                else
		        { 
                    SET_MASK(POWER_FLAG2, fan_on);
			        ///ZTIER = 0x02;  
		        }
            }
            DCR3 = FanLevel6[FanLevelTemp].DACValue; //GPU fan Duty 
         }
         //981004-190731-A-E (Super Quiet mode)		 
        } 
        else //Full speed fan
        {
            DCR3 = 0xE5; //Turbo fan //981004-171102-M from DCR0
			FanLevelTemp = 14; //981004-171205-M from 9			
		    FanRPM1	= DCR3; //981004-150414-A for System gauge //981004-171102-M from DCR0 
        }
		//981004-171205-M-S
        //if (IS_MASK_CLEAR(POWER_FLAG12, autofan)) //20C BIT4 //Auto Low
        //{		
        DCR0 = DCR3; 		
        //}		
        //981004-171205-M-E	
      }	  
	//981004-201105-M-E 
      else //Adjust fan 1
      {	
		  DCR0 = FanRPM1;	
          DCR3 = FanRPM2;	//981004-140904-A
        //981004-150414-A-S			
		  if(IS_MASK_SET(POWER_FLAG5, BIOS_flash))	//140587-150306-A set rpm duty 0x67 when run flash bios.
		  {
		      DCR0 = 0x5D; //981004-100813-M from 0x67
			  DCR3 = 0x5D; //981004-100813-M from 0x67
		  }
       //981004-150414-A-E		
      }
	}
	//981004-191017-A-S
	if ((!SLP_S3_L) && (SLP_S4_L))
	{
       DCR0 = 0x00;
       DCR3 = 0x00;
	   //ZTIER = 0x00; //981004-191125-R
    }
	
	//981004-191017-A-E
	
    CPU_DUTY = DCR0; //981004-181114-A //0x2B3
	GPU_DUTY = DCR3; //981004-191119-A //0x2B4
    FanDACLevel = FanLevelTemp;
    FanDACLevel2 = FanLevelTemp2; //981004-201106-A	
}


//981004-161202-A-S
void tSetDefault()
{
	int i=0;
	
	#if 0
	//981004-170419-M-S
	if (IS_MASK_SET(POWER_FLAG10, ac_current_180w)) //X5Y7 NV 980 
	{
	for(i=0;i<15;i++) //981004-180126-M from 11
	   {
		   tFanOn[i]=tFanDefault[i].FanOn;		   
		   tFandw[i]=tFanDefault[i].DACValue;	
	   }
	}
    else
    {
	   for(i=0;i<15;i++) 
	   {
		   tFanOn[i]=tFanDefault2[i].FanOn;		   
		   tFandw[i]=tFanDefault2[i].DACValue;	
	   }

    }
    #endif
	 for(i=0;i<15;i++) //X5X8+X5Y8 //981004-180126-M from 11
	 {
		tFanOn[i]=tFanDefault2[i].FanOn;		   
		tFandw[i]=tFanDefault2[i].DACValue;	
	 }

	//981004-170419-M-E
	   	
	ReadFAN_LV = 0x0f;
	SetFAN_LV	 = 0x0f;
}

void tSetZero()
{
	int i=0;

	for(i=0;i<15;i++) //981004-180126-M from 11
	{
		tFanOn[i]=0;
		tFandw[i]=0;
	
	}
}

void fanfunc_READ(BYTE lv)
{
   
	 FAN_ONR = tFanOn[lv];
	 FAN_DWR = tFandw[lv];
	
}

void fanfunc_SET(BYTE lv ,BYTE temp,BYTE dw)
{
   
	  tFanOn[lv]=temp;
	  tFandw[lv]=dw;
	  

}
//981004-161202-A-E

void vMoniterTemprature(void)
{
    //981004-151022-M-S	
    #if 0	
    if (IS_MASK_SET(POWER_FLAG6, GPU_on))
    {	    	   
		if (GPU_TMPR <= 5)
		{
		    GPU_TMPR = 5;
		}
	}	
    else
    {
        GPU_TMPR = 0;
    }
	#endif
    //981004-151022-M-E
	
    //if ((FINAL_TEMP2 >= CPUTHERMSHDN) || (GPU_TMPR >= 100)) 
	if ((PECI_CPU_temp >= 100) || (GPU_TMPR >= 100)) //981004-231220-M
    {
        VeryHotCnt++;		      

        if (VeryHotCnt > CpuTooHotTimes)
		{
            //while (1);  //981004-130314-R
            //SysPowState = SYSTEM_EC_WDTRST; //981004-130314-A
			//SysPowState = SYSTEM_S0_S4; //981004-221130-M
			///ETWCFG = EWDKEYEN;      /* Force Watchdog active */
            ///EWDCNTLLR = 0x01;       // for 1ms counter
            ///EWDKEYR = 0x5A;         // External WDTreset not match
			WDT->CTRL = 0x03; // force WDT
            while(1);               // Wait for watch dog time-out
		}	
    }	   
    else
        VeryHotCnt = 0x00;
		
	
    if(IS_MASK_SET(POWER_FLAG2, sci_on))	
	{		
        if ((PECI_CPU_temp >= 100) || (GPU_TMPR >= 100)) //981004-231220-M			
        {		
			ECQEvent(SCI_CPU_OVERHEAT, SCIMode_ACPI_SMBus); //0x68
		}	
	}
    
	#if 1 //981004-231220-A-S
    //if ((TEMP_TR1 >= 100) || (TEMP_TR2 >= 126) || (TEMP_TR3 >= 94) || (TEMP_TR4 >= 79) || (TEMP_TR5 >= 97) || (TEMP_TR6 >= 84) || (TEMP_TR8 >= 98)) 
	if ((TEMP_TR1 >= 92) || (TEMP_TR2 >= 119) || (TEMP_TR3 >= 94) || (TEMP_TR4 >= 76) || (TEMP_TR8 >= 100)) //981004-231228-M
    {
        VeryHotCnt2++;		      

        if (VeryHotCnt2 >= 10)
		{
            VeryHotCnt2 = 0x00;
            //SysPowState = SYSTEM_EC_WDTRST;
            //SysPowState = SYSTEM_S0_S4; //981004-221109-M
            ///ETWCFG = EWDKEYEN;      /* Force Watchdog active */
            ///EWDCNTLLR = 0x01;       // for 1ms counter
            ///EWDKEYR = 0x5A;         // External WDTreset not match
			WDT->CTRL = 0x03; // force WDT
            while(1);               // Wait for watch dog time-out
		}	
    }	   
    else
	{	
        VeryHotCnt2 = 0x00;
	}
	
	//CPU too hot
	if ((PECI_CPU_temp >= 98)) //981004-231220-M		
	{
		ThrottlingCnt1++;
		if (ThrottlingCnt1 >= 10)
		{
            ThrottlingCnt1 = 0;			
		    SET_MASK(CPU_HOT1, CPU_DTS); //0x349 bit0
			SET_MASK(CPU_HOT2, CPU_DTS_ONCE); //0x34B bit0
		}	 
	}
	else
	{
		ThrottlingCnt1 = 0;
	}	
    if ((TEMP_TR1 >= 88) || ((IS_MASK_SET(CPU_HOT2, NCT_TR1_ONCE)) && (TEMP_TR1 >= 86))) //981004-231228-M
	{
		ThrottlingCnt2++;
		if (ThrottlingCnt2 >= 10)
		{
            ThrottlingCnt2 = 0;			
		    SET_MASK(CPU_HOT1, NCT_TR1); //0x349 bit1
			SET_MASK(CPU_HOT2, NCT_TR1_ONCE); //0x34B bit1
		}	 
	}
	else
	{
		ThrottlingCnt2 = 0;
	}	
		
    if ((TEMP_TR4 >= 72)|| ((IS_MASK_SET(CPU_HOT2, NCT_TR4_ONCE)) && (TEMP_TR4 >= 70))) //981004-231228-M
	{
		ThrottlingCnt3++;
		if (ThrottlingCnt3 >= 10)
		{
            ThrottlingCnt3 = 0;			
		    SET_MASK(CPU_HOT1, NCT_TR4); //0x349 bit2
			SET_MASK(CPU_HOT2, NCT_TR4_ONCE); //0x34B bit2
		}	 
	}
	else
	{
		ThrottlingCnt3 = 0;
	}			
	
	if (IS_MASK_SET(CPU_HOT1, CPU_DTS) || IS_MASK_SET(CPU_HOT1, NCT_TR1) || IS_MASK_SET(CPU_HOT1, NCT_TR4))
	{
		SET_MASK(CPU_HOT1, CPU_TEMP_HOT); //0x349 bit3
		NVDeventdnCnt1 = 0;		
	}
    else
    {
		CLEAR_MASK(CPU_HOT1, CPU_TEMP_HOT); //0x349 bit3
		NVDeventupCnt1 = 0;
	}	
	
	//CPU cool down
	if (IS_MASK_SET(CPU_HOT1, CPU_DTS))
    {		
	   if ((PECI_CPU_temp <= 96)) //981004-231228-M			 
	   {
		   ThrottlingCnt10++;
		   if (ThrottlingCnt10 >= 10)
		   {
              ThrottlingCnt10 = 0;
		      CLEAR_MASK(CPU_HOT1, CPU_DTS); //0x349 bit0
	       }
	   }
       else
       {
		   ThrottlingCnt10 = 0;
	   }		   
	}
  
    if (IS_MASK_SET(CPU_HOT1, NCT_TR1))
    {  
        if ((TEMP_TR1 <= 83)) //981004-231228-M
	    {
		   ThrottlingCnt11++;
		   if (ThrottlingCnt11 >= 10)
		   {
              ThrottlingCnt11 = 0;
		      CLEAR_MASK(CPU_HOT1, NCT_TR1); //0x349 bit1
	       }
	   }
       else
       {
		   ThrottlingCnt11 = 0;
	   }			
	}
	
	if (IS_MASK_SET(CPU_HOT1, NCT_TR4))
    {
        if ((TEMP_TR4 <= 67)) //981004-231220-M
		{
		   ThrottlingCnt12++;
		   if (ThrottlingCnt12 >= 10)
		   {
              ThrottlingCnt12 = 0;
		      CLEAR_MASK(CPU_HOT1, NCT_TR4); //0x349 bit2	
	       }
	    }
       else
       {
		   ThrottlingCnt12 = 0;
	   }				  
    }
    //GPU too hot
	if ((GPU_TMPR >= 98) || ((IS_MASK_SET(GPU_HOT2, GPU_DTS_ONCE)) && (GPU_TMPR >= 92))) //981004-231228-M
	{
		ThrottlingCnt4++;
		if (ThrottlingCnt4 >= 10)
		{
            ThrottlingCnt4 = 0;			
		    SET_MASK(GPU_HOT1, GPU_DTS); //0x34A bit0
			SET_MASK(GPU_HOT2, GPU_DTS_ONCE); //0x34C bit0
		}	 
	}
	else
	{
		ThrottlingCnt4 = 0;
	}	
		
    if ((TEMP_TR2 >= 115) || ((IS_MASK_SET(GPU_HOT2, NCT_TR2_ONCE)) && (TEMP_TR2 >= 113))) //981004-231228-M
	{
        ThrottlingCnt5++;
		if (ThrottlingCnt5 >= 10)
		{
            ThrottlingCnt5 = 0;			
		    SET_MASK(GPU_HOT1, NCT_TR2); //0x34A bit1
			SET_MASK(GPU_HOT2, NCT_TR2_ONCE); //0x34C bit1
		}	 
	}
	else
	{
		ThrottlingCnt5 = 0;
	}			
		
    if ((TEMP_TR3 >= 90) || ((IS_MASK_SET(GPU_HOT2, NCT_TR3_ONCE)) && (TEMP_TR3 >= 88))) //981004-231228-M
	{
		ThrottlingCnt6++;
		if (ThrottlingCnt6 >= 10)
		{
            ThrottlingCnt6 = 0;			
		    SET_MASK(GPU_HOT1, NCT_TR3); //0x34A bit2
			SET_MASK(GPU_HOT2, NCT_TR3_ONCE); //0x34C bit2
		}	 
	}
	else
	{
		ThrottlingCnt6 = 0;
	}			
	#if 0	
    if ((TEMP_TR5 >= 93) || ((IS_MASK_SET(GPU_HOT2, NCT_TR5_ONCE)) && (TEMP_TR5 >= 92)))
	{
		ThrottlingCnt7++;
		if (ThrottlingCnt7 >= 10)
		{
            ThrottlingCnt7 = 0;			
		    SET_MASK(GPU_HOT1, NCT_TR5); //0x34A bit3
			SET_MASK(GPU_HOT2, NCT_TR5_ONCE); //0x34C bit3
		}	 
	}
	else
	{
		ThrottlingCnt7 = 0;
	}			
		
    if ((TEMP_TR6 >= 80) || ((IS_MASK_SET(GPU_HOT2, NCT_TR6_ONCE)) && (TEMP_TR6 >= 79)))
	{
		ThrottlingCnt8++;
		if (ThrottlingCnt8 >= 10)
		{
            ThrottlingCnt8 = 0;			
		    SET_MASK(GPU_HOT1, NCT_TR6); //0x34A bit4
			SET_MASK(GPU_HOT2, NCT_TR6_ONCE); //0x34C bit4
		}	 
	}
	else
	{
		ThrottlingCnt1 = 0;
	}			
	#endif	
    if ((TEMP_TR8 >= 98) || ((IS_MASK_SET(GPU_HOT2, NCT_TR8_ONCE)) && (TEMP_TR8 >= 98))) //981004-231228-M
	{
		ThrottlingCnt9++;
		if (ThrottlingCnt9 >= 10)
		{
            ThrottlingCnt9 = 0;			
		    SET_MASK(GPU_HOT1, NCT_TR8); //0x34A bit5
			SET_MASK(GPU_HOT2, NCT_TR8_ONCE); //0x34C bit5
		}	 
	}
	else
	{
		ThrottlingCnt9 = 0;
	}			
			
	//if (IS_MASK_SET(GPU_HOT1, GPU_DTS) || IS_MASK_SET(GPU_HOT1, NCT_TR2) || IS_MASK_SET(GPU_HOT1, NCT_TR3) || IS_MASK_SET(GPU_HOT1, NCT_TR5) || IS_MASK_SET(GPU_HOT1, NCT_TR6) || IS_MASK_SET(GPU_HOT1, NCT_TR8))
	if (IS_MASK_SET(GPU_HOT1, GPU_DTS) || IS_MASK_SET(GPU_HOT1, NCT_TR2) || IS_MASK_SET(GPU_HOT1, NCT_TR3) || IS_MASK_SET(GPU_HOT1, NCT_TR8))	
	{
		SET_MASK(GPU_HOT1, GPU_TEMP_HOT); //0x34A bit6
		NVDeventdnCnt2 = 0;
	}
    else
    {
		CLEAR_MASK(GPU_HOT1, GPU_TEMP_HOT); //0x34A bit6
		NVDeventupCnt2 = 0;
	}	
	
	//GPU cool down
	if (IS_MASK_SET(GPU_HOT1, GPU_DTS))
    {
	    if ((GPU_TMPR <= 90)) //981004-231228-M
	    {		 
		   ThrottlingCnt13++;
		   if (ThrottlingCnt13 >= 10)
		   {
              ThrottlingCnt13 = 0;
		      CLEAR_MASK(GPU_HOT1, GPU_DTS); //0x34A bit0	
	       }
	    }
        else
        {
		   ThrottlingCnt13 = 0;
	    }				   	  
	}
	
    if (IS_MASK_SET(GPU_HOT1, NCT_TR2))
    {	
        if ((TEMP_TR2 <= 110)) //981004-231228-M
	    {
			ThrottlingCnt14++;
		   if (ThrottlingCnt14 >= 10)
		   {
              ThrottlingCnt14 = 0;
		      CLEAR_MASK(GPU_HOT1, NCT_TR2); //0x34A bit1	
	       }
	    }
        else
        {
		   ThrottlingCnt14 = 0;
	    }				   	 		    	    
	}

    if (IS_MASK_SET(GPU_HOT1, NCT_TR3))
    {	
        if ((TEMP_TR3 <= 85)) //981004-231228-M
	    {
			ThrottlingCnt15++;
		   if (ThrottlingCnt15 >= 10)
		   {
              ThrottlingCnt15 = 0;
		      CLEAR_MASK(GPU_HOT1, NCT_TR3); //0x34A bit2	
	       }
	    }
        else
        {
		   ThrottlingCnt15 = 0;
	    }						    
	}
    
	#if 0
    if (IS_MASK_SET(GPU_HOT1, NCT_TR5))
    {	
        if ((TEMP_TR5 <= 90))
	    {
			ThrottlingCnt16++;
		   if (ThrottlingCnt16 >= 10)
		   {
              ThrottlingCnt16 = 0;
		      CLEAR_MASK(GPU_HOT1, NCT_TR5); //0x34A bit3	
	       }
	    }
        else
        {
		   ThrottlingCnt16 = 0;
	    }			
	}

    if (IS_MASK_SET(GPU_HOT1, NCT_TR6))
    {	
        if ((TEMP_TR6 <= 77))
	    {
			ThrottlingCnt17++;
		   if (ThrottlingCnt17 >= 10)
		   {
              ThrottlingCnt17 = 0;
		      CLEAR_MASK(GPU_HOT1, NCT_TR6); //0x34A bit4	
	       }
	    }
        else
        {
		   ThrottlingCnt17 = 0;
	    }					    
	}
	#endif

    if (IS_MASK_SET(GPU_HOT1, NCT_TR8))
    {	
        if ((TEMP_TR8 <= 96)) //981004-231228-M
	    {
			ThrottlingCnt18++;
		   if (ThrottlingCnt18 >= 10)
		   {
              ThrottlingCnt18 = 0;
		      CLEAR_MASK(GPU_HOT1, NCT_TR8); //0x34A bit5	
	       }
	    }
        else
        {
		   ThrottlingCnt18 = 0;
	    }						    
	}
	
		
	
	//CPU too Hot to reduce frequency
	if (IS_MASK_SET(CPU_HOT1, CPU_DTS) || IS_MASK_SET(CPU_HOT1, NCT_TR1) || IS_MASK_SET(CPU_HOT1, NCT_TR4))
    {                         
                    if (NVDeventStatus2 < 0x0A)  //CPU too Hot to reduce frequency
                    {
						NVDeventupCnt1++;
						if (NVDeventupCnt1 >= 10)
						{	
                            NVDeventStatus2++;
							NVDeventupCnt1 = 0;
                        }
                        switch (NVDeventStatus2)
                        {
                            case 0x01:
                                 //ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
                                 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 53;
                                 }
                                 else
                                 {
									WTDP = 30; 
								 }									 
                                 							 
                                break;
            
                            case 0x02:
                                 //ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3                                 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 51;
                                 }
                                 else
                                 {
									WTDP = 28; 
								 }											 
                                break;
                                
                            case 0x03:
                                 //ECQEvent(SCI_NV_D4, SCIMode_ACPI_SMBus); //0xD4								 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 49;
                                 }
                                 else
                                 {
									WTDP = 26; 
								 }			             
                                break;
                                
                            case 0x04:
                                 //ECQEvent(SCI_NV_D5, SCIMode_ACPI_SMBus); //0xD5                                 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 47;
                                 }
                                 else
                                 {
									WTDP = 24; 
								 }			                     								 
                                break;
                                
                            case 0x05:
                                 //ECQEvent(SCI_NV_D6, SCIMode_ACPI_SMBus);  //0xD6
								 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 45;
                                 }
                                 else
                                 {
									WTDP = 22; 
								 }			
                                break;
                            
                            case 0x06:
                                 //ECQEvent(SCI_NV_D7, SCIMode_ACPI_SMBus);  //0xD7								
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 43;
                                 }
                                 else
                                 {
									WTDP = 20; 
								 }			                   
                                break;

                            case 0x07:
                                 //ECQEvent(SCI_NV_D8, SCIMode_ACPI_SMBus);  //0xD8								 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 41;
                                 }
                                 else
                                 {
									WTDP = 18; 
								 }			                                 
                                break;

                            case 0x08:                                   
                                 //ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 39;
                                 }
                                 else
                                 {
									WTDP = 16; 
								 }			
                                break;
								
							case 0x09:                                   
                                 //ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 37;
                                 }
                                 else
                                 {
									WTDP = 14; 
								 }		
                                break;	

                            case 0x0A:                                   
                                 //ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA                                							 
				                 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 35;
                                 }
                                 else
                                 {
									WTDP = 12; 
								 }			                            
                                break;
								
							
                            default:
                                break;
                        }
                    }    
    }        
	else 
	{		 
                    if (NVDeventStatus2 >= 1)
                    {
						NVDeventdnCnt1++;
						if (NVDeventdnCnt1 >= 10)  //CPU recovery
						{	
                           NVDeventStatus2--;
						   NVDeventdnCnt1 = 0;
						}
                        switch (NVDeventStatus2)
                        {
							case 0x00:
							     if (IS_MASK_SET(CPU_HOT1, CPU_Throttling1))
								 {	 
                                    if (!AC_IN_L)
                                    {									 
						               WTDP = 100;
                                    }
									else
									{
										if (IS_MASK_CLEAR(POWER_FLAG4, bat30_on) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on)))   
                                        {	
                                           WTDP = 45;
										}
                                        else
                                        {
										   WTDP = 20;
										}											
									}	
									CLEAR_MASK(CPU_HOT1, CPU_Throttling1); //EC RAM 0x349 bit4	
								 }	
								 break;
                            case 0x01:
                                 //ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2
                                 SET_MASK(CPU_HOT1, CPU_Throttling1); //EC RAM 0x349 bit4								 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 53;
                                 }
                                 else
                                 {
									WTDP = 30; 
								 }						                                  							 
                                break;
            
                            case 0x02:
                                 //ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3
                                 //981004-200130-M-S
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 51;
                                 }
                                 else
                                 {
									WTDP = 28; 
								 }											 
                                break;
                                
                            case 0x03:
                                 //ECQEvent(SCI_NV_D4, SCIMode_ACPI_SMBus); //0xD4								 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 49;
                                 }
                                 else
                                 {
									WTDP = 26; 
								 }			             
                                break;
                                
                            case 0x04:
                                 //ECQEvent(SCI_NV_D5, SCIMode_ACPI_SMBus); //0xD5                                 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 47;
                                 }
                                 else
                                 {
									WTDP = 24; 
								 }		                     								 
                                break;
                                
                            case 0x05:
                                 //ECQEvent(SCI_NV_D6, SCIMode_ACPI_SMBus);  //0xD6
								 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 45;
                                 }
                                 else
                                 {
									WTDP = 22; 
								 }			
                                break;
                            
                            case 0x06:
                                 //ECQEvent(SCI_NV_D7, SCIMode_ACPI_SMBus);  //0xD7								
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 43;
                                 }
                                 else
                                 {
									WTDP = 20; 
								 }			                   
                                break;

                            case 0x07:
                                 //ECQEvent(SCI_NV_D8, SCIMode_ACPI_SMBus);  //0xD8								 
						         if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 41;
                                 }
                                 else
                                 {
									WTDP = 18; 
								 }				                                 
                                break;

                            case 0x08:                                   
                                 //ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 39;
                                 }
                                 else
                                 {
									WTDP = 16; 
								 }			
                                break;
								
							case 0x09:                                   
                                 //ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 37;
                                 }
                                 else
                                 {
									WTDP = 14; 
								 }			
                                break;	

                            case 0x0A:                                   
                                 //ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA                                							 
				                 if (((IS_MASK_SET(POWER_FLAG6, adjustfan)) && (FanRPM2 >= 0xE5)) || (IS_MASK_SET(POWER_FLAG12, autofan)))
                                 {									 
						            WTDP = 35;
                                 }
                                 else
                                 {
									WTDP = 12; 
								 }			    	                            
                                break;
								
							
                                
                            default:
                                break;
                        }
                    }           
    }
   
    //GPU too Hot to issue Q-event
	if (IS_MASK_SET(GPU_HOT1, GPU_DTS) || IS_MASK_SET(GPU_HOT1, NCT_TR2) || IS_MASK_SET(GPU_HOT1, NCT_TR3) || IS_MASK_SET(GPU_HOT1, NCT_TR5) || IS_MASK_SET(GPU_HOT1, NCT_TR6) || IS_MASK_SET(GPU_HOT1, NCT_TR8))
    {                         
                    if (NVDeventStatus3 < 9) 
                    {
						NVDeventupCnt2++;
						if (NVDeventupCnt2 >= 10)
						{	
                            NVDeventStatus3++;
							NVDeventupCnt2 = 0;
                        }
                        switch (NVDeventStatus3)
                        {
                            case 0x01:
                                 ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2								 						         
						         //WTDP = 45;				                                 							 
                                break;
            
                            case 0x02:
                                 ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3                                 
						         //WTDP = 45;									 
                                break;
                                
                            case 0x03:
                                 ECQEvent(SCI_NV_D4, SCIMode_ACPI_SMBus); //0xD4								 
						         //WTDP = 40;	             
                                break;
                                
                            case 0x04:
                                 ECQEvent(SCI_NV_D5, SCIMode_ACPI_SMBus); //0xD5                                 
						         //WTDP = 40;	                     								 
                                break;
                                
                            case 0x05:
                                 ECQEvent(SCI_NV_D6, SCIMode_ACPI_SMBus);  //0xD6
								 //WTDP = 35;	
                                break;
                            
                            case 0x06:
                                 ECQEvent(SCI_NV_D7, SCIMode_ACPI_SMBus);  //0xD7								
						         //WTDP = 30;	                   
                                break;

                            case 0x07:
                                 ECQEvent(SCI_NV_D8, SCIMode_ACPI_SMBus);  //0xD8								 
						         //WTDP = 25;	                                 
                                break;

                            case 0x08:                                   
                                 ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 //WTDP = 20;	
                                break;
								
							case 0x09:                                   
                                 ECQEvent(SCI_NV_DA, SCIMode_ACPI_SMBus);  //0xDA 
								 //WTDP = 15;	
                                break;	

                            default:
                                break;
                        }
                    }    
    }        
	else 
	{		 
                    if (NVDeventStatus3 >= 1) 
                    {
                        NVDeventdnCnt2++;
						if (NVDeventdnCnt2 >= 10)
						{	
                           NVDeventStatus3--;
						   NVDeventdnCnt2 = 0;
						}
						
                        switch (NVDeventStatus3)
                        {
							case 0x00:
							     if (IS_MASK_SET(GPU_HOT1, GPU_Throttling1))
								 {
							         if (!AC_IN_L)
								     {	 
                                       ECQEvent(SCI_BATT_LOW_TEMPER, SCIMode_ACPI_SMBus); //0xD1
                                     }
									 else
									 {
										ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2 
									 }	 
									 CLEAR_MASK(GPU_HOT1, GPU_Throttling1); //EC RAM 0x34A bit7
                                 }									 
						         //WTDP = 45;				                                 							 
                                break; 
                            case 0x01:
                                 ECQEvent(SCI_BATT_HIGH_TEMPER, SCIMode_ACPI_SMBus); //0xD2	
                                 SET_MASK(GPU_HOT1, GPU_Throttling1); //EC RAM 0x34A bit7								 
						         //WTDP = 45;				                                 							 
                                break;
            
                            case 0x02:
                                 ECQEvent(SCI_NV_D3, SCIMode_ACPI_SMBus); //0xD3                                 
						         //WTDP = 45;									 
                                break;
                                
                            case 0x03:
                                 ECQEvent(SCI_NV_D4, SCIMode_ACPI_SMBus); //0xD4								 
						         //WTDP = 40;	             
                                break;
                                
                            case 0x04:
                                 ECQEvent(SCI_NV_D5, SCIMode_ACPI_SMBus); //0xD5                                 
						         //WTDP = 40;	                     								 
                                break;
                                
                            case 0x05:
                                 ECQEvent(SCI_NV_D6, SCIMode_ACPI_SMBus);  //0xD6
								 //WTDP = 35;	
                                break;
                            
                            case 0x06:
                                 ECQEvent(SCI_NV_D7, SCIMode_ACPI_SMBus);  //0xD7								
						         //WTDP = 30;	                   
                                break;

                            case 0x07:
                                 ECQEvent(SCI_NV_D8, SCIMode_ACPI_SMBus);  //0xD8								 
						         //WTDP = 25;	                                 
                                break;

                            case 0x08:                                   
                                 ECQEvent(SCI_NV_D9, SCIMode_ACPI_SMBus);  //0xD9
								 //WTDP = 20;	
								
							
                                
                            default:
                                break;
                        }
                    }           
    }
    #endif	//981004-231218-R-E
}

void bGetThermalData(void)
{
    BYTE cnt = 0; 
		
    ReadCPUTemp(); //To Get PECI_CPU_temp
	
	//MBX_CPU_TEMP = PECI_CPU_temp; //981004-190109-A
	//MBX_GPU_TEMP = GPU_TMPR;//981004-190109-A
	
	#if 0
    for (cnt=0; cnt<5; cnt++)			
        if (bRWSMBus(SMbusChD, SMbusRB, GPUThermalAddr, RLTS, &GPU_TMPR2, SMBus_NoPEC)) //Second GPU(Slave)		
            break;		//(EC RAM : 264)		    	
	for (cnt=0; cnt<5; cnt++) //981004-130819-A	//Master GPU		
        if (bRWSMBus(SMbusChB, SMbusRB, GPUThermalAddr2, RLTS, &GPU_TMPR, SMBus_NoPEC)) //Master GPU
            break;		//(EC RAM : 261)
	#endif
	
    //981004-200923-A-S
	if (IS_MASK_SET(POWER_FLAG2, sci_on)) 
    {
       //if (bRWSMBus(SMbusChB, SMbusRB, GPUThermalAddr2, RLTS, &GPU_TMPR, SMBus_NoPEC))
	   if(SMBUS_RW_B(1,ReadByte,GPUThermalAddr2,RLTS,&GPU_TMPR))
       {
		   SET_MASK(POWER_FLAG6, GPU_on);
       }
       else
       {
           CLEAR_MASK(POWER_FLAG6, GPU_on);		   
       }		
    }	
    //981004-200923-A-E

    //981004-221130-A-S
    if ((GPU_TMPR <= 83) && (IS_MASK_SET(EC_Flag4, GPU_temp_75))) //981004-221128-M  
    {
       CLEAR_MASK(EC_Flag4, GPU_temp_75);
	   ECQEvent(SCI_GPUTEMP72, SCIMode_ACPI_SMBus); //0x59
	  if (!AC_IN_L)
      {				
          WTDP = 157; //981004-230915-M		  
      }      	  	   
    }
	
	if ((GPU_TMPR >= 88) && (IS_MASK_CLEAR(EC_Flag4, GPU_temp_75))) 
    {            
	    SET_MASK(EC_Flag4, GPU_temp_75);
	    ECQEvent(SCI_GPUTEMP75, SCIMode_ACPI_SMBus); //0x58
		if (!AC_IN_L)
        {	
		   WTDP = 45;
        }		   
	}	
	//981004-221130-A-E		
	
	//981004-230926-R-S PER Thermal request
	#if 0
    if (((IS_MASK_SET(POWER_FLAG8, smart_cooling_on)) || (IS_MASK_SET(POWER_FLAG9, super_quiet))) && (IS_MASK_SET(POWER_FLAG2, sci_on)))
    {
        if ((FINAL_TEMP2 <= 52) && (IS_MASK_SET(POWER_FLAG6, sv_thrt_on)))   
        {
            CLEAR_MASK(POWER_FLAG6, sv_thrt_on);
            //ECQEvent(SCI_SV_THROFF, SCIMode_ACPI_SMBus); //0x97 //981004-151204-R
			//ECQEvent(SCI_BATT_LOW_TEMPER, SCIMode_ACPI_SMBus); //0xD1 //981004-190826-R
			if ((IS_MASK_CLEAR(POWER_FLAG10, gtx970_bat_low)) && (IS_MASK_CLEAR(POWER_FLAG4, pstate_off)) && (IS_MASK_CLEAR(AmpHigh_flag, AmpHigh)) && (AC_boost_Status == 0) )
			{
			    if (NVDeventStatus <= 1)
				{
			         //981004-190610-M-S
                     if (IS_MASK_CLEAR(POWER_FLAG10, ac_current_180w))
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
                     //981004-190610-M-E 
				}	 
			}		 
        }
        if ((FINAL_TEMP2 >= 62) && (IS_MASK_CLEAR(POWER_FLAG6, sv_thrt_on))) //981004-190329-M
		//else if (FINAL_TEMP2 >= 62) 
        {
            SET_MASK(POWER_FLAG6, sv_thrt_on); //992022-130708-M            
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
    
    }
	#endif
	//981004-230926-R-E
	 
	if (IS_MASK_CLEAR(POWER_FLAG8, smart_cooling_on) && (IS_MASK_CLEAR(POWER_FLAG9, super_quiet)))
    {
       CLEAR_MASK(POWER_FLAG6, sv_thrt_on); //EC RAM 206 bit 7 
    }
    //981004-190731-M-E				
}

		
//981004-170418-R-S
#if 0
//-----------------------------------------------------------------------------
// Fan table 1   2009/08/18 Rev.01
//-----------------------------------------------------------------------------
const thermal2 code ThermalTalbe1[]=
{
    {0,	38,	0,	0,	&Fan1On_Step1,	&Fan1Off_Step1,	&Fan1RPM_Step1	},	// Level 0 	
    {1,	50,	36,	30,	&Fan1On_Step2,	&Fan1Off_Step2,	&Fan1RPM_Step2	},	// Level 1 	
    {2,	55,	48,	34,	&Fan1On_Step3,	&Fan1Off_Step3,	&Fan1RPM_Step3	},	// Level 2 	
    {3,	60,	53,	37,	&Fan1On_Step4,	&Fan1Off_Step4,	&Fan1RPM_Step4	},	// Level 3 	
    {4,	65,	58,	40,	&Fan1On_Step5,	&Fan1Off_Step5,	&Fan1RPM_Step5	},	// Level 4 	
    {5,	70,	63,	43,	&Fan1On_Step6,	&Fan1Off_Step6,	&Fan1RPM_Step6	},	// Level 5 	
    {6,	75,	68,	46,	&Fan1On_Step7,	&Fan1Off_Step7,	&Fan1RPM_Step7	},	// Level 6 	
    {7,127, 73, 56, &Fan1On_Step8,	&Fan1Off_Step8,	&Fan1RPM_Step8	},	// Level 7 		
};

//-----------------------------------------------------------------------------
// Fan table 2
//-----------------------------------------------------------------------------
const thermal2 code ThermalTalbe2[]=
{
	{0,	38,	 0,	0,	&Fan2On_Step1,	&Fan2Off_Step1,	&Fan2RPM_Step1	},	// Level 0 	
	{1,	50,	36,	30,	&Fan2On_Step2,	&Fan2Off_Step2,	&Fan2RPM_Step2	},	// Level 1 	
	{2,	55,	48,	34,	&Fan2On_Step3,	&Fan2Off_Step3,	&Fan2RPM_Step3	},	// Level 2 	
	{3,	60,	53,	37,	&Fan2On_Step4,	&Fan2Off_Step4,	&Fan2RPM_Step4	},	// Level 3 	
	{4,	65,	58,	40,	&Fan2On_Step5,	&Fan2Off_Step5,	&Fan2RPM_Step5	},	// Level 4 	
	{5,	70,	63,	43,	&Fan2On_Step6,	&Fan2Off_Step6,	&Fan2RPM_Step6	},	// Level 5 	
	{6,	75,	68,	46,	&Fan2On_Step7,	&Fan2Off_Step7,	&Fan2RPM_Step7	},	// Level 6 	
	{7,127, 73,	56,	&Fan2On_Step8,	&Fan2Off_Step8,	&Fan2RPM_Step8	},	// Level 7 		
};
#endif
//981004-170418-R-E


//-----------------------------------------------------------------------------
// The function of check fan rpm 1
//-----------------------------------------------------------------------------	
void CheckFanRPM1(void)
{
    #if 0
	BYTE FanLevel_t = FanLevel1;	
	BYTE Fan1RPM_t = Fan1RPM;

	if(Debugtemperature1==0x00)
	{
		temperature1 = TCPU_temp;
	}
	else
	{
		temperature1 = Debugtemperature1;
	}
		
	if(FanLevel_t <((sizeof(ThermalTalbe1)/sizeof(thermal2))-1))
	{
		if(temperature1> *ThermalTalbe1[FanLevel_t].FanOn)
		{
			FanLevel_t += 1;
		}
	}
	
	if (FanLevel_t>0)
	{
		if (temperature1< *ThermalTalbe1[FanLevel_t].FanOff)
		{			
			FanLevel_t-=1;
		}
	}
		
	FanLevel1 = FanLevel_t;	
	Fan1RPM = *ThermalTalbe1[FanLevel_t].RPM;
    #endif
}

//-----------------------------------------------------------------------------
// The function of check fan rpm 2
//-----------------------------------------------------------------------------
void CheckFanRPM2(void)
{
    #if 0
	BYTE FanLevel_t = FanLeve2;	
	BYTE Fan1RPM_t = Fan2RPM;

	if(Debugtemperature2==0x00)
	{
		temperature2 = TSys_temp;
	}
	else
	{
		temperature2 = Debugtemperature2;
	}
		
	if(FanLevel_t <((sizeof(ThermalTalbe2)/sizeof(thermal2))-1))
	{
		if(temperature2> *ThermalTalbe2[FanLevel_t].FanOn)
		{
			FanLevel_t += 1;
		}
	}
	
	if (FanLevel_t>0)
	{
		if (temperature2< *ThermalTalbe2[FanLevel_t].FanOff)
		{			
			FanLevel_t-=1;
		}
	}
		
	FanLeve2 = FanLevel_t;	
	Fan2RPM = *ThermalTalbe2[FanLevel_t].RPM;
	#endif
}

void Fan1MainControl(void)
{
    #if 0
	if(Fan1RPM>=Fan2RPM)
	{	
		if(((Fan1RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan1RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}
	}
	else
	{
		if(((Fan2RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan2RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}		
	}
	#endif
}

void Fan2MainControl(void)
{
    #if 0
	if(Fan2RPM>=Fan1RPM)
	{
		if(((Fan2RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan2RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}			
	}
    else
	{	
		if(((Fan1RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan1RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}
	}
	#endif
}

//-----------------------------------------------------------------------------
// The function of fan rpm control
//-----------------------------------------------------------------------------
void FanControl(void)
{
    #if 0
	if(	RPM1==0x0000)
	{
		FanValue = FanInitValue;
	}
	
    if(Fan1RPM!=0x00)
    {
        Fan1MainControl();
    }
    else
    {
        Fan2MainControl();
    }
	#endif
}


//-----------------------------------------------------------------------------
// Init. thermal table 1
//-----------------------------------------------------------------------------
void InitThermalTable1(void)
{
    #if 0
	BYTE index;
	index=0x00;
	while(index<(sizeof(ThermalTalbe1)/sizeof(thermal2)))
	{
		*ThermalTalbe1[index].FanOn=ThermalTalbe1[index].CFanOn;
		*ThermalTalbe1[index].FanOff=ThermalTalbe1[index].CFanOff;
		*ThermalTalbe1[index].RPM=ThermalTalbe1[index].CRPM;
		index++;
	}
	#endif
}

//-----------------------------------------------------------------------------
// Init. thermal table 2
//-----------------------------------------------------------------------------
void InitThermalTable2(void)
{
    #if 0
	BYTE index;
	index=0x00;
	while(index<(sizeof(ThermalTalbe2)/sizeof(thermal2)))
	{
		*ThermalTalbe2[index].FanOn=ThermalTalbe2[index].CFanOn;
		*ThermalTalbe2[index].FanOff=ThermalTalbe2[index].CFanOff;
		*ThermalTalbe2[index].RPM=ThermalTalbe2[index].CRPM;
		index++;
	}
	#endif
}

//-----------------------------------------------------------------------------
// Fan full on control
//-----------------------------------------------------------------------------
void FanFullOn(void)
{
    #if 0
	FanValue = MaxOutValue;
	FanFullOnCont = FullOnCounter;		    //2sec
	#endif
}

//-----------------------------------------------------------------------------
// Fan full off control
//-----------------------------------------------------------------------------
void FanFullOff(void)
{
    #if 0
	FanValue = 0x00;
	#endif
}

//-----------------------------------------------------------------------------
// Fan Init on control
//-----------------------------------------------------------------------------
void FanInitOn(void)
{
    #if 0
	FanValue = FanInitValue;
	FanFullOnCont = FullOnCounter;		    //2sec	
	#endif
}


//981004-160509-M-S from RPM1 By Mr.Ma request
//-----------------------------------------------------------------------------
// The function of get fan RPM
//-----------------------------------------------------------------------------
void GetRPM1(void)
{
    #if 0
    BYTE tach_H;
    BYTE tach_L;

    tach_H = F1TMRR; 
    tach_L = F1TLRR;
    if((tach_H!=0x00)||(tach_L!=0x00))
    {
		if(((tach_H*256) + tach_L)<RPM1Max)
		{
            RPM1=(4312500/TACH1P/((tach_H*256) + tach_L));
		}
        else
        {
            RPM1=RPM1Max; 
        }
    }
    else
    {
        RPM1=0x0000;
    }
	#endif
	
	uint8_t tach_H2;
    uint8_t tach_L2;

//    tach_H2 = F2TMRR;
//    tach_L2 = F2TLRR;
    tach_H2 = (uint8_t)(((uint16_t)(100000/(TACHO1->CTRL_b.CNT))*30)>>8); 
    tach_L2 = (uint8_t)(((uint16_t)(100000/(TACHO1->CTRL_b.CNT))*30));
    if((tach_H2!=0x00)||(tach_L2!=0x00))
    {
		if(((tach_H2*256) + tach_L2)<RPM1Max)
		{
            RPM1=(uint16_t)(4312500/TACH2P/((tach_H2*256) + tach_L2));
		}
        else
        {
            RPM1=RPM2Max; 
        }
    }
    else
    {
        RPM1=0x0000;
    }
}
//981004-140709-A-E

//981004-140813-A-S
//-----------------------------------------------------------------------------
// The function of get fan RPM
//-----------------------------------------------------------------------------
void GetRPM2(void)
{
    #if 0
    BYTE tach_H2;
    BYTE tach_L2;

    tach_H2 = F2TMRR;
    tach_L2 = F2TLRR;
    if((tach_H2!=0x00)||(tach_L2!=0x00))
    {
		if(((tach_H2*256) + tach_L2)<RPM2Max)
		{
            RPM2=(4312500/TACH2P/((tach_H2*256) + tach_L2));
		}
        else
        {
            RPM2=RPM2Max; 
        }
    }
    else
    {
        RPM2=0x0000;
    }
	#endif
	
	uint8_t tach_H;
    uint8_t tach_L;

    tach_H = (uint8_t)(((uint16_t)(100000/(TACHO1->CTRL_b.CNT))*30)>>8); 
    tach_L = (uint8_t)(((uint16_t)(100000/(TACHO1->CTRL_b.CNT))*30));
    if((tach_H!=0x00)||(tach_L!=0x00))
    {
		if(((tach_H*256) + tach_L)<RPM2Max)
		{
            RPM2=(uint16_t)(4312500/TACH1P/((tach_H*256) + tach_L));
		}
        else
        {
            RPM2=RPM1Max; 
        }
    }
    else
    {
        RPM2=0x0000;
    }
}
//981004-160509-M-E from RPM1 By Mr.Ma request

//-----------------------------------------------------------------------------
// The function of smart fan
//-----------------------------------------------------------------------------
void FanManager(void)
{
    //981004-200721-R-S
	#if 0
	if(FanFullOnCont!=0x00)
	{
		FanFullOnCont--;
        GetRPM1();
		return;
	}

	if(DebugFan1RPMT==0x00)			    // In normal control mode
	{
		if((Fan1RPM!=0x00)||(Fan2RPM!=0x00))
		{
            GetRPM1();
			FanControl();
		}
		else
		{
			if(FanValue != 0x00)
			{
				RPM1=0x0000;
				FanFullOff();
			}
		}
	}
	else											// In RPM debug mode
	{
		GetRPM1();
		if(	RPM1==0x0000)
		{
			FanValue = FanInitValue;
		}
		else
		{
			if(((DebugFan1RPMT*100)-RPMACC)>RPM1)
			{
				if(FanValue<MaxOutValue)
				FanValue++;	
			}
			else if(((DebugFan1RPMT*100)+RPMACC)<RPM1)
			{
				if(FanValue>0x00)
				FanValue--;	
			}
		}
	}
	#endif
    //981004-200721-R-E
}

//981004-220509-R-S
#if 0
//-----------------------------------------------------------------------------
// Moniter temperature
//-----------------------------------------------------------------------------
const sTooHot code asTooHot[]=
{
	//{ &TCPU_temp, 	CpuTooHot, &VeryHotCnt, 	CpuTooHotTimes },
	//{ &TSys_temp,   SysTooHot, &SysVeryHotCnt, 	SysTooHotTimes }	
};
#endif

void MoniterTemprature(void)
{
	#if 0
	BYTE index=0x00;
	while(index<(sizeof(asTooHot)/sizeof(sTooHot)))
	{
		if((*asTooHot[index].Temprature) >=asTooHot[index].Limit)
		{
			*asTooHot[index].Counter += 1;
			if(*asTooHot[index].Counter>asTooHot[index].Times)
			{
				Oem_TriggerS0S4(SC_CPUHOT);
			}
		}
		else
		{
			*asTooHot[index].Counter = 0x00;
		}
		index++;
	}	
    #endif
}
//981004-220509-R-E

//-----------------------------------------------------------------------------
// Function Name : ReadCPUTemp
//-----------------------------------------------------------------------------
void ReadCPUTemp(void) 
{
    if(SystemIsS0)
    {
        // Use PECI interface to read cpu temperature
        #ifdef PECI_Support
            #if ReadCPUTemperature
            if(CPUTjmax==0x00)         // Need to read CPU Tjmax
            {
                PECI_ReadCPUTJMAX();
            }
            else
            {
                PECI_ReadCPUTemp();     // Use PECI interface to read cpu temperature
            }
            #endif
        #endif 
        
        // Use thermal sensor to read cpu temperature
        //SET_MASK(SMBus2Flag1, PollRemote);
    }
}


//-----------------------------------------------------------------------------
// Function Name : ReadSysTemp
//-----------------------------------------------------------------------------
void ReadSysTemp(void) 
{
    if(SystemIsS0)
    {
        SET_MASK(SMBus2Flag1, PollLocal);
    }
}

//-----------------------------------------------------------------------------
// Function Name : InitThermalChip
//-----------------------------------------------------------------------------
void InitThermalChip(void)
{
    
    
}

#if 0
//981004-220509-A-S    
//-----------------------------------------------------------------------------
// The function of get fan RPM3 => NCT7802
//-----------------------------------------------------------------------------
void GetRPM3(void)
{
    bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN1_THERMAL, &FAN1_TEMP ,  SMBus_NoPEC);
	bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN1_RPMH, &FAN1_RPM_H ,  SMBus_NoPEC);
	bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN_RPML,  &FAN_RPM_L ,  SMBus_NoPEC);
   
    if((FAN1_RPM_H!=0x00)||(FAN_RPM_L!=0x00))
    {
		RPM3 =(1350000/(((FAN1_RPM_H*256) + (FAN_RPM_L)) >>3));
    }
    else
    {
        RPM3=0x0000;
    }
}

//-----------------------------------------------------------------------------
// The function of get fan RPM4 => NCT7802
//-----------------------------------------------------------------------------
void GetRPM4(void)
{
	bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN2_THERMAL, &FAN2_TEMP ,  SMBus_NoPEC);
    bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN2_RPMH, &FAN2_RPM_H ,  SMBus_NoPEC);
	bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN_RPML,  &FAN_RPM_L ,  SMBus_NoPEC);
   
    if((FAN2_RPM_H!=0x00)||(FAN_RPM_L!=0x00))
    {
		RPM4=(1350000/(((FAN2_RPM_H*256) + (FAN_RPM_L)) >>3));
    }
    else
    {
        RPM4=0x0000;
    }
}


//-----------------------------------------------------------------------------
// The function of get fan RPM5 => NCT7802
//-----------------------------------------------------------------------------
void GetRPM5(void)
{
	bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN3_THERMAL, &FAN3_TEMP ,  SMBus_NoPEC);
    bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN3_RPMH, &FAN3_RPM_H ,  SMBus_NoPEC);
	bRWSMBus(SMbusCh1, SMbusRB, NCT7802YAddr, FAN_RPML,  &FAN_RPM_L ,  SMBus_NoPEC);
   
    if((FAN3_RPM_H!=0x00)||(FAN_RPM_L!=0x00))
    {
		RPM5=(1350000/(((FAN3_RPM_H*256) + (FAN_RPM_L)) >>3));
    }
    else
    {
        RPM5=0x0000;
    }
}
#endif