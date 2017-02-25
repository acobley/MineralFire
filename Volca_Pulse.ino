#include <SoftwareSerial.h>

int Counter = 0;
boolean state[] = {false, false, false, false};
int pins[] = {13, 12, 11, 10};
int BarsCount[]={3,1,2,2};
int SeqLengths[]={16,8,16,8};
int ElementCount =0; //the element of the BarsCount Array
int CurrentBar=1; //how far through the current Bars we are

int CurrentSeqLength = SeqLengths[ElementCount];
int CurrentBarsLength = BarsCount[ElementCount];;

const byte interruptPin = 2;
const byte switchinterruptPin = 3;

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin
char tempString[10]; //Used for sprintf

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), StartCount, RISING);
  Serial.begin(9600);  
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  
}



void SetPin(int pin, boolean state) {
  digitalWrite(pins[pin], state);
  
}

void StartCount() {
  Counter++;
  int maxCounter =CurrentSeqLength * CurrentBarsLength;
  int tmp =(maxCounter)*100+Counter;
  if (Counter %4 ==0)
     tmp=CurrentSeqLength *100+ CurrentBarsLength;
  
    if (Counter %8 ==0)
     tmp=ElementCount;
  
  sprintf(tempString, "%4d", tmp); //Convert deciSecond into a string that is right adjusted
  
  int brightnessLevel=64;
  
  brightnessLevel=2+(int)(((float)((float)Counter/(float)maxCounter))*(32.0));
 //Serial.print(brightnessLevel);
  Serial7Segment.write(0x7A);  // Brightness control command
  Serial7Segment.write((byte) brightnessLevel);  // 0 is dimmest, 255 is brightest
  Serial7Segment.print(tempString); //Send serial string out the soft serial port to the S7S

  if (Counter >= (maxCounter )) {
    Pulse();
    Counter = 0;
    CurrentBar++;
    
      ElementCount++;
      if (ElementCount >3)
         ElementCount=0;
      CurrentBar=1;
      CurrentBarsLength=BarsCount[ElementCount];
      CurrentSeqLength = SeqLengths[ElementCount];
    
    
  }
}


void Pulse() {
  
  
  int i=0;
  SetPin(0, HIGH);
  for (i=0;i<1000;i++){
    int j=i*10;
  }

  SetPin(0, LOW);

}
// the loop function runs over and over again forever
void loop() {



}
