import serial        
import time
archivo = "ruta1.csv"
csv = open(archivo, 'w')
#titulo = "latitud, longitud \n"
#csv.write(titulo)
serialArduino = serial.Serial("/dev/ttyACM1",115200,timeout=1.0)
for i in range(6):
   
    #timeout (1 segundo) o tiempo máximo de espera para una lectura.
    time.sleep(1) # espera 1 seg, para dar tiempoa conectarse
    serialArduino.write(b'a')
    for i in range(3):
        #cad =serialArduino.readline().decode('ascii')

        cad =serialArduino.readline().decode('ascii').strip()
       
        if ( cad != ''):
            ll = cad

    ll = ll.split(' ')
    lat = ll[0]
    log = ll[1]
    lat = float(lat)
    log = float(log)
    dato = "{0},{1}\n".format(lat, log)
    csv.write(dato)
    