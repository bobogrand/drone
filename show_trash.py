import serial
import matplotlib.pyplot as plt
import numpy as np

myPort = serial.Serial('COM3',115200)
print("Connecting Serail Port 4...")

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
    
    spect = np.abs(result[2500:samples-200])
    max_frq = np.argmax(spect)
    print("계산중")
    print(max_frq)
    total  = np.sum(spect)

    trash = []
    
    pla1 = np.sum(spect[1400:1500]/total)
    pla2= np.sum((spect[2100:2150]+spect[1625:1675])/total)
    pla3 = np.sum(spect[2050:2150])/total
    pla = [pla1,pla2,pla3]
    for percent in pla:
        print("pla :",percent)
    
    pla = np.amax([pla1,pla2,pla3])
    
    can1 = np.sum(spect[800:900]/total)
    can2 = np.sum(spect[200:300])/total
    can3= np.sum(spect[700:800])/total
    can4 = np.sum(spect[100:200])/total
    can5 = np.sum(spect[300:400])/total

    can = [can1,can2,can3,can4,can5]

    for percent in can:
        print("can :",percent)
    can = np.amax([can1,can2,can3,can4])
    glass1 = np.sum(spect[1925:1975])+np.sum(spect[1275:1325])
    glass1 /= total
    glass2 = np.sum(spect[1050:1100])+np.sum(spect[1950:2000])
    glass2 /= total
    glass3 = np.sum(spect[1475:1525])+np.sum(spect[1625:1675])
    glass3 /= total
    glass4 = np.sum(spect[1075:1125]) + np.sum(spect[1575:1625])
    glass4 /= total
    glass = [glass1,glass2,glass3,glass4]
    for percent in glass:
        print("glass :",percent)

    glass = np.max([glass1,glass2,glass3,glass4])
    trash.append(pla)
    trash.append(can)
    trash.append(glass)
    
    
    first = trash.index(max(trash))

    who = 'others'
    ##pla
    if trash[first] > 0.05:
        if first == 0 :
            who = "plastic!"
        elif first ==1:
            who = "can!"
        elif first ==2:
            who = 'glass!'
    print(who)

    chart = plt.plot(spect)
    plt.grid(True)
    plt.show()
    
