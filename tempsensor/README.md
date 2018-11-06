# TempSensor (for Homekit)

_State: final_

This project was created because I wanted to measure the temperature in my aquarium but could not buy a waterproof sensor. Therefore I combined an ESP8266 with a digital temperature sensor [DS18B20][1]. 

![An ESP8266 based sensor for HomeKit][image-1]

The ESP8266 connects to my WLAN and returns the temperature value via a simple REST service.

In order not to encode the WLAN access data hard in the source code, I use the WiFiManager from [Tzapu][2] in this project. This makes it easy to configure the sensor. A sample for the integration can found on [GitHub][3].

![][image-2]

To retrieve the temperature you can simply enter the IP address of the sensor in the browser. Since this is not a "nice" UI, I have integrated the sensor into my Apple HomeKit app. For this the [Homebridge][4] (very great project!) is used with [HTTP-Temperature][5]. A manual for installing Homebridge on a Raspberry can found [here][6].

## Quickstart

Load the [source code][7] in the Arduino IDE and update your ESP8266. 

## Connecting the DS18B20

Connecting the digital temperature sensor is very simple. On the plug-in board, the sensor is simply connected to the power supply from the ESP8266 and the data line to a GPIO port.

![Plug-in board][image-3]

The circuit diagram looks as follows

![Wiring diagram][image-4]

Both can be found in the [fritzing file][8].

[1]:	https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806
[2]:	https://github.com/tzapu/WiFiManager
[3]:	https://github.com/tzapu/WiFiManager/blob/master/examples/AutoConnect/AutoConnect.ino
[4]:	https://github.com/nfarina/homebridge
[5]:	https://www.npmjs.com/package/homebridge-http-temperature
[6]:	https://github.com/nfarina/homebridge/wiki/Running-HomeBridge-on-a-Raspberry-Pi
[7]:	TempsensorRest_v2.ino
[8]:	doc/Tempsensor.fzz "Fritzing file for the TempSensor"

[image-1]:	doc/Tempsensor.jpg "Temperature Sensor"
[image-2]:	doc/Tempsensor_open.jpg "Wiring"
[image-3]:	doc/Tempsensor_Plug-in_board.png "Plug-in board"
[image-4]:	doc/Tempsensor_Wiring_diagram.png "Wiring diagram"