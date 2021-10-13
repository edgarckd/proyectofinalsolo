import sys
import io
import folium # pip install folium
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout
from PyQt5.QtWebEngineWidgets import QWebEngineView # pip install PyQtWebEngine
import serial        
import time
import csv
"""
Folium in PyQt5
"""

rt = (0,0)
class MyApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Folium in PyQt Example')
        self.window_width, self.window_height = 1300, 700
        self.setMinimumSize(self.window_width, self.window_height)

        layout = QVBoxLayout()
        self.setLayout(layout)
        
        '''
        serialArduino = serial.Serial("/dev/ttyACM0",115200,timeout=1.0)
        #timeout (1 segundo) o tiempo máximo de espera para una lectura.
        time.sleep(1) # espera 1 seg, para dar tiempoa conectarse
        serialArduino.write(b'a')
        for i in range(3):
            #cad =serialArduino.readline().decode('ascii') 
            cad = serialArduino.readline().decode('ascii').strip()
            if cad:         
                pos=cad.index(":")
                label=cad[:pos]
                value=cad[pos+1:]
                if label == 'dis':
                    print("Es val de la distancia es: {}".format(value))
                if label == 'pot':
                    print("Es valor del potenciometro es: {}".format(value))     
                print("**************")
            
            if ( cad != ''):
                ll = cad
            #serialArduino.close()
        ll = ll.split(' ')
        lat = ll[0]
        log = ll[1]
        lat = float(lat)
        log = float(log)
        ''' 
        

        coordinate = (11.019521, -74.851585)
        m = folium.Map(coordinate)
        location=coordinate,
        zoom_start=18,
        tiles='https://tiles.wmflabs.org/hikebike/{z}/{x}/{y}.png',
        attr='Mapbox attribution'
        
        with open('ruta1.csv', newline='') as File:  
            
            reader = csv.reader(File)
            rut = list()
            for row in reader:
                rut.append((float(row[0]), float(row[1])))
        '''
        marcador = folium.PolyLine(rut, smooth_factor=(2), popup="Ruta: Entrada - Bloque K") 
        marcador.add_to(m)
        '''
        
        
        mar = folium.Marker(rt, tooltip="Inicio")
        mar.add_to(m)   
        
        # save map data to data object
        data = io.BytesIO()
        m.save(data, close_file=False)
        webView = QWebEngineView()
        webView.setHtml(data.getvalue().decode())
        layout.addWidget(webView)

if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    app.setStyleSheet('''
        QWidget {
            font-size: 35px;
        }
    ''')

    myApp = MyApp()
    
    myApp.show()
    
    try:
        sys.exit(app.exec_())
    except SystemExit:
        print('Closing Window...')