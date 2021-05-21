//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include <xc.h>
#include "tmr0.h"
#include "app.h"

/**
  Section: Global Variables Definitions
 */
volatile uint16_t timer0ReloadVal16bit;
/**
  Section: TMR0 APIs
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_Initialize(void) {
    // Set TMR0 to the options selected in the User Interface
    // TMR0ON enabled; T0SE Increment_hi_lo; PSA not_assigned; T0CS FOSC/4; T08BIT 16-bit; T0PS 1:2; 
    //T0CON = 0x98;
    //T0CON = 0b10011000; // 16 bit   
    T0CON = 0b11000000;  // 16 bit /1
    //T0CON = 0b            1       0      0      0             000; 
             // |TMR0ON | T08BIT | T0CS | T0SE | PSA | T0PS2 | T0PS1 | T0PS0 |
    
    //0xd8
    //T0CON = 0b11001000;  // 8 bit /1   
    // TMR0H 254; 
    TMR0H = 1; 
    TMR0L = 19;
    
    // Load TMR0 value to the 16-bit reload variable
    // timer0ReloadVal16bit = 65136;
     
    //timer0ReloadVal16bit = 64775;
     
    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;
    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;
    // Start TMR0
    TMR0_StartTimer();
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_StartTimer(void) {
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_StopTimer(void) {
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
uint16_t TMR0_Read16bitTimer(void) {
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;
    readValLow = TMR0L;
    readValHigh = TMR0H;
    readVal = ((uint16_t) readValHigh << 8) + readValLow;
    return readVal;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_Write16bitTimer(uint16_t timerVal) {
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_Reload16bit(void) {
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_ISR(void) {
    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;
    
    TMR0H = 1;
    TMR0L = 19; // próximo a 32.55uS. ok
    
    
    // Write to the Timer0 register
    //TMR0H = timer0ReloadVal16bit >> 8;
    //TMR0L = (uint8_t) timer0ReloadVal16bit;
    // ticker function call;
    // ticker is 1 -> Callback function gets called every time this ISR executes
    TMR0_CallBack();
    // add your TMR0 interrupt custom code
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TMR0_CallBack(void) {
    // Add your custom callback code here
    // this code executes every 1 TMR0 periods
    AppTimer30us();
}
//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------
