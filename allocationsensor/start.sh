#!/bin/bash
#
# This scripts starts the sender i for testing the communication.
#

SERVER=transportcontrol.local
PORT=1111
STATION=TCSAS001

python src/allocationsensor.py ${SERVER} ${PORT} ${STATION}
