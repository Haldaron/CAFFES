import os
import time

str1="&"
numero_intentos=5
path_tipo_finca='/home/pi/USCO/administrativo/tipo_finca.txt'
file_tipo_finca=open(path_tipo_finca,'r')
for line in file_tipo_finca.readlines():
    tipo_finca=line.strip().lower()
"--------------Variables del Formulario----------------------------------------------"

path_IP='/home/pi/USCO/administrativo/IP.txt'
file_IP=open(path_IP,'r')
for line in file_IP.readlines():
    IP=line.strip().lower()

"""IP="http://157.253.231.114/server/index.php"""
path_usuario='/home/pi/USCO/administrativo/usuario.txt'
file_usuario=open(path_usuario,'r')
for line in file_usuario.readlines():
    user=line.strip().lower()
    
"""user="finca"""

path_password='/home/pi/USCO/administrativo/contrasena.txt'
file_password=open(path_password,'r')
for line in file_password.readlines():
    password=line.strip().lower()
    
"""password="finca123"""

path_cordID='/home/pi/USCO/administrativo/Cord_ID.txt'
file_cordID=open(path_cordID,'r')
for line in file_cordID.readlines():
    cordID=line.strip().lower()

"""cordID="3"""

path_remID='/home/pi/USCO/administrativo/Rem_ID.txt'
file_remID=open(path_remID,'r')
for line in file_remID.readlines():
    remoteID=line.strip().lower()

"""remoteID="2"""

path_rem_m_ID='/home/pi/USCO/administrativo/Rem_ID.txt'
file_rem_m_ID=open(path_rem_m_ID,'r')
for line in file_rem_m_ID.readlines():
    remoteID_m=line.strip().lower()

enviar="Importar"
path_respuesta="/home/pi/USCO/output.html"


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
if tipo_finca=='si':
    "---------------Brillo Solar-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_brillo_solar"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_brillo_solar_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    while iteracion<=numero_intentos:
        os.system(comando)
        file_brillo_solar=open(path_respuesta,'r')
        valor_html=[]

        for line in file_brillo_solar.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            print(iteracion)
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_brillo_solar_o):
                print(iteracion)
                os.remove(path_brillo_solar_o)
                archivo=open(path_brillo_solar_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
    "---------------Direccion Viento-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_direccion_viento"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_direccion_viento_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta
    while iteracion<=numero_intentos:
        os.system(comando)
        file_direccion_viento=open(path_respuesta,'r')
        valor_html=[]

        for line in file_direccion_viento.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_direccion_viento_o):
                os.remove(path_direccion_viento_o)
                archivo=open(path_direccion_viento_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
    "---------------Velocidad Viento-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_velocidad_viento"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_velocidad_viento_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    while iteracion<=numero_intentos:
        os.system(comando)
        file_velocidad_viento=open(path_respuesta,'r')
        valor_html=[]

        for line in file_velocidad_viento.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_velocidad_viento_o):
                os.remove(path_velocidad_viento_o)
                archivo=open(path_velocidad_viento_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
    "---------------Temperatura Ambiente-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_temperatura"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_temperatura_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    while iteracion<=numero_intentos:
        os.system(comando)
        file_temperatura=open(path_respuesta,'r')
        valor_html=[]

        for line in file_temperatura.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_temperatura_o):
                os.remove(path_temperatura_o)
                archivo=open(path_temperatura_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
    "---------------Humedad-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_humedad"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_humedad_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    while iteracion<=numero_intentos:
        os.system(comando)
        file_humedad=open(path_respuesta,'r')
        valor_html=[]

        for line in file_humedad.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_humedad_o):
                os.remove(path_humedad_o)
                archivo=open(path_humedad_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
    "---------------Precipitacion-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_precipitacion"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_precipitacion_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    while iteracion<=numero_intentos:
        os.system(comando)
        file_precipitacion=open(path_respuesta,'r')
        valor_html=[]

        for line in file_precipitacion.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_precipitacion_o):
                os.remove(path_precipitacion_o)
                archivo=open(path_precipitacion_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
    "---------------PAR-----------------------------------------------------------"
    confirmacion="Null"
    iteracion=1
    variable="metereologico_radiacion_PAR"
    comando="curl --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%remoteID_m+" --form datafile=@%s"%path_PAR_o
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    while iteracion<=numero_intentos:
        os.system(comando)
        file_precipitacion=open(path_respuesta,'r')
        valor_html=[]

        for line in file_precipitacion.readlines():
            linea=line.strip().lower()
            valor_html.append(linea)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        if confirmacion=="ok":
            iteracion=numero_intentos+10
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)
            if os.path.exists(path_precipitacion_o):
                os.remove(path_precipitacion_o)
                archivo=open(path_precipitacion_o,"a+")
                archivo.close
        else:
            iteracion=iteracion+1
"---------------Humedad suelo-----------------------------------------------------------"
confirmacion="Null"
iteracion=1
variable="suelo_humedad"
comando="curl --form user=%s"%user+" --form password=%s"%password
comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
comando=comando+" --form remoteID=%s"%remoteID+" --form datafile=@%s"%path_humedad_suelo_o
comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta
print comando
while iteracion<=numero_intentos:
    os.system(comando)
    file_precipitacion=open(path_respuesta,'r')
    valor_html=[]

    for line in file_precipitacion.readlines():
        linea=line.strip().lower()
        valor_html.append(linea)
    confirmacion=valor_html[len(valor_html)-2]
    posicion0=confirmacion.find(str1)
    posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
    posicion1=posicion1+posicion0+1
    confirmacion=confirmacion[posicion0+1:posicion1]
    if confirmacion=="ok":
        iteracion=numero_intentos+10
        if os.path.exists(path_respuesta):
            os.remove(path_respuesta)
        if os.path.exists(path_precipitacion_o):
            os.remove(path_precipitacion_o)
            archivo=open(path_precipitacion_o,"a+")
            archivo.close
    else:
        iteracion=iteracion+1
"---------------Temperatura suelo-----------------------------------------------------------"
confirmacion="Null"
iteracion=1
variable="suelo_temperatura"
comando="curl --form user=%s"%user+" --form password=%s"%password
comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
comando=comando+" --form remoteID=%s"%remoteID+" --form datafile=@%s"%path_temperatura_suelo_o
comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

while iteracion<=numero_intentos:
    os.system(comando)
    file_precipitacion=open(path_respuesta,'r')
    valor_html=[]

    for line in file_precipitacion.readlines():
        linea=line.strip().lower()
        valor_html.append(linea)
    confirmacion=valor_html[len(valor_html)-2]
    posicion0=confirmacion.find(str1)
    posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
    posicion1=posicion1+posicion0+1
    confirmacion=confirmacion[posicion0+1:posicion1]
    if confirmacion=="ok":
        iteracion=numero_intentos+10
        if os.path.exists(path_respuesta):
            os.remove(path_respuesta)
        if os.path.exists(path_precipitacion_o):
            os.remove(path_precipitacion_o)
            archivo=open(path_precipitacion_o,"a+")
            archivo.close
    else:
        iteracion=iteracion+1
