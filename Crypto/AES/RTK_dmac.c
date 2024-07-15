#include "Include.h"


#define SEC_BASE 0x40004000
//struct rtk_dmac_chn_config_struct ch_config = RTK_CHN_CONFIG_DEFAULT_DEFINE_PARAMS;
struct rtk_dmac_chn_config_struct ch_config;
struct dmac_struct dmac0;
//struct rtk_dmac_param_struct dmac_param = RTK_DEFINE_DMAC_PARAMS();
struct rtk_dmac_param_struct dmac_param;
//struct rtk_dmac_regmap_struct *dmac_map = (struct rtk_dmac_regmap_struct *)RTK_LALU_AES_REG_BASE;
struct rtk_dmac_regmap_struct *dmac_map;
//struct rtk_dmac_aes_regmap_struct *dmac_aes_map = (struct rtk_dmac_aes_regmap_struct *) RTK_LALU_AES_DMAC_BASE;
struct rtk_dmac_aes_regmap_struct *dmac_aes_map;

//static enum rtk_dmac_irq_type_enum irqType0; // dmac irq type
//static enum rtk_dmac_chn_num_enum chNum; // channel number, for lalu aes fifo is channel 0
//static struct rtk_dmac_aes_int_and_constant_regmap_struct *dmac_aes_int_map = (struct rtk_dmac_aes_int_and_constant_regmap_struct*)(SEC_BASE+0xEE0);
struct rtk_dmac_aes_int_and_constant_regmap_struct *dmac_aes_int_map;



void userListener(struct rtk_device_struct *dev, int eCode);
void userCallback(struct rtk_device_struct *dev, int eCode);
enum rtk_dmac_chn_num_enum rtk_dmac_get_free_chn(struct rtk_device_struct *dev);
void rtk_dmac_enable(struct rtk_device_struct *dev);
int rtk_dmac_clearIrq(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num,enum rtk_dmac_irq_type_enum ch_irq);
uint32_t rtk_dmac_initialize(struct rtk_device_struct *dev);
uint32_t rtk_dmac_set_addr(struct rtk_device_struct * dev,enum rtk_dmac_chn_num_enum ch_num,enum rtk_dmac_src_dst_sel_enum sd_sel,uint32_t address);
uint32_t rtk_dmac_set_block_size(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, uint32_t block_size);
uint32_t rtk_dmac_set_chn_config(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num,struct rtk_dmac_chn_config_struct *ch_config);
uint32_t rtk_dmac_set_llp_loc(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num, uint32_t address);
unsigned rtk_dmac_get_chn_index(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num);
uint32_t rtk_dmac_set_tt_fc(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num,enum dw_dmac_transfer_flow tt_fc);
uint32_t rtk_dmac_set_trans_width(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_src_dst_sel_enum sd_sel, enum dw_dmac_transfer_width xf_width);
uint32_t rtk_dmac_set_mas_sel(struct rtk_device_struct *dev,enum rtk_dmac_chn_num_enum ch_num,enum rtk_dmac_src_dst_sel_enum sd_sel,enum rtk_dmac_mas_num_enum mst_num);
uint32_t rtk_dmac_set_msize(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_src_dst_sel_enum sd_sel, enum dw_dmac_burst_trans_length xf_length);
uint32_t rtk_dmac_set_addr_inc(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_src_dst_sel_enum sd_sel, enum dw_dmac_address_increment addr_inc);
uint32_t rtk_dmac_set_hs_inter(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_src_dst_sel_enum sd_sel, enum rtk_dmac_hs_inter_num_sel_enum hs_inter);
uint32_t rtk_dmac_set_fifo_mode(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_fifo_mode_enum fifo_mode);
uint32_t rtk_dmac_set_hs_type(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_src_dst_sel_enum sd_sel, enum rtk_dmac_hs_type_sel_enum hs_hwsw_sel);
uint32_t rtk_dmac_gat_en(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_state_enum state);
uint32_t rtk_dmac_set_sca_en(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_state_enum state);
uint32_t rtk_dmac_setGatherIntervalCount(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, uint32_t sgr);
uint32_t rtk_dmac_setScatterIntervalCount(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, uint32_t dsr);
uint32_t rtk_dmac_set_prot_sec_mode(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_prot_sec_mod_en_enum prot_lvl);
uint32_t rtk_dmac_setWrnpEnable(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_state_enum state);
uint32_t rtk_dmac_set_int_en(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_state_enum state);
uint32_t rtk_dmac_set_reload(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_src_dst_sel_enum sd_sel, enum rtk_state_enum state);
uint32_t rtk_dmac_set_chn_pri(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num, enum rtk_dmac_chn_pri_enum ch_priority);



const uint32_t channel_val[18] = 
{
	Dmac_no_channel,
	Dmac_channel0,
	Dmac_channel1,
	Dmac_channel2,
	Dmac_channel3,
	Dmac_channel4,
	Dmac_channel5,
	Dmac_channel6,
	Dmac_channel7,
	Dmac_channel8,
	Dmac_channel9,
	Dmac_channel10,
	Dmac_channel11,
	Dmac_channel12,
	Dmac_channel13,
	Dmac_channel14,
	Dmac_channel15,
	Dmac_all_channels
};


int RTK_dmac(struct dmac_struct *dmac)
{
	uint32_t info;
	//volatile int *data;

	enum rtk_dmac_chn_num_enum channel_num;
	struct rtk_dmac_regmap_struct *dmac0_map;

	//unsigned int errorCode; // function return status
	//enum rtk_dmac_chn_num_enum chNum; // channel number, for lalu aes fifo is channel 0
	enum rtk_dmac_irq_type_enum irqType0; // dmac irq type
	dmac_map = (struct rtk_dmac_regmap_struct *) RTK_LALU_AES_DMAC_BASE; // set dmac base address
	dmac_aes_map = (struct rtk_dmac_aes_regmap_struct *) RTK_LALU_AES_REG_BASE; // set dmac aes fifo register base address
	dmac_aes_int_map = (struct rtk_dmac_aes_int_and_constant_regmap_struct *) (RTK_LALU_AES_REG_BASE + 0xEE0); // set dmac aes fifo intertupt register base address


	dmac_param.num_channels = 1; // set channel number to dmac_param
	//dmac->dmac0.comp_param = &dmac_param;


	printf("nDMA START\n");
	printf("************\n");
	// 1. get dmac
	dmac0_map = dmac->dmac0.base_address;
	channel_num = rtk_dmac_get_free_chn(&dmac->dmac0);

	// 2. initial dmac
	info = rtk_dmac_initialize(&dmac->dmac0);

	unsigned int errorCode;
	irqType0 = Dmac_irq_tfr;
	//chNum = Dmac_channel0;

	errorCode = rtk_dmac_enableChannelIrq(&dmac->dmac0, channel_num);
	if(errorCode != 0)
    	printf("\n ERROR: Failed to enable channel interrupts\n");

	errorCode = rtk_dmac_unmaskIrq(&dmac->dmac0, channel_num, irqType0);
	if(errorCode != 0)
    	printf("\n ERROR: Failed to un-mask channel tfr interrupts\n");

	errorCode = rtk_dmac_aes_set_maskIrq(&dmac->dmac0, channel_num, 0);
	if(errorCode != 0)
    	printf("\n ERROR: Failed to set mask channel aes interrupt\n");

	ch_config.ctl_src_tr_width = Dmac_trans_width_64;
	ch_config.ctl_dst_tr_width = Dmac_trans_width_64;
	ch_config.cfg_fifo_mode = 1;
	ch_config.ctl_src_msize = Dmac_msize_4;
	ch_config.ctl_dst_msize = Dmac_msize_4;
	ch_config.ctl_int_en = 0x1;

	errorCode = rtk_dmac_init_config_reg(&dmac->dmac0, channel_num, &ch_config);
	if(errorCode != 0){
    	printf("\n ERROR: Failed to write configuration structure\n");
    	printf("into the DMA controller register on channel 0\n");
		}

	
	if(info != 0)
		printf(" 2. is not correct! \n");

	//info = rtk_dmac_set_chn_config(&(dmac->dmac0),channel_num,&(dmac->dmac0_chan_config));
	info = rtk_dmac_set_chn_config(&(dmac->dmac0),channel_num,&ch_config);


	if(info != 0)
		printf("3. setchannel config is not correct!\n");
	else
		printf("3. setchannel config is correct!\n");

	// 4. ENABLE DMA, channel
	if(!rtk_dmac_is_enabled(&dmac->dmac0))
	{
		rtk_dmac_enable(&dmac->dmac0);
		while(1)
		{
			if(rtk_dmac_is_enabled(&dmac->dmac0))
				break;
		}
	}
	printf(" DMAC is enable\n");

	// 4. Enable channel
	info = rtk_dmac_enableChannel(&dmac->dmac0, channel_num);

	while(1)
	{
		if(!rtk_dmac_is_chn_enabled(&dmac->dmac0, channel_num))
			break;
	}

	printf("**************\n");
	return 0;
}

uint32_t rtk_dmac_initialize(struct rtk_device_struct *dev)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	//uint32_t ID = 0xFFFFFFFF;
	uint32_t info;
	//uint32_t channel_num;

	printf("dmac init start\n");

	dmac_map = dev->base_address;

//	printf("dmac_map address (%08x) \n", dmac_map);

	rtk_dmac_enable(dev);
	dmac_map->ch_en_reg_l_ = 0xFF00FF00;
	info = (uint32_t)rtk_dmac_clearIrq(dev,Dmac_all_channels,Dmac_irq_all);

	if(!info)
		printf("All Interrupt are cleard !!\n");

	if( (dmac_map->ch_en_reg_l_  != 0)     ||
		(dmac_map->status_tfr_l_ != 0)     ||
		(dmac_map->status_block_l_ != 0)   ||
		(dmac_map->status_srctran_l_ != 0) ||
		(dmac_map->status_dsttran_l_ != 0) ||
		(dmac_map->status_err_l_ != 0))
	{
		printf("dmac_map = %x %x %x %x %x %x %x\n",dmac_map->ch_en_reg_l_, dmac_map->status_tfr_l_ ,
			dmac_map->status_tfr_l_ ,
			dmac_map->status_block_l_,
			dmac_map->status_srctran_l_ ,
			dmac_map->status_dsttran_l_ ,
			dmac_map->status_err_l_ 
			);
	  return RTK_EIO;
	}
		printf("DMAC Init finish \n");

	return 0;
}

void rtk_dmac_enable(struct rtk_device_struct *dev)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	dmac_map = dev->base_address;
	dmac_map->dma_cfg_reg_l_ = 0x1;

}

enum rtk_dmac_chn_num_enum rtk_dmac_get_free_chn(struct rtk_device_struct *dev)
{
	unsigned int channel_num;
	uint32_t chen_reg;
	int get_num;

	//struct rtk_dmac_regmap_struct *dmac_map;
	struct rtk_dmac_param_struct *dmac_para;

	dmac_map = dev->base_address;
	chen_reg = dmac_map->ch_en_reg_l_;
	dmac_para = dev->comp_param;

	for(channel_num = 1, get_num = 0; channel_num<=dmac_para->num_channels;channel_num++)
	{
		printf("channel_num = %x\n", channel_num);
		printf("channel_val[%x] = %x\n", channel_num , channel_val[channel_num]);
		if((chen_reg && (channel_val[channel_num])) == 0)
		{
			get_num = 1;
			break;
		}
	}

	if(get_num == 0)
		return channel_val[0];
	else
		return channel_val[channel_num];
}

int rtk_dmac_clearIrq(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_irq_type_enum ch_irq)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	struct rtk_dmac_param_struct *dmac_para;
	//uint32_t info;
	unsigned int channel_num = 0;
	dmac_map = dev->base_address;
	dmac_para = dev->comp_param;

	//channel_num = rtk_dmac_get_chn_index(dev,ch_num);

	if((ch_num != Dmac_all_channels)&&(channel_num >= dmac_para->num_channels))
	{
		return RTK_ECHRNG;
	}
	else if(channel_num < 8)
	{
		if(ch_irq == Dmac_irq_none)
		{}
		else if(ch_irq == Dmac_irq_tfr)
		{
			dmac_map->clear_tfr_l_ = ch_num & 0xFF;
		}
		else if(ch_irq == Dmac_irq_block)
		{
			dmac_map->clear_block_l_ = ch_num & 0xFF;
		}
		else if(ch_irq == Dmac_irq_srctran)
		{
			dmac_map->clear_srctran_l_ = ch_num & 0xFF;
		}
		else if(ch_irq == Dmac_irq_dsttran)
		{
			dmac_map->clear_dsttran_l_ = ch_num & 0xFF;
		}
		else if(ch_irq == Dmac_irq_err)
		{
			dmac_map->clear_err_l_ = ch_num & 0xFF;
		}
		else if(ch_irq == Dmac_irq_all)
		{
			dmac_map->clear_tfr_l_ = ch_num & 0xFF;
			dmac_map->clear_block_l_ = ch_num & 0xFF;
			dmac_map->clear_srctran_l_ = ch_num & 0xFF;
			dmac_map->clear_dsttran_l_ = ch_num & 0xFF;
			dmac_map->clear_err_l_ = ch_num & 0xFF;
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if(ch_irq == Dmac_irq_none)
		{}
		else if(ch_irq == Dmac_irq_tfr)
		{
			dmac_map->clear_tfr_l_ = (ch_num & 0x00FF0000)>>8;
		}
		else if(ch_irq == Dmac_irq_block)
		{
			dmac_map->clear_block_l_ = (ch_num & 0x00FF0000)>>8;
		}
		else if(ch_irq == Dmac_irq_srctran)
		{
			dmac_map->clear_srctran_l_ = (ch_num & 0x00FF0000)>>8;
		}
		else if(ch_irq == Dmac_irq_dsttran)
		{
			dmac_map->clear_dsttran_l_ = (ch_num & 0x00FF0000)>>8;
		}
		else if(ch_irq == Dmac_irq_err)
		{
			dmac_map->clear_err_l_ = (ch_num & 0x00FF0000)>>8;
		}
		else if(ch_irq == Dmac_irq_all)
		{
			dmac_map->clear_tfr_l_ = (ch_num & 0x00FF0000)>>8;
			dmac_map->clear_block_l_ = (ch_num & 0x00FF0000)>>8;
			dmac_map->clear_srctran_l_ = (ch_num & 0x00FF0000)>>8;
			dmac_map->clear_dsttran_l_ = (ch_num & 0x00FF0000)>>8;
			dmac_map->clear_err_l_ = (ch_num & 0x00FF0000)>>8;
		}
		return 0;
	}
	else if(channel_num == 16)
	{
		if(ch_irq == Dmac_irq_none)
		{}
		else if(ch_irq == Dmac_irq_tfr)
		{
			dmac_map->clear_tfr_l_ = (0x00FFFF);
		}
		else if(ch_irq == Dmac_irq_block)
		{
			dmac_map->clear_block_l_ = (0x00FFFF);
		}
		else if(ch_irq == Dmac_irq_srctran)
		{
			dmac_map->clear_srctran_l_ = (0x00FFFF);
		}
		else if(ch_irq == Dmac_irq_dsttran)
		{
			dmac_map->clear_dsttran_l_ = (0x00FFFF);
		}
		else if(ch_irq == Dmac_irq_err)
		{
			dmac_map->clear_err_l_ = (0x00FFFF);
		}
		else if(ch_irq == Dmac_irq_all)
		{
			dmac_map->clear_tfr_l_ = (0x00FFFF);
			dmac_map->clear_block_l_ = (0x00FFFF);
			dmac_map->clear_srctran_l_ = (0x00FFFF);
			dmac_map->clear_dsttran_l_ = (0x00FFFF);
			dmac_map->clear_err_l_ = (0x00FFFF);
		}
		return 0;
	}
	return RTK_ECHRNG;
}

uint32_t rtk_dmac_set_chn_config(struct rtk_device_struct *dev, 
	enum rtk_dmac_chn_num_enum ch_num,
	struct rtk_dmac_chn_config_struct *ch_config1)
{
	uint32_t info;
	//uint32_t transfer_type = 0;
	info = rtk_dmac_set_addr(dev, ch_num, Dmac_src, ch_config1->sar);
	if(info != 0)
		printf("\3.a is not correct \n");
	info = rtk_dmac_set_addr(dev, ch_num, Dmac_dst, ch_config1->sar);
	if(info != 0)
		printf("\3.b is not correct \n");

	info = rtk_dmac_set_block_size(dev, ch_num, ch_config1->ctl_block_ts);
	if (info != 0)
		printf("\3 block size is not correct \n");

	info = rtk_dmac_set_llp_loc(dev, ch_num,((ch_config1->llp_loc)|
											  ch_config1->llp_lms));
	if(info != 0)
		printf("3.c LLP is not correct! \n");

	info = rtk_dmac_set_tt_fc(dev, ch_num, ch_config1->ctl_tt_fc);
	if(info !=0)
		printf("3.d.i is not correct \n");

	info = rtk_dmac_set_trans_width(dev, ch_num, Dmac_src, ch_config1->ctl_src_tr_width);
	if(info != 0)
		printf("3.d.ii tr_src_width is not correct!\n");

	info = rtk_dmac_set_trans_width(dev, ch_num, Dmac_dst, ch_config1->ctl_dst_tr_width);
	if(info != 0)
		printf("3.d.ii tr_dst_width is not correct!\n");

	info = rtk_dmac_set_mas_sel(dev, ch_num, Dmac_src, ch_config1->ctl_sms);
	if(info != 0)
		printf("3.d.ii ctl_sms is not correct!\n");	

	info = rtk_dmac_set_mas_sel(dev, ch_num, Dmac_dst, ch_config1->ctl_dms);
	if(info != 0)
		printf("3.d.ii ctl_dms is not correct!\n");	

	info = rtk_dmac_set_msize(dev, ch_num, Dmac_src, ch_config1->ctl_src_msize);
	if(info != 0)
		printf("3.d.ii ctl_src_msize is not correct!\n");	

	info = rtk_dmac_set_msize(dev, ch_num, Dmac_dst, ch_config1->ctl_dst_msize);
	if(info != 0)
		printf("3.d.ii ctl_dst_msize is not correct!\n");	

	info = rtk_dmac_set_addr_inc(dev, ch_num, Dmac_src, ch_config1->ctl_sinc);
	if(info != 0)
		printf("3.d.ii ctl_sinc is not correct!\n");	

	info = rtk_dmac_set_addr_inc(dev, ch_num, Dmac_dst, ch_config1->ctl_dinc);
	if(info != 0)
		printf("3.d.ii ctl_dinc is not correct!\n");	

	info = rtk_dmac_set_hs_inter(dev, ch_num, Dmac_src, ch_config1->cfg_src_per);
	if(info != 0)
		printf("3.d.ii cfg_src_per is not correct!\n");

	info = rtk_dmac_set_hs_inter(dev, ch_num, Dmac_dst, ch_config1->cfg_dst_per);
	if(info != 0)
		printf("3.d.ii cfg_dst_per is not correct!\n");

	info = rtk_dmac_set_fifo_mode(dev, ch_num, ch_config1->cfg_fifo_mode);
	if(info != 0)
		printf("3.d.ii cfg_fifo_mode is not correct!\n");

	info = rtk_dmac_set_hs_type(dev, ch_num, Dmac_src, ch_config1->cfg_hs_sel_src);
	if(info != 0)
		printf("3.d.ii cfg_hs_sel_src is not correct!\n");

	info = rtk_dmac_set_hs_type(dev, ch_num, Dmac_dst, ch_config1->cfg_hs_sel_dst);
	if(info != 0)
		printf("3.d.ii cfg_hs_sel_dst is not correct!\n");

	if(ch_config1->ctl_src_gather_en)
	{
		info = rtk_dmac_gat_en(dev, ch_num, ch_config1->ctl_src_gather_en);
		if(info != 0)
			printf("3.d.ii ctl_src_gather_en is not correct!\n");
	}

	if(ch_config1->ctl_dst_scatter_en)
	{
		info = rtk_dmac_set_sca_en(dev, ch_num, ch_config1->ctl_dst_scatter_en);
		if(info != 0)
			printf("3.d.ii ctl_dst_scatter_en is not correct!\n");
	}

	info = rtk_dmac_setGatherIntervalCount(dev, ch_num,
										((ch_config1->sgr_sgc << 20)|
										  ch_config1->sgr_sgi)
											);
	if(info != 0)
		printf("3.c cfg_sgr is not correct!\n");

	info = rtk_dmac_setScatterIntervalCount(dev, ch_num,
										((ch_config1->dsr_dsc << 20)|
										  ch_config1->dsr_dsi)
											);
	if(info != 0)
		printf("3.c cfg_dsr is not correct!\n");

	info = rtk_dmac_set_prot_sec_mode(dev, ch_num, ch_config1->cfg_protctl);
	if(info != 0)
		printf("3 sec_mode is not correct!\n");

	if(ch_config1->ctl_wrnp_en)
	{
		info = rtk_dmac_setWrnpEnable(dev, ch_num, ch_config1->ctl_wrnp_en);
		if(info != 0)
			printf("3.c wrnp_en is not correct!\n");
	}

	info = rtk_dmac_set_int_en(dev, ch_num, ch_config1->ctl_int_en);
	if(info != 0)
		printf("3.c ctl int_en is not correct!\n");

	if(ch_config1->cfg_reload_dst)
	{
		info = rtk_dmac_set_reload(dev, ch_num, Dmac_dst, ch_config1->cfg_reload_dst);
		if(info != 0)
			printf(" Set dst reload is not correct!\n");
	}

	if(ch_config1->cfg_reload_src)
	{
		info = rtk_dmac_set_reload(dev, ch_num, Dmac_src, ch_config1->cfg_reload_src);
		if(info != 0)
			printf(" Set src reload is not correct!\n");
	}

	info = rtk_dmac_set_chn_pri(dev, ch_num, ch_config1->cfg_ch_prior);
	if(info != 0)
		printf(" 3.e cfg_ch_prior is not correct!\n");

	return 0;
}

uint32_t rtk_dmac_set_addr(struct rtk_device_struct * dev,
	enum rtk_dmac_chn_num_enum ch_num,
	enum rtk_dmac_src_dst_sel_enum sd_sel,
	uint32_t address)
{
	//unsigned int channel_num;
	ch_num =0;
	//struct rtk_dmac_regmap_struct *dmac_map;
	dmac_map = dev->base_address;
	if(sd_sel == Dmac_src)
	{
		dmac_map->ch[0].sar_l =address;
	}
	if(sd_sel == Dmac_dst)
	{
		dmac_map->ch[0].dar_l = address;
	}
	return 0;
}

uint32_t rtk_dmac_set_block_size(struct rtk_device_struct *dev,
	enum rtk_dmac_chn_num_enum ch_num, uint32_t block_size)
{
	//int info;
	ch_num=0;
	//struct rtk_dmac_regmap_struct *dmac_map;
	dmac_map = dev->base_address;
	RTK_BITS_SET_VAL(dmac_map->ch[0].ctl_h,bit_off_RTK_DMAC_CTL_H_BLOCK_TS,
		block_size, bit_wid_RTK_DMAC_CTL_H_BLOCK_TS);
	return 0;
}

uint32_t rtk_dmac_set_llp_loc(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num, uint32_t address)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev,ch_num);
	if(channel_num < 8)
	{
		dmac_map->ch[channel_num].llp_l = address;
		return 0;
	}
	else if(channel_num < 16)
	{
		dmac_map->ch8[channel_num-8].llp_l = address;
		return 0;
	}
	else
		return RTK_EBUSY;
}

unsigned rtk_dmac_get_chn_index(struct rtk_device_struct *dev, enum rtk_dmac_chn_num_enum ch_num)
{
	struct rtk_dmac_param_struct *dmac_para;
	int get_num;
	unsigned int channel_num;
	dmac_para = dev->comp_param;
	for(channel_num = 1, get_num = 0;channel_num <= dmac_para->num_channels;channel_num++)
	{
		if(ch_num == channel_val[channel_num])
		{
			get_num = 1;
			break;
		}

	}
	if(get_num==1)
		return (channel_num-1);
	else
		return 16;
}

uint32_t rtk_dmac_set_tt_fc(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum dw_dmac_transfer_flow tt_fc)
{
	unsigned int channel_num;
	//int info = 0;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev,ch_num);
	if(channel_num < 8)
	{
		if(tt_fc < 0x8)
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_TT_FC,
				tt_fc, bit_wid_RTK_DMAC_CTL_L_TT_FC);
			return 0;
		}
		else
			return RTK_EPERM;
	}
	else if(channel_num < 16)
	{
		if(tt_fc < 0x8)
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_TT_FC,
				tt_fc, bit_wid_RTK_DMAC_CTL_L_TT_FC);
			return 0;
		}
		else
			return RTK_EPERM;
	}
	else
		return RTK_EPERM;

}

uint32_t rtk_dmac_set_trans_width(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum dw_dmac_transfer_width xf_width)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_SRC_TR_WIDTH,
				xf_width, bit_wid_RTK_DMAC_CTL_L_SRC_TR_WIDTH);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_DST_TR_WIDTH,
			xf_width, bit_wid_RTK_DMAC_CTL_L_DST_TR_WIDTH);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_SRC_TR_WIDTH,
				xf_width, bit_wid_RTK_DMAC_CTL_L_SRC_TR_WIDTH);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_DST_TR_WIDTH,
			xf_width, bit_wid_RTK_DMAC_CTL_L_DST_TR_WIDTH);
		}
		return 0;
	}
	else
		return RTK_ECHRNG;
}

uint32_t rtk_dmac_set_mas_sel(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum rtk_dmac_mas_num_enum mst_num)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_SMS,
				mst_num, bit_wid_RTK_DMAC_CTL_L_SMS);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_DMS,
			mst_num, bit_wid_RTK_DMAC_CTL_L_DMS);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_SMS,
				mst_num, bit_wid_RTK_DMAC_CTL_L_SMS);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_DMS,
			mst_num, bit_wid_RTK_DMAC_CTL_L_DMS);
		}
		return 0;
	}
	else
		return RTK_ECHRNG;

}
		
uint32_t rtk_dmac_set_msize(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum dw_dmac_burst_trans_length xf_length)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_SRC_MSIZE,
				xf_length, bit_wid_RTK_DMAC_CTL_L_SRC_MSIZE);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_DEST_MSIZE,
			xf_length, bit_wid_RTK_DMAC_CTL_L_DEST_MSIZE);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_SRC_MSIZE,
				xf_length, bit_wid_RTK_DMAC_CTL_L_SRC_MSIZE);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_DEST_MSIZE,
			xf_length, bit_wid_RTK_DMAC_CTL_L_DEST_MSIZE);
		}
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_addr_inc(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum dw_dmac_address_increment addr_inc)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_SINC,
				addr_inc, bit_wid_RTK_DMAC_CTL_L_SINC);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_DINC,
			addr_inc, bit_wid_RTK_DMAC_CTL_L_DINC);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_SINC,
				addr_inc, bit_wid_RTK_DMAC_CTL_L_SINC);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_DINC,
			addr_inc, bit_wid_RTK_DMAC_CTL_L_DINC);
		}
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_hs_inter(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum rtk_dmac_hs_inter_num_sel_enum hs_inter)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	struct rtk_dmac_param_struct *dmac_para;
	dmac_para = dev->comp_param;
	if(hs_inter >= dmac_para->num_hs_int)
	{
		return RTK_EINVAL;
	}
	if(ch_num == Dmac_no_channel)
	{
		return RTK_ECHRNG;
	}
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_SRC_PER,
				hs_inter, bit_wid_RTK_DMAC_CFG_H_SRC_PER);
			if(((hs_inter >=16)&&(hs_inter<=31)) || ((hs_inter >=48)&&(hs_inter<=63)))
			{
				RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_SRC_PER_EXT1,
				1, bit_wid_RTK_DMAC_CFG_H_SRC_PER_EXT1);
			}
			if((hs_inter >=32)&&(hs_inter<=63))
			{
				RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_SRC_PER_EXT2,
				1, bit_wid_RTK_DMAC_CFG_H_SRC_PER_EXT2);
			}
			printf("[ok] CFG = %08x\n",dmac_map->ch[channel_num].cfg_h);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_DEST_PER,
			hs_inter, bit_wid_RTK_DMAC_CFG_H_DEST_PER);
			if(((hs_inter >=16)&&(hs_inter<=31)) || ((hs_inter >=48)&&(hs_inter<=63)))
			{
				RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_DEST_PER_EXT1,
				1, bit_wid_RTK_DMAC_CFG_H_DEST_PER_EXT1);
			}
			if((hs_inter >=32)&&(hs_inter<=63))
			{
				RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_DEST_PER_EXT2,
				1, bit_wid_RTK_DMAC_CFG_H_DEST_PER_EXT2);
			}
			printf("[ok] CFG = %08x\n",dmac_map->ch[channel_num].cfg_h);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_SRC_PER,
				hs_inter, bit_wid_RTK_DMAC_CFG_H_SRC_PER);
			if(((hs_inter >=16)&&(hs_inter<=31)) || ((hs_inter >=48)&&(hs_inter<=63)))
			{
				RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_SRC_PER_EXT1,
				1, bit_wid_RTK_DMAC_CFG_H_SRC_PER_EXT1);
			}
			if((hs_inter >=32)&&(hs_inter<=63))
			{
				RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_SRC_PER_EXT2,
				1, bit_wid_RTK_DMAC_CFG_H_SRC_PER_EXT2);
			}
			printf("[ok] CFG = %08x\n",dmac_map->ch8[channel_num-8].cfg_h);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_DEST_PER,
			hs_inter, bit_wid_RTK_DMAC_CFG_H_DEST_PER);
			if(((hs_inter >=16)&&(hs_inter<=31)) || ((hs_inter >=48)&&(hs_inter<=63)))
			{
				RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_DEST_PER_EXT1,
				1, bit_wid_RTK_DMAC_CFG_H_DEST_PER_EXT1);
			}
			if((hs_inter >=32)&&(hs_inter<=63))
			{
				RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_DEST_PER_EXT2,
				1, bit_wid_RTK_DMAC_CFG_H_DEST_PER_EXT2);
			}
		}
		printf("[ok] CFG = %08x\n",dmac_map->ch8[channel_num-8].cfg_h);
		return 0;
	}
	else
	{
		printf("[error] HS per setting:channel_num bigger than 8\n");
		return RTK_ECHRNG;
	}
}

uint32_t rtk_dmac_set_fifo_mode(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_fifo_mode_enum fifo_mode)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_h, bit_off_RTK_DMAC_CFG_H_FIFO_MODE,
			fifo_mode, bit_wid_RTK_DMAC_CFG_H_FIFO_MODE);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_h, bit_off_RTK_DMAC_CFG_H_FIFO_MODE,
			fifo_mode, bit_wid_RTK_DMAC_CFG_H_FIFO_MODE);
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_hs_type(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum rtk_dmac_hs_type_sel_enum hs_hwsw_sel)
{
	unsigned int channel_num;
	//int info;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_l, bit_off_RTK_DMAC_CFG_L_HS_SEL_SRC,
				hs_hwsw_sel, bit_wid_RTK_DMAC_CFG_L_HS_SEL_SRC);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_l, bit_off_RTK_DMAC_CFG_L_HS_SEL_DST,
			hs_hwsw_sel, bit_wid_RTK_DMAC_CFG_L_HS_SEL_DST);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_l, bit_off_RTK_DMAC_CFG_L_HS_SEL_SRC,
				hs_hwsw_sel, bit_wid_RTK_DMAC_CFG_L_HS_SEL_SRC);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_l, bit_off_RTK_DMAC_CFG_L_HS_SEL_DST,
			hs_hwsw_sel, bit_wid_RTK_DMAC_CFG_L_HS_SEL_DST);
		}
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_gat_en(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_state_enum state)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_SRC_GATHER_EN,
			state, bit_wid_RTK_DMAC_CTL_L_SRC_GATHER_EN);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_SRC_GATHER_EN,
			state, bit_wid_RTK_DMAC_CTL_L_SRC_GATHER_EN);
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_sca_en(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_state_enum state)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_DST_SCATTER_EN,
			state, bit_wid_RTK_DMAC_CTL_L_DST_SCATTER_EN);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_DST_SCATTER_EN,
			state, bit_wid_RTK_DMAC_CTL_L_DST_SCATTER_EN);
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_setGatherIntervalCount(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num, uint32_t sgr)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		dmac_map->ch[channel_num].sgr_l = sgr; 
		return 0;
	}
	else if(channel_num < 16)
	{
		dmac_map->ch8[channel_num-8].sgr_l = sgr;
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_setScatterIntervalCount(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num, uint32_t dsr)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		dmac_map->ch[channel_num].dsr_l = dsr; 
		return 0;
	}
	else if(channel_num < 16)
	{
		dmac_map->ch8[channel_num-8].dsr_l = dsr;
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_prot_sec_mode(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_prot_sec_mod_en_enum prot_lvl)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	uint32_t temp;
	prot_lvl = 0;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		temp = dmac_map->ch[channel_num].cfg_h;
		temp &= (uint32_t)~(0x1<<3);
		dmac_map->ch[channel_num].cfg_h = temp;
		return 0;
	}
	else if(channel_num < 16)
	{
		temp = dmac_map->ch8[channel_num].cfg_h;
		temp &= (uint32_t)~(0x1<<3);
		dmac_map->ch8[channel_num-8].cfg_h = temp;
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_setWrnpEnable(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_state_enum state)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_WRNP_EN,
			state, bit_wid_RTK_DMAC_CTL_L_WRNP_EN);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_WRNP_EN,
			state, bit_wid_RTK_DMAC_CTL_L_WRNP_EN);
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_int_en(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_state_enum state)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_INT_EN,
			state, bit_wid_RTK_DMAC_CTL_L_INT_EN);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_INT_EN,
			state, bit_wid_RTK_DMAC_CTL_L_INT_EN);
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_reload(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_src_dst_sel_enum sd_sel,
		enum rtk_state_enum state)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_l, bit_off_RTK_DMAC_CFG_L_RELOAD_SRC,
				state, bit_wid_RTK_DMAC_CFG_L_RELOAD_SRC);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_l, bit_off_RTK_DMAC_CFG_L_RELOAD_DST,
			state, bit_wid_RTK_DMAC_CFG_L_RELOAD_DST);
		}
		return 0;
	}
	else if(channel_num < 16)
	{
		if((sd_sel == Dmac_src) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_l, bit_off_RTK_DMAC_CFG_L_RELOAD_SRC,
				state, bit_wid_RTK_DMAC_CFG_L_RELOAD_SRC);
		}
		if((sd_sel == Dmac_dst) || (sd_sel == Dmac_src_dst))
		{
			RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].cfg_l, bit_off_RTK_DMAC_CFG_L_RELOAD_DST,
			state, bit_wid_RTK_DMAC_CFG_L_RELOAD_DST);
		}
		return 0;
	}
	else
		return RTK_EBUSY;


}

uint32_t rtk_dmac_set_chn_pri(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_chn_pri_enum ch_priority)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].cfg_l, bit_off_RTK_DMAC_CFG_L_CH_PRIOR,
			ch_priority, bit_wid_RTK_DMAC_CFG_L_CH_PRIOR);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CFG_L_CH_PRIOR,
			ch_priority, bit_wid_RTK_DMAC_CFG_L_CH_PRIOR);
		return 0;
	}
	else
		return RTK_ECHRNG;

}

uint32_t rtk_dmac_set_lalu_block(struct rtk_device_struct *dev,
	enum rtk_dmac_chn_num_enum ch_num,
	struct rtk_dmac_chn_config_struct *ch_config1)
{
	//int info;
	ch_num = 0;
	//struct rtk_dmac_regmap_struct *dmac_map;
	dmac_map = dev->base_address;
	dmac_map->ch[0].sar_l = ch_config1->sar;
	dmac_map->ch[0].dar_l = ch_config1->dar;

	//printf("dmac_map = %x\n",dmac_map);
	//printf("dmac_map->ch[0].sar_l = %x\n",dmac_map->ch[0].sar_l);
	//printf("dmac_map->ch[0].dar_l = %x\n",dmac_map->ch[0].dar_l);
	RTK_BITS_SET_VAL(dmac_map->ch[0].ctl_h, bit_off_RTK_DMAC_CTL_H_BLOCK_TS,
					ch_config1->ctl_block_ts, bit_wid_RTK_DMAC_CTL_H_BLOCK_TS);

	return 0;
}

uint32_t rtk_dmac_set_aes(struct rtk_device_struct *dev,
	enum rtk_dmac_chn_num_enum ch_num,
	struct rtk_dmac_chn_config_struct *ch_config1)
{
	uint32_t temp;
	struct rtk_device_struct* temp1;
	temp1 = dev;
	ch_num = 0;
	//struct rtk_dmac_aes_regmap_struct *dmac_aes_map;
	dmac_aes_map = (struct rtk_dmac_aes_regmap_struct *) SEC_BASE;
	temp = dmac_aes_map->ch_aes[0].config;

	//---------------------------------------------------------------------
	if(ch_config1->aes_dma_mode == RTK_set)
		temp |= (0x1<<0);
	else
		temp &= (uint32_t)~(0x1<<0);

	//---------------------------------------------------------------------
	if(ch_config1->aes_cipher_mode == CBC_mode)
	{
		temp |= (0x1<<1);
		temp &= (uint32_t)~(0x7<<2);
	}
	else if(ch_config1->aes_cipher_mode == CFB_mode)
	{
		temp &= (uint32_t)~(0x1<<1);
		temp |= (0x1<<2);
		temp &= (uint32_t)~(0x3<<3);
	}
	else if(ch_config1->aes_cipher_mode == OFB_mode)
	{
		temp |= (0x3<<1);
		temp &= (uint32_t)~(0x3<<3);
	}
	else if(ch_config1->aes_cipher_mode == CTR_mode)
	{
		temp &= (uint32_t)~(0x3<<1);
		temp |= (0x1<<3);
		temp &= (uint32_t)~(0x1<<4);
	}
	else if(ch_config1->aes_cipher_mode == GMAC_mode)
	{
		temp |= (0x1<<1);
		temp &= (uint32_t)~(0x1<<2);
		temp |= (0x1<<3);
		temp &= (uint32_t)~(0x1<<4);
	}
	else if(ch_config1->aes_cipher_mode == GCM_mode)
	{
		temp &= (uint32_t)~(0x1<<1);
		temp |= (0x3<<2);
		temp &= (uint32_t)~(0x1<<4);
	}
	else if(ch_config1->aes_cipher_mode == CMAC_mode)
	{
		temp |= (0x7<<1);
		temp &= (uint32_t)~(0x1<<4);
	}
	else if(ch_config1->aes_cipher_mode == XTS_mode)
	{
		temp &= (uint32_t)~(0x7<<1);
		temp |= (0x1<<4);
	}
	else	// ECB
		temp &= (uint32_t)~(0xF<<1);

	//-------------------------------------------------------------------
	if(ch_config1->aes_ende == encrypt)
		temp |= (0x1<<7);
	else
		temp &= (uint32_t)~(0x1<<7);

	//-------------------------------------------------------------------
	if(ch_config1->aes_de_key_gen == RTK_set)
		temp |= (0x1<<9);
	else
		temp &= (uint32_t)~(0x1<<9);

	dmac_aes_map->ch_aes[0].config = temp;

	return 0;
}

uint32_t rtk_dmac_enableChannel(struct rtk_device_struct *dev,
	enum rtk_dmac_chn_num_enum ch_num)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	struct rtk_dmac_param_struct *dmac_para;
	dmac_para = dev->comp_param;
	dmac_map = dev->base_address;
	//printf("dmac_map = %08x\n", dmac_map);

	if(!dmac_map->dma_cfg_reg_l_)
	{
		printf("\n DMAC is not enable\n");
		return RTK_EPERM;
	}
	else
	{
		dmac_map->ch_en_reg_l_ = ch_num;
		//printf("dmac_channel enabled %08x\n", ch_num);
		//printf("dmac_map->ch_en_reg_l_ %08x\n", dmac_map->ch_en_reg_l_);
		return 0;
	}
}

uint32_t rtk_dmac_set_aes_first(struct rtk_device_struct *dev,
	enum rtk_dmac_chn_num_enum ch_num,
	enum rtk_state_enum aes_first)
{
	uint32_t temp;
	struct rtk_device_struct* temp1;
	temp1 = dev;
	//struct rtk_dmac_aes_regmap_struct *dmac_aes_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	//dmac_aes_map = (struct rtk_dmac_aes_regmap_struct*) SEC_BASE;
	temp = dmac_aes_map->ch_aes[0].config;
	//printf("temp  = %x\n", temp);
	//-------------------------------------------------------------------
	if(aes_first == RTK_set)
	{
		temp |= (0x1<<8);
		dmac_aes_map->ch_aes[0].config = temp;
		//printf("AES will start from the first block\n");
	}
	else
	{
		temp &= (uint32_t)~(0x1<<8);
		dmac_aes_map->ch_aes[0].config = temp;
		printf("AES will not start from the first block\n");
	}
	return 0;
}

bool rtk_dmac_is_enabled(struct rtk_device_struct *dev)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	dmac_map = dev->base_address;
	if((dmac_map->dma_cfg_reg_l_)!= 0)
		return 1;
	else
		return 0;
}

bool rtk_dmac_is_chn_enabled(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	unsigned int channel_num;
	unsigned int info;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	info = (unsigned int)(dmac_map->ch_en_reg_l_);
	info = info & ch_num;
	if(info)
	{
		printf("channel %08x is enabled \n", channel_num);
		return 1;
	}
	else
		return 0;
}

uint32_t rtk_dmac_enableChannelIrq(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num)
{
	unsigned int channel_num;
	//struct rtk_dmac_regmap_struct *dmac_map;

	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	dmac_map = dev->base_address;
	channel_num = rtk_dmac_get_chn_index(dev, ch_num);
	if(channel_num < 8)
	{
		RTK_BITS_SET_VAL(dmac_map->ch[channel_num].ctl_l, bit_off_RTK_DMAC_CTL_L_INT_EN,
			1, bit_wid_RTK_DMAC_CTL_L_INT_EN);
		return 0;
	}
	else if(channel_num < 16)
	{
		RTK_BITS_SET_VAL(dmac_map->ch8[channel_num-8].ctl_l, bit_off_RTK_DMAC_CTL_L_INT_EN,
			1, bit_wid_RTK_DMAC_CTL_L_INT_EN);
		return 0;
	}
	else
		return RTK_ECHRNG;
}

uint32_t rtk_dmac_unmaskIrq(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		enum rtk_dmac_irq_type_enum ch_irq)
{
	//struct rtk_dmac_regmap_struct *dmac_map;
	struct rtk_dmac_param_struct *dmac_para;
	unsigned int channel_num;
	printf("dmac_Un_mask rIRQ start\n");
	dmac_map = dev->base_address;
	dmac_para = dev->comp_param;

	channel_num = rtk_dmac_get_chn_index(dev,ch_num);

	if((ch_num!=Dmac_all_channels)&&(channel_num >= dmac_para->num_channels))
	{
		return RTK_ECHRNG;
	}
	else
	{
		if(ch_irq == Dmac_irq_none)
			{}
		else if(ch_irq == Dmac_irq_tfr)
		{
			dmac_map->mask_tfr_l_ = ch_num;
		}
		else if(ch_irq == Dmac_irq_block)
		{
			dmac_map->mask_block_l_ = ch_num;
		}
		else if(ch_irq == Dmac_irq_srctran)
		{
			dmac_map->mask_srctran_l_ = ch_num;
		}
		else if(ch_irq == Dmac_irq_dsttran)
		{
			dmac_map->mask_dsttran_l_ = ch_num;
		}
		else if(ch_irq == Dmac_irq_err)
		{
			dmac_map->mask_err_l_ = ch_num;
		}
		else if(ch_irq == Dmac_irq_all)
		{
			dmac_map->mask_tfr_l_ = ch_num;
			dmac_map->mask_block_l_ = ch_num;
			dmac_map->mask_srctran_l_ = ch_num;
			dmac_map->mask_dsttran_l_ = ch_num;
			dmac_map->mask_err_l_ = ch_num;
		}
		return 0;
	}
}

uint32_t rtk_dmac_aes_set_maskIrq(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		uint32_t mask)
{
	unsigned int channel_num;
	//uint32_t *addr;
	//uint32_t temp;
	//struct rtk_dmac_aes_int_and_constant_regmap_struct *dmac_aes_int_map;
	if(ch_num == Dmac_no_channel)
		return RTK_EBUSY;
	//dmac_aes_int_map = (struct rtk_dmac_aes_int_and_constant_regmap_struct*)(SEC_BASE+0xEE0);
	channel_num = rtk_dmac_get_chn_index(dev,ch_num);
	
	//-------------------------------------------------------------------------------
	dmac_aes_int_map->ch_aes[channel_num].mask_aes = mask;
	return 0;
}

uint32_t rtk_dmac_init_config_reg(struct rtk_device_struct *dev,
		enum rtk_dmac_chn_num_enum ch_num,
		struct rtk_dmac_chn_config_struct *ch_config1)
{
	uint32_t info;

	info = rtk_dmac_set_trans_width(dev, ch_num, Dmac_src, ch_config1->ctl_src_tr_width);
	if(info != 0)
		printf(" tr_src_width is not correct!\n");

	info = rtk_dmac_set_trans_width(dev, ch_num, Dmac_dst, ch_config1->ctl_dst_tr_width);
	if(info != 0)
		printf(" tr_dst_width is not correct!\n");	

	info = rtk_dmac_set_msize(dev, ch_num, Dmac_src, ch_config1->ctl_src_msize);
	if(info != 0)
		printf(" ctl_src_msize is not correct!\n");	

	info = rtk_dmac_set_msize(dev, ch_num, Dmac_dst, ch_config1->ctl_dst_msize);
	if(info != 0)
		printf(" ctl_dst_msize is not correct!\n");	

	info = rtk_dmac_set_fifo_mode(dev, ch_num, ch_config1->cfg_fifo_mode);
	if(info != 0)
		printf(" cfg_fifo_mode is not correct!\n");

	info = rtk_dmac_set_prot_sec_mode(dev, ch_num, ch_config1->cfg_protctl);
	if(info != 0)
		printf(" sec_mode is not correct!\n");

	info = rtk_dmac_set_int_en(dev, ch_num, ch_config1->ctl_int_en);
	if(info != 0)
		printf(" ctl int_en set is not correct!\n");

	return 0;
}

void Initaesdma(void)
{
	dmac_param = (struct rtk_dmac_param_struct)RTK_DEFINE_DMAC_PARAMS();
	ch_config = (struct rtk_dmac_chn_config_struct)RTK_CHN_CONFIG_DEFAULT_DEFINE_PARAMS;
	dmac_map = (struct rtk_dmac_regmap_struct *)RTK_LALU_AES_REG_BASE;
	dmac_aes_map = (struct rtk_dmac_aes_regmap_struct *) RTK_LALU_AES_DMAC_BASE;
	dmac0.dmac0.base_address = (uint32_t *) RTK_LALU_AES_DMAC_BASE;
	dmac0.dmac0.comp_param = &dmac_param;
	dmac_aes_int_map = (struct rtk_dmac_aes_int_and_constant_regmap_struct*)(SEC_BASE+0xEE0);
	RTK_dmac(&dmac0);
}

