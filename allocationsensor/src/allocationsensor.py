from PyCRC.CRCCCITT import CRCCCITT
import socket
import sys
import time

#
# This scripts starts the server and reads the status of the GPIO-port
# from the reflex light barrier.  The status is continuously transmitting
# to the receiver.
#
# For configuration the script reads the parameter from the command line.
# Order of parameters
#  1. SERVER = name or IP address
#  2. PORT = port
#  3. STATION = name of the station, in syntax TCSxxxxx
#  4. DEBUG = DEBUG or nothing to enable debug mode
#
# Structure of the telegram
# index     bytes       type    name
# 0         8           string  TCSxxxxx
# 8         1           boolean allocation state, 0 = open, 1 = occupied
# 9         n           short   CRC16-CCINT for bytes 0 - 9
#
# require pip modules
#  - PyCRC
#

# Default settings
UDP_IP = "127.0.0.1"
UDP_PORT = 1111
STATION = "TCS00000"
DEBUG = False
INTERVAL = 1

# Reading parameter from command line
if len(sys.argv) < 4:
    print("Missing parameter, please use at least SERVER, PORT, STATION")
    exit(1)

UDP_IP = sys.argv[1]
UDP_PORT = int(sys.argv[2])
STATION = sys.argv[3]

print("AllocationSensor started - for stopping please press CRTL-c")
print(" - station:", STATION)
print(" - UDP target IP:", UDP_IP)
print(" - UDP target port:", UDP_PORT)

# Debug output
if len(sys.argv) > 4:
    DEBUG = True

if DEBUG:
    print("Number of arguments:", len(sys.argv), "arguments.")
    print("Argument List:", str(sys.argv))

# Running server
while True:
    # Reading state from GPIO port
    # TODO implementation
    # Example: http://raspberry.io/projects/view/reading-and-writing-from-gpio-ports-from-python/
    ALLOCATED = True
    ALLOCATED_AS_BYTE = b'0'
    if ALLOCATED:
        ALLOCATED_AS_BYTE = b'1'

    # Building message
    MESSAGE_AS_BYTES = str.encode(STATION) + ALLOCATED_AS_BYTE
    CHECKSUM = CRCCCITT("FFFF").calculate(MESSAGE_AS_BYTES)

    if DEBUG:
        print("message:", MESSAGE_AS_BYTES)
        print("checksum:", CHECKSUM)
        print("checksum (hex):", hex(CHECKSUM))

    MESSAGE_AS_BYTES = MESSAGE_AS_BYTES + str.encode(str(CHECKSUM))

    # Sending message
    sock = socket.socket(socket.AF_INET,  # Internet
                         socket.SOCK_DGRAM)  # UDP
    sock.sendto(MESSAGE_AS_BYTES, (UDP_IP, UDP_PORT))

    # wait for next update
    time.sleep(INTERVAL)
