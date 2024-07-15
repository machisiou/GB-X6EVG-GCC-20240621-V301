/****************************************************************************/
/*																			*/
/*		(C)Copyright 2022- Realtek Inc.										*/
/*		All Rights Reserved.												*/
/*																			*/
/*						 													*/
/****************************************************************************/

//Common
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>



#include "chip\rts5911\nvic.h"
#include "chip\rts5911\RTS5911.h"
#include "chip\rts5911\system_RTS5911.h"

//hal

#include "hal\ACPI.h"
#include "hal\adc.h"
#include "hal\DIO.h"
#include "hal\DMA.h"
#include "hal\EMI.h"
#include "hal\eRPMC.h"
#include "hal\ESPI_MAFS.h"
#include "hal\ESPI_OOB.h"
#include "hal\ESPI_SAFS.h"
#include "hal\GPIO.h"
#include "hal\I2C.h"
#include "hal\KBC.h"
#include "hal\KBM.h"
#include "hal\LED.h"
#include "hal\MBX.h"
#include "hal\MONOTONIC_COUNTER.h"
#include "hal\P80P81.h"
#include "hal\PECI.h"
#include "hal\PerVW.h"
#include "hal\PMPORT0.h"
#include "hal\PMPORT1.h"
#include "hal\PMPORT2.h"
#include "hal\PMPORT3.h"
#include "hal\PS2.h"
#include "hal\PWM.h"
#include "hal\SPI.h"
#include "hal\SPIC.h"
#include "hal\SYSTEM.h"
#include "hal\TACHO.h"
#include "hal\TIMER.h"
#include "hal\UART.h"
#include "hal\WDT.h"


#include "oem\battery\bq40z80.h"
#include "oem\crb\CRB.h"
#include "oem\crb\Oem_ADC.h"
#include "oem\crb\Oem_battery.h"
#include "oem\crb\Oem_fan.h"
#include "oem\crb\Oem_gpio.h"
#include "oem\crb\Oem_led.h"
#include "oem\crb\Oem_main.h"
#include "oem\crb\Oem_pmport0.h"
#include "oem\crb\Oem_pmport1.h"
#include "oem\crb\Oem_pmport2.h"
#include "oem\crb\Oem_pmport3.h"
#include "oem\crb\Oem_power.h"
#include "oem\crb\Oem_scan.h"
#include "oem\crb\Oem_timer.h"
#include "oem\crb\Oem_event.h"
#include "oem\crb\Oem_Qevent.h"
#include "oem\crb\Oem_Peci.h"
#include "oem\crb\Project.h"
#include "oem\crb\Oem_ACPI_Command.h"
#include "oem\crb\Oem_KBC_Command.h"
#include "oem\crb\Oem_UDPDFW_TI.h"
#include "oem\crb\Oem_Ver.h"

#include "system\ACPI_Command.h"
#include "system\Debug.h"
#include "system\Flashtool.h"
#include "system\interrupt.h"
#include "system\KBC_Command.h"
#include "system\Memory.h"
#include "system\peripheral.h"
#include "system\Type.h"

