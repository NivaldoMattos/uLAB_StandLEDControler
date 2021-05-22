# -----------------------------------------------------------------------------------
# A-21: Python COM-Port Explorer P1 - P6
# Dev: N.M.
# Data: 22/10/2020
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


def SendData(DadosTx):
    terminator = 255
    #DadosTx = [channel, rgb_seq, pos, red, green, blue, terminator]
    
    print(len(DadosTx))

    for idx in range(0, len(DadosTx)):
        send_byte(DadosTx[idx])
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


def f1():
    if ulcom.is_open():

        channel = 1
        data_len = 21
        DadosTx = [PREAMB, channel, LED_SEQ_RBG, data_len, STRT_PAY, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
        SendData(DadosTx)
    else:
        ask_to_open_port()


def f2():
    if ulcom.is_open():
        channel = 1
        data_len = 21
        DadosTx = [PREAMB, channel, LED_SEQ_RBG, data_len, STRT_PAY, 0, 10, 2, 50, 6, 1, 100, 0,0, 2, 50, 6, 2, 50, 6, 2, 50, 6, 2, 50, 6]
        SendData(DadosTx)
    else:
        ask_to_open_port()


def f3():
    if ulcom.is_open():
        print("Teste3")
    else:
        ask_to_open_port()


def f4():
    ulcom.OpenCom("COM4", "115200")


def f5():
    global SearchingPorts
    SearchingPorts = True


def f6():
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
            bt_f6["image"] = btf6_close_img
            GetTemperatureFlag = True
            if not receiving_serial.is_alive():
                receiving_serial.start()
    else:
        ulcom.close()
        message.botton('Unconnected!', "red", beep=False)
        bt_f6["image"] = btf6_open_img


# -----------------------------------------------------------------------------------
# Widgets
# -----------------------------------------------------------------------------------
back_img = PhotoImage(file="images/bg_inicial.png")
btf1_img = PhotoImage(file="images/btf1.png")
btf2_img = PhotoImage(file="images/btf2.png")
btf3_img = PhotoImage(file="images/btf3.png")
btf4_img = PhotoImage(file="images/btf4.png")
btf5_img = PhotoImage(file="images/btf5.png")
btf6_close_img = PhotoImage(file="images/btf6_close.png")
btf6_open_img = PhotoImage(file="images/btf6_open.png")

label_fundo = Label(Master, image=back_img)
label_fundo.place(x=0, y=0)

bt_f1 = Button(Master, image=btf1_img, bd=0, command=f1)
bt_f1.place(width=121, height=70, x=23, y=80)

bt_f2 = Button(Master, image=btf2_img, bd=0, command=f2)
bt_f2.place(width=121, height=70, x=151, y=80)

bt_f3 = Button(Master, image=btf3_img, bd=0, command=f3)
bt_f3.place(width=121, height=70, x=279, y=80)

bt_f4 = Button(Master, image=btf4_img, bd=0, command=f4)
bt_f4.place(width=121, height=70, x=407, y=80)

bt_f5 = Button(Master, image=btf5_img, bd=0, command=f5)
bt_f5.place(width=94, height=50, x=45, y=484)

bt_f6 = Button(Master, image=btf6_open_img, bd=0, command=f6)
bt_f6.place(width=94, height=50, x=158, y=484)

port_list = Listbox(Master, height=1, width=7, bd=10, font="Arial 10", bg="black",
                    fg="#008000",
                    highlightcolor="black",
                    highlightthickness=0,
                    selectbackground="black",
                    )

port_list.place(width=83, height=175, x=51, y=285)
port_list.insert(END, "COM5")
port_list.bind('<Double-Button>', lambda e: message.port("green", port_list.get(ANCHOR)))

baud_list = Listbox(Master, height=1, width=7, bd=10, font="Arial 10", bg="black",
                    fg="#008000",
                    highlightcolor="black",
                    highlightthickness=0,
                    selectbackground="black",
                    )

baud_list.place(width=82, height=175, x=163, y=285)
baud_list.insert(END, "9600", "19200", "38400", "57200", "115200", "128000", "256000")
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

LEDs = ulcom.Leds(Master)


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

