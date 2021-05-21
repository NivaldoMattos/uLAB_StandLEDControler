//------------------------------------------------------------------------------
// USART1
//------------------------------------------------------------------------------
#include "eusart1.h"
#include "pin_manager.h"
#include "app.h"
/**
  Section: Macro Declarations
 */
#define EUSART1_TX_BUFFER_SIZE 8
#define EUSART1_RX_BUFFER_SIZE 8
/**
  Section: EUSART1 APIs
 */
void EUSART1_Initialize(void) {
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    PIE1bits.TX1IE = 0;
    
    // Set the EUSART1 module to the options selected in the user interface.
    // ABDEN disabled; 
    // WUE disabled; 
    // RCIDL idle; 
    // ABDOVF no_overflow; 
    // CKTXP async_noninverted_sync_fallingedge; 
    // BRG16 16bit_generator; DTRXP not_inverted; 
    BAUD1CON = 0x48;

    // ADDEN disabled; 
    // RX9 8-bit; 
    // RX9D 0x0; 
    // FERR no_error; 
    // CREN disabled; 
    // SPEN enabled; 
    // SREN disabled; 
    // OERR no_error; 
    // RC1STA = 0x80;
    RC1STA = 0b10010000;
    
    // CSRC slave_mode; 
    // TRMT TSR_empty; 
    // TXEN disabled; 
    // BRGH hi_speed; 
    // SYNC asynchronous; 
    // SENDB sync_break_complete; 
    // TX9D 0x0; TX9 8-bit; 
    // TX1STA = 0x06;
    TX1STA = 0b00100110;
    //--------------------------------------------------
    // Funciona ok quando  SPBRG_VAL eh menor que 512
    //--------------------------------------------------
	#define X_FREQ 64000000
    //#define BAUDRATE_DESEJADO 128000      // Ok
                                            // devido ao uso dos optos H11L1 Onsemi
    //#define BAUDRATE_DESEJADO 256000      // Ok Funcionou 200kbps no ISl32xx intersil
    #define BAUDRATE_DESEJADO 115200        // Ok
    //#define BAUDRATE_DESEJADO 31250       // Ok MIDI
    
    //------------------------------------
    // Configuração automática de SPBRG1
    //------------------------------------
    #define SPBRG_VAL ((X_FREQ/BAUDRATE_DESEJADO)/4)-1
    if( SPBRG_VAL > 255 ){
       SPBRGH1 = 1;
       SPBRG1=(int)(SPBRG_VAL)&0x00ff;
    }
    else{
       SPBRGH1 = 0;
       SPBRG1=(int)(SPBRG_VAL)&0x00ff;
    }    
    // enable receive interrupt
    PIE1bits.RC1IE = 1; 
}


uint8_t EUSART1_Read(void) 
{
    uint8_t readValue = 0;
    return readValue;
}

void EUSART1_Write(uint8_t txData) 
{
    TXREG1=txData;
}
char getch(void) 
{
    return 0;    
}


void putch(char txData) 
{
    EUSART1_Write(txData);
}


void EUSART1_Transmit_ISR(void) 
{
    PIE1bits.TX1IE = 0;
}


void EUSART1_Receive_ISR(void) 
{
    unsigned char byteReceived = 0;
    if (1 == RC1STAbits.OERR) 
    {
        // EUSART1 error - restart
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    byteReceived = RCREG1;
    AppINT_USART1_RX(byteReceived);  
 }
//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------


