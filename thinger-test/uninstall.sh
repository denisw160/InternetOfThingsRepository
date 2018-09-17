#!/bin/bash
#
# This scripts remove the systemd service.
#

sudo systemctl stop thinger-test.service
sudo systemctl disable thinger-test.service
sudo rm /etc/systemd/system/thinger-test.service
