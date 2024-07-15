#include <stdint.h>
#include "system/Type.h"
#include "system/Memory.h"
#include "system/KBC_Command.h"
#include "oem/crb/Oem_scan.h"
#include "oem/crb/Oem_timer.h"
#include "hal/KBM.h"
#include "system/peripheral.h"

KBSBuff_Type TheNewKBBuffer[20] = {0};
KBSBuff_Type TempKBBuffer[20] = {0};
KBS_Type SentKey[10] = {0};
KBS_Type KBActiveData = {0};
ScanControlType ScanType;
FnControlType ScanType1;

static const uint16_t TypeMCnt [32] = {33, 37, 42, 46, 48, 54, 58, 62, 67, 75, 83, 92, 100, 109, 116, 125, 
							133, 149, 167, 182, 200, 217, 232, 250, 270, 303, 333, 370, 400, 435, 476, 500};
static const uint16_t DelayCnt [4] = {250, 500, 750, 1000};

void IniKBM(void)
{
	// KBM initial
	*(uint32_t*) 0x400900A4 = 0x00008102;	// GPIO41 KSO0
	*(uint32_t*) 0x400900A8 = 0x00008102;	// GPIO42 KSO1
	*(uint32_t*) 0x400900AC = 0x00008102;	// GPIO43 KSO2
	*(uint32_t*) 0x400900B0 = 0x00008102;	// GPIO44 KSO3
	*(uint32_t*) 0x400900B4 = 0x00008102; 	// GPIO45 KSO4
	*(uint32_t*) 0x400900B8 = 0x00008102;	// GPIO46 KSO5
	*(uint32_t*) 0x400900BC = 0x00008102;	// GPIO47 KSO6
	*(uint32_t*) 0x400900C0 = 0x00008102;	// GPIO48 KSO7
	*(uint32_t*) 0x400900C4 = 0x00008102;	// GPIO49 KSO8
	*(uint32_t*) 0x400900C8 = 0x00008102;	// GPIO50 KSO9
	*(uint32_t*) 0x400900CC = 0x00008102;	// GPIO51 KSO10
	*(uint32_t*) 0x400900DC = 0x00008102;	// GPIO55 KSO11
	*(uint32_t*) 0x400900E0 = 0x00008102;	// GPIO56 KSO12
	*(uint32_t*) 0x400900E4 = 0x00008102;	// GPIO57 KSO13
	*(uint32_t*) 0x400900E8 = 0x00008102;	// GPIO58 KSO14
	*(uint32_t*) 0x400900EC = 0x00008102;	// GPIO59 KSO15

	*(uint32_t*) 0x40090100 = 0x0000C106;	// GPIO64 KSI0
	*(uint32_t*) 0x40090104 = 0x0000C106;	// GPIO65 KSI1
	*(uint32_t*) 0x40090108 = 0x0000C106;	// GPIO66 KSI2
	*(uint32_t*) 0x4009010C = 0x0000C106;	// GPIO67 KSI3
	*(uint32_t*) 0x40090110 = 0x0000C106;	// GPIO68 KSI4
	*(uint32_t*) 0x40090114 = 0x0000C106;	// GPIO69 KSI5
	*(uint32_t*) 0x40090118 = 0x0000C106;	// GPIO70 KSI6
	*(uint32_t*) 0x4009011C = 0x0000C106;	// GPIO71 KSI7

// Used for KSI8, KSI9
#if SupportKSI10
	KBM_Extra_KSI_Config(8,1);
	KBM_Extra_KSI_Config(9,1);
#endif

// Used for KSO18, KSO19
#if SupportKSO20
	KBM_Extra_KSO_Config(18,1);
	KBM_Extra_KSO_Config(19,1);
#endif
	KBM_Write_KSO_All_Low();

	// Support Interrupt
	for(uint8_t i=0;i<KSILINES;i++)
		KBM_Intr_Config(i,1);
}

void KbScan(void)
{
	uint32_t KSOLow,KSILow;
	uint32_t KSIChange;
	uint8_t j, SendKey=0;
	// Check if any KSI is low

	if(KBM->DBG_b.STEP >= 1)
		return;

	if(KBM_Read_All_KSI()) {
		if(KBActiveData.BITS.GhostKeyFlag)
			return;
		KBM_Write_KSO_All_High();

		for(KSOLow=0;KSOLow<KSOLINES;KSOLow++) {
			KBM_Write_KSOL(KSOLow);
			// Check if any KSI is "zero"
			Delay27us;
			KSIData = KBM_Read_All_KSI();
			if(KSIData!=0) {
				TheNewKBBuffer[KSOLow].DWORD = KSIData; 		// has sense key press
				if(KeyPress == 0) {
					// it the first scan
					if(TheNewKBBuffer[KSOLow].BITS.KSIPress) {
						TempKBBuffer[KSOLow].DWORD = TheNewKBBuffer[KSOLow].DWORD;
						TempKBBuffer[KSOLow].BITS.KSIValidCnt++;
						for(KSILow=0;KSILow<KSILINES;KSILow++) {
							if((TheNewKBBuffer[KSOLow].BITS.KSIPress >> KSILow) & 1ul) {
								KBActiveData.BITS.KSIPress = KSILow;
								KBActiveData.BITS.KSOPress = KSOLow;
								KBActiveData.BITS.DebounceFlag = 1;
								//printf("The fisrt key KSI = %x KSO = %x\n",KSILow, KSOLow);
							}
						}
					}
				}
				else {
					// More than First scan
					KSIChange = (TempKBBuffer[KSOLow].BITS.KSIPress ^ TheNewKBBuffer[KSOLow].BITS.KSIPress);
					if(KSIChange != 0) {
						for(KSILow=0;KSILow<KSILINES;KSILow++) {
							if((KSIChange >> KSILow) & 1ul) {
								// changed key happend
								if((TheNewKBBuffer[KSOLow].BITS.KSIPress >> KSILow) & 1ul)
								{
									// the second press key
									KBActiveData.BITS.KSIPress = KSILow;
									KBActiveData.BITS.KSOPress = KSOLow;
									KBActiveData.BITS.InvalidData = 0; 
									KBActiveData.BITS.DebounceFlag = 1;
									//printf("The Second key KSI = %x KSO = %x\n",KSILow, KSOLow);
									TempKBBuffer[KSOLow].BITS.KSIPress |= (1ul << KSILow);
									TempKBBuffer[KSOLow].BITS.KSIValidCnt++;
									// Check Ghost key
#if SupportGhostKey
									CheckGhostKey(KSOLow);
#endif
								}
							}
						}
					}
					else {
						// No current KSO's KSI change
						// Check if the old KSO's KSI
						if((TempKBBuffer[KSOLow].BITS.KSIPress != 0) && (KBActiveData.BITS.InvalidData == 0) ) {
							// Check if debounce done
							if(KBActiveData.BITS.DebounceFlag) {
								KBValidDebounceCnt++;
								if(KBValidDebounceCnt == ScanDebounce/ScanIntrval1msbase) {
									KBActiveData.BITS.DebounceFlag = 0;
									KBActiveData.BITS.DebounceDone = 1;
									// Send make key
									ScanCode(KBActiveData,Make);
#if SupportGhostKey
									SentKey[SentKeyCnt].DWORD = KBActiveData.DWORD;
									SentKeyCnt++;
#endif
									KBValidDebounceCnt = 0;
									// Reload KB delay counter
									KBDelayCnt = DelayCnt[(KBTypematic & 0x60)>> 5]/ScanIntrval1msbase;
									//printf("KBDelayCnt = %x\n",KBDelayCnt);
								}
							}
							else if(KBActiveData.BITS.DebounceDone) {
								// Delay time
								if(KBDelayCnt !=0) {
									KBDelayCnt--;
								}
								if(KBDelayCnt == 0) {
									// trigger repeat scan code 
									KBActiveData.BITS.DebounceDone = 0;
									KBActiveData.BITS.TypeDebounceDone = 1;
									// Reload Typematic counter
									KBRepetCnt = TypeMCnt[(KBTypematic & 0x1F)]/ScanIntrval1msbase;
								}
							}
							else if(KBActiveData.BITS.TypeDebounceDone) {
								// In Typematic
								if(KBRepetCnt != 0) {
									KBRepetCnt--;

								}
								else if(KBRepetCnt == 0) {
									// Reload Typematic counter
									ScanCode(KBActiveData,Repeat);
									KBRepetCnt = TypeMCnt[(KBTypematic & 0x1F)]/ScanIntrval1msbase;
								}
							}
						}
					}
				}
			}
		}
		// scan finish
		// Check if any key release
		for(KSOLow=0;KSOLow<KSOLINES;KSOLow++) {
			KSIChange = (TempKBBuffer[KSOLow].BITS.KSIPress ^ TheNewKBBuffer[KSOLow].BITS.KSIPress);
			if(KSIChange != 0) {
				// Check which key is release
				for(KSILow=0;KSILow<KSILINES;KSILow++) {
					if((KSIChange >> KSILow) & 1ul) {
						KBActiveData.BITS.KSIPress = KSILow;
						KBActiveData.BITS.KSOPress = KSOLow;
						//printf("Release the hold key KSI = %x KSO = %x\n",KSILow, KSOLow);
						ScanCode(KBActiveData,Break);
						KBActiveData.DWORD = 0;
						// Update
						TempKBBuffer[KSOLow].BITS.KSIPress &= ~(1ul << KSILow);
						TempKBBuffer[KSOLow].BITS.KSIValidCnt--;
					}
				}
			}
		}

		// Clear current scan
		for(KSOLow=0;KSOLow<KSOLINES;KSOLow++) {
			TheNewKBBuffer[KSOLow].DWORD = 0;
		}
		KBM_Write_KSO_All_Low();

		if(KeyPress == 0) {
			// First scan
			KeyPress = 1;
		}
	}
	else {
		// No key press
		// Check if need
		if(KeyPress == 1) {
			// Search for the last key
			for(KSOLow=0;KSOLow<KSOLINES;KSOLow++) {
				if(TempKBBuffer[KSOLow].BITS.KSIPress != 0) {
					for(KSILow=0;KSILow<KSILINES;KSILow++) {
						if((TempKBBuffer[KSOLow].BITS.KSIPress >> KSILow) & 1ul) {
							// The last key need to break
#if SupportGhostKey
							if(KBActiveData.BITS.GhostKeyFlag) {
								for(j=0;j<SentKeyCnt;j++) {
									if((SentKey[j].BITS.KSIPress == KSILow) && (SentKey[j].BITS.KSOPress == KSOLow)) {
										SendKey = 1;
										break;
									}
									else
										SendKey = 0;
								}
							}
							else
								SendKey = 1;
#endif
							if(SendKey) {
								KBActiveData.BITS.KSIPress = KSILow;
								KBActiveData.BITS.KSOPress = KSOLow;
								//printf("Release the last key KSI = %x KSO = %x\n",KSILow, KSOLow);
								ScanCode(KBActiveData,Break);
								SendKey = 0;
							}
						}
					}
				}
			// Clear Break key
			TempKBBuffer[KSOLow].DWORD = 0;
			}
		}
		// Clear All keys
		KeyPress = 0;
		KBActiveData.DWORD = 0;

		while(SentKeyCnt) {
			SentKey[--SentKeyCnt].DWORD = 0;
		}
		KBM_Write_KSO_All_Low();
		KSI_Intr_Enable();
		KBM_ClrIntr();
	}
}

void ScanCode(KBS_Type RowClm, enum KeyEvent Event)
{
	uint8_t RcNum,IbmNum;
	struct KeyType IKey;
	//printf("RowClm = %x\n", RowClm);
	RcNum = RowClm.BITS.KSOPress*KSILINES+RowClm.BITS.KSIPress;
	//printf("RcNum = %x\n", RcNum);
	IbmNum = Rc2IbmNum[RcNum];
	//printf("Ibm Num = %x\n", IbmNum);

	IKey = IbmNumTable[IbmNum];

	//printf("IKey.ScanCodeData = %x\n", IKey.ScanCodeData);

	//printf("Event = %x\n", Event);

	CheckScanCtrl(IKey, Event);

	IKey = CheckFnHotKey(IKey);

	HandleKey(IKey, Event);
}

void HandleKey(struct KeyType KeyCode ,enum KeyEvent Event)
{
	if(KeyCode.ScanCodeType & Standard_Key) {
		NormalKey(KeyCode.ScanCodeData,Event);
	}
	else if(KeyCode.ScanCodeType & Cursor_Key) {
		CursorKey(KeyCode.ScanCodeData,Event);
	}
	else if(KeyCode.ScanCodeType & PrefixE0_Key) {
		PrefixE0Key(KeyCode.ScanCodeData,Event);
	}
	else if(KeyCode.ScanCodeType & Prntscr_Key) {
		PrntScrKey(KeyCode.ScanCodeData,Event);
	}
	else if(KeyCode.ScanCodeType & Pause_Key) {
		PauseKey(KeyCode.ScanCodeData,Event);
	}
	else if(KeyCode.ScanCodeType & FnHot_Key) {
		FnHotKey(KeyCode.ScanCodeData,Event);
	}
}

void CheckGhostKey(uint32_t KSO)
{
	uint8_t i;
	if(TempKBBuffer[KSO].BITS.KSIValidCnt >= 2) {
		for(i=0;i<KSOLINES;i++) {
			if(i==KSO)
				continue;
			if(TempKBBuffer[KSO].BITS.KSIPress == TempKBBuffer[i].BITS.KSIPress) {
				// Ghost key occur
				// printf("Ghost key occur\n");
				KBActiveData.BITS.GhostKeyFlag = 1;
			}
		}
	}
}

void NormalKey(uint8_t KeyCode, enum KeyEvent Event)
{
	if(Event == Break)
		KeyCode |= BIT7;

	SendKey(KeyCode);
}

void CursorKey(uint8_t KeyCode, enum KeyEvent Event)
{
	if(Event == Break) {
		SendKey(0xE0);
		SendKey(KeyCode | BIT7);
	}

	CheckNumLock4Cursor(KeyCode,Event);

	if(Event != Break) {
		SendKey(0xE0);
		SendKey(KeyCode);
	}
}

void PrefixE0Key(uint8_t KeyCode, enum KeyEvent Event)
{
	if(Event == Break)
		KeyCode |= BIT7;

	SendKey(0xE0);
	SendKey(KeyCode);
}

void PrntScrKey(uint8_t KeyCode, enum KeyEvent Event)
{
	if((ScanType.BITS.LeftShift || ScanType.BITS.RightShift) && (ScanType.BITS.LeftCtrl || ScanType.BITS.RightCtrl)) {
		PrefixE0Key(KeyCode,Event);
	}
	else if (ScanType.BITS.LeftAlt || ScanType.BITS.RightAlt) {
		KeyCode = 0x54;
		if(Event == Break)
			KeyCode |= BIT7;

		SendKey(KeyCode);
	}
	else {
		if(Event == Make) {
			PrefixE0Key(0x2A, Event);
			PrefixE0Key(KeyCode, Event);
		}
		else if(Event == Repeat) {
			PrefixE0Key(KeyCode, Event);
			}
		else if(Event == Break) {
			PrefixE0Key(0xB7, Event);
			PrefixE0Key(0xAA, Event);
		}
	}
}

void PauseKey(uint8_t KeyCode, enum KeyEvent Event)
{
	KeyCode = 0;
	if(Event == Make) {
		if(ScanType.BITS.LeftCtrl || ScanType.BITS.RightCtrl) {
			PrefixE0Key(0x46, Event);
			PrefixE0Key(0xC6, Event);
		}
		else {
			SendKey(0xE1);
			SendKey(0x1D);
			SendKey(0x45);
			SendKey(0xE1);
			SendKey(0x9D);
			SendKey(0xC5);
		}
	}
	
}

void FnHotKey(uint8_t KeyCode, enum KeyEvent Event)
{
	if(ScanType1.BITS.FnFlag && (KeyCode == 0x3B))
	{
		HookF1HotKey(Event);		//Fn+F1
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x3C))
	{
		HookF2HotKey(Event);		//Fn+F2
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x3D))
	{
		HookF3HotKey(Event);		//Fn+F3
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x3E))
	{
		HookF4HotKey(Event);		//Fn+F4
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x3F))
	{
		HookF5HotKey(Event);		//Fn+F5
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x40))
	{
		HookF6HotKey(Event);		//Fn+F6
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x41))
	{
		HookF7HotKey(Event);		//Fn+F7
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x42))
	{
		HookF8HotKey(Event);		//Fn+F8
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x43))
	{
		HookF9HotKey(Event);		//Fn+F9
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x44))
	{
		HookF10HotKey(Event);		//Fn+F10
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x57))
	{
		HookF11HotKey(Event);		//Fn+F11
	}
	else if(ScanType1.BITS.FnFlag && (KeyCode == 0x58))
	{
		HookF12HotKey(Event);		//Fn+F12
	}
}


void SendKey(uint8_t KeyCode)
{
	Kbcwritedata(KeyCode);
}

void CheckNumLock4Cursor(uint8_t KeyCode, enum KeyEvent Event)
{
	if(Event == Repeat)
		return;

	if(ScanType.BITS.NumLock && (KeyCode != 0x35) )   /* key 95 must go below */
	{
		// Number Lock
		SendKey(0xE0);
		SendKey((Event != Break) ? 0x2A : 0xAA);
	}
	else
	{
		if(ScanType.BITS.LeftShift)
		{
			SendKey(0xE0);
			SendKey((Event != Break) ? 0xAA : 0x2A);
		}

		if(ScanType.BITS.RightShift)
		{
			SendKey(0xE0);
			SendKey((Event != Break) ? 0xB6 : 0x36);
		}
	}
}

void CheckScanCtrl(struct KeyType KeyCode ,enum KeyEvent Event)
{
	if(Event == Make) {
		if(KeyCode.ScanCodeData == 0x2A)
		{
			ScanType.BITS.LeftShift = 1;
		}

		if(KeyCode.ScanCodeData == 0x36)
		{
			ScanType.BITS.RightShift = 1;
		}

		if((KeyCode.ScanCodeData == 0x38) && (KeyCode.ScanCodeType & Standard_Key))
		{
			ScanType.BITS.LeftAlt = 1;
		}

		if((KeyCode.ScanCodeData == 0x38) && (KeyCode.ScanCodeType & PrefixE0_Key))
		{
			ScanType.BITS.RightAlt = 1;
		}

		if((KeyCode.ScanCodeData == 0x1D) && (KeyCode.ScanCodeType & Standard_Key))
		{
			ScanType.BITS.LeftCtrl = 1;
		}

		if((KeyCode.ScanCodeData == 0x1D) && (KeyCode.ScanCodeType & PrefixE0_Key))
		{
			ScanType.BITS.RightCtrl = 1;
		}
#if	SupportFnLock
		if(KeyCode.ScanCodeType & Fn_KEY)
		{
			if(ScanType1.BITS.FnLockFlag)
				ScanType1.BITS.FnFlag = 0;
			else
				ScanType1.BITS.FnFlag = 1;
		}
#else
		if(KeyCode.ScanCodeType & Fn_KEY)
		{
			ScanType1.BITS.FnFlag = 1;
		}
#endif
	}
	else if(Event == Break) {
		if(KeyCode.ScanCodeData == 0x2A)
		{
			ScanType.BITS.LeftShift = 0;
		}

		if(KeyCode.ScanCodeData == 0x36)
		{
			ScanType.BITS.RightShift = 0;
		}

		if((KeyCode.ScanCodeData == 0x38) && (KeyCode.ScanCodeType & Standard_Key))
		{
			ScanType.BITS.LeftAlt = 0;
		}

		if((KeyCode.ScanCodeData == 0x38) && (KeyCode.ScanCodeType & PrefixE0_Key))
		{
			ScanType.BITS.RightAlt = 0;
		}

		if((KeyCode.ScanCodeData == 0x1D) && (KeyCode.ScanCodeType & Standard_Key))
		{
			ScanType.BITS.LeftCtrl = 0;
		}

		if((KeyCode.ScanCodeData == 0x1D) && (KeyCode.ScanCodeType & PrefixE0_Key))
		{
			ScanType.BITS.RightCtrl = 0;
		}

		if((KeyCode.ScanCodeData == 0x45) && (KeyCode.ScanCodeType & Standard_Key))
		{
			NumLockCnt++;
			if(NumLockCnt == 1)
				ScanType.BITS.NumLock = 1;
			else if(NumLockCnt ==2) {
				ScanType.BITS.NumLock = 0;
				NumLockCnt =0;
			}
		}

#if	SupportFnLock
		if(KeyCode.ScanCodeType & Fn_KEY)
		{
			FnCnt++;
			if(FnCnt == 1) {
				ScanType1.BITS.FnLockFlag = 1;
				ScanType1.BITS.FnFlag = 1;
			}
			else if(FnCnt == 2) {
				ScanType1.BITS.FnLockFlag = 0;
				ScanType1.BITS.FnFlag = 0;
				FnCnt = 0;
			}
		}
#else
		if(KeyCode.ScanCodeType & Fn_KEY)
		{
			ScanType1.BITS.FnFlag = 0;
		}
#endif
	}
}

struct KeyType CheckFnHotKey(struct KeyType KeyCode)
{
	if(KeyCode.ScanCodeType & Overlay_Key)
	{
		if(ScanType1.BITS.FnFlag) {
			return (IbmNumTable[KeyCode.Alt]);
		}
		else {
			return KeyCode;
		}
	}
	else
		return KeyCode;
}

void HookF1HotKey(enum KeyEvent Event)
{
	if(Event == Make){
		// printf("F1 hot key make\n");
	}
	else if(Event == Break) {
		// printf("F1 hot key break\n");
	}
}

void HookF2HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF3HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF4HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF5HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF6HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF7HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF8HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF9HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF10HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF11HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void HookF12HotKey(enum KeyEvent Event)
{
	if(Event == Make){
	}
	else if(Event == Break) {
	}
}

void EnKBMInt(void)
{ //KB scan 
	KSI_Intr_Enable();
	KBM_ClrIntr();
}

void DisKBMInt(void)
{
	NVIC_DisableIRQ(KBM_IRQn);
	KBM_ClrIntr();
	NVIC_ClearPendingIRQ(KBM_IRQn);	
	KSI_Intr_Disable();
}

