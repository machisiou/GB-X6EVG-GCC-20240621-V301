#ifndef __Oem_UPPDFW_TI_H__
#define __Oem_UPPDFW_TI_H__
/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/
#define _TIPD_CUSTUSE_ADD		0xA6	// the custuse begining address of tps6598x_lowregion_array_gandalf

/*-----------------------------------------------------------------------------
 * UCSI Data field & Data Structure Prototype
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Data Type & Data Structure Prototype
 *---------------------------------------------------------------------------*/
 
/*-----------------------------------------------------------------------------
 ******************************************************************************
 * For TI PD Parameters Prototype & Define
 ******************************************************************************
 *---------------------------------------------------------------------------*/
#define _TI_RD_TYPE1                0x00
#define _TI_WR_TYPE1                0x80

#define _TIPD_VID                   0x00
#define _TIPD_DID                   0x01
#define _TIPD_PROTO_VER             0x02
#define _TIPD_MODE                  0x03
#define _TIPD_TYPE                  0x04
#define _TIPD_OUID					0x06 //981004-220208-A
#define _TIPD_CMD1                  0x08
#define _TIPD_DATA1                 0x09
#define _TIPD_VERSION               0x0F

#define _TIPD_INT_EVENT1            0x14
#define _TIPD_INT_EVENT2            0x15
#define _TIPD_INT_MASK1             0x16
#define _TIPD_INT_MASK2             0x17
#define _TIPD_INT_CLEAR1            0x18
#define _TIPD_INT_CLEAR2            0x19
#define _TIPD_STATUS                0x1A
#define _POWER_STATUS               0x20 //981004-211215-A
#define _TIPD_SYSTEM_CONFIG         0x28
#define _TIPD_CONTROL_CONFIG        0x29
#define _TIPD_BOOT_STATUS			0x2D //981004-220208-A
#define _TIPD_RX_SRC_CAPABILITIES   0x30
#define _TIPD_ACTIVE_CONTRACT_PDO   0x34
#define _TIPD_ACTIVE_CONTRACT_RDO   0x35
#define _TIPD_POWER_STATUS          0x3F
#define _TIPD_PD_STATUS             0x40
#define _TIPD_DATA_CONTROL          0x50 //981004-220830-A
#define _TIPD_DATA_STATUS           0x5F
#define _TIPD_CCn_PIN_STATE         0x69

#define LowAppConfigOffset         	0x3FC //981004-220208-A
#define HighAppConfigOffset         0x7FC //981004-220208-A
// Event Bit Define
//Reserved                          BIT7    //INT_uint8_ts11.87.BIT7
//Reserved                          BIT6    //INT_uint8_ts11.86.BIT6
//Reserved                          BIT5    //INT_uint8_ts11.85.BIT5
//Reserved                          BIT4    //INT_uint8_ts11.84.BIT4
//Reserved                          BIT3    //INT_uint8_ts11.83.BIT3
#define F_I2CMasterNACKed	        BIT2    //INT_uint8_ts11.82.BIT2
#define F_ReadyForPatch		        BIT1    //INT_uint8_ts11.81.BIT1
#define F_PatchLoaded		        BIT0    //INT_uint8_ts11.80.BIT0

#define F_Cmd2Complete              BIT7    //INT_uint8_ts4.31.BIT7
#define F_Cmd1Complete              BIT6    //INT_uint8_ts4.30.BIT6
//Reserved                          BIT5    //INT_uint8_ts4.29.BIT5
//Reserved                          BIT4    //INT_uint8_ts4.28.BIT4
#define F_PDStatusUpdate            BIT3    //INT_uint8_ts4.27.BIT3
#define F_StatusUpdate              BIT2    //INT_uint8_ts4.26.BIT2
#define F_DataStatusUpdate          BIT1    //INT_uint8_ts4.25.BIT1
#define F_PowerStatusUpdate         BIT0    //INT_uint8_ts4.24.BIT0

#define F_PPswitchChanged           BIT7    //INT_uint8_ts3.23.BIT7
//Reserved                          BIT6    //INT_uint8_ts3.22.BIT6
#define F_UsbHostPresentNoLonger    BIT5    //INT_uint8_ts3.21.BIT5
#define F_UsbHostPresent            BIT4    //INT_uint8_ts3.20.BIT4
//Reserved                          BIT3    //INT_uint8_ts3.19.BIT3
#define F_DRSwapRequested           BIT2    //INT_uint8_ts3.18.BIT2
#define F_PRSwapRequested           BIT1    //INT_uint8_ts3.17.BIT1
//Reserved                          BIT0    //INT_uint8_ts3.16.BIT0

//Reserved                          BIT7    //INT_uint8_ts2.15.BIT7
#define F_SourceCapMsgRcvd          BIT6    //INT_uint8_ts2.14.BIT6
#define F_NewContractAsProv         BIT5    //INT_uint8_ts2.13.BIT5
#define F_NewContractAsCons         BIT4    //INT_uint8_ts2.12.BIT4
#define F_VDMReceived               BIT3    //INT_uint8_ts2.11.BIT3
#define F_AttentionReceived         BIT2    //INT_uint8_ts2.10.BIT2
#define F_Overcurrent               BIT1    //INT_uint8_ts2.9 .BIT1
//Reserved                          BIT0    //INT_uint8_ts2.8 .BIT0

#define F_SourceCapUpdated          BIT7    //INT_uint8_ts1.7 .BIT7
#define F_FRSwapComplete            BIT6    //INT_uint8_ts2.6 .BIT6
#define F_DRSwapComplete            BIT5    //INT_uint8_ts1.5 .BIT5
#define F_PRSwapComplete            BIT4    //INT_uint8_ts1.4 .BIT4
#define F_PlugInsertOrRemoval       BIT3    //INT_uint8_ts1.3 .BIT3
//Reserved                          BIT2    //INT_uint8_ts1.2 .BIT2
#define F_PDHardReset               BIT1    //INT_uint8_ts1.1 .BIT1
//Reserved                          BIT0    //INT_uint8_ts1.0 .BIT0

/* TI 4CC Command list used for the primary command interface */
typedef struct Ti4ccStruct
{
    uint8_t    ccmd;
    uint8_t    bcnt;
    uint8_t    cch1;
    uint8_t    cch2;
    uint8_t    cch3;
    uint8_t    cch4;
} sTi4ccStruct;
enum ti_4cc_command
{
	_4CC_UCSI   = 0x00,
    _4CC_Gaid   = 0x01,
    _4CC_GAID   = 0x02,
    _4CC_PBMs	= 0x03,
    _4CC_PBMc	= 0x04,
    _4CC_PBMe	= 0x05,
	_4CC_SRDY	= 0x06,
	_4CC_SRYR	= 0x07,
	_4CC_FLrd	= 0x08,                   //981004-220208-A
    _4CC_FLad	= 0x09,                   //981004-220208-A
    _4CC_FLwd	= 0x0A,                   //981004-220208-A
    _4CC_FLvy	= 0x0B,                   //981004-220208-A
};
/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/

//extern void ucsi_cmd_unsupported_command(void);
//extern void RTS_FirmwareUpdate(uint8_t PD_ADDR);
//extern void RTS_GetBinPDVersion(uint8_t PD_ADDR);
extern void TI_FirmwareUpdate(void);
extern void Get_Bin_Size(void);
extern void pd_i2c_buffer_clear(void);
extern uint8_t TI_PD_WrToRdStream(uint8_t I2C_Addr, uint8_t *Var, uint8_t Count, uint8_t WrDly,
                            uint8_t *Var2, uint8_t Count2);

extern void pd_ti_get_active_PDO(void); //981004-210118-A
extern void pd_ti_get_active_PDO2(void);
extern void Enable_pd_adapter(void); //981004-210118-A
extern void Enable_pd_adapter2(void); //981004-210118-A								
extern void Disable_pd_adapter(void); //981004-210118-A
extern void Disable_pd_adapter2(void); //981004-210118-A
extern uint8_t pd1_ti_check_version(void); //981004-210611-A
extern uint8_t pd1_ti_check_version2(void); //981004-210611-A
extern void TI_PD_Warm_reset(void); //981004-211102-A
extern void TI_PD_Warm_reset2(void); //981004-211102-A
//extern void TBT_Reconnet(void);
//extern void TBT_Reconnet2(void);
extern void TI_FW_CHECK(void); //981004-211119-A
extern void TI_FW_CHECK2(void); //981004-211119-A
//extern void S0_STATUS(void); //981004-211215-A
//extern void S4_STATUS(void); //981004-211215-A
extern void service_app_update_ti_pd(void); //981004-220208-A
extern uint8_t pd_ti_send_4cc(uint8_t Index4cc);
extern const sTi4ccStruct _TI_PD_4CC_TBLs[];
extern uint8_t I2C_Protocol_PD(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf);
extern uint8_t I2C_Protocol_PD2(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf);
extern void pd1_ti_HandleErroe(void);
extern void pd_ti_clear_event(uint8_t *Var);
extern uint8_t pd_ti_check_Cmd1Complete(void);
extern uint8_t pd_ti_check_readyforpatch(void);
extern uint8_t pd_ti_check_patchloaded(void);
extern uint8_t pd1_ti_check_ptch_mode(void);
extern uint8_t pd1_ti_check_app_mode(void);
extern uint8_t pd_ti_check_CMD1(void);

extern uint8_t pd_ti_check_Cmd1Complete2(void);
extern uint8_t pd_ti_check_readyforpatch2(void);
extern uint8_t pd_ti_check_patchloaded2(void);
extern uint8_t pd1_ti_check_ptch_mode2(void);
extern uint8_t pd1_ti_check_app_mode2(void);
extern uint8_t pd_ti_check_CMD2(void);

extern uint8_t I2C_Protocol_SMART_AMP(uint8_t Channel, uint8_t Addr, uint8_t WDatCnt, uint8_t RDatCnt, uint8_t *WDatBuf, uint8_t *RDatBuf);
extern void Clear_Ti_SmartAmp(void);
extern void Init_Ti_SmartAmp(void);
extern void Read_Ti_SmartAmp(void);
/*-----------------------------------------------------------------------------
 * For TI PD Function Call Prototype
 *---------------------------------------------------------------------------*/
//extern uint8_t Realtek_pd_gpio8_control(uint8_t PD_ADDR, uint8_t HI_LO);
//extern uint8_t pd_fw_update_get_ping_success(void);
//extern uint8_t RTS_CheckPDVersion(void);
/*-----------------------------------------------------------------------------
 * Realtek Data Type & Data Structure Prototype
 *---------------------------------------------------------------------------*/
//#define _RTS_PING_SUCCESS           0x01


#endif