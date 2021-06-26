void setup() {
  // put your setup code here, to run once:
  pinMode(D2,OUTPUT);  //Defines D2 pin as output pin.
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D2,HIGH);  //Write means to get output, High==1.
  delay(1000);    //Delay is given as speed of processing is fast,cant see the blinking.
  digitalWrite(D2,LOW);   //Low==0.
  delay(1000);   //1000ns=1sec
}
