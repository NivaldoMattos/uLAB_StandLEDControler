//------------------------------------------------------------------------------
// SAÍDA DAC: RA2 
// Sinal de referência para ajuda na centralização do sinal de corrente em 2.5V
//------------------------------------------------------------------------------
#include <xc.h>
#include "dac.h"
void DAC_Initialize(void)
{
    // Vout= (( Vsrc+ - Vsrc- ) x (DACR<4:0> / 32)) + Vsrc-
    // Vsrc+ --> FVR, Vref+,VDD
    // Vsrc- --> Vref-,VSS
    // REGISTER 22-1: VREFCON1: VOLTAGE REFERENCE CONTROL REGISTER
    // DACEN DACLPS DACOE  nc  DACPSS<1:0>  nc   DACNSS
    // 1      1      1    0     0    0     0      0
    VREFCON1 = 0b11100000;
    VREFCON0 = 0b00000000;  // DAC Value
    DACCON1 = 0x00;
} 
void DAC_SetOutput(uint8_t inputData)
{
   DACCON1 = inputData;
}
uint8_t DAC_GetOutput(void)
{
    return DACCON1;
}
//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------





