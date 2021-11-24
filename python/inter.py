import threading
import time
import serial


s = serial.Serial(port="/dev/ttyACM0", baudrate=115200, timeout=3)
time.sleep(2)
print("ia")
s.write(b'M')
mensaje = s.readline().decode()
print(mensaje)