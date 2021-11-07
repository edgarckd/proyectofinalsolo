import time
import threading
class pp:
    variableA = str
    variableB = float
    variableC = int
    def __init__(self) -> None:
        self.variableA = 'maluco'
        self.variableB = 324.55
        self.variableC = 324

def suma(variable):
    for i in range(7):
        variable +=1
        p.variableB = variable
        time.sleep(1)

def cuadrado(variable):
    for i in range(4):
        variable = variable**2
        p.variableC = variable
        time.sleep(1)

if __name__ == '__main__':
    p = pp()
    print(p.variableB,' ', p.variableC,' ', p.variableA)
    threading.Thread(target= suma, args=(8,)).start()
    threading.Thread(target= cuadrado, args=(2,)).start()
    for i in range(4):
        print(p.variableB,' ', p.variableC,' ', p.variableA)
        time.sleep(1)