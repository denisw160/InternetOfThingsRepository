# Raspberry monitoring for Thinger.io

_State: final_

This is an implementation of the Thinger.io Linux-Client (https://github.com/thinger-io/Linux-Client). The client submits the cpu and memory load to the Thinges-Server. This client run on a Rasperry PI 3 and give access to the system information to the IoT platfrom [thinger.io][1].

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

For setup the parameter in system environment, please use command `sudo systemctl edit thinger-monitor`and add following lines

	[Service]
	Environment="THINGER_USERID=userId"
	Environment="THINGER_DEVICEID=deviceId"
	Environment="THINGER_DEVICECREDENTIAL=password"

[1]:	http://thinger.io "thinger.io IoT Cloud Platform"