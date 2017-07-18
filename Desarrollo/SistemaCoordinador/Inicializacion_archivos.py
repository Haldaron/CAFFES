import os

path_principal='/home/pi/USCO'
if os.path.exists(path_principal):
    os.system("rm -r /home/pi/USCO")

if not os.path.exists(path_principal):
    os.mkdir(path_principal)
    
path_administrativo='/home/pi/USCO/administrativo'

tipo_finca=raw_input('En esta finca se instalara estacion metereologica?si/no: ')

path_suelos_remoto_1='/home/pi/USCO/remoto_suelo/remoto1'

rem_m_ID="NA"

if tipo_finca=='si':

    path_ambiental='/home/pi/USCO/remoto_meteorologico'

    rem_m_ID=raw_input('ID del remoto metereologico en la base de datos: ')
    

    if not os.path.exists(path_ambiental):
        os.mkdir(path_ambiental)


        archivo_brillo_solar=open(path_ambiental+"/BrilloSolar.csv","a+")
        archivo_brillo_solar.close()

        archivo_direccion_viento=open(path_ambiental+"/DireccionViento.csv","a+")
        archivo_direccion_viento.close()

        archivo_humedad_relativa=open(path_ambiental+"/HumedadRelativa.csv","a+")
        archivo_humedad_relativa.close()


        archivo_precipitacion=open(path_ambiental+"/Precipitacion.csv","a+")
        archivo_humedad_relativa.close()

        archivo_temperatura_ambiente=open(path_ambiental+"/TempAmbiente.csv","a+")
        archivo_temperatura_ambiente.close()

        archivo_velocidad_viento=open(path_ambiental+"/VelocidadViento.csv","a+")
        archivo_velocidad_viento.close()

path_suelos='/home/pi/USCO/remoto_suelo'

if not os.path.exists(path_suelos):
    os.mkdir(path_suelos)

primera_pregunta=input("Cuantos nodos remotos estan asociados a este coordinador: ")


for i in range(1,primera_pregunta+1):

    path_temp='/home/pi/USCO/remoto_suelo/remoto%d'% i

    if not os.path.exists(path_temp):
        os.mkdir(path_temp)
        
    archivo_humedad_1=open(path_temp+"/Humedad1.csv","a+")
    archivo_humedad_1.close()
    archivo_humedad_2=open(path_temp+"/Humedad2.csv","a+")
    archivo_humedad_2.close()
    archivo_humedad_3=open(path_temp+"/Humedad3.csv","a+")
    archivo_humedad_3.close()
    archivo_temperatura=open(path_temp+"/Temperatura.csv","a+")
    archivo_temperatura.close()
    archivo_ph=open(path_temp+"/ph.csv","a+")
    archivo_ph.close()
    os.system('sudo chmod 777 %s/ph*'%path_temp)

path_tanques='/home/pi/USCO/remoto_tanque'

if not os.path.exists(path_tanques):
    os.mkdir(path_tanques)
    archivo_ph_tanque=open(path_tanques+"/ph.csv","a+")
    archivo_ph_tanque.close()
    archivo_temperatura_tanque=open(path_tanques+"/Temperatura.csv","a+")
    archivo_temperatura_tanque.close()


os.system('sudo chmod 777 /home/pi/USCO/remoto_tanque/*')
          
print 'su respuesta fue: %d y ya se crearon los directorios y archivos'% primera_pregunta


if not os.path.exists(path_administrativo):
    os.mkdir(path_administrativo)

usuario= raw_input('Cual es el usuario del nodo coordinador: ')
archivo_usuario=open(path_administrativo+"/usuario.txt","a+")
archivo_usuario.write(usuario)
archivo_usuario.close()

contrasena= raw_input('Cual es la contrasena del nodo coordinador: ')
archivo_contrasena=open(path_administrativo+"/contrasena.txt","a+")
archivo_contrasena.write(contrasena)

archivo_tipo_finca=open(path_administrativo+"/tipo_finca.txt","a+")
archivo_tipo_finca.write(tipo_finca)
archivo_tipo_finca.close()

IP=raw_input('Cual es la pagina web a la que se suben los datos?: ')
archivo_IP=open(path_administrativo+"/IP.txt","a+")
archivo_IP.write(IP)

cordID=raw_input('ID del cordinador en la base de datos: ')
archivo_cordID=open(path_administrativo+"/Cord_ID.txt","a+")
archivo_cordID.write(cordID)

remID=raw_input('ID del remoto suelos en la base de datos: ')
archivo_remID=open(path_administrativo+"/Rem_ID.txt","a+")
archivo_remID.write(remID)

archivo_rem_m_ID=open(path_administrativo+"/Rem_metereologico_ID.txt","a+")
archivo_rem_m_ID.write(rem_m_ID)

rem_T_ID=raw_input('ID del remoto tanques en la base de datos: ')
archivo_rem_T_ID=open(path_administrativo+"/Rem_Tanques.txt","a+")
archivo_rem_T_ID.write(rem_T_ID)

if tipo_finca=='si':
    
    archivo_PAR=open(path_suelos_remoto_1+"/PAR.csv","a+")
    archivo_PAR.close()

    archivo_PAR=open(path_ambiental+"/PAR.csv","a+")
    archivo_PAR.close()

print 'ha finalizado con exito la inicializacion'
