#include "RTK_Include.h"

uint8_t *Tmp_SMBPntr;

//----------------------------------------------------------------------------
// SMBus Center Variables
//----------------------------------------------------------------------------
const SMBUS_CENTER_CONTROL SMBUS_CTRL_TBL[] =
{
	{   &u8SMBus0_Index,  &u8SMBus0_Counter,  &u8I2C0_Wr_Len, &u8SMBus0_InUsing,  &u8SMBus0_TableSize, &u8Service_SMBus0,   ProcessSMBus0  },
	{   &u8SMBus1_Index,  &u8SMBus1_Counter,  &u8I2C1_Wr_Len, &u8SMBus1_InUsing,  &u8SMBus1_TableSize, &u8Service_SMBus1,   ProcessSMBus0  },
	{   &u8SMBus2_Index,  &u8SMBus2_Counter,  &u8I2C2_Wr_Len, &u8SMBus2_InUsing,  &u8SMBus2_TableSize, &u8Service_SMBus2,   ProcessSMBus0  },
	{   &u8SMBus3_Index,  &u8SMBus3_Counter,  &u8I2C3_Wr_Len, &u8SMBus3_InUsing,  &u8SMBus3_TableSize, &u8Service_SMBus3,   ProcessSMBus0  },
};

void Hook_Test(void)
{

}

void Error_Null(void)
{
    
}

//----------------------------------------------------------------------------
// SMBus channel table
//----------------------------------------------------------------------------
const SMBUS_COMMAND_SET SMBUS_CH0_TBL[] =
{
#ifdef SMBUS_TOOL_SUPPORT
	// SMBus protocol   Addr    Cmd     Data address    active flag and variable                                        byte cunt
	{ Cmd_RecvByte,     0x01,   0xFF,   &DB_SMBusData[0],  DB_R,   &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_SendByte,     0x01,   0xFF,   &DB_SMBusData[0],  DB_S,   &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_ReadByte,     0x01,   0xFF,   &DB_SMBusData[0],  DB_RB,  &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_WriteByte,    0x01,   0xFF,   &DB_SMBusData[0],  DB_WB,  &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_ReadWord,     0x01,   0xFF,   &DB_SMBusData[0],  DB_RW,  &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_WriteWord,    0x01,   0xFF,   &DB_SMBusData[0],  DB_WW,  &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_ReadBlock,    0x01,   0xFF,   &DB_SMBusData[0],  DB_RBB, &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
	{ Cmd_WriteBlock,   0x01,   0xFF,   &DB_SMBusData[0],  DB_WBB, &u8EC_SMBusFlag1, Hook_SMB1Debug, Error_SMB1Debug,    0x00},
#endif /*SMBUS_TOOL_SUPPORT*/

//#if (1)
	// SMBus protocol   Addr            cmd         		Date address        			active flag     	Variable        Hook func           Error func
	{ ReadWord,     SmBat_Addr,     BATCmd_CV1,			    &BAT_CV1,		            F_Bat_Cell1_Volt,  	&u8SMBus1_Flag4,   Hook_Test,           Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_CV2,   		    &BAT_CV2,   		        F_Bat_Cell2_Volt,  	&u8SMBus1_Flag4,   Hook_Test,      Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_CV3,   		    &BAT_CV3,   		        F_Bat_Cell3_Volt,  	&u8SMBus1_Flag4,   Hook_Test,      Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_CV4,   		    (uint16_t *)&BAT_CV4,   	F_Bat_Cell4_Volt,  	&u8SMBus1_Flag4,   Hook_Test,      Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_Current,  		&BAT_PRSNTRATE, 		    F_Bat_Curr,     	&u8SMBus1_Flag3,   Hook_Test,       Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_Volt,     		&BAT_PRSNTVOL,  	        F_Bat_Volt,      	&u8SMBus1_Flag3,   Hook_Test,       Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_Temp,     		&BAT_TEMPER,    		    F_Bat_Temp,      	&u8SMBus1_Flag3,   Hook_Test,   Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_BatStatus,   	(uint16_t *)&BAT_STATUS, 	F_Bat_Status,     	&u8SMBus1_Flag3,   Hook_Test,        Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_CC,  		    (uint16_t *)&BAT1_CC_L,		F_Bat_Chg_Curr,     &u8SMBus1_Flag3,   Hook_Test,    Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_CV, 		        (uint16_t *)&BAT1_CV_L, 	F_Bat_Chg_Volt,     &u8SMBus1_Flag3,   Hook_Test,    Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_DCap,     		&New_DSNCAP,			    F_Bat_Dsg_Curr,     &u8SMBus1_Flag3,   Hook_Test,     Error_Null,  0x00    },
	{ ReadWord,     SmBat_Addr,     BATCmd_DVolt,    		&BAT_DSNVTG,   		        F_Bat_Dsg_Volt,     &u8SMBus1_Flag3,   Hook_Test,    Error_Null,  0x00    },
// 	{ ReadWord,     SmBat_Addr,     C_FCCAP,    		(UINT8 *)&u16BAT1_FCC,   		F_Bat_Full_Cap,   	&u8SMBus1_Flag4,   Hook_FullCap,       Error_BAT1,  0x00    },
// 	{ ReadByte,     SmBat_Addr,     C_RSOC,     		&u8BAT1_RSOC_L,      			F_Bat_RSOC,      	&u8SMBus1_Flag4,   Hook_RSOC,          Error_BAT1,  0x00    },
// 	{ ReadWord,     SmBat_Addr,     C_RMCAP,    		(UINT8 *)&u16BAT1_RmCap,   		F_Bat_Rem_Cap,      &u8SMBus1_Flag4,   Hook_RMCap,         Error_BAT1,  0x00    },
// 	{ ReadWord,     SmBat_Addr,     C_CYCLE,    		(UINT8 *)&u16BAT1_Cycle_Count, 	F_Bat_Cycle_Count,	&u8SMBus1_Flag4,   Hook_CycleCount,    Error_BAT1,  0x00    },
// 	{ ReadWord,     SmBat_Addr,     C_MAX_ERR,  		(UINT8 *)&Bat1_MaxErr,  		F_Bat_Max_Error,  	&u8SMBus1_Flag2,   Hook_Null,      	 Error_BAT1,  0x00    },
// 	{ ReadWord,     SmBat_Addr,     C_DATE,  			(UINT8 *)&Bat1_Date,  			F_Bat_Date,  	   	&u8SMBus1_Flag2,   Hook_Null,          Error_BAT1,  0x00    },
// 	{ ReadWord,     SmBat_Addr,     C_SPEC,  			(UINT8 *)&Bat1_Spec,  			F_Bat_Spec,  	   	&u8SMBus1_Flag2,   Hook_Null,          Error_BAT1,  0x00    },
// 	{ ReadBlock,    SmBat_Addr,     C_DCHEM,  			(UINT8 *)&Bat1_Chem,  			F_Bat_Chem,     	&u8SMBus1_Flag2,   Hook_Null,          Error_BAT1,  0x00    },
// 	{ ReadBlock,    SmBat_Addr,     C_DNAME,  			(UINT8 *)&Bat1_DName,  			F_Bat_Dev_Name,     &u8SMBus1_Flag2,   Hook_Null,          Error_BAT1,  0x00    },
// 	{ ReadBlock,    SmBat_Addr,     CT_LABEL,  			(UINT8 *)&Bat1_CTLabel, 		F_Bat_CT_Label,   	&u8SMBus1_Flag2,   Hook_Null,          Error_BAT1,  0x00    },
// 	{ ReadBlock,    SmBat_Addr,     C_MNAME,  			(UINT8 *)&Bat1_MName,  			F_Bat_Mfg_Name,     &u8SMBus1_Flag2,   Hook_ManuName,      Error_BAT1,  0x00    },
// 	{ WriteWord,    Charger_Addr,   C_INPUT_CURRENT_L1, (UINT8 *)&u16SBC_AC_LimitL1, 	F_SBC_IC_Watt,  	&u8SMBus1_Flag6,   HookWriteChgIC,     HookChgFail, 0x00    },
// 	{ WriteWord,    Charger_Addr,   C_INPUT_CURRENT_L2, (UINT8 *)&u16SBC_AC_LimitL2, 	F_SBC_AC_Lim2,     	&u8SMBus1_Flag6,   Hook_Null,      	 HookChgFail, 0x00    },
// #if (ISL_95522)
// 	{ Cmd_WriteWord,    Charger_Addr,   C_MIN_CHG_VOLT, 	(UINT8 *)&u16SBC_MinChargeVolt, F_SBC_Sys_Volt,     &u8SMBus1_Flag6,   Hook_Null,      	 HookChgFail, 0x00    },
// #elif(ISL_8237)
// 	{ Cmd_WriteWord,    Charger_Addr,   C_SYS_VOLT, 		(UINT8 *)&u16SBC_SYS_Voltage,  	F_SBC_Sys_Volt,     &u8SMBus1_Flag6,   Hook_Null,      	 HookChgFail, 0x00    },
// #endif
// 	{ Cmd_WriteWord,    Charger_Addr,   C_CHG_VOLT, 		(UINT8 *)&u16SBC_Charge_Volt,  	F_SBC_Chg_Volt, 	&u8SMBus1_Flag6,   Hook_Null,      	 HookChgFail, 0x00    },
// 	{ Cmd_WriteWord,    Charger_Addr,   C_CHG_CURR, 		(UINT8 *)&u16SBC_Charge_Curr,  	F_SBC_Chhg_Curr,	&u8SMBus1_Flag6,   Hook_Null,      	 HookChgFail, 0x00    },
// 	{ Cmd_WriteWord,    Charger_Addr,   C_CONTROL_3C, 		(UINT8 *)&u16SBC_Reg_3C, 		F_SBC_Set_Opt1,   	&u8SMBus1_Flag7,   Hook_Null,          HookChgFail, 0x00    },
// 	{ Cmd_WriteWord,    Charger_Addr,   C_CONTROL_3D, 		(UINT8 *)&u16SBC_Reg_3D, 		F_SBC_Set_Opt2,   	&u8SMBus1_Flag7,   Hook_Null,          HookChgFail, 0x00    },
// 	{ Cmd_WriteWord,    Charger_Addr,   C_SBC_AC_PROCHOT,  	(UINT8 *)&u16SBC_AC_Prochot, 	F_SBC_AC_Prochot,   &u8SMBus1_Flag6,   Hook_Null,     	 HookChgFail, 0x00    },
// 	{ Cmd_WriteWord,    Charger_Addr,   C_SBC_DC_PROCHOT, 	(UINT8 *)&u16SBC_DC_Prochot, 	F_SBC_DC_Prochot,   &u8SMBus1_Flag6,   Hook_Null,      	 HookChgFail, 0x00    },
// #if (ISL_95522)
// 	{ Cmd_WriteWord,    Charger_Addr,   C_PROCHOT_DEBOUNCE, (UINT8 *)&u16Procchot_Debounce, F_SBC_Set_Opt3,   	&u8SMBus1_Flag7,   Hook_Null,          HookChgFail, 0x00    },
// 	{ Cmd_WriteWord,    Charger_Addr,   C_PROCHOT_DURATION, (UINT8 *)&u16Prochot_Duration, 	F_SBC_Set_Opt4,   	&u8SMBus1_Flag7,   Hook_Null,          HookChgFail, 0x00    },
// #elif(ISL_8237)
// 	{ Cmd_WriteWord,    Charger_Addr,   C_SBC_CONTROL_4C, 	(UINT8 *)&u16SBC_Control3, 		F_SBC_Set_Opt3,   	&u8SMBus1_Flag7,   Hook_Null,          HookChgFail, 0x00    },
// #endif
// 	{ Cmd_ReadWord,     Charger_Addr,   C_INPUT_CURRENT_L1, (UINT8 *)&u16SBC_R_AC_LimitL1,  F_SBC_Get_Inp_Curr, &u8SMBus1_Flag9,   Hook_Null,     	 HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_INPUT_CURRENT_L2, (UINT8 *)&u16SBC_R_AC_LimitL2, 	F_SBC_Get_AC_Lim2,  &u8SMBus1_Flag8,   Hook_Null,      	 HookChgFail, 0x00    },
// #if (ISL_95522)
// 	{ Cmd_ReadWord,     Charger_Addr,   C_MIN_CHG_VOLT, 	(UINT8 *)&u16SBC_R_MinChgVolt, 	F_SBC_Get_SYS_V, 	&u8SMBus1_Flag8,   Hook_Null,      	 HookChgFail, 0x00    },
// #elif(ISL_8237)
// 	{ Cmd_ReadWord,     Charger_Addr,   C_SYS_VOLT, 		(UINT8 *)&u16SBC_R_SYS_Voltage, F_SBC_Get_SYS_V, 	&u8SMBus1_Flag8,   Hook_Null,      	 HookChgFail, 0x00    },
// #endif
// 	{ Cmd_ReadWord,     Charger_Addr,   C_CHG_VOLT	, 		(UINT8 *)&u16SBC_R_Chg_Voltage, F_SBC_Get_Chg_Volt, &u8SMBus1_Flag9,   Hook_Null,      	 HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_CHG_CURR,	 		(UINT8 *)&u16SBC_R_Chg_Current, F_SBC_Get_Chg_Curr, &u8SMBus1_Flag9,   Hook_Null,      	 HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_SBC_AC_PROCHOT,  	(UINT8 *)&u16SBC_R_AC_Prochot, 	F_SBC_Get_AC_PH,  	&u8SMBus1_Flag8,   Hook_Null,     	 HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_SBC_DC_PROCHOT, 	(UINT8 *)&u16SBC_R_DC_Prochot, 	F_SBC_Get_DC_PH,  	&u8SMBus1_Flag8,   Hook_Null,      	 HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_CONTROL_3C, 		(UINT8 *)&u16SBC_R_Reg_3C, 		F_SBC_Get_Opt1,    	&u8SMBus1_Flag8,   Hook_Null,          HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_CONTROL_3D, 		(UINT8 *)&u16SBC_R_Reg_3D, 		F_SBC_Get_Opt2,    	&u8SMBus1_Flag8,   Hook_Null,          HookChgFail, 0x00    },
// #if (ISL_95522)
// 	{ Cmd_ReadWord,     Charger_Addr,   C_PROCHOT_DEBOUNCE, (UINT8 *)&u16PHOT_R_Debounce, 	F_SBC_Get_Opt3,    	&u8SMBus1_Flag8,   Hook_Null,          HookChgFail, 0x00    },
// 	{ Cmd_ReadWord,     Charger_Addr,   C_PROCHOT_DURATION, (UINT8 *)&u16PHOT_R_Duration, 	F_SBC_Get_Opt4,    	&u8SMBus1_Flag8,   Hook_Null,          HookChgFail, 0x00    },
// #elif(ISL_8237)
// 	{ Cmd_ReadWord,     Charger_Addr,   C_SBC_CONTROL_4C, 	(UINT8 *)&u16SBC_R_Control3, 	F_SBC_Get_Opt3,    	&u8SMBus1_Flag8,   Hook_Null,          HookChgFail, 0x00    },
// #endif
// #endif
	//For I2C used
	/*  SMBus protocol  Addr        ID Index	Useless             Useless         Useless         Hook ok             Hook Fail       Useless  */
	//{ Cmd_I2cCompatible,0xff,       0,          &DB_SMBusData[0],      F_I2C_Test0,       &u8SMBus1_Flag5,   Hook_I2C1_OK,       Hook_I2C1_FAIL,	0x00},
	//{ Cmd_I2cCompatible,0xff,       1,          &DB_SMBusData[0],      F_I2C_Test1,       &u8SMBus1_Flag5,   Hook_I2C1_OK,       Hook_I2C1_FAIL,	0x00},

};

void SMBusMgr(void)
{
    u8SMBus_Select = 0;
	SMBusDataSender(u8SMBus_Select);
    //if (++u8SMBus_Select >= 7)
	{
		u8SMBus_Select=0x00;
	}
}


// do this function if interrupt occur
void SMBusDataHandle(void)
{
    if(u8Service_SMBus0 == 1)
    {
        u8Service_SMBus0 = 0;
        ProcessSMBus0();
    }
}

void SMBusDataSender(uint8_t channel)
{
    uint8_t tempSMBusindex;
    uint8_t smbus_flag;
    uint8_t smbus_protocol;
    uint8_t smbus_cmd;
    uint8_t smbus_address;
    uint16_t *smbus_data =0;
    uint8_t smbus_Bcnt;

    if (*SMBUS_CTRL_TBL[channel].inusing !=0x00)
    {
        (*SMBUS_CTRL_TBL[channel].timeout)++;
        if(*SMBUS_CTRL_TBL[channel].timeout > 50)
        {
            I2C_Timeout_Process(channel);        
            *SMBUS_CTRL_TBL[channel].inusing = 0x00;
            tempSMBusindex++;

		    if (tempSMBusindex >= *SMBUS_CTRL_TBL[channel].tablesize)
		    {
			    tempSMBusindex=0x00;
		    }
        }
        *SMBUS_CTRL_TBL[channel].index = tempSMBusindex;

	}
    else
    {
        *SMBUS_CTRL_TBL[channel].timeout = 0x00; /* Clear time-out flag. */
		smbus_flag = 0x00;              /* Pre-clear need service flag. */
        switch(channel)
        {
            case 0:
            if(IS_MASK_SET(*SMBUS_CH0_TBL[tempSMBusindex].ConditionVar,SMBUS_CH0_TBL[tempSMBusindex].Conditionflag))
            {
                smbus_flag = 0x01;
            }
            break;

            default:
            break;

        }

        if(smbus_flag==0)
        {
            tempSMBusindex++;
            if(tempSMBusindex >= *SMBUS_CTRL_TBL[channel].tablesize)
            {
                tempSMBusindex = 0;
            }
            *SMBUS_CTRL_TBL[channel].index = tempSMBusindex;
        }
        else
        {
            *SMBUS_CTRL_TBL[channel].inusing = 0x01;
            //stop transaction
            //clear status bit
            switch (channel)
            {
            case 0:
                smbus_protocol = SMBUS_CH0_TBL[tempSMBusindex].protocol;
                smbus_address = SMBUS_CH0_TBL[tempSMBusindex].address;
                smbus_cmd = SMBUS_CH0_TBL[tempSMBusindex].cmd;
                smbus_data = SMBUS_CH0_TBL[tempSMBusindex].smbdata;
                smbus_Bcnt = SMBUS_CH0_TBL[tempSMBusindex].Bcunt;

                break;
            
            default:
                break;
            }

            switch (smbus_protocol)
            {
            case ReadWord:
            PollReadSMBusWord(channel,smbus_address,smbus_cmd);
                break;
            
            default:
            *SMBUS_CTRL_TBL[channel].inusing=0x00;
                break;
            }
        }
    }
   
}

void PollReadSMBusWord(uint8_t ch,uint8_t addr, uint8_t cmd)
{
    /// Enable interrupt
    
    *asSMBus[ch].SMBusADR = (uint32_t)addr>>1;
    *asSMBus[ch].SMBusEN = 0x00000001;
    *asSMBus[ch].SMBusDCMD = cmd;
    I2C0_EnableIRQ();
    //*asSMBus[ch].SMBusDCMD |= BIT8;

}

void ProcessSMBus0(void)
{
    static uint8_t step =0;
    //if smbus using

        //if(IS_BIT_SET(*asSMBus[0].SMBusSTA,BIT4))
        if(((*asSMBus[0].SMBusSTA & 0x00000010) == 0x0000010) || ((*asSMBus[0].SMBusSTA & 0x00000004) == 0x00000004))
        {
            *asSMBus[0].SMBusDCMD = 0x01<<8; //Read
            I2C0_EnableIRQ();
            *SMBUS_CH0_TBL->smbdata = (uint8_t)*asSMBus[0].SMBusDCMD;
            *asSMBus[0].SMBusDCMD = 0x03<<8; // Read with STOP
            I2C0_EnableIRQ();
            *(SMBUS_CH0_TBL->smbdata+1) = (uint8_t)*asSMBus[0].SMBusDCMD;
        }
        //if(IS_BIT_SET(*asSMBus[0].SMBusSTA,BIT2))
        if((*asSMBus[0].SMBusSTA & 0x00000004) == 0x00000004)
        {

            //I2C0_EnableIRQ();
        }

        if(IS_BIT_SET(*asSMBus[0].SMBusSTA,BIT2+BIT9))
        {
            
        }
    
    // if(IS_BIT_SET(*asSMBus[0].SMBusSTA,BIT4))
    // {
    //     *asSMBus[0].SMBusDCMD = 0x01<<8; //Read
    //     I2C0_EnableIRQ();
    // }
    // if(IS_BIT_SET(*asSMBus[0].SMBusSTA,BIT2))
    // {
    //     *SMBUS_CH0_TBL->smbdata = (uint8_t)*asSMBus[0].SMBusDCMD;
    //     *asSMBus[0].SMBusDCMD = 0x03<<8; // Read with STOP
    //     I2C0_EnableIRQ();
    // }
    // else if(IS_BIT_SET(*asSMBus[0].SMBusSTA,BIT2+BIT9))
    // {
    //     *(SMBUS_CH0_TBL->smbdata+1) = (uint8_t)*asSMBus[0].SMBusDCMD;
    // }
}

void CheckSMBusTableSize(void)
{
	u8SMBus0_TableSize = (sizeof(SMBUS_CH0_TBL)/sizeof(SMBUS_COMMAND_SET));
	//u8SMBus1_TableSize = (sizeof(SMBUS_CH1_TBL)/sizeof(SMBUS_COMMAND_SET));
	//u8SMBus2_TableSize = (sizeof(SMBUS_CH2_TBL)/sizeof(SMBUS_COMMAND_SET));
	//u8SMBus3_TableSize = (sizeof(SMBUS_CH3_TBL)/sizeof(SMBUS_COMMAND_SET));
}