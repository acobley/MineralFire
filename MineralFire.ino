#include <SoftwareSerial.h>

volatile byte DivPulseCounter = 0;
volatile byte NumPulseCounter = 0;
boolean state[] = {false, false, false, false};
volatile boolean running = false;

byte SwitchConvert[] = {1, 3, 2}; //We use this to convert from the numbers the switch puts out to a sensible


int DivFactors[3][4] = {{4, 4, 2, 1},
  {4, 2, 4, 2},
  {3, 5, 3, 7}
};
int NumberPulses[3][4] = {{8, 8, 4, 8},
  {32, 16, 8, 16},
  {9, 10, 9, 14}
};

byte DivSwitch = 0; //Used to set the pattern by the switches
byte PulseSwitch = 0;
byte ModeSwitch=1;

volatile byte CurrentPtr = 0; //how far through the current Bars we are

byte CurrentDivFactor = DivFactors[DivSwitch][CurrentPtr];
byte CurrentPulseLength = NumberPulses[PulseSwitch][CurrentPtr];

const byte GateOut=8;
const byte GateInInterrupt = 2;
const byte switchinterruptPin = 3;

const int SW11 = 4; //These define the two switches for selecting patterns
const int SW12 = 5;
const int SW21 = 7;
const int SW22 = 6;
const int SW31= A0;
const int SW32 = A1; 

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin
char tempString[10]; //Used for sprintf

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(GateOut,OUTPUT);

  pinMode(SW11, INPUT);
  pinMode(SW12, INPUT);
  pinMode(SW21, INPUT);
  pinMode(SW22, INPUT);
  pinMode(SW31, INPUT);
  pinMode(SW32, INPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(GateInInterrupt), HandleClock, RISING);
  attachInterrupt(digitalPinToInterrupt(switchinterruptPin), Run, RISING); // Note only one interrupt can be attached to an input
  Serial.begin(9600);
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  Serial7Segment.print("H_H_"); //Send serial string out the soft serial port to the S7S
 
  running =false;
}
unsigned long oldtime=0;
const unsigned long bouncedelay =500UL; 
void Run() {

  if (oldtime==0){
    oldtime=millis();
    return;
    }
  unsigned long newtime=millis();
  if ((newtime -oldtime) <bouncedelay){
    oldtime=newtime;
    return;
  }
   oldtime=0;
  if (running == false) {
    DivPulseCounter = 0;
    NumPulseCounter = 0;
    running = true;
    CurrentDivFactor = DivFactors[DivSwitch][CurrentPtr];
    CurrentPulseLength = NumberPulses[PulseSwitch][CurrentPtr];
    Serial7Segment.print("R_R_"); //Send serial string out the soft serial port to the S7S
  } else {
    running = false;
  }
  
}



void SetPin(boolean state) {
  digitalWrite(GateOut, state);

}


void DisplayNumbers(byte A, byte B, byte C, byte  D) {
  char c4 = ' ';
  char c3 = ' ';
  char c2 = ' ';
  char c1 = ' ';
  if (A < 100){ //NUmbers greater than 100 are blank for convienience
    if (A<=9)
       c4 = '0' + A;
    else 
       c4= 'A'+(A-10);
  }
  if (B < 100){
    if (B<=9)
       c3 = '0' + B;
    else 
       c3= 'A'+(B-10);

  }  
  if (C < 100){
    if (C<=9)
       c2 = '0' + C;
    else 
       c2= 'A'+(C-10);
  }
  if (D < 100){
    if (D<=9)
       c1 = '0' + D;
    else 
       c1= 'A'+(D-10);
  }


  tempString[0] = c4;
  tempString[1] = c3;
  tempString[2] = c2;
  tempString[3] = c1;
  tempString[4] = '\0';
  Serial7Segment.print(tempString);
  //  Serial.println(tempString);
}


void ReadPatternSwitches() {
  byte cSW11 = 1;
  byte cSW12 = 1;
  byte cSW21 = 1;
  byte cSW22 = 1;
  byte cSW31 = 1;
  byte cSW32 =1;
  if (digitalRead(SW11) == LOW) {
    cSW11 = 0;
  }
  if (digitalRead(SW12) == LOW) {
    cSW12 = 0;
  }

  if (digitalRead(SW21) == LOW) {
    cSW21 = 0;
  }
  if (digitalRead(SW22) == LOW) {
    cSW22 = 0;
  }

  if (digitalRead(SW31) == LOW) {
    cSW31 = 0;
  }
  if (digitalRead(SW32) == LOW) {
    cSW32 = 0;
  }
  byte SW1 = 2 * cSW12 + cSW11;
  SW1 = SwitchConvert[SW1 - 1];
  byte SW2 = 2 * cSW21 + cSW22;
  SW2 = SwitchConvert[SW2 - 1];
  byte SW3 =  2 * cSW31 + cSW32;
  DivSwitch = SW1 - 1;
  PulseSwitch = SW2 - 1;
  ModeSwitch=SW3;

  if (running == false) {
    DisplayNumbers(SW3, SW2, 110, SW1);
  }
}

void HandleClock() {
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  ReadPatternSwitches();
 
  if (running == true) {

    DisplayNumbers(CurrentPtr, CurrentPulseLength, CurrentDivFactor, DivPulseCounter);
    if (DivPulseCounter < CurrentDivFactor) {


      DivPulseCounter++;
      if (DivPulseCounter >= CurrentDivFactor) {
        Pulse();
        DivPulseCounter = 0;
      }
    }
    byte endCon=CurrentPulseLength;
    if (ModeSwitch==2){
      endCon=CurrentPulseLength*CurrentDivFactor;
    }
    if (NumPulseCounter < endCon) {
      NumPulseCounter++;
      if (NumPulseCounter >= endCon) {
        NumPulseCounter = 0;
        CurrentPtr++;
        if (CurrentPtr < 4) {
          CurrentDivFactor = DivFactors[DivSwitch][CurrentPtr];
          CurrentPulseLength = NumberPulses[PulseSwitch][CurrentPtr];
        } else {
          CurrentPtr = 0;
          CurrentDivFactor = DivFactors[DivSwitch][CurrentPtr];
          CurrentPulseLength = NumberPulses[PulseSwitch][CurrentPtr];
        }

      }
    }
  }
}


void Pulse() {


  int i = 0;
  SetPin( HIGH);
  for (i = 0; i < 1000; i++) {
    int j = i * 10; //Add some delay work
  }

  SetPin( LOW);

}
// the loop function runs over and over again forever
void loop() {




}
