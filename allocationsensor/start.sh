#!/bin/bash
#
# This scripts starts the sender i for testing the communication.
#

SERVER=127.0.0.1
PORT=1111
STATION=TCSAS001

# ToDo Check possibilities to restart on error
python src/allocationsensor.py ${SERVER} ${PORT} ${STATION}
