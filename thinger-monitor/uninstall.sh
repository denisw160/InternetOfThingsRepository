#!/bin/bash
#
# This scripts remove the systemd service.
#

sudo systemctl stop thinger-monitor.service
sudo systemctl disable thinger-monitor.service
sudo rm /etc/systemd/system/thinger-monitor.service
