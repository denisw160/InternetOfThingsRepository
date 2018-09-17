#!/usr/bin/env bash

# Showing bluetooth devices
echo Searching for bluetooth devices - press CRTL-C to stop
sudo hcitool lescan

# Run python script for testing
sudo python src/sensortagcollector.py C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow
