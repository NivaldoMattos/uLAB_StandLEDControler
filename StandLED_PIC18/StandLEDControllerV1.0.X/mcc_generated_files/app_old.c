//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
#include "app.h"
#include <xc.h>
#include "pin_manager.h"
#include "eusart1.h"


#define MY_RX_BUFFER_SIZE 10
static int CountTick1ms=0;
static int ShootingAngle=60;
static int Angle=0;
static uint8_t MyRxBuffer[MY_RX_BUFFER_SIZE];
static int  Contador=0;
static int  ContFrac=0;


static FlagTransmite=0;

 static int FlagT=0;

 
 static int NumEspiras=0;
 
 
 
void AppInitialize(void)
{
    //Habilita INT0
    INTCONbits.INT0IE = 1;
    //INT0 on rising edge
    //INTCON2bits.INTEDG0 = 1;
    //INT0 on rising edge
    INTCON2bits.INTEDG0 = 0;     
    LED1_SetDigitalOutput(); // Selecionado como pino digital
    LED2_SetDigitalOutput();
    LED3_SetDigitalOutput();
    LED4_SetDigitalOutput();
}
void delay_ms(int tempo)
{
    CountTick1ms=tempo;
    while(CountTick1ms>0);
}

void AppProcess(void)
{
    static int  Contador_old=0;
          //static uint8_t data;
      //if(!IO_S_UP_GetValue()) // Decrementa
      //{
      //   Contador=0;
      //   //-------------------------
      //   while(!IO_S_UP_GetValue());
      //   delay_ms(30);
      //   
      //}
      //putch('a');
      //putch('b');
      if(Contador != Contador_old)
      {
         Contador_old=Contador;  
      }   
      delay_ms(10);
}
//------------------------
// Interrompe a cada 1s
//------------------------
void AppTimer1s()
{
    
   //IO_LED_Toggle();  
         //--------------------------       
  
    
   
   // if(ContFrac==23)
   //     Contador+=10;
    
   // if(ContFrac<9)
   // {
   //    ContFrac++;
   // }
   // else
   // {
   //    ContFrac=0;
   //    Contador++;  
   // }
    
    
    
    
    
    
}       
//------------------------
// Interrompe a cada 100ms
//------------------------
void AppTimer100ms()
{   
    
     //LED3_Toggle();
    
     //static int Cnt1=0;
    
 
     LED3_Toggle();  
    
     
     
     //if(Cnt1==0){putch('1'); }
    //if(Cnt1==1){putch('2'); } 
    //if(Cnt1==3){putch('3'); }
    //if(Cnt1==4){putch('4'); }
    //if(Cnt1==5){putch('5'); }

   
     //if(Cnt1>5)
     //    Cnt1=0;
     //else
     //    Cnt1++;
    
    //LED1_Toggle();   
    //LED2_Toggle();   
    //LED3_Toggle();   
    //LED4_Toggle();   
}
//------------------------
// Interrompe a cada 10ms
//------------------------
void AppTimer10ms(){  

    
     
    
}
//------------------------
// Interrompe a cada 1ms
//------------------------
void AppTimer1ms()
{
       if(CountTick1ms>0)
        CountTick1ms--;  
    
      // if(Contador>=NumEspiras)
          // LED4_SetLow(); 
       
}
//------------------------------------------------------------------------------
// Interrupção do tmr0
//------------------------------------------------------------------------------
void AppTimer100us(void)
{
    static int count1ms = 9;
    static int count10ms = 9;
    static int count100ms = 9;
    static int count1000ms = 9;
    //---------------------------
    if (count1ms > 0) count1ms--;
    else {
        count1ms = 9;
        AppTimer1ms();
        if (count10ms > 0)count10ms--;
        else {
            count10ms = 4;  //
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
// Interrupção do pino RB0
//------------------------------------------------------------------------------
void AppINT0_ISR(void)
{
  
    
    if(ContFrac<7)
    {
        ContFrac+=2;

    }
    else
    {
        ContFrac=0;
        Contador++;
       // LED1_Toggle();
    }
}


void AppResponde(void){  

}

//------------------------------------------------------------------------------
// Interrupção de recepção serial
//------------------------------------------------------------------------------
void AppINT_USART1_RX(char rxData)
{
    static uint8_t Index=0;
    
    if(rxData==1)
       Index=1;
    if(rxData==255)
       Index=0;
    if(Index>0)
    {
        MyRxBuffer[Index]=rxData;
    }
    Index++;
    if(MyRxBuffer[2]=='C')
    {
       // LED1_Toggle();  
        
       // if(MyRxBuffer[3]=='M')
       // if(MyRxBuffer[4]=='D')
       // {
        //    if(MyRxBuffer[5]=='1')
        //    {
           //  LED1_Toggle(); 
              //ContFrac=0;
              //Contador=0;
              //static int tempo=0;
              //tempo=5000;
              //while(tempo--);
              //ContFrac=0;
              //Contador=0; 
          //     LED4_SetLow();
          //  }
           // else if(MyRxBuffer[5]=='2') 
            //{
             // LED4_SetHigh();
            
            
           // }
           // else if(MyRxBuffer[5]=='3')
           // {    
           /*
               
               //  LED1_Toggle();    
              AppPutChar(1);
              AppPutChar(2);
              AppPutChar(3);
              AppPutChar(4);
              AppPutChar(5);
              AppPutChar(6);
              AppPutChar(7);
              AppPutChar(8);
              AppPutChar(9);
              AppPutChar(Contador);
              AppPutChar(0);
              AppPutChar(ContFrac);
              AppPutChar(99);
              AppPutChar(99);
              AppPutChar(15);
              AppPutChar(16);
              AppPutChar(17);
              AppPutChar(18);
              AppPutChar(19);
              AppPutChar(20);
              AppPutChar(21);
              AppPutChar(22);
              AppPutChar(23);
              AppPutChar(24);
              AppPutChar(25);
              AppPutChar(26);
              AppPutChar(27);
              AppPutChar(28);
              AppPutChar(29);
              AppPutChar(30);
              AppPutChar(31);
              AppPutChar(32);
              AppPutChar(33);
              AppPutChar(34);
              AppPutChar(35);
              AppPutChar(36);
            }
            
            NumEspiras=MyRxBuffer[6];
    
        }
          */
    
    
    }
}


static void AppPutChar(unsigned char value){
    static int tempo=0;
    TX_OK=1;
    TXREG1 = value;
   
    tempo=500;
    
    while(tempo--);
    
    //while(TX_OK);
    
}

//------------------------------------------------------------------------------
// FIM
//------------------------------------------------------------------------------

// Deslocador em java
/*
              Data=0x0f;
              switch (State) {
                  case 0:  
                 	  tvV1.setText("Estado="+String.valueOf(State));
                 	  if(Qt_Bits >= 8)   // 8 bits a serem deslocados
                 		    State=0;  // Next State =1
                 	  else
                 		  {
                 		      if(((Data << Qt_Bits) & 128) >0)
                 		         tvV3.setText("Dt=1");
                 		      else
                 		         tvV3.setText("Dt=0");
                         	  Qt_Bits++;
                   	          tvV2.setText("Qt_Bits="+String.valueOf(Qt_Bits));	
                  		      State=1;  // Next state
                          }
                	  break;
                  case 1:   
                	  tvV1.setText("Estado="+String.valueOf(State));	 
                	  tvV3.setText("Sobe Clock...");
                	  State=2;
                	  break;
                  case 2:
                	  tvV1.setText("Estado="+String.valueOf(State));	 
                	  tvV3.setText("Desce Clock...");
                	  State=0;
                      break;
                  default: break;
*/