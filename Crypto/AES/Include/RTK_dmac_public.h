#ifndef __RTK_DMAC_H__
#define __RTK_DMAC_H__

enum rtk_dmac_src_dst_sel_enum
{
	Dmac_src = 0x1,
	Dmac_dst = 0x2,
	Dmac_src_dst = 0x3
};

enum rtk_dmac_hs_type_sel_enum
{
	Dmac_hs_hardware = 0x0,
	Dmac_hs_software = 0x1
};

enum rtk_dmac_sca_gat_cnt_int_sel_enum
{
	Dmac_sg_count = 0x0,
	Dmac_sg_interval = 0x1
};

enum rtk_dmac_irq_type_enum
{
	Dmac_irq_none		= 0x00,
	Dmac_irq_tfr		= 0x01,
	Dmac_irq_block		= 0x02,
	Dmac_irq_srctran	= 0x04,
	Dmac_irq_dsttran	= 0x08,
	Dmac_irq_err		= 0x10,
	Dmac_irq_all		= 0x1F
};

enum rtk_dmac_sw_req_reg_sel_enum
{
	Dmac_request		= 0x1,
	Dmac_single_request = 0x2,
	Dmac_last_request	= 0x4
};

enum rtk_dmac_mas_num_enum
{
	Dmac_master1 = 0x0,
	Dmac_master2 = 0x1,
	Dmac_master3 = 0x2,
	Dmac_master4 = 0x3
};

//enum rtk_dmac_trans_type_enum
//{
//	Dmac_transfer_row1  = 0x1,
//	Dmac_transfer_row2  = 0x2,
//	Dmac_transfer_row3  = 0x3,
//	Dmac_transfer_row4  = 0x4,
//	Dmac_transfer_row5  = 0x5,
//	Dmac_transfer_row6  = 0x6,
//	Dmac_transfer_row7  = 0x7,
//	Dmac_transfer_row8  = 0x8,
//	Dmac_transfer_row9  = 0x9,
//	Dmac_transfer_row10 = 0xa
//};

enum rtk_dmac_hs_inter_num_sel_enum
{
	Dmac_hs_if0		= 0x0,
	Dmac_hs_if1		= 0x1,
	Dmac_hs_if2		= 0x2,
	Dmac_hs_if3		= 0x3,
	Dmac_hs_if4		= 0x4,
	Dmac_hs_if5		= 0x5,
	Dmac_hs_if6		= 0x6,
	Dmac_hs_if7		= 0x7,
	Dmac_hs_if8		= 0x8,
	Dmac_hs_if9		= 0x9,
	Dmac_hs_if10	= 0xA,
	Dmac_hs_if11	= 0xB,
	Dmac_hs_if12	= 0xC,
	Dmac_hs_if13	= 0xD,
	Dmac_hs_if14	= 0xE,
	Dmac_hs_if15	= 0xF,
	Dmac_hs_if16	= 0x10,
	Dmac_hs_if17	= 0x11,
	Dmac_hs_if18	= 0x12,
	Dmac_hs_if19	= 0x13,
	Dmac_hs_if20	= 0x14,
	Dmac_hs_if21	= 0x15,
	Dmac_hs_if22	= 0x16,
	Dmac_hs_if23	= 0x17,
	Dmac_hs_if24	= 0x18,
	Dmac_hs_if25	= 0x19,
	Dmac_hs_if26	= 0x1A,
	Dmac_hs_if27	= 0x1B,
	Dmac_hs_if28	= 0x1C,
	Dmac_hs_if29	= 0x1D,
	Dmac_hs_if30	= 0x1E,
	Dmac_hs_if31	= 0x1F,
	Dmac_hs_if32	= 0x20,
	Dmac_hs_if33	= 0x21,
	Dmac_hs_if34	= 0x22,
	Dmac_hs_if35	= 0x23,
	Dmac_hs_if36	= 0x24,
	Dmac_hs_if37	= 0x25,
	Dmac_hs_if38	= 0x26,
	Dmac_hs_if39	= 0x27,
	Dmac_hs_if40	= 0x28,
	Dmac_hs_if41	= 0x29,
	Dmac_hs_if42	= 0x2A,
	Dmac_hs_if43	= 0x2B,
	Dmac_hs_if44	= 0x2C,
	Dmac_hs_if45	= 0x2D,
	Dmac_hs_if46	= 0x2E,
	Dmac_hs_if47	= 0x2F,
	Dmac_hs_if48	= 0x30,
	Dmac_hs_if49	= 0x31,
	Dmac_hs_if50	= 0x32,
	Dmac_hs_if51	= 0x33,
	Dmac_hs_if52	= 0x34,
	Dmac_hs_if53	= 0x35,
	Dmac_hs_if54	= 0x36,
	Dmac_hs_if55	= 0x37,
	Dmac_hs_if56	= 0x38,
	Dmac_hs_if57	= 0x39,
	Dmac_hs_if58	= 0x3A,
	Dmac_hs_if59	= 0x3B,
	Dmac_hs_if60	= 0x3C,
	Dmac_hs_if61	= 0x3D,
	Dmac_hs_if62	= 0x3E,
	Dmac_hs_if63	= 0x3F
};

enum rtk_dmac_prot_sec_mod_en_enum
{
	Dmac_sec_mod_enable = 0x0,
	Dmac_sec_mod_disable = 0x1
};

enum rtk_dmac_fifo_mode_enum
{
	Dmac_fifo_mode_single = 0x0,
	Dmac_fifo_mode_half	  = 0x1
};

enum rtk_dmac_flow_ctl_mod_enum
{
	Dmac_data_prefetch_enabled = 0x0,
	Dmac_data_prefetch_disabled = 0x1
};

enum rtk_dmac_hs_polarity_enum
{
	Dmac_active_high = 0x0,
	Dmac_acrive_low  = 0x1
};

enum rtk_dmac_chn_pri_enum
{
	Dmac_priority_0 =   0x0,
	Dmac_priority_1 =   0x1,
	Dmac_priority_2 =   0x2,
	Dmac_priority_3 =   0x3,
	Dmac_priority_4 =   0x4,
	Dmac_priority_5 =   0x5,
	Dmac_priority_6 =   0x6,
	Dmac_priority_7 =   0x7,
	Dmac_priority_8 =   0x8,
	Dmac_priority_9 =   0x9,
	Dmac_priority_10 =  0xA,
	Dmac_priority_11 =  0xB,
	Dmac_priority_12 =  0xC,
	Dmac_priority_13 =  0xD,
	Dmac_priority_14 =  0xE,
	Dmac_priority_15 =  0xF
};

enum rtk_ende_enum
{
	encrypt = 1,
	decrypt = 0
};

enum rtk_key_size_enum
{
	key_128 = 0x00,
	key_192 = 0x01,
	key_256 = 0x10
};

enum rtk_cipher_mode_enum
{
	ECB_mode =  0x0000,
	CBC_mode =  0x0001,
	CFB_mode =  0x0010,
	OFB_mode =  0x0011,
	CTR_mode =  0x0100,
	GMAC_mode = 0x0101,
	GCM_mode =  0x0110,
	CMAC_mode = 0x0111,
	XTS_mode = 0x1000
};

struct rtk_dmac_chn_config_struct
{
	uint32_t							sar;
	uint32_t							dar;
	enum rtk_state_enum					ctl_llp_src_en;
	enum rtk_state_enum					ctl_llp_dst_en;
	enum rtk_dmac_mas_num_enum			ctl_sms;
	enum rtk_dmac_mas_num_enum			ctl_dms;
	enum dw_dmac_burst_trans_length		ctl_src_msize;
	enum dw_dmac_burst_trans_length		ctl_dst_msize;
	enum dw_dmac_address_increment		ctl_sinc;
	enum dw_dmac_address_increment		ctl_dinc;
	enum dw_dmac_transfer_width			ctl_src_tr_width;
	enum dw_dmac_transfer_width			ctl_dst_tr_width;
	uint8_t								testpad12;			//12
	uint8_t								testpad13;			//13
	uint32_t							sstat;
	uint32_t							dstat;
	uint32_t							sstatar;
	uint32_t							dstatar;
	enum rtk_dmac_hs_inter_num_sel_enum	cfg_dst_per;
	enum rtk_dmac_hs_inter_num_sel_enum	cfg_src_per;
	enum rtk_state_enum					cfg_ss_upd_en;
	enum rtk_state_enum					cfg_ds_upd_en;
	enum rtk_state_enum					cfg_reload_src;
	enum rtk_state_enum					cfg_reload_dst;
	enum rtk_dmac_hs_polarity_enum		cfg_src_hs_pol;
	enum rtk_dmac_hs_polarity_enum		cfg_dst_hs_pol;
	enum rtk_dmac_hs_type_sel_enum		cfg_hs_sel_src;
	enum rtk_dmac_hs_type_sel_enum		cfg_hs_sel_dst;
	uint8_t								testpad28;			// 28
	uint8_t								testpad29;			// 29
	uint32_t							llp_loc;
	enum rtk_dmac_mas_num_enum			llp_lms;
	enum rtk_state_enum					ctl_done;
	uint8_t								testpad33;			// 33
	uint8_t								testpad34;			// 34
	uint32_t							ctl_block_ts;
	enum dw_dmac_transfer_flow			ctl_tt_fc;
	enum rtk_state_enum					ctl_wrnp_en;
	enum rtk_state_enum					ctl_dst_scatter_en;
	enum rtk_state_enum					ctl_src_gather_en;
	enum rtk_state_enum					ctl_int_en;
	enum rtk_dmac_prot_sec_mod_en_enum	cfg_protctl;
	enum rtk_dmac_fifo_mode_enum		cfg_fifo_mode;
	enum rtk_dmac_flow_ctl_mod_enum		cfg_fc_mode;
	uint32_t							cfg_max_abrst;
	enum rtk_state_enum 				cfg_lock_b;
	enum rtk_state_enum 				cfg_lock_ch;
	enum rtk_dmac_chn_pri_enum			cfg_ch_prior;
	uint8_t								testpad48;			//48
	uint32_t							sgr_sgc;
	uint32_t							sgr_sgi;
	uint32_t							dsr_dsc;
	uint32_t							dsr_dsi;
	uint32_t							cpu_datain_3;
	uint32_t							cpu_datain_2;
	uint32_t							cpu_datain_1;
	uint32_t							cpu_datain_0;
	uint32_t							key_7;
	uint32_t							key_6;
	uint32_t							key_5;
	uint32_t							key_4;
	uint32_t							key_3;
	uint32_t							key_2;
	uint32_t							key_1;
	uint32_t							key_0;
	uint32_t							iv_3;
	uint32_t							iv_2;
	uint32_t							iv_1;
	uint32_t							iv_0;
	enum rtk_state_enum 				aes_dma_mode;
	uint8_t								testpad70;			// 70
	enum rtk_cipher_mode_enum			aes_cipher_mode;
	enum rtk_key_size_enum				aes_key_size;
	enum rtk_ende_enum					aes_ende;
	enum rtk_state_enum					aes_first;
	enum rtk_state_enum					aes_de_key_gen;
	enum rtk_state_enum					aes_byte_swap;
	enum rtk_state_enum					aes_mask_en;
	enum rtk_state_enum					aes_gcm_last;
	enum rtk_state_enum					aes_cmac_last;
	uint32_t							cipher_len;
	uint32_t							gmac_len_1;
	uint32_t							gmac_len_0;
	uint32_t							tag_3;
	uint32_t							tag_2;
	uint32_t							tag_1;
	uint32_t							tag_0;
	uint32_t							ghash_key_3;
	uint32_t							ghash_key_2;
	uint32_t							ghash_key_1;
	uint32_t							ghash_key_0;
};

struct rtk_dmac_lli_item
{
	uint32_t		sar;
	uint32_t		dar;
	uint32_t		llp;
	uint32_t		ctl_l;
	uint32_t		ctl_h;
	uint32_t		sstat;
	uint32_t		dstat;
	struct	rtk_list_head	list;
};

struct dmac_struct {
	struct rtk_device_struct dmac0;
	struct rtk_dmac_chn_config_struct dmac0_chan_config;
};

extern int RTK_dmac(struct dmac_struct *dmac);
extern uint32_t rtk_dmac_set_lalu_block(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num,struct rtk_dmac_chn_config_struct *ch_config1);
extern uint32_t rtk_dmac_set_aes(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num, struct rtk_dmac_chn_config_struct *ch_config1);
extern uint32_t rtk_dmac_enableChannel(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num);
extern uint32_t rtk_dmac_set_aes_first(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_state_enum aes_first);
extern bool rtk_dmac_is_enabled(struct rtk_device_struct *dev);
extern bool rtk_dmac_is_chn_enabled(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num);
extern uint32_t rtk_dmac_enableChannelIrq(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num);
extern uint32_t rtk_dmac_unmaskIrq(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num,enum rtk_dmac_irq_type_enum ch_irq);
extern uint32_t rtk_dmac_aes_set_maskIrq(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, uint32_t mask);
extern uint32_t rtk_dmac_init_config_reg(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, struct rtk_dmac_chn_config_struct *ch_config1);
extern void Initaesdma(void);
extern struct dmac_struct dmac0;
extern struct rtk_dmac_param_struct dmac_param;
extern struct rtk_dmac_regmap_struct *dmac_map;
extern struct rtk_dmac_aes_regmap_struct *dmac_aes_map;
extern struct rtk_dmac_chn_config_struct ch_config;
extern struct rtk_dmac_aes_int_and_constant_regmap_struct *dmac_aes_int_map;
extern const uint32_t channel_val[18];
#endif
