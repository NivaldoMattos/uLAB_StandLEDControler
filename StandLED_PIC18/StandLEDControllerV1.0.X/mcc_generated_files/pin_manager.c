#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void) {
    LATA =   0x00;
    TRISA =  0b00001011; 
    ANSELA = 0b00000000; 
    //----------------
    LATB =   0b00000000;
    TRISB =  0b00000000;  
    ANSELB = 0b00000000; 
    WPUB =   0b00000000; 
    //----------------
    LATC =   0b00000000;
    TRISC =  0b10000010;    
    ANSELC = 0b00000000;
    //---------------------------------
    INTCON2bits.nRBPU = 0x01;  // Habilita os pinos Pull-Up selecionados
}
//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------
