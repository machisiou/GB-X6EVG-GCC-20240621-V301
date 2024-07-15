#ifndef __RTK_DMAC_Private_H__
#define __RTK_DMAC_Private_H__

#define DMAC_COMMON_REQUIREMENTS(p)		\
do{										\
	RTK_REQUIRE(p!=NULL);				\
	RTK_REQUIRE(p->instance!=NULL);		\
	RTK_REQUIRE(p->comp_param!=NULL);	\
	RTK_REQUIRE(p->base_address!=NULL);	\
	RTK_REQUIRE(p->comp_type!=NULL);	\
}while(0)

#define DMAC_MAX_CHANNELS	16

#define DMAH_NUM_CHANNELS(prefix)		prefix ## _CC_DMAH_NUM_CHANNELS
#define DMAH_MABRST(prefix)				prefix ## _CC_DMAH_MABRST
#define DMAH_M1_HDATA_WIDTH(prefix)		prefix ## _CC_DMAH_M1_HDATA_WIDTH
#define	DMAH_CH0_MAX_BLK_SIZE(prefix)	prefix ## _CC_DMAH_CH0_MAX_BLK_SIZE
#define DMAH_NUM_HS_INT(prefix)			prefix ## _CC_DMAH_NUM_HS_INT

#define DMAC_MAX_INTERRRUPTS	5

#define DMAC_DMA_FC_ONLY		0x0
#define DMAC_SRC_FC_ONLY		0x1
#define DMAC_DST_FC_ONLY		0x2
#define DMAC_ANY_FC				0x3

#define DMAC_MAX_CH_MASK	\
		(~(~0 << DMAC_MAX_CHANNELS))

#define DMAC_CH_MASK	\
		(DMAC_MAX_CH_MASK & (DMAC_MAX_CH_MASK << param-> num_channels))

#define DMAC_CH_EN_MASK	\
		(DMAC_MAX_CH_MASK & ~(DMAC_CH_MASK))

#define DMAC_CH_ALL_MASK	\
		((DMAC_CH_EN_MASK) + ((DMAC_CH_EN_MASK) << DMAC_MAX_CHANNELS))

#define DMAC_CH_NUM(ch_idx)		(0x101 << (ch_idx))

#define POW2(pow)	\
	(1 << (pow))

#define A_MAXEQ_B(a,b)	\
	((a) >= (b))

#define bit_off_RTK_DMAC_DMACFGREG_L_DMA_EN		((uint32_t)	0)
#define bit_wid_RTK_DMAC_DMACFGREG_L_DMA_EN		((uint32_t)	1)

#define bit_off_RTK_DMAC_CHENREG_L_EN(ch)		((uint32_t)	(ch))
#define bit_wid_RTK_DMAC_CHENREG_L_EN(ch)		((uint32_t)	1)
#define bit_off_RTK_DMAC_CHENREG_L_EN_ALL		((uint32_t)	0)
#define bit_WID_RTK_DMAC_CHENREG_L_EN_ALL		((uint32_t)	8)

#define bit_off_RTK_DMAC_CHENREG_L_EN_WE(ch)		((uint32_t)	(ch)+8)
#define bit_wid_RTK_DMAC_CHENREG_L_EN_WE(ch)		((uint32_t)	1)
#define bit_off_RTK_DMAC_CHENREG_L_EN_WE_ALL		((uint32_t)	8)
#define bit_WID_RTK_DMAC_CHENREG_L_EN_WE_ALL		((uint32_t)	8)

#define bit_off_RTK_DMAC_SAR_L_SAR				((uint32_t)	0)
#define bit_wid_RTK_DMAC_SAR_L_SAR				((uint32_t)	32)
#define bit_off_RTK_DMAC_DAR_L_SAR				((uint32_t)	0)
#define bit_wid_RTK_DMAC_DAR_L_SAR				((uint32_t)	32)

#define bit_off_RTK_DMAC_LLP_L_LMS				((uint32_t)	0)
#define bit_wid_RTK_DMAC_LLP_L_LMS				((uint32_t)	2)
#define bit_off_RTK_DMAC_LLP_L_LOC				((uint32_t)	2)
#define bit_wid_RTK_DMAC_LLP_L_LOC				((uint32_t)	30)

#define bit_off_RTK_DMAC_CTL_L_INT_EN			((uint32_t)	0)
#define bit_wid_RTK_DMAC_CTL_L_INT_EN			((uint32_t)	1)
#define bit_off_RTK_DMAC_CTL_L_DST_TR_WIDTH		((uint32_t)	1)
#define bit_wid_RTK_DMAC_CTL_L_DST_TR_WIDTH		((uint32_t)	3)
#define bit_off_RTK_DMAC_CTL_L_SRC_TR_WIDTH		((uint32_t)	4)
#define bit_wid_RTK_DMAC_CTL_L_SRC_TR_WIDTH		((uint32_t)	3)
#define bit_off_RTK_DMAC_CTL_L_DINC				((uint32_t)	7)
#define bit_wid_RTK_DMAC_CTL_L_DINC				((uint32_t)	2)
#define bit_off_RTK_DMAC_CTL_L_SINC				((uint32_t)	9)
#define bit_wid_RTK_DMAC_CTL_L_SINC				((uint32_t)	2)
#define bit_off_RTK_DMAC_CTL_L_DEST_MSIZE		((uint32_t) 11)
#define bit_wid_RTK_DMAC_CTL_L_DEST_MSIZE		((uint32_t) 3)
#define bit_off_RTK_DMAC_CTL_L_SRC_MSIZE		((uint32_t) 14)
#define bit_wid_RTK_DMAC_CTL_L_SRC_MSIZE		((uint32_t) 3)
#define bit_off_RTK_DMAC_CTL_L_SRC_GATHER_EN	((uint32_t) 17)
#define bit_wid_RTK_DMAC_CTL_L_SRC_GATHER_EN	((uint32_t) 1)
#define bit_off_RTK_DMAC_CTL_L_DST_SCATTER_EN	((uint32_t) 18)
#define bit_wid_RTK_DMAC_CTL_L_DST_SCATTER_EN	((uint32_t) 1)
#define bit_off_RTK_DMAC_CTL_L_WRNP_EN			((uint32_t) 19)
#define bit_wid_RTK_DMAC_CTL_L_WRNP_EN			((uint32_t) 1)
#define bit_off_RTK_DMAC_CTL_L_TT_FC			((uint32_t) 20)
#define bit_wid_RTK_DMAC_CTL_L_TT_FC			((uint32_t) 3)
#define bit_off_RTK_DMAC_CTL_L_DMS				((uint32_t) 23)
#define bit_wid_RTK_DMAC_CTL_L_DMS				((uint32_t) 2)
#define bit_off_RTK_DMAC_CTL_L_SMS				((uint32_t) 25)
#define bit_wid_RTK_DMAC_CTL_L_SMS				((uint32_t) 2)
#define bit_off_RTK_DMAC_CTL_L_LLP_DST_EN		((uint32_t) 27)
#define bit_wid_RTK_DMAC_CTL_L_LLP_DST_EN		((uint32_t) 1)
#define bit_off_RTK_DMAC_CTL_L_LLP_SRC_EN		((uint32_t) 28)
#define bit_wid_RTK_DMAC_CTL_L_LLP_SRC_EN		((uint32_t) 1)

#define bit_off_RTK_DMAC_CTL_H_BLOCK_TS			((uint32_t) 0)
#define bit_wid_RTK_DMAC_CTL_H_BLOCK_TS			((uint32_t) 12)
#define bit_off_RTK_DMAC_CTL_H_DONE				((uint32_t) 12)
#define bit_wid_RTK_DMAC_CTL_H_DONE				((uint32_t) 1)

#define bit_off_RTK_DMAC_SSTAT_L_SSTAT			((uint32_t) 0)
#define bit_wid_RTK_DMAC_SSTAT_L_SSTAT			((uint32_t) 32)

#define bit_off_RTK_DMAC_DSTAT_L_DSTAT			((uint32_t) 0)
#define bit_wid_RTK_DMAC_DSTAT_L_DSTAT			((uint32_t) 32)

#define bit_off_RTK_DMAC_SSTATR_L_SSTATR		((uint32_t) 0)
#define bit_wid_RTK_DMAC_SSTATR_L_SSTATR		((uint32_t) 32)

#define bit_off_RTK_DMAC_DSTATR_L_DSTATR		((uint32_t) 0)
#define bit_wid_RTK_DMAC_DSTATR_L_DSTATR		((uint32_t) 32)

#define bit_off_RTK_DMAC_CFG_L_INACTIVE			((uint32_t) 0)
#define bit_wid_RTK_DMAC_CFG_L_INACTIVE			((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_SRC_PCTL_OVER	((uint32_t) 1)
#define bit_wid_RTK_DMAC_CFG_L_SRC_PCTL_OVER	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_DST_PCTL_OVER	((uint32_t) 2)
#define bit_wid_RTK_DMAC_CFG_L_DST_PCTL_OVER	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_CH_PRIOR			((uint32_t) 4)
#define bit_wid_RTK_DMAC_CFG_L_CH_PRIOR			((uint32_t) 4)
#define bit_off_RTK_DMAC_CFG_L_CH_SUSP			((uint32_t) 8)
#define bit_wid_RTK_DMAC_CFG_L_CH_SUSP			((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_FIFO_EMPTY		((uint32_t) 9)
#define bit_wid_RTK_DMAC_CFG_L_FIFO_EMPTY		((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_HS_SEL_DST		((uint32_t) 10)
#define bit_wid_RTK_DMAC_CFG_L_HS_SEL_DST		((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_HS_SEL_SRC		((uint32_t) 11)
#define bit_wid_RTK_DMAC_CFG_L_HS_SEL_SRC		((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_LOCK_CH_L		((uint32_t) 12)
#define bit_wid_RTK_DMAC_CFG_L_LOCK_CH_L		((uint32_t) 2)
#define bit_off_RTK_DMAC_CFG_L_LOCK_B_L			((uint32_t) 14)
#define bit_wid_RTK_DMAC_CFG_L_LOCK_B_L			((uint32_t) 2)
#define bit_off_RTK_DMAC_CFG_L_LOCK_CH			((uint32_t) 16)
#define bit_wid_RTK_DMAC_CFG_L_LOCK_CH			((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_LOCK_B			((uint32_t) 17)
#define bit_wid_RTK_DMAC_CFG_L_LOCK_B			((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_DST_HS_POL		((uint32_t) 18)
#define bit_wid_RTK_DMAC_CFG_L_DST_HS_POL		((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_SRC_HS_POL		((uint32_t) 19)
#define bit_wid_RTK_DMAC_CFG_L_SRC_HS_POL		((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_MAX_ABRST		((uint32_t) 20)
#define bit_wid_RTK_DMAC_CFG_L_MAX_ABRST		((uint32_t) 10)
#define bit_off_RTK_DMAC_CFG_L_RELOAD_SRC		((uint32_t) 30)
#define bit_wid_RTK_DMAC_CFG_L_RELOAD_SRC		((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_L_RELOAD_DST		((uint32_t) 31)
#define bit_wid_RTK_DMAC_CFG_L_RELOAD_DST		((uint32_t) 1)

#define bit_off_RTK_DMAC_CFG_H_FCMODE		((uint32_t) 0)
#define bit_wid_RTK_DMAC_CFG_H_FCMODE		((uint32_t) 1)

#define bit_off_RTK_DMAC_CFG_H_FIFO_MODE	((uint32_t) 1)
#define bit_wid_RTK_DMAC_CFG_H_FIFO_MODE	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_H_PROTCTL		((uint32_t) 2)
#define bit_wid_RTK_DMAC_CFG_H_PROTCTL		((uint32_t) 3)
#define bit_off_RTK_DMAC_CFG_H_DS_UPD_EN	((uint32_t) 5)
#define bit_wid_RTK_DMAC_CFG_H_DS_UPD_EN	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_H_SS_UPD_EN	((uint32_t) 6)
#define bit_wid_RTK_DMAC_CFG_H_SS_UPD_EN	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_H_SRC_PER		((uint32_t) 7)
#define bit_wid_RTK_DMAC_CFG_H_SRC_PER		((uint32_t) 4)
#define bit_off_RTK_DMAC_CFG_H_DEST_PER		((uint32_t)11)
#define bit_wid_RTK_DMAC_CFG_H_DEST_PER		((uint32_t) 4)
#define bit_off_RTK_DMAC_CFG_H_SRC_PER_EXT1	((uint32_t) 15)
#define bit_wid_RTK_DMAC_CFG_H_SRC_PER_EXT1	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_H_DEST_PER_EXT1	((uint32_t) 17)
#define bit_wid_RTK_DMAC_CFG_H_DEST_PER_EXT1	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_H_SRC_PER_EXT2	((uint32_t) 16)
#define bit_wid_RTK_DMAC_CFG_H_SRC_PER_EXT2	((uint32_t) 1)
#define bit_off_RTK_DMAC_CFG_H_DEST_PER_EXT2	((uint32_t) 18)
#define bit_wid_RTK_DMAC_CFG_H_DEST_PER_EXT2	((uint32_t) 1)

#define bit_off_RTK_DMAC_SGR_L_SGI			((uint32_t)0)
#define bit_wid_RTK_DMAC_SGR_L_SGI			((uint32_t)20)
#define bit_off_RTK_DMAC_SGR_L_SGC			((uint32_t)20)
#define bit_wid_RTK_DMAC_SGR_L_SGC			((uint32_t)12)

#define bit_off_RTK_DMAC_DSR_L_DSI			((uint32_t)0)
#define bit_wid_RTK_DMAC_DSR_L_DSI			((uint32_t)20)
#define bit_off_RTK_DMAC_DSR_L_DSC			((uint32_t)20)
#define bit_wid_RTK_DMAC_DSR_L_DSC			((uint32_t)12)

#define bit_off_RTK_DMAC_INT_RAW_STAT_CLR(ch)	((uint32_t)(ch))
#define bit_wid_RTK_DMAC_INT_RAW_STAT_CLR(ch)	((uint32_t)1)
#define bit_off_RTK_DMAC_INT_RAW_STAT_CLR_ALL	((uint32_t)0)
#define bit_wid_RTK_DMAC_INT_RAW_STAT_CLR_ALL	((uint32_t)8)

#define bit_off_RTK_DMAC_INT_MASK_L(ch)			((uint32_t)(ch))
#define bit_wid_RTK_DMAC_INT_MASK_L(ch)			((uint32_t)1)
#define bit_off_RTK_DMAC_INT_MASK_L_ALL			((uint32_t)0)
#define bit_wid_RTK_DMAC_INT_MASK_L_ALL			((uint32_t)8)
#define bit_off_RTK_DMAC_INT_MASK_L_WE(ch)		((uint32_t)(ch)+8)
#define bit_wid_RTK_DMAC_INT_MASK_L_WE(ch)		((uint32_t)1)
#define bit_off_RTK_DMAC_INT_MASK_L_WE_ALL		((uint32_t)8)
#define bit_wid_RTK_DMAC_INT_MASK_L_WE_ALL		((uint32_t)8)

#define bit_off_RTK_DMAC_STATUSINT_L_TFR		((uint32_t)0)
#define bit_wid_RTK_DMAC_STATUSINT_L_TFR		((uint32_t)1)
#define bit_off_RTK_DMAC_STATUSINT_L_BLOCK		((uint32_t)1)
#define bit_wid_RTK_DMAC_STATUSINT_L_BLOCK		((uint32_t)1)
#define bit_off_RTK_DMAC_STATUSINT_L_SRCTRAN	((uint32_t)2)
#define bit_wid_RTK_DMAC_STATUSINT_L_SRCTRAN	((uint32_t)1)
#define bit_off_RTK_DMAC_STATUSINT_L_DSTTRAN	((uint32_t)3)
#define bit_wid_RTK_DMAC_STATUSINT_L_DSTTRAN	((uint32_t)1)
#define bit_off_RTK_DMAC_STATUSINT_L_ERR		((uint32_t)4)
#define bit_wid_RTK_DMAC_STATUSINT_L_ERR		((uint32_t)1)

#define bit_off_RTK_DMAC_SW_HANDSHAKE_L(ch)		((uint32_t)(ch))
#define bit_wid_RTK_DMAC_SW_HANDSHAKE_L(ch)		((uint32_t)1)
#define bit_off_RTK_DMAC_SW_HANDSHAKE_L_WE(ch)	((uint32_t)(ch)+8)
#define bit_wid_RTK_DMAC_SW_HANDSHAKE_L_WE(ch)	((uint32_t)1)

#define bit_off_RTK_DMAC_DMALD_L_DMA_ID			((uint32_t)0)
#define bit_wid_RTK_DMAC_DMALD_L_DMA_ID			((uint32_t)32)

#define bit_off_RTK_DMAC_DMATESTREG_L_TEST_SLV_IF	((uint32_t)0)
#define bit_wid_RTK_DMAC_DMATESTREG_L_TEST_SLV_IF	((uint32_t)1)

#define bit_off_RTK_DMAC_DMACOMPVER_L_DMACOMPVER	((uint32_t)0)
#define bit_wid_RTK_DMAC_DMACOMPVER_L_DMACOMPVER	((uint32_t)32)

#define bit_off_RTK_DMAC_PARAM_CHX_DTW					((uint32_t)0)
#define bit_wid_RTK_DMAC_PARAM_CHX_DTW					((uint32_t)3)
#define bit_off_RTK_DMAC_PARAM_CHX_STW					((uint32_t)3)
#define bit_wid_RTK_DMAC_PARAM_CHX_STW					((uint32_t)3)
#define bit_off_RTK_DMAC_PARAM_CHX_STAT_DST				((uint32_t)6)
#define bit_wid_RTK_DMAC_PARAM_CHX_STAT_DST				((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_STAT_SRC				((uint32_t)7)
#define bit_wid_RTK_DMAC_PARAM_CHX_STAT_SRC				((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_DST_SCA_EN			((uint32_t)8)
#define bit_wid_RTK_DMAC_PARAM_CHX_DST_SCA_EN			((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_SRC_GAT_EN			((uint32_t)9)
#define bit_wid_RTK_DMAC_PARAM_CHX_SRC_GAT_EN			((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_LOCK_EN				((uint32_t)10)
#define bit_wid_RTK_DMAC_PARAM_CHX_LOEC_EN				((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_MULTI_BLK_EN			((uint32_t)11)
#define bit_wid_RTK_DMAC_PARAM_CHX_MULTI_BLK_EN			((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_CTL_WB_EN			((uint32_t)12)
#define bit_wid_RTK_DMAC_PARAM_CHX_CTL_WB_EN			((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_HC_LLP				((uint32_t)13)
#define bit_wid_RTK_DMAC_PARAM_CHX_HC_LLP				((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_CHX_FC					((uint32_t)14)
#define bit_wid_RTK_DMAC_PARAM_CHX_FC					((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_CHX_MAX_MULT_SIZE		((uint32_t)16)
#define bit_wid_RTK_DMAC_PARAM_CHX_MAX_MULT_SIZE		((uint32_t)3)
#define bit_off_RTK_DMAC_PARAM_CHX_DMS					((uint32_t)19)
#define bit_wid_RTK_DMAC_PARAM_CHX_DMS					((uint32_t)3)
#define bit_off_RTK_DMAC_PARAM_CHX_LMS					((uint32_t)22)
#define bit_wid_RTK_DMAC_PARAM_CHX_LMS					((uint32_t)3)
#define bit_off_RTK_DMAC_PARAM_CHX_SMS					((uint32_t)25)
#define bit_wid_RTK_DMAC_PARAM_CHX_SMS					((uint32_t)3)
#define bit_off_RTK_DMAC_PARAM_CHX_FIFO_DEPTH			((uint32_t)28)
#define bit_wid_RTK_DMAC_PARAM_CHX_FIFO_DEPTH			((uint32_t)3)

#define bit_off_RTK_DMAC_PARAM_CH0_MUTLI_BLK_TYPE		((uint32_t)0)
#define bit_wid_RTK_DMAC_PARAM_CH0_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH1_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_wid_RTK_DMAC_PARAM_CH1_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH2_MUTLI_BLK_TYPE		((uint32_t)8)
#define bit_wid_RTK_DMAC_PARAM_CH2_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH3_MUTLI_BLK_TYPE		((uint32_t)12)
#define bit_wid_RTK_DMAC_PARAM_CH3_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH4_MUTLI_BLK_TYPE		((uint32_t)16)
#define bit_wid_RTK_DMAC_PARAM_CH4_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH5_MUTLI_BLK_TYPE		((uint32_t)20)
#define bit_wid_RTK_DMAC_PARAM_CH5_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH6_MUTLI_BLK_TYPE		((uint32_t)24)
#define bit_wid_RTK_DMAC_PARAM_CH6_MUTLI_BLK_TYPE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH7_MUTLI_BLK_TYPE		((uint32_t)28)
#define bit_wid_RTK_DMAC_PARAM_CH7_MUTLI_BLK_TYPE		((uint32_t)4)

#define bit_off_RTK_DMAC_PARAM_BIG_ENDIAN				((uint32_t)0)
#define bit_wid_RTK_DMAC_PARAM_BIG_ENDIAN				((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_INTR_IO					((uint32_t)1)
#define bit_wid_RTK_DMAC_PARAM_INTR_IO					((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_MABRST					((uint32_t)3)
#define bit_wid_RTK_DMAC_PARAM_MABRST					((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_NUM_CHANNELS				((uint32_t)7)
#define bit_wid_RTK_DMAC_PARAM_NUM_CHANNELS				((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_NUM_MASTER_INT			((uint32_t)11)
#define bit_wid_RTK_DMAC_PARAM_NUM_MASTER_INT			((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_S_HDATA_WIDTH			((uint32_t)13)
#define bit_wid_RTK_DMAC_PARAM_S_HDATA_WIDTH			((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_M1_HDATA_WIDTH			((uint32_t)15)
#define bit_wid_RTK_DMAC_PARAM_M1_HDATA_WIDTH			((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_M2_HDATA_WIDTH			((uint32_t)17)
#define bit_wid_RTK_DMAC_PARAM_M2_HDATA_WIDTH			((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_M3_HDATA_WIDTH			((uint32_t)19)
#define bit_wid_RTK_DMAC_PARAM_M3_HDATA_WIDTH			((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_M4_HDATA_WIDTH			((uint32_t)21)
#define bit_wid_RTK_DMAC_PARAM_M4_HDATA_WIDTH			((uint32_t)2)
#define bit_off_RTK_DMAC_PARAM_NUM_HS_INT				((uint32_t)23)
#define bit_wid_RTK_DMAC_PARAM_NUM_HS_INT				((uint32_t)5)
#define bit_off_RTK_DMAC_PARAM_ADD_ENCODED_PARAMS		((uint32_t)28)
#define bit_wid_RTK_DMAC_PARAM_ADD_ENCODED_PARAMS		((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_HIGH_BIT_NUM_HS_INT1		((uint32_t)30)
#define bit_wid_RTK_DMAC_PARAM_HIGH_BIT_NUM_HS_INT1		((uint32_t)1)
#define bit_off_RTK_DMAC_PARAM_HIGH_BIT_NUM_HS_INT2		((uint32_t)31)
#define bit_wid_RTK_DMAC_PARAM_HIGH_BIT_NUM_HS_INT2		((uint32_t)1)

#define bit_off_RTK_DMAC_PARAM_CH0_MAX_BLK_SIZE			((uint32_t)0)
#define bit_wid_RTK_DMAC_PARAM_CH0_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH1_MAX_BLK_SIZE			((uint32_t)4)
#define bit_wid_RTK_DMAC_PARAM_CH1_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH2_MAX_BLK_SIZE			((uint32_t)8)
#define bit_wid_RTK_DMAC_PARAM_CH2_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH3_MAX_BLK_SIZE			((uint32_t)12)
#define bit_wid_RTK_DMAC_PARAM_CH3_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH4_MAX_BLK_SIZE			((uint32_t)16)
#define bit_wid_RTK_DMAC_PARAM_CH4_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH5_MAX_BLK_SIZE			((uint32_t)20)
#define bit_wid_RTK_DMAC_PARAM_CH5_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH6_MAX_BLK_SIZE			((uint32_t)24)
#define bit_wid_RTK_DMAC_PARAM_CH6_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH7_MAX_BLK_SIZE			((uint32_t)28)
#define bit_wid_RTK_DMAC_PARAM_CH7_MAX_BLK_SIZE			((uint32_t)4)

#define bit_off_RTK_DMAC_PARAM_CH8_MAX_BLK_SIZE			((uint32_t)0)
#define bit_wid_RTK_DMAC_PARAM_CH8_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH9_MAX_BLK_SIZE			((uint32_t)4)
#define bit_wid_RTK_DMAC_PARAM_CH9_MAX_BLK_SIZE			((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH10_MAX_BLK_SIZE		((uint32_t)8)
#define bit_wid_RTK_DMAC_PARAM_CH10_MAX_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH11_MAX_BLK_SIZE		((uint32_t)12)
#define bit_wid_RTK_DMAC_PARAM_CH11_MAX_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH12_MAX_BLK_SIZE		((uint32_t)16)
#define bit_wid_RTK_DMAC_PARAM_CH12_MAX_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH13_MAX_BLK_SIZE		((uint32_t)20)
#define bit_wid_RTK_DMAC_PARAM_CH13_MAX_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH14_MAX_BLK_SIZE		((uint32_t)24)
#define bit_wid_RTK_DMAC_PARAM_CH14_MAX_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH15_MAX_BLK_SIZE		((uint32_t)28)
#define bit_wid_RTK_DMAC_PARAM_CH15_MAX_BLK_SIZE		((uint32_t)4)

#define bit_off_RTK_DMAC_PARAM_CH8_MUTLI_BLK_SIZE		((uint32_t)0)
#define bit_wid_RTK_DMAC_PARAM_CH8_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH9_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_wid_RTK_DMAC_PARAM_CH9_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH10_MUTLI_BLK_SIZE		((uint32_t)8)
#define bit_wid_RTK_DMAC_PARAM_CH10_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH11_MUTLI_BLK_SIZE		((uint32_t)12)
#define bit_wid_RTK_DMAC_PARAM_CH11_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH12_MUTLI_BLK_SIZE		((uint32_t)16)
#define bit_wid_RTK_DMAC_PARAM_CH12_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH13_MUTLI_BLK_SIZE		((uint32_t)20)
#define bit_wid_RTK_DMAC_PARAM_CH13_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH14_MUTLI_BLK_SIZE		((uint32_t)24)
#define bit_wid_RTK_DMAC_PARAM_CH14_MUTLI_BLK_SIZE		((uint32_t)4)
#define bit_off_RTK_DMAC_PARAM_CH15_MUTLI_BLK_SIZE		((uint32_t)28)
#define bit_wid_RTK_DMAC_PARAM_CH15_MUTLI_BLK_SIZE		((uint32_t)4)

#define RTK_DEFINE_DMAC_PARAMS(prefix)	{	\
	prefix ## RTK_DMAC_ID,					\
	prefix ## RTK_DMAC_NUM_MASTER_INT, 		\
	prefix ## RTK_DMAC_NUM_CHANNELS, 		\
	prefix ## RTK_DMAC_NUM_HS_INT,	 		\
	prefix ## RTK_DMAC_INTR_IO, 			\
	prefix ## RTK_DMAC_S_DATA_WIDTH, 		\
	prefix ## RTK_DMAC_M_DATA_WIDTH, 		\
	prefix ## RTK_DMAC_BIG_ENDIAN,	 		\
	prefix ## RTK_DMAC_SECURE_MODE,			\
	prefix ## RTK_DMAC_CH0_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH1_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH2_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH3_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH4_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH5_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH6_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH7_FIFO_DEPTH,		\
	prefix ## RTK_DMAC_CH8_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH9_FIFO_DEPTH, 		\
	prefix ## RTK_DMAC_CH10_FIFO_DEPTH, 	\
	prefix ## RTK_DMAC_CH11_FIFO_DEPTH,		\
	prefix ## RTK_DMAC_CH12_FIFO_DEPTH, 	\
	prefix ## RTK_DMAC_CH13_FIFO_DEPTH, 	\
	prefix ## RTK_DMAC_CH14_FIFO_DEPTH, 	\
	prefix ## RTK_DMAC_CH15_FIFO_DEPTH,		\
	prefix ## RTK_DMAC_CH0_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH1_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH2_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH3_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH4_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH5_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH6_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH7_MAX_BLK_SIZE,	\
	prefix ## RTK_DMAC_CH8_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH9_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH10_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH11_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH12_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH13_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH14_MAX_BLK_SIZE, 	\
	prefix ## RTK_DMAC_CH15_MAX_BLK_SIZE,	\
	prefix ## RTK_DMAC_CH0_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH1_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH2_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH3_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH4_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH5_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH6_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH7_MULTI_BLK_EN,	\
	prefix ## RTK_DMAC_CH8_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH9_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH10_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH11_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH12_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH13_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH14_MULTI_BLK_EN, 	\
	prefix ## RTK_DMAC_CH15_MULTI_BLK_EN,	\
	prefix ## RTK_DMAC_CH0_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH1_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH2_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH3_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH4_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH5_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH6_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH7_MULTI_BLK_TYPE,	\
	prefix ## RTK_DMAC_CH8_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH9_MULTI_BLK_TYPE, 	\
	prefix ## RTK_DMAC_CH10_MULTI_BLK_TYPE, \
	prefix ## RTK_DMAC_CH11_MULTI_BLK_TYPE, \
	prefix ## RTK_DMAC_CH12_MULTI_BLK_TYPE, \
	prefix ## RTK_DMAC_CH13_MULTI_BLK_TYPE, \
	prefix ## RTK_DMAC_CH14_MULTI_BLK_TYPE, \
	prefix ## RTK_DMAC_CH15_MULTI_BLK_TYPE,	\
	prefix ## RTK_DMAC_CH0_HC_LLP, 			\
	prefix ## RTK_DMAC_CH1_HC_LLP, 			\
	prefix ## RTK_DMAC_CH2_HC_LLP, 			\
	prefix ## RTK_DMAC_CH3_HC_LLP, 			\
	prefix ## RTK_DMAC_CH4_HC_LLP, 			\
	prefix ## RTK_DMAC_CH5_HC_LLP, 			\
	prefix ## RTK_DMAC_CH6_HC_LLP, 			\
	prefix ## RTK_DMAC_CH7_HC_LLP,			\
	prefix ## RTK_DMAC_CH8_HC_LLP, 			\
	prefix ## RTK_DMAC_CH9_HC_LLP, 			\
	prefix ## RTK_DMAC_CH10_HC_LLP, 		\
	prefix ## RTK_DMAC_CH11_HC_LLP, 		\
	prefix ## RTK_DMAC_CH12_HC_LLP, 		\
	prefix ## RTK_DMAC_CH13_HC_LLP, 		\
	prefix ## RTK_DMAC_CH14_HC_LLP, 		\
	prefix ## RTK_DMAC_CH15_HC_LLP,			\
	prefix ## RTK_DMAC_CH0_STAT_DST, 		\
	prefix ## RTK_DMAC_CH1_STAT_DST, 		\
	prefix ## RTK_DMAC_CH2_STAT_DST, 		\
	prefix ## RTK_DMAC_CH3_STAT_DST, 		\
	prefix ## RTK_DMAC_CH4_STAT_DST, 		\
	prefix ## RTK_DMAC_CH5_STAT_DST, 		\
	prefix ## RTK_DMAC_CH6_STAT_DST, 		\
	prefix ## RTK_DMAC_CH7_STAT_DST,		\
	prefix ## RTK_DMAC_CH8_STAT_DST, 		\
	prefix ## RTK_DMAC_CH9_STAT_DST, 		\
	prefix ## RTK_DMAC_CH10_STAT_DST, 		\
	prefix ## RTK_DMAC_CH11_STAT_DST, 		\
	prefix ## RTK_DMAC_CH12_STAT_DST, 		\
	prefix ## RTK_DMAC_CH13_STAT_DST, 		\
	prefix ## RTK_DMAC_CH14_STAT_DST, 		\
	prefix ## RTK_DMAC_CH15_STAT_DST,		\
	prefix ## RTK_DMAC_CH0_STAT_SRC,		\
	prefix ## RTK_DMAC_CH1_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH2_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH3_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH4_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH5_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH6_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH7_STAT_SRC,		\
	prefix ## RTK_DMAC_CH8_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH9_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH10_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH11_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH12_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH13_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH14_STAT_SRC, 		\
	prefix ## RTK_DMAC_CH15_STAT_SRC,		\
	prefix ## RTK_DMAC_CH0_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH1_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH2_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH3_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH4_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH5_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH6_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH7_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH8_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH9_UNL_SUP_EN, 		\
	prefix ## RTK_DMAC_CH10_UNL_SUP_EN, 	\
	prefix ## RTK_DMAC_CH11_UNL_SUP_EN, 	\
	prefix ## RTK_DMAC_CH12_UNL_SUP_EN, 	\
	prefix ## RTK_DMAC_CH13_UNL_SUP_EN, 	\
	prefix ## RTK_DMAC_CH14_UNL_SUP_EN, 	\
	prefix ## RTK_DMAC_CH15_UNL_SUP_EN, 	\
	prefix ## RTK_DMAC_CH0_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH1_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH2_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH3_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH4_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH5_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH6_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH7_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH8_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH9_SRC_GAT_EN, 		\
	prefix ## RTK_DMAC_CH10_SRC_GAT_EN, 	\
	prefix ## RTK_DMAC_CH11_SRC_GAT_EN, 	\
	prefix ## RTK_DMAC_CH12_SRC_GAT_EN, 	\
	prefix ## RTK_DMAC_CH13_SRC_GAT_EN, 	\
	prefix ## RTK_DMAC_CH14_SRC_GAT_EN, 	\
	prefix ## RTK_DMAC_CH15_SRC_GAT_EN, 	\
	prefix ## RTK_DMAC_CH0_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH1_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH2_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH3_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH4_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH5_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH6_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH7_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH8_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH9_DST_SCA_EN, 		\
	prefix ## RTK_DMAC_CH10_DST_SCA_EN, 	\
	prefix ## RTK_DMAC_CH11_DST_SCA_EN, 	\
	prefix ## RTK_DMAC_CH12_DST_SCA_EN, 	\
	prefix ## RTK_DMAC_CH13_DST_SCA_EN, 	\
	prefix ## RTK_DMAC_CH14_DST_SCA_EN, 	\
	prefix ## RTK_DMAC_CH15_DST_SCA_EN, 	\
	prefix ## RTK_DMAC_CH0_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH1_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH2_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH3_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH4_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH5_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH6_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH7_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH8_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH9_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH10_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH11_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH12_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH13_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH14_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_CH15_CTL_WB_EN, 		\
	prefix ## RTK_DMAC_PROGRAM_PRI, 		\
	prefix ## RTK_DMAC_TEST0		 		\
}

#define RTK_CHN_CONFIG_DEFAULT_DEFINE_PARAMS {	\
	0x00000000,		\
	0x00000000,		\
	0x0,		\
	0x0,		\
	0x00,		\
	0x00,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x1,		\
	0x1,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0,		\
	0x0			\
}

struct rtk_dmac_param_struct	{
	uint32_t	rtk_dmac_id;
	uint8_t		num_master_int;
	uint8_t		num_channels;
	uint8_t		num_hs_int;
	uint8_t		intr_io;
	uint16_t	s_data_width;
	uint16_t	m_data_width;
	bool		big_endian;
	bool		ch_secure_mode;
	uint8_t		ch_fifo_depth0;
	uint8_t		ch_fifo_depth1;
	uint8_t		ch_fifo_depth2;
	uint8_t		ch_fifo_depth3;
	uint8_t		ch_fifo_depth4;
	uint8_t		ch_fifo_depth5;
	uint8_t		ch_fifo_depth6;
	uint8_t		ch_fifo_depth7;
	uint8_t		ch_fifo_depth8;
	uint8_t		ch_fifo_depth9;
	uint8_t		ch_fifo_depth10;
	uint8_t		ch_fifo_depth11;
	uint8_t		ch_fifo_depth12;
	uint8_t		ch_fifo_depth13;
	uint8_t		ch_fifo_depth14;
	uint8_t		ch_fifo_depth15;
	uint16_t	ch_max_blk_size0;
	uint16_t	ch_max_blk_size1;
	uint16_t	ch_max_blk_size2;
	uint16_t	ch_max_blk_size3;
	uint16_t	ch_max_blk_size4;
	uint16_t	ch_max_blk_size5;
	uint16_t	ch_max_blk_size6;
	uint16_t	ch_max_blk_size7;
	uint16_t	ch_max_blk_size8;
	uint16_t	ch_max_blk_size9;
	uint16_t	ch_max_blk_size10;
	uint16_t	ch_max_blk_size11;
	uint16_t	ch_max_blk_size12;
	uint16_t	ch_max_blk_size13;
	uint16_t	ch_max_blk_size14;
	uint16_t	ch_max_blk_size15;
	bool		ch_multi_blk_en0;
	bool		ch_multi_blk_en1;
	bool		ch_multi_blk_en2;
	bool		ch_multi_blk_en3;
	bool		ch_multi_blk_en4;
	bool		ch_multi_blk_en5;
	bool		ch_multi_blk_en6;
	bool		ch_multi_blk_en7;
	bool		ch_multi_blk_en8;
	bool		ch_multi_blk_en9;
	bool		ch_multi_blk_en10;
	bool		ch_multi_blk_en11;
	bool		ch_multi_blk_en12;
	bool		ch_multi_blk_en13;
	bool		ch_multi_blk_en14;
	bool		ch_multi_blk_en15;
	uint16_t	ch_multi_blk_type0;
	uint16_t	ch_multi_blk_type1;
	uint16_t	ch_multi_blk_type2;
	uint16_t	ch_multi_blk_type3;
	uint16_t	ch_multi_blk_type4;
	uint16_t	ch_multi_blk_type5;
	uint16_t	ch_multi_blk_type6;
	uint16_t	ch_multi_blk_type7;
	uint16_t	ch_multi_blk_type8;
	uint16_t	ch_multi_blk_type9;
	uint16_t	ch_multi_blk_type10;
	uint16_t	ch_multi_blk_type11;
	uint16_t	ch_multi_blk_type12;
	uint16_t	ch_multi_blk_type13;
	uint16_t	ch_multi_blk_type14;
	uint16_t	ch_multi_blk_type15;
	bool		ch_hc_llp0;
	bool		ch_hc_llp1;
	bool		ch_hc_llp2;
	bool		ch_hc_llp3;
	bool		ch_hc_llp4;
	bool		ch_hc_llp5;
	bool		ch_hc_llp6;
	bool		ch_hc_llp7;
	bool		ch_hc_llp8;
	bool		ch_hc_llp9;
	bool		ch_hc_llp10;
	bool		ch_hc_llp11;
	bool		ch_hc_llp12;
	bool		ch_hc_llp13;
	bool		ch_hc_llp14;
	bool		ch_hc_llp15;
	bool		ch_stat_dst0;
	bool		ch_stat_dst1;
	bool		ch_stat_dst2;
	bool		ch_stat_dst3;
	bool		ch_stat_dst4;
	bool		ch_stat_dst5;
	bool		ch_stat_dst6;
	bool		ch_stat_dst7;
	bool		ch_stat_dst8;
	bool		ch_stat_dst9;
	bool		ch_stat_dst10;
	bool		ch_stat_dst11;
	bool		ch_stat_dst12;
	bool		ch_stat_dst13;
	bool		ch_stat_dst14;
	bool		ch_stat_dst15;
	bool		ch_stat_src0;
	bool		ch_stat_src1;
	bool		ch_stat_src2;
	bool		ch_stat_src3;
	bool		ch_stat_src4;
	bool		ch_stat_src5;
	bool		ch_stat_src6;
	bool		ch_stat_src7;
	bool		ch_stat_src8;
	bool		ch_stat_src9;
	bool		ch_stat_src10;
	bool		ch_stat_src11;
	bool		ch_stat_src12;
	bool		ch_stat_src13;
	bool		ch_stat_src14;
	bool		ch_stat_src15;
	bool		ch_unl_sup_en0;
	bool		ch_unl_sup_en1;
	bool		ch_unl_sup_en2;
	bool		ch_unl_sup_en3;
	bool		ch_unl_sup_en4;
	bool		ch_unl_sup_en5;
	bool		ch_unl_sup_en6;
	bool		ch_unl_sup_en7;
	bool		ch_unl_sup_en8;
	bool		ch_unl_sup_en9;
	bool		ch_unl_sup_en10;
	bool		ch_unl_sup_en11;
	bool		ch_unl_sup_en12;
	bool		ch_unl_sup_en13;
	bool		ch_unl_sup_en14;
	bool		ch_unl_sup_en15;
	bool		ch_src_gat_en0;
	bool		ch_src_gat_en1;
	bool		ch_src_gat_en2;
	bool		ch_src_gat_en3;
	bool		ch_src_gat_en4;
	bool		ch_src_gat_en5;
	bool		ch_src_gat_en6;
	bool		ch_src_gat_en7;
	bool		ch_src_gat_en8;
	bool		ch_src_gat_en9;
	bool		ch_src_gat_en10;
	bool		ch_src_gat_en11;
	bool		ch_src_gat_en12;
	bool		ch_src_gat_en13;
	bool		ch_src_gat_en14;
	bool		ch_src_gat_en15;
	bool		ch_dst_sca_en0;
	bool		ch_dst_sca_en1;
	bool		ch_dst_sca_en2;
	bool		ch_dst_sca_en3;
	bool		ch_dst_sca_en4;
	bool		ch_dst_sca_en5;
	bool		ch_dst_sca_en6;
	bool		ch_dst_sca_en7;
	bool		ch_dst_sca_en8;
	bool		ch_dst_sca_en9;
	bool		ch_dst_sca_en10;
	bool		ch_dst_sca_en11;
	bool		ch_dst_sca_en12;
	bool		ch_dst_sca_en13;
	bool		ch_dst_sca_en14;
	bool		ch_dst_sca_en15;
	bool		ch_ctl_wb_en0;
	bool		ch_ctl_wb_en1;
	bool		ch_ctl_wb_en2;
	bool		ch_ctl_wb_en3;
	bool		ch_ctl_wb_en4;
	bool		ch_ctl_wb_en5;
	bool		ch_ctl_wb_en6;
	bool		ch_ctl_wb_en7;
	bool		ch_ctl_wb_en8;
	bool		ch_ctl_wb_en9;
	bool		ch_ctl_wb_en10;
	bool		ch_ctl_wb_en11;
	bool		ch_ctl_wb_en12;
	bool		ch_ctl_wb_en13;
	bool		ch_ctl_wb_en14;
	bool		ch_ctl_wb_en15;
	bool		programmable_pri;
	bool		test0;
};

struct rtk_dmac_regmap_struct	{

	struct	{
		volatile uint32_t sar_l;
		volatile uint32_t sar_h;
		volatile uint32_t dar_l;
		volatile uint32_t dar_h;
		volatile uint32_t llp_l;
		volatile uint32_t llp_h;
		volatile uint32_t ctl_l;
		volatile uint32_t ctl_h;
		volatile uint32_t sstat_l;
		volatile uint32_t sstat_h;
		volatile uint32_t dstat_l;
		volatile uint32_t dstat_h;
		volatile uint32_t sstatar_l;
		volatile uint32_t sstatar_h;
		volatile uint32_t dstatar_l;
		volatile uint32_t dstatar_h;
		volatile uint32_t cfg_l;
		volatile uint32_t cfg_h;
		volatile uint32_t sgr_l;
		volatile uint32_t sgr_h;
		volatile uint32_t dsr_l;
		volatile uint32_t dsr_h;
	}ch[8];
	
		volatile uint32_t raw_tfr_l_;
		volatile uint32_t raw_tfr_h_;
		volatile uint32_t raw_block_l_;
		volatile uint32_t raw_block_h_;
		volatile uint32_t raw_srctran_l_;
		volatile uint32_t raw_srctran_h_;
		volatile uint32_t raw_dsttran_l_;
		volatile uint32_t raw_dsttran_h_;
		volatile uint32_t raw_err_l_;
		volatile uint32_t raw_err_h_;

		volatile uint32_t status_tfr_l_;
		volatile uint32_t status_tfr_h_;
		volatile uint32_t status_block_l_;
		volatile uint32_t status_block_h_;
		volatile uint32_t status_srctran_l_;
		volatile uint32_t status_srctran_h_;
		volatile uint32_t status_dsttran_l_;
		volatile uint32_t status_dsttran_h_;
		volatile uint32_t status_err_l_;
		volatile uint32_t status_err_h_;

		volatile uint32_t mask_tfr_l_;
		volatile uint32_t mask_tfr_h_;
		volatile uint32_t mask_block_l_;
		volatile uint32_t mask_block_h_;
		volatile uint32_t mask_srctran_l_;
		volatile uint32_t mask_srctran_h_;
		volatile uint32_t mask_dsttran_l_;
		volatile uint32_t mask_dsttran_h_;
		volatile uint32_t mask_err_l_;
		volatile uint32_t mask_err_h_;

		volatile uint32_t clear_tfr_l_;
		volatile uint32_t clear_tfr_h_;
		volatile uint32_t clear_block_l_;
		volatile uint32_t clear_block_h_;
		volatile uint32_t clear_srctran_l_;
		volatile uint32_t clear_srctran_h_;
		volatile uint32_t clear_dsttran_l_;
		volatile uint32_t clear_dsttran_h_;
		volatile uint32_t clear_err_l_;
		volatile uint32_t clear_err_h_;
		volatile uint32_t status_int_l_;
		volatile uint32_t status_int_h_;

		volatile uint32_t req_src_reg_l_;
		volatile uint32_t req_src_reg_h_;
		volatile uint32_t req_dst_reg_l_;
		volatile uint32_t req_dst_reg_h_;
		volatile uint32_t sgl_rq_src_reg_l_;
		volatile uint32_t sgl_rq_src_reg_h_;
		volatile uint32_t sgl_rq_dst_reg_l_;
		volatile uint32_t sgl_rq_dst_reg_h_;
		volatile uint32_t lst_src_reg_l_;
		volatile uint32_t lst_src_reg_h_;
		volatile uint32_t lst_dst_reg_l_;
		volatile uint32_t lst_dst_reg_h_;

		volatile uint32_t dma_cfg_reg_l_;
		volatile uint32_t dma_cfg_reg_h_;
		volatile uint32_t ch_en_reg_l_;
		volatile uint32_t ch_en_reg_h_;
		volatile uint32_t dma_id_reg_l_;
		volatile uint32_t dma_id_reg_h_;
		volatile uint32_t dma_test_reg_l_;		
		volatile uint32_t dma_test_reg_h_;
		volatile uint32_t old_version_id_l_;
		volatile uint32_t old_version_id_h_;
		volatile uint32_t reserved_low_;
		volatile uint32_t reserved_high_;
		volatile uint32_t dma_comp_params_6_l_;
		volatile uint32_t dma_comp_params_6_h_;
		volatile uint32_t dma_comp_params_5_l_;
		volatile uint32_t dma_comp_params_5_h_;
		volatile uint32_t dma_comp_params_4_l_;
		volatile uint32_t dma_comp_params_4_h_;
		volatile uint32_t dma_comp_params_3_l_;
		volatile uint32_t dma_comp_params_3_h_;
		volatile uint32_t dma_comp_params_2_l_;
		volatile uint32_t dma_comp_params_2_h_;
		volatile uint32_t dma_comp_params_1_l_;
		volatile uint32_t dma_comp_params_1_h_;
		volatile uint32_t dma_version_id_l_;
		volatile uint32_t dma_version_id_h_;

	struct	{
		volatile uint32_t sar_l;
		volatile uint32_t sar_h;
		volatile uint32_t dar_l;
		volatile uint32_t dar_h;
		volatile uint32_t llp_l;
		volatile uint32_t llp_h;
		volatile uint32_t ctl_l;
		volatile uint32_t ctl_h;
		volatile uint32_t sstat_l;
		volatile uint32_t sstat_h;
		volatile uint32_t dstat_l;
		volatile uint32_t dstat_h;
		volatile uint32_t sstatar_l;
		volatile uint32_t sstatar_h;
		volatile uint32_t dstatar_l;
		volatile uint32_t dstatar_h;
		volatile uint32_t cfg_l;
		volatile uint32_t cfg_h;
		volatile uint32_t sgr_l;
		volatile uint32_t sgr_h;
		volatile uint32_t dsr_l;
		volatile uint32_t dsr_h;
	}ch8[8];

		volatile uint32_t dma_comp_params_11_l_;
		volatile uint32_t dma_comp_params_11_h_;
		volatile uint32_t dma_comp_params_10_l_;
		volatile uint32_t dma_comp_params_10_h_;		
		volatile uint32_t dma_comp_params_9_l_;
		volatile uint32_t dma_comp_params_9_h_;
		volatile uint32_t dma_comp_params_8_l_;
		volatile uint32_t dma_comp_params_8_h_;
		volatile uint32_t dma_comp_params_7_l_;
		volatile uint32_t dma_comp_params_7_h_;
};

struct rtk_dmac_aes_regmap_struct {
	struct {
		volatile uint32_t cpu_datain_3;
		volatile uint32_t cpu_datain_2;
		volatile uint32_t cpu_datain_1;
		volatile uint32_t cpu_datain_0;
		volatile uint32_t cpu_dataout_3;
		volatile uint32_t cpu_dataout_2;
		volatile uint32_t cpu_dataout_1;
		volatile uint32_t cpu_dataout_0;
		volatile uint32_t key_de_out_7;
		volatile uint32_t key_de_out_6;
		volatile uint32_t key_de_out_5;
		volatile uint32_t key_de_out_4;
		volatile uint32_t key_de_out_3;
		volatile uint32_t key_de_out_2;
		volatile uint32_t key_de_out_1;
		volatile uint32_t key_de_out_0;
		volatile uint32_t key_7;
		volatile uint32_t key_6;
		volatile uint32_t key_5;
		volatile uint32_t key_4;
		volatile uint32_t key_3;
		volatile uint32_t key_2;
		volatile uint32_t key_1;
		volatile uint32_t key_0;
		volatile uint32_t iv_3;
		volatile uint32_t iv_2;
		volatile uint32_t iv_1;
		volatile uint32_t iv_0;
		volatile uint32_t config;
		volatile uint32_t cipher_len;
		volatile uint32_t gmac_len_1;
		volatile uint32_t gmac_len_0;
		volatile uint32_t tag_3;
		volatile uint32_t tag_2;
		volatile uint32_t tag_1;
		volatile uint32_t tag_0;
		volatile uint32_t ghash_key_3;
		volatile uint32_t ghash_key_2;
		volatile uint32_t ghash_key_1;
		volatile uint32_t ghash_key_0;
	}ch_aes[16];
};

struct rtk_dmac_aes_int_and_constant_regmap_struct {
	volatile uint32_t aes_int;
	volatile uint32_t reserved_0;
	volatile uint32_t reserved_1;
	volatile uint32_t reserved_2;
	struct {
		volatile uint32_t raw_aes;
		volatile uint32_t mask_aes;
		volatile uint32_t status_aes;
		volatile uint32_t clear_aes;
	}ch_aes[16];
	volatile uint32_t aes_chn_en;
	volatile uint32_t de_en_circuit;
	volatile uint32_t gcm_dou_circuit;
	volatile uint32_t date;
};

enum rtk_dmac_ch_state_enum {
	Dmac_idle = 0x0,
	Dmac_single_region = 0x1,
	Dmac_burst_region = 0x2
};


enum rtk_dmac_chn_num_enum
{
	Dmac_no_channel = 0x00000000,
	Dmac_channel0 	= 0x00000101,
	Dmac_channel1 	= 0x00000202,
	Dmac_channel2 	= 0x00000404,
	Dmac_channel3 	= 0x00000808,
	Dmac_channel4 	= 0x00001010,
	Dmac_channel5 	= 0x00002020,
	Dmac_channel6 	= 0x00004040,
	Dmac_channel7 	= 0x00008080,
	Dmac_channel8 	= 0x01010000,
	Dmac_channel9 	= 0x02020000,
	Dmac_channel10 	= 0x04040000,
	Dmac_channel11	= 0x08080000,
	Dmac_channel12 	= 0x10100000,
	Dmac_channel13 	= 0x20200000,
	Dmac_channel14 	= 0x40400000,
	Dmac_channel15,
	Dmac_all_channels
};
//typedef uint32_t rtk_dmac_chn_num_enum;

//#define Dmac_channel15 0x80800000
//#define Dmac_all_channels 0xFFFFFFFF

enum rtk_dmac_trans_type_enum
{
	Dmac_transfer_row1  = 0x1,
	Dmac_transfer_row2  = 0x2,
	Dmac_transfer_row3  = 0x3,
	Dmac_transfer_row4  = 0x4,
	Dmac_transfer_row5  = 0x5,
	Dmac_transfer_row6  = 0x6,
	Dmac_transfer_row7  = 0x7,
	Dmac_transfer_row8  = 0x8,
	Dmac_transfer_row9  = 0x9,
	Dmac_transfer_row10 = 0xa
};


struct rtk_dmac_instance {
	struct {
		enum rtk_dmac_chn_num_enum chnum;
		enum rtk_dmac_ch_state_enum src_state;
		enum rtk_dmac_ch_state_enum dst_state;
		enum rtk_dmac_ch_state_enum test[2];
		int block_cnt;
		int total_blocks;
		int src_byte_cnt;
		int dst_byte_cnt;
		int src_single_inc;
		int src_burst_inc;
		int dst_single_inc;
		int dst_burst_inc;
		enum rtk_dmac_trans_type_enum trans_type;
		enum dw_dmac_transfer_flow tt_fc;
		enum dw_dmac_transfer_flow test1[2];
		rtk_callback userCallback;
		rtk_callback userListener;
		}ch[16];
		int ch_order[DMAC_MAX_CHANNELS];
};
#endif
