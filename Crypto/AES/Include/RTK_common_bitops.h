#ifndef __RTK_Common_bitops_H__
#define __RTK_Common_bitops_H__

#define	RTK_BIT0		0x00000001
#define	RTK_BIT1		0x00000002
#define	RTK_BIT2		0x00000004
#define	RTK_BIT3		0x00000008
#define	RTK_BIT4		0x00000010
#define	RTK_BIT5		0x00000020
#define	RTK_BIT6		0x00000040
#define	RTK_BIT7		0x00000080
#define	RTK_BIT8		0x00000100
#define	RTK_BIT9		0x00000200
#define	RTK_BIT10		0x00000400
#define	RTK_BIT11		0x00000800
#define	RTK_BIT12		0x00001000
#define	RTK_BIT13		0x00002000
#define	RTK_BIT14		0x00004000
#define	RTK_BIT15		0x00008000
#define	RTK_BIT16		0x00010000
#define	RTK_BIT17		0x00020000
#define	RTK_BIT18		0x00040000
#define	RTK_BIT19		0x00080000
#define	RTK_BIT20		0x00100000
#define	RTK_BIT21		0x00200000
#define	RTK_BIT22		0x00400000
#define	RTK_BIT23		0x00800000
#define	RTK_BIT24		0x01000000
#define	RTK_BIT25		0x02000000
#define	RTK_BIT26		0x04000000
#define	RTK_BIT27		0x08000000
#define	RTK_BIT28		0x10000000
#define	RTK_BIT29		0x20000000
#define	RTK_BIT30		0x40000000
#define	RTK_BIT31		0x80000000
#define RTK_BITS_ALL	0xFFFFFFFF

#define RTK_BIT_WIDTH(__bfws)	((uint32_t)(bfw ## __bfws))

#define RTK_BIT_OFFSET(__bfws)	((uint32_t)(bfo ## __bfws))

#define RTK_BITS_MASK(__bfws, __bits)	((uint32_t)((__bfws)==32)? \
		0x00: (((0xFFFFFFFF)>>32-__bits)) << (__bfws))

#define RTK_BIT_MASK(__bfws)	((uint32_t)((__bfws)==32)? \
		0x00 : (0x1 << (__bfws)))

#define RTK_BIT_MASK_WIDTH(__bfws, __bits)	((uint32_t)((__bfws)==32)? \
		0xFFFFFFFF :(uint32_t)((( (uint32_t)1 << ((uint32_t)__bits)) -1) << ((uint32_t)__bfws)))

#define RTK_BITS_CLEAR(__datum, __bfws, __bits)			\
		((__datum) = ((uint32_t)(__datum) & ~RTK_BIT_MASK(__bfws)))

#define RTK_BIT_GET_UNSHIFTED(__datum, __bfws)			\
		((uint32_t) ((__datum) & RTK_BIT_MASK(__bfws)))

#define RTK_BIT_GET(__datum, __bfws)					\
		((uint32_t) (((__datum) & RTK_BIT_MASK(__bfws)) >>	\
		(__bfws)))

#define RTK_BITS_GET(__datum, __bfws, bit_num)					\
		((uint32_t) (((__datum) & RTK_BIT_MASK_WIDTH(__bfws, bit_num)) >>	\
		(__bfws)))

#define RTK_BITS_SET(__datum, __bfws, __bits)					\
		((__datum) = ((uint32_t)(__datum) & ~RTK_BITS_MASK(__bfws, __bits)) |	\
			(RTK_BITS_MASK(__bfws, __bits)))

#define RTK_BIT_SET(__datum, __bfws)							\
		((__datum) = ((uint32_t)(__datum) & ~RTK_BIT_MASK(__bfws)) |	\
			(RTK_BIT_MASK(__bfws)))

#define RTK_BITS_SET_VAL(__datum, __bfws, __val ,bit_num)		\
		((__datum) = ((uint32_t)(__datum) & ~RTK_BIT_MASK_WIDTH(__bfws, bit_num)) |	\
			(((uint32_t)__val << ((uint32_t)__bfws)) & (uint32_t) RTK_BIT_MASK_WIDTH(__bfws, bit_num)))

#define RTK_BIT_SET_NOREAD(__datum, __bfws, __val)			\
	((uint32_t)((__datum) = (((__val) << (bfo ## __bfws)) &	\
								RTK_BIT_MASK(__bfws))))

#define	RTK_BIT_BUILD(__bfws, __val)						\
	((uint32_t)(((__val) << (bfo ## __bfws)) & RTK_BIT_MASK(__bfws)))



#endif
