# ----------------------------------------------------------------------------------
# A-17: Mdulo para uso no Python COM-Port Explorer
# Dev: N.M.
# Data: 13/09/2020
# Referncias: uLab Eletrnica
# https://github.com/NivaldoMattos/Curso-de-Python-com-Interface-Grafica
# ----------------------------------------------------------------------------------
import serial
from tkinter import *
import winsound

Port = "COMx"
Baud = "BAUD"

LED_BuiltInState = False
comport = serial.Serial()

# Terminadores para o reconhecimento dos comandos
RGB_TERMINATOR = 255
GET_TEMPERATURE_ON = 254
GET_TEMPERATURE_OFF = 253
LED_BUILTIN_ON = 252
LED_BUILTIN_OFF = 251


# ----------------------------------------------------------------------------------
# Classe para controle dos labels e do beep
# ----------------------------------------------------------------------------------
class Message:
    def __init__(self, master):

        self.label_port = Label(master, text="COMx", font="Arial 10 bold", bg="black", fg="yellow")
        self.label_port.place(width=80, height=18, x=42, y=361)

        self.label_baud = Label(master, text="BAUDx", font="Arial 10 bold", bg="black", fg="yellow")
        self.label_baud.place(width=80, height=18, x=42, y=175)

        self.label_RGB = Label(master, text="---.---.---", font="Arial 20", fg="green", bg="black")
        #self.label_RGB.place(width=194, height=33, x=571, y=112)

        #self.label_temp = Label(master, text="--.--", font="Arial 20", fg="green", bg="black")
        #self.label_temp.place(width=120, height=33, x=808, y=112)

        self.label_message = Label(master, text="Status2:", font="Arial 13", fg="yellow", bg="black")
        self.label_message.place(width=907, height=21, x=37, y=574)

    def port(self, color, port):
        global Port
        Port = port
        self.label_port["fg"] = color
        self.label_port["text"] = port


    def baud(self, color, baud):
        global Baud
        Baud = baud
        self.label_baud["fg"] = color
        self.label_baud["text"] = baud+"Bps"


    def temper(self, temp):
        temp=temp[2:7]
        self.label_temp["text"] = temp + "ºC"

    def rgb(self, r, g, b):
        self.label_RGB["text"] = str(r) + ',' + str(g) + ',' + str(b)


    def botton(self, message, color, beep):
        self.label_message["text"] = message
        self.label_message["fg"] = color
        if beep:
            frequency = 1200
            duration = 200
            winsound.Beep(frequency, duration)


# ----------------------------------------------------------------------------------
# Classe para controle dos LEDs
# ----------------------------------------------------------------------------------
class Leds:
    def __init__(self, master):
        self.label_LED_RX = Label(master, bg="black")
        self.label_LED_RX.place(width=10, height=7, x=606, y=354)

        self.label_LED_TX = Label(master, bg="black")
        self.label_LED_TX.place(width=9, height=6, x=606, y=381)

        self.label_LED_BUILT_IN = Label(master, bg="black")
        self.label_LED_BUILT_IN.place(width=9, height=6, x=606, y=406)

        self.label_LED_RGB = Button(master, bg="black")
        self.label_LED_RGB.place(width=19, height=12, x=653, y=251)

    def LED_L(self, state):
        global LED_BuiltInState
        if state:
            self.label_LED_BUILT_IN["background"] = "light green"
        else:
            self.label_LED_BUILT_IN["background"] = "black"
        LED_BuiltInState = state


    def LED_TX(self, state):
        if state:
            self.label_LED_TX["background"] = "red"
        else:
            self.label_LED_TX["background"] = "black"

    def LED_RX(self, state):
        if state:
            self.label_LED_RX["background"] = "white"
        else:
            self.label_LED_RX["background"] = "black"

    def LED_RGB(self, color):
        self.label_LED_RGB["background"] = color


# ----------------------------------------------------------------------------------
#  Funções para o acesso da porta serial
# ----------------------------------------------------------------------------------
def open():
    global comport, Port, Baud
    if not comport.is_open:
        try:
            comport = serial.Serial(port=Port, baudrate=Baud)
        except IOError:
            comport.close()
            comport.open()


def open():
    global comport, Port, Baud
    if not comport.is_open:
        try:
            comport = serial.Serial(port=Port, baudrate=Baud)
        except IOError:
            comport.close()
            comport.open()


def close():
    global comport
    comport.close()


def is_open():
    global comport
    return comport.is_open


def write_byte(byte):
    if comport.is_open:
        comport.write((byte,))


def read_line():
    return comport.readline()


def reset_input_buffer():
    if comport.is_open:
        comport.reset_input_buffer()

# ----------------------------------------------------------------------------------
# E.O.F
# ----------------------------------------------------------------------------------

