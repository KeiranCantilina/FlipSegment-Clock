// TODO: Figure out how to handle setting time manually, and/or how to handle loss of wifi/connection to time servers

// Libraries
#include <SoftwareSerial.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>  
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include <NTPClient.h>

// Software serial pins for comms with display modules
#define DEVICE_0 12
#define DEVICE_1 13
#define DEVICE_1 13
#define DEVICE_1 13

// Pins for spoofing display modules buttons
#define BUTTON1PIN 13
#define BUTTON2PIN 14

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "us.pool.ntp.org", 0, 60000); // UTC Time

void setup() {
  
  // Init button spoofing pins ("on" might be high or low, gotta test. Should be initialized to off)
  pinMode(BUTTON1PIN, OUTPUT);
  pinMode(BUTTON2PIN, OUTPUT);
  digitalWrite(BUTTON1PIN, HIGH);
  digitalWrite(BUTTON2PIN, HIGH);
  
  // Debug serial
  Serial.begin(115200);
  delay(10);
  Serial.println(F("Keiran's FlipDigit Clock"));
  
  // Softserial init to display modules here
  // Hours 10s digit module serial init (device 0)
  // Hours 1s digit module serial init (device 1)
  // Minutes 10s digit module serial init (device 2)
  // Minutes 1s digit module serial init (device 3)

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

byte numberToSegmentPattern(int number){
/*    1
      _
   6 | | 2
   7  - 
   5 | | 3
      -
      4
*/
  switch (number%10){
    case 0:
      return B0111111;
    case 1:
      return B0000110;
    case 2:
      return B1011011;
    case 3:
      return B1001111;
    case 4:
      return B1100110;
    case 5:
      return B1101101;
    case 6:
      return B1111101;
    case 7:
      return B0000111;
    case 8:
      return B1111111;
    case 9:
      return B1100111;
    default:
      return B0000000;
  }
}

void initializeDisplayModule(){
  // May be possible to have all button1s and all button2s on every module connected together

  // Hold both buttons down for 2 seconds to enter mode change mode
  digitalWrite(BUTTON1PIN, LOW);
  digitalWrite(BUTTON2PIN, LOW);
  delay(2000);
  digitalWrite(BUTTON1PIN, HIGH);
  digitalWrite(BUTTON2PIN, HIGH);
  delay(1000);

  // Press button 2 until module is in external control mode (mode 7)
  for (int i=1, i<7, i++){
    digitalWrite(BUTTON2PIN, LOW);
    delay(100);
    digitalWrite(BUTTON2PIN, HIGH);
    delay(1000);
  }

  // Press button 1 to leave mode change mode
  digitalWrite(BUTTON1PIN, LOW);
  delay(100);
  digitalWrite(BUTTON1PIN, HIGH);
  delay(1000);
}

void blank_display(int device_number){
  switch (device_number){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    default:
      break;
  }
}
