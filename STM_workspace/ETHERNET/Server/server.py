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

    try:
        # Listen for incoming datagrams
        while True:

            clientMessage, clientAdress = UDPServerSocket.recvfrom(bufferSize)
            
            clientMessage = clientMessage.decode('utf-8')

            if clientMessage == 'ID246':
                access = True
            else:
                access = False

            # read client message, go get log....

            # filter
            # if clientAdress == "192.168.2.90":

            # Sending a reply to client
            # if user has access, send TRUE

            sendStr = "{},{}".format(clientMessage, str(access)).encode('utf-8')
            UDPServerSocket.sendto(sendStr, clientAdress)
            
    except KeyboardInterrupt:
        pass

    UDPServerSocket.close()

# first time handshake
def initialize():

    serverReady = False

    while not serverReady:

        clientMessage, clientAdress = UDPServerSocket.recvfrom(bufferSize)
        
        print("Client found at", clientAdress)

        clientMessage = clientMessage.decode('utf-8')

        print(clientMessage, end='')

        if clientMessage == "stmF746ZG_ready":
            # send confirmation
            UDPServerSocket.sendto("server_ready".encode('utf-8'), clientAdress)
            serverReady = True

def debugWhileAlwaysOn():
    try:
        # Listen for incoming datagrams
        while True:

            clientMessage, clientAdress = UDPServerSocket.recvfrom(bufferSize)
            clientMessage = clientMessage.decode('utf-8')

            if clientMessage == "stmF746ZG_ready":
                # send confirmation
                UDPServerSocket.sendto("server_ready".encode('utf-8'), clientAdress)
                continue

            if clientMessage == 'ID246':
                access = True
            else:
                access = False

            # read client message, go get log....

            # filter
            # if clientAdress == "192.168.2.90":

            # Sending a reply to client
            # if user has access, send TRUE

            sendStr = "{},{}".format(clientMessage, str(access)).encode('utf-8')
            UDPServerSocket.sendto(sendStr, clientAdress)
            
    except KeyboardInterrupt:
        pass

    UDPServerSocket.close()

        

createSocket()
# initialize()
# listenForRequests()
debugWhileAlwaysOn()