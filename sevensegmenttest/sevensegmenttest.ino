byte CSEGA = A0;
byte CSEGB = 2;
byte CSEGC = 8;
byte CSEGD = 6;
byte CSEGE = 7;
byte CSEGF = A1;
byte CSEGG = 4;

byte CDIG2 = A2;
byte CDIG3 = A3;
byte CDIG1 = 9;
byte CDIG4 = 3;

byte zero[] = {CSEGA, CSEGB, CSEGC, CSEGD, CSEGE, CSEGF};
byte one[] = {CSEGB, CSEGC};
byte two[] = {CSEGA, CSEGB, CSEGD, CSEGE, CSEGG};
byte three[] = {CSEGA, CSEGB, CSEGC, CSEGD, CSEGG};
byte four[] = {CSEGB, CSEGC, CSEGF, CSEGG};
byte five[] = {CSEGA, CSEGC, CSEGD, CSEGF, CSEGG};
byte six[] = {CSEGC, CSEGD, CSEGE, CSEGF, CSEGG};
byte seven[] = {CSEGA, CSEGB, CSEGC};
byte eight[] = {CSEGA, CSEGB, CSEGC, CSEGD, CSEGE, CSEGF, CSEGG};
byte  nine[] = {CSEGA, CSEGB, CSEGC, CSEGF, CSEGG};
byte A[] = {CSEGA, CSEGB, CSEGC, CSEGE, CSEGF, CSEGG};
byte B[] = {CSEGC, CSEGD, CSEGE, CSEGF, CSEGG};
byte C[] = {CSEGA, CSEGD, CSEGE, CSEGF};
byte D[] = {CSEGB, CSEGC, CSEGD, CSEGE, CSEGG};
byte E[] = {CSEGA, CSEGD, CSEGE, CSEGF, CSEGG};
byte F[] = {CSEGA, CSEGE, CSEGF, CSEGG};
byte G[] = {CSEGA, CSEGB, CSEGC, CSEGD, CSEGE, CSEGF, CSEGG};

void setup() {
  // put your setup code here, to run once:
  int i = 0;
  pinMode(CSEGA, OUTPUT);
  pinMode(CSEGB, OUTPUT);
  pinMode(CSEGC, OUTPUT);
  pinMode(CSEGD, OUTPUT);
  pinMode(CSEGE, OUTPUT);
  pinMode(CSEGF, OUTPUT);
  pinMode(CSEGG, OUTPUT);

  pinMode(CDIG1, OUTPUT);
  pinMode(CDIG2, OUTPUT);
  pinMode(CDIG3, OUTPUT);
  pinMode(CDIG4, OUTPUT);
  digitalWrite(CSEGA, false);
  digitalWrite(CSEGB, false);
  digitalWrite(CSEGC, false);
  digitalWrite(CSEGD, false);
  digitalWrite(CSEGE, false);
  digitalWrite(CSEGF, false);
  digitalWrite(CSEGG, false);

  digitalWrite(CDIG2, false);
  digitalWrite(CDIG3, false);
  digitalWrite(CDIG4, false);

}


void writeDigit(byte number) {

  //Turn off all display cells
  int n = sizeof(eight) / sizeof(eight[0]);
  for (int i = 0; i < n; i++) {
    digitalWrite(eight[i], true);
  }
  switch (number) {
    case 1:
      n = sizeof(one) / sizeof(one[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(one[i], false);
      }
      break;
    case 2:
      n = sizeof(two) / sizeof(two[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(two[i], false);
      }
      break;
    case 3:
      n = sizeof(three) / sizeof(three[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(three[i], false);
      }
      break;
    case 4:
      n = sizeof(four) / sizeof(four[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(four[i], false);
      }
      break;
    case 5:
      n = sizeof(five) / sizeof(five[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(five[i], false);
      }
      break;
    case 6:
      n = sizeof(six) / sizeof(six[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(six[i], false);
      }
      break;
    case 7:
      n = sizeof(seven) / sizeof(seven[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(seven[i], false);
      }
      break;
    case 8:
      n = sizeof(eight) / sizeof(eight[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(eight[i], false);
      }
      break;
    case 9:
      n = sizeof(nine) / sizeof(nine[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(nine[i], false);
      }
      break;
    case 0:
      n = sizeof(zero) / sizeof(zero[0]);
      for (int i = 0; i < n; i++) {
        digitalWrite(zero[i], false);
      }
      break;
    default:
      break;
  }
}

void DisplayNumbers(byte A, byte B, byte C, byte  D) {
  byte Char[4];
  Char[0] = A;
  Char[1] = B;
  Char[2] = C;
  Char[3] = D;
  int Digits[] = {CDIG1, CDIG2, CDIG3, CDIG4};
  for (int j = 0; j < 4; j++) {
    writeDigit(Char[j]);
    int dig = Digits[j];
    digitalWrite(dig, true);
    delay(2);
    digitalWrite(dig, false);
  }

 

}

byte Count=0;
void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<50;i++){
      DisplayNumbers(Count,Count-1,Count-2,Count-3);
}
  Count++;

  if (Count > 13)
     Count=0;

}
