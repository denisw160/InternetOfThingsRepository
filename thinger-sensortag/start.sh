#!/usr/bin/env bash
#
# This scripts starts the Thinger.io client.
#
# For setup the server for Thinger.io add the servername
# iot.thinger.io in your DNS server or in /etc/hosts
#
# Setup the IDs of the SensorTags in system environment,
# use command and add
#
# sudo systemctl edit thinger-sensortag
#
# [Service]
# Environment="THINGER_SENSORTAGS=C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen"
#

echo Starting Thinger-SensorTag ...

echo Using the following hosts:
cat /etc/hosts

SENSORTAGS=C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen

if [ "$THINGER_SENSORTAGS" != "" ]; then
    echo Setting SensorTags from environment
    SENSORTAGS=${THINGER_SENSORTAGS}
fi

# Starting the client
./thinger

#!/usr/bin/env bash
cd build

sudo ./thinger ${SENSORTAGS}