#include <stdint.h>
#include "system/Type.h"
#include "hal/DIO.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Enable Dedicated IO
 * DIO_num - DedIO0 or DedIO1
 * IO_num - DIO use IO number
 * EnDis - enable or disable
 * return SUCCESS
*******************************************************************************/
uint8_t DIO_Enable(uint8_t DIO_num, uint16_t IO_num, uint8_t EnDis)
{
	if(DIO_num == DedIO0) {
		DIO0->ADDR = IO_num;
		DIO0->CFG_b.EN = EnDis;
	}else if(DIO_num == DedIO1) {
		DIO1->ADDR = IO_num;
		DIO1->CFG_b.EN = EnDis;
	}else return FAIL;
	return SUCCESS;
}
