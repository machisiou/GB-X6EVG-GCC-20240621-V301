#include "system/Type.h"
#include "system/Memory.h"
#include "system/ACPI_Command.h"
#include "oem/crb/CRB.h"
#include "hal/PerVW.h"
#include "hal/GPIO.h"

void HookHandle66Port(void)
{
	switch(AcpiCmd)
	{
		case BOARDID:
			ACPI2HOST(0x09);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case ChargingMethodSelect:
			ACPI2HOST(0x01);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case 0x09:
			ACPI2HOST(0x4B);
			ACPI2HOST(0x53);
			ACPI2HOST(0x43);
			ACPI2HOST(0x8C);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case 0x0A:
			ACPI2HOST(0x71);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case 0x1B:
		case 0x55:
			ACPI2HOST(0x00);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case 0x0B:
		case 0x8A:
			ACPI2HOST(0x01);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case 0x90:
			ACPI2HOST(0x01);
			ACPI2HOST(0x26);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case 0x06:
		case 0xB0:
		case 0xB2:
		//case 0xE1:
			ACPI2HOST(0x09);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;
		case SMCHOST_READ_PLAT_SIGNATURE:
			ACPI2HOST(0x01);
			BIT_CLR(CustomFlags,ECCheckBurstMode);
			break;

		default:
			break;
	}
}

uint8_t HandleACPI80Data(void)
{
	switch(AcpiData)
	{
		case 1:					// Remote temp
			return 0x2F;
		case 3:
			if(IS_BIT_SET(CustomFlags,ACPI_Mode))
				return 0x61;
			else
				return 0x41;
		case 0x30:
			return 0x88;		//acpi_status2_flags
		case 0x3A:
			return 0;
		case 0x81:				// PCH DTS reading
			return 0x26;
		case 0x91:				// sensor1
			return 0;
		case 0x92:				// sensor1
			return 0;
		case 0x93:				// sensor2
			return 9;
		case 0x94:				// sensor2
			return 1;
		case 0x95:				// sensor3
			return 0x13;
		case 0x96:				// sensor3
			return 1;
		case 0x97:				// sensor4
			return 0x31;
		case 0x98:				// sensor4
			return 0x1;
		case 0x99:				// sensor5
			return 0x9;
		case 0x9A:				// sensor5
			return 0x1;
		default:
			return 0xFF;
	}
}

void CRBS5toS0(void)
{
	if(GPIO_Read(24))	// RSMRST_PWRGD
	{
//		printf("PRIM PWRGD high\n");
		GPIO_Write(28,1);	//rsmrst high
//		printf("SET RSMRST high\n");
		while(!GetVWEnable)
		{
//			printf("wait VW ENABLE \n");
		}
	
//		printf("ESPI->EVCFG = %x \n", ESPI->EVCFG);
	
		VW_Set_Index(0x05, 0x99);	/* Set boot load down */
		//ESPI->EVTXDAT = 0x0599;
		while(!GetSus_warn)
		{
			//printf("wait sus warn \n");
		}
	
		VW_Set_Index(0x40, 0x11);	/* Set Sus_ack */
		//ESPI->EVTXDAT = 0x4011;
//		printf("SUS ACK \n");
		SystemState = SYSTEM_S0;
	}
}


