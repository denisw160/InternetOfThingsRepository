#!/bin/bash
#
# This scripts starts the sender for the communication.
#
# For setup the Server add the servername
# server.local in your DNS server or in /etc/hosts
#
# Setup in global system environment, add these lines
# in /etc/profile (or similar)
#
# export SERVER_STATION=TCSAS001
# export SERVER_PORT=1112
#
# For the system service add this to
# sudo systemctl edit allocationsensor
#
# [Service]
# Environment="SERVER_PORT=1112"
# Environment="SERVER_STATION=TCSAS001"
#

SERVER=server.local
PORT=1111
STATION=TCSAS001

echo Starting AllocationSensor ...

echo Using the following hosts:
cat /etc/hosts

if [ "$SERVER_PORT" != "" ]; then
    echo Setting port from environment
    PORT=${SERVER_PORT}
fi

if [ "$SERVER_STATION" != "" ]; then
    echo Setting station from environment
    STATION=${SERVER_STATION}
fi

python src/allocationsensor.py ${SERVER} ${PORT} ${STATION}
