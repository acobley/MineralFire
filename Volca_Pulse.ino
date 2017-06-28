#include <SoftwareSerial.h>

volatile int DivPulseCounter = 0;
boolean state[] = {false, false, false, false};
volatile boolean running =false;
int pins[] = {13, 12, 11, 10};
int DivFactors[]={1,2,1,1};
int NumberBeats[]={8,8,4,4};
volatile int CurrentFactor =0; //the element of the DivFactors Array
volatile int CurrentBeatArray=0; //how far through the current Bars we are

int CurrentDivFactor = DivFactors[CurrentFactor];
int CurrentBarsLength = NumberBeats[CurrentBeatArray];;

const byte interruptPin = 2;
const byte switchinterruptPin = 3;
const int Switch=9; // We need this connection because we can't read the interrupt pin (I think!)
SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin
char tempString[10]; //Used for sprintf

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(Switch,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), HandleClock, RISING);
  attachInterrupt(digitalPinToInterrupt(switchinterruptPin), Run, RISING); // Note only one interrupt can be attached to an input
  Serial.begin(9600);  
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  
}

void Run(){
  DivPulseCounter = 0;
  CurrentFactor=0;
  CurrentBeatArray=0;
  running = true;
  Serial7Segment.print("RRRR"); //Send serial string out the soft serial port to the S7S
  
}

void Stop(){
  running =false;
   Serial7Segment.print("5555"); //Send serial string out the soft serial port to the S7S
}

void SetPin(int pin, boolean state) {
  digitalWrite(pins[pin], state);
  
}

void HandleClock() {
  if (digitalRead(Switch) ==LOW){
     Stop();
  }
  if (running==true){
    
    int tmp=DivPulseCounter;
    sprintf(tempString, "%4d", tmp); //Convert deciSecond into a string that is right adjusted
  
    Serial7Segment.print(tempString); //Send serial string out the soft serial port to the S7S
    if (DivPulseCounter < CurrentDivFactor){
   
      
      DivPulseCounter++;
      if (DivPulseCounter >=CurrentDivFactor){\
         Pulse();
         DivPulseCounter=0;
      }
    }
      
  }
}


void Pulse() {
  
  
  int i=0;
  SetPin(0, HIGH);
  for (i=0;i<1000;i++){
    int j=i*10; //Add some delay work
  }

  SetPin(0, LOW);

}
// the loop function runs over and over again forever
void loop() {



}
