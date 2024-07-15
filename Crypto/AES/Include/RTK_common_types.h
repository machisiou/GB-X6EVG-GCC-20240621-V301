#ifndef __RTK_Common_Types_H__
#define __RTK_Common_Types_H__

#ifndef EOF
#define EOF	(-1)
#endif

#ifndef MIN
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
#endif

enum rtk_state_enum
{
	RTK_err = -1,
	RTK_clear = 0,
	RTK_set = 1
};

enum rtk_comp_type_enum
{
	Rtk_dev_none = 0x00000000,
	Rtk_dmac = 0x35000000
};

struct rtk_device_struct
{
	const char *name;
	unsigned data_width;
	void *base_address;
	void *instance;
	void *os;
	void *comp_param;
	uint32_t comp_version;
	enum rtk_comp_type_enum comp_type;
	struct rtk_list_head list;
};

enum rtk_dma_mode_struct
{
	Rtk_dma_none,
	Rtk_dma_sw_handshake,
	Rtk_dma_hw_handshake
};

typedef void (*rtk_dma_notifier_func)(struct rtk_device_struct *dev, unsigned channel, bool single, bool last);
typedef void (*rtk_callback)(struct rtk_device_struct *dev, int32_t ecode);

struct rtk_dma_config_struct
{
	enum rtk_dma_mode_struct mode;
	rtk_dma_notifier_func notifier;
	struct rtk_device_struct *dmac;
	unsigned channel;
};

#endif
