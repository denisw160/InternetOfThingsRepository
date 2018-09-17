from PyCRC.CRCCCITT import CRCCCITT
import RPi.GPIO as GPIO
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
# 8         1           string  allocation state, 0 = open, 1 = occupied
# 9         n           short   CRC16-CCINT for bytes 0 - 9
#
# require modules
#  - PyCRC (pip)
#  - python-dev + python-rpi.gpio (apt)
#    or for development fakeRPiGPIO (pip)
#

# Default settings
UDP_IP = "127.0.0.1"
UDP_PORT = 1111
STATION = "TCS00000"
DEBUG = False
INTERVAL = 1

ALLOCATED_SENSOR = 7  # GPIO 04
STATUS_LED = 11  # GPIO 17
ALLOCATED_LED = 13  # GPIO 27


# Functions

def int2bytes(n):
    b = bytearray([0, 0])  # init
    b[1] = n & 0xFF
    n >>= 8
    b[0] = n & 0xFF

    # Return the result as byte array
    return b


def getsensordata():
    # Reading High/Low from sensor
    # Example: http://raspberry.io/projects/view/reading-and-writing-from-gpio-ports-from-python/
    #          https://tutorials-raspberrypi.de/raspberry-pi-gpio-erklaerung-beginner-programmierung-lernen/
    r = GPIO.input(ALLOCATED_SENSOR)
    if r == 0:
        return True
    else:
        return False


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

# Setup GPIO layout
GPIO.setmode(GPIO.BOARD)
GPIO.setup(STATUS_LED, GPIO.OUT)  # Pin 11 (GPIO 17) as output
GPIO.setup(ALLOCATED_LED, GPIO.OUT)  # Pin 13 (GPIO 27) as output
GPIO.setup(ALLOCATED_SENSOR, GPIO.IN)  # Pin 07 (GPIO 04) as input

# Activate on booting
GPIO.output(STATUS_LED, GPIO.HIGH)
GPIO.output(ALLOCATED_LED, GPIO.HIGH)

# Running server
HEARTBEAT = False
try:
    while True:
        # Toggle status led for heartbeat
        HEARTBEAT = not HEARTBEAT
        if HEARTBEAT:
            GPIO.output(STATUS_LED, GPIO.HIGH)
        else:
            GPIO.output(STATUS_LED, GPIO.LOW)

        # Reading state from GPIO port
        ALLOCATED = getsensordata()
        ALLOCATED_AS_STRING = "0"
        if ALLOCATED:
            ALLOCATED_AS_STRING = "1"
            GPIO.output(ALLOCATED_LED, GPIO.HIGH)
        else:
            GPIO.output(ALLOCATED_LED, GPIO.LOW)

        # Building message
        MESSAGE_AS_BYTES = str.encode(STATION) + str.encode(ALLOCATED_AS_STRING)
        CHECKSUM = CRCCCITT("FFFF").calculate(MESSAGE_AS_BYTES)

        if DEBUG:
            print("message:", MESSAGE_AS_BYTES)
            print("checksum:", CHECKSUM)
            print("checksum (hex):", hex(CHECKSUM))

        # FixMe: perhaps a mistake in converting int to 2 bytes
        MESSAGE_AS_BYTES = MESSAGE_AS_BYTES + int2bytes(CHECKSUM)

        # Sending message
        sock = socket.socket(socket.AF_INET,  # Internet
                             socket.SOCK_DGRAM)  # UDP
        sock.sendto(MESSAGE_AS_BYTES, (UDP_IP, UDP_PORT))

        # wait for next update
        time.sleep(INTERVAL)
except KeyboardInterrupt:
    if DEBUG:
        print("Strg-C called")
finally:
    print("AllocationSensor stopped")
    # Release GPIO ports
    GPIO.cleanup()
