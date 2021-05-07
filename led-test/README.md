# LED-Test

_State: final_

This script was created to test the status-hat. I use the status-hat for my test projects in order to have visual output possibilities (LED) in addition to the connection of sensors. 

![An extension for the Raspberry Pi][image-1]

Since the Raspberry Pis usually run without display or console, the LEDs show different states of the programs. Additionally there is a switch to send input to the programs.

The test script checks the LEDs and the switch. 

![Plug-in board of the Status-Hat][image-2]

The electrical wiring diagram can be found in the doc folder.

## Technology

The script for testing is implemented in Python 2.x.

### Libraries

Python 2.x
- python-dev + python-rpi.gpio (apt) or for development fakeRPiGPIO (pip)

## Scripts

The following scripts are available for easy handling of the project
- setup.sh - Installs all needed components (require sudo rights)
- start.sh - runs the services (see description for customizing service)

[image-1]:	doc/Status-Hat.jpg "Status-Hat"
[image-2]:	doc/Status-Hat_Plug-in_board.png "Plug-in board"