import serial
import time
import os
from xbee import XBee

str1 = 'rf_data'
str2 = ">"
HoraLimite="59"
contador=0
path_humedad_1='/home/pi/USCO/remoto_suelo/remoto1/Humedad1.csv'
path_humedad_2='/home/pi/USCO/remoto_suelo/remoto1/Humedad2.csv'
path_humedad_3='/home/pi/USCO/remoto_suelo/remoto1/Humedad3.csv'
path_temperatura='/home/pi/USCO/remoto_suelo/remoto1/Temperatura.csv'
path_PAR='/home/pi/USCO/remoto_suelo/remoto1/PAR.csv'


ser=serial.Serial('/dev/ttyUSB0' , 9600, timeout=0.5)
xbee = XBee(ser)


parar=False
leer=False

while True:
    Hora=time.strftime("%M")
    raw_incoming =xbee.wait_read_frame()
    print raw_incoming
    incoming = raw_incoming[str1]
    
    
    
    posicion0=incoming.find(str2)
    posicion1=incoming[posicion0+1:len(incoming)].find(str2)
    posicion1=posicion1+posicion0+1
    posicion2=incoming[posicion1+1:len(incoming)].find(str2)
    posicion2=posicion2+posicion1+1
    posicion3=incoming[posicion2+1:len(incoming)].find(str2)
    posicion3=posicion3+posicion2+1
    posicion4=len(incoming)

    tipo=incoming[0:posicion0]
    remotoID=incoming[posicion0+1:posicion1]
    accion=incoming[posicion1+1:posicion2]
    tipo_archivo=incoming[posicion2+1:posicion3]
    variable=incoming[posicion3+1:posicion4]
    """print 'received data: '+incoming"""

    if tipo_archivo=='var':
        path="/home/pi/USCO/remoto_suelo/"+remotoID+"/"+variable+".csv"
    elif tipo_archivo=='log':
        path="/home/pi/USCO/remoto_suelo/"+remotoID+"/log.csv"
    
    if accion=='stop':
        parar=True
    elif accion=='transmitir':
        leer=True
    elif accion!='transmitir' and accion!='stop' and incoming!='':
        parar=False
        leer=True
    else:
        parar=False
        leer=False
    if leer==True and parar==False:
        if tipo=="d":
            print 'received data: '+incoming
            archivo=open(path,'a')
            archivo.write(incoming[posicion0+1:posicion4])
            archivo.write('\n')
            archivo.close
    if (Hora==HoraLimite):
        if os.path.exists(path_humedad_1):
            os.remove(path_humedad_1)
        if os.path.exists(path_humedad_2):
            os.remove(path_humedad_2)
        if os.path.exists(path_humedad_3):
            os.remove(path_humedad_3)
        if os.path.exists(path_temperatura):
            os.remove(path_temperatura)
        if os.path.exists(path_PAR):
            os.remove(path_PAR)
            
            
        

         
         
