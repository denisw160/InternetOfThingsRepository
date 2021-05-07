/*
 *******************************************************************************************
 ** LED-Matrix                                                                            **
 **                                                                                       **
 ** Program to control multiple dot matrix modules with MAX7219 driver.                   **
 **                                                                                       **
 **                                                                                       **
 ** The ESP8266 is integrated into the WLAN via WiFi. The message and additional settings **
 ** can be configured via the website (http). The message is displayed in ticker.         **
 **                                                                                       **
 ** The program is designed and tested for an ESP8266. For the controlling of the dot     **
 ** matrix display two libraries have to be installed:                                    **
 **  - https://github.com/markruys/arduino-Max72xxPanel                                   **
 **  - https://github.com/adafruit/Adafruit-GFX-Library                                   **
 **                                                                                       **
 ** In addition, the WiFiManager is required:                                             **
 **  - https://github.com/tzapu/WiFiManager                                               **
 **                                                                                       **
 ** Open issues / tasks                                                                   **
 **  - add icons / graphics                                                               **
 **  - add different displayTypes                                                         **
 **                                                                                       **
 ** Autor: Denis Wirries                                                                  **
 ** Datum: May 2021                                                                       **
 ** Version: 1.0                                                                          **
 * *****************************************************************************************
*/

/************************( Import )********************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>      // Use ESP8266 web server for update
#include <ESP8266mDNS.h>           // Include the mDNS library

#include <WiFiManager.h>           // Include the WiFi Manager for WiFi configuration

#include <SPI.h>                   // Include SPI for communication
#include <Adafruit_GFX.h>          // Character fonts
#include <Max72xxPanel.h>          // Control of the MAX7219 driver

#include "HtmlPage.h"              // H-File with HTML page as string (var htmlPage)

/************************( Global constants )*********************************************/
// Connecting the dot matrix modules (MAX7219)
// MAX7219:          ESP8266 NodeMCU:
// VCC               5V (VUSB)
// GND               GND
// DIN               D7 (GPIO13)
// CS                D8 (GPIO15)
// CLK               D5 (GPIO14)

const int pinLED                     = 2;     // LED-PIN (NodeMCU v3 Lolin)
const int pinCS                      = 15;    // CS-PIN / D8 / GPIO15
const int numberOfHorizontalDisplays = 4;     // Number of horizontal modules
const int numberOfVerticalDisplays   = 3;     // Number of vertical modules
const int httpPort                   = 80;    // Port number of the web server (http)
const int spacer                     = 1;     // Space length

/************************( Initialize libraries )*****************************************/
// Start web server with the HTML page fron "HtmlPage.h".
ESP8266WebServer server(httpPort);

// Setup dot matrix
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

/************************( Global variables with defaults )********************************/
String text         = "LED MATRIX ";            // Initial text for display
String displayType  = "scrolling";              // Default type for display (not yet implemented)
int fontSize        = 2;                        // Size factor for font
int width           = (5 + spacer) * fontSize;  // Font length is 5 pixels
int speed           = 50;                       // Time in ms for scroll
int brightness      = 0;                        // Default brightness (0 to 15)

/************************( Setup )*********************************************************/
void setup() {
  // Initialize the LED_BUILTIN pin as an output
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, HIGH);

  // Wait after power on
  delay(2000);
  digitalWrite(pinLED, LOW);

  // Initialize Debug-Console
  Serial.begin(115200);
  Serial.println();

  // Initialize WiFi with WiFiManager
  // explicitly set mode, esp defaults to STA+AP
  WiFi.mode(WIFI_STA);
  WiFiManager wm;

  // Reset settings - wipe credentials for testing
  //wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point
  if (! wm.autoConnect()) {
    Serial.println("Error setting up WiFiManager!");
    haltOnError();
  }
  Serial.println("WiFiManager started");

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Update inital text with current IP
  text = text + WiFi.localIP().toString();

  // Set up mDNS responder:
  // - first argument is the host name
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    haltOnError();
  }
  Serial.println("mDNS responder started");

  // Activate web server and register url
  server.on("/", HTTP_GET, handleRoot);
  server.on("/update", HTTP_POST, handleUpdate);
  server.onNotFound(handleNotFound);
  server.begin();

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);

  // Configure dot matrix modules
  matrix.setIntensity(brightness);

  // Correct rotation
  matrix.setRotation(0, 1);
  matrix.setRotation(1, 1);
  matrix.setRotation(2, 1);
  matrix.setRotation(3, 1);
  matrix.setRotation(4, 1);
  matrix.setRotation(5, 1);
  matrix.setRotation(6, 1);
  matrix.setRotation(7, 1);
  matrix.setRotation(8, 1);
  matrix.setRotation(9, 1);
  matrix.setRotation(10, 1);
  matrix.setRotation(11, 1);

  // Test display
  matrix.fillScreen(HIGH);
  matrix.write();

  delay(2000);
  digitalWrite(pinLED, HIGH);
  Serial.println("Setup completed");
}

void haltOnError() {
  while (1) {
    digitalWrite(pinLED, HIGH);
    delay(1000);
    digitalWrite(pinLED, LOW);
    delay(1000);
  }
}

/************************( Show HTML page )************************************************/
void handleRoot() {
  server.send(200, "text/html", rootPage);
}

/************************( Update parameter )***********************************************/
void handleUpdate() {
  // Update parameter with incoming data
  if (server.hasArg("text") && server.arg("text").length() != 0) {
    Serial.println("Updating from client received");
    text = server.arg("text");
    Serial.print("text: "); Serial.println(text);

    if (server.hasArg("displayType")) {
      displayType = server.arg("displayType");
      Serial.print("displayType: "); Serial.println(displayType);
    }
    if (server.hasArg("fontSize")) {
      Serial.print("fontSize: "); Serial.println(server.arg("fontSize"));
      fontSize = server.arg("fontSize").toInt();
      width = (5 + spacer) * fontSize;

    }
    if (server.hasArg("speed")) {
      Serial.print("speed: "); Serial.println(server.arg("speed"));
      speed = server.arg("speed").toInt();
    }
    if (server.hasArg("brightness")) {
      Serial.print("brightness: "); Serial.println(server.arg("brightness"));
      brightness = server.arg("brightness").toInt();
      matrix.setIntensity(brightness);
    }

    Serial.println("Update completed");
    server.send(200, "text/html", successPage);

  } else {
    server.send(400, "text/html", failedPage);
  }
}

/************************( Show not found )************************************************/
void handleNotFound() {
  // Send HTTP status 404 (Not Found)
  server.send(404, "text/html", notFoundPage);
}

void handleNetwork() {
  // Advertise the service via mDNS
  MDNS.update();
  // Check for new incoming data
  server.handleClient();
}

/************************( Function for scrolling the text )*******************************/
void scrolling() {
  // Iterate over the text
  for (int i = 0; i < width * text.length() + matrix.width() - 1 - spacer; i++) {
    // Clear screen
    matrix.fillScreen(LOW);

    // Center text on screen
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - (7 * fontSize)) / 2;

    int letter = i / width;
    while (x + width - spacer >= 0 && letter >= 0) {
      if (letter < text.length()) {
        // Draw letter
        matrix.drawChar(x, y, text[letter], HIGH, LOW, fontSize);
        // Response to clients
        handleNetwork();
      }
      letter--;
      x -= width;
    }

    // Update display ant wait
    matrix.write();
    delay(speed);
  }
}

/************************( Main loop )*****************************************************/
void loop() {
  // Response to clients
  handleNetwork();

  // TODO implement different displayTypes
  scrolling();
}
