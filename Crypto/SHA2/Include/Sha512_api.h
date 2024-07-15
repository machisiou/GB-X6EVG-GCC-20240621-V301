#ifndef __Sha512_api_H__
#define __Sha512_api_H__

/** SHA-512 input data was malformed. */
#define MBEDTLS_ERR_SHA512_BAD_INPUT_DATA						-0x0075
#define UL64(x) x##ULL

/**
* Get the unsigned 64 bits integer corresponding to eight bytes in
* big-endian order (MSB first).
*
* \param   data    Base address of the memory to get the eight bytes from.
* \param   offset  Offset from \p data of the first and most significant
*                  byte of the eight bytes to build the 64 bits unsigned
*                  integer from.
*/
#ifndef MBEDTLS_GET_UINT64_BE
#define MBEDTLS_GET_UINT64_BE( data, offset )					\
	(															\
		( (UINT64) ( data )[( offset )    ] << 56 )				\
		| ( (UINT64) ( data )[( offset ) + 1] << 48 )			\
		| ( (UINT64) ( data )[( offset ) + 2] << 40 )			\
		| ( (UINT64) ( data )[( offset ) + 3] << 32 )			\
		| ( (UINT64) ( data )[( offset ) + 4] << 24 )			\
		| ( (UINT64) ( data )[( offset ) + 5] << 16 )			\
		| ( (UINT64) ( data )[( offset ) + 6] <<  8 )			\
		| ( (UINT64) ( data )[( offset ) + 7]       )			\
	)
#endif


/**
* Put in memory a 64 bits unsigned integer in big-endian order.
*
* \param   n       64 bits unsigned integer to put in memory.
* \param   data    Base address of the memory where to put the 64
*                  bits unsigned integer in.
* \param   offset  Offset from \p data where to put the most significant
*                  byte of the 64 bits unsigned integer \p n.
*/
#ifndef MBEDTLS_PUT_UINT64_BE
#define MBEDTLS_PUT_UINT64_BE( n, data, offset )				\
{																\
	( data )[( offset )    ] = MBEDTLS_BYTE_7( n );				\
	( data )[( offset ) + 1] = MBEDTLS_BYTE_6( n );				\
	( data )[( offset ) + 2] = MBEDTLS_BYTE_5( n );				\
	( data )[( offset ) + 3] = MBEDTLS_BYTE_4( n );				\
	( data )[( offset ) + 4] = MBEDTLS_BYTE_3( n );				\
	( data )[( offset ) + 5] = MBEDTLS_BYTE_2( n );				\
	( data )[( offset ) + 6] = MBEDTLS_BYTE_1( n );				\
	( data )[( offset ) + 7] = MBEDTLS_BYTE_0( n );				\
}
#endif

/**
* Get the unsigned 64 bits integer corresponding to eight bytes in
* little-endian order (LSB first).
*
* \param   data    Base address of the memory to get the eight bytes from.
* \param   offset  Offset from \p data of the first and least significant
*                  byte of the eight bytes to build the 64 bits unsigned
*                  integer from.
*/
#ifndef MBEDTLS_GET_UINT64_LE
#define MBEDTLS_GET_UINT64_LE( data, offset )					\
	(															\
		( (UINT64) ( data )[( offset ) + 7] << 56 )				\
		| ( (UINT64) ( data )[( offset ) + 6] << 48 )			\
		| ( (UINT64) ( data )[( offset ) + 5] << 40 )			\
		| ( (UINT64) ( data )[( offset ) + 4] << 32 )			\
		| ( (UINT64) ( data )[( offset ) + 3] << 24 )			\
		| ( (UINT64) ( data )[( offset ) + 2] << 16 )			\
		| ( (UINT64) ( data )[( offset ) + 1] <<  8 )			\
		| ( (UINT64) ( data )[( offset )    ]       )			\
	)
#endif

extern void mbedtls_sha512_init( mbedtls_sha512_context *ctx );
extern void mbedtls_sha512_free( mbedtls_sha512_context *ctx );
extern void mbedtls_sha512_clone( mbedtls_sha512_context *dst,const mbedtls_sha512_context *src );
extern int32_t mbedtls_sha512_starts( mbedtls_sha512_context *ctx, DWORD is384 );
extern int32_t mbedtls_internal_sha512_process( mbedtls_sha512_context *ctx,const UINT8 data[128] );
extern int32_t mbedtls_sha512_update( mbedtls_sha512_context *ctx,const unsigned char *input,size_t ilen );
extern int32_t mbedtls_sha512_finish( mbedtls_sha512_context *ctx,UINT8 *output );
extern int32_t mbedtls_sha512( const UINT8 *input,size_t ilen,UINT8 *output,DWORD is384 );
#endif

