from conexion import Conexion
from calculos import Calculos
import threading as Tr
import serial as s
from silla import Silla



def entradaSalida():
    """Esta función actualiza los buffer de entrada del GPS y la Brujula"""
    message = Silla.escribirRecibir(Conexion.bufferSalida)
    if message == 'ok': Conexion.statusProcess = True
    else:
        message = message.split(' ')
        Conexion.bufferGPS = [float(message[0]), float(message[1])]
        Conexion.bufferBrujula = float(message[2])
    Tr.Thread(target = entradaSalida, daemon=True).start()

if __name__ == '__main__':
    Conexion = Conexion()
    Calculos = Calculos()
    Silla = Silla()
    Tr.Thread(target = entradaSalida, daemon=True).start() 
    

