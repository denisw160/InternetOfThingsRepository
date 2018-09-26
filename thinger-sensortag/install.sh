#!/bin/bash
#
# This scripts install the systemd service.
#

APP_DIR=$(pwd -P)

sudo cp src/thinger-sensortag.service  /etc/systemd/system/thinger-sensortag.service
sudo sed -i -e "s~##APP_DIR##~$APP_DIR~g" /etc/systemd/system/thinger-sensortag.service
sudo systemctl enable thinger-sensortag.service
sudo systemctl start thinger-sensortag.service
