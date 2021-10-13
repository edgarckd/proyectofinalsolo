import csv
with open('ruta1.csv', newline='') as File:  
    reader = csv.reader(File)
    rut = list()
    for row in reader:
        rut.append((float(row[0]), float(row[1])))
