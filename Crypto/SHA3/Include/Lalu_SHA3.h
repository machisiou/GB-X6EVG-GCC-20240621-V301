#ifndef __Lalu_SHA3_H__
#define __Lalu_SHA3_H__

typedef struct
{
	DWORD sha3_spec;
	DWORD state[50];
}
lalu_sha3_context;

#define SHA3_ADDR                   0x40002000UL

#define SHA3_ADDR_DIN_START	(SHA3_ADDR + 0x00)
#define SHA3_ADDR_DIN_LEN	(SHA3_ADDR + 0x04)
#define SHA3_SPEC_TYPE		(SHA3_ADDR + 0x08)
#define SHA3_DISABLE_INTR	(SHA3_ADDR + 0x0C)
#define SHA3_DISABLE_LP		(SHA3_ADDR + 0x10)
#define SHA3_ENABLE_CMD		(SHA3_ADDR + 0x14)
#define	SHA3_CLEAR_SHA3		(SHA3_ADDR + 0x18)
#define	SHA3_CLEAR_INTR		(SHA3_ADDR + 0x1C)
#define	SHA3_SQUEEZE		(SHA3_ADDR + 0x20)
#define	SHA3_INTERRUPT		(SHA3_ADDR + 0x24)
#define SHA3_INFO			(SHA3_ADDR + 0x28)
#define SHA3_ERR_CONDITION	(SHA3_ADDR + 0x2C)
#define	SHA3_ERR_ADDR		(SHA3_ADDR + 0x30)
#define	SHA3_HASH_BASE		(SHA3_ADDR + 0x34)

extern void lalu_sha3_init(void);
extern void lalu_sha3_clear_intr(void);
extern void lalu_sha3_update(const DWORD input, const DWORD size);
extern void lalu_sha3_final(void);
extern void lalu_sha3_squeeze(void);
extern void lalu_sha3_hash_in(const DWORD src);
extern void lalu_sha3_hash_out(const DWORD dst);
extern void lalu_sha3_clone(lalu_sha3_context *ctx);

extern void write_word(DWORD test_addr, DWORD data);
extern DWORD read_word(DWORD test_addr);

#endif
