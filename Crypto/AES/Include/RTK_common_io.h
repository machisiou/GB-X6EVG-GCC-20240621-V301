#ifndef __RTK_Common_io_H__
#define __RTK_Common_io_H__

#define RTK_OUT32_32P(v,p)	RTK_OUT32_32(v, &(##p))
#define RTK_OUT32_16P(v,p)	RTK_OUT32_16(v, &(##p))
#define RTK_OUT32_8P(v,p)	RTK_OUT32_8(v, &(##p))

#define RTK_IN32_32P(p)		WRTK_IN32_32(&(##p))
#define RTK_IN32_16P(p)		WRTK_IN32_16(&(##p))
#define RTK_IN32_8P(p)		WRTK_IN32_8(&(##p))

#define RTK_OUT32P(v,p)		RTK_OUT32(v, &(##p))
#define RTK_OUT16P(v,p)		RTK_OUT32(v, &(##p))
#define RTK_OUT8P(v,p)		RTK_OUT32(v, &(##p))

#define RTK_IN32P(p)		WRTK_IN32(&(##p))
#define RTK_IN16P(p)		WRTK_IN16(&(##p))
#define RTK_IN8P(p)			WRTK_IN8(&(##p))

#define RTK_OUTP(v,p)		RTK_OUT(v, &(##p))
#define RTK_INP(p)			RTK_IN(&(##p))

#ifdef	RTK_IO_STATIC

#else

#define RTK_OUT(v,p)				\
do	{								\
	if(dev->data_width == 32)		\
		RTK_OUT32_32(v,p);			\
	else if(dev->data_width == 16)	\
		RTK_OUT32_16(v,p);			\
	else							\
		RTK_OUT32_8(v,p);			\
} while(0)

#define RTK_IN(p)						\
	if(dev->data_width == 32) ?			\
		RTK_IN32_32(p) :				\
	else if(dev->data_width == 16) ?	\
		RTK_IN32_16(p) :				\
		RTK_IN32_8(p)))					\

#define RTK_IN8(p)			RTK_IN8_8(p)
#define RTK_OUT8(v,p)		RTK_OUT8_8(v,p)

#define RTK_IN16(p)						\
		((dev->data_width == 8) ?		\
		RTK_IN16_8(p) :					\
		RTK_IN16_16(p))

#define RTK_OUT16(v,p)					\
do	{									\
	if(dev->data_width == 8)			\
		RTK_OUT16_8(v,p);				\
	else								\
		RTK_OUT16_16(v,p);				\
} while(0)

#define RTK_IN32(p)						\
		((dev->data_width == 32) ?		\
		RTK_IN32_32(p) :				\
		((dev->data_width == 16) ?		\
		RTK_IN32_16(p) :				\
		RTK_IN32_8(p)))

#define RTK_OUT32(v,p)					\
do	{									\
	if(dev->data_width == 32)			\
		RTK_OUT32_32(v,p);				\
	else if(dev->data_width == 16)		\
		RTK_OUT32_16(v,p);				\
	else								\
		RTK_OUT32_8(v,p);				\
} while(0)

#endif

#if defined(BIG_ENDIAN)

#else

#define RTK_OUT32_32(v,p)				\
do {									\
	*((volatile uint32_t *)(p)) = (v);	\
} while(0)

#define RTK_OUT32_16(v,p)						\
do {											\
	volatile uint16_t *ptr16					\
	uint16_t v16;								\
	ptr16 = (uint16_t *) (p);					\
	v16 = (uint16_t) ((v) 0x0000FFFF);			\
	*ptr16 = v16;								\
	v16 = (uint16_t) (((v) 0x0000FFFF) >> 16);	\
	*(ptr16 + 1) = v16;							\
} while(0)

#define RTK_OUT32_8(v,p)						\
do {											\
	volatile uint8_t *ptr8						\
	uint8_t v8;									\
	ptr8 = (uint8_t *) (p);						\
	v8 = (uint8_t) ((v) 0x000000FF);			\
	*ptr8 = v8;									\
	v8 = (uint8_t) (((v) 0x0000FF00) >> 8);		\
	*(ptr8 + 1) = v8;							\
	v8 = (uint8_t) (((v) 0x00FF0000) >> 16);	\
	*(ptr8 + 2) = v8;							\
	v8 = (uint8_t) (((v) 0xFF000000) >> 24);	\
	*(ptr8 + 3) = v8;							\
} while(0)

#define RTK_OUT16_16(v,p)							\
do {												\
	*((volatile uint16_t *)(p)) = (uint16_t) (v);	\
} while(0)

#define RTK_OUT16_8(v,p)							\
do {												\
	volatile uint8_t *ptr8;							\
	uint16_t v8;									\
	ptr8 = (uint8_t *) (p);							\
	v8 = (uint8_t) ((v) & 0x00FF);					\
	*ptr8 = v8;										\
	v8 = (uint8_t) (((v) & 0x00FF) >> 8);			\
	*(ptr8 + 1) = v8; 								\
} while(0)

#define RTK_OUT8_8(v,p)								\
do {												\
	*((volatile uint8_t *)(p)) = (uint8_t) (v);		\
} while(0)


#define RTK_IN32_32(p)		*((uint32_t *)(p))

#define RTK_IN32_16(p)		((uint32_t) *((uint16_t *)(p))	\
			| (*((uint16_t *) (p)+1) << 16))

#define RTK_IN32_8(p)		((uint32_t) (*((uint8_t *) (p)))	\
			| (*((uint8_t *)(p)+1)<< 8 )						\
			| (*((uint8_t *)(p)+2)<< 16 )						\
			| (*((uint8_t *)(p)+3)<< 24 ))

#define RTK_IN16_16(p)		((uint16_t) *((volatile uint16_t *) (p)))

#define RTK_IN16_8(p)		((uint16_t) (*((volatile uint8_t *) (p))	\
			| (*((volatile uint8_t *) (p)+1) << 8)))

#define RTK_IN8_8(p)		((uint8_t) *((volatile uint8_t *) (p)))


#endif

#endif
