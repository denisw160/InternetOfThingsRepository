#!/bin/bash
#
# This scripts installs necessary components
#

sudo apt update
sudo apt upgrade
sudo apt autoremove

sudo apt-get install -y python-pip
#sudo apt-get install -y python3-pip

sudo pip install PyCRC
