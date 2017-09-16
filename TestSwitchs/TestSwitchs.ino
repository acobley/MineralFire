#include <Wire.h>
/*
 * Tests the operation of the switches and displays on the 7 segment LED array
 * 
 * 
 */



byte DivSwitch = 0; //Used to set the pattern by the switches
byte PulseSwitch = 0;
byte ModeSwitch=1;

const int GateOut=8;
const byte InputLED = 9;
const byte interruptPin = 2;
const byte switchinterruptPin = 3;
const int SW11 = A2; //These define the two switches for selecting patterns
const int SW12 = A3;
const int SW21 = 4;
const int SW22 = 5;
const int SW31 =  A0;
const int SW32 = A1;

const int PROG1 = 6;
const int PROG2 = 7;

byte SwitchConvert[] = {1, 3, 2}; //We use this to convert from the numbers the switch puts out to a sensible


void setup() {
  // put your setup code here, to run once:
    pinMode(GateOut, OUTPUT);
     pinMode(InputLED, OUTPUT);
    pinMode(SW11, INPUT);
  pinMode(SW12, INPUT);
  pinMode(SW21, INPUT);
  pinMode(SW22, INPUT);
  pinMode(SW31, INPUT);
  pinMode(SW32, INPUT);
    pinMode(PROG1, INPUT);
  pinMode(PROG2, INPUT);
  delay(2000);
Wire.begin();
Wire.beginTransmission(8);
  Wire.write(8);
  Wire.write(7);
  Wire.write(6);
  Wire.write(5);
  Wire.endTransmission();
delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
ReadPatternSwitches() ;
}

 byte Disp1;
 byte Disp2;
byte Disp3;
 byte Disp4;

void DisplayNumbers(byte A, byte B, byte C, byte  D) {
   //Send to IC2
  Disp1 = A;
  Disp2 = B;
  Disp3 = C;
  Disp4 = D;

Wire.beginTransmission(8);
  Wire.write(Disp1);
  Wire.write(Disp2);
  Wire.write(Disp3);
  Wire.write(Disp4);
  Wire.endTransmission();

}


void ReadPatternSwitches() {
  byte cSW11 = 1;
  byte cSW12 = 1;
  byte cSW21 = 1;
  byte cSW22 = 1;
  byte cSW31 = 1;
  byte cSW32 = 1;

  byte cPROG1 = 1;
  byte cPROG2 = 1;
  
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

  if (digitalRead(PROG1) == LOW) {
    cPROG1 = 0;
  }
  if (digitalRead(PROG2) == LOW) {
    cPROG2 = 0;
  }
  
  byte SW1 = 2 * cSW12 + cSW11;
  SW1 = SwitchConvert[SW1 - 1];
  byte SW2 = 2 * cSW21 + cSW22;
  SW2 = SwitchConvert[SW2 - 1];
  byte SW3 =  2 * cSW31 + cSW32;
  SW3 = SwitchConvert[SW3 - 1];

  byte PROG =  2 * cPROG1 + cPROG2;
  PROG = SwitchConvert[PROG - 1];


    DisplayNumbers(SW3, SW2, SW1,PROG);
}



