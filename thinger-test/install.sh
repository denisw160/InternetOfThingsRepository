#!/bin/bash
#
# This scripts install the systemd service.
#

APP_DIR=$(pwd -P)

sudo cp src/thinger-test.service  /etc/systemd/system/thinger-test.service
sudo sed -i -e "s~##APP_DIR##~$APP_DIR~g" /etc/systemd/system/thinger-test.service
sudo systemctl enable thinger-test.service
sudo systemctl start thinger-test.service
