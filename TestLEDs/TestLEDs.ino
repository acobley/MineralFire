
#include <SoftwareSerial.h>
/*
 * 
 * Loops flashing the LED and output pulse.  Sends to the 7 segmentLED as well.
 * 
 * 
 * 
 */
byte A [2][4]{{1,2,3,4},
           {2,3,4,5}};




void setup() {
  // put your setup code here, to run once:
  byte num=A[2][3];

   pinMode(8, OUTPUT);

}

long int work;
void loop() {
  // put your main code here, to run repeatedly:
  int pin=8;
  
   digitalWrite(pin, HIGH);  
long int i=0;
int k=0;
  for (k=0;k<10;k++){
  for (i = 0; i < 1000; i++) {
    work= i * k; //Add some delay work
    
  }
  }
  //delay(1);  

  digitalWrite(pin, LOW); 
 
  delay(180);   
}
