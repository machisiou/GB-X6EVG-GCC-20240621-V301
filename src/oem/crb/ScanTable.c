#include "oem/crb/Oem_scan.h"

#if (KBMatrix == 1)

 /*------------------------------ Keyboard Matrix ------------------------------

  0:    Home    PGUP    END     Home    PGDN    WM      \       B
        (80+)   (85)    (81+)   (80)    (86)    (204)   (29)    (81)

  1:    ---     BkSp    =       ---     ]       ---     Entr    ''
        (131)   (15)    (13)    (14)    (28)    (56)    (43)    (41)

  2:    F10     ---     7       U       J       UpArw   LefArw  M
        (121)   (0)     (08)    (23)    (37)    (83)    (79+)   (52)

  3:    F11     K       8       I       ,       DnArw   UpArw   Ins
        (122)   (38)    (09)    (24)    (53)    (84)    (83+)   (75)

  4:    F7      F8      5       T       G       ---     B       ---
        (118)   (119)   (06)    (21)    (35)    (133)   (50)    (125)

  5:    6       H       Y       F9      ---     LefArw  N       ---
        (07)    (36)    (22)    (120)   (0)     (79)    (51)    (0)

  6:    Space   P       0       -       [       /       RArw    ;
        (61)    (26)    (11)    (12)    (27)    (55)    (89+)   (40)

  7:    ---     ---     ---     RAlt    LAlt    ---     ===     ---
        (0)     (0)     (0)     (62)    (60)    (0)     (0)     (0)

  8:    4       F       R       F6      ---     ---     ---     V
        (05)    (34)    (20)    (117)   (0)     (126)   (108)   (49)

  9:    F12     L       9       O       .       RArw    DnArw   ---
        (123)   (39)    (10)    (25)    (54)    (89)    (84+)   (76)

  10:   F4      F5      3       E       D       PrtScn  ---     C
        (115)   (116)   (04)    (19)    (33)    (124)   (132)   (48)

  11:   F2      W       F3      2       S       ---     `       X
        (113)   (18)    (114)   (03)    (32)    (45)    (01)    (47)

  12:   ---     Win     ---     ---     ---     Fn      ---     ---
        (0)     (203)   (0)     (0)     (0)     (202)   (0)     (0)

  13:   LShift  ---     ---     ---     ---     ---     RShift  ---
        (57)    (0)     (0)     (0)     (0)     (0)     (44)    (0)

  14:   ---     ---     RCtrl   ---     ---     ---     ---     LCtrl
        (0)     (0)     (64)    (0)     (0)     (0)     (0)     (58)

  15:   ESC     Tab     F1      1       Q       Z       A       CapLock
        (110)   (16)    (112)   (02)    (17)    (46)    (31)    (30)
        
******************************************************************************/
/*
const uint8_t Rc2IbmNum[] =
{
//	KSI0	KSI1	KSI2	KSI3	KSI4	KSI5	KSI6	KSI7
	80,		85,		81,		80,		86,		204,	29,		81,		//KSO00
	131,	15,		13,		14,		28,		56,		43,		41,		//KSO01
	121,	0,		8,		23,		37,		83,		79,		52,		//KSO02
	122,	38,		9,		24,		53,		84,		83,		75,		//KSO03
	118,	119,	6,		21,		35,		133,	50,		125,	//KSO04
	7,		36,		22,		120,	0,		79,		51,		0,		//KSO05
	61,		26,		11,		12,		27,		55,		89,		40,		//KSO06
	0,		0,		0,		62,		60,		0,		0,		0,		//KSO07
	5,		34,		20,		117,	0,		126,	108,	49,		//KSO08
	123,	39,		10,		25,		54,		89,		84,		76,		//KSO09
	115,	116,	4,		19,		33,		124,	132,	48,		//KSO10
	113,	18,		114,	3,		32,		45,		1,		47,		//KSO11
	0,		203,	0,		0,		0,		202,	0,		0,		//KSO12
	57,		0,		0,		0,		0,		0 ,		44,		0,		//KSO13
	0,		142,	156,	75,		0,		123,	0,		89,		//KSO14
	110,	16,		112,	2,		17,		46,		31,		30,		//KSO15
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO16
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO17
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO18
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO19
};
*/
const uint8_t Rc2IbmNum[] =
{
//	KSI0	KSI1	KSI2	KSI3	KSI4	KSI5	KSI6	KSI7
	48,		105,	106,	98,		103,	104,	93,		95,		//KSO00
	76,		75,		101,	138,	91,		80,		85,		90,		//KSO01
	17,		99,		59,		16,		1,		2,		131,	31,		//KSO02
	62,		60,		0,		0,		0,		0,		0,		0,		//KSO03
	108,	61,		19,		115,	30,		4,		114,	86,		//KSO04
	47,		46,		113,	112,	32,		3,		18,		110,	//KSO05
	49,		50,		35,		21,		6,		5,		20,		34,		//KSO06
	52,		51,		36,		22,		7,		8,		23,		37,		//KSO07
	54,		84,		29,		25,		121,	10,		122,	39,		//KSO08 84-1
	57,		44,		0,		0,		0,		0,		0,		0,		//KSO19
	53,		100,	118,	117,	116,	9,		24,		38,		//KSO10
	133,	132,	96,		120,	56,		45,		79,		129,	//KSO11 79-1
	64,		58,		0,		0,		0,		0,		0,		0,		//KSO12
	55,		83,		12,		123,	11,		26,		27,		40,		//KSO13 83-1
	41,		43,		124,	81,		13,		15,		28,		33,		//KSO14
	14,		119,	89,		126,	76,		92,		97,		102,	//KSO15 89-1 76-2

//	1,		2,		17,		16,		31,		110,	46,		131,	//KSO00
//	112,	3,		18,		30,		32,		45,		47,		0,		//KSO01
//	113,	4,		19,		114,	33,		115,	48,		0,		//KSO02
//	6,		5,		20,		21,		34,		35,		49,		50,		//KSO03
//	7,		8,		23,		22,		37,		36,		52,		51,		//KSO04
//	13,		9,		24,		28,		38,		117,	53,		56,		//KSO05
//	119,	10,		25,		118,	39,		132,	54,		133,	//KSO06
//	12,		11,		26,		27,		40,		41,		42,		55,		//KSO07
//	120,	121,	14,		15,		29,		116,	43,		61,		//KSO08
//	75,		123,	0,		155,	0,		0,		0,		89,		//KSO09
//	76,		122,	154,	153,	152,	151,	160,	84,		//KSO10
//	85,		86,		130,	129,	156,	0,		137,	138,	//KSO11
//	80,		81,		128,	127,	0,		83,		126,	79,		//KSO12
//	0,		124,	125,	0,		0,		60 ,	0,		62,		//KSO13
//	0,		0,		0,		44,		0,		0,		57,		89,		//KSO14
//	140,		0,		0,		0,		0,		0,		64,		0,		//KSO15
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO16
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO17
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO18
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO19
};

#elif  (KBMatrix == 2)

const uint8_t Rc2IbmNum[] =
{
//	KSI0	KSI1	KSI2	KSI3	KSI4	KSI5	KSI6	KSI7
	1,		2,		17,		16,		31,		110,	46,		131,	//KSO00
	112,	3,		18,		30,		32,		45,		47,		0,		//KSO01
	113,	4,		19,		114,	33,		115,	48,		0,		//KSO02
	6,		5,		20,		21,		34,		35,		49,		50,		//KSO03
	7,		8,		23,		22,		37,		36,		52,		51,		//KSO04
	13,		9,		24,		28,		38,		117,	53,		56,		//KSO05
	119,	10,		25,		118,	39,		132,	54,		133,	//KSO06
	12,		11,		26,		27,		40,		41,		42,		55,		//KSO07
	120,	121,	14,		15,		29,		116,	43,		61,		//KSO08
	75,		123,	0,		155,	0,		0,		0,		89,		//KSO09
	76,		122,	154,	153,	152,	151,	160,	84,		//KSO10
	85,		86,		130,	129,	156,	0,		137,	138,	//KSO11
	80,		81,		128,	127,	0,		83,		126,	79,		//KSO12
	0,		124,	125,	0,		0,		60 ,	0,		62,		//KSO13
	0,		0,		0,		44,		0,		0,		57,		89,		//KSO14
	58,		0,		0,		0,		0,		0,		64,		0,		//KSO15
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO16
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO17
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO18
	0,		0,		0,		0,		0,		0,		0,		0,		//KSO19
};

#endif

const struct KeyType IbmNumTable[] =
{
	{ Reserved_Key,		0x00, 0 },			// 
	{ Standard_Key,		0x29, 0 },			// key 1 - `
	{ Standard_Key,		0x02, 0 },			// key 2 - 1
	{ Standard_Key,		0x03, 0 },			// key 3 - 2
	{ Standard_Key,		0x04, 0 },			// key 4 - 3
	{ Standard_Key,		0x05, 0 },			// key 5 - 4
	{ Standard_Key,		0x06, 0 },			// key 6 - 5
	{ Standard_Key,		0x07, 0 },			// key 7 - 6
	{ Standard_Key,		0x08, 0 },			// key 8 - 7
	{ Standard_Key,		0x09, 0 },			// key 9 - 8
	{ Standard_Key,		0x0A, 0 },			// key 10 - 9
	{ Standard_Key,		0x0B, 0 },			// key 11 - 0
	{ Standard_Key,		0x0C, 0 },			// key 12 - -
	{ Standard_Key,		0x0D, 0 },			// key 13 - =
	{ Reserved_Key,		0x7D, 0 },			// key 14 - (Jap Layout)
	{ Standard_Key,		0x0E, 0 },			// key 15 - BackSpace
	{ Standard_Key,		0x0F, 0 },			// key 16 - Tab
	{ Standard_Key,		0x10, 0 },			// key 17 - q
	{ Standard_Key,		0x11, 0 },			// key 18 - w
	{ Standard_Key,		0x12, 0 },			// key 19 - e
	{ Standard_Key,		0x13, 0 },			// key 20 - r
	{ Standard_Key,		0x14, 0 },			// key 21 - t
	{ Standard_Key,		0x15, 0 },			// key 22 - y
	{ Standard_Key,		0x16, 0 },			// key 23 - u
	{ Standard_Key,		0x17, 0 },			// key 24 - i
	{ Standard_Key,		0x18, 0 },			// key 25 - o
	{ Standard_Key,		0x19, 0 },			// key 26 - p
	{ Standard_Key,		0x1A, 0 },			// key 27 - [
	{ Standard_Key,		0x1B, 0 },			// key 28 - ]
	{ Standard_Key,		0x2B, 0 },			// key 29 - \ (US Keyboard only)
	{ Standard_Key,		0x3A, 0 },			// key 30 - CapsLock
	{ Standard_Key,		0x1E, 0 },			// key 31 - a
	{ Standard_Key,		0x1F, 0 },			// key 32 - s
	{ Standard_Key,		0x20, 0 },			// key 33 - d
	{ Standard_Key,		0x21, 0 },			// key 34 - f
	{ Standard_Key,		0x22, 0 },			// key 35 - g
	{ Standard_Key,		0x23, 0 },			// key 36 - h
	{ Standard_Key,		0x24, 0 },			// key 37 - j
	{ Standard_Key,		0x25, 0 },			// key 38 - k
	{ Standard_Key,		0x26, 0 },			// key 39 - l
	{ Standard_Key,		0x27, 0 },			// key 40 - ;
	{ Standard_Key,		0x28, 0 },			// key 41 - '
	{ Standard_Key,		0x2B, 0 },			// key 42 - (International Keyboard only)
	{ Standard_Key,		0x1C, 0 },			// key 43 - Enter
	{ Standard_Key,		0x2A, 0 },			// key 44 - left shift
	{ Standard_Key,		0x56, 0 },			// key 45 - (International Keyboard only)
	{ Standard_Key,		0x2C, 0 },			// key 46 - z
	{ Standard_Key,		0x2D, 0 },			// key 47 - x
	{ Standard_Key,		0x2E, 0 },			// key 48 - c
	{ Standard_Key,		0x2F, 0 },			// key 49 - v
	{ Standard_Key,		0x30, 0 },			// key 50 - b
	{ Standard_Key,		0x31, 0 },			// key 51 - n
	{ Standard_Key,		0x32, 0 },			// key 52 - m
	{ Standard_Key,		0x33, 0 },			// key 53 - ,
	{ Standard_Key,		0x34, 0 },			// key 54 - .
	{ Standard_Key,		0x35, 0 },			// key 55 - /
	{ Standard_Key,		0x73, 0 },			// key 56 - (Jap/Brazil layout)
	{ Standard_Key,		0x36, 0 },			// key 57 - right shift
	{ Standard_Key,		0x1D, 0 },			// key 58 - left ctrl
	{ Reserved_Key,		0x59, 0 },			// key 59 - NO KEY
	{ Standard_Key,		0x38, 0 },			// key 60 - left alt
	{ Standard_Key,		0x39, 0 },			// key 61 - Space
	{ PrefixE0_Key,		0x38, 0 },			// key 62 - right alt
	{ Reserved_Key,		0x63, 0 },			// key 63 - NO KEY
	{ PrefixE0_Key,		0x1D, 0 },			// key 64 - right ctrl
	{ Reserved_Key,		0x65, 0 },			// key 65 - NO KEY
	{ Reserved_Key,		0x66, 0 },			// key 66 - NO KEY
	{ Reserved_Key,		0x67, 0 },			// key 67 - NO KEY
	{ Reserved_Key,		0x68, 0 },			// key 68 - NO KEY
	{ Reserved_Key,		0x69, 0 },			// key 69 - NO KEY
	{ Reserved_Key,		0x70, 0 },			// key 70 - NO KEY
	{ Reserved_Key,		0x71, 0 },			// key 71 - NO KEY
	{ Reserved_Key,		0x72, 0 },			// key 72 - NO KEY
	{ Reserved_Key,		0x73, 0 },			// key 73 - NO KEY
	{ Reserved_Key,		0x74, 0 },			// key 74 - NO KEY
	{ Cursor_Key,		0x52, 0 },			// key 75 - Insert
	{ Cursor_Key,		0x53, 0 },			// key 76 - Delete
	{ Reserved_Key,		0x77, 0 },			// key 77 - NO KEY
	{ Reserved_Key,		0x78, 0 },			// key 78 - NO KEY
	{ Cursor_Key,		0x4B, 0 },			// key 79 - left arrow
	{ Cursor_Key,		0x47, 0 },			// key 80 - Home
	{ Cursor_Key,		0x4F, 0 },			// key 81 - End -> Sleep
	{ Reserved_Key,		0x82, 0 },			// key 82 - NO KEY
	{ Cursor_Key,		0x48, 0 },			// key 83 - up arrow
	{ Cursor_Key,		0x50, 0 },			// key 84 - down arrow
	{ Cursor_Key,		0x49, 0 },			// key 85 - PageUp
	{ Cursor_Key,		0x51, 0 },			// key 86 - PageDown
	{ Reserved_Key,		0x87, 0 },			// key 87 - NO KEY
	{ Reserved_Key,		0x88, 0 },			// key 88 - NO KEY
	{ Cursor_Key,		0x4D, 0 },			// key 89 - right arrow
	{ Standard_Key,		0x45, 0 },			// key 90 - NumLock
	{ Standard_Key,		0x47, 0 },			// key 91 - Keypad 7/Home
	{ Standard_Key,		0x4B, 0 },			// key 92 - Keypad 4/left arrow
	{ Standard_Key,		0x4F, 0 },			// key 93 - Keypad 1/End
	{ Reserved_Key,		0x94, 0 },			// key 94 - NO KEY
	{ Cursor_Key,		0x35, 0 },			// key 95 - Keypad /
	{ Standard_Key,		0x48, 0 },			// key 96 - Keypad 8/up arrow
	{ Standard_Key,		0x4C, 0 },			// key 97 - Keypad 5
	{ Standard_Key,		0x50, 0 },			// key 98 - Keypad 2/down arrow
	{ Standard_Key,		0x52, 0 },			// key 99 - Keypad 0/insert
	{ Standard_Key,		0x37, 0 },			// key 100 - Keypad *
	{ Standard_Key,		0x49, 0 },			// key 101 - Keypad 9/PageUp
	{ Standard_Key,		0x4D, 0 },			// key 102 - Keypad 6/right arrow
	{ Standard_Key,		0x51, 0 },			// key 103 - Keypad 3/PageDown
	{ Standard_Key,		0x53, 0 },			// key 104 - Keypad ./Del
	{ Standard_Key,		0x4A, 0 },			// key 105 - Keypad -
	{ Standard_Key,		0x4E, 0 },			// key 106 - Keypad +
	{ Reserved_Key,		0x7E, 0 },			// key 107 - NO KEY
	{ PrefixE0_Key,		0x1C, 0 },			// key 108 - Keypad Enter: E0 1C
	{ Reserved_Key,		109,  0 },			// key 109 - NO KEY
	{ Standard_Key,		0x01, 0 },			// key 110 - ESC
	{ Reserved_Key,		111,  0 },			// key 111 - NO KEY
	{ Standard_Key+Overlay_Key,		0x3B, 141 },		// key 112 - F1
	{ Standard_Key+Overlay_Key,		0x3C, 142 },		// key 113 - F2
	{ Standard_Key+Overlay_Key,		0x3D, 143 },		// key 114 - F3
	{ Standard_Key+Overlay_Key,		0x3E, 144 },		// key 115 - F4
	{ Standard_Key+Overlay_Key,		0x3F, 145 },		// key 116 - F5
	{ Standard_Key+Overlay_Key,		0x40, 146 },		// key 117 - F6
	{ Standard_Key+Overlay_Key,		0x41, 147 },		// key 118 - F7
	{ Standard_Key+Overlay_Key,		0x42, 148 },		// key 119 - F8
	{ Standard_Key+Overlay_Key,		0x43, 149 },		// key 120 - F9
	{ Standard_Key+Overlay_Key,		0x44, 150 },		// key 121 - F10
	{ Standard_Key+Overlay_Key,		0x57, 151 },		// key 122 - F11
	{ Standard_Key+Overlay_Key,		0x58, 152 },		// key 123 - F12
	{ Prntscr_Key,		0x37, 0 },			// key 124 - PrintScreen
	{ Standard_Key,		0x46, 0 },			// key 125 - ScrollLock
	{ Pause_Key,		0x0,  0 },			// key 126 - Pause
	{ Reserved_Key,		127,  0 },			// key 127 - NO KEY
	{ Reserved_Key,		128,  0 },			// key 128 - NO KEY
	{ Reserved_Key,		129,  0 },			// key 129 - NO KEY
	{ Reserved_Key,		130,  0 },			// key 130 - NO KEY
	{ PrefixE0_Key,		0x19, 0 },			// key 131 - Next Track
	{ PrefixE0_Key,		0x10, 0 },			// key 132 - Previous Track
	{ PrefixE0_Key,		0x24, 0 },			// key 133 - Stop
	{ PrefixE0_Key,		0x22, 0 },			// key 134 - Play/Pause
	{ PrefixE0_Key,		0x20, 0 },			// key 135 - Mute
	{ PrefixE0_Key,		0x30, 0 },			// key 136 - Volume up
	{ PrefixE0_Key,		0x2E, 0 },			// key 137 - Volume down
	{ PrefixE0_Key,		0x5B, 0 },			// key 138 - Left win
	{ PrefixE0_Key,		0x5C, 0 },			// key 139 - Right win
	{ Fn_KEY,			140,  0 },			// key 140 - Fn

	{ FnHot_Key,		0x3B, 0 },			// key 141 - Hot key F1
	{ FnHot_Key,		0x3C, 0 },			// key 142 - Hot key F2
	{ FnHot_Key,		0x3D, 0 },			// key 143 - Hot key F3
	{ FnHot_Key,		0x3E, 0 },			// key 144 - Hot key F4
	{ FnHot_Key,		0x3F, 0 },			// key 145 - Hot key F5
	{ FnHot_Key,		0x40, 0 },			// key 146 - Hot key F6
	{ FnHot_Key,		0x41, 0 },			// key 147 - Hot key F7
	{ FnHot_Key,		0x42, 0 },			// key 148 - Hot key F8
	{ FnHot_Key,		0x43, 0 },			// key 149 - Hot key F9
	{ FnHot_Key,		0x44, 0 },			// key 150 - Hot key F10
	{ FnHot_Key,		0x57, 0 },			// key 151 - Hot key F11
	{ FnHot_Key,		0x58, 0 },			// key 152 - Hot key F12
};

