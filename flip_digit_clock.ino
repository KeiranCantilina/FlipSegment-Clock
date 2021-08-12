#include <SoftwareSerial.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>  
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include <NTPClient.h>


// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

void setup() {
  // Debug serial
  Serial.begin(115200);
  delay(10);
  Serial.println(F("Keiran's FlipDigit Clock"));
  
  // Softserial init to display modules here

  // Initialize WifiManager captive portal
  WiFiManager wifiManager;

  //Callback to function that executes right before config mode
  wifiManager.setAPCallback(configModeCallback);

  // First parameter is name of access point, second is the password
  wifiManager.autoConnect("FlipDigit_Clock", "password");
  Serial.println("WiFi connected! Yay");

  // Timeserver init stuff here

}

void loop() {
  // put your main code here, to run repeatedly:

}

// Function for handling failed wifi connections
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  // Placeholder for future callback code here (debug, maybe)
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
