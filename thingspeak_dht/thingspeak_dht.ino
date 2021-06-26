#include<ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
DHT dht(D2,DHT11); //Tell what where we are connecting dht sensor.
char* ssid="Rana Villa";
char* pass="Sp@9991109566";
WiFiClient client;
char* api="53GN6WNC5TD1MXBH";
long id=1308085; //channel id
float t,h;
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
  ThingSpeak.begin(client);
  dht.begin();  
  }

void loop() {
  // put your main code here, to run repeatedly:
  h=dht.readHumidity();
  t=dht.readTemperature(); //value in celsius
  // t=dht.readTemperature(true); //value in fahrenhiet
  if(isnan(h) || isnan(t)){ //nan value is given when connection is loose or delay is less
    Serial.println("Unable to Fetch data");
    }
  else{
    Serial.print("Humidity-");Serial.print(h);
    Serial.print(",");
    Serial.print("Temperature-");Serial.println(t);
    ThingSpeak.setField(1,t);
    ThingSpeak.setField(2,h);
    ThingSpeak.writeFields(id,api);
    client.stop();
    }  
  delay(15000);  //Atleast this much delay is needed due to internet connectivity and all
}
