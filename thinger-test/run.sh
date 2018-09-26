#!/usr/bin/env bash
#
# This scripts starts the Thinger.io client.
#
# For setup the server for Thinger.io add the servername
# iot.thinger.io in your DNS server or in /etc/hosts
#

# Building the release
./build.sh
cd build

echo Starting Thinger-Test ...

echo Using the following hosts:
cat /etc/hosts

# Starting the client
./thinger