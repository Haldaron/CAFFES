import RPi.GPIO as GPIO
import time
import os

"----------------------------------encender o resetear el modem----------------------------------"
"""pin_GPIO=27
path_archivo='/home/pi/respuesta_ping.txt'
if os.path.exists(path_archivo):
    os.system("rm -r /home/pi/respuesta_ping.txt")
os.system("ping 192.168.1.1 -c 2 >> respuesta_ping.txt")
time.sleep(20)
string_encendido="2 packets transmitted, 2 received, 0% packet loss"
string_apagado="2 packets transmitted, 0 received, 100% packet loss"

"si la respuesta al ping es correcta haga"
if string_encendido in open(path_archivo).read():
    print("estaba prendido")
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin_GPIO, GPIO.OUT)
    GPIO.output(pin_GPIO,0)
    time.sleep(5)
    GPIO.output(pin_GPIO,1)
    time.sleep(5)
    GPIO.output(pin_GPIO,0)
    time.sleep(5)
    GPIO.output(pin_GPIO,1)
    time.sleep(5)
    time.sleep(20)
    GPIO.output(pin_GPIO,0)
    time.sleep(5)
    GPIO.output(pin_GPIO,1)
    time.sleep(5)
    GPIO.output(pin_GPIO,0)
    time.sleep(5)
    GPIO.output(pin_GPIO,1)
    time.sleep(5)
else:
    print("estaba apagado")
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin_GPIO, GPIO.OUT)
    GPIO.output(pin_GPIO,0)
    time.sleep(5)
    GPIO.output(pin_GPIO,1)
    time.sleep(5)
    GPIO.output(pin_GPIO,0)
    time.sleep(5)
    GPIO.output(pin_GPIO,1)
    time.sleep(5)

time.sleep(120)"""
"--------------comprobar la conexion a internet escribiendo en un archivo los exitos----------"
"""path_respuesta_internet='/home/pi/respuesta_google.txt'
path='/home/pi/prueba_internet.txt'
if os.path.exists(path_respuesta_internet):
    os.system("rm -r /home/pi/respuesta_google.txt")
os.system("curl http://proyectocaffes.com/server/index.php >> respuesta_google.txt")
string_internet="<p>Diligencie los siguientes campos para exportar su archivo:</p>"
Fecha_Hora=time.strftime("%Y-%m-%d,%H:%M:%S")
if string_internet in open(path_respuesta_internet).read():
    archivo=open(path,'a')
    archivo.write(Fecha_Hora)
    archivo.write('\n')
    archivo.close
else:
    archivo=open(path,'a')
    archivo.write("NA")
    archivo.write('\n')
    archivo.close"""
    
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
"---------------Rutas de los archivos temporales-----------------------------------------"

path_brillo_solar_t="/home/pi/USCO/remoto_meteorologico/BrilloSolar_temp.csv"
path_velocidad_viento_t="/home/pi/USCO/remoto_meteorologico/VelocidadViento_temp.csv"
path_direccion_viento_t="/home/pi/USCO/remoto_meteorologico/DireccionViento_temp.csv"
path_temperatura_t="/home/pi/USCO/remoto_meteorologico/TempAmbiente_temp.csv"
path_humedad_t="/home/pi/USCO/remoto_meteorologico/HumedadRelativa_temp.csv"
path_precipitacion_t="/home/pi/USCO/remoto_meteorologico/Precipitacion_temp.csv"
path_humedad_suelo_t='/home/pi/USCO/remoto_suelo/remoto1/Humedad_estadistico_temp.csv'
path_temperatura_suelo_t='/home/pi/USCO/remoto_suelo/remoto1/Temperatura_estadistico_temp.csv'
path_PAR_t='/home/pi/USCO/remoto_meteorologico/PAR_temp.csv'
path_ph_suelo_t='/home/pi/USCO/remoto_suelo/remoto1/ph_temp.csv'
path_ph_tanque_t='/home/pi/USCO/remoto_tanque/ph_temp.csv'
path_temperatura_tanque_t='/home/pi/USCO/remoto_tanque/Temperatura_temp.csv'
"--------------------------variables base de datos----------------------------------------"
variable_brillo_solar="metereologico_brillo_solar"
variable_direccion_viento="metereologico_direccion_viento"
variable_velocidad_viento="metereologico_velocidad_viento"
variable_temperatura_amb="metereologico_temperatura"
variable_humedad_amb="metereologico_humedad"
variable_precipitacion="metereologico_precipitacion"
variable_PAR="metereologico_radiacion_PAR"
variable_humedad_suelo="suelo_humedad"
variable_temperatura_suelo="suelo_temperatura"
variable_ph_suelo="suelo_pH"
variable_ph_tanque="tanque_pH"
variable_temperatura_tanque="tanque_temperatura"


"--------------------------variables auxiliares----------------------------------------"
str1="&"
numero_intentos=2
path_respuesta="/home/pi/output.html"
"--------------Variables del Formulario----------------------------------------------"
path_tipo_finca='/home/pi/USCO/administrativo/tipo_finca.txt'
file_tipo_finca=open(path_tipo_finca,'r')
for line in file_tipo_finca.readlines():
    tipo_finca=line.strip().lower()
    
path_IP='/home/pi/USCO/administrativo/IP.txt'
file_IP=open(path_IP,'r')
for line in file_IP.readlines():
    IP=line.strip().lower()

"""USUARIO"""
path_usuario='/home/pi/USCO/administrativo/usuario.txt'
file_usuario=open(path_usuario,'r')
for line in file_usuario.readlines():
    user=line.strip().lower()
    
"""CONTRASENA"""

path_password='/home/pi/USCO/administrativo/contrasena.txt'
file_password=open(path_password,'r')
for line in file_password.readlines():
    password=line.strip().lower()
    
"""CORD_ID"""

path_cordID='/home/pi/USCO/administrativo/Cord_ID.txt'
file_cordID=open(path_cordID,'r')
for line in file_cordID.readlines():
    cordID=line.strip().lower()

"""REM_SUELOS_ID"""

path_remID='/home/pi/USCO/administrativo/Rem_ID.txt'
file_remID=open(path_remID,'r')
for line in file_remID.readlines():
    remoteID=line.strip().lower()

"""REM_MET_ID="2"""

path_rem_m_ID='/home/pi/USCO/administrativo/Rem_metereologico_ID.txt'
file_rem_m_ID=open(path_rem_m_ID,'r')
for line in file_rem_m_ID.readlines():
    remoteID_m=line.strip().lower()

"""REM_TANQU_ID="2"""

path_rem_tanque_ID='/home/pi/USCO/administrativo/Rem_Tanques.txt'
file_rem_tanque_ID=open(path_rem_tanque_ID,'r')
for line in file_rem_tanque_ID.readlines():
    remoteID_tanque=line.strip().lower()

enviar="Importar"
"--------------Funcion que envia un archivo por lineas-----------------------------------"
def enviar_archivo(path_datos,path_datos_temporal,variable,rID):
    comando="curl -m 60 --form user=%s"%user+" --form password=%s"%password
    comando=comando+" --form cordID=%s"%cordID+" --form variable=%s"%variable
    comando=comando+" --form remoteID=%s"%rID+" --form datafile=@%s"%path_datos_temporal
    comando=comando+" --form enviar=%s"%enviar+" %s"%IP+" > %s"%path_respuesta

    if os.path.exists(path_datos_temporal):
        os.remove(path_datos_temporal)
    " duplicar ultima linea de archivo"
    file_datos=open(path_datos,'r')
    lineas=file_datos.readlines()
    n_lineas=len(lineas)
    file_datos.close
    file_datos=open(path_datos,'a')
    if n_lineas>0:
        file_datos.write(lineas[n_lineas-1])
    file_datos.close
    file_datos=open(path_datos,'r')
    confirmaciones=[]
    lineas_no_subidas=[]
    "leer archivo por lineas"
    for linea in file_datos.readlines():
        archivo=open(path_datos_temporal,'w')
        archivo.write(linea)
        archivo.close
        confirmacion="Null"
        "iteracion=1"
        os.system(comando)
        file_respuesta=open(path_respuesta,'r')
        valor_html=[]
        for line1 in file_respuesta.readlines():
            linea1=line1.strip().lower()
            valor_html.append(linea1)
        confirmacion=valor_html[len(valor_html)-2]
        posicion0=confirmacion.find(str1)
        posicion1=confirmacion[posicion0+1:len(confirmacion)].find(str1)
        posicion1=posicion1+posicion0+1
        confirmacion=confirmacion[posicion0+1:posicion1]
        confirmaciones.append(confirmacion)
        if confirmacion=="ok":
            if os.path.exists(path_respuesta):
                os.remove(path_respuesta)

    confirmaciones=confirmaciones[-n_lineas:]
    for i in range(0,n_lineas):
        if confirmaciones[i]!="ok":
            lineas_no_subidas.append(lineas[i])
    file_datos=open(path_datos,'w')
    file_datos.writelines(lineas_no_subidas)
    file_datos.close
"-----envio de todos los archivos----------------------------------"
if tipo_finca=='si':
    enviar_archivo(path_brillo_solar_o,path_brillo_solar_t,variable_brillo_solar,remoteID_m)
    enviar_archivo(path_direccion_viento_o,path_direccion_viento_t,variable_direccion_viento,remoteID_m)
    enviar_archivo(path_velocidad_viento_o,path_velocidad_viento_t,variable_velocidad_viento,remoteID_m)
    enviar_archivo(path_temperatura_o,path_temperatura_t,variable_temperatura_amb,remoteID_m)
    enviar_archivo(path_humedad_o,path_humedad_t,variable_humedad_amb,remoteID_m)
    enviar_archivo(path_precipitacion_o,path_precipitacion_t,variable_precipitacion,remoteID_m)
    enviar_archivo(path_PAR_o,path_PAR_t,variable_PAR,remoteID_m)
enviar_archivo(path_humedad_suelo_o,path_humedad_suelo_t,variable_humedad_suelo,remoteID)
enviar_archivo(path_temperatura_suelo_o,path_temperatura_suelo_t,variable_temperatura_suelo,remoteID)
enviar_archivo(path_ph_suelo_o,path_ph_suelo_t,variable_ph_suelo,remoteID)
enviar_archivo(path_ph_tanque_o,path_ph_tanque_t,variable_ph_tanque,remoteID_tanque)
enviar_archivo(path_temperatura_tanque_o,path_temperatura_tanque_t,variable_temperatura_tanque,remoteID_tanque)

"-----------dar permisos a todos las variables manuales-----------------"

os.system('sudo chmod 777 /home/pi/USCO/remoto_suelo/remoto1/ph*')
os.system('sudo chmod 777 /home/pi/USCO/remoto_tanque/ph*')
os.system('sudo chmod 777 /home/pi/USCO/remoto_tanque/Temperatura*')
        
        
            
    

