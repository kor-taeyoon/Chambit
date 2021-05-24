import socket
import time
import serial
HOST = "192.168.60.142"
PORT = 9999

lat = 0
lnt = 0

ser_port = "dev/ttyUSB0"
ser_baudrate = "9600"


# Serial Part
# ================
try:
    ser = serial.Serial(ser_port, baudrate = ser_baudrate, timeout = None)
except:
    print("cannot connect to device")


# Socket Part
# ================
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_socket.bind((HOST, PORT))
server_socket.listen()
print("listening")

client_socket, addr = server_socket.accept()
print("Connected by", addr)

# Main Loop
# ================================

while True:
    # Serial Part
    # ================
    try:
        if ser.isOpen():
            if ser.in_waiting != 0:
                temp_data = ser.readline()
                print(temp_data)
    except:
        try:
            ser = serial.Serial(ser_port, baudrate = ser_baudrate, timeout = None)
        except:
            print("cannot connect to device")
        lat = 0
        lnt = 0
        print("not connected")


    # Socket Part
    # ================
    try:
        data = client_socket.recv(1024)
    except:
        client_socket.close()
        server_socket.listen()
        print("listening")
        client_socket, addr = server_socket.accept()
        continue
    if not data:
        client_socket.close()
        server_socket.listen()
        print("listening")
        client_socket, addr = server_socket.accept()
        continue
    
    # Replying Part
    # ================
    if lat == 0 and lnt == 0:
        client_socket.sendall("0".encode())
    else:
        client_socket.sendall((str(lat)+"*"+str(lnt)).encode())

client_socket.close()
server_socket.close()
