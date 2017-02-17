
int Counter = 0;
boolean state[] = {false, false, false, false};
int pins[] = {13, 12, 11, 10};
int BarsCount[]={3,1,2,2};
int SeqLengths[]={8,4,8,4};
int BarCount =0; //the element of the BarsCount Array
int CurrentBar=1; //how far through the current Bars we are

int SeqLength = SeqLengths[BarCount];
int Bars = 1;

const byte interruptPin = 2;


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
  Bars=BarsCount[BarCount];
}



void SetPin(int pin, boolean state) {
  digitalWrite(pins[pin], state);
  
}

void StartCount() {
  Counter++;
  Serial.print(Counter); 
  Serial.print("  :  ");
  if (Counter >= (SeqLength * Bars)) {
    Pulse();
    Counter = 0;
    CurrentBar++;
    if (CurrentBar > Bars){
      BarCount++;
      if (BarCount >3)
         BarCount=0;
      CurrentBar=1;
      Bars=BarsCount[BarCount];
      SeqLength = SeqLengths[BarCount];
    }
    
  }
}


void Pulse() {
  
  Serial.println(" Pulse");
  int i=0;
  SetPin(0, HIGH);
  for (i=0;i<1000;i++){
    int j=i*10;
  }
Serial.println(" end");
  SetPin(0, LOW);

}
// the loop function runs over and over again forever
void loop() {

while (true){
  delay(1);
}

}
