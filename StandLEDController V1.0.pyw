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

channel = 10

# Bancada_superior
Top = [1, 1, 1,   1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

# Bancada_superior
Utop = [1, 1, 1,   1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

# Torres de suporte da bancada superior 
Tw_1 = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]
Tw_2 = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]
Tw_3 = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]
Tw_4 = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

# Bancada_inferior
Bench_edge = [1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,
1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1]

AllOff = [ [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] , [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0] ]
AllOn = [ [255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255] , [255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255] , [255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255] , [255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255] , [255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255] , [255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255] , [255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255] ]
Cena1 =[ [41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38, 41, 36, 38] , 
[31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38, 31, 33, 38] , 
[31, 32, 32, 31, 32, 32, 31, 32, 32, 31, 32, 32] , 
[41, 34, 37, 41, 34, 37, 41, 34, 37, 41, 34, 37] , 
[45, 35, 38, 45, 35, 38, 45, 35, 38, 45, 35, 38] , 
[41, 34, 34, 41, 34, 34, 41, 34, 34, 41, 34, 34] , 
[36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41, 36, 39, 41] ]

Cena2 = [ [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] , [0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0] ]
Cena3 = [ [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] , [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] , [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] , [255, 
0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] , [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] , [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] , [255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0] ]
Cena4 =[ [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] , [10, 245, 1, 10, 245, 1, 10, 245, 1] , [10, 245, 1, 10, 245, 1, 10, 245, 1] , [10, 245, 1, 10, 245, 1, 10, 245, 1] , [10, 245, 1, 
10, 245, 1, 10, 245, 1] , [0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91, 0, 0, 91] , [0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225, 0, 225, 225] ]

Cena5 = [ [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] ]
Cena6 = [ [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2] , [2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255] , [2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] ]
Cena7 = [ [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255, 2] , [2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255] , [2, 0, 255, 2, 0, 255, 2, 0, 255, 2, 0, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] , [2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255, 2, 2, 255] ]

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
        #LEDs.LED_TX(OFF)
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
    
    #print(len(Cena[0]))
    #print(Cena[0])
    #print(len(Top))
    #print(Top)

    for idx in range(0,len(Top)):
        Top[idx] = Cena[0][idx]    
    for idx in range(0, len(Utop)):
        Utop[idx] = Cena[0][idx]
    for idx in range(0, len(Tw_1)):
        Tw_1[idx] = Cena[0][idx]
    for idx in range(0, len(Tw_2)):
        Tw_2[idx] = Cena[0][idx]
    for idx in range(0, len(Tw_3)):
        Tw_3[idx] = Cena[0][idx]
    for idx in range(0, len(Tw_4)):
        Tw_4[idx] = Cena[0][idx]
    for idx in range(0, len(Bench_edge)):
        Bench_edge[idx] = Cena[0][idx]
    
    time = 0.001
    DadosConf = [PREAMB, 1, LED_SEQ_RBG, len(Top), STRT_PAY]
    SendData(DadosConf, Top)
    sleep(time)
    DadosConf = [PREAMB, 2, LED_SEQ_RBG, len(Utop), STRT_PAY]
    SendData(DadosConf, Utop)
    sleep(time)
    DadosConf = [PREAMB, 3, LED_SEQ_RBG, len(Tw_1), STRT_PAY]
    SendData(DadosConf, Tw_1)
    sleep(time)
    DadosConf = [PREAMB, 4, LED_SEQ_RBG, len(Tw_2), STRT_PAY]
    SendData(DadosConf, Tw_2)
    sleep(time)
    DadosConf = [PREAMB, 5, LED_SEQ_RBG, len(Tw_3), STRT_PAY]
    SendData(DadosConf, Tw_3)
    sleep(time)
    DadosConf = [PREAMB, 6, LED_SEQ_RBG, len(Tw_4), STRT_PAY]
    SendData(DadosConf, Tw_4)
    sleep(time)
    DadosConf = [PREAMB, 7, LED_SEQ_RBG, len(Bench_edge), STRT_PAY]
    SendData(DadosConf, Bench_edge)
    sleep(time)


def SendColor(ch, varG, varR, varB):
    #global varR, varG, varB
    channel = ch
    if ulcom.is_open():

        if channel == 7:
            for idx in range(0, len(Top),3):
                Top[idx+2] = varG
                Top[idx+1] = varR
                Top[idx+0] = varB
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Top), STRT_PAY]
            SendData(DadosConf, Top)

        if channel == 6:
            for idx in range(0, len(Utop),3):
                Utop[idx+2] =varB #varB  #
                Utop[idx+1] =varG #varG
                Utop[idx+0] =varR #varR
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Utop), STRT_PAY]
            SendData(DadosConf, Utop)

        if channel == 5:
            for idx in range(0, len(Tw_4),3):
                Tw_4[idx+2] = varG
                Tw_4[idx+1] = varR
                Tw_4[idx+0] = varB
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_4), STRT_PAY]
            SendData(DadosConf, Tw_4)

        if channel == 4:
            for idx in range(0, len(Tw_3),3):
                Tw_3[idx+2] = varG
                Tw_3[idx+1] = varR
                Tw_3[idx+0] = varB
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_3), STRT_PAY]
            SendData(DadosConf, Tw_3)

        if channel == 3:
            for idx in range(0, len(Tw_2),3):
                Tw_2[idx+2] = varG
                Tw_2[idx+1] = varR
                Tw_2[idx+0] = varB
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_2), STRT_PAY]
            SendData(DadosConf, Tw_2)

        if channel == 2:
            for idx in range(0, len(Tw_1),3):
                Tw_1[idx+2] = varG
                Tw_1[idx+1] = varR
                Tw_1[idx+0] = varB
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_1), STRT_PAY]
            SendData(DadosConf, Tw_1)

        if channel == 1:
            for idx in range(0, len(Bench_edge),3):
                Bench_edge[idx+2] = varG
                Bench_edge[idx+1] = varR
                Bench_edge[idx+0] = varB
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Bench_edge), STRT_PAY]
            SendData(DadosConf, Bench_edge)

    else:
        ask_to_open_port()


def SelectChannel(ch):
    global channel, varG , varR , varB 

    channel = ch
    #varG = 0
   # varR = 0
   # varB = 0

    #print("Channel-:", channel, varG, varR, varB)

    if channel == 1:
        bt_bench_edge.configure(bg="gray")
        varG = Bench_edge[2]
        varR = Bench_edge[1] 
        varB = Bench_edge[0] 
    elif channel == 2: 
        bt_tw1.configure(bg="gray")
        varG = Tw_1[2]
        varR = Tw_1[1] 
        varB = Tw_1[0] 

    elif channel == 3: 
        bt_tw2.configure(bg="gray")
        varG = Tw_2[2]
        varR = Tw_2[1] 
        varB = Tw_2[0] 
    elif channel == 4: 
        bt_tw3.configure(bg="gray")
        varG = Tw_3[2]
        varR = Tw_3[1] 
        varB = Tw_3[0] 
    elif channel == 5: 
        bt_tw4.configure(bg="gray")
        varG = Tw_4[2]
        varR = Tw_4[1] 
        varB = Tw_4[0] 
    elif channel == 6: 
        pass
        bt_utop.configure(bg="gray")
        varB = Utop[2]
        varG = Utop[1] 
        varR = Utop[0] 
    elif channel == 7: 
        pass
        bt_top.configure(bg="gray")
        varG = Top[2]
        varR = Top[1] 
        varB = Top[0] 

    sliderR.set(varR)
    sliderG.set(varG)
    sliderB.set(varB)

    #print("Channel--:", channel, varG, varR, varB)
    SendColor(channel, varG, varR, varB)


def SetColor(ch, varG, varR, varB):
    global channel

    channel = ch

    bt_bench_edge.configure(bg="black")
    bt_tw1.configure(bg="black") 
    bt_tw2.configure(bg="black")  
    bt_tw3.configure(bg="black")  
    bt_tw4.configure(bg="black")  
    bt_top.configure(bg="black")  
    bt_utop.configure(bg="black")  

    idx=0

    if channel == 7:
            #bt_top["background"] = clr[1] 
        for idx in range(0, len(Top),3):
            Top[idx+2] = varG
            Top[idx+1] = varR
            Top[idx+0] = varB

    if channel == 6:
        #bt_utop["background"] = clr[1]
        for idx in range(0, len(Utop),3):
            Utop[idx+2] =varB #varB  #
            Utop[idx+1] =varG #varG
            Utop[idx+0] =varR #varR
    if channel == 5:
        #bt_tw4["background"] = clr[1]
        for idx in range(0, len(Tw_4),3):
            Tw_4[idx+2] = varG
            Tw_4[idx+1] = varR
            Tw_4[idx+0] = varB
    if channel == 4:
        #bt_tw3["background"] = clr[1]
        for idx in range(0, len(Tw_3),3):
            Tw_3[idx+2] = varG
            Tw_3[idx+1] = varR
            Tw_3[idx+0] = varB
    if channel == 3:
        #bt_tw2["background"] = clr[1]
        for idx in range(0, len(Tw_2),3):
            Tw_2[idx+2] = varG
            Tw_2[idx+1] = varR
            Tw_2[idx+0] = varB
    if channel == 2:
        #bt_tw1["background"] = clr[1]
        for idx in range(0, len(Tw_1),3):
            Tw_1[idx+2] = varG
            Tw_1[idx+1] = varR
            Tw_1[idx+0] = varB

    if channel == 1:
        #bt_bench_edge["background"] = clr[1]
        for idx in range(0, len(Bench_edge),3):
            Bench_edge[idx+2] = varG
            Bench_edge[idx+1] = varR
            Bench_edge[idx+0] = varB


def f_AllOff():
    global channel
    print("AllOff")
    sliderR.set(0)
    sliderG.set(0)
    sliderB.set(0)
    if ulcom.is_open():
        SendCena(AllOff)
    else:
        ask_to_open_port()


def f_AllOn(): 
    print("AllOn")
    if ulcom.is_open():
        SendCena(AllOn)
    else:
        ask_to_open_port()


def f_Cena1(): 
    print("Cena1")
    if ulcom.is_open():
        SendCena(Cena1)
    else:
        ask_to_open_port()


def f_Cena2(): 
    print("Cena2")
    if ulcom.is_open():
        SendCena(Cena2)
    else:
        ask_to_open_port()

def f_Cena3(): 
    print("Cena3")
    if ulcom.is_open():
        SendCena(Cena3)
    else:
        ask_to_open_port()

def f_Cena4(): 
    print("Cena4")
    if ulcom.is_open():
        SendCena(Cena4)
    else:
        ask_to_open_port()
def f_Cena5(): 
    print("Cena5")
    if ulcom.is_open():
        SendCena(Cena5)
    else:
        ask_to_open_port()
def f_Cena6(): 
    print("Cena6")
    if ulcom.is_open():
        SendCena(Cena6)
    else:
        ask_to_open_port()

def f_Cena7(): 
    print("Cena7")
    if ulcom.is_open():
        SendCena(Cena7)
    else:
        ask_to_open_port()


def f10():
    global SearchingPorts, channel
    SearchingPorts = True

    print("Dados atuais para o cenário:")
    print( "Cenax = [",Top,",", Utop,",", Tw_1,",", Tw_2,",", Tw_3,",", Tw_4,",", Bench_edge,"]")


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
            #if not receiving_serial.is_alive():
            #    receiving_serial.start()
    else:
        ulcom.close()
        message.botton('Unconnected!', "red", beep=False)
        bt_f11["image"] = btf11_open_img

    #---------------------------------


def FuncSlider(val):
    global channel

    varG = sliderG.get()
    varR = sliderR.get()
    varB = sliderB.get()

    #print("Canal:", channel, "G", varG, "R", varR, "B", varB)


    if ulcom.is_open():

        if channel == 7:
            #bt_top["background"] = varR, varG, varB
            for idx in range(0, len(Top),3):
                Top[idx+2] = varG
                Top[idx+1] = varR
                Top[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Top), STRT_PAY]
            SendData(DadosConf, Top)
            #print("Top:", Top)

        if channel == 6:
            #bt_utop["background"] = varR, varG, varB
            for idx in range(0, len(Utop),3):
                Utop[idx+2] =varB #varB  #
                Utop[idx+1] =varG #varG
                Utop[idx+0] =varR #varR
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Utop), STRT_PAY]
            SendData(DadosConf, Utop)
            #print("Utop:", Utop)


        if channel == 5:
            #bt_tw4["background"] = varR, varG, varB
            for idx in range(0, len(Tw_4),3):
                Tw_4[idx+2] = varG
                Tw_4[idx+1] = varR
                Tw_4[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_4), STRT_PAY]
            SendData(DadosConf, Tw_4)
            #print("Tw_4:", Tw_4)


        if channel == 4:
            #bt_tw3["background"] = varR, varG, varB
            for idx in range(0, len(Tw_3),3):
                Tw_3[idx+2] = varG
                Tw_3[idx+1] = varR
                Tw_3[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_3), STRT_PAY]
            SendData(DadosConf, Tw_3)
            #print("Tw_3:", Tw_3)

        if channel == 3:
            #bt_tw2["background"] = varR, varG, varB
            for idx in range(0, len(Tw_2),3):
                Tw_2[idx+2] = varG
                Tw_2[idx+1] = varR
                Tw_2[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_2), STRT_PAY]
            SendData(DadosConf, Tw_2)
            #print("Tw_2:", Tw_2)

        if channel == 2:
            #bt_tw1["background"] = varR, varG, varB
            for idx in range(0, len(Tw_1),3):
                Tw_1[idx+2] = varG
                Tw_1[idx+1] = varR
                Tw_1[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Tw_1), STRT_PAY]
            SendData(DadosConf, Tw_1)
            #print("Tw_1:", Tw_1)

        if channel == 1:
            #bt_bench_edge["background"] = varR, varG, varB
            for idx in range(0, len(Bench_edge),3):
                Bench_edge[idx+2] = varG
                Bench_edge[idx+1] = varR
                Bench_edge[idx+0] = varB
                #print(idx)
            DadosConf = [PREAMB, channel, LED_SEQ_RBG, len(Bench_edge), STRT_PAY]
            SendData(DadosConf, Bench_edge)
            #print("Bench_edge:", Bench_edge)

    else:
        ask_to_open_port()

# -----------------------------------------------------------------------------------
# Widgets
# -----------------------------------------------------------------------------------
back_img = PhotoImage(file="images/bg_inicial2.png")
'''
btf1_img = PhotoImage(file="images/bt_alloff.png")
btf2_img = PhotoImage(file="images/bt_allon.png")

btf3_img = PhotoImage(file="images/bt_c1.png")
btf4_img = PhotoImage(file="images/bt_c2.png")
btf5_img = PhotoImage(file="images/bt_c3.png")
btf6_img = PhotoImage(file="images/bt_c4.png")
btf7_img = PhotoImage(file="images/bt_c5.png")
btf8_img = PhotoImage(file="images/bt_c6.png")
btf9_img = PhotoImage(file="images/bt_c7.png")
'''

btf10_img = PhotoImage(file="images/btf10.png")
btf11_close_img = PhotoImage(file="images/btf11_close.png")
btf11_open_img = PhotoImage(file="images/btf11_open.png")

label_fundo = Label(Master, image=back_img)
label_fundo.place(x=0, y=0)

bt_f1 = Button(Master, text="AllOff", font = " Arial 20", bd=1, command=f_AllOff)
bt_f1.place(width=100, height=70, x=23, y=80)

bt_f2 = Button(Master, text="AllOn", font = " Arial 20", bd=1, command=f_AllOn)
bt_f2.place(width=100, height=70, x=131, y=80)

bt_f3 = Button(Master, text="Cena1",font = " Arial 20",  bd=1, command=f_Cena1)
bt_f3.place(width=100, height=70, x=239, y=80)

bt_f4 = Button(Master, text="Cena2",font = " Arial 20",  bd=1, command=f_Cena2)
bt_f4.place(width=100, height=70, x=347, y=80)

bt_f5 = Button(Master, text="Cena3", font = " Arial 20", bd=1, command=f_Cena3)
bt_f5.place(width=100, height=70, x=455, y=80)

bt_f6 = Button(Master, text="Cena4", font = " Arial 20", bd=1, command=f_Cena4)
bt_f6.place(width=100, height=70, x=563, y=80)

bt_f7 = Button(Master, text="Cena5", font = " Arial 20", bd=1, command=f_Cena5)
bt_f7.place(width=100, height=70, x=671, y=80)

bt_f8 = Button(Master, text="Cena6",font = " Arial 20",  bd=1, command=f_Cena6)
bt_f8.place(width=100, height=70, x=779, y=80)

bt_f9 = Button(Master, text="Cena7", font = " Arial 20", bd=1, command=f_Cena7)
bt_f9.place(width=100, height=70, x=887, y=80)


bt_f10 = Button(Master, image=btf10_img, bd=1, command=f10)
bt_f10.place(width=94, height=50, x=35, y=480)

bt_f11 = Button(Master, image=btf11_open_img, bd=1, command=f11)
bt_f11.place(width=94, height=50, x=35, y=296)


bt_top = Button(Master, background="green", bd=1, command=partial(SelectChannel, 7))  
bt_top.place(width=40, height=15, x=430, y=250)

bt_utop = Button(Master, background="green", bd=1, command=partial(SelectChannel, 6)) 
bt_utop.place(width=40, height=15, x=650, y=290)

bt_tw4 = Button(Master, background="green", bd=1, command=partial(SelectChannel, 5)) 
bt_tw4.place(width=20, height=20, x=778, y=300)

bt_tw3 = Button(Master, background="green", bd=1, command=partial(SelectChannel, 4))
bt_tw3.place(width=20, height=20, x=588, y=300)

bt_tw2 = Button(Master, background="green", bd=1, command=partial(SelectChannel, 3)) 
bt_tw2.place(width=20, height=20, x=540, y=300)

bt_tw1 = Button(Master, background="green", bd=1, command=partial(SelectChannel, 2)) 
bt_tw1.place(width=20, height=20, x=393, y=300)

bt_bench_edge = Button(Master, background="green", bd=1, command=partial(SelectChannel, 1))
bt_bench_edge.place(width=40, height=15, x=550, y=410)

sliderR=Scale(Master, command=FuncSlider, length=360, from_=255, to=0, resolution=1, orient=VERTICAL, bg="#f5f5f5", bd=2)
sliderR.place(x=130, y=170)

sliderG=Scale(Master, command=FuncSlider, length=360, from_=255, to=0, resolution=1, orient=VERTICAL, bg="#f5f5f5", bd=2)
sliderG.place(x=170, y=170)

sliderB=Scale(Master, command=FuncSlider, length=360, from_=255, to=0, resolution=1, orient=VERTICAL, bg="#f5f5f5", bd=2)
sliderB.place(x=210, y=170)


port_list = Listbox(Master, height=1, width=7, bd=10, font="Arial 10", bg="black",
                    fg="#008000",
                    highlightcolor="black",
                    highlightthickness=0,
                    selectbackground="black",
                    )

port_list.place(width=83, height=90, x=41, y=385)
port_list.insert(END, "COM5")
port_list.bind('<Double-Button>', lambda e: message.port("green", port_list.get(ANCHOR)))

baud_list = Listbox(Master, height=1, width=7, bd=10, font="Arial 10", bg="black",
                    fg="#008000",
                    highlightcolor="black",
                    highlightthickness=0,
                    selectbackground="black",
                    )

baud_list.place(width=82, height=90, x=41, y=200)
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
Master.geometry("1012x615+5+5")
#Master.geometry("986x615+-995+3")
Master.mainloop()
# ----------------------------------------------------------------------------------
#  EOF
# ----------------------------------------------------------------------------------

