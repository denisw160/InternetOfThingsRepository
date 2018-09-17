#!/bin/bash
#
# This scripts install the systemd service.
#

sudo cp src/thinger-test.service  /etc/systemd/system/thinger-test.service
sudo systemctl enable thinger-test.service
sudo systemctl start thinger-test.service
