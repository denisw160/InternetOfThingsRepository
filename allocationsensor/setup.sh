#!/bin/bash
#
# This scripts installs necessary components
#

sudo apt update
sudo apt upgrade
sudo apt autoremove

sudo apt-get install -y python-pip
#sudo apt-get install -y python3-pip

sudo apt-get install -y python-dev
sudo apt-get install -y python-rpi.gpio

sudo pip install PyCRC