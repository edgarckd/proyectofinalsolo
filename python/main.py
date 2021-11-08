from conexion import Conexion
from calculos import Calculos
import threading 
import serial as s
from silla import Silla, aRed
import time


def aServer(mensaje):
    aRed.enviarWeb(mensaje)
    time.sleep(1.5)
    threading.Thread(target=aServer,args=(Conexion.bufferGPS,)).start()

def buffers():
    bufferEntrada = Silla.escribirRecibir(Conexion.bufferSalida)
    if bufferEntrada == 'ok':
        Conexion.statusProcess = True
        Conexion.bufferSalida = b'M'
    else:
        bufferEntrada = bufferEntrada.split(' ')
        Conexion.bufferGPS = [float(bufferEntrada[0]),float(bufferEntrada[1])]
        Conexion.bufferBrujula = float(bufferEntrada[2])
    time.sleep(0.1)
    threading.Thread(target=buffers).start()

def SiguientePunto():
    Conexion.posicionObjetivo()
    Conexion.anguloAObjetivo()
    Conexion.distanciaAObjetivo()

def verificador():
    pass

if __name__ == '__main__':
    Conexion = Conexion()
    Calculos = Calculos()
    Silla = Silla()
    aRed = aRed(direccionIP='3.132.246.245')
    threading.Thread(target=aServer,args=(Conexion.bufferGPS,)).start()
    threading.Thread(target=buffers).start()
    
    """ ¿Estoy en el punto de inicio?"""
    while Conexion.puntoInicio == False:
        print(f'Por favor acerquese al punto de inicio de la ruta')
    
    """Ir a la Ruta siguiente"""
      