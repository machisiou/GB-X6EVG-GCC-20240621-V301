#ifndef __DIO_H__
#define __DIO_H__

#include <stdint.h>

#define DedIO0 0
#define DedIO1 1

extern uint8_t DIO_Enable(uint8_t DIO_num, uint16_t IO_num, uint8_t EnDis);

#endif
