
int Counter = 0;
boolean state[] = {false, false, false, false};
int pins[] = {13, 12, 11, 10};
int pulsecount[] = {0, 0, 0, 0};


int SeqLength = 8;
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
}



void SetPin(int pin, boolean state) {
  digitalWrite(pins[pin], state);
}

void StartCount() {
  Counter++;
  if (Counter >= SeqLength * Bars) {
    Pulse();
    Counter = 0;
  }
}


void Pulse() {
  int i = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  SetPin(0, HIGH);
  for (i = 0; i < 16; i++) {
    delay(1);
  }
  digitalWrite(LED_BUILTIN, LOW);
  SetPin(0, LOW);

}
// the loop function runs over and over again forever
void loop() {



}
