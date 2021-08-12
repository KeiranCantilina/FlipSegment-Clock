/*    1
      _
   6 | | 2
   7  - 
   5 | | 3
      -
      4
*/

#define STATUS_LED D4 // Power status LED

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);
  Serial.begin(2400);
  Serial.swap(); //Change serial TX output to alt pin D8 (GPIO15)

}

void loop() {
 // TO DO: FIX TIMING
  send_command(B1110110); // H
  delay(1000);
  blank();
  
  send_command(B1111001); // E
  delay(1000);
  blank();
  
  send_command(B0111000); // L
  delay(1000);
  blank();
  
  send_command(B0111000); // L
  delay(1000);
  blank();
  
  send_command(B0111111); // O
  delay(1000);
  blank();
  delay(1000);
}

void send_command(byte bitmask){
  byte message[] = {0x80, 0x85, 0x00, bitmask, 0x8F};
  Serial.write(message, sizeof(message));
  blinkOn();
}

void blank(){
  byte message[] = {0x80, 0x85, 0x00, 0x00, 0x8F};
  Serial.write(message, sizeof(message));
  blinkOff();
  delay(1000);
}

void blinkOn(){
  digitalWrite(STATUS_LED, LOW);
}

void blinkOff(){
  digitalWrite(STATUS_LED, HIGH);
}
