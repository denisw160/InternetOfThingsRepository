#!/bin/bash
#
# This scripts installs necessary components
#

sudo apt update
sudo apt upgrade
sudo apt autoremove

sudo apt-get install python-pip
#sudo apt-get install python3-pip

sudo pip install PyCRC
