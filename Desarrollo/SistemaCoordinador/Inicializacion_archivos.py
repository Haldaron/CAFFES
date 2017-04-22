import os

path_principal='/home/pi/USCO'
os.system("rm -r /home/pi/USCO")

if not os.path.exists(path_principal):
    os.mkdir(path_principal)

path_ambiental='/home/pi/USCO/remoto_meteorologico'

if not os.path.exists(path_ambiental):
    os.mkdir(path_ambiental)


archivo_brillo_solar=open(path_ambiental+"/BrilloSolar.csv","a+")
archivo_brillo_solar.close()

archivo_direccion_viento=open(path_ambiental+"/DireccionViento.csv","a+")
archivo_direccion_viento.close()

archivo_humedad_relativa=open(path_ambiental+"/HumedadRelativa.csv","a+")
archivo_humedad_relativa.close()

archivo_PAR=open(path_ambiental+"/PAR.csv","a+")
archivo_PAR.close()

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
    archivo_temperatura=open(path_temp+"/Temperatura.csv","a+")
    archivo_temperatura.close()
print 'su respuesta fue: %d y ya se crearon los directorios y archivos'% primera_pregunta

path_administrativo='/home/pi/USCO/administrativo'

if not os.path.exists(path_administrativo):
    os.mkdir(path_administrativo)

usuario= raw_input('Cual es el usuario del nodo coordinador: ')
archivo_usuario=open(path_administrativo+"/usuario.txt","a+")
archivo_usuario.write(usuario)
archivo_usuario.close()

contrasena= raw_input('Cual es la contrasena del nodo coordinador: ')
archivo_contrasena=open(path_administrativo+"/contrasena.txt","a+")
archivo_contrasena.write(contrasena)
archivo_velocidad_viento.close()

print 'ha finalizado con exito la inicializacion'
