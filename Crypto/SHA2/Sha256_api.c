#include "Include.h"

#define SHA256_VALIDATE_RET(cond)							\
	MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_SHA256_BAD_INPUT_DATA )
#define SHA256_VALIDATE(cond)  MBEDTLS_INTERNAL_VALIDATE( cond )


void mbedtls_sha256_init( mbedtls_sha256_context *ctx )
{
	SHA256_VALIDATE( ctx != NULL );

	memset( ctx, 0, sizeof( mbedtls_sha256_context ) );
}

void mbedtls_platform_zeroize( void *buf, size_t len )
{
	MBEDTLS_INTERNAL_VALIDATE( len == 0 || buf != NULL );

	if( len > 0 )
		memset( buf, 0, len );
}


#if !defined(MBEDTLS_SHA256_PROCESS_ALT)
static const DWORD K[] =
{
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
	0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
	0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
};

#define  SHR(x,n) (((x) & 0xFFFFFFFF) >> (n))
#define ROTR(x,n) (SHR(x,n) | ((x) << (32 - (n))))

#define S0(x) (ROTR(x, 7) ^ ROTR(x,18) ^  SHR(x, 3))
#define S1(x) (ROTR(x,17) ^ ROTR(x,19) ^  SHR(x,10))

#define S2(x) (ROTR(x, 2) ^ ROTR(x,13) ^ ROTR(x,22))
#define S3(x) (ROTR(x, 6) ^ ROTR(x,11) ^ ROTR(x,25))

#define F0(x,y,z) (((x) & (y)) | ((z) & ((x) | (y))))
#define F1(x,y,z) ((z) ^ ((x) & ((y) ^ (z))))

#define R(t)														\
	(																\
		local.W[t] = S1(local.W[(t) -  2]) + local.W[(t) -  7] +	\
		S0(local.W[(t) - 15]) + local.W[(t) - 16]					\
    )

#define P(a,b,c,d,e,f,g,h,x,K)										\
	do																\
	{																\
		local.temp1 = (h) + S3(e) + F1((e),(f),(g)) + (K) + (x);	\
		local.temp2 = S2(a) + F0((a),(b),(c));						\
		(d) += local.temp1; (h) = local.temp1 + local.temp2;		\
	} while( 0 )

int32_t mbedtls_internal_sha256_process( mbedtls_sha256_context *ctx,
								const UINT8 data[64] )
{
	struct
	{
		DWORD temp1, temp2, W[64];
		DWORD A[8];
	} local;

	unsigned int i;
	printf("mbedtls_internal_sha256_process\n");

	//SHA256_VALIDATE_RET( ctx != NULL );
	//SHA256_VALIDATE_RET( (const unsigned char *)data != NULL );

	for( i = 0; i < 8; i++ )
		local.A[i] = ctx->state[i];

#if defined(MBEDTLS_SHA256_SMALLER)
	for( i = 0; i < 64; i++ )
	{
		if( i < 16 )
			local.W[i] = MBEDTLS_GET_UINT32_BE( data, 4 * i );
		else
			R( i );

		P( local.A[0], local.A[1], local.A[2], local.A[3], local.A[4],
			local.A[5], local.A[6], local.A[7], local.W[i], K[i] );

		local.temp1 = local.A[7]; local.A[7] = local.A[6];
		local.A[6] = local.A[5]; local.A[5] = local.A[4];
		local.A[4] = local.A[3]; local.A[3] = local.A[2];
		local.A[2] = local.A[1]; local.A[1] = local.A[0];
		local.A[0] = local.temp1;
	}
#else /* MBEDTLS_SHA256_SMALLER */
	for( i = 0; i < 16; i++ )
		local.W[i] = MBEDTLS_GET_UINT32_BE( data, 4 * i );

	for( i = 0; i < 16; i += 8 )
	{
		P( local.A[0], local.A[1], local.A[2], local.A[3], local.A[4],
			local.A[5], local.A[6], local.A[7], local.W[i+0], K[i+0] );
		P( local.A[7], local.A[0], local.A[1], local.A[2], local.A[3],
			local.A[4], local.A[5], local.A[6], local.W[i+1], K[i+1] );
		P( local.A[6], local.A[7], local.A[0], local.A[1], local.A[2],
			local.A[3], local.A[4], local.A[5], local.W[i+2], K[i+2] );
		P( local.A[5], local.A[6], local.A[7], local.A[0], local.A[1],
			local.A[2], local.A[3], local.A[4], local.W[i+3], K[i+3] );
		P( local.A[4], local.A[5], local.A[6], local.A[7], local.A[0],
			local.A[1], local.A[2], local.A[3], local.W[i+4], K[i+4] );
		P( local.A[3], local.A[4], local.A[5], local.A[6], local.A[7],
			local.A[0], local.A[1], local.A[2], local.W[i+5], K[i+5] );
		P( local.A[2], local.A[3], local.A[4], local.A[5], local.A[6],
			local.A[7], local.A[0], local.A[1], local.W[i+6], K[i+6] );
		P( local.A[1], local.A[2], local.A[3], local.A[4], local.A[5],
			local.A[6], local.A[7], local.A[0], local.W[i+7], K[i+7] );
	}

	for( i = 16; i < 64; i += 8 )
	{
		P( local.A[0], local.A[1], local.A[2], local.A[3], local.A[4],
			local.A[5], local.A[6], local.A[7], R(i+0), K[i+0] );
		P( local.A[7], local.A[0], local.A[1], local.A[2], local.A[3],
			local.A[4], local.A[5], local.A[6], R(i+1), K[i+1] );
		P( local.A[6], local.A[7], local.A[0], local.A[1], local.A[2],
			local.A[3], local.A[4], local.A[5], R(i+2), K[i+2] );
		P( local.A[5], local.A[6], local.A[7], local.A[0], local.A[1],
			local.A[2], local.A[3], local.A[4], R(i+3), K[i+3] );
		P( local.A[4], local.A[5], local.A[6], local.A[7], local.A[0],
			local.A[1], local.A[2], local.A[3], R(i+4), K[i+4] );
		P( local.A[3], local.A[4], local.A[5], local.A[6], local.A[7],
			local.A[0], local.A[1], local.A[2], R(i+5), K[i+5] );
		P( local.A[2], local.A[3], local.A[4], local.A[5], local.A[6],
			local.A[7], local.A[0], local.A[1], R(i+6), K[i+6] );
		P( local.A[1], local.A[2], local.A[3], local.A[4], local.A[5],
			local.A[6], local.A[7], local.A[0], R(i+7), K[i+7] );
	}
#endif /* MBEDTLS_SHA256_SMALLER */

	for( i = 0; i < 8; i++ )
		ctx->state[i] += local.A[i];

	/* Zeroise buffers and variables to clear sensitive data from memory. */
	mbedtls_platform_zeroize( &local, sizeof( local ) );

	return( 0 );
}

#endif /* !MBEDTLS_SHA256_PROCESS_ALT */


/*
* SHA-256 context setup
*/
int32_t mbedtls_sha256_starts( mbedtls_sha256_context *ctx, DWORD is224 )
{
	SHA256_VALIDATE_RET( ctx != NULL );

#if defined(MBEDTLS_SHA224_C)
		SHA256_VALIDATE_RET( is224 == 0 || is224 == 1 );
#else
		SHA256_VALIDATE_RET( is224 == 0 );
#endif

	ctx->total[0] = 0;
	ctx->total[1] = 0;

#if defined CONFIG_ENABLE_LALU_SHA2
	lalu_sha256_starts_ret(is224);
#else
	if( is224 == 0 )
	{
		/* SHA-256 */
		ctx->state[0] = 0x6A09E667;
		ctx->state[1] = 0xBB67AE85;
		ctx->state[2] = 0x3C6EF372;
		ctx->state[3] = 0xA54FF53A;
		ctx->state[4] = 0x510E527F;
		ctx->state[5] = 0x9B05688C;
		ctx->state[6] = 0x1F83D9AB;
		ctx->state[7] = 0x5BE0CD19;
	}
	else
	{
#if defined MBEDTLS_SHA224_C
		/* SHA-224 */
		ctx->state[0] = 0xC1059ED8;
		ctx->state[1] = 0x367CD507;
		ctx->state[2] = 0x3070DD17;
		ctx->state[3] = 0xF70E5939;
		ctx->state[4] = 0xFFC00B31;
		ctx->state[5] = 0x68581511;
		ctx->state[6] = 0x64F98FA7;
		ctx->state[7] = 0xBEFA4FA4;
#endif
	}
#endif
	ctx->is224 = is224;

	return( 0 );
}


/*
 * SHA-256 process buffer
 */
int32_t mbedtls_sha256_update( mbedtls_sha256_context *ctx,
								const UINT8 *input,
								DWORD ilen )
{
	int32_t ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
	DWORD fill;
	DWORD left;
#if defined CONFIG_ENABLE_LALU_SHA2
	DWORD blk_size;
#endif
	SHA256_VALIDATE_RET( ctx != NULL );
	SHA256_VALIDATE_RET( ilen == 0 || input != NULL );

	if( ilen == 0 )
		return( 0 );

	left = ctx->total[0] & 0x3F;
	fill = 64 - left;

	ctx->total[0] += (DWORD) ilen;
	ctx->total[0] &= 0xFFFFFFFF;

	if( ctx->total[0] < (DWORD) ilen )
		ctx->total[1]++;

	if( left && ilen >= fill )
	{
		memcpy( (void *) (ctx->buffer + left), input, fill );

#if defined CONFIG_ENABLE_LALU_SHA2
#if defined SLAVE_MODE
		/* Add slave mode block < 1 ctx->buffer, 64 byte */
		if( ( ret = lalu_internal_sha256_process_remain( ctx, ctx->buffer ) ) != 0 )
			return( ret );
#else
		if( ( ret = lalu_internal_sha256_process( ctx, ctx->buffer,0x1 ) ) != 0 )
			return( ret );
#endif
#else
		if( ( ret = mbedtls_internal_sha256_process( ctx, ctx->buffer ) ) != 0 )
			return( ret );
#endif
		input += fill;
		ilen  -= fill;
		left = 0;
	}

	while( ilen >= 64 )
	{
#if defined CONFIG_ENABLE_LALU_SHA2
		blk_size = ilen >> 6;
		if ((ret = lalu_internal_sha256_process(ctx, input, blk_size)) != 0)
			return ret;

		input += (blk_size << 6);
		ilen -= (blk_size << 6);
#else
		if( ( ret = mbedtls_internal_sha256_process( ctx, input ) ) != 0 )
			return( ret );

		input += 64;
		ilen  -= 64;
#endif
	}

	if( ilen > 0 )
		memcpy( (void *) (ctx->buffer + left), input, ilen );

	return( 0 );
}

/*
 * SHA-256 final digest
 */
int32_t mbedtls_sha256_finish( mbedtls_sha256_context *ctx,
								UINT8 *output )
{
	int32_t ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
	DWORD used;
	DWORD high, low;

	SHA256_VALIDATE_RET( ctx != NULL );
	SHA256_VALIDATE_RET( (UINT8 *)output != NULL );

	/*
	* Add padding: 0x80 then 0x00 until 8 bytes remain for the length
	*/
	used = ctx->total[0] & 0x3F;

	ctx->buffer[used++] = 0x80;

	if( used <= 56 )
	{
		/* Enough room for padding + length in current block */
		memset( ctx->buffer + used, 0, 56 - used );
	}
	else
	{
		/* We'll need an extra block */
		memset( ctx->buffer + used, 0, 64 - used );

#if defined CONFIG_ENABLE_LALU_SHA2
#if defined SLAVE_MODE
		/* Add slave mode block < 1 ctx->buffer, 64 byte */
		if( ( ret = lalu_internal_sha256_process_remain( ctx, ctx->buffer ) ) != 0 )
			return( ret );
#else
		if( ( ret = lalu_internal_sha256_process( ctx, ctx->buffer,0x1 ) ) != 0 )
			return( ret );
#endif
#else
		if( ( ret = mbedtls_internal_sha256_process( ctx, ctx->buffer ) ) != 0 )
		return( ret );
#endif
		memset( ctx->buffer, 0, 56 );
	}

	/*
	* Add message length
	*/
	high = ( ctx->total[0] >> 29 )
		| ( ctx->total[1] <<  3 );
	low  = ( ctx->total[0] <<  3 );

	MBEDTLS_PUT_UINT32_BE( high, ctx->buffer, 56 )
	MBEDTLS_PUT_UINT32_BE( low,  ctx->buffer, 60 )

#if defined CONFIG_ENABLE_LALU_SHA2
#if defined SLAVE_MODE
	/* Add slave mode block < 1 ctx->buffer, 64 byte */
	if( ( ret = lalu_internal_sha256_process_remain( ctx, ctx->buffer ) ) != 0 )
		return( ret );
#else
	if( ( ret = lalu_internal_sha256_process( ctx, ctx->buffer,0x1 ) ) != 0 )
		return( ret );
#endif
#else
	if( ( ret = mbedtls_internal_sha256_process( ctx, ctx->buffer ) ) != 0 )
		return( ret );
#endif
	/*
	* Output final state
	*/
	MBEDTLS_PUT_UINT32_BE( ctx->state[0], output,  0 )
	MBEDTLS_PUT_UINT32_BE( ctx->state[1], output,  4 )
	MBEDTLS_PUT_UINT32_BE( ctx->state[2], output,  8 )
	MBEDTLS_PUT_UINT32_BE( ctx->state[3], output, 12 )
	MBEDTLS_PUT_UINT32_BE( ctx->state[4], output, 16 )
	MBEDTLS_PUT_UINT32_BE( ctx->state[5], output, 20 )
	MBEDTLS_PUT_UINT32_BE( ctx->state[6], output, 24 )

#if defined(MBEDTLS_SHA224_C)
	if( ctx->is224 == 0 )
#endif
		MBEDTLS_PUT_UINT32_BE( ctx->state[7], output, 28 )

	return( 0 );
}

void mbedtls_sha256_free( mbedtls_sha256_context *ctx )
{
	if( ctx == NULL )
		return;

	mbedtls_platform_zeroize( ctx, sizeof( mbedtls_sha256_context ) );
}

int32_t mbedtls_sha256( const UINT8 *input,
						DWORD ilen,
						UINT8 *output,
						DWORD is224 )
{
	int32_t ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
	mbedtls_sha256_context ctx;

#if defined(MBEDTLS_SHA224_C)
	SHA256_VALIDATE_RET( is224 == 0 || is224 == 1 );
#else
	SHA256_VALIDATE_RET( is224 == 0 );
#endif

	SHA256_VALIDATE_RET( ilen == 0 || input != NULL );
	SHA256_VALIDATE_RET( (UINT8 *)output != NULL );

	mbedtls_sha256_init( &ctx );

	if( ( ret = mbedtls_sha256_starts( &ctx, is224 ) ) != 0 )
		goto exit;

	if( ( ret = mbedtls_sha256_update( &ctx, input, ilen ) ) != 0 )
		goto exit;

	if( ( ret = mbedtls_sha256_finish( &ctx, output ) ) != 0 )
		goto exit;

exit:
	mbedtls_sha256_free( &ctx );

	return( ret );
}

void mbedtls_sha256_clone( mbedtls_sha256_context *dst,const mbedtls_sha256_context *src )
{
	SHA256_VALIDATE( dst != NULL );
	SHA256_VALIDATE( src != NULL );

	*dst = *src;
}

