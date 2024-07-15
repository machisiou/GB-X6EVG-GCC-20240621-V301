#ifndef __Sha256_api_H__
#define __Sha256_api_H__

#define MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED	-0x006E	/**< This is a bug in the library */
/** SHA-256 input data was malformed. */
#define MBEDTLS_ERR_SHA256_BAD_INPUT_DATA		-0x0074

/** Byte Reading Macros
*
* Given a multi-byte integer \p x, MBEDTLS_BYTE_n retrieves the n-th
* byte from x, where byte 0 is the least significant byte.
*/
//#define MBEDTLS_BYTE_0( x ) ( (UINT8) (   ( x )         & 0xff ) )
//#define MBEDTLS_BYTE_1( x ) ( (UINT8) ( ( ( x ) >> 8  ) & 0xff ) )
//#define MBEDTLS_BYTE_2( x ) ( (UINT8) ( ( ( x ) >> 16 ) & 0xff ) )
//#define MBEDTLS_BYTE_3( x ) ( (UINT8) ( ( ( x ) >> 24 ) & 0xff ) )
//#define MBEDTLS_BYTE_4( x ) ( (UINT8) ( ( ( x ) >> 32 ) & 0xff ) )
//#define MBEDTLS_BYTE_5( x ) ( (UINT8) ( ( ( x ) >> 40 ) & 0xff ) )
//#define MBEDTLS_BYTE_6( x ) ( (UINT8) ( ( ( x ) >> 48 ) & 0xff ) )
//#define MBEDTLS_BYTE_7( x ) ( (UINT8) ( ( ( x ) >> 56 ) & 0xff ) )


/**
* Get the unsigned 32 bits integer corresponding to four bytes in
* big-endian order (MSB first).
*
* \param	data	Base address of the memory to get the four bytes from.
* \param	offset	Offset from \p data of the first and most significant
*					byte of the four bytes to build the 32 bits unsigned
*					integer from.
*/

//#ifndef MBEDTLS_GET_UINT32_BE
//#define MBEDTLS_GET_UINT32_BE( data , offset )					\
//	(															\
//		( (DWORD) ( data )[( offset )    ] << 24 )				\
//		| ( (DWORD) ( data )[( offset ) + 1] << 16 )			\
//		| ( (DWORD) ( data )[( offset ) + 2] <<  8 )			\
//		| ( (DWORD) ( data )[( offset ) + 3]       )			\
//	)
//#endif

/**
* Put in memory a 32 bits unsigned integer in big-endian order.
*
* \param   n       32 bits unsigned integer to put in memory.
* \param   data    Base address of the memory where to put the 32
*                  bits unsigned integer in.
* \param   offset  Offset from \p data where to put the most significant
*                  byte of the 32 bits unsigned integer \p n.
*/
//#ifndef MBEDTLS_PUT_UINT32_BE
//#define MBEDTLS_PUT_UINT32_BE( n, data, offset )				\
//{																\
//	( data )[( offset )    ] = MBEDTLS_BYTE_3( n );				\
//	( data )[( offset ) + 1] = MBEDTLS_BYTE_2( n );				\
//	( data )[( offset ) + 2] = MBEDTLS_BYTE_1( n );				\
//	( data )[( offset ) + 3] = MBEDTLS_BYTE_0( n );				\
//}
//#endif

extern void mbedtls_sha256_init( mbedtls_sha256_context *ctx );
extern void mbedtls_sha256_free( mbedtls_sha256_context *ctx );
extern void mbedtls_platform_zeroize( void *buf, size_t len );
extern int32_t mbedtls_sha256_starts( mbedtls_sha256_context *ctx, DWORD is224 );
extern int32_t mbedtls_internal_sha256_process( mbedtls_sha256_context *ctx,const UINT8 data[64] );
extern int32_t mbedtls_sha256_update( mbedtls_sha256_context *ctx,const UINT8 *input,DWORD ilen );
extern int32_t mbedtls_sha256_finish( mbedtls_sha256_context *ctx,UINT8 *output );
extern int32_t mbedtls_sha256( const UINT8 *input,DWORD ilen,UINT8 *output,DWORD is224 );
extern void mbedtls_sha256_clone( mbedtls_sha256_context *dst, const mbedtls_sha256_context *src );

#endif
