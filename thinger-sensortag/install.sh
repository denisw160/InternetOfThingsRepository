#!/bin/bash
#
# This scripts install the systemd service.
#

sudo cp src/thinger-sensortag.service  /etc/systemd/system/thinger-sensortag.service
sudo systemctl enable thinger-sensortag.service
sudo systemctl start thinger-sensortag.service
