//------------------------------------------------------------------------------
// Firmware para controle do LED IX1903b e do WS2812b
// Serve como Bridge RS232/LED enderecavel.
//
// Dev: N.M
// Data: 21/05/2021
// Adicionado repositorio no github
//
// Utilizando codigo inline disparado por interrupcao de timer.
// A configuracao dos LEDs e feita pela usart na velocidade de 115200Kbps
//
// Versaoo de compilador utilizado: Microchip\xc8\v1.41
//
// Formato do pacote de configuracao: 
//  0 a 254 para comandos e valores r g b;
//
//  terminador: 255
//  canal, tipo, posicao, red, green, blue, 255  
//  ShowLed = 1;
//------------------------------------------------------------------------------
#include "app.h"
#include <xc.h>
#include "pin_manager.h"
#include "eusart1.h"
//------------------------------------------------------------------------------
#define MY_RX_BUFFER_SIZE 128
static uint8_t Buffer[MY_RX_BUFFER_SIZE];

// Sao 50 chips enderecaveis em 5 metros da fita de LED IX1903b

# define MAX_LEDS_CH0 7
# define MAX_LEDS_CH1 7
# define MAX_LEDS_CH2 64
# define MAX_LEDS_CH3 64
# define MAX_LEDS_CH4 64
# define MAX_LEDS_CH5 64
# define MAX_LEDS_CH6 64

# define RBG 0
# define GBR 1

static uint8_t CH0[MAX_LEDS_CH0]; 

static uint8_t R0[MAX_LEDS_CH0]; 
static uint8_t G0[MAX_LEDS_CH0]; 
static uint8_t B0[MAX_LEDS_CH0];

static uint8_t R1[MAX_LEDS_CH1]; 
static uint8_t G1[MAX_LEDS_CH1]; 
static uint8_t B1[MAX_LEDS_CH1];

static uint8_t R2[MAX_LEDS_CH2]; 
static uint8_t G2[MAX_LEDS_CH2]; 
static uint8_t B2[MAX_LEDS_CH2];

static uint8_t R3[MAX_LEDS_CH3]; 
static uint8_t G3[MAX_LEDS_CH3]; 
static uint8_t B3[MAX_LEDS_CH3];

static uint8_t R4[MAX_LEDS_CH4]; 
static uint8_t G4[MAX_LEDS_CH4]; 
static uint8_t B4[MAX_LEDS_CH4];

static uint8_t R5[MAX_LEDS_CH5]; 
static uint8_t G5[MAX_LEDS_CH5]; 
static uint8_t B5[MAX_LEDS_CH5];

static uint8_t R6[MAX_LEDS_CH6]; 
static uint8_t G6[MAX_LEDS_CH6]; 
static uint8_t B6[MAX_LEDS_CH6];

static int ShootLedsCh0 = 0;
static int ShootLedsCh1 = 0;
static int ShootLedsCh2 = 0;
static int ShootLedsCh3 = 0;
static int ShootLedsCh4 = 0;
static int ShootLedsCh5 = 0;
static int ShootLedsCh6 = 0;

uint8_t Idx = 0;
uint8_t IdxFrame = 0;

bool  ftest = true;

int channel = 0;
int type = RBG;

int ch0_len = 0;
bool send_ch0 = false;



//------------------------------------------------------------------------------
//  Inicializa��o
//------------------------------------------------------------------------------
void AppInitialize(void)
{
    //Habilita INT0
    INTCONbits.INT0IE = 1;
    //INT0 on rising edge
    INTCON2bits.INTEDG0 = 1;
    //ADCON0bits.CHS = 0;  // Ad canal 0
    //ADCON0bits.ADON = 1; // Liga o AD
}


//------------------------------------------------------------------------------
//   AppProcess(void): 
//------------------------------------------------------------------------------
void AppProcess(void){
    while(1){
    
    }
}


/*
//------------------------------------------------------------------------------
// WS2812B
void um(){
    //#Inline code
    LATB0 = 1;
    NOP();NOP();NOP();NOP();NOP();NOP();
    NOP();NOP();NOP();NOP();NOP();NOP();
    LATB0 = 0;
}
void zero(){
    //#inline code
    LATB0 = 1;
    NOP();NOP();NOP();
    LATB0 = 0;
    NOP();NOP();NOP();NOP();NOP();NOP();
}
*/


//------------------------------------------------------------------------------
// Codigo inline para geraco do diagrama de tempos 
// Fita LED com chip IX1903B (um endereco controla 3 LEDs)
// Obs: Refatorar utilizando bloco inline em assembler + ponteiros para
// simplificação do codigo e unificação destas funcoes.
//------------------------------------------------------------------------------
void um_0(){ LATB0 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB0 = 0;
}
void zero_0(){ LATB0 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB0 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_1(){ LATB1 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB1 = 0;
}
void zero_1(){ LATB1 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB1 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_2(){ LATB2 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB2 = 0;
}
void zero_2(){ LATB2 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB2 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_3(){ LATB3 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB3 = 0;
}
void zero_3(){ LATB3 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB3 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_4(){ LATB4 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB4 = 0;
}
void zero_4(){ LATB4 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB4 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_5(){ LATB5 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB5 = 0;
}
void zero_5(){ LATB5 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB5 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_6(){ LATB5 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB5 = 0;
}
void zero_6(){ LATB5 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB5 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }



//------------------------------------------------------------------------------
// Refatorar utilizando ponteiros para unificacao dessas funcoes
//------------------------------------------------------------------------------
void SendBuffCh0(uint8_t idx ){
   //-----------------------------
    if( (G0[idx] & 128) > 0) um_0();else zero_0();
    if( (G0[idx] & 64) > 0) um_0();else zero_0();
    if( (G0[idx] & 32) > 0) um_0();else zero_0();
    if( (G0[idx] & 16) > 0) um_0();else zero_0();
    if( (G0[idx] & 8) > 0) um_0();else zero_0();
    if( (G0[idx] & 4) > 0) um_0();else zero_0();
    if( (G0[idx] & 2) > 0) um_0();else zero_0();
    if( (G0[idx] & 1) > 0) um_0();else zero_0();
    //-----------------------------
    if( (R0[idx] & 128) > 0) um_0();else zero_0();
    if( (R0[idx] & 64) > 0) um_0();else zero_0();
    if( (R0[idx] & 32) > 0) um_0();else zero_0();
    if( (R0[idx] & 16) > 0) um_0();else zero_0();
    if( (R0[idx] & 8) > 0) um_0();else zero_0();
    if( (R0[idx] & 4) > 0) um_0();else zero_0();
    if( (R0[idx] & 2) > 0) um_0();else zero_0();
    if( (R0[idx] & 1) > 0) um_0();else zero_0();
    //-----------------------------
    if( (B0[idx] & 128) > 0) um_0();else zero_0();
    if( (B0[idx] & 64) > 0) um_0();else zero_0();
    if( (B0[idx] & 32) > 0) um_0();else zero_0();
    if( (B0[idx] & 16) > 0) um_0();else zero_0();
    if( (B0[idx] & 8) > 0) um_0();else zero_0();
    if( (B0[idx] & 4) > 0) um_0();else zero_0();
    if( (B0[idx] & 2) > 0) um_0();else zero_0();
    if( (B0[idx] & 1) > 0) um_0();else zero_0();
}
void SendBuffCh1(uint8_t idx ){
   //-----------------------------
    if( (G1[idx] & 128) > 0) um_1();else zero_1();
    if( (G1[idx] & 64) > 0) um_1();else zero_1();
    if( (G1[idx] & 32) > 0) um_1();else zero_1();
    if( (G1[idx] & 16) > 0) um_1();else zero_1();
    if( (G1[idx] & 8) > 0) um_1();else zero_1();
    if( (G1[idx] & 4) > 0) um_1();else zero_1();
    if( (G1[idx] & 2) > 0) um_1();else zero_1();
    if( (G1[idx] & 1) > 0) um_1();else zero_1();
    //-----------------------------
    if( (R1[idx] & 128) > 0) um_1();else zero_1();
    if( (R1[idx] & 64) > 0) um_1();else zero_1();
    if( (R1[idx] & 32) > 0) um_1();else zero_1();
    if( (R1[idx] & 16) > 0) um_1();else zero_1();
    if( (R1[idx] & 8) > 0) um_1();else zero_1();
    if( (R1[idx] & 4) > 0) um_1();else zero_1();
    if( (R1[idx] & 2) > 0) um_1();else zero_1();
    if( (R1[idx] & 1) > 0) um_1();else zero_1();
    //-----------------------------
    if( (B1[idx] & 128) > 0) um_1();else zero_1();
    if( (B1[idx] & 64) > 0) um_1();else zero_1();
    if( (B1[idx] & 32) > 0) um_1();else zero_1();
    if( (B1[idx] & 16) > 0) um_1();else zero_1();
    if( (B1[idx] & 8) > 0) um_1();else zero_1();
    if( (B1[idx] & 4) > 0) um_1();else zero_1();
    if( (B1[idx] & 2) > 0) um_1();else zero_1();
    if( (B1[idx] & 1) > 0) um_1();else zero_1();
}
void SendBuffCh2(uint8_t idx ){
   //-----------------------------
    if( (G2[idx] & 64) > 0) um_2();else zero_2();
    if( (G2[idx] & 128) > 0) um_2();else zero_2();
    if( (G2[idx] & 32) > 0) um_2();else zero_2();
    if( (G2[idx] & 16) > 0) um_2();else zero_2();
    if( (G2[idx] & 8) > 0) um_2();else zero_2();
    if( (G2[idx] & 4) > 0) um_2();else zero_2();
    if( (G2[idx] & 2) > 0) um_2();else zero_2();
    if( (G2[idx] & 1) > 0) um_2();else zero_2();
    //-----------------------------
    if( (R2[idx] & 128) > 0) um_2();else zero_2();
    if( (R2[idx] & 64) > 0) um_2();else zero_2();
    if( (R2[idx] & 32) > 0) um_2();else zero_2();
    if( (R2[idx] & 16) > 0) um_2();else zero_2();
    if( (R2[idx] & 8) > 0) um_2();else zero_2();
    if( (R2[idx] & 4) > 0) um_2();else zero_2();
    if( (R2[idx] & 2) > 0) um_2();else zero_2();
    if( (R2[idx] & 1) > 0) um_2();else zero_2();
    //-----------------------------
    if( (B2[idx] & 128) > 0) um_2();else zero_2();
    if( (B2[idx] & 64) > 0) um_2();else zero_2();
    if( (B2[idx] & 32) > 0) um_2();else zero_2();
    if( (B2[idx] & 16) > 0) um_2();else zero_2();
    if( (B2[idx] & 8) > 0) um_2();else zero_2();
    if( (B2[idx] & 4) > 0) um_2();else zero_2();
    if( (B2[idx] & 2) > 0) um_2();else zero_2();
    if( (B2[idx] & 1) > 0) um_2();else zero_2();
}
void SendBuffCh3(uint8_t idx ){
   //-----------------------------
    if( (G3[idx] & 128) > 0) um_3();else zero_3();
    if( (G3[idx] & 64) > 0) um_3();else zero_3();
    if( (G3[idx] & 32) > 0) um_3();else zero_3();
    if( (G3[idx] & 16) > 0) um_3();else zero_3();
    if( (G3[idx] & 8) > 0) um_3();else zero_3();
    if( (G3[idx] & 4) > 0) um_3();else zero_3();
    if( (G3[idx] & 2) > 0) um_3();else zero_3();
    if( (G3[idx] & 1) > 0) um_3();else zero_3();
    //-----------------------------
    if( (R3[idx] & 128) > 0) um_3();else zero_3();
    if( (R3[idx] & 64) > 0) um_3();else zero_3();
    if( (R3[idx] & 32) > 0) um_3();else zero_3();
    if( (R3[idx] & 16) > 0) um_3();else zero_3();
    if( (R3[idx] & 8) > 0) um_3();else zero_3();
    if( (R3[idx] & 4) > 0) um_3();else zero_3();
    if( (R3[idx] & 2) > 0) um_3();else zero_3();
    if( (R3[idx] & 1) > 0) um_3();else zero_3();
    //-----------------------------
    if( (B3[idx] & 128) > 0) um_3();else zero_3();
    if( (B3[idx] & 64) > 0) um_3();else zero_3();
    if( (B3[idx] & 32) > 0) um_3();else zero_3();
    if( (B3[idx] & 16) > 0) um_3();else zero_3();
    if( (B3[idx] & 8) > 0) um_3();else zero_3();
    if( (B3[idx] & 4) > 0) um_3();else zero_3();
    if( (B3[idx] & 2) > 0) um_3();else zero_3();
    if( (B3[idx] & 1) > 0) um_3();else zero_3();
}
void SendBuffCh4(uint8_t idx ){
   //-----------------------------
    if( (G4[idx] & 128) > 0) um_4();else zero_4();
    if( (G4[idx] & 64) > 0) um_4();else zero_4();
    if( (G4[idx] & 32) > 0) um_4();else zero_4();
    if( (G4[idx] & 16) > 0) um_4();else zero_4();
    if( (G4[idx] & 8) > 0) um_4();else zero_4();
    if( (G4[idx] & 4) > 0) um_4();else zero_4();
    if( (G4[idx] & 2) > 0) um_4();else zero_4();
    if( (G4[idx] & 1) > 0) um_4();else zero_4();
    //-----------------------------
    if( (R4[idx] & 128) > 0) um_4();else zero_4();
    if( (R4[idx] & 64) > 0) um_4();else zero_4();
    if( (R4[idx] & 32) > 0) um_4();else zero_4();
    if( (R4[idx] & 16) > 0) um_4();else zero_4();
    if( (R4[idx] & 8) > 0) um_4();else zero_4();
    if( (R4[idx] & 4) > 0) um_4();else zero_4();
    if( (R4[idx] & 2) > 0) um_4();else zero_4();
    if( (R4[idx] & 1) > 0) um_4();else zero_4();
    //-----------------------------
    if( (B4[idx] & 128) > 0) um_4();else zero_4();
    if( (B4[idx] & 64) > 0) um_4();else zero_4();
    if( (B4[idx] & 32) > 0) um_4();else zero_4();
    if( (B4[idx] & 16) > 0) um_4();else zero_4();
    if( (B4[idx] & 8) > 0) um_4();else zero_4();
    if( (B4[idx] & 4) > 0) um_4();else zero_4();
    if( (B4[idx] & 2) > 0) um_4();else zero_4();
    if( (B4[idx] & 1) > 0) um_4();else zero_4();
}
void SendBuffCh5(uint8_t idx ){
   //-----------------------------
    if( (G5[idx] & 128) > 0) um_5();else zero_5();
    if( (G5[idx] & 64) > 0) um_5();else zero_5();
    if( (G5[idx] & 32) > 0) um_5();else zero_5();
    if( (G5[idx] & 16) > 0) um_5();else zero_5();
    if( (G5[idx] & 8) > 0) um_5();else zero_5();
    if( (G5[idx] & 4) > 0) um_5();else zero_5();
    if( (G5[idx] & 2) > 0) um_5();else zero_5();
    if( (G5[idx] & 1) > 0) um_5();else zero_5();
    //-----------------------------
    if( (R5[idx] & 128) > 0) um_5();else zero_5();
    if( (R5[idx] & 64) > 0) um_5();else zero_5();
    if( (R5[idx] & 32) > 0) um_5();else zero_5();
    if( (R5[idx] & 16) > 0) um_5();else zero_5();
    if( (R5[idx] & 8) > 0) um_5();else zero_5();
    if( (R5[idx] & 4) > 0) um_5();else zero_5();
    if( (R5[idx] & 2) > 0) um_5();else zero_5();
    if( (R5[idx] & 1) > 0) um_5();else zero_5();
    //-----------------------------
    if( (B5[idx] & 128) > 0) um_5();else zero_5();
    if( (B5[idx] & 64) > 0) um_5();else zero_5();
    if( (B5[idx] & 32) > 0) um_5();else zero_5();
    if( (B5[idx] & 16) > 0) um_5();else zero_5();
    if( (B5[idx] & 8) > 0) um_5();else zero_5();
    if( (B5[idx] & 4) > 0) um_5();else zero_5();
    if( (B5[idx] & 2) > 0) um_5();else zero_5();
    if( (B5[idx] & 1) > 0) um_5();else zero_5();
}
void SendBuffCh6(uint8_t idx ){
   //-----------------------------
    if( (G6[idx] & 128) > 0) um_6();else zero_6();
    if( (G6[idx] & 64) > 0) um_6();else zero_6();
    if( (G6[idx] & 32) > 0) um_6();else zero_6();
    if( (G6[idx] & 16) > 0) um_6();else zero_6();
    if( (G6[idx] & 8) > 0) um_6();else zero_6();
    if( (G6[idx] & 4) > 0) um_6();else zero_6();
    if( (G6[idx] & 2) > 0) um_6();else zero_6();
    if( (G6[idx] & 1) > 0) um_6();else zero_6();
    //-----------------------------
    if( (R6[idx] & 128) > 0) um_6();else zero_6();
    if( (R6[idx] & 64) > 0) um_6();else zero_6();
    if( (R6[idx] & 32) > 0) um_6();else zero_6();
    if( (R6[idx] & 16) > 0) um_6();else zero_6();
    if( (R6[idx] & 8) > 0) um_6();else zero_6();
    if( (R6[idx] & 4) > 0) um_6();else zero_6();
    if( (R6[idx] & 2) > 0) um_6();else zero_6();
    if( (R6[idx] & 1) > 0) um_6();else zero_6();
    //-----------------------------
    if( (B6[idx] & 128) > 0) um_6();else zero_6();
    if( (B6[idx] & 64) > 0) um_6();else zero_6();
    if( (B6[idx] & 32) > 0) um_6();else zero_6();
    if( (B6[idx] & 16) > 0) um_6();else zero_6();
    if( (B6[idx] & 8) > 0) um_6();else zero_6();
    if( (B6[idx] & 4) > 0) um_6();else zero_6();
    if( (B6[idx] & 2) > 0) um_6();else zero_6();
    if( (B6[idx] & 1) > 0) um_6();else zero_6();
}


//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
void SetLED(uint8_t channel, uint8_t type, uint8_t led, uint8_t color1, uint8_t color2, uint8_t color3){
    
    uint8_t red, green, blue;
             
    if(type == 0){  // Algumas fitas tem o a sequencia RGB invertidas... LEDs inferior Tampa ok.
        red = color2;
        green = color1;
        blue = color3;
    }
    else if(type==1){
        red = color1;
        green = color3;
        blue = color2;
    }
    //-----------------
    if(channel == 0){
        R0[led]=red;
        G0[led]=green;
        B0[led]=blue;
    }
    else if(channel == 1){
        R1[led]=red;
        G1[led]=green;
        B1[led]=blue;
    }
    else if(channel == 2){
        R2[led]=red;
        G2[led]=green;
        B2[led]=blue;
    }
    else if(channel == 3){
        R3[led]=red;
        G3[led]=green;
        B3[led]=blue;
    }
    else if(channel == 4){
        R4[led]=red;
        G4[led]=green;
        B4[led]=blue;
    }
    else if(channel == 5){
        R5[led]=red;
        G5[led]=green;
        B5[led]=blue;
    }
}


//------------------------------------------------------------------------------
// Rotima de teste dos LEDs (1 x na inicializa��o))
//------------------------------------------------------------------------------
void TestLEDs(){  
}
//------------------------
void AppTimer1s(){
}   
//------------------------
// Interrompe a cada 100ms
//------------------------
void AppTimer100ms(){
}
//------------------------
// Interrompe a cada 10ms
//------------------------
void AppTimer10ms(){
    static int cnt=0;
    
    if(send_ch0){
        if(cnt<ch0_len){
            EUSART1_Write(CH0[cnt]);
            cnt++;
        }
        else {
            cnt=0;
            send_ch0 = false;
        }
    }
    
     
}
//------------------------
// Interrompe a cada 1ms
//------------------------
void AppTimer1ms(){
    
    if(ShootLedsCh0 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH0; Idx++)
            SendBuffCh0(Idx);
        ShootLedsCh0 = 0;
    }
    if(ShootLedsCh1 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH1; Idx++)
            SendBuffCh1(Idx);
        ShootLedsCh1 = 0;
    }
    if(ShootLedsCh2 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH2; Idx++)
            SendBuffCh2(Idx);
        ShootLedsCh2 = 0;
    }
    if(ShootLedsCh3 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH3; Idx++)
            SendBuffCh3(Idx);
        ShootLedsCh3 = 0;
    }
    if(ShootLedsCh4 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH4; Idx++)
            SendBuffCh4(Idx);
        ShootLedsCh4 = 0;
    }
    if(ShootLedsCh5 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH5; Idx++)
            SendBuffCh5(Idx);
        ShootLedsCh5 = 0;
    }
    if(ShootLedsCh6 == 1){
        for(Idx=0; Idx < MAX_LEDS_CH6; Idx++)
            SendBuffCh6(Idx);
        ShootLedsCh6 = 0;
    }
}    


//------------------------------------------------------------------------------
// Interrup��o do tmr0  pr�ximo a 32.55uS.
//------------------------------------------------------------------------------
void AppTimer30us(void)  {
    static int count1ms = 4;
    static int count10ms = 9;
    static int count100ms = 9;
    static int count1000ms = 9;
   
    //---------------------------
    if (count1ms > 0) count1ms--;
    else {
        count1ms = 33; //33
        AppTimer1ms();
        if (count10ms > 0)count10ms--;
        else {
            count10ms = 9;
            AppTimer10ms();
            if (count100ms > 0)count100ms--;
            else {
                count100ms = 9;
                AppTimer100ms();
                if (count1000ms > 0)count1000ms--;
                else {
                    count1000ms = 9;
                    AppTimer1s();
                }
            }
        }
    }       

}

//------------------------------------------------------------------------------
// Interrupcao de recepcao serial
// Formato de pacote de entrada:
//          preamb chann type len_pay strt_pay dt0 dt1    dtn
// DadosRx = [85,    1,    1,    8,      254,   1,  2...  11]
//------------------------------------------------------------------------------
void AppINT_USART1_RX(unsigned char rxData)
{    
    static int Idx2, Idx3;
    static int len_package = 0;
    static bool capturando = false;
    
   
    
    if(capturando){
        
        
        CH0[Idx3] = rxData; 
        
       // EUSART1_Write(CH0[Idx3]);
        
       // EUSART1_Write(Idx3);
        
        if(Idx2 > (len_package)){
            capturando=false;
            Idx2 = 0;
            Idx3 = 0;
            send_ch0 = true;
       }
        
    }
    
    
    Buffer[Idx2]= rxData;
    if(Buffer[Idx2] == 254 && !capturando){
        if(Buffer[Idx2-4]== 85){
            len_package= Buffer[Idx2-1];
            ch0_len = len_package; 
            type= Buffer[Idx2-2];
            channel= Buffer[Idx2-3];
            //EUSART1_Write(channel);
            capturando = true;
            Idx2 = 2;
            Idx3 = 0;
        }
    }
    else{
       Idx2++;
       Idx3++;
       
    }
    
}
 
//------------------------------------------------------------------------------
// Interrupcao de recepcao serial

// pacote com 7  bytes:
// canal(0-5) Type(0-1) led(0-N) red_val(0-254) green_val(0-254) blue_val(0-254) end_code(255)
// Frmt:  0       0     1        10                 0             10               255

// Pacote com2 bytes:
// cmd(0-10)  end_code(255)
// Frmt:  0      255
//------------------------------------------------------------------------------
/*
void AppINT_USART1_RX(unsigned char rxData)
{    
    uint8_t channel, pos, red, green, blue, cmd , type, c;
    EUSART1_Write(rxData);
    Buffer[Idx]= rxData;
    
    static int data_cnt;
    data_cnt++;
    
    if(Buffer[Idx] == 255){ 
       
        if(data_cnt==7){       // Pacote com 5 cmds + end_code
           
            channel = Buffer[Idx-6];
            type = Buffer[Idx-5];
            pos = Buffer[Idx-4];        
            red= Buffer[Idx-3];
            green = Buffer[Idx-2];
            blue = Buffer[Idx-1];

            Idx = 0;
            
            SetLED(channel, type, pos, red, green, blue); 

            if(channel==0)  ShootLedsCh0 = 1;
            else if(channel==1)  ShootLedsCh1 = 1;
            else if(channel==2)  ShootLedsCh2 = 1;
            else if(channel==3)  ShootLedsCh3 = 1;
            else if(channel==4)  ShootLedsCh4 = 1;
            else if(channel==5)  ShootLedsCh5 = 1;          
            IdxFrame = 0;
            
            data_cnt=0; 
            
        }
        if(data_cnt==2){       // Pacote com 1 cmd + end_code
            
           cmd = Buffer[Idx-1];      
           Idx = 0;
           
           if(cmd==0){ 
                LED_Toggle();
                for(int c=0; c< 50; c++){
                    SetLED(0, RBG, c, 10 , 0 , 0); // Fita Tampo menor
                    SetLED(1, GBR, c, 10 , 0 , 0); // Fita ainda nao utilizada
                }
                ShootLedsCh0 = 1;
                ShootLedsCh1 = 1;
           }
           else if(cmd==1){   
                LED_Toggle();
                for(int c=0; c< 50; c++){
                    SetLED(0, RBG, c, 0 , 10 , 0);
                    SetLED(1, GBR, c, 0 , 10 , 0);
                }
                ShootLedsCh0 = 1;
                ShootLedsCh1 = 1;
           }
           else if(cmd==2){  
                LED_Toggle();
                for(int c=0; c< 50; c++){
                    SetLED(0, RBG, c, 0 , 0 , 10);
                    SetLED(1, GBR, c, 0 , 0 , 10);
                }
                ShootLedsCh0 = 1;
                ShootLedsCh1 = 1;
           }
           
           data_cnt=0; 
        }    
    }
    else  
      Idx += 1;
}
  */
//------------------------------------------------------------------------------
//End of File
//--------------