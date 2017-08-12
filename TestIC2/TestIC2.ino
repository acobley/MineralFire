
#include <SoftwareSerial.h>
#include <Wire.h>
/*
 * 
 * Loops flashing the LED and output pulse.  Sends to the 7 segmentLED as well.
 * 
 * 
 * 
 */





void setup() {
  // put your setup code here, to run once:

delay(1000);
//   pinMode(8, OUTPUT);
  Wire.begin();
}

long int work;
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
/*      
long int i=0;
int k=0;
  for (k=0;k<10;k++){
  for (i = 0; i < 5000; i++) {
    work= i * k; //Add some delay work
    
  }
  }
*/    

//  digitalWrite(pin, LOW); 
delay (500);
  
}
