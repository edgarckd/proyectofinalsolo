
import serial as s
import time
class Silla:
    silla = s

    def __init__(self, puerto= '/dev/ttyACM0', baudios = 115200) -> None:
        try:
            self.silla = s.Serial(puerto,baudios,timeout=1)
        except:
            print("no se pudo generar la conexión")
            #exit()
    
    def escribirRecibir(self, bufferSalida, timeout=30):
        if type(bufferSalida)!= bytes : bufferSalida = str(bufferSalida).encode('utf-8')      
        self.silla.write(bufferSalida)
        ll = ' '
        inicio = time.time()
        while self.silla.in_waiting() == 0 & (time.time()-inicio) < timeout:
            time.sleep(0.01)
        while (self.silla.in_waiting()!=0):
            ll = ll + self.silla.readline().decode('ascii').strip()
        return  ll
    def giro(self, errorAngulo):
        message = f'{"B" if errorAngulo >0 else "P"}{abs(errorAngulo) }'.encode('utf-8')
        return message
    
    def caminar(self):
        return b'A'
    def detener(self):
        return b'S'


if __name__=='__main__':
    p = Silla()
    print(p.giro(-75.89))