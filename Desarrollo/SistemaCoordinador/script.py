import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cbook as cbook
import os
import time

print "Impresion previa de los datos registrados"

def plotTemp(path,tipo):
	if os.path.exists(path):
		variable=open(path,'r')
		valor=[]
		for line in variable.readlines():
			linea=line.strip().lower()
			index=linea.split(',')
			if index[4]==tipo:
				dato=int(index[2])	
				valor.append(dato) 
		plt.plot(valor)
		plt.title(path+tipo)
		plt.show()
		
	else:
		print "El archivo "+path+" no existe"

def plotHum(path,tipo,prof):
	if os.path.exists(path):
		variable=open(path,'r')
		valor=[]
		for line in variable.readlines():
			linea=line.strip().lower()
			index=linea.split(',')
			if index[0]==prof:
				if index[5]==tipo:
					dato=int(index[3])	
					valor.append(dato) 
		plt.plot(valor)
		plt.title(path+tipo+prof)
		plt.show()
		
	else:
		print "El archivo "+path+" no existe"


plotTemp('./USCO/remoto_suelo/remoto1/Temperatura_estadistico.csv','promedio')
plotTemp('./USCO/remoto_suelo/remoto1/Temperatura_estadistico.csv','maximo')
plotTemp('./USCO/remoto_suelo/remoto1/Temperatura_estadistico.csv','minimo')


plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','promedio','p1')
plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','promedio','p2')
plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','promedio','p3')

plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','maximo','p1')
plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','maximo','p2')
plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','maximo','p3')

plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','minimo','p1')
plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','minimo','p2')
plotHum('./USCO/remoto_suelo/remoto1/Humedad_estadistico.csv','minimo','p3')

plotTemp('./USCO/remoto_meteorologico/PAR.csv','promedio')
plotTemp('./USCO/remoto_meteorologico/PAR.csv','maximo')
plotTemp('./USCO/remoto_meteorologico/PAR.csv','minimo')


