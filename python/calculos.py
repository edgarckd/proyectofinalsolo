import math
import csv

class Calculos:
    def __init__(self) -> None:
        self.rad = math.pi/180
        self.R = 6372.795477598

    def distancia(self,coor1=[], coor2 =[]):
        dlat=coor2[0]-coor1[0]
        dlon=coor2[1]-coor1[1]
        R=6372.795477598
        a=(math.sin(self.rad*dlat/2))**2 + math.cos(self.rad*coor1[0])*math.cos(self.rad*coor2[0])*(math.sin(self.rad*dlon/2))**2
        distancia=2*self.R*math.asin(math.sqrt(a))
        return distancia

    def anguloNorte2Puntos(self, ubicacion=[], Objetivo=[]):
        coor= [Objetivo[0] - ubicacion[0],Objetivo[1] - ubicacion[1]]
        if coor[0] == 0: coor[0] = 0.000000000000000001
        if coor[1] == 0: coor[1] = 0.000000000000000001
        print(coor)
        rad = math.atan2(coor[1],coor[0])
        angulo =   (rad*180)/math.pi
        if angulo < 0 : angulo += 360
        return angulo
    def puntosPorRuta(self, archivo = 'archivo.csv'):
        with open(archivo, newline='') as csvfile:
            reader = list(csv.DictReader(csvfile))
        return len(reader)


if __name__=='__main__':
    pass
    

