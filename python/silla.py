import serial 
import time
from socket import socket, AF_INET, SOCK_DGRAM
import threading


class Silla:
    #silla = s

    def __init__(self, puerto='/dev/ttyACM0', baudios = 115200) -> None:
        
        try:
            self.silla = serial.Serial(puerto,baudios, timeout=3)
            time.sleep(2)
        except:
            print("no se pudo generar la conexión")
            #exit()
    
    def escribirRecibir(self, bufferSalida, time_out=3):
        if type(bufferSalida)!= bytes : bufferSalida = str(bufferSalida).encode()
        #print(bufferSalida)      
        self.silla.write(bufferSalida)
        
        #inicio = time.time()
        #print(self.silla.in_waiting())
        """while self.silla.in_waiting() & (time.time()-inicio) < timeout :
            print("pruuu")
            time.sleep(0.01)"""
        #while (self.silla.in_waiting()):
        
        ll = self.silla.readline().decode('ascii').strip()
        an = ll
        
        return  ll
    
    def giro(self, errorAngulo):
        message = f'{"B" if errorAngulo >0 else "P"}{abs(errorAngulo) }'.encode('utf-8')
        return message
    
    def caminar(self):
        return b'A'
    def detener(self):
        return b'S'

class aRed:
    direccionIP         = str
    puertoWeb           = int
    socket              = socket
    def __init__(self, direccionIP = 'localhost', puertoWeb = 37777) -> None:
        self.direccionIP    = direccionIP
        self.puertoWeb      = puertoWeb
        self.socket         = socket(AF_INET, SOCK_DGRAM)
    
    def enviarWeb(self, mensaje):
        """Falta corregir el envio a socket. El mensaje son las coordenadas en la version del txt
        como mensaje es una lista en float, se debe acomodar el mensaje de tal forma que se pueda enviar"""
        if type(mensaje) == list:
            mensaje = f'{mensaje[0]}/{mensaje[1]}/2021-05-31 21:37/1/8'.encode('utf-8')
        #if type(mensaje)!= bytes : mensaje = str(mensaje).encode('utf-8')
        self.socket.sendto(mensaje,('localhost', self.puertoWeb))
        #self.socket.recvfrom(8192)
        self.socket.sendto(mensaje,(self.direccionIP, self.puertoWeb))
        #self.socket.recvfrom(8192)

def data(mensaje):
    p = aRed(direccionIP='3.132.246.245')
    p.enviarWeb(mensaje)
    time.sleep(1.5)
    threading.Thread(target=data,args=([345.45,34.566],)).start()

if __name__=='__main__':
    con = Silla()
    print(con.escribirRecibir("M"))


