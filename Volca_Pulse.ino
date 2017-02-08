
int Counter=0;
boolean state[]={false,false,false,false};
int pins[]={13,12,11,10};
int pulsecount[]={0,0,0,0};


int SeqLength=8;
int Bars=1;

const byte interruptPin = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
   attachInterrupt(digitalPinToInterrupt(interruptPin), StartCount, CHANGE);
}

void SetPin(int pin, boolean state){
    digitalWrite(pins[pin], state);
}

void StartCount(){
  Counter++;
 
  if (Counter >=SeqLength){
       StartCount(1);
       Counter=0;
  }
    
}

void StartCount(int pin){
  pulsecount[pin]=0;
}

void Pulse(){
  for (int i=0;i<4;i++){
    if (pulsecount[i]<16){
      if (i==0){
          digitalWrite(LED_BUILTIN, HIGH);
      }
       SetPin(i,HIGH);
    }   
    else {
      if (i==0){
           digitalWrite(LED_BUILTIN, LOW); 
      }
        SetPin(i,LOW);
    }    
    pulsecount[i]++;
  }
}
// the loop function runs over and over again forever
void loop() {
 
  delay(1);
  Pulse();
  
  
}
