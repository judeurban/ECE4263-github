from ctypes import sizeof
import serial
from time import sleep
# from sys import size

arduino = serial.Serial(port='COM6')
arduino.baudrate = 9600
arduino.timeout = 1

try:
    while True:
        # readstring: in bytes
        readstring = arduino.read_until('\n')
        if len(readstring) > 1:
            print("string: {}".format(readstring.decode('utf-8')), end='')
            print("size: {} bytes".format(len(readstring)))
        sleep(0.01)

except KeyboardInterrupt:
    arduino.close()
    exit()