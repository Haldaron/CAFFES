import os
import shutil
import time
import math
import statistics

str1=">"
Fecha_Hora=time.strftime("%Y-%m-%d,%H:%M:%S")
cifras_significativas_1=9
cifras_significativas=3
path_tipo_finca='/home/pi/USCO/administrativo/tipo_finca.txt'
file_tipo_finca=open(path_tipo_finca,'r')
for line in file_tipo_finca.readlines():
    tipo_finca=line.strip().lower()


"---------------------------------ORIGINALES-----------------------------------------------------"
path_brillo_solar_o="/home/pi/USCO/remoto_meteorologico/BrilloSolar.csv"
path_velocidad_viento_o="/home/pi/USCO/remoto_meteorologico/VelocidadViento.csv"
path_direccion_viento_o="/home/pi/USCO/remoto_meteorologico/DireccionViento.csv"
path_temperatura_o="/home/pi/USCO/remoto_meteorologico/TempAmbiente.csv"
path_humedad_o="/home/pi/USCO/remoto_meteorologico/HumedadRelativa.csv"
path_precipitacion_o="/home/pi/USCO/remoto_meteorologico/Precipitacion.csv"
path_humedad_suelo_o='/home/pi/USCO/remoto_suelo/remoto1/Humedad_estadistico.csv'
path_temperatura_suelo_o='/home/pi/USCO/remoto_suelo/remoto1/Temperatura_estadistico.csv'
path_PAR_o='/home/pi/USCO/remoto_meteorologico/PAR.csv'

"---------------------------------ORIGINALES RECURRENTES-----------------------------------------------------"
path_brillo_solar="/home/pi/USCO/remoto_meteorologico/BrilloSolar_recurrente.csv"
path_velocidad_viento="/home/pi/USCO/remoto_meteorologico/VelocidadViento_recurrente.csv"
path_direccion_viento="/home/pi/USCO/remoto_meteorologico/DireccionViento_recurrente.csv"
path_temperatura="/home/pi/USCO/remoto_meteorologico/Temperatura_recurrente.csv"
path_humedad="/home/pi/USCO/remoto_meteorologico/Humedad_recurrente.csv"
path_precipitacion="/home/pi/USCO/remoto_meteorologico/Precipitacion_recurrente.csv"
path_humedad_suelo_1='/home/pi/USCO/remoto_suelo/remoto1/Humedad1.csv'
path_humedad_suelo_2='/home/pi/USCO/remoto_suelo/remoto1/Humedad2.csv'
path_humedad_suelo_3='/home/pi/USCO/remoto_suelo/remoto1/Humedad3.csv'
path_temperatura_suelo='/home/pi/USCO/remoto_suelo/remoto1/Temperatura.csv'
path_PAR_suelo='/home/pi/USCO/remoto_suelo/remoto1/PAR.csv'

"--------------------------------COPIAS----------------------------------------------------------"

copia_path_brillo_solar="/home/pi/USCO/remoto_meteorologico/copia_BrilloSolar_recurrente.csv"
copia_path_velocidad_viento="/home/pi/USCO/remoto_meteorologico/copia_VelocidadViento_recurrente.csv"
copia_path_direccion_viento="/home/pi/USCO/remoto_meteorologico/copia_DireccionViento_recurrente.csv"
copia_path_temperatura="/home/pi/USCO/remoto_meteorologico/copia_Temperatura_recurrente.csv"
copia_path_humedad="/home/pi/USCO/remoto_meteorologico/copia_Humedad_recurrente.csv"
copia_path_precipitacion="/home/pi/USCO/remoto_meteorologico/copia_Precipitacion_recurrente.csv"
copia_path_humedad_suelo_1='/home/pi/USCO/remoto_suelo/remoto1/copia_Humedad1.csv'
copia_path_humedad_suelo_2='/home/pi/USCO/remoto_suelo/remoto1/copia_Humedad2.csv'
copia_path_humedad_suelo_3='/home/pi/USCO/remoto_suelo/remoto1/copia_Humedad3.csv'
copia_path_temperatura_suelo='/home/pi/USCO/remoto_suelo/remoto1/copia_Temperatura.csv'
copia_path_PAR_suelo='/home/pi/USCO/remoto_suelo/remoto1/copia_PAR.csv'

"-----------------------SE COPIAN LOS ARCHIVOS RECURRENTES----------------------------------------"

if tipo_finca=='si':
    
    shutil.copy(path_brillo_solar,copia_path_brillo_solar)
    shutil.copy(path_velocidad_viento,copia_path_velocidad_viento)
    shutil.copy(path_direccion_viento,copia_path_direccion_viento)
    shutil.copy(path_temperatura,copia_path_temperatura)
    shutil.copy(path_humedad,copia_path_humedad)
    shutil.copy(path_precipitacion,copia_path_precipitacion)
    shutil.copy(path_PAR_suelo,copia_path_PAR_suelo)
    
shutil.copy(path_humedad_suelo_1,copia_path_humedad_suelo_1)
shutil.copy(path_humedad_suelo_2,copia_path_humedad_suelo_2)
shutil.copy(path_humedad_suelo_3,copia_path_humedad_suelo_3)
shutil.copy(path_temperatura_suelo,copia_path_temperatura_suelo)


"------------------------Brillo Solar------------------------------------------------------------"
if tipo_finca=='si':
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
    Unidades='Celsius'
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

    "------------------------------PAR----------------------------------------------------------------------------------------------"

    file_PAR_suelo=open(copia_path_PAR_suelo,'r')
    valor_PAR_suelo=[]


    for line in file_PAR_suelo.readlines():
        linea=line.strip().lower()
        valor_PAR_suelo.append(float(linea))
    valor_PAR_suelo_promedio=math.floor(round(sum(valor_PAR_suelo)/float(len(valor_PAR_suelo)),cifras_significativas_1))
    valor_PAR_suelo_maximo=max(valor_PAR_suelo)
    valor_PAR_suelo_minimo=min(valor_PAR_suelo)
    Unidades='PARios'
    Tipo_valor='Promedio'
    Periodicidad='Horario'
    string_temp=str(valor_PAR_suelo_promedio)
    string_temp=string_temp.replace(',','')
    string_a_escribir_promedio=Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
    Tipo_valor='Maximo'
    string_temp=str(valor_PAR_suelo_maximo)
    string_temp=string_temp.replace(',','')
    string_a_escribir_max=Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
    Tipo_valor='Minimo'
    string_temp=str(valor_PAR_suelo_minimo)
    string_temp=string_temp.replace(',','')
    string_a_escribir_min=Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
    file_original_humedad=open(path_PAR_o,'a')
    file_original_humedad.write(string_a_escribir_promedio)
    file_original_humedad.write(string_a_escribir_max)
    file_original_humedad.write(string_a_escribir_min)
    file_original_humedad.close()

"------------------------------Humedad_suelo_1----------------------------------------------------------------------------------------------"

file_humedad_suelo_1=open(copia_path_humedad_suelo_1,'r')
valor_humedad_suelo_1=[]


for line in file_humedad_suelo_1.readlines():
    linea=line.strip().lower()
    valor_humedad_suelo_1.append(float(linea))
valor_humedad_suelo_1_promedio=math.floor(round(sum(valor_humedad_suelo_1)/float(len(valor_humedad_suelo_1)),cifras_significativas_1))
valor_humedad_suelo_1_maximo=max(valor_humedad_suelo_1)
valor_humedad_suelo_1_minimo=min(valor_humedad_suelo_1)
Unidades='%'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_temp=str(valor_humedad_suelo_1_promedio)
string_temp=string_temp.replace(',','')
string_a_escribir_promedio="P1,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_temp=str(valor_humedad_suelo_1_maximo)
string_temp=string_temp.replace(',','')
string_a_escribir_max="P1,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Minimo'
string_temp=str(valor_humedad_suelo_1_minimo)
string_temp=string_temp.replace(',','')
string_a_escribir_min="P1,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_humedad=open(path_humedad_suelo_o,'a')
file_original_humedad.write(string_a_escribir_promedio)
file_original_humedad.write(string_a_escribir_max)
file_original_humedad.write(string_a_escribir_min)
file_original_humedad.close()

"------------------------------Humedad_suelo_2----------------------------------------------------------------------------------------------"

file_humedad_suelo_2=open(copia_path_humedad_suelo_2,'r')
valor_humedad_suelo_2=[]


for line in file_humedad_suelo_2.readlines():
    linea=line.strip().lower()
    valor_humedad_suelo_2.append(float(linea))
valor_humedad_suelo_2_promedio=math.floor(round(sum(valor_humedad_suelo_2)/float(len(valor_humedad_suelo_2)),cifras_significativas_1))
valor_humedad_suelo_2_maximo=max(valor_humedad_suelo_2)
valor_humedad_suelo_2_minimo=min(valor_humedad_suelo_2)
Unidades='%'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_temp=str(valor_humedad_suelo_2_promedio)
string_temp=string_temp.replace(',','')
string_a_escribir_promedio="P2,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_temp=str(valor_humedad_suelo_2_maximo)
string_temp=string_temp.replace(',','')
string_a_escribir_max="P2,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Minimo'
string_temp=str(valor_humedad_suelo_2_minimo)
string_temp=string_temp.replace(',','')
string_a_escribir_min="P2,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_humedad=open(path_humedad_suelo_o,'a')
file_original_humedad.write(string_a_escribir_promedio)
file_original_humedad.write(string_a_escribir_max)
file_original_humedad.write(string_a_escribir_min)
file_original_humedad.close()

"------------------------------Humedad_suelo_3----------------------------------------------------------------------------------------------"

file_humedad_suelo_3=open(copia_path_humedad_suelo_3,'r')
valor_humedad_suelo_3=[]


for line in file_humedad_suelo_3.readlines():
    linea=line.strip().lower()
    valor_humedad_suelo_3.append(float(linea))
valor_humedad_suelo_3_promedio=math.floor(round(sum(valor_humedad_suelo_3)/float(len(valor_humedad_suelo_3)),cifras_significativas_1))
valor_humedad_suelo_3_maximo=max(valor_humedad_suelo_3)
valor_humedad_suelo_3_minimo=min(valor_humedad_suelo_3)
Unidades='%'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_temp=str(valor_humedad_suelo_3_promedio)
string_temp=string_temp.replace(',','')
string_a_escribir_promedio="P3,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_temp=str(valor_humedad_suelo_3_maximo)
string_temp=string_temp.replace(',','')
string_a_escribir_max="P3,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Minimo'
string_temp=str(valor_humedad_suelo_3_minimo)
string_temp=string_temp.replace(',','')
string_a_escribir_min="P3,"+Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_humedad=open(path_humedad_suelo_o,'a')
file_original_humedad.write(string_a_escribir_promedio)
file_original_humedad.write(string_a_escribir_max)
file_original_humedad.write(string_a_escribir_min)
file_original_humedad.close()

"------------------------------Temperatura_suelo----------------------------------------------------------------------------------------------"

file_temperatura_suelo=open(copia_path_temperatura_suelo,'r')
valor_temperatura_suelo=[]


for line in file_temperatura_suelo.readlines():
    linea=line.strip().lower()
    valor_temperatura_suelo.append(float(linea))
valor_temperatura_suelo_promedio=math.floor(round(sum(valor_temperatura_suelo)/float(len(valor_temperatura_suelo)),cifras_significativas_1))
valor_temperatura_suelo_maximo=max(valor_temperatura_suelo)
valor_temperatura_suelo_minimo=min(valor_temperatura_suelo)
Unidades='Celsius'
Tipo_valor='Promedio'
Periodicidad='Horario'
string_temp=str(valor_temperatura_suelo_promedio)
string_temp=string_temp.replace(',','')
string_a_escribir_promedio=Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Maximo'
string_temp=str(valor_temperatura_suelo_maximo)
string_temp=string_temp.replace(',','')
string_a_escribir_max=Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
Tipo_valor='Minimo'
string_temp=str(valor_temperatura_suelo_minimo)
string_temp=string_temp.replace(',','')
string_a_escribir_min=Fecha_Hora+","+string_temp+","+Unidades+","+Tipo_valor+","+Periodicidad+"\n"
file_original_temperatura=open(path_temperatura_suelo_o,'a')
file_original_temperatura.write(string_a_escribir_promedio)
file_original_temperatura.write(string_a_escribir_max)
file_original_temperatura.write(string_a_escribir_min)
file_original_temperatura.close()




"-----------------------SE BORRAN LAS COPIAS-----------------------------------------------------"
if tipo_finca=='si':
    os.remove(copia_path_brillo_solar)
    os.remove(copia_path_velocidad_viento)
    os.remove(copia_path_direccion_viento)
    os.remove(copia_path_temperatura)
    os.remove(copia_path_humedad)
    os.remove(copia_path_PAR_suelo)
    os.remove(copia_path_precipitacion)
    
os.remove(copia_path_humedad_suelo_1)
os.remove(copia_path_humedad_suelo_2)
os.remove(copia_path_humedad_suelo_3)
os.remove(copia_path_temperatura_suelo)


