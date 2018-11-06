# AllocationSensor

_State: final_

This project shows a simple realization for an allocation sensor, which is realizable with simple means. A digital reflex light barrier is connected to a Raspberry Pi 3. The signal is processed and forwarded by means of a Python script. This allows other systems to be informed of the allocation status. The Python script runs as a systemd service and is loaded directly at startup. 

The electrical wiring diagram can be found in the doc folder.

**Schematic structure**

![Schematic structure][image-1]

** Example of realization**

![Example of realization][image-2]

## Technology

A Wenglor reflex light barrier is used as hardware for the detection of the allocation. The P1KH001 is a digital sensor based on 12 volts that can be read out via an IO port.

The signal of the sensor is read in at an IO port of the Raspberry PI and processed further. The 3.3 V or 5 V of the Raspberry is not sufficient to operate the sensor, therefore an additional 12 V power supply is required.

The signal is processed by a Python script, which reads the signal and transmits it to the server by means of a UDP telegram.

### Libraries

Python 2.x
- PyCRC (pip)
- python-dev + python-rpi.gpio (apt) or for development fakeRPiGPIO (pip)

## Scripts

The following scripts are available for easy handling of the project
- setup.sh - Installs all needed components (require sudo rights)
- start.sh - runs the services (see description for customizing service)
- test.sh - runs a test script, this scripts can read the transmitted messages
- install.sh / uninstall.sh - installs or uninstalls the systemd service

### Customize service

In order for the service to use the parameters of the corresponding environment, the scripts do not have to be individually adapted. To do this, the parameters can be passed as environment variables in the systemd service.

For setup the Server add the servername server.local in your DNS server or in /etc/hosts

Setup in global system environment, add these lines in /etc/profile (or similar)

	export SERVER_STATION=TCSAS001
	export SERVER_PORT=1112

For the system service add this to

	sudo systemctl edit allocationsensor


	[Service]
	Environment="SERVER_PORT=1112"
	Environment="SERVER_STATION=TCSAS001"

[image-1]:	doc/Design_P1KH001_v2_Plug-in_board.png "Plug-in Board"
[image-2]:	doc/Realisation_example.jpg "Example image of the connection"
