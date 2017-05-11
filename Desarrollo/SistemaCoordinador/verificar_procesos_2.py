import os

os.system("ps -aef | grep py > archivo1.txt")

found2=False
if 'python comunicaciones_meteorologico.py' in open('archivo1.txt').read():
 found2=True

if found2==False:
    os.system("python comunicaciones_meteorologico.py")
    
