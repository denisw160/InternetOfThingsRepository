import datetime
import socket

#
# This is a test script for displaying the incoming messages
# on the UDP port.
#

# Setup the ip and port for receiving the messages
UDP_IP = "127.0.0.1"
UDP_PORT = 1111

# Binding to socket
sock = socket.socket(socket.AF_INET,  # Internet
                     socket.SOCK_DGRAM)  # UDP
sock.bind((UDP_IP, UDP_PORT))

# Receiving all messages on this port
print("Receiver started - for stopping please press CRTL-c")
print("Waiting for messages on port %s" % UDP_PORT)
while True:
    data, addr = sock.recvfrom(1024)  # buffer size is 1024 bytes
    print("%s received message: %s" % (datetime.datetime.now(), data))
