#!/bin/bash
#
# This scripts starts the sender i for testing the communication.
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

SERVER=transportcontrol.local
PORT=1111
STATION=TCSAS001

if [ "$TRANSPORTCONTROL_PORT" != "" ]; then
    echo Setting port from environment
    PORT=${TRANSPORTCONTROL_PORT}
fi

if [ "$TRANSPORTCONTROL_STATION" != "" ]; then
    echo Setting station from environment
    STATION=${TRANSPORTCONTROL_STATION}
fi

python src/allocationsensor.py ${SERVER} ${PORT} ${STATION}
