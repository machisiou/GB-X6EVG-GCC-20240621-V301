#ifndef _Lalu_SHA2_H__
#define _Lalu_SHA2_H__

#define ENABLE_CH(n)	BIT(n)
#define ENABLE_CH_WRITE(n)	(1<<(n+8))

#define	 STATUS_INT_MASK			0x1F
#define	 STATUS_INT_ERR				BIT(4)
#define	 STATUS_INT_DSTT			BIT(3)
#define	 STATUS_INT_SRCT			BIT(2)
#define	 STATUS_INT_BLOCK			BIT(1)
#define	 STATUS_INT_TFR				BIT(0)

// Salve mode
#define  SHA2_CTRL_MASK				0x0000007F
#define  SHA2_CTRL_SLAVE_MODE		0x00000040
#define  SHA2_CTRL_ICG_ENABLE		BIT(5)
#define  SHA2_CTRL_SHA_MODE			BIT(4)
#define  SHA2_CTRL_BYTE_INV			BIT(3)
#define  SHA2_CTRL_DMA_MODE			BIT(2)
#define  SHA2_CTRL_RSTN_DIG			BIT(1)

#define  CH_CTRL_MASK				0xFFFF0000
#define  INT_EN						BIT(0)
#define  DST_TR_WIDTH(n)			(n<<1)
#define  SRC_TR_WIDTH(n)			(n<<4)
#define  DST_MSIZE(n)				(n<<11)
#define  SRC_MSIZE(n)				(n<<14)


#define  SHA2_MAX_FIFO_SIZE			0x10
#define  SHA2_STATUS_FIFO_MASK		0x1F
#define  SHA2_STATUS_BUSY			BIT(28)

// DMA Interrupt register
#define	 TFR_INT_MASK				0xFFFF0000
#define	 CH_INT_MASK(n)				BIT(n)
#define	 CH_INT_MASK_WE(n)			(1<<(n+8))

#define MAX_DMA_BLK_TS				4095
#define MAX_BUS_TS_SIZE8			511
#define MSIZE8_LOG2					3
#define DMA_DATA_WIDTH_LOG2			3
#define MAX_BUS_TS_SIZE16			255
#define MSIZE16_LOG2				4

#define GET_DWORD_WE(n,b,i)			\
{										\
	(n)((UINT64) (b)[(i)	] << 32ul )	\
		|((UINT64) (b)[(i) + 1ul]		);	\
}

typedef struct mbedtls_sha256_context
{
	DWORD total[2];				/*!< The number of Bytes processed.  */
	DWORD state[8];				/*!< The intermediate digest state.  */
	UINT8 buffer[64];			/*!< The data block being processed. */
	DWORD is224;
}
mbedtls_sha256_context;

typedef struct mbedtls_sha512_context
{
	UINT64 total[2];			/*!< The number of Bytes processed. */
	UINT64 state[8];			/*!< The intermediate digest state. */
	UINT8 buffer[128];			/*!< The data block being processed. */
#if defined(MBEDTLS_SHA384_C)
	DWORD is384;				/*!< Determines which function to use:0: Use SHA-512, or 1: Use SHA-384. */
#endif
}
mbedtls_sha512_context;

extern DWORD Start_sha2_dma(DWORD Phy_addr, DWORD Dma_blk_ts);
extern int32_t lalu_internal_sha256_process_remain(mbedtls_sha256_context* ctx, const UINT8 data[64]);
extern int32_t lalu_internal_sha256_process(mbedtls_sha256_context *ctx, const UINT8 data[64], DWORD  blk_size);
extern void lalu_sha256_starts_ret(DWORD is224);
extern int32_t lalu_internal_sha512_process_remain(mbedtls_sha512_context* ctx, const UINT8 data[128]);
extern int32_t lalu_internal_sha512_process(mbedtls_sha512_context *ctx, const UINT8 data[128], DWORD  blk_size);
extern void lalu_sha512_starts_ret(DWORD is384);
#endif
