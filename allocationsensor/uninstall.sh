#!/bin/bash
#
# This scripts remove the systemd service.
#

sudo systemctl stop allocationsensor.service
sudo systemctl disable allocationsensor.service
sudo rm /etc/systemd/system/allocationsensor.service
