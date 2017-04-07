import os
import shutil
import time
import statistics

str1=">"
Fecha_Hora=time.strftime("%Y-%m-%d,%H:%M:%S")
cifras_significativas=3

"---------------------------------ORIGINALES-----------------------------------------------------"
path_brillo_solar_o="/home/pi/USCO/remoto_meteorologico/BrilloSolar.csv"
path_velocidad_viento_o="/home/pi/USCO/remoto_meteorologico/VelocidadViento.csv"
path_direccion_viento_o="/home/pi/USCO/remoto_meteorologico/DireccionViento.csv"
path_temperatura_o="/home/pi/USCO/remoto_meteorologico/TempAmbiente.csv"
path_humedad_o="/home/pi/USCO/remoto_meteorologico/HumedadRelativa.csv"
path_precipitacion_o="/home/pi/USCO/remoto_meteorologico/Precipitacion.csv"

"---------------------------------ORIGINALES RECURRENTES-----------------------------------------------------"
path_brillo_solar="/home/pi/USCO/remoto_meteorologico/BrilloSolar_recurrente.csv"
path_velocidad_viento="/home/pi/USCO/remoto_meteorologico/VelocidadViento_recurrente.csv"
path_direccion_viento="/home/pi/USCO/remoto_meteorologico/DireccionViento_recurrente.csv"
path_temperatura="/home/pi/USCO/remoto_meteorologico/Temperatura_recurrente.csv"
path_humedad="/home/pi/USCO/remoto_meteorologico/Humedad_recurrente.csv"
path_precipitacion="/home/pi/USCO/remoto_meteorologico/Precipitacion_recurrente.csv"

"--------------------------------COPIAS----------------------------------------------------------"

copia_path_brillo_solar="/home/pi/USCO/remoto_meteorologico/copia_BrilloSolar_recurrente.csv"
copia_path_velocidad_viento="/home/pi/USCO/remoto_meteorologico/copia_VelocidadViento_recurrente.csv"
copia_path_direccion_viento="/home/pi/USCO/remoto_meteorologico/copia_DireccionViento_recurrente.csv"
copia_path_temperatura="/home/pi/USCO/remoto_meteorologico/copia_Temperatura_recurrente.csv"
copia_path_humedad="/home/pi/USCO/remoto_meteorologico/copia_Humedad_recurrente.csv"
copia_path_precipitacion="/home/pi/USCO/remoto_meteorologico/copia_Precipitacion_recurrente.csv"

"-----------------------SE COPIAN LOS ARCHIVOS RECURRENTES----------------------------------------"

shutil.copy(path_brillo_solar,copia_path_brillo_solar)
shutil.copy(path_velocidad_viento,copia_path_velocidad_viento)
shutil.copy(path_direccion_viento,copia_path_direccion_viento)
shutil.copy(path_temperatura,copia_path_temperatura)
shutil.copy(path_humedad,copia_path_humedad)
shutil.copy(path_precipitacion,copia_path_precipitacion)

"------------------------Brillo Solar------------------------------------------------------------"

file_brillo_solar=open(copia_path_brillo_solar,'r')
valor_brillo_solar=[]

for line in file_brillo_solar.readlines():
    linea=line.strip().lower()
    indice=linea.find(str1)
    valor_brillo_solar.append(float(linea[indice+1:len(linea)]))
    
valor_brillo_solar_promedio=round(sum(valor_brillo_solar)/float(len(valor_brillo_solar)),cifras_significativas)
Unidades='W/m2'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_a_escribir=Fecha_Hora+","+str(valor_brillo_solar_promedio)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_brillo_solar=open(path_brillo_solar_o,'a')
file_original_brillo_solar.write(string_a_escribir)
file_original_brillo_solar.close()
            
"-----------------------Velocidad Viento-----------------------------------------------------------------------------"

file_velocidad_viento=open(copia_path_velocidad_viento,'r')
valor_velocidad_viento=[]
fecha_hora_velocidad_viento=[]

for line in file_velocidad_viento.readlines():
    linea=line.strip().lower()
    indice=linea.find(str1)
    valor_velocidad_viento.append(float(linea[indice+1:len(linea)]))
    fecha_hora_velocidad_viento.append(linea[0:indice-1])
valor_velocidad_viento_promedio=round(sum(valor_velocidad_viento)/float(len(valor_velocidad_viento)),cifras_significativas)
valor_velocidad_viento_maximo=max(valor_velocidad_viento)
indice_maximo=valor_velocidad_viento.index(max(valor_velocidad_viento))
Fecha_Hora_max=fecha_hora_velocidad_viento[indice_maximo]
Unidades='MPH'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_a_escribir_promedio=Fecha_Hora+","+str(valor_velocidad_viento_promedio)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_a_escribir_maximo=Fecha_Hora_max+","+str(valor_velocidad_viento_maximo)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_velocidad_viento=open(path_velocidad_viento_o,'a')
file_original_velocidad_viento.write(string_a_escribir_promedio)
file_original_velocidad_viento.write(string_a_escribir_maximo)
file_original_velocidad_viento.close()

"-----------------------Direccion Viento-----------------------------------------------------------------------------"

file_direccion_viento=open(copia_path_direccion_viento,'r')
valor_direccion_viento=[]

for line in file_direccion_viento.readlines():
    linea=line.strip().lower()
    indice=linea.find(str1)
    valor_direccion_viento.append(float(linea[indice+1:len(linea)]))
valor_direccion_viento_promedio=round(sum(valor_direccion_viento)/float(len(valor_direccion_viento)),cifras_significativas)
valor_direccion_viento_desviacion=round(statistics.stdev(valor_direccion_viento),cifras_significativas)
Unidades='Grados'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_a_escribir_promedio=Fecha_Hora+","+str(valor_direccion_viento_promedio)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='DesviacionEstandar'
string_a_escribir_desviacion=Fecha_Hora+","+str(valor_direccion_viento_desviacion)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_direccion_viento=open(path_direccion_viento_o,'a')
file_original_direccion_viento.write(string_a_escribir_promedio)
file_original_direccion_viento.write(string_a_escribir_desviacion)
file_original_direccion_viento.close()

"------------------------------Temperatura----------------------------------------------------------------------------------------------"

file_temperatura=open(copia_path_temperatura,'r')
valor_temperatura=[]
fecha_hora_temperatura=[]

for line in file_temperatura.readlines():
    linea=line.strip().lower()
    indice=linea.find(str1)
    valor_temperatura.append(float(linea[indice+1:len(linea)]))
    fecha_hora_temperatura.append(linea[0:indice-1])
valor_temperatura_promedio=sum(valor_temperatura)/float(len(valor_temperatura))
valor_temperatura_promedio=round((valor_temperatura_promedio-32)*5/9,cifras_significativas)
valor_temperatura_maximo=max(valor_temperatura)
indice_maximo=valor_temperatura.index(valor_temperatura_maximo)
valor_temperatura_maximo=round((valor_temperatura_maximo-32)*5/9,cifras_significativas)
valor_temperatura_minimo=min(valor_temperatura)
indice_minimo=valor_temperatura.index(valor_temperatura_minimo)
valor_temperatura_minimo=round((valor_temperatura_minimo-32)*5/9,cifras_significativas)
Fecha_Hora_max=fecha_hora_temperatura[indice_maximo]
Fecha_Hora_min=fecha_hora_temperatura[indice_minimo]
Unidades='GradosCentigrados'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_a_escribir_promedio=Fecha_Hora+","+str(valor_temperatura_promedio)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_a_escribir_max=Fecha_Hora_max+","+str(valor_temperatura_maximo)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Minimo'
string_a_escribir_min=Fecha_Hora_min+","+str(valor_temperatura_minimo)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_temperatura=open(path_temperatura_o,'a')
file_original_temperatura.write(string_a_escribir_promedio)
file_original_temperatura.write(string_a_escribir_max)
file_original_temperatura.write(string_a_escribir_min)
file_original_temperatura.close()

"------------------------------Humedad----------------------------------------------------------------------------------------------"

file_humedad=open(copia_path_humedad,'r')
valor_humedad=[]
fecha_hora_humedad=[]

for line in file_humedad.readlines():
    linea=line.strip().lower()
    indice=linea.find(str1)
    valor_humedad.append(float(linea[indice+1:len(linea)]))
    fecha_hora_humedad.append(linea[0:indice-1])
valor_humedad_promedio=round(sum(valor_humedad)/float(len(valor_humedad)),cifras_significativas)
valor_humedad_maximo=max(valor_humedad)
valor_humedad_minimo=min(valor_humedad)
indice_maximo=valor_humedad.index(valor_humedad_maximo)
indice_minimo=valor_humedad.index(valor_humedad_minimo)
Fecha_Hora_max=fecha_hora_humedad[indice_maximo]
Fecha_Hora_min=fecha_hora_humedad[indice_minimo]
Unidades='%'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_a_escribir_promedio=Fecha_Hora+","+str(valor_humedad_promedio)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_a_escribir_max=Fecha_Hora_max+","+str(valor_humedad_maximo)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Minimo'
string_a_escribir_min=Fecha_Hora_min+","+str(valor_humedad_minimo)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_humedad=open(path_humedad_o,'a')
file_original_humedad.write(string_a_escribir_promedio)
file_original_humedad.write(string_a_escribir_max)
file_original_humedad.write(string_a_escribir_min)
file_original_humedad.close()

"------------------------Precipitacion------------------------------------------------------------"

file_precipitacion=open(copia_path_precipitacion,'r')
valor_precipitacion=[]

for line in file_precipitacion.readlines():
    linea=line.strip().lower()
    indice=linea.find(str1)
    valor_precipitacion.append(float(linea[indice+1:len(linea)]))
    
valor_precipitacion_promedio=round(sum(valor_precipitacion)/float(len(valor_precipitacion)),cifras_significativas)
Unidades='mm/H'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_a_escribir=Fecha_Hora+","+str(valor_precipitacion_promedio)+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_precipitacion=open(path_precipitacion_o,'a')
file_original_precipitacion.write(string_a_escribir)
file_original_precipitacion.close()


"-----------------------SE BORRAN LAS COPIAS-----------------------------------------------------"
os.remove(copia_path_brillo_solar)
os.remove(copia_path_velocidad_viento)
os.remove(copia_path_direccion_viento)
os.remove(copia_path_temperatura)
os.remove(copia_path_humedad)
os.remove(copia_path_precipitacion)
