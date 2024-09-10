#ifndef __Oem_main_H__
#define __Oem_main_H__

extern void oem_1ms_service(void);
extern void oem_5ms_service(void);
extern void oem_10msA_service(void);
extern void oem_10msB_service(void);
extern void oem_50msA_service(void);
extern void oem_50msB_service(void);
extern void oem_100msA_service(void);
extern void oem_100msB_service(void);
extern void oem_100msC_service(void);
extern void oem_500msA_service(void);
extern void oem_500msB_service(void);
extern void oem_1SA_service(void);
extern void oem_1SB_service(void);
extern void oem_1min_service(void);

extern void Oem_init(void);
extern void Oem_SysPowerContrl(void);
extern void GETRPM1(void);
#define SUPPORT_DEBUG_CARD 1
#define SUPPORT_GBITEM_1 1
#define SUPPORT_GBITEM_2 1
#define SUPPORT_GBITEM_3 1
#define SUPPORT_GBITEM_4 1
#define SUPPORT_GBITEM_5 1
#define SUPPORT_GBITEM_6 1
#define SUPPORT_GBITEM_7 1
#define SUPPORT_GBITEM_8 1
#define SUPPORT_GBITEM_9 1
#define SUPPORT_GBITEM_10 1
#define SUPPORT_GBITEM_11 1
#define SUPPORT_GBITEM_12 1
#define SUPPORT_GBITEM_13 1
#define SUPPORT_GBITEM_14 1
#define SUPPORT_GBITEM_15 1
#define SUPPORT_GBITEM_16 1
#define SUPPORT_GBITEM_17 1
#define SUPPORT_GBITEM_18 1
#define SUPPORT_GBITEM_19 1
#define SUPPORT_GBITEM_20 1
#define SUPPORT_GBITEM_21 1
#define SUPPORT_GBITEM_22 1
#define SUPPORT_GBITEM_23 1
#define SUPPORT_GBITEM_24 1
#define SUPPORT_GBITEM_25 1
#define SUPPORT_GBITEM_26 1

extern void INIT_TM1650(void);
extern uint8_t Check_PORT80(void);
extern void PD_Adapter_setting(void);
#define Only_Timer1msEvent  0x01
#define All_TimerEvent      0x00
#define Normal_MainService  0xFF

extern void service_OEM_1(void);
extern void service_OEM_2(void);
extern void service_OEM_3(void);
extern void service_OEM_4(void);
#endif
