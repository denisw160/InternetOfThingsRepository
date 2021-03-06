#!/usr/bin/env bash
#
# This scripts starts the Thinger.io client.
#
# For setup a local server for Thinger.io add the servername
# iot.thinger.io in your DNS server or in /etc/hosts
#

# Parameter for connection
USERID=denisw
DEVICEID=gateway
DEVICECREDENTIAL=password

#SENSORTAGS="A0:E6:F8:AE:37:80=sensorYellow"
SENSORTAGS="C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen"

# Building the release
./build.sh
cd build

echo Starting Thinger-SensorTag ...

echo Using the following hosts:
cat /etc/hosts

# Starting the client
sudo ./thinger ${USERID} ${DEVICEID} ${DEVICECREDENTIAL} ${SENSORTAGS}
