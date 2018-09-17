#!/bin/bash
#
# This scripts installs necessary components
#

sudo apt update
sudo apt upgrade
sudo apt autoremove

sudo apt-get install -y cmake
sudo apt-get install -y libssl-dev
sudo apt-get install -y libjsoncpp-dev
sudo apt-get install -y bluez build-essential libglib2.0-dev libdbus-1-dev python-dev

sudo apt-get install -y python
sudo apt-get install -y python-pip

sudo pip install bluepy
