#include "interrupt_manager.h"
#include "mcc.h"


void INTERRUPT_Initialize(void) {
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    RCONbits.IPEN = 0;
    // Clear peripheral interrupt priority bits (default reset value)
    // TMRI
    INTCON2bits.TMR0IP = 0;
    // RCI
    IPR1bits.RC1IP = 0;
    // TXI
    IPR1bits.TX1IP = 0;
}


void interrupt INTERRUPT_InterruptManager(void) {
    // interrupt handler
    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1) {
        TMR0_ISR();
    } else if (PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1) {
        EUSART1_Receive_ISR();
    } else if (PIE1bits.TX1IE == 1 && PIR1bits.TX1IF == 1) {
        EUSART1_Transmit_ISR();
    } else if(INTCONbits.INT0IE && INTCONbits.INT0IF){
        //AppINT0_ISR();
        INTCONbits.INT0IF = 0;
    }
    else {
        //Unhandled Interrupt
    }
    
    INTCON2bits.TMR0IP = 1;  // Prioridade para a int de tmr 0
}

//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------
