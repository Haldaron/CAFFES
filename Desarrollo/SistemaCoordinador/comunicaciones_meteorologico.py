import os 
import time

device="/dev/ttyUSB1"
contador=0
offset_RadiacionSolar=14
offset_VelocidadViento=6
offset_DireccionViento=8
offset_Temperatura=5
offset_Humedad=10
offset_Precipitacion=11
Fecha_Hora=time.strftime("%Y-%m-%d,%H:%M:%S")
print(Fecha_Hora)


while True:
    if (contador % 7)==0:
        Fecha_Hora=time.strftime("%Y-%m-%d,%H:%M:%S")
        if os.path.isfile('/home/pi/vproweather-1.1/rtwdata.txt'):
            os.system("rm /home/pi/vproweather-1.1/rtwdata.txt")
        os.system("cd /home/pi/vproweather-1.1")
        os.system("./vproweather --get-realtime %s > /home/pi/vproweather-1.1/rtwdata.txt" %device)
        file=open('/home/pi/vproweather-1.1/rtwdata.txt', 'r')
        lineas=file.readlines()
        "--------------------------Radiacion Solar--------------------------"
        linea_RadiacionSolar=lineas[offset_RadiacionSolar]
        temp1=linea_RadiacionSolar.find("=")+2
        temp2=linea_RadiacionSolar.find("\n")
        valor_RadiacionSolar=linea_RadiacionSolar[temp1:temp2]
        path_brillo_solar="/home/pi/USCO/remoto_meteorologico/BrilloSolar_recurrente.csv"
        archivo=open(path_brillo_solar,'a')
        archivo.write(Fecha_Hora+">"+valor_RadiacionSolar)
        archivo.write('\n')
        archivo.close
        "--------------------------Direccion Viento--------------------------"
        linea_DireccionViento=lineas[offset_DireccionViento]
        temp1=linea_DireccionViento.find("=")+2
        temp2=linea_DireccionViento.find("\n")
        valor_DireccionViento=linea_DireccionViento[temp1:temp2]
        path_direccion_viento="/home/pi/USCO/remoto_meteorologico/DireccionViento_recurrente.csv"
        archivo=open(path_direccion_viento,'a')
        archivo.write(Fecha_Hora+">"+valor_DireccionViento)
        archivo.write('\n')
        archivo.close
        "--------------------------Velocidad Viento--------------------------"
        linea_VelocidadViento=lineas[offset_VelocidadViento]
        temp1=linea_VelocidadViento.find("=")+2
        temp2=linea_VelocidadViento.find("\n")
        valor_VelocidadViento=linea_VelocidadViento[temp1:temp2]
        path_velocidad_viento="/home/pi/USCO/remoto_meteorologico/VelocidadViento_recurrente.csv"
        archivo=open(path_velocidad_viento,'a')
        archivo.write(Fecha_Hora+">"+valor_VelocidadViento)
        archivo.write('\n')
        archivo.close
    if (contador % 45)==0:
        "--------------------------Temperatura--------------------------"
        linea_Temperatura=lineas[offset_Temperatura]
        temp1=linea_Temperatura.find("=")+2
        temp2=linea_Temperatura.find("\n")
        valor_Temperatura=linea_Temperatura[temp1:temp2]
        path_temperatura="/home/pi/USCO/remoto_meteorologico/Temperatura_recurrente.csv"
        archivo=open(path_temperatura,'a')
        archivo.write(Fecha_Hora+">"+valor_Temperatura)
        archivo.write('\n')
        archivo.close
        "--------------------------Humedad--------------------------"
        linea_Humedad=lineas[offset_Humedad]
        temp1=linea_Humedad.find("=")+2
        temp2=linea_Humedad.find("\n")
        valor_Humedad=linea_Humedad[temp1:temp2]
        path_Humedad="/home/pi/USCO/remoto_meteorologico/Humedad_recurrente.csv"
        archivo=open(path_Humedad,'a')
        archivo.write(Fecha_Hora+">"+valor_Humedad)
        archivo.write('\n')
        archivo.close
    if (contador % 650)==0:
        "--------------------------Precipitacion--------------------------"
        linea_Precipitacion=lineas[offset_Precipitacion]
        temp1=linea_Precipitacion.find("=")+2
        temp2=linea_Precipitacion.find("\n")
        valor_Precipitacion=linea_Precipitacion[temp1:temp2]
        path_Precipitacion="/home/pi/USCO/remoto_meteorologico/Precipitacion_recurrente.csv"
        archivo=open(path_Precipitacion,'a')
        archivo.write(Fecha_Hora+">"+valor_Precipitacion)
        archivo.write('\n')
        archivo.close
    if (contador==2800):
        os.remove(path_brillo_solar)
        os.remove(path_direccion_viento)
        os.remove(path_velocidad_viento)
        os.remove(path_temperatura)
        os.remove(path_Humedad)
        os.remove(path_Precipitacion)
        contador=1
        print(Fecha_Hora)
        
        
        
        
            
                
            
        
    
        
    contador=contador+1
    time.sleep(1)
    
