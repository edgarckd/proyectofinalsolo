
import serial
from calculos import Calculos
import csv

class Conexion:
    puntosPorRuta          = int
    corrdenadaObjetivo      = [float, float]
    bufferGPS               = [float, float]
    bufferBrujula           = float
    errorDistancia          = float
    _toleranciaDistancia    = float
    errorAngulo             = float
    _toleranciaAngulo       = float 
    rutaActiva              = bool
    puntoObjetivo           = int
    bufferSalida            = bytes
    statusProcess           = bool
    finishRoute             = bool
    def __init__(self,toleranciaDistancia=2.0 ,toleranciaAngulo = 10,rutaActiva = False,puntoObjetivo = 1) -> None:
        #self._puntosPorRuta = puntoPorRuta
        self.puntoObjetivo = puntoObjetivo
        #self.bufferBrujula = bufferBrujula
        #self.bufferBrujula  = bufferBrujula
        #self.errorDistancia = errorDistancia
        self._toleranciaDistancia = toleranciaAngulo
        #self.errorAngulo = errorAngulo
        self._toleranciaAngulo = toleranciaAngulo
        self.rutaActiva = rutaActiva
        self.statusProcess = False
        self.finishRoute = False                
    def puntoInicio(self):
        self.errorDistancia = Calculos.distancia(self.puntoObjetivo, self.bufferGPS)
        if self.errorDistancia <= self._toleranciaDistancia :
            return True
        else:
            return False
    
    def anguloAObjetivo(self):
        angulo = Calculos.anguloNorte2Puntos(self.bufferGPS, self.puntoObjetivo)
        self.errorAngulo = angulo - self.bufferBrujula
        if (self.errorAngulo < 0):
            if abs(self.errorAngulo) > 180 :
                self.errorAngulo += 360
        else:
            if self.errorAngulo > 180:
                self.errorAngulo -= 360 
        return self.errorAngulo

    def distanciaAObjetivo(self):
        self.errorDistancia = Calculos.distancia(self.coordenadaObjetivo, self.bufferGPS)
        return(self.errorDistancia)
    
    def posicionObjetivo(self, archivo='Ruta1.csv'):
        with open(archivo, newline='') as csvfile:
            reader = list(csv.DictReader(csvfile))
        dato = list(filter(lambda r: r['punto'] == str(self.puntoObjetivo), reader) ) 
        dato = dato[0]
        self.corrdenadaObjetivo = [float(dato['lat']), float(dato['log'])]
        int(self.puntoObjetivo)
        self.puntoObjetivo +=1
        if self.puntoObjetivo <= Calculos.puntosPorRuta(archivo):            
            return self.puntoObjetivo-1 , self.corrdenadaObjetivo
        else:
            self.puntoObjetivo -=1
            self.finishRoute = True
            return self.puntoObjetivo , self.corrdenadaObjetivo

    

if __name__=='__main__':
    c = Conexion()
    for i in range(4):
        m =  c.posicionObjetivo('archivo.csv')
        print(m, c.puntoObjetivo, c.finishRoute)