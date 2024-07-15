#include "system/Type.h"
#include "hal/MONOTONIC_COUNTER.h"
#include "chip/rts5911/RTS5911.h"

/******************************************************************************/
/** Read Monotonic Counter
 * SelCnt - Select Monotonic Counter (0~3)
 * return Monotonic Counter (0~3) value
*******************************************************************************/
uint32_t Monotonic_ReadCounter(uint32_t SelCnt)
{
	MONOTONIC->CTRL_b.LOAD = 1;				/* Load from Monotonic Counter */
	if(SelCnt == 0)
		return MONOTONIC->MCNT0;
	else if(SelCnt == 1)
		return MONOTONIC->MCNT1;
	else if(SelCnt == 2)
		return MONOTONIC->MCNT2;
	else if(SelCnt == 3)
		return MONOTONIC->MCNT3;
	else
		return FAIL;
}

/******************************************************************************/
/** Write Monotonic Counter
 * SelCnt - Select Monotonic Counter (0~3)
 * return None
*******************************************************************************/
void Monotonic_WriteCounter(uint32_t SelCnt)
{
	MONOTONIC->CTRL_b.LOAD = 1;				/* Load from Monotonic Counter */
	if(SelCnt == 0)
		MONOTONIC->CTRL_b.INC0 = 1;			/* increase Monotonic Counter */
	else if(SelCnt == 1)
		MONOTONIC->CTRL_b.INC1 = 1;
	else if(SelCnt == 2)
		MONOTONIC->CTRL_b.INC2 = 1;
	else if(SelCnt == 3)
		MONOTONIC->CTRL_b.INC3 = 1;	
	MONOTONIC->CTRL_b.UPDATE = 1;			/* Update Monotonic Counter */
}

