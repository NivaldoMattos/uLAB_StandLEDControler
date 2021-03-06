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
// Formato de pacote de entrada:
//          preamb chann type len_pay strt_pay dt0 dt1    dtn
// DadosRx = [85,    1,    1,    8,      254,   1,  2...  11]
//------------------------------------------------------------------------------
#include "app.h"
#include <xc.h>
#include "pin_manager.h"
#include "eusart1.h"
//------------------------------------------------------------------------------
#define MY_RX_BUFFER_SIZE 64
static uint8_t Buffer[MY_RX_BUFFER_SIZE];

// Sao 50 chips enderecaveis em 5 metros da fita de LED IX1903b

# define MAX_LEDS_CH1 64
# define MAX_LEDS_CH2 64
# define MAX_LEDS_CH3 64
# define MAX_LEDS_CH4 64
# define MAX_LEDS_CH5 64
# define MAX_LEDS_CH6 64
# define MAX_LEDS_CH7 64

# define RBG 0
# define GBR 1

static uint8_t CH1[MAX_LEDS_CH1];
static uint8_t CH2[MAX_LEDS_CH2];
static uint8_t CH3[MAX_LEDS_CH3];
static uint8_t CH4[MAX_LEDS_CH4];
static uint8_t CH5[MAX_LEDS_CH5];
static uint8_t CH6[MAX_LEDS_CH6];
static uint8_t CH7[MAX_LEDS_CH7];

bool  SendLedsCh1 = false;
bool  SendLedsCh2 = false;
bool  SendLedsCh3 = false;
bool  SendLedsCh4 = false;
bool  SendLedsCh5 = false;
bool  SendLedsCh6 = false;
bool  SendLedsCh7 = false;

uint8_t ch1_len = 0;
uint8_t ch2_len = 0;
uint8_t ch3_len = 0;
uint8_t ch4_len = 0;
uint8_t ch5_len = 0;
uint8_t ch6_len = 0;
uint8_t ch7_len = 0;

uint8_t Idx0 = 0;
uint8_t Idx1 = 0;
uint8_t Idx2 = 0;

int channel = 0;
int type = RBG;

uint8_t len_package = 0;
bool capturando = false;

//------------------------------------------------------------------------------
//  Inicializa��o
//------------------------------------------------------------------------------
void AppInitialize(void)
{
    //Habilita INT0
    INTCONbits.INT0IE = 1;
    INTCON2bits.INTEDG0 = 1;

}

//------------------------------------------------------------------------------
//   AppProcess(void): 
//------------------------------------------------------------------------------
void AppProcess(void){
    while(1){
    
    }
}

//------------------------------------------------------------------------------
// Codigo inline para geraco do diagrama de tempos 
// Fita LED com chip IX1903B (um endereco controla 3 LEDs)
// Obs: Refatorar utilizando bloco inline em assembler + ponteiros para
// simplificacao do codigo e unificacaoo destas funcoes.
//------------------------------------------------------------------------------
void um_1(){ LATB0 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); 
             LATB0 = 0;
}
void zero_1(){ LATB0 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB0 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_2(){ LATB1 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB1 = 0;
}
void zero_2(){ LATB1 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB1 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_3(){ LATB2 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB2 = 0;
}
void zero_3(){ LATB2 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB2 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_4(){ LATB3 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB3 = 0;
}
void zero_4(){ LATB3 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB3 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_5(){ LATB4 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB4 = 0;
}
void zero_5(){ LATB4 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB4 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_6(){ LATB5 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATB5 = 0;
}
void zero_6(){ LATB5 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATB5 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }
//-----------------------------
void um_7(){ LATC0 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP();NOP();NOP();NOP();
             NOP();NOP();NOP(); LATC0 = 0;
}
void zero_7(){ LATC0 = 1; NOP();NOP();NOP();NOP();NOP();NOP();
               LATC0 = 0; NOP();NOP();NOP();NOP();NOP();NOP(); }


void SendBuffCh1(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
    //-----------------------------
    if( (CH1[idx_color1] & 128) > 0)um_1(); else zero_1();
    if( (CH1[idx_color1] & 64) > 0) um_1(); else zero_1();
    if( (CH1[idx_color1] & 32) > 0) um_1(); else zero_1();
    if( (CH1[idx_color1] & 16) > 0) um_1(); else zero_1();
    if( (CH1[idx_color1] & 8) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color1] & 4) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color1] & 2) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color1] & 1) > 0)  um_1(); else zero_1();
    //-----------------------------
    if( (CH1[idx_color2] & 128) > 0)um_1(); else zero_1();
    if( (CH1[idx_color2] & 64) > 0) um_1(); else zero_1();
    if( (CH1[idx_color2] & 32) > 0) um_1(); else zero_1();
    if( (CH1[idx_color2] & 16) > 0) um_1(); else zero_1();
    if( (CH1[idx_color2] & 8) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color2] & 4) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color2] & 2) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color2] & 1) > 0)  um_1(); else zero_1();
    //-----------------------------
    if( (CH1[idx_color3] & 128) > 0)um_1(); else zero_1();
    if( (CH1[idx_color3] & 64) > 0) um_1(); else zero_1();
    if( (CH1[idx_color3] & 32) > 0) um_1(); else zero_1();
    if( (CH1[idx_color3] & 16) > 0) um_1(); else zero_1();
    if( (CH1[idx_color3] & 8) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color3] & 4) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color3] & 2) > 0)  um_1(); else zero_1();
    if( (CH1[idx_color3] & 1) > 0)  um_1(); else zero_1();
}

void SendBuffCh2(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
    //-----------------------------
    if( (CH2[idx_color1] & 128) > 0)um_2(); else zero_2();
    if( (CH2[idx_color1] & 64) > 0) um_2(); else zero_2();
    if( (CH2[idx_color1] & 32) > 0) um_2(); else zero_2();
    if( (CH2[idx_color1] & 16) > 0) um_2(); else zero_2();
    if( (CH2[idx_color1] & 8) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color1] & 4) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color1] & 2) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color1] & 1) > 0)  um_2(); else zero_2();
    //-----------------------------
    if( (CH2[idx_color2] & 128) > 0)um_2(); else zero_2();
    if( (CH2[idx_color2] & 64) > 0) um_2(); else zero_2();
    if( (CH2[idx_color2] & 32) > 0) um_2(); else zero_2();
    if( (CH2[idx_color2] & 16) > 0) um_2(); else zero_2();
    if( (CH2[idx_color2] & 8) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color2] & 4) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color2] & 2) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color2] & 1) > 0)  um_2(); else zero_2();
    //-----------------------------
    if( (CH2[idx_color3] & 128) > 0)um_2(); else zero_2();
    if( (CH2[idx_color3] & 64) > 0) um_2(); else zero_2();
    if( (CH2[idx_color3] & 32) > 0) um_2(); else zero_2();
    if( (CH2[idx_color3] & 16) > 0) um_2(); else zero_2();
    if( (CH2[idx_color3] & 8) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color3] & 4) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color3] & 2) > 0)  um_2(); else zero_2();
    if( (CH2[idx_color3] & 1) > 0)  um_2(); else zero_2();
}


void SendBuffCh3(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
    //-----------------------------
    if( (CH3[idx_color1] & 128) > 0)um_3(); else zero_3();
    if( (CH3[idx_color1] & 64) > 0) um_3(); else zero_3();
    if( (CH3[idx_color1] & 32) > 0) um_3(); else zero_3();
    if( (CH3[idx_color1] & 16) > 0) um_3(); else zero_3();
    if( (CH3[idx_color1] & 8) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color1] & 4) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color1] & 2) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color1] & 1) > 0)  um_3(); else zero_3();
    //-----------------------------
    if( (CH3[idx_color2] & 128) > 0)um_3(); else zero_3();
    if( (CH3[idx_color2] & 64) > 0) um_3(); else zero_3();
    if( (CH3[idx_color2] & 32) > 0) um_3(); else zero_3();
    if( (CH3[idx_color2] & 16) > 0) um_3(); else zero_3();
    if( (CH3[idx_color2] & 8) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color2] & 4) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color2] & 2) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color2] & 1) > 0)  um_3(); else zero_3();
    //-----------------------------
    if( (CH3[idx_color3] & 128) > 0)um_3(); else zero_3();
    if( (CH3[idx_color3] & 64) > 0) um_3(); else zero_3();
    if( (CH3[idx_color3] & 32) > 0) um_3(); else zero_3();
    if( (CH3[idx_color3] & 16) > 0) um_3(); else zero_3();
    if( (CH3[idx_color3] & 8) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color3] & 4) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color3] & 2) > 0)  um_3(); else zero_3();
    if( (CH3[idx_color3] & 1) > 0)  um_3(); else zero_3();
}
void SendBuffCh4(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
        //-----------------------------
    if( (CH4[idx_color1] & 128) > 0)um_4(); else zero_4();
    if( (CH4[idx_color1] & 64) > 0) um_4(); else zero_4();
    if( (CH4[idx_color1] & 32) > 0) um_4(); else zero_4();
    if( (CH4[idx_color1] & 16) > 0) um_4(); else zero_4();
    if( (CH4[idx_color1] & 8) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color1] & 4) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color1] & 2) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color1] & 1) > 0)  um_4(); else zero_4();
    //-----------------------------
    if( (CH4[idx_color2] & 128) > 0)um_4(); else zero_4();
    if( (CH4[idx_color2] & 64) > 0) um_4(); else zero_4();
    if( (CH4[idx_color2] & 32) > 0) um_4(); else zero_4();
    if( (CH4[idx_color2] & 16) > 0) um_4(); else zero_4();
    if( (CH4[idx_color2] & 8) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color2] & 4) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color2] & 2) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color2] & 1) > 0)  um_4(); else zero_4();
    //-----------------------------
    if( (CH4[idx_color3] & 128) > 0)um_4(); else zero_4();
    if( (CH4[idx_color3] & 64) > 0) um_4(); else zero_4();
    if( (CH4[idx_color3] & 32) > 0) um_4(); else zero_4();
    if( (CH4[idx_color3] & 16) > 0) um_4(); else zero_4();
    if( (CH4[idx_color3] & 8) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color3] & 4) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color3] & 2) > 0)  um_4(); else zero_4();
    if( (CH4[idx_color3] & 1) > 0)  um_4(); else zero_4();
}
void SendBuffCh5(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
        //-----------------------------
    if( (CH5[idx_color1] & 128) > 0)um_5(); else zero_5();
    if( (CH5[idx_color1] & 64) > 0) um_5(); else zero_5();
    if( (CH5[idx_color1] & 32) > 0) um_5(); else zero_5();
    if( (CH5[idx_color1] & 16) > 0) um_5(); else zero_5();
    if( (CH5[idx_color1] & 8) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color1] & 4) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color1] & 2) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color1] & 1) > 0)  um_5(); else zero_5();
    //-----------------------------
    if( (CH5[idx_color2] & 128) > 0)um_5(); else zero_5();
    if( (CH5[idx_color2] & 64) > 0) um_5(); else zero_5();
    if( (CH5[idx_color2] & 32) > 0) um_5(); else zero_5();
    if( (CH5[idx_color2] & 16) > 0) um_5(); else zero_5();
    if( (CH5[idx_color2] & 8) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color2] & 4) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color2] & 2) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color2] & 1) > 0)  um_5(); else zero_5();
    //-----------------------------
    if( (CH5[idx_color3] & 128) > 0)um_5(); else zero_5();
    if( (CH5[idx_color3] & 64) > 0) um_5(); else zero_5();
    if( (CH5[idx_color3] & 32) > 0) um_5(); else zero_5();
    if( (CH5[idx_color3] & 16) > 0) um_5(); else zero_5();
    if( (CH5[idx_color3] & 8) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color3] & 4) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color3] & 2) > 0)  um_5(); else zero_5();
    if( (CH5[idx_color3] & 1) > 0)  um_5(); else zero_5();
}
void SendBuffCh6(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
        //-----------------------------
    if( (CH6[idx_color1] & 128) > 0)um_6(); else zero_6();
    if( (CH6[idx_color1] & 64) > 0) um_6(); else zero_6();
    if( (CH6[idx_color1] & 32) > 0) um_6(); else zero_6();
    if( (CH6[idx_color1] & 16) > 0) um_6(); else zero_6();
    if( (CH6[idx_color1] & 8) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color1] & 4) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color1] & 2) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color1] & 1) > 0)  um_6(); else zero_6();
    //-----------------------------
    if( (CH6[idx_color2] & 128) > 0)um_6(); else zero_6();
    if( (CH6[idx_color2] & 64) > 0) um_6(); else zero_6();
    if( (CH6[idx_color2] & 32) > 0) um_6(); else zero_6();
    if( (CH6[idx_color2] & 16) > 0) um_6(); else zero_6();
    if( (CH6[idx_color2] & 8) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color2] & 4) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color2] & 2) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color2] & 1) > 0)  um_6(); else zero_6();
    //-----------------------------
    if( (CH6[idx_color3] & 128) > 0)um_6(); else zero_6();
    if( (CH6[idx_color3] & 64) > 0) um_6(); else zero_6();
    if( (CH6[idx_color3] & 32) > 0) um_6(); else zero_6();
    if( (CH6[idx_color3] & 16) > 0) um_6(); else zero_6();
    if( (CH6[idx_color3] & 8) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color3] & 4) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color3] & 2) > 0)  um_6(); else zero_6();
    if( (CH6[idx_color3] & 1) > 0)  um_6(); else zero_6();
}
void SendBuffCh7(uint8_t idx_color1, uint8_t idx_color2, uint8_t idx_color3){
        //-----------------------------
    if( (CH7[idx_color1] & 128) > 0)um_7(); else zero_7();
    if( (CH7[idx_color1] & 64) > 0) um_7(); else zero_7();
    if( (CH7[idx_color1] & 32) > 0) um_7(); else zero_7();
    if( (CH7[idx_color1] & 16) > 0) um_7(); else zero_7();
    if( (CH7[idx_color1] & 8) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color1] & 4) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color1] & 2) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color1] & 1) > 0)  um_7(); else zero_7();
    //-----------------------------
    if( (CH7[idx_color2] & 128) > 0)um_7(); else zero_7();
    if( (CH7[idx_color2] & 64) > 0) um_7(); else zero_7();
    if( (CH7[idx_color2] & 32) > 0) um_7(); else zero_7();
    if( (CH7[idx_color2] & 16) > 0) um_7(); else zero_7();
    if( (CH7[idx_color2] & 8) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color2] & 4) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color2] & 2) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color2] & 1) > 0)  um_7(); else zero_7();
    //-----------------------------
    if( (CH7[idx_color3] & 128) > 0)um_7(); else zero_7();
    if( (CH7[idx_color3] & 64) > 0) um_7(); else zero_7();
    if( (CH7[idx_color3] & 32) > 0) um_7(); else zero_7();
    if( (CH7[idx_color3] & 16) > 0) um_7(); else zero_7();
    if( (CH7[idx_color3] & 8) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color3] & 4) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color3] & 2) > 0)  um_7(); else zero_7();
    if( (CH7[idx_color3] & 1) > 0)  um_7(); else zero_7();
}


void AppTimer1ms(){
    if(SendLedsCh1){ Idx0=0; 
        while(Idx0 < ch1_len){ SendBuffCh1(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh1 = false; }
    if(SendLedsCh2){ Idx0=0;
        while(Idx0 < ch2_len){ SendBuffCh2(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh2 = false; }
    if(SendLedsCh3){ Idx0=0;
        while(Idx0 < ch3_len){ SendBuffCh3(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh3 = false; }
    if(SendLedsCh4){ Idx0=0;
        while(Idx0 < ch4_len){ SendBuffCh4(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh4 = false; }
    if(SendLedsCh5){ Idx0=0;
        while(Idx0 < ch5_len){ SendBuffCh5(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh5 = false; }
    if(SendLedsCh6){ Idx0=0;
        while(Idx0 < ch6_len){ SendBuffCh6(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh6 = false; }
    if(SendLedsCh7){ Idx0=0;
        while(Idx0 < ch7_len){ SendBuffCh7(Idx0, Idx0+1, Idx0+2); Idx0+=3;}
        SendLedsCh7 = false; }
}    


//------------------------------------------------------------------------------
// Interrupcaoo do tmr0  proximo a 32.55uS.
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
            //AppTimer10ms();
            if (count100ms > 0)count100ms--;
            else {
                count100ms = 9;
                //AppTimer100ms();
                if (count1000ms > 0)count1000ms--;
                else {
                    count1000ms = 9;
                    //AppTimer1s();
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
    // Obs: Vari�vel est�tica perdendo valor neste ponto...
    Buffer[Idx1]= rxData;
    if(Buffer[Idx1] == 254 && !capturando){
        if(Buffer[Idx1-4]== 85){
            len_package= Buffer[Idx1-1];
            
            type= Buffer[Idx1-2];
            channel= Buffer[Idx1-3];
            if(channel==0){
            }
            else if(channel==1){
                ch1_len = len_package;
            }
            else if(channel==2)
                ch2_len = len_package;
            else if(channel==3)
                ch3_len = len_package;
            else if(channel==4)
                ch4_len = len_package;
            else if(channel==5)
                ch5_len = len_package;
            else if(channel==6)
                ch6_len = len_package;
            else if(channel==7)
                ch7_len = len_package;
            capturando = true;
            Idx2 = 0;
        }
    }
    else {
       if(capturando){
                if(channel==0){
            }
            else if(channel==1)
                CH1[Idx2] = rxData;
            else if(channel==2)
                CH2[Idx2] = rxData;
            else if(channel==3)
                CH3[Idx2] = rxData;
            else if(channel==4)
                CH4[Idx2] = rxData;
            else if(channel==5)
                CH5[Idx2] = rxData;
            else if(channel==6)
                CH6[Idx2] = rxData;
            else if(channel==7)
                CH7[Idx2] = rxData;
            
            Idx1=0;
            //EUSART1_Write(Idx2);
            if(Idx2 >= len_package-2){  //
                capturando=false;
                Idx1=0;
                Idx2=0;
                if(channel==0){
                }
                else if(channel==1)
                    SendLedsCh1 = 1;
                else if(channel==2)
                    SendLedsCh2 = 1;
                else if(channel==3)
                    SendLedsCh3 = 1;
                else if(channel==4)
                    SendLedsCh4 = 1;
                else if(channel==5)
                    SendLedsCh5 = 1;
                else if(channel==6)
                    SendLedsCh6 = 1;
                else if(channel==7)
                    SendLedsCh7 = 1;
               LED_Toggle();
            }
            else
                Idx2++; 
       }
    }
    Idx1++; 
}
//------------------------------------------------------------------------------
//End of File
//------------------------------------------------------------------------------