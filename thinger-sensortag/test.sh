#!/usr/bin/env bash

# Showing bluetooth devices
echo Searching for bluetooth devices - press CRTL-C to stop
sudo hcitool lescan

# Run python script for testing
sudo python src/sensortagcollector.py -d C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen
