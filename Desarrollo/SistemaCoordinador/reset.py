import RPi.GPIO as GPIO
import time
import os

"----------------------------------encender o resetear el modem----------------------------------"
pin_GPIO=27
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
    time.sleep(4)
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

"""time.sleep(120)"""

        
        
            
    

