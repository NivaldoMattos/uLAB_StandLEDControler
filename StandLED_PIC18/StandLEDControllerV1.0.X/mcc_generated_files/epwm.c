//------------------------------------------------------------------------------
// Ajuste dos registros de para operar em PWM
//------------------------------------------------------------------------------
#include <xc.h>
#include "epwm.h"
//------------------------------------------------------------------------------
#define PWM1_INITIALIZE_DUTY_VALUE    511

void EPWM1_Initialize(void) 
{
    // P1M single;  DC1B 48; CCP1M P1AP1Chi_P1BP1Dhi; 
    //CCP1CON = 0x3C;
    //CCP1CON = 0B00111100;  //Ok mas sai por dois pinos e nao funciona PWM3
    CCP1CON =   0B00111100;
    // PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0; 
    ECCP1AS = 0x00;
    // P1RSEN automatic_restart; P1DC 0; 
    PWM1CON = 0x80;
    // STR1A P1A_to_CCP1M; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin; 
    PSTR1CON = 0x01;
    // CCPR1L 127; 
    CCPR1L = 0x7F;
    // CCPR1H 0x0; 
    CCPR1H = 0x00;
    // Selecting Timer2
    CCPTMRS0bits.C1TSEL = 0x0;
}

void EPWM1_LoadDutyValue(uint16_t dutyValue) 
{
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC) >> 2);
    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}




void EPWM2_Initialize(void) 
{
    // P1M single;  DC1B 48; CCP1M P1AP1Chi_P1BP1Dhi; 
    //CCP1CON = 0x3C;
    CCP2CON = 0B00111100;
    // PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0; 
    ECCP2AS = 0x00;
    // P1RSEN automatic_restart; P1DC 0; 
    PWM2CON = 0x80;

    // STR1A P1A_to_CCP1M; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin; 
    PSTR2CON = 0x01;

    // CCPR1L 127; 
    CCPR2L = 0x7F;

    // CCPR1H 0x0; 
    CCPR2H = 0x00;

    // Selecting Timer2
    CCPTMRS0bits.C2TSEL = 0x0;
}

void EPWM2_LoadDutyValue(uint16_t dutyValue) 
{
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR2L = ((dutyValue & 0x03FC) >> 2);
    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP2CON = (CCP2CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}

void EPWM3_Initialize(void) 
{
    // P1M single;  DC1B 48; CCP1M P1AP1Chi_P1BP1Dhi; 
    //CCP1CON = 0x3C;
    
    CCP3CON = 0B00111100;
    
    // PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0; 
    ECCP3AS = 0x00;

    // P1RSEN automatic_restart; P1DC 0; 
    PWM3CON = 0x80;

    // STR1A P1A_to_CCP1M; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin; 
    PSTR3CON = 0x01; //01

    // CCPR1L 127; 
    CCPR3L = 0x7F;

    // CCPR1H 0x0; 
    CCPR3H = 0x00;

    // Selecting Timer2
    CCPTMRS0bits.C3TSEL = 0x0;
}

void EPWM3_LoadDutyValue(uint16_t dutyValue) 
{
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR3L = ((dutyValue & 0x03FC) >> 2);
    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP3CON = (CCP3CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}


void EPWM4_Initialize(void) 
{
    // P1M single;  DC1B 48; CCP1M P1AP1Chi_P1BP1Dhi; 
    //CCP1CON = 0x3C;
    
    //CCP1CON = 0B00111100;  //Ok mas sai por dois pinos e nao funciona PWM3
    CCP1CON =   0B00111100;
    
    
    // PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0; 
    ECCP1AS = 0x00;

    // P1RSEN automatic_restart; P1DC 0; 
    PWM1CON = 0x80;

    // STR1A P1A_to_CCP1M; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin; 
    PSTR1CON = 0x01;

    // CCPR1L 127; 
    CCPR1L = 0x7F;

    // CCPR1H 0x0; 
    CCPR1H = 0x00;

    // Selecting Timer2
    CCPTMRS0bits.C1TSEL = 0x0;
}

void EPWM4_LoadDutyValue(uint16_t dutyValue) 
{
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC) >> 2);
    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP4CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}


void EPWM5_Initialize(void) 
{
    // P1M single;  DC1B 48; CCP1M P1AP1Chi_P1BP1Dhi; 
    //CCP1CON = 0x3C;
    
    //CCP1CON = 0B00111100;  //Ok mas sai por dois pinos e nao funciona PWM3
    CCP5CON =   0B00111100;
    
    
    // PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0; 
   // ECCP5AS = 0x00;

    // P1RSEN automatic_restart; P1DC 0; 
   // PWM5CON = 0x80;

    // STR1A P1A_to_CCP1M; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin; 
    //PSTR5CON = 0x01;

    
        
    // CCPR1L 127; 
    CCPR5L = 0x7F;

    // CCPR1H 0x0; 
    CCPR5H = 0x00;
    
    

    // Selecting Timer2
 //   CCPTMRS0bits.C5TSEL = 0x0;
}

void EPWM5_LoadDutyValue(uint16_t dutyValue) 
{
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR5L = ((dutyValue & 0x03FC) >> 2);
    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP5CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}

//------------------------------------------------------------------------------
// End of File
//------------------------------------------------------------------------------
