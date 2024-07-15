#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>

enum dw_dmac_address_increment {
	Dmac_addr_increment = 0x0,
	Dmac_addr_decrement = 0x1,
	Dmac_addr_nochange  = 0x2
};

enum dw_dmac_transfer_width {
	Dmac_trans_width_8   = 0x0,
	Dmac_trans_width_16  = 0x1,
	Dmac_trans_width_32  = 0x2,
	Dmac_trans_width_64  = 0x3,
	Dmac_trans_width_128 = 0x4,
	Dmac_trans_width_256 = 0x5
};

enum dw_dmac_burst_trans_length {
	Dmac_msize_1   = 0x0,
	Dmac_msize_4   = 0x1,
	Dmac_msize_8   = 0x2,
	Dmac_msize_16  = 0x3,
	Dmac_msize_32  = 0x4,
	Dmac_msize_64  = 0x5,
	Dmac_msize_128 = 0x6,
	Dmac_msize_256 = 0x7
};

enum dw_dmac_transfer_flow {
	Dmac_mem2mem_dma    = 0x0, /* mem to mem - DMAC   flow ctlr */
	Dmac_mem2prf_dma    = 0x1, /* mem to prf - DMAC   flow ctlr */
	Dmac_prf2mem_dma    = 0x2, /* prf to mem - DMAC   flow ctlr */
	Dmac_prf2prf_dma    = 0x3, /* prf to prf - DMAC   flow ctlr */
	Dmac_prf2mem_prf    = 0x4, /* prf to mem - periph flow ctlr */
	Dmac_prf2prf_srcprf = 0x5, /* prf to prf - source flow ctlr */
	Dmac_mem2prf_prf    = 0x6, /* mem to prf - periph flow ctlr */
	Dmac_prf2prf_dstprf = 0x7  /* prf to prf - dest   flow ctlr */
};

extern void DMAC_MtoM(uint32_t SrcAddr, uint32_t DesAddr, uint32_t Size);
extern void DMAC_PtoM(uint32_t SrcAddr, uint32_t DesAddr, uint32_t Size);
extern void DMAC_MtoP(uint32_t SrcAddr, uint32_t DesAddr, uint32_t Size);
extern void HookFunction(void);

#endif
