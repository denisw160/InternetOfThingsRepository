#!/bin/bash
#
# This scripts install the systemd service.
#

sudo cp src/allocationsensor.service  /etc/systemd/system/allocationsensor.service
sudo systemctl enable allocationsensor.service
sudo systemctl start allocationsensor.service
