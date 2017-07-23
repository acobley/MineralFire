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

const int TXpin=9;

SoftwareSerial Serial7Segment(10, TXpin); //RX pin, TX pin
char tempString[10]; //Used for sprintf

void setup() {
  // put your setup code here, to run once:
  byte num=A[2][3];

   pinMode(8, OUTPUT);
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  Serial7Segment.print("H_H_"); //Send serial string out the soft serial port to the S7S

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
   Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  Serial7Segment.print("H_H_"); //Send serial string out the soft serial port to the S7S

  digitalWrite(pin, LOW); 
 
  delay(180);   
}
