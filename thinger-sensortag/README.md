# Sensortag for Thinger.io

This is an implementation of the Thinger.io Linux-Client (https://github.com/thinger-io/Linux-Client). This client run on a Rasperry PI 3 and connect multiple TI Sensortags via Bluetooth to the IoT platfrom [thinger.io](http://thinger.io "thinger.io IoT Cloud Platform").

For the connection the python script Sensortag from IBM is used. You found it also in this repository.

The client is still in development.


## Quickstart
 
Setup your username, device, and device credentials in the file ```src/main.cpp```. Then you can start the client with ```./run.sh```, that will compile, start and run the thinger.io client.
  
## Notes for compiling on Raspberry Pi

- Check the compiler version and install a newer compiler if necessary. At least GCC 4.8.2.
- Install CMake ```sudo apt-get install cmake```
- Install Open SSL Libraries (not required but useful for secured connection) ```sudo apt-get install libssl-dev```
