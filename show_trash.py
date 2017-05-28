
import serial
#import numpy as py
import win32com.client
from win32com.client import constants as c
import matplotlib.pyplot as plt
import numpy as np

myPort = serial.Serial('COM4',115200)
print("Connecting Serail Port 4...")
excel = win32com.client.Dispatch("Excel.Application")

path = 'C:\\Users\ksj\\Desktop\\plastic.xlsx'
wb = excel.Workbooks.Open(path)
excel.Visible = True
ws = wb.ActiveSheet

samples = int(5000)
for e in range(1,5000):
    real_data = []
    ## input data from node MCU
    for count in range(samples):
        data =  myPort.readline()
        data = data[:-2].decode()
        data = float(data)
        real_data.append(data)
    result = np.fft.fft(real_data)
    
    spect = np.abs(result[2500:samples-100])
    print("계산중")
    total  = np.sum(spect)
    trash = []
    pla1 = np.sum(spect[1400:1500]/total)
    pla2= np.sum((spect[2000:2050]+spect[1625:1675])/total)
    can = np.sum(spect[1000:1100]/total)
    glass1 = np.sum((spect[1925:1975]+spect[1275:1325])/total)
    glass2 = np.sum(spect[1075:1175]/total)
    trash.append(pla1)
    trash.append(pla2)
    trash.append(can)
    trash.append(glass1)
    trash.append(glass2)
    
    
    first = trash.index(max(trash))
    print("pla1: %d",pla1)
    print("pla2: %d",pla2)
    print("can: %d",can)
    print("glass:%d",glass1)
    print("glass:%d",glass2)
    who = 'others'
    ##pla
    if trash[first] > 0.05:
        if first == 0 or first == 1:
            who = "plastic!"
        elif first ==2:
            who = "can!"
        elif first ==3:
            who = 'glass!'
    print(who)
        
  
    chart = plt.plot(spect)
    plt.grid(True)
    plt.show()
    


        
    
