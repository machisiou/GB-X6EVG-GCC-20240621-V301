#ifndef __Oem_scan_H__
#define __Oem_scan_H__

#include "system/Type.h"

typedef union
{
	struct
	{
		uint32_t KSIPress:10;		// KSI0~KSI9
		uint32_t DebounceFlag:1;
		uint32_t DebounceDone:1;
		uint32_t TypeDebounceDone:1;
		uint32_t InvalidData:1;
		uint32_t KSIValidCnt:4;
		uint32_t Padding:14;
	}BITS;
	uint32_t DWORD;
}KBSBuff_Type;

typedef union
{
	struct
	{
		uint32_t KSIPress:4;		// KSI0~KSI9
		uint32_t KSOPress:5;		// KSO0~KSO19
		uint32_t DebounceFlag:1;
		uint32_t DebounceDone:1;
		uint32_t TypeDebounceDone:1;
		uint32_t InvalidData:1;
		uint32_t GhostKeyFlag:1;
		uint32_t Padding:18;
	}BITS;
	uint32_t DWORD;
}KBS_Type;

typedef union
{
	struct
	{
		uint8_t LeftShift:1;
		uint8_t RightShift:1;
		uint8_t LeftCtrl:1;
		uint8_t RightCtrl:1;
		uint8_t LeftAlt:1;
		uint8_t RightAlt:1;
		uint8_t NumLock:1;
		uint8_t Reserved:1;
	} BITS;
	uint8_t BYTE;
}ScanControlType;

typedef union
{
	struct
	{
		uint8_t FnFlag:1;
		uint8_t FnLockFlag:1;
		uint8_t Reserved:6;
	} BITS;
	uint8_t BYTE;
}FnControlType;

enum KeyEvent
{
	Make,
	Break,
	Repeat
};

struct KeyType
{
	uint8_t ScanCodeType;
	#define  Reserved_Key		0x00
	#define  Standard_Key		0x01
	#define  Cursor_Key			0x02
	#define  Fn_KEY				0x04
	#define  PrefixE0_Key		0x08
	#define  Prntscr_Key		0x10
	#define  Pause_Key			0x20
	#define  Overlay_Key		0x40
	#define  FnHot_Key			0x80

	uint8_t ScanCodeData;
	uint8_t Alt;
};

extern KBSBuff_Type TheNewKBBuffer[20];
extern KBSBuff_Type TempKBBuffer[20];
extern KBS_Type SentKey[10];
extern KBS_Type KBActiveData;
extern ScanControlType ScanType;
extern FnControlType ScanType1;

//KB SCAN
#define SupportOD		1

#define ScanDebounce	2
#define SupportKSO20	0
#define KSOLINES	(SupportKSO20 ? 18 : 16)
#define SupportKSI10	0
#define KSILINES	(SupportKSI10 ? 10 : 8)
#define SupportGhostKey	1
#define SupportFnLock	0
#define KBMatrix	1	// 1: Dyna KB, 2: Lenovo KB
#define ScanIntrval1msbase		1	// scan interval count (1ms base)

//ACPI
#define EVENT_BUFFER_SIZE 8

extern void IniKBM(void);
extern void KbScan(void);
extern void EnKBMInt(void);
extern void DisKBMInt(void);
extern void ScanCode(KBS_Type RowClm, enum KeyEvent Even);
extern void HandleKey(struct KeyType KeyCode ,enum KeyEvent Event);
extern void NormalKey(uint8_t KeyCode, enum KeyEvent Event);
extern void CursorKey(uint8_t KeyCode, enum KeyEvent Event);
extern void PrefixE0Key(uint8_t KeyCode, enum KeyEvent Event);
extern void PrntScrKey(uint8_t KeyCode, enum KeyEvent Event);
extern void PauseKey(uint8_t KeyCode, enum KeyEvent Event);
extern void FnHotKey(uint8_t KeyCode, enum KeyEvent Event);
extern void CheckNumLock4Cursor(uint8_t KeyCode, enum KeyEvent Event);
extern void CheckScanCtrl(struct KeyType KeyCode ,enum KeyEvent Event);
extern struct KeyType CheckFnHotKey(struct KeyType KeyCode);
extern void SendKey(uint8_t KeyCode);
extern void CheckGhostKey(uint32_t KSO);
extern const uint8_t Rc2IbmNum[];
extern const struct KeyType IbmNumTable[];

extern void HookF1HotKey(enum KeyEvent Event);
extern void HookF2HotKey(enum KeyEvent Event);
extern void HookF3HotKey(enum KeyEvent Event);
extern void HookF4HotKey(enum KeyEvent Event);
extern void HookF5HotKey(enum KeyEvent Event);
extern void HookF6HotKey(enum KeyEvent Event);
extern void HookF7HotKey(enum KeyEvent Event);
extern void HookF8HotKey(enum KeyEvent Event);
extern void HookF9HotKey(enum KeyEvent Event);
extern void HookF10HotKey(enum KeyEvent Event);
extern void HookF11HotKey(enum KeyEvent Event);
extern void HookF12HotKey(enum KeyEvent Event);

#endif
