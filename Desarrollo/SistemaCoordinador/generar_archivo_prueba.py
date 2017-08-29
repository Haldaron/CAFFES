import time
import os
"----------------------Fecha y hora de los datos----------------------------"
Fecha=time.strftime("%Y-%m-%d")
Hora=time.strftime("%H:%M:%S")
N_por_hora=10
"---------------Rutas de los archivos a subir-----------------------------------------"

path_brillo_solar_o="/home/pi/USCO/remoto_meteorologico/BrilloSolar.csv"
path_velocidad_viento_o="/home/pi/USCO/remoto_meteorologico/VelocidadViento.csv"
path_direccion_viento_o="/home/pi/USCO/remoto_meteorologico/DireccionViento.csv"
path_temperatura_o="/home/pi/USCO/remoto_meteorologico/TempAmbiente.csv"
path_humedad_o="/home/pi/USCO/remoto_meteorologico/HumedadRelativa.csv"
path_precipitacion_o="/home/pi/USCO/remoto_meteorologico/Precipitacion.csv"
path_humedad_suelo_o='/home/pi/USCO/remoto_suelo/remoto1/Humedad_estadistico.csv'
path_temperatura_suelo_o='/home/pi/USCO/remoto_suelo/remoto1/Temperatura_estadistico.csv'
path_PAR_o='/home/pi/USCO/remoto_meteorologico/PAR.csv'
path_ph_suelo_o='/home/pi/USCO/remoto_suelo/remoto1/ph.csv'
path_ph_tanque_o='/home/pi/USCO/remoto_tanque/ph.csv'
path_temperatura_tanque_o='/home/pi/USCO/remoto_tanque/Temperatura.csv'

"------------------brillo solar------------------------------------"
path_datos=path_brillo_solar_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"W/m2,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------velocidad viento-----------------------------------"
path_datos=path_velocidad_viento_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"m/s,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------direccion viento-----------------------------------"
path_datos=path_direccion_viento_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"Grados,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------temperatura ambiente-----------------------------------"
path_datos=path_temperatura_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"Celsius,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------humedad ambiente-----------------------------------"
path_datos=path_humedad_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"%,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------precipitacion-----------------------------------"
path_datos=path_precipitacion_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"In/h,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------humedad suelo-----------------------------------"
path_datos=path_humedad_suelo_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir="P1,"+Fecha+","+Hora+","+valor+","+"%,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------temperatura suelo----------------------------------"
path_datos=path_temperatura_suelo_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"Celsius,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------PAR-----------------------------------"
path_datos=path_PAR_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"PARios,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------ph suelo-----------------------------------"
path_datos=path_ph_suelo_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"pH,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------ph tanque-----------------------------------"
path_datos=path_ph_tanque_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"pH,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close
"------------------temperatura tanque-----------------------------------"
path_datos=path_temperatura_tanque_o
os.system("chmod 777 %s"%path_datos)
if os.path.exists(path_datos):
    os.remove(path_datos)
for x in range(1, N_por_hora):
    valor=str(x*1000000)
    string_a_escribir=Fecha+","+Hora+","+valor+","+"Celsius,Promedio,Diario"
    archivo=open(path_datos,'a+')
    archivo.write(string_a_escribir)
    archivo.write('\n')
    archivo.close

