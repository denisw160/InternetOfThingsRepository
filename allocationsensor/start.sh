#!/bin/bash
#
# This scripts starts the sender for the communication.
#
# For setup the TransportControl Server add the servername
# transportcontrol.local in your DNS server or in /etc/hosts
#
# Setup for TransportControl in system environment, add these lines
# in /etc/profile
#
# export TRANSPORTCONTROL_STATION=TCSAS001
# export TRANSPORTCONTROL_PORT=1112
#
# For the system service add this to
# sudo systemctl edit allocationsensor
#
# [Service]
# Environment="TRANSPORTCONTROL_PORT=1112"
# Environment="TRANSPORTCONTROL_STATION=TCSAS001"
#

SERVER=transportcontrol.local
PORT=1111
STATION=TCSAS001

echo Starting AllocationSensor ...

echo Using the following hosts:
cat /etc/hosts

if [ "$TRANSPORTCONTROL_PORT" != "" ]; then
    echo Setting port from environment
    PORT=${TRANSPORTCONTROL_PORT}
fi

if [ "$TRANSPORTCONTROL_STATION" != "" ]; then
    echo Setting station from environment
    STATION=${TRANSPORTCONTROL_STATION}
fi

python src/allocationsensor.py ${SERVER} ${PORT} ${STATION}
