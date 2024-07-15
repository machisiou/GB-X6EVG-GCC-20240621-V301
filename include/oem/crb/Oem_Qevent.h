#define PowerManagement       0x20
#define SCI_BRIGHT_DN         0x28  //Fn+F3
#define SCI_BRIGHT_UP         0x30  //Fn+F4
#define SCI_DISPLAY_SWITCH    0x57  //Fn+F5
#define SCI_TOUCHON           0x31
#define SCI_TOUCHOFF          0x32
#define SCI_MOUSE_PAD         0x33  //Fn+F6
#define SCI_VOLUME_MUTE       0x40  //Fn+F7    
#define SCI_VOLUME_DOWN       0x41  //Fn+F8    
#define SCI_VOLUME_UP         0x42  //Fn+F9 
//#define SCI_GSENSOR           0x43
#define SCI_SHIP              0x43 //981004-190116-A
#define SCI_SLEEP             0x50  //Fn+F1
#define SCI_DISPLAY_SWITCH    0x57 //Fn+F5
#define SCI_GPUTEMP75         0x58 //981004-221130-A
#define SCI_GPUTEMP72         0x59 //981004-221130-A
#define SCI_ADAPTERIN         0x60  
#define SCI_ADAPTEROUT        0x61
#define SCI_BATIN             0x62  
#define SCI_BATOUT            0x63 
#define SCI_SMART             0x64 
#define SCI_BAT30ON           0x65
//#define SCI_BAT30ON2          0xD2 //981004-140904-R 
#define SCI_THRON             0x66 
#define SCI_THROFF            0x67 
#define SCI_CPU_OVERHEAT      0x68
#define SCI_BOOST_ON          0x69 //981004-220216-A
#define SCI_BOOST_OFF         0x6A //981004-220216-A
//#define SCI_HEAVY_LOAD        0x69 //981004-180906-A
#define SCI_LID_CHANGE        0x70
//#define SCI_LIDCLOSE          0x70
#define SCI_LIDOPEN           0x71 //981004-200721-A
//#define SCI_BBATIN            0x72  
//#define SCI_BBATOUT           0x73
//#define SCI_BAT_TEMP          0x75 //P8 //981004-150417-R 
//#define SCI_BAT_AMP           0x76 //981004-150417-R 
#define SCI_DOCKEJECT         0x77 
#define SCI_HDMI              0x79
#define SCI_BAT_CURRENT       0x7A //981004-140505-A //P8 
#define SCI_DOCKIN            0x80
#define SCI_WiFi              0x81  //Fn+F2
#define SCI_DOCKOUT           0x82

//981004-221025-A-S for DB2.0 support
#define SCI_DB20_0            0x83 //80%
#define SCI_DB20_1            0x84 //60%
#define SCI_DB20_2            0x85 //40%
#define SCI_DB20_3            0x86 //20%
#define SCI_DB20_4            0x87 //BELOW 20%
//981004-221025-A-E

//#define SCI_BT                0x87  //Fn+F11
#define SCI_AIRPLANE          0x88  //Fn+F11 Airplane mode //981004-190801-A
#define SCI_CCD               0x89  //Fn+F12 //981004-130408-M from 0x86
#define SCI_PD_ACIN           0x90  //981004-210114-A 
#define SCI_PD_ACOUT          0x91  //981004-210114-A 
//#define SCI_BAT_AGING2        0x92  //981004-181030-A //Bat FCC < 50% DSG 
#define SCI_ESC               0x93  //Fn+ESC
//#define SCI_Light_sensor      0x94  //Fn+SPACE //981004-180712-R
//#define SCI_Light_sensor2     0x95  //Fn+SPACE //981004-180712-R
#define SCI_SV_THRON          0x96 //981004-130703-A
#define SCI_SV_THROFF         0x97 //981004-130703-A 
#define SCI_LS_DATA           0x98 
#define SCI_FLASH             0x99  //Windows Flash EC
#define SCI_GC6_On            0x9A //981004-121227-A
#define SCI_GC6_Off           0x9B //981004-121227-A
#define SCI_DGPU              0x9C //981004-130207-A
#define SCI_CPUP8             0x9D //981004-131111-A //P8
#define SCI_WINKEY            0x9E //981004-131125-A 
#define SCI_BAT_CUSTOM        0x9F //981004-171107-A 
#define SCI_P0                0xA0 //981004-140317-A
#define SCI_P1                0xA1 //981004-140317-A
#define SCI_LCD_SWITCH        0xA5 //981004-130107-A
#define SCI_BATT_LOW_TEMPER   0xD1 //981004-140505-A
#define SCI_BATT_HIGH_TEMPER  0xD2 //981004-140505-A
#define SCI_NV_D3             0xD3 //992022-140904-A
#define SCI_NV_D4             0xD4 //992022-140904-A
#define SCI_NV_D5             0xD5 //992022-140904-A
#define SCI_NV_D6             0xD6 //992022-140904-A
#define SCI_NV_D7             0xD7 //992022-140904-A
#define SCI_NV_D8             0xD8 //992022-140922-A
#define SCI_NV_D9             0xD9 //992022-140922-A
#define SCI_NV_DA             0xDA 
#define SCI_NV_DB             0xDB
 
#define SCI_RESET_TP          0xFF //RESET Touchpad