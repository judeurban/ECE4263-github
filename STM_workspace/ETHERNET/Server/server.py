import time
import socket

hostIP     = "192.168.2.95"
hostPort   = 20001
bufferSize  = 1024

def createSocket():
    global UDPServerSocket

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Bind to clientAdress and ip
    UDPServerSocket.bind((hostIP, hostPort))

    print("UDP server up and listening")

def listenForRequests():

    # first time
    clientMessage, clientAdress = UDPServerSocket.recvfrom(bufferSize)
    print("Client found at", clientAdress)

    try:
        # Listen for incoming datagrams
        while True:

            print(clientMessage)

            # Sending a reply to client
            UDPServerSocket.sendto("Hello UDP Client".encode('utf-8'), clientAdress)

            time.sleep(1)

            UDPServerSocket.sendto("ID246,TRUE".encode('utf-8'), clientAdress)
            
            clientMessage, clientAdress = UDPServerSocket.recvfrom(bufferSize)
    
    except KeyboardInterrupt:
        pass

    UDPServerSocket.close()

createSocket()
listenForRequests()