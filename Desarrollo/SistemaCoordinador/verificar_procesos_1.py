import os

os.system("ps -aef | grep py > archivo.txt")


found1=False
if 'python comunicaciones.py' in open('archivo.txt').read():
 found1=True


if found1==False:
    os.system("sudo python comunicaciones.py")
    
    


