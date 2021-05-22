//-------------------------------------------------
#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H
//-------------------------------------------------
#define INPUT   1
#define OUTPUT  0
#define HIGH    1
#define LOW     0
#define ANALOG      1
#define DIGITAL     0
#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0
//------------------------------------------------
//LEDs
#define LED_SetHigh()       do { LATC3 = 1; } while(0)
#define LED_SetLow()        do { LATC3 = 0; } while(0)
#define LED_Toggle()        do { LATC3 = ~LATC3; } while(0)
#define LED_SetOutput()     do { TRISC3 = 0; } while(0)

#define B3_SetHigh()       do { LATB3 = 1; } while(0)
#define B3_SetLow()        do { LATB3 = 0; } while(0)
#define B3_Toggle()        do { LATB3 = ~LATB3; } while(0)
#define B3_SetOutput()     do { TRISB3 = 0; } while(0)

//---------------------------------------------------------

//---------------------
void PIN_MANAGER_Initialize(void);
void PIN_MANAGER_IOC(void);
//---------------------
#endif // PIN_MANAGER_H
/**
 End of File
 */