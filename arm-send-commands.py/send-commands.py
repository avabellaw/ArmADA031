# Python code transmits a byte to Arduino /Microcontroller
import serial
import time
try: 
    SerialObj = serial.Serial('/dev/ttyUSB0') # COMxx  format on Windows
                    # ttyUSBx format on Linux
    SerialObj.baudrate = 115200  # set Baud rate to 9600
    time.sleep(3)
    while (True):
        i = input("enter command)")
        if i == 'q':
            break
        SerialObj.write(i.encode('ascii'))    #transmit 'A' (8bit) to micro/Arduino
    #transmit 'A' (8bit) to micro/Arduino
except Exception as e:
    print("Error: " + str(e))
finally:
    SerialObj.close()      # Close the port