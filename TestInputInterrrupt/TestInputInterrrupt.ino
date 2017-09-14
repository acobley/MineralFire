/*

   Tests the gate in interupt is working, and sends a pulse to the output



*/



const byte GateInInterrupt = 2;
const byte GateIn = 9; //The input LED
const byte GateOut = 8;
byte v = 2;
void setup() {
  // put your setup code here, to run once:
  delay(5000);
  pinMode(GateIn, OUTPUT);
  pinMode(GateOut, OUTPUT);
  digitalWrite(GateOut, LOW);
  digitalWrite(GateIn, LOW);
  
   attachInterrupt(digitalPinToInterrupt(GateInInterrupt), HandleClock, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:


}

void HandleClock() {
  Pulse();
}


volatile long int work;
boolean state = LOW;


void Pulse() {


  digitalWrite(GateOut, HIGH);
  digitalWrite(GateIn, HIGH);
 

  long int i;
  long k;
  for (k = 0; k < 10; k++) {
    for (i = 0; i < 100; i++) {
      work = i * k; //Add some delay work
    }
  }
  
  digitalWrite(GateOut, LOW);
  digitalWrite(GateIn, LOW);

}
