//------------------------------------------------------------------------------
// Firmware para controle do LED IX1903b
//------------------------------------------------------------------------------
#include "mcc_generated_files/mcc.h"
void main(void) 
{
    SYSTEM_Initialize();    // Configura o dispositivo em MCC.C
    AppInitialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    AppProcess();
    
    while(true){
        
    }
    
}
//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------