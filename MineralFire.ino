
#include <Wire.h>

volatile byte DivPulseCounter = 0;
volatile byte NumPulseCounter = 0;
boolean state[] = {false, false, false, false};
volatile boolean running = false;

byte SwitchConvert[] = {1, 3, 2}; //We use this to convert from the numbers the switch puts out to the correct number


int DivFactors[3][8] = {{4, 4, 2, 1,4, 4, 2, 1},
  {2, 1, 4, 2,4, 2, 4, 1},
  {3, 5, 3, 7,3, 5, 3, 7}
};
int NumberPulses[3][8] = {{8, 8, 4, 8,8, 8, 4, 8},
  {2, 2, 4, 16,32, 16, 8, 16},
  {9, 10, 9, 14,9, 10, 9, 14}
};

int DataLength=8;

int Divider1[]={1,2,3}; //Adjusted for the logic of the switches
int Divider2[]={1,2,4};
int Divider=1;

int Div1=1;
int Div2=1;

byte DivSwitch = 0; //Used to set the pattern by the switches
byte PulseSwitch = 0;
byte ModeSwitch=1;

volatile byte CurrentPtr = 0; //how far through the current Bars we are

byte CurrentDivFactor = DivFactors[DivSwitch][CurrentPtr];
byte CurrentPulseLength = NumberPulses[PulseSwitch][CurrentPtr];

const byte InputLED=9;
const byte GateOut=8;
const byte interruptPin = 2;
const byte switchinterruptPin = 3;

const int SW11 = 4; //These define the two switches for selecting patterns
const int SW12 = 5;
const int SW21 = 7;
const int SW22 = 6;
const int SW31= A0;
const int SW32 = A1; 

long IntMillis =0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.

  pinMode(InputLED, OUTPUT);
  pinMode(GateOut, OUTPUT);
  pinMode(SW11, INPUT);
  pinMode(SW12, INPUT);
  pinMode(SW21, INPUT);
  pinMode(SW22, INPUT);
  pinMode(SW31, INPUT);
  pinMode(SW32, INPUT);
  
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), HandleClock, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchinterruptPin), Run, FALLING); // Note only one interrupt can be attached to an input
Wire.begin();

   
  IntMillis=millis();
  running =false;
}
unsigned long oldtime=0;
const unsigned long bouncedelay =50UL; 


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
//Send to IC2
} else {
    running = false;
  }
 
}



void DisplayNumbers(byte A, byte B, byte C, byte  D) {
//Send to IC2
Wire.beginTransmission(8);
   Wire.write(A); 
   Wire.write(B);
   Wire.write(C);
   Wire.write(D);
   Wire.endTransmission();
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
  byte SW3 =  2 * cSW32 + cSW31;
  SW3 = SwitchConvert[SW3 - 1];
  DivSwitch = SW1 - 1;
  PulseSwitch = SW2 - 1;
  ModeSwitch=SW3;

  if (ModeSwitch==3){
     Div1=Divider1[SW1-1];
     Div2=Divider2[SW2-1];
     Divider=Div1*Div2;
  }

  if (running == false) {
    if (ModeSwitch==3){
       DisplayNumbers(SW3, Div1,Div2,Divider);
       //DisplayNumbers(SW3, SW1, 110, SW2);
    
    }
    else{
      DisplayNumbers(SW3, SW1, 110, SW2);
    }
  }
}

float tempo;
void DoSimpleDivision(){

    
      DivPulseCounter++;
       DisplayTempo(tempo);
      //DisplayNumbers(DivPulseCounter, Div1, Div2, Divider);
      if (DivPulseCounter >= Divider) {
        Pulse();
        DivPulseCounter = 0;
      }
   
}

void DisplayTempo(float Tempo){
  int iTempo=(int)(Tempo);
  //Send to IC2
 }


void HandleClock() {
   ReadPatternSwitches();
 digitalWrite(InputLED, HIGH);  
  if (running == true) {
    if (ModeSwitch==3){
      long NewTime=millis();
      long tTime =NewTime - IntMillis;
      IntMillis=NewTime;
      tempo = 30.0*((float)1000/(float)tTime);
     
      DoSimpleDivision();
      return;
    }
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
        if (CurrentPtr < DataLength) {
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
  digitalWrite(InputLED, LOW);  
}

volatile long int work;

void Pulse() {

int pin= GateOut;
   digitalWrite(pin, HIGH);  
   
long int i=0;
int k=0;
  for (k=0;k<10;k++){
  for (i = 0; i < 100; i++) {
    work= i * k; //Add some delay work
  }
  }
 digitalWrite(pin, LOW);  

}
// the loop function runs over and over again forever
void loop() {

}
