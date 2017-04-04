import serial
import time
import os
from xbee import XBee

str1 = 'rf_data'
str2 = ">"

ser=serial.Serial('/dev/ttyUSB0' , 9600, timeout=0.5)
xbee = XBee(ser)


parar=False
leer=False

while True:
    
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
        path="/home/pi/USCO/remoto_suelo/"+remotoID+" /"+variable+".csv"
    elif tipo_archivo=='log':
        path="/home/pi/USCO/remoto_suelo/"+remotoID+" /log.csv"
    
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
        
            
            
        

         
         
