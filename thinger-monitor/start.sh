#!/usr/bin/env bash
#
# This scripts starts the Thinger.io client.
#
# For setup a local server for Thinger.io add the servername
# iot.thinger.io in your DNS server or in /etc/hosts
#
# For setup the parameter in system environment, please use command
# sudo systemctl edit thinger-monitor
#
# and add following lines
#
# [Service]
# Environment="THINGER_USERID=userId"
# Environment="THINGER_DEVICEID=deviceId"
# Environment="THINGER_DEVICECREDENTIAL=password"
#

echo Starting Thinger-SensorTag ...

echo Using the following hosts:
cat /etc/hosts

USERID=denisw
DEVICEID=$HOSTNAME
DEVICECREDENTIAL=password

if [ "$THINGER_USERID" != "" ]; then
    echo Setting UserID from environment
    USERID=${THINGER_USERID}
fi

if [ "$THINGER_DEVICEID" != "" ]; then
    echo Setting DeviceID from environment
    DEVICEID=${THINGER_DEVICEID}
fi

if [ "$THINGER_DEVICECREDENTIAL" != "" ]; then
    echo Setting DeviceCredential from environment
    DEVICECREDENTIAL=${THINGER_DEVICECREDENTIAL}
fi

# Starting the client
cd build
./thinger ${USERID} ${DEVICEID} ${DEVICECREDENTIAL}
