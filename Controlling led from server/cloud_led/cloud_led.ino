#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
char* ssid="Rana Villa";
char* pass="Sp@9991109566";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Connecting to Wifi");
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("WiFi Connected");
  pinMode(D2,OUTPUT);  
  }

void loop() {
  // put your main code here, to run repeatedly:
    String api ="http://topping-sewers.000webhostapp.com/get.php";
    HTTPClient client;
    client.begin(api);
    int code = client.GET();
    String response = client.getString();
    Serial.println(code);
    Serial.println(response);
    if(response=="ON"){
      digitalWrite(D2,HIGH);
      Serial.println("LED ON");
      }
     if(response=="OFF"){
      digitalWrite(D2,LOW);
      Serial.println("LED OFF");
      } 
    client.end();  
    delay(100);  
}
