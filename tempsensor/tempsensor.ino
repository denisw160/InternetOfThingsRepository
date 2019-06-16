// Libraries for the ESP8266
#include <ESP8266WiFi.h>

// Libraries for WebServer & WiFi
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>

// Libraries for the sensor
#include <DallasTemperature.h>
#include <OneWire.h>

// Port on NodeMCU (D1) for the sensor
#define ONE_WIRE_BUS D1

// Define the server
ESP8266WebServer server(80);

// Connection to the sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Heartbeat status
boolean led = false;

// Temperature offset - to fix temperature
float offset = 0.25;


void setup(void)
{
  // Initialize Debug-Console
  Serial.begin(115200);
  Serial.println("Booting ...");

  // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // WiFiManager - local intialization.
  WiFiManager wifiManager;
  // reset saved settings - for deleting the settings
  //wifiManager.resetSettings();

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize Sensors
  sensors.begin();

  // Set the resolution to 10 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(10);
  // Confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(), DEC);

  // Associate the handler function to the path
  server.on("/", handleRequest);
  server.begin(); // Start the server
  Serial.println("Server listening");

  Serial.println("Setup completed");
}

void loop(void)
{
  // Handling of incoming requests
  server.handleClient();
  heartbeat();
}

void handleRequest() {
  // Handler for the incoming request

  // Creating rest object
  String message = "{\n";
  message += "\t\"temperature\": ";
  message += getTemperature();
  message += "\n";
  message += "}";

  // Sending to client
  server.send(200, "text/plain", message);

  // Debug
  Serial.println("");
  Serial.print("Message for client: ");
  Serial.println(message);
}

float getTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0) + offset;
}

void heartbeat() {
  if (led) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("*");
    delay(1000);
    led = false;
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    Serial.print("-");
    led = true;
  }
}
