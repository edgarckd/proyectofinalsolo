import threading
import time
from calculos import Calculos
def funcion_1 ():
    global var
    for i in range(5):
        time.sleep(5)
        print(f'ejecuciónn numero {i} {"vamos ganando"if var else "vamos perdiendo"}')
        if (var==True): 
            var=False
        else: 
            var=True

def funcion_2():
    for x in range(7):
              
        time.sleep(6)
        print(f'ejecucion {"final" if var  else f"numero {x}" }')

def main():
    for x in range(6):
        print(f'bloqueando {x}')
        time.sleep(0.5)

def doit(stop_event, arg):
    while stop_event.wait(1) == True:
        time.sleep(1)
        print ("working on %s" % arg)
    print("Stopping as you wish.")


def main():
    pill2kill = threading.Event()
    t = threading.Thread(target=doit, args=(pill2kill, "task"))
    t.start()
    pill2kill.set()
    time.sleep(5)
    pill2kill.clear()
    t.join()
    


if __name__=='__main__':
    '''var = True
    a = threading.Thread(group = None, target=funcion_1, daemon=False)
    b = threading.Thread(group = None, target=funcion_2, daemon=False)
    c = threading.Thread(target=main)
    a.start()
    b.start()
    time.sleep(8)
    c.start() '''

   
    punto1 = [10.924653, -74.782071]
    punto2 = [10.924830, -74.782128]
    #print(p.distancia(punto1,punto2))
    print(Calculos.anguloNorte2Puntos(punto2,punto1))