#ifndef __Oem_gpio_H__
#define __Oem_gpio_H__

#include "hal/GPIO.h"

#define STD_GPIO_OUTPUT_H	FUNC0+GPIO_PINON+GPIO_INOUT+GPIO_HILOW+GPIO_SCHMITTER
#define STD_GPIO_OUTPUT_L	FUNC0+GPIO_PINON+GPIO_INOUT+GPIO_SCHMITTER
#define STD_GPIO_OUTPUT_HOD	FUNC0+GPIO_PINON+GPIO_INOUT+GPIO_HILOW+GPIO_TYPE+GPIO_SCHMITTER
#define STD_GPIO_OUTPUT_LOD	FUNC0+GPIO_PINON+GPIO_INOUT+GPIO_TYPE+GPIO_SCHMITTER
#define STD_GPIO_INPUT		FUNC0+GPIO_PINON+GPIO_SCHMITTER
#define STD_GPIO_FUNC1		FUNC1+GPIO_PINON+GPIO_SCHMITTER
#define STD_GPIO_FUNC2		FUNC2+GPIO_PINON+GPIO_SCHMITTER
#define STD_GPIO_FUNC3		FUNC3+GPIO_PINON+GPIO_SCHMITTER

extern void Initial_GPIO(void);

#endif
