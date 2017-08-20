/*
 * 
 * Tests the gate in interupt is working, and sends a pulse to the output
 * 
 * 
 * 
 */

#include <Wire.h>


const byte GateInInterrupt = 2;
const byte GateOut=8;

void setup() {
  // put your setup code here, to run once:
  pinMode(GateOut,OUTPUT);
   attachInterrupt(digitalPinToInterrupt(GateInInterrupt), HandleClock, RISING);
   Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
}

void HandleClock() {
  Pulse();
}

void SetPin(boolean state) {
  

}
volatile long int work;
boolean state=LOW;
byte v=0;

void Pulse() {

int pin= GateOut;
   digitalWrite(pin, HIGH);  

      Wire.beginTransmission(8);
   Wire.write(v); 
   Wire.write(v);
   Wire.write(v);
   Wire.write(v);
   Wire.endTransmission();
   v++;
   if (v>9)
      v=0;
long int i=0;
int k=0;
  for (k=0;k<10;k++){
  for (i = 0; i < 100; i++) {
    work= i * k; //Add some delay work
  }
  }
 digitalWrite(pin, LOW);  

}
