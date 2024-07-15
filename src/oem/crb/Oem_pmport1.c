#include "system/Memory.h"
#include "system/Debug.h"
#include "system/peripheral.h"
#include "system/interrupt.h"
#include "hal/PMPORT1.h"
#include "oem/crb/Oem_pmport1.h"

void PM1_process(void)
{
	if(PM1_Is_CMD()) {
		pm1cmd = PM1_Read();
		pm1len = 0;
		//PM1_CMD();
		DebugCmdPort();
	}else {			// Data
		//pm1len--;
		pm1dat = PM1_Read();
		//PM1_DAT();
		DebugDataPort();
	}
	NVIC_EnableIRQ(PMPORT1_IB_IRQn);
}

void PM1_CMD(void)
{
}

void PM1_DAT(void)
{
}
