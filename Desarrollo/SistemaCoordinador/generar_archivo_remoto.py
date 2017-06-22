import os
if os.path.exists('/home/pi/ejemplo.csv'):
    os.system("rm -r /home/pi/ejemplo.csv")
    
year=17
mes=06
dia_max=31;

for dia in range(1,dia_max):
    for hora in range(0,23):
        for minuto in range(0,59):
            for segundo in range(0,6):
                cadena="d>"+str(year)+"/"+str(mes)+"/"+str(dia)+"/"+str(hora)+"/"+str(minuto)+"/"+str(10*segundo)+"<"+str(year+mes+dia+hora+minuto+segundo)
                archivo=open('/home/pi/ejemplo.csv','a')
                archivo.write(cadena)
                archivo.write('\n')
                archivo.close
    
