# LED-Matrix (for Text-Messages)

_State: beta_

I started this project because I would like to receive (text) notifications directly in my apartment. For this I was looking for a small solution how to display text content directly. For this I built myself a small LED bar 32x24 that can receive content via HTTP-Post. In the background Node-RED processes the events and sends appropriate texts to the LED matrix.

Technically, an ESP8266 is used to control the LED matrix panels (MAX7219). The ESP is connected via WiFi. The original source code and idea of the project comes from a [blog entry][1] of bastelgarage.ch.

![LED matrix][image-1]

In order not to encode the WLAN access data hard in the source code, I use the WiFiManager from [Tzapu][2] in this project. This makes it easy to configure the LED matrix. A sample for the integration can found on [GitHub][3].

## Quickstart

For the ArduinoIDE an additional library is needed. This library "arduino-Max72xxPanel" can be downloaded [here][4]. The other dependencies are loaded via the library manager. 
Load the [source code][5] in the Arduino IDE and update your ESP8266. 

## Connecting the MAX7219

The LED matrix modules are connected in series and connected to the ESP8266.
The connections are as follows:

| LED matrix  | ESP8266 NodeMCU  |
| ----------- | ---------------- |
| VCC         | 5V (VUSB!)       | 
| GND         | GND              |
| DIN         | D7 (GPIO13)      |
| CS          | D8 (GPIO15)      |
| CLK         | D5 (GPIO14)      |

Graphically, it looks like this:

![Plug-in board][image-2]

The construction can be found in the [fritzing file][6].

[1]:	https://www.bastelgarage.ch/index.php?route=extension/d_blog_module/post&post_id=6
[2]:	https://github.com/tzapu/WiFiManager
[3]:	https://github.com/tzapu/WiFiManager/blob/master/examples/AutoConnect/AutoConnect.ino
[4]:	https://github.com/markruys/arduino-Max72xxPanel 
[5]:	TempsensorRest_v2.ino
[6]:	doc/led-matrix.fzz "Fritzing file for the LED-Matrix"

[image-1]:	doc/led-matrix.jpg "LED matrix"
[image-2]:	doc/led-matrix_plug-in_board.png "Plug-in board"
