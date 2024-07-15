#include "system/Debug.h"
#include "system/Memory.h"
#include "hal/PMPORT1.h"

Debug_Type DebugIO32;

void DebugCmdPort(void)
{
#if SupportIODebug64
	switch (KbcCmd)
#elif SupportIODebug66
	switch (AcpiCmd)
#elif SupportIODebugPM0
	switch (pm0cmd)
#elif SupportIODebugPM1
	switch (pm1cmd)
#elif SupportIODebugPM2
	switch (pm2cmd)
#elif SupportIODebugPM3
	switch (pm3cmd)
#endif
	{
		case DebugCmdR:
			DebugCMDR();
			break;
		case DebugCmdW:
		case DebugIO0:
		case DebugIO1:
		case DebugIO2:
		case DebugIO3:
			DebugAddr();
			break;
	}
}

void DebugDataPort(void)
{
#if SupportIODebug64
	switch (KbcCmd)
#elif SupportIODebug66
	switch (AcpiCmd)
#elif SupportIODebugPM0
	switch (pm0cmd)
#elif SupportIODebugPM1
	switch (pm1cmd)
#elif SupportIODebugPM2
	switch (pm2cmd)
#elif SupportIODebugPM3
	switch (pm3cmd)
#endif
	{
		case DebugCmdW:
		case DebugIO0:
		case DebugIO1:
		case DebugIO2:
		case DebugIO3:
			DebugData();
			break;
	}
}

void DebugCMDR(void)
{
	//printf(" cmdr\n");
#if SupportIODebug64
	KBC_Write(*(uint8_t *)(DebugIO32.IOAddr.DWORD));
#elif SupportIODebug66
	ACPI_Write(*(uint8_t *)(DebugIO32.IOAddr.DWORD));
#elif SupportIODebugPM0
	PM0_Write(*(uint8_t *)(DebugIO32.IOAddr.DWORD));
#elif SupportIODebugPM1
	PM1_Write(*(uint8_t *)(DebugIO32.IOAddr.DWORD));
#elif SupportIODebugPM2
	PM2_Write(*(uint8_t *)(DebugIO32.IOAddr.DWORD));
#elif SupportIODebugPM3
	PM3_Write(*(uint8_t *)(DebugIO32.IOAddr.DWORD));
#endif
}

void DebugAddr(void)
{
#if SupportIODebug64
	KbcDLen = 1;
#elif SupportIODebug66
	AcpiDLen = 1;
#elif SupportIODebugPM0
	pm0len = 1;
#elif SupportIODebugPM1
	pm1len = 1;
#elif SupportIODebugPM2
	pm2len = 1;
#elif SupportIODebugPM3
	pm3len = 1;
#endif
}

void DebugData(void)
{
#if SupportIODebug64
	switch (KbcCmd)
#elif SupportIODebug66
	switch (AcpiCmd)
#elif SupportIODebugPM0
	switch (pm0cmd)
#elif SupportIODebugPM1
	switch (pm1cmd)
#elif SupportIODebugPM2
	switch (pm2cmd)
#elif SupportIODebugPM3
	switch (pm3cmd)
#endif
	{
		case DebugCmdW:
#if SupportIODebug64
			*(uint8_t *)(DebugIO32.IOAddr.DWORD) = KbcData;
#elif SupportIODebug66
			*(uint8_t *)(DebugIO32.IOAddr.DWORD) = AcpiData;
#elif SupportIODebugPM0
			*(uint8_t *)(DebugIO32.IOAddr.DWORD) = pm0dat;
#elif SupportIODebugPM1
			*(uint8_t *)(DebugIO32.IOAddr.DWORD) = pm1dat;
#elif SupportIODebugPM2
			*(uint8_t *)(DebugIO32.IOAddr.DWORD) = pm2dat;
#elif SupportIODebugPM3
			*(uint8_t *)(DebugIO32.IOAddr.DWORD) = pm3dat;
#endif
			break;

		case DebugIO0:
#if SupportIODebug64
			DebugIO32.IOAddr.Bits.IOAddr0 = KbcData;		// low address
#elif SupportIODebug66
			DebugIO32.IOAddr.Bits.IOAddr0 = AcpiData;
#elif SupportIODebugPM0
			DebugIO32.IOAddr.Bits.IOAddr0 = pm0dat;
#elif SupportIODebugPM1
			DebugIO32.IOAddr.Bits.IOAddr0 = pm1dat;
#elif SupportIODebugPM2
			DebugIO32.IOAddr.Bits.IOAddr0 = pm2dat;
#elif SupportIODebugPM3
			DebugIO32.IOAddr.Bits.IOAddr0 = pm3dat;
#endif
			break;

		case DebugIO1:
#if SupportIODebug64
			DebugIO32.IOAddr.Bits.IOAddr1 = KbcData;
#elif SupportIODebug66
			DebugIO32.IOAddr.Bits.IOAddr1 = AcpiData;
#elif SupportIODebugPM0
			DebugIO32.IOAddr.Bits.IOAddr1 = pm0dat;
#elif SupportIODebugPM1
			DebugIO32.IOAddr.Bits.IOAddr1 = pm1dat;
#elif SupportIODebugPM2
			DebugIO32.IOAddr.Bits.IOAddr1 = pm2dat;
#elif SupportIODebugPM3
			DebugIO32.IOAddr.Bits.IOAddr1 = pm3dat;
#endif
			break;


		case DebugIO2:
#if SupportIODebug64
			DebugIO32.IOAddr.Bits.IOAddr2 = KbcData;
#elif SupportIODebug66
			DebugIO32.IOAddr.Bits.IOAddr2 = AcpiData;
#elif SupportIODebugPM0
			DebugIO32.IOAddr.Bits.IOAddr2 = pm0dat;
#elif SupportIODebugPM1
			DebugIO32.IOAddr.Bits.IOAddr2 = pm1dat;
#elif SupportIODebugPM2
			DebugIO32.IOAddr.Bits.IOAddr2 = pm2dat;
#elif SupportIODebugPM3
			DebugIO32.IOAddr.Bits.IOAddr2 = pm3dat;
#endif
			break;

		case DebugIO3:
#if SupportIODebug64
			DebugIO32.IOAddr.Bits.IOAddr3 = KbcData;		// high address
#elif SupportIODebug66
			DebugIO32.IOAddr.Bits.IOAddr3 = AcpiData;
#elif SupportIODebugPM0
			DebugIO32.IOAddr.Bits.IOAddr3 = pm0dat;
#elif SupportIODebugPM1
			DebugIO32.IOAddr.Bits.IOAddr3 = pm1dat;
#elif SupportIODebugPM2
			DebugIO32.IOAddr.Bits.IOAddr3 = pm2dat;
#elif SupportIODebugPM3
			DebugIO32.IOAddr.Bits.IOAddr3 = pm3dat;
#endif
			break;

		default:
			break;
	}
}

