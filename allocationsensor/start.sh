#!/bin/bash
#
# This scripts starts the sender i for testing the communication.
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
