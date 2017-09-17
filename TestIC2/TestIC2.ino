
#include <SoftwareSerial.h>
#include <Wire.h>
/*
   Loops flashing the LED and output pulse.  Sends to the 7 segmentLED as well.
*/
const byte GateInInterrupt = 2;
const byte GateIn = 9; //The input LED
const byte GateOut = 8;
void setup() {


  delay(2000);
  pinMode(GateIn, OUTPUT);
  pinMode(GateOut, OUTPUT);
  Wire.begin();
}



byte packDigit(byte Digit, byte Number) {
  byte pDigit = (byte)((Digit << 6) | Number);
  return pDigit;
}

byte v = 0;
void loop() {


  for (byte i = 0; i < 4; i++) {
    Wire.beginTransmission(8);
    if ((v-i)>=0){
       Wire.write(packDigit(i, v-i));}
    else{
      Wire.write(packDigit(i, 63));
    }
    Wire.endTransmission();
  }

  v++;
  if (v > 15)
    v = 0;

  Pulse();

}


volatile long int work;

void Pulse() {


  digitalWrite(GateOut, HIGH);
  digitalWrite(GateIn, HIGH);

  delay(500);


  digitalWrite(GateOut, LOW);
  digitalWrite(GateIn, LOW);
  delay(500);

}
