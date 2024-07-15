/****************************************************************************/
/*																			*/
/*		(C)Copyright 2022- Realtek Inc.										*/
/*		All Rights Reserved.												*/
/*																			*/
/*						 													*/
/****************************************************************************/

//Common
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

//Type
#include "system/Type.h"
#include "config.h"
#include "hal/DMA.h"
#include "chip/rts5911/RTS5911.h"

typedef	signed char					INT8;
typedef	unsigned char				UINT8;
typedef	short						INT16;
typedef	unsigned short				UINT16;
typedef	int							INT32;
typedef	unsigned int				UINT32;
typedef signed long long			INT64;
typedef unsigned long long			UINT64;

typedef	unsigned int				DWORD;

// Crypto AES
#include "AES\Include\RTK_dmac_defs.h"
#include "AES\Include\RTK_common_io.h"
#include "AES\Include\RTK_common_list.h"
#include "AES\Include\RTK_common_types.h"
#include "AES\Include\RTK_common_bitops.h"
#include "AES\Include\RTK_common_dbc.h"
#include "AES\Include\RTK_common_errno.h"
#include "AES\Include\RTK_dmac_private.h"
#include "AES\Include\RTK_dmac_public.h"
#include "AES\Include\mbedtls_config.h"
#include "AES\Include\private_access.h"
#include "AES\Include\build_info.h"
#include "AES\Include\platform_time.h"
#include "AES\Include\check_config.h"
#include "AES\Include\platform_util.h"
#include "AES\Include\error.h"
#include "AES\Include\platform.h"
#include "AES\Include\aes.h"
#include "AES\Include\common.h"
#include "AES\Include\AES_Slave.h"

// Crypto SHA2
#include "SHA2\Include\Lalu_SHA2.h"
#include "SHA2\Include\Sha256_api.h"
#include "SHA2\Include\Sha512_api.h"

// Crypto SHA3
#include "SHA3\Include\Lalu_SHA3.h"
#include "SHA3\Include\keccak.h"
#include "SHA3\Include\shake.h"
#include "SHA3\Include\Sha3.h"

// Crypto HMAC
#include "HMAC\md.h"
#include "HMAC\md_wrap.h"

//*****************************************************************************
//*****************************************************************************
//**																		 **
//**		Copyright 2022- Realtek Inc.									 **
//**		All Rights Reserved.											 **
//**																		 **
//*****************************************************************************
//*****************************************************************************