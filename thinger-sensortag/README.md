# Sensortag for Thinger.io

_State: final_

This is an implementation of the Thinger.io Linux-Client (https://github.com/thinger-io/Linux-Client). This client run on a Rasperry PI 3 and connect multiple TI Sensortags via Bluetooth to the IoT platfrom [thinger.io][1].

For the connection the python script Sensortag from IBM is used. You found it also in this repository.

## Quickstart
 
Setup your username, device, and device credentials in the file `run.sh`. Then you can start the client with `./run.sh`, that will compile, start and run the thinger.io client.
  
## Notes for compiling on Raspberry Pi

- Check the compiler version and install a newer compiler if necessary. At least GCC 4.8.2.
- Install CMake `sudo apt-get install cmake`
- Install Open SSL Libraries (not required but useful for secured connection) `sudo apt-get install libssl-dev`

Use can you the `setup.sh` to install the compile dependencies.

## Run as systemd service

The client can also be operated as a systemd service. Just use the scripts `install.sh` or `uninstall.sh`.

For setup a local server for Thinger.io add the servername iot.thinger.io in your DNS server or in `/etc/hosts`.

For setup the parameter in system environment, please use command `sudo systemctl edit thinger-sensortag`and add following lines

	[Service]
	Environment="THINGER_USERID=userId"
	Environment="THINGER_DEVICEID=deviceId"
	Environment="THINGER_DEVICECREDENTIAL=password"
	Environment="THINGER_SENSORTAGS=C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow B0:91:22:F6:CF:87=sensorViolet 54:6C:0E:4D:CC:02=sensorBlue 54:6C:0E:4D:5E:80=sensorOrange B0:91:22:F6:E6:02=sensorGreen"

[1]:	http://thinger.io "thinger.io IoT Cloud Platform"