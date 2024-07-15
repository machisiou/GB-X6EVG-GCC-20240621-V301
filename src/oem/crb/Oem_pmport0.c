#include "system/Memory.h"
#include "oem/crb/Oem_pmport0.h"
#include "system/interrupt.h"
#include "system/peripheral.h"
#include "hal/PMPORT0.h"

void PM0_process(void)
{
	if(PM0_Is_CMD()) {
		pm0cmd = PM0_Read();
		pm0len = 0;
		PM0_CMD();
	}else if(pm0len) {
		pm0len--;
		pm0dat = PM0_Read();
		//PMPORT0_IB_EnableIRQ();
		PM0_DAT();
	}
	NVIC_EnableIRQ(PMPORT0_IB_IRQn);
}

void PM0_CMD(void)
{

}


void PM0_DAT(void)
{

}
