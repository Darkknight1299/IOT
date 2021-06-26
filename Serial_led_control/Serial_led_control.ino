void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //enables the serial comm. 9600-baud rate(transmission of input and output).
  pinMode(D2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
    if(Serial.available()){
      char data=Serial.read();
      if(data=='1'){
        digitalWrite(D2,HIGH);
        Serial.println("LED ON");
        }
      if(data=='0'){
        digitalWrite(D2,LOW);
        Serial.println("LED OFF");
        } 
      } 
  }
