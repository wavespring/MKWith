import serial
import csv

ser = serial.Serial(port="COM12", baudrate=115200)

with open("temp.csv", "w") as f:
  writer = csv.writer(f)
  writer.writerow(["Xcor, Ycor, type"])
  while True:
    data = ser.readline().decode().strip()
    xcor, ycor, mattype = data.split(",")
    print(xcor, ycor, mattype)
    writer.writerow([xcor, ycor, mattype])

