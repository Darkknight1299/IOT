void setup() {
  // put your setup code here, to run once:
  pinMode(D2,OUTPUT);  //Defines D2 pin as output pin.
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<=255;i++){
    analogWrite(D2,i);
    delay(50);
  }//For Range of analog output
  
  analogWrite(D2,50);//For constant analog output
  }
