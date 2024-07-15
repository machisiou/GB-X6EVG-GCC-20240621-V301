#include "Include.h"

// DMA mode

DWORD Start_sha2_dma(DWORD Phy_addr, DWORD Dma_blk_ts)
{
	DWORD Ch_en = 0, ret =0;
	SHA2DMA->SAR = Phy_addr;	
	// Number of Tranfer blocks
	SHA2DMA->CTRLH = Dma_blk_ts;
	
	Ch_en = (ENABLE_CH(0)|ENABLE_CH_WRITE(0));
	SHA2DMA->CHEN = Ch_en;
	
	while(!(SHA2DMA->INTSTS & STATUS_INT_MASK))
	{
		if(((SHA2DMA->INTSTS & STATUS_INT_MASK) & STATUS_INT_ERR))
			return SHA2DMA->INTSTS;
	}

	// Clear interrupt
	SHA2DMA->CLRTFR = 0x1;
	
	return ret;	

}


// Salve mode

int32_t lalu_internal_sha256_process_remain(mbedtls_sha256_context* ctx, const UINT8 data[64])
{
	DWORD i;
	DWORD sent_len = 0;
	DWORD len = 0;
	DWORD size = sizeof(ctx->buffer) / sizeof(ctx->buffer[0]);
	printf("lalu_internal_sha256_process_remain \n");
	//change to slave mode
	SHA2->CTRL = (SHA2->CTRL & SHA2_CTRL_MASK) | SHA2_CTRL_SLAVE_MODE;

	//transfer data to sha2 fifo
	while(sent_len < size)
	{
		len = SHA2->STS  & SHA2_STATUS_FIFO_MASK;
		for(i=0;i<len;i++)
		{
			SHA2->FIFOIN = data[i+sent_len];
		}
		sent_len += len;	
	}

	// CHECK Sha2 engine finish
	while((SHA2->STS & SHA2_STATUS_BUSY));

	// Change to DMA mode
	SHA2->CTRL = (SHA2->CTRL & SHA2_CTRL_MASK) &  (DWORD)~SHA2_CTRL_SLAVE_MODE;

	return 0;
}

int32_t lalu_internal_sha512_process_remain(mbedtls_sha512_context* ctx, const UINT8 data[128])
{
	DWORD i;
	DWORD sent_len = 0;
	DWORD len = 0;
	DWORD size = sizeof(ctx->buffer) / sizeof(ctx->buffer[0]);
	printf("lalu_internal_sha512_process_remain \n");
	//change to slave mode
	SHA2->CTRL = (SHA2->CTRL & SHA2_CTRL_MASK) | SHA2_CTRL_SLAVE_MODE;

	//transfer data to sha2 fifo
	while(sent_len < size)
	{
		len = SHA2->STS  & SHA2_STATUS_FIFO_MASK;
		for(i=0;i<len;i++)
		{
			SHA2->FIFOIN = data[i+sent_len];
		}
		sent_len += len;	
	}

	// CHECK Sha2 engine finish
	while((SHA2->STS & SHA2_STATUS_BUSY));

	// Change to DMA mode
	SHA2->CTRL = (SHA2->CTRL & SHA2_CTRL_MASK) &  (DWORD)~SHA2_CTRL_SLAVE_MODE;

	return 0;
}


// DMA mode
// Transfer sha2 block by DMA
int32_t lalu_internal_sha256_process(mbedtls_sha256_context *ctx, const UINT8 data[64], DWORD  blk_size)
{
	DWORD  i;
	DWORD  phy_addr;
	
	phy_addr = (DWORD)(data);
//	printf("lalu_internal_sha256_process\n");
	while(blk_size>0)
	{
		if(blk_size>MAX_BUS_TS_SIZE8)
		{
			Start_sha2_dma(phy_addr,MAX_BUS_TS_SIZE16<<MSIZE8_LOG2);
			phy_addr += MAX_BUS_TS_SIZE8<<MSIZE8_LOG2<<DMA_DATA_WIDTH_LOG2;
			blk_size -=MAX_BUS_TS_SIZE8;
		}
		else
		{
			Start_sha2_dma(phy_addr, blk_size<<MSIZE8_LOG2);
			break;
		}
	}
	for(i=0;i<8;i++)
	{
		ctx->state[i] = SHA2->DIGEST[(i<<1)];
	}
	return 0;
}

int32_t lalu_internal_sha512_process(mbedtls_sha512_context *ctx, const UINT8 data[128], DWORD  blk_size)
{
	DWORD  i;
	DWORD  phy_addr;
	
	phy_addr = (DWORD)(data);
	printf("lalu_internal_sha512_process\n");
	// may need to translate address for lalu psm
	while(blk_size>0)
	{
		// message into multiple DMAC transfer blocks
		// the block size should <= max DMAC supported size
		// the block size should >= single sha512 block size
		if(blk_size>MAX_BUS_TS_SIZE16)
		{
			Start_sha2_dma(phy_addr,MAX_BUS_TS_SIZE16<<MSIZE16_LOG2);
			phy_addr += MAX_BUS_TS_SIZE16<<MSIZE16_LOG2<<DMA_DATA_WIDTH_LOG2;
			blk_size -=MAX_BUS_TS_SIZE16;
		}
		else
		{
			Start_sha2_dma(phy_addr, blk_size<<MSIZE16_LOG2);
			break;
		}
	}
	for(i=0;i<8;i++)
	{
		//GET_DWORD_WE(ctx->state[i],SHA2->DIGEST,i<<1)
		ctx->state[i] = ((UINT64) SHA2->DIGEST[i<<1] << 32) 
						| ((UINT64)SHA2->DIGEST[(i<<1)+1]);
	}
	return 0;
}


void lalu_sha256_starts_ret(DWORD is224)
{
//	printf("lalu_sha256_starts_ret\n");
	// Icg en, sha256, byte-swap, read only, 0x28	
	SHA2->CTRL  = ((SHA2->CTRL & SHA2_CTRL_MASK)|SHA2_CTRL_ICG_ENABLE|SHA2_CTRL_BYTE_INV) & (DWORD)~SHA2_CTRL_SHA_MODE;
	
	if(is224==0)
	{
		// ctrl:0x2A
		SHA2->CTRL = ((SHA2->CTRL & SHA2_CTRL_MASK)|SHA2_CTRL_ICG_ENABLE|SHA2_CTRL_BYTE_INV) | SHA2_CTRL_RSTN_DIG;
	}
	else
	{
		#if defined(MBEDTLS_SHA224_C)
		SHA2->DIGEST[(0<<1)]=0xC1059ED8;
		SHA2->DIGEST[(1<<1)]=0x367CD507;
		SHA2->DIGEST[(2<<1)]=0x3070DD17;
		SHA2->DIGEST[(3<<1)]=0xF70E5939;
		SHA2->DIGEST[(4<<1)]=0xFFC00B31;
		SHA2->DIGEST[(5<<1)]=0x68581511;
		SHA2->DIGEST[(6<<1)]=0x64F98FA7;
		SHA2->DIGEST[(7<<1)]=0xBEFA4FA4;

		for(DWORD i=0;i<8;i++)
		{
			SHA2->DIGEST[(i<<1)+1]=0;
		}	
		#endif
	}
	
	SHA2DMA->CONF = 0x1;
	SHA2DMA->CFG = 0x0;
	SHA2DMA->DAR=0x0;
	// rmsize = 8, wmsize = 1, 0x37
	SHA2DMA->CTRLL = (SHA2DMA->CTRLL & CH_CTRL_MASK)|INT_EN|DST_TR_WIDTH(3)|SRC_TR_WIDTH(3)|DST_MSIZE(0)|SRC_MSIZE(2);
	SHA2DMA->MSKTFR =(SHA2DMA->MSKTFR & TFR_INT_MASK)|CH_INT_MASK(0)|CH_INT_MASK_WE(0);
	SHA2DMA->RESERVED4[1]= 0x0;
}

void lalu_sha512_starts_ret(DWORD is384)
{
	printf("lalu_sha512_starts_ret\n");
	// Icg en, sha2 512, byte-swap, read only, 0x38	
	SHA2->CTRL  = (SHA2->CTRL & SHA2_CTRL_MASK) 
												| SHA2_CTRL_ICG_ENABLE 
												| SHA2_CTRL_BYTE_INV 
												| SHA2_CTRL_SHA_MODE;

	if(is384==0)
	{
		// SHA 512
		SHA2->DIGEST[0] = 0x6A09E667;
		SHA2->DIGEST[1] = 0xF3BCC908;
		SHA2->DIGEST[2] = 0xBB67AE85;
		SHA2->DIGEST[3] = 0x84CAA73B;
		SHA2->DIGEST[4] = 0x3C6EF372;
		SHA2->DIGEST[5] = 0xFE94F82B;
		SHA2->DIGEST[6] = 0xA54FF53A;
		SHA2->DIGEST[7] = 0x5F1D36F1;
		SHA2->DIGEST[8] = 0x510E527F;
		SHA2->DIGEST[9] = 0xADE682D1;
		SHA2->DIGEST[10] = 0x9B05688C;
		SHA2->DIGEST[11] = 0x2B3E6C1F;
		SHA2->DIGEST[12] = 0x1F83D9AB;
		SHA2->DIGEST[13] = 0xFB41BD6B;
		SHA2->DIGEST[14] = 0x5BE0CD19;
		SHA2->DIGEST[15] = 0x137E2179;
	}
	else
	{
		// SHA-384, Ctrl:0x3A
		SHA2->CTRL  = (SHA2->CTRL & SHA2_CTRL_MASK) 
													| SHA2_CTRL_ICG_ENABLE 
													| SHA2_CTRL_BYTE_INV 
													| SHA2_CTRL_SHA_MODE
													| SHA2_CTRL_RSTN_DIG;
	}
	
	SHA2DMA->CONF = 0x1;
	SHA2DMA->CFG = 0x0;
	SHA2DMA->DAR=0x0;
	// rmsize = 16, wmsize = 1, 0x37
	SHA2DMA->CTRLL = (SHA2DMA->CTRLL & CH_CTRL_MASK)	|INT_EN
																			|DST_TR_WIDTH(3)
																			|SRC_TR_WIDTH(3)
																			|DST_MSIZE(0)
																			|SRC_MSIZE(3);
	SHA2DMA->MSKTFR =(SHA2DMA->MSKTFR & TFR_INT_MASK)	|CH_INT_MASK(0)
															|CH_INT_MASK_WE(0);
	SHA2DMA->RESERVED4[1]= 0x0;
}

