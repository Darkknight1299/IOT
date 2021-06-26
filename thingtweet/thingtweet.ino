#include<ESP8266WiFi.h>
char* ssid="Rana Villa";
char* pass="Sp@9991109566";
WiFiClient client;
char ip[]="184.106.153.149";//Thingspeak IP address
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
}

void loop() {
  // put your main code here, to run repeatedly:
  if(client.connect(ip,80)){ //If thingspeak website is connected then only code is sent otherwise not
    String data ="api_key=5JKMZRGPKNRGJ0Q7&status=Hello Friends! I posted this using IOT";  
    client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n"); //These 6-7 lines will always be common for post method.....just api and url will change
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length:");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);
    Serial.println("Tweet Success");
    delay(15000);
    } 
}
