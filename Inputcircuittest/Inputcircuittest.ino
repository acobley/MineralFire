
const byte GateInInterrupt = 2;
byte OutputLed=4;
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(GateInInterrupt), HandleClock, RISING);
 pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OutputLed, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

}

void HandleClock() {
  Pulse();
}

volatile long int work;
boolean state=LOW;
void Pulse() {

int pin=LED_BUILTIN ;
   digitalWrite(pin, HIGH);  
   digitalWrite(OutputLed, HIGH);  
long int i=0;
int k=0;
  for (k=0;k<10;k++){
  for (i = 0; i < 1000; i++) {
    work= i * k; //Add some delay work
  }
  }

 digitalWrite(pin, LOW);  
    digitalWrite(OutputLed, LOW); 

}
