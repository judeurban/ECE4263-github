import time
import socket

hostIP     = "129.244.42.177"
hostPort   = 12345
bufferSize  = 1024

validID = ("6013CA34", "8023BC37", "8B9BB54C", "5F9BA54F", "595BA47D")

def createSocket():

    global UDPServerSocket

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Bind to clientAdress and ip
    UDPServerSocket.bind((hostIP, hostPort))

    print("UDP server up and listening")

def AlwaysOn():
    try:
        # Listen for incoming datagrams
        while True:

            clientMessage, clientAdress = UDPServerSocket.recvfrom(bufferSize)
            clientMessage = clientMessage.decode('utf-8')

            print("\nclient: {}\treceived message: '{}'".format(clientAdress, clientMessage))

            # handshake between client and server
            if clientMessage == "stmF746ZG_ready":
                # send confirmation
                sendStr = "server_ready"
                UDPServerSocket.sendto(sendStr.encode('utf-8'), clientAdress)
                print("client: {}\tsent message: '{}'".format(clientAdress, sendStr))
                continue
            # requesting access
            else:
                if clientMessage in validID:
                    access = True
                    print("access granted")
                else:
                    access = False
                    print("access denied")

                sendStr = str(access)

                UDPServerSocket.sendto(sendStr.encode('utf-8'), clientAdress)
                print("client: {}\tsent message: '{}'\n".format(clientAdress, sendStr))
            
    except KeyboardInterrupt:
        UDPServerSocket.close()
        exit()


        
print("\n")
createSocket()
AlwaysOn()
'''

    UDP server up and listening
    client: ('129.244.42.104', 55555)       received message: 'stmF746ZG_ready'
    client: ('129.244.42.104', 55555)       sent message: 'server_ready'


    client: ('129.244.42.104', 55555)       received message: '8B8BB54C'
    access denied
    client: ('129.244.42.104', 55555)       sent message: 'False'

    client: ('129.244.42.104', 55555)       received message: '3F9BA57F'
    access denied
    client: ('129.244.42.104', 55555)       sent message: 'False'

    client: ('129.244.42.104', 55555)       received message: '595BA47D'
    access granted
    client: ('129.244.42.104', 55555)       sent message: 'True'


'''


