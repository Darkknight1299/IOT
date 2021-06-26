void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //enables the serial comm. 9600-baud rate(transmission of input and output).
  pinMode(A0,INPUT);
  pinMode(D2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
    int s = analogRead(A0);
    Serial.println(s);//200 something-Room light, 20-no light
    if(s<30){
      digitalWrite(D2,HIGH);     
    }
    else{
      digitalWrite(D2,LOW);
      } 
  }
