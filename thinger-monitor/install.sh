#!/bin/bash
#
# This scripts install the systemd service.
#

APP_DIR=$(pwd -P)

sudo cp src/thinger-monitor.service  /etc/systemd/system/thinger-monitor.service
sudo sed -i -e "s~##APP_DIR##~$APP_DIR~g" /etc/systemd/system/thinger-monitor.service
sudo systemctl enable thinger-monitor.service
sudo systemctl start thinger-monitor.service
