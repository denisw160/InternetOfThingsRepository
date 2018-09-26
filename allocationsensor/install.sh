#!/bin/bash
#
# This scripts install the systemd service.
#

APP_DIR=$(pwd -P)

sudo cp src/allocationsensor.service  /etc/systemd/system/allocationsensor.service
sudo sed -i -e "s~##APP_DIR##~$APP_DIR~g" /etc/systemd/system/allocationsensor.service
sudo systemctl enable allocationsensor.service
sudo systemctl start allocationsensor.service
