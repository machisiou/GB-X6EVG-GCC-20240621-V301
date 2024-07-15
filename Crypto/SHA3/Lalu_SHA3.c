#include "Include.h"

void lalu_sha3_init(void)
{
	write_word(SHA3_CLEAR_SHA3,0x01);
	//SHA3->ClrSha3.BITS.ClrSh3engine = 1;
}

void lalu_sha3_clear_intr(void)
{
	write_word(SHA3_CLEAR_INTR,0x01);
	//SHA3->ClrInt.BITS.ClrInt = 1;
}

void lalu_sha3_update(const DWORD input, const DWORD size)
{
	// set start address of input
	write_word(SHA3_ADDR_DIN_START, input);
	// set input data length
	write_word(SHA3_ADDR_DIN_LEN, size-1);

	lalu_sha3_clear_intr();
	// enable sha3 engine to read input data
	write_word(SHA3_ENABLE_CMD, 0x01);
	while(1)
	{
		// wait sha3 engine done
		if(read_word(SHA3_INTERRUPT))
			break;
	}
}

void lalu_sha3_final(void)
{
	lalu_sha3_clear_intr();
	// enable sha3 engine to generate hash
	write_word(SHA3_ENABLE_CMD, 0x02);
	while(1)
	{
		// wait sha3 engine done
		if(read_word(SHA3_INTERRUPT))
			break;
	}
}

void lalu_sha3_squeeze(void)
{
	lalu_sha3_clear_intr();
	write_word(SHA3_SQUEEZE, 0x01);
	while(1)
	{
		// wait sha3 engine done
		if(read_word(SHA3_INTERRUPT))
			break;
	}

}

void lalu_sha3_hash_in(const DWORD src)
{
	DWORD i;
	for(i=0;i<50;i++)
	{
		write_word(SHA3_HASH_BASE+4*i, read_word(src+4*i));
	}
}

void lalu_sha3_hash_out(const DWORD dst)
{
	DWORD i;
	for(i=0;i<50;i++)
	{
		write_word(dst+4*i, read_word(SHA3_HASH_BASE+4*i));
	}
}

void lalu_sha3_clone(lalu_sha3_context *ctx)
{
	lalu_sha3_init();
	write_word(SHA3_SPEC_TYPE, ctx->sha3_spec);
	lalu_sha3_hash_in((DWORD)&ctx->state);
}

void write_word(DWORD test_addr, DWORD data)
{
	volatile unsigned int *addr;
	addr = (DWORD *) test_addr;
	*addr = data;
}

DWORD read_word(DWORD test_addr)
{
	volatile unsigned int *addr;
	addr = (DWORD *) test_addr;
	return *addr;
}

