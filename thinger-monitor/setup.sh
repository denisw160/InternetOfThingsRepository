#!/bin/bash
#
# This scripts installs necessary components
#

sudo apt update
sudo apt upgrade
sudo apt autoremove

sudo apt-get install -y cmake
sudo apt-get install -y libssl-dev
