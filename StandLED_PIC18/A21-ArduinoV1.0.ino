// --------------------------------------------------------------------------------------------
// Programa Arduino para A-21: Python COM-Port Explorer Final
// Dev: N.M.
// Data: 22/10/2020
// Referencias:# uLab Eletronica
// https://github.com/NivaldoMattos/Curso-de-Python-com-Interface-Grafica
// --------------------------------------------------------------------------------------------

String inputString = "";         
bool sendTemperature = false;  
bool LedOn = false;
unsigned char Buffer[10];
const int RPin = 10;     // LED Vermelho
const int GPin = 9;      // LED Verde
const int BPin = 11;     // LED Azul
const int GNDPin = 8;    // GND dos 3 LED´s

int Red = 0;             // Variaveis para guardar o brilho de cada LED
int Green = 0;           //
int Blue = 0;            //

const int LM35 = A0;     // Pino para a entrada do LM35  (1->5V  2->A0  3->GND)
// https://www.homemade-circuits.com/lm35-circuit/

float temperatura;       // Variavel para guardar a temperatura 

// --------------------------------------------------------------------------------------------
// Configurações do programa
// --------------------------------------------------------------------------------------------
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);    // LED "L" na placa do arduino (Pino 13)
  pinMode(RPin, OUTPUT);           // 
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);
  pinMode(GNDPin, OUTPUT);

  digitalWrite(GNDPin, LOW);
  Serial.begin(256000);
  inputString.reserve(8);          // Reservei 8 bytes para os comandos que chegam pela serial
}
// --------------------------------------------------------------------------------------------
// Rotima main, fica executando sempre...
// --------------------------------------------------------------------------------------------
void loop() {

  analogWrite(RPin, Red);       // Escreve as cores no LED RGB
  analogWrite(GPin, Green);
  analogWrite(BPin, Blue);
  
  temperatura = (float(analogRead(LM35))*5/(1023))/0.01;  //Le o AD e converte para temperatura
  
  if(sendTemperature)             
    Serial.println(temperatura); // Envia temeratura para a serial se o flag for true
  
  digitalWrite(LED_BUILTIN, LedOn); // Atualiza o estado do LED "L"

  delay(500);
  
}

// --------------------------------------------------------------------------------------------
// Interrupção de recepção serial - Passa aqui a cada byte que a serial recebe.
// --------------------------------------------------------------------------------------------
void serialEvent() {
  static int Idx = 0;     
  while (Serial.available()) {    
    Buffer[Idx] = (unsigned char)Serial.read();   // Recebe 1 byte
   
    if (Buffer[Idx] == 255){      // Se for==255, os 3 bytes anteriores foram as cores
       Red = Buffer[Idx-1];
       Green = Buffer[Idx-2];
       Blue = Buffer[Idx-3];
       Idx = 0;
    }
    else if(Buffer[Idx] == 254){  //Enviando a temperatura
      sendTemperature = true;
    }
    else if(Buffer[Idx] == 253){
      sendTemperature = false;
    }
    else if(Buffer[Idx] == 252){  //Liga o LED
      LedOn = true;
    } 
    else if(Buffer[Idx] == 251){
      LedOn = false;
      Idx = 0;
    }
    else  
      Idx += 1;
  }
}
// --------------------------------------------------------------------------------------------
// E.O.F
// --------------------------------------------------------------------------------------------
