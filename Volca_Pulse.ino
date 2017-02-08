
int Counter=0;
boolean state[]={false,false,false,false};
int pins[]={13,12,11,10};
int pulsecount[]={0,0,0,0};
int BPM=60;
int BPQ=(int)(BPM*4/60);

int Baserate=(int)((1.0/BPQ)*1000);
int Totaltime = 4* Baserate; // so we can get 4 times
int Halfrate = Totaltime/2; 

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
  StartCount(0);
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
  
  
  if  ((Counter % Halfrate) ==0)
      StartCount(1);
  if  ((Counter % Totaltime) ==0)
      StartCount(2);  
  Pulse();
  Counter++;
  if (Counter >=Totaltime)
     Counter=0;
  
}
