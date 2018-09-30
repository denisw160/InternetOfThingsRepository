#!/usr/bin/env bash
#
# This scripts starts the Thinger.io client.
#
# For setup a local server for Thinger.io add the servername
# iot.thinger.io in your DNS server or in /etc/hosts
#

# Parameter for connection
USERID=denisw
DEVICEID=TEST
DEVICECREDENTIAL=pasW0rdZ

# Building the release
./build.sh
cd build

echo Starting Thinger-Monitor ...

echo Using the following hosts:
cat /etc/hosts

# Starting the client
./thinger ${USERID} ${DEVICEID} ${DEVICECREDENTIAL}
