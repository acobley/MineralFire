
#include <SoftwareSerial.h>
#include <Wire.h>
/*
 * 
 * Loops flashing the LED and output pulse.  Sends to the 7 segmentLED as well.
 * 
 * 
 * 
 */
 const byte GateInInterrupt = 2;
const byte GateIn = 9; //The input LED
const byte GateOut = 8;
void setup() {


delay(1000);
   pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
     attachInterrupt(digitalPinToInterrupt(GateInInterrupt), HandleClock, FALLING);


  Wire.begin();
}


byte v=0;
void loop() {
  // put your main code here, to run repeatedly:
 // int pin=8;
  
 //  digitalWrite(pin, HIGH);  
   Wire.beginTransmission(8);
   Wire.write(v); 
   Wire.write(v);
   Wire.write(v);
   Wire.write(v);
   Wire.endTransmission();
   v++;
   if (v>9)
      v=0;

  

//  digitalWrite(pin, LOW); 

  
}

void HandleClock() {
  Pulse();
}

volatile long int work;

void Pulse() {


  digitalWrite(GateOut, HIGH);
  digitalWrite(GateIn, HIGH);

   long int i = 0;
  int k = 0;
  for (k = 0; k < 10; k++) {
    for (i = 0; i < 100; i++) {
      work = i * k; //Add some delay work

    }
  }

  
  digitalWrite(GateOut, LOW);
  digitalWrite(GateIn, LOW);

}
