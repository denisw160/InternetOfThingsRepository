#!/usr/bin/env bash
#
# This scripts starts the Thinger.io client.
#
# For setup a local server for Thinger.io add the servername
# iot.thinger.io in your DNS server or in /etc/hosts
#
# For setup the parameter in system environment, please use command
# sudo systemctl edit thinger-sensortag
#
# and add following lines
#
# [Service]
# Environment="THINGER_USERID=userId"
# Environment="THINGER_DEVICEID=deviceId"
# Environment="THINGER_DEVICECREDENTIAL=password"
# Environment="THINGER_SENSORTAGS=C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen"
#

echo Starting Thinger-SensorTag ...

echo Using the following hosts:
cat /etc/hosts

USERID=denisw
DEVICEID=gateway
DEVICECREDENTIAL=password

SENSORTAGS="C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen"


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

if [ "$THINGER_SENSORTAGS" != "" ]; then
    echo Setting SensorTags from environment
    SENSORTAGS=${THINGER_SENSORTAGS}
fi

# Starting the client
cd build
sudo ./thinger ${USERID} ${DEVICEID} ${DEVICECREDENTIAL} ${SENSORTAGS}
