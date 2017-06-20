import serial
import matplotlib.pyplot as plt
import numpy as np

myPort = serial.Serial('COM4',115200)
print("Connecting Serail Port 4...")

samples = int(256)
for e in range(1,samples):
    real_data = []
    ## input data from node MCU
    for count in range(samples):
        data =  myPort.readline()
        data = data[:-2].decode()
        data = float(data)
        real_data.append(data)
    result = np.fft.fft(real_data)
    
    spect = np.abs(result[128:samples-5])
    max_frq = np.argmax(spect)
    print("계산중")
    print(max_frq)
    total  = np.sum(spect)
    trash = []
    dic = {}
    can1 = np.sum(spect[54:62])/total
    can2 = np.sum(spect[78:86])/total
    can = [can1,can2]

    for percent in can:
        print("can :",percent)
    can = np.amax([can1,can2])
    dic['can'] = can
    
    pla1 = np.sum(spect[90:98]/total)
    pla2 = np.sum(spect[100:108])/total
    pla = [pla1,pla2]
    for percent in pla:
        print("pla :",percent)
    pla = np.amax([pla1,pla2])
    dic['pla'] = pla

    ret = max(dic, key = dic.__getitem__)
    print(ret,dic[ret])
    chart = plt.plot(spect)
    plt.plot(real_data)
    plt.grid(True)
    plt.show()
    

