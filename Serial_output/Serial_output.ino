void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //enables the serial comm. 9600-baud rate(transmission of input and output).
}

void loop() {
  // put your main code here, to run repeatedly:  
  if(Serial.available()){//If is used to avaoid '-1' printing when no inout is given
    int data =Serial.read();//Use char to not get ascii value
    Serial.println(data);
    //delay(1000);  Required when if is not used
    }//Dont select new line in serial monitor 
}
