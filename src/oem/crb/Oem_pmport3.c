#include "system/Memory.h"
#include "system/peripheral.h"
#include "system/interrupt.h"
#include "oem/crb/Oem_pmport3.h"
#include "hal/PMPORT3.h"


void PM3_process(void)
{
	if(PM3_Is_CMD()) {
		pm3cmd = PM3_Read();
		pm3len = 0;
		PM3_CMD();
	}else {			// Data
		pm3len--;
		pm3dat = PM3_Read();
		PM3_DAT();
	}
	NVIC_EnableIRQ(PMPORT3_IB_IRQn);
}

void PM3_CMD(void)
{
}

void PM3_DAT(void)
{
}
