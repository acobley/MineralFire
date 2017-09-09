
/*

   Loops flashing the LED and output pulse.


*/

const byte GateOut = 8;

void setup() {
  // put your setup code here, to run once:


  pinMode(GateOut, OUTPUT);

}

long int work;
void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(GateOut, HIGH);
  long int i = 0;
  int k = 0;
  for (k = 0; k < 10; k++) {
    for (i = 0; i < 1000; i++) {
      work = i * k; //Add some delay work

    }
  }
  delay(100);
  digitalWrite(GateOut, LOW);
  delay(200);
}
