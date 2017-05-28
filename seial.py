 #-*- coding: utf-8 -*-
import serial 
#import numpy as py
import win32com.client

myPort = serial.Serial('COM4',115200)
print("Connecting Serail Port 4...")
excel = win32com.client.Dispatch("Excel.Application")

path = 'C:\\Users\ksj\\Desktop\\data.xlsx'
wb = excel.Workbooks.Open(path)
excel.Visible = True

ws = wb.ActiveSheet


n = 128
print("excel")
for e in range(2,1000):
    temp = []
    for count in range(1,n+1):
        
        i = myPort.readline()
        i = i[:-2].decode()
        print(i)
        data = myPort.readline()
        data = data[:-2].decode()
        count %= n
        
        ws.Cells(e,count+1).Value = data
wb.SaveAs(path)
myPort.close()
excel.Quit()
 
