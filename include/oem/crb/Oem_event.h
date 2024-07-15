#ifndef __Oem_Event_H__
#define __Oem_Event_H__


/* FUNCT_PTR_V_V is a pointer to a function that returns nothing
   (V for void) and takes nothing for a parameter (V for void). */
typedef void (*FUNCT_PTR_V_V)(void);

struct sDebounce
{
    uint8_t         *REG;
    uint8_t          Flag;
    uint8_t         *Counter;
    uint8_t          Time;
    FUNCT_PTR_V_V press;
    FUNCT_PTR_V_V release;
    FUNCT_PTR_V_V nochange;	
};

extern const struct sDebounce Debounce_TBL[]; 
extern uint8_t* Tmp_XPntr;
extern uint8_t* Tmp_XPntr1;


//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void EventManager(BYTE device_id);
extern void LidOpen(void);
extern void LidClose(void);
static void CHECKUSBCHARGE(void); 
extern void USB_CHARGE_S5(); 
static void DoUSBCharge(void); 
static void NoUSBCharge(void);   
extern void Check_Adapter(void); 
extern void S4_PD_ACTIVE(void); //981004-210225-A	 

#endif
