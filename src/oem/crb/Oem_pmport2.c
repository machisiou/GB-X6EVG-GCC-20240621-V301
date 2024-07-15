#include "system/Memory.h"
#include "system/peripheral.h"
#include "system/interrupt.h"
#include "oem/crb/Oem_pmport2.h"
#include "hal/PMPORT2.h"

void PM2_process(void)
{
	if(PM2_Is_CMD()) {
		pm2cmd = PM2_Read();
		pm2len = 0;
		PM2_CMD();
	}else {			// Data
		pm2len--;
		pm2dat = PM2_Read();
		PM2_DAT();
	}
	NVIC_EnableIRQ(PMPORT2_IB_IRQn);
}

void PM2_CMD(void)
{
}

void PM2_DAT(void)
{
}
