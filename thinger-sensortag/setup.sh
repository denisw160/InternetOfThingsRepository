#!/bin/bash
#
# This scripts installs necessary components
#

sudo apt update
sudo apt upgrade
sudo apt autoremove

sudo apt-get install -y cmake
sudo apt-get install -y libssl-dev
sudo apt-get install -y libglib2.0-dev

sudo apt-get install -y python
sudo apt-get install -y python-pip

sudo pip install bluepy
