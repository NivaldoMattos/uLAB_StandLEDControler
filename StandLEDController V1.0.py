# -----------------------------------------------------------------------------------
# Controlador para os LEDs da bancada uLAB
# Dev: N.M.
# Data: 23/05/2021
# Referencias:# uLab Eletronica
# https://github.com/NivaldoMattos/Curso-de-Python-com-Interface-Grafica
# -----------------------------------------------------------------------------------
# Importações
# -----------------------------------------------------------------------------------
from tkinter import *
import ulcom
import ulwplace1
import threading
import serial.tools.list_ports
from time import sleep
from tkinter import colorchooser
from functools import partial

Master = Tk()

ON = True
OFF = False

LED_SEQ_RBG = 0
LED_SEQ_GBR = 1
PREAMB      = 85   # 0x55
STRT_PAY    = 254  # 0xFE

SearchingPorts = True
GetTemperatureFlag = False
x="Teste"

channel = 1

# Bancada_superior
Top = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

# Bancada_superior
Utop = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

# Torres de suporte da bancada superior 
Tw_1 = [1, 1, 1,  1, 1, 1,  1, 1, 1]
Tw_2 = [1, 1, 1,  1, 1, 1,  1, 1, 1]
Tw_3 = [1, 1, 1,  1, 1, 1,  1, 1, 1]
Tw_4 = [1, 1, 1,  1, 1, 1,  1, 1, 1]

# Bancada_inferior
Bench_edge = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

Clear = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ]

Cena1 =[ [4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 
2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2, 4, 0, 2] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] , [0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0] ]


Cena2 = [ [0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 
9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9] , [191, 0, 0, 191, 0, 0, 191, 0, 0] , [0, 255, 255, 0, 255, 255, 0, 255, 255] , [0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0] , [60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64, 60, 2, 64] , [0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 
74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0, 0, 74, 0] ]

Cena3 = [ [9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 
0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 1, 1, 1, 1, 1, 1] , [1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] , [32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0, 32, 0, 0] ]

Cena4 =[ [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] , [10, 245, 1, 10, 245, 1, 10, 245, 1] , [10, 245, 1, 10, 245, 1, 10, 245, 1] , [10, 245, 1, 10, 245, 1, 10, 245, 1] , [10, 245, 1, 
10, 245, 1, 10, 245, 1] , [0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91] , [0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225] ]
Cena5 = [ [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] , 
[255, 128, 0, 255, 128, 0, 255, 128, 0] , 
[255, 128, 0, 255, 128, 0, 255, 128, 0] , 
[255, 128, 0, 255, 128, 0, 255, 128, 0] , 
[255, 128, 0, 255, 128, 0, 255, 128, 0] , 
[83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166, 83, 0, 166] , [0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255] ]

Cena6 = [ [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , 
[0, 0, 0, 0, 0, 0, 0, 0, 0] ,
[0, 0, 0, 0, 0, 0, 0, 0, 0] , 
[0, 0, 0, 0, 0, 0, 0, 0, 0] ,
[0, 0, 0, 0, 0, 0, 0, 0, 0] , 
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] ]

varR = 0
varG = 0
varB = 0

# -----------------------------------------------------------------------------------
# Funções
# -----------------------------------------------------------------------------------
def ask_to_open_port():
    message.botton("Please, Open the Serial Port!", "yellow", beep=True)


def send_byte(byte):
    #list = [10, 255,  30,  40, 50, 60]
    if ulcom.is_open():
        ulcom.write_byte(byte)
    else:
        ask_to_open_port()


def SendData(DadosConf, DadosLEDs):

    #print(DadosConf[1])
    #print(len(DadosLEDs))
    
    for idx in range(0, len(DadosConf)):
        send_byte(DadosConf[idx])
        #sleep(0.01)
    
    for idx in range(0, len(DadosLEDs)):
        send_byte(DadosLEDs[idx])
        #sleep(0.01)

    sleep(0.001)


def f_searching_ports():
    global SearchingPorts
    while True:
        sleep(0.3)
        LEDs.LED_TX(OFF)
        if SearchingPorts:
            message.botton('Waitt, searching COM ports...', "red", beep=False)
            ports = serial.tools.list_ports.comports(include_links=False)
            port_list.delete('0', 'end')
            idx = 0
            for port in sorted(ports):
                port_list.insert(idx, port.device)
                idx = idx + 1
            port_list["height"] = idx
            SearchingPorts = False
            message.botton('Chose your desired COM/BAUD pair,'
                            'then press "F6" button...',
                            "yellow",
                            beep=False)
            #    2   3      6     5     4      7         1
            # [Top, Utop, Tw_1, Tw_2, Tw_3, Tw_4, Bench_edge]
            #    1   2      5     4     3      6         0
            
def SendCena(Cena):

    time = 0.001
    DadosConf = [PREAMB, 1, LED_SEQ_RBG, len(Cena[0]), STRT_PAY]
    SendData(DadosConf, Cena[0])
    sleep(time)
    DadosConf = [PREAMB, 2, LED_SEQ_RBG, len(Cena[1]), STRT_PAY]
    SendData(DadosConf, Cena[1])
    sleep(time)
    DadosConf = [PREAMB, 3, LED_SEQ_RBG, len(Cena[2]), STRT_PAY]
    SendData(DadosConf, Cena[2])
    sleep(time)
    DadosConf = [PREAMB, 4, LED_SEQ_RBG, len(Cena[3]), STRT_PAY]
    SendData(DadosConf, Cena[3])
    sleep(time)
    DadosConf = [PREAMB, 5, LED_SEQ_RBG, len(Cena[4]), STRT_PAY]
    SendData(DadosConf, Cena[4])
    sleep(time)
    DadosConf = [PREAMB, 6, LED_SEQ_RBG, len(Cena[5]), STRT_PAY]
    SendData(DadosConf, Cena[5])
    sleep(time)
    DadosConf = [PREAMB, 7, LED_SEQ_RBG, len(Cena[6]), STRT_PAY]
    SendData(DadosConf, Cena[6])
    sleep(time)


def f1():
    global channel
    if ulcom.is_open():
       
        DadosLEDs = Clear 
        for idx in range(1,8):
            DadosConf = [PREAMB, idx, LED_SEQ_RBG, len(DadosLEDs), STRT_PAY]
            SendData(DadosConf, DadosLEDs)
            sleep(0.001)
    else:
        ask_to_open_port()


def f2():
    if ulcom.is_open():
        SendCena(Cena1)
    else:
        ask_to_open_port()


def f3():
    if ulcom.is_open():
        SendCena(Cena2)
    else:
        ask_to_open_port()


def f4():
    if ulcom.is_open():
        SendCena(Cena3)
    else:
        ask_to_open_port()

def f5():
    if ulcom.is_open():
        SendCena(Cena4)
    else:
        ask_to_open_port()

def f6():
    if ulcom.is_open():
        SendCena(Cena5)
    else:
        ask_to_open_port()


def f10():
    global SearchingPorts, channel
    SearchingPorts = True
    print("----------------------")
  
    print("[", Bench_edge, ",", Tw_1, ",", Tw_2, ",", Tw_3, ",", Tw_4, ",", Utop, "," , Top, "]" )

    #if channel < 7:
        #channel = channel + 1
    #else:
        #channel = 0;

    #print("Channel:", channel)



def f11():
    global GetTemperatureFlag
    if ulcom.Port == 'COMx' or ulcom.Baud == '0':
        message.botton('Chose your desired COM/BAUD pair,'
                       'then press "F6" button...',
                       "yellow",
                       beep=False)
        return None

    if not ulcom.is_open():
        ulcom.open()
        if ulcom.is_open():
            message.botton(message='Connected!', color="green", beep=False)
            bt_f11["image"] = btf11_close_img
            GetTemperatureFlag = True
            if not receiving_serial.is_alive():
                receiving_serial.start()
    else:
        ulcom.close()
        message.botton('Unconnected!', "red", beep=False)
        bt_f11["image"] = btf11_open_img


def SendColor(channel):
    global varR, varG, varB
    clr = colorchooser.askcolor(title="Select color")
    str1 = clr[0]
    varR = int(str1[0])
    varG = int(str1[1])
    varB = int(str1[2])
  
    if ulcom.is_open():

        if channel == 7:
            bt_top["background"] = clr[1]
            for idx in range(0, len(Top),3):
                Top[idx+2] = varG
                Top[idx+1] = varR
                Top[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Top), STRT_PAY]
            SendData(DadosConf, Top)

        if channel == 6:
            bt_utop["background"] = clr[1]
            for idx in range(0, len(Utop),3):
                Utop[idx+2] =varB #varB  #
                Utop[idx+1] =varG #varG
                Utop[idx+0] =varR #varR
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Utop), STRT_PAY]
            SendData(DadosConf, Utop)

        if channel == 5:
            bt_tw4["background"] = clr[1]
            for idx in range(0, len(Tw_4),3):
                Tw_4[idx+2] = varG
                Tw_4[idx+1] = varR
                Tw_4[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_4), STRT_PAY]
            SendData(DadosConf, Tw_4)

        if channel == 4:
            bt_tw3["background"] = clr[1]
            for idx in range(0, len(Tw_3),3):
                Tw_3[idx+2] = varG
                Tw_3[idx+1] = varR
                Tw_3[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_3), STRT_PAY]
            SendData(DadosConf, Tw_3)

        if channel == 3:
            bt_tw2["background"] = clr[1]
            for idx in range(0, len(Tw_2),3):
                Tw_2[idx+2] = varG
                Tw_2[idx+1] = varR
                Tw_2[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_2), STRT_PAY]
            SendData(DadosConf, Tw_2)

        if channel == 2:
            bt_tw1["background"] = clr[1]
            for idx in range(0, len(Tw_1),3):
                Tw_1[idx+2] = varG
                Tw_1[idx+1] = varR
                Tw_1[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_1), STRT_PAY]
            SendData(DadosConf, Tw_1)

        if channel == 1:
            bt_bench_edge["background"] = clr[1]
            for idx in range(0, len(Bench_edge),3):
                Bench_edge[idx+2] = varG
                Bench_edge[idx+1] = varR
                Bench_edge[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Bench_edge), STRT_PAY]
            SendData(DadosConf, Bench_edge)

    else:
        ask_to_open_port()


# -----------------------------------------------------------------------------------
# Widgets
# -----------------------------------------------------------------------------------
back_img = PhotoImage(file="images/bg_inicial2.png")
btf1_img = PhotoImage(file="images/bt_s1.png")
btf2_img = PhotoImage(file="images/bt_s2.png")
btf3_img = PhotoImage(file="images/bt_s3.png")
btf4_img = PhotoImage(file="images/bt_s4.png")
btf5_img = PhotoImage(file="images/bt_s5.png")
btf6_img = PhotoImage(file="images/bt_s6.png")


btf10_img = PhotoImage(file="images/btf10.png")
btf11_close_img = PhotoImage(file="images/btf11_close.png")
btf11_open_img = PhotoImage(file="images/btf11_open.png")

label_fundo = Label(Master, image=back_img)
label_fundo.place(x=0, y=0)

bt_f1 = Button(Master, image=btf1_img, bd=1, command=f1)
bt_f1.place(width=121, height=70, x=23, y=80)

bt_f2 = Button(Master, image=btf2_img, bd=1, command=f2)
bt_f2.place(width=121, height=70, x=151, y=80)

bt_f3 = Button(Master, image=btf3_img, bd=1, command=f3)
bt_f3.place(width=121, height=70, x=279, y=80)

bt_f4 = Button(Master, image=btf4_img, bd=1, command=f4)
bt_f4.place(width=121, height=70, x=407, y=80)


bt_f5 = Button(Master, image=btf5_img, bd=1, command=f5)
bt_f5.place(width=121, height=70, x=535, y=80)

bt_f6 = Button(Master, image=btf6_img, bd=1, command=f6)
bt_f6.place(width=121, height=70, x=663, y=80)


bt_f10 = Button(Master, image=btf10_img, bd=1, command=f10)
bt_f10.place(width=94, height=50, x=45, y=484)

bt_f11 = Button(Master, image=btf11_open_img, bd=1, command=f11)
bt_f11.place(width=94, height=50, x=158, y=484)


bt_top = Button(Master, background="green", bd=1, command=partial(SendColor, 7)) 
bt_top.place(width=40, height=15, x=430, y=250)

bt_utop = Button(Master, background="green", bd=1, command=partial(SendColor, 6)) 
bt_utop.place(width=40, height=15, x=650, y=290)

bt_tw4 = Button(Master, background="green", bd=1, command=partial(SendColor, 5)) 
bt_tw4.place(width=20, height=20, x=778, y=300)

bt_tw3 = Button(Master, background="green", bd=1, command=partial(SendColor, 4))
bt_tw3.place(width=20, height=20, x=588, y=300)

bt_tw2 = Button(Master, background="green", bd=1, command=partial(SendColor, 3)) 
bt_tw2.place(width=20, height=20, x=540, y=300)

bt_tw1 = Button(Master, background="green", bd=1, command=partial(SendColor, 2)) 
bt_tw1.place(width=20, height=20, x=393, y=300)

bt_bench_edge = Button(Master, background="green", bd=1, command=partial(SendColor, 1))
bt_bench_edge.place(width=40, height=15, x=550, y=410)


port_list = Listbox(Master, height=1, width=7, bd=10, font="Arial 10", bg="black",
                    fg="#008000",
                    highlightcolor="black",
                    highlightthickness=0,
                    selectbackground="black",
                    )

port_list.place(width=83, height=90, x=51, y=385)
port_list.insert(END, "COM5")
port_list.bind('<Double-Button>', lambda e: message.port("green", port_list.get(ANCHOR)))

baud_list = Listbox(Master, height=1, width=7, bd=10, font="Arial 10", bg="black",
                    fg="#008000",
                    highlightcolor="black",
                    highlightthickness=0,
                    selectbackground="black",
                    )

baud_list.place(width=82, height=90, x=163, y=385)
baud_list.insert(END, "9600", "19200", "38400", "115200", "256000")
baud_list.bind('<Double-Button>', lambda e: message.baud("green", baud_list.get(ANCHOR)))

# Threads para a busca das p ortas
searching_ports = threading.Thread(target=f_searching_ports)
searching_ports.daemon = True
searching_ports.start()

# Thread para a recepcao serial
#receiving_serial = threading.Thread(target=f_receiving_serial)
#receiving_serial.daemon = True

# Comandos do mouse para o posicionador de Widgets
#Master.bind('<Button-1>', lambda e: ulwplace1.m_btn1(e, Master))
#Master.bind('<Button-3>', lambda e: ulwplace1.m_btn3(e, Master))
#Master.bind('<ButtonRelease-1>', lambda e: ulwplace1.m_btn1_release(e, Master))

message = ulcom.Message(Master)

# Configuraes da tela Master
Master.title("Python COM-Port Explorer")
Master.iconbitmap(default='images/ulab.ico')
Master.resizable(width=FALSE, height=FALSE)
Master.geometry("986x615+5+5")
#Master.geometry("986x615+-995+3")
Master.mainloop()
# ----------------------------------------------------------------------------------
#  EOF
# ----------------------------------------------------------------------------------

