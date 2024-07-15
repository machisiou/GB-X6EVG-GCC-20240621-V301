#include <stdint.h>
#include "chip/rts5911/RTS5911.h"
#include "hal/DMA.h"

static const uint16_t Dmacchannel [] =
{
	0x0101,				// Dmac_channel0
	0x0202,				// Dmac_channel1
	0x0404,				// Dmac_channel2
	0x0808,				// Dmac_channel3
	0x1010,				// Dmac_channel4
	0x2020,				// Dmac_channel5
	0x4040,				// Dmac_channel6
	0x8080,				// Dmac_channel7
	0xFFFF				// Dmac_all_channels
};

/******************************************************************************/
/** DMAC Memory to Memory
 * Source Address : (UINT:uint32_t)
 * Destination Address : (UINT:uint32_t)
 * Size:(UINT: uin16_t)
 * return None
*******************************************************************************/
void DMAC_MtoM(uint32_t SrcAddr, uint32_t DesAddr, uint32_t Size)
{
	uint32_t Channel;
	DMA_Type* Ptr;

	for(Channel=0;Channel<8;Channel++) {						/* DMA support 8 channel */
		if((DMA->CHEN & Dmacchannel[Channel]) != 0) {			/* Check if channel is using */
			//printf("DMA Channel %x is using Ch_en_reg_l value 0x%lx \n", i,DMAC->Ch_en_reg_l);
			continue;
		}
		break;
	}
	DMA->CLRTFR = 1 << Channel;									/* ClearTfr */
	DMA->CLRBLOCK = 1 << Channel;								/* ClearBlock */
	DMA->CLRSRCTRAN = 1 << Channel;								/* ClearSrcTran */
	DMA->CLRDSTTRAN = 1 << Channel;								/* ClearDstTran */

	Ptr = (DMA_Type*)((uint32_t)DMA_BASE + (uint32_t)(Channel * 0x58UL));
	Ptr->SAR0 = SrcAddr;										/* Source address is SPI address */
	Ptr->DAR0 = DesAddr;										/* Destination address is SRAM */

	// Setting Controller
	Ptr->CTRL0L_b.SINC = Dmac_addr_increment;
	Ptr->CTRL0L_b.DINC = Dmac_addr_increment;
	Ptr->CTRL0L_b.SRCTRWIDTH = Dmac_trans_width_8;
	Ptr->CTRL0L_b.DSTTRWIDTH = Dmac_trans_width_8;
	Ptr->CTRL0L_b.SRCMSIZE = Dmac_msize_256;
	Ptr->CTRL0L_b.DESTMSIZE = Dmac_msize_256;
	Ptr->CTRL0H = Size;											/* Number of Tranfer blocks */
	Ptr->CTRL0L_b.TTFC = Dmac_mem2mem_dma;						/* Type */
	DMA->CONF = 1;												/* Enable RTK_DMAC */
	DMA->CHEN |= Dmacchannel[Channel];							/* Enable channel */

	while(!(DMA->RAWTFR & (1 << Channel)))
	{
		//printf("Channel %x Transmit in progress \n",i);
	}
	//printf("Transmit complete \n");
}

/******************************************************************************/
/** DMAC Peripheral I/O to Memory
 * Source Address : (UINT:uint32_t)
 * Destination Address : (UINT:uint32_t)
 * Size:(UINT: uin16_t)
 * return None
*******************************************************************************/
void DMAC_PtoM(uint32_t SrcAddr, uint32_t DesAddr, uint32_t Size)
{
	uint32_t Channel;
	DMA_Type* Ptr;

	for(Channel=0;Channel<8;Channel++) {						/* DMA support 8 channel */
		if((DMA->CHEN & Dmacchannel[Channel]) != 0) {			/* Check if channel is using */
			//printf("DMA Channel %x is using Ch_en_reg_l value 0x%lx \n", i,DMAC->Ch_en_reg_l);
			continue;
		}
		break;
	}
	DMA->CLRTFR = 1 << Channel;									/* ClearTfr */
	DMA->CLRBLOCK = 1 << Channel;								/* ClearBlock */
	DMA->CLRSRCTRAN = 1 << Channel;								/* ClearSrcTran */
	DMA->CLRDSTTRAN = 1 << Channel;								/* ClearDstTran */

	Ptr = (DMA_Type*)((uint32_t)DMA_BASE + (uint32_t)(Channel * 0x58UL));
	Ptr->SAR0 = SrcAddr;										/* Source address is SPI address */
	Ptr->DAR0 = DesAddr;										/* Destination address is SRAM */

	// Setting Controller
	Ptr->CTRL0L_b.SINC = Dmac_addr_nochange;
	Ptr->CTRL0L_b.DINC = Dmac_addr_increment;
	Ptr->CTRL0L_b.SRCTRWIDTH = Dmac_trans_width_8;
	Ptr->CTRL0L_b.DSTTRWIDTH = Dmac_trans_width_8;
	Ptr->CTRL0L_b.SRCMSIZE = Dmac_msize_1;
	Ptr->CTRL0L_b.DESTMSIZE = Dmac_msize_1;
	Ptr->CTRL0H = Size;											/* Number of Tranfer blocks */
	Ptr->CFG0L_b.HSSELSRC =0;									/* Hardware handshake */
	Ptr->CFG0L_b.HSSELDST =0;
	// Type
	Ptr->CTRL0L_b.TTFC = Dmac_prf2mem_dma;						/* Type */
	
	HookFunction();
	Ptr->CFG0H_b.SRCPER = 1;									/* RTS5911 define SPIC RX_req connect on channel */
	
	DMA->CONF = 1;												/* Enable RTK_DMAC */
	DMA->CHEN |= Dmacchannel[Channel];							/* Enable channel */

	while(!(DMA->RAWTFR & (1 << Channel)))
	{
		//printf("Channel %x Transmit in progress \n",i);
	}
	//printf("Transmit complete \n");
}

/******************************************************************************/
/** DMAC Memory to Peripheral I/O
 * Source Address : (UINT:uint32_t)
 * Destination Address : (UINT:uint32_t)
 * Size:(UINT: uin16_t)
 * return None
*******************************************************************************/
void DMAC_MtoP(uint32_t SrcAddr, uint32_t DesAddr, uint32_t Size)
{
	uint32_t Channel;
	DMA_Type* Ptr;

	for(Channel=0;Channel<8;Channel++) {						/* DMA support 8 channel */
		if((DMA->CHEN & Dmacchannel[Channel]) != 0) {			/* Check if channel is using */
			//printf("DMA Channel %x is using Ch_en_reg_l value 0x%lx \n", i,DMAC->Ch_en_reg_l);
			continue;
		}
		break;
	}
	DMA->CLRTFR = 1 << Channel;									/* ClearTfr */
	DMA->CLRBLOCK = 1 << Channel;								/* ClearBlock */
	DMA->CLRSRCTRAN = 1 << Channel;								/* ClearSrcTran */
	DMA->CLRDSTTRAN = 1 << Channel;								/* ClearDstTran */

	Ptr = (DMA_Type*)((uint32_t)DMA_BASE + (uint32_t)(Channel * 0x58UL));
	Ptr->SAR0 = SrcAddr;										/* Source address is SPI address */
	Ptr->DAR0 = DesAddr;										/* Destination address is SRAM */

	// Setting Controller
	Ptr->CTRL0L_b.SINC = Dmac_addr_increment;
	Ptr->CTRL0L_b.DINC = Dmac_addr_nochange;
	Ptr->CTRL0L_b.SRCTRWIDTH = Dmac_trans_width_8;
	Ptr->CTRL0L_b.DSTTRWIDTH = Dmac_trans_width_8;
	Ptr->CTRL0L_b.SRCMSIZE = Dmac_msize_1;
	Ptr->CTRL0L_b.DESTMSIZE = Dmac_msize_1;
	Ptr->CTRL0H = Size;											/* Number of Tranfer blocks */
	Ptr->CFG0L_b.HSSELSRC =0;									/* Hardware handshake */
	Ptr->CFG0L_b.HSSELDST =0;
	// Type
	Ptr->CTRL0L_b.TTFC = Dmac_mem2prf_dma;						/* Type */
	
	HookFunction();
	Ptr->CFG0H_b.SRCPER = 1;									/* RTS5911 define SPIC RX_req connect on channel */
	
	DMA->CONF = 1;												/* Enable RTK_DMAC */
	DMA->CHEN |= Dmacchannel[Channel];							/* Enable channel */

	while(!(DMA->RAWTFR & (1 << Channel)))
	{
		//printf("Channel %x Transmit in progress \n",i);
	}
	//printf("Transmit complete \n");
}

void HookFunction(void)
{
	// to enable function
#ifdef  __SPIC_H__
	SPIC_DMA_En();
#endif
}

