#!/bin/bash
#
# This scripts remove the systemd service.
#

sudo systemctl stop thinger-sensortag.service
sudo systemctl disable thinger-sensortag.service
sudo rm /etc/systemd/system/thinger-sensortag.service
