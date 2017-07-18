import os

path_serial_EM='puerto_EM.txt'
path_serial_Xbee='puerto_Remoto.txt'

if os.path.exists(path_serial_EM):
    os.remove(path_serial_EM)
if os.path.exists(path_serial_Xbee):
    os.remove(path_serial_Xbee)

os.system("dmesg | grep -iC 3 'cp210x converter now attached to' > serial_EM.txt")
os.system("dmesg | grep -iC 3 'FTDI USB Serial Device converter now attached to' > serial_Remoto.txt")
puerto_EM=''
if 'cp210x converter now attached to ttyUSB0' in open('serial_EM.txt').read():
 puerto_EM='/dev/ttyUSB0'
if 'cp210x converter now attached to ttyUSB1' in open('serial_EM.txt').read():
 puerto_EM='/dev/ttyUSB1'
puerto_remoto=''
if 'FTDI USB Serial Device converter now attached to ttyUSB0' in open('serial_Remoto.txt').read():
 puerto_remoto='/dev/ttyUSB0'
if 'FTDI USB Serial Device converter now attached to ttyUSB1' in open('serial_Remoto.txt').read():
 puerto_remoto='/dev/ttyUSB1'

archivo=open(path_serial_EM,'a')
archivo.write(puerto_EM)
archivo.close

archivo=open(path_serial_Xbee,'a')
archivo.write(puerto_remoto)
archivo.close
