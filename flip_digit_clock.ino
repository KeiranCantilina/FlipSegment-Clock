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
WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "us.pool.ntp.org", 0, 60000); // UTC Time

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
  Serial.println("Current timestamp is: " + current_timestamp() + "\n");
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

// Get NTP time and convert to timestamp
String current_timestamp(){
  time_t utcCalc = timeClient.getEpochTime();
  return String(hour(utcCalc)) + ":" + String(minute(utcCalc)) + ":" + String(second(utcCalc)) + " UTC on " + String(day(utcCalc)) + " " + monthString(month(utcCalc)) + " " + String(year(utcCalc));
}

// Convert integer month to word month
String monthString(int monthInt){
  String monthStringArray[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  for (int i = 1; i<13; i++){
    if(monthInt == i){
      return monthStringArray[i-1];
    }
  }
  return "MONTH ERROR";
}

int get_HourOnesPlace(){
  
}

int get_HourTensPlace(){
  
}

int get_MinutesOnesPlace(){
  
}

int get_MinutesTensPlace(){
  
}

byte numberToDigitPattern(int number){
  
}
