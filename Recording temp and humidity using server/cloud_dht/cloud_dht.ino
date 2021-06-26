#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
DHT dht(D2,DHT11); //Tell what where we are connecting dht sensor.
char* ssid="Rana Villa";
char* pass="Sp@9991109566";
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
  dht.begin();  
  }

void loop() {
  // put your main code here, to run repeatedly:
  h=dht.readHumidity();
  t=dht.readTemperature(); //value in celsius
  if(isnan(h) || isnan(t)){ //nan value is given when connection is loose or delay is less
    Serial.println("Unable to Fetch data");
    }
  else{
    Serial.print("Humidity-");Serial.print(h);
    Serial.print(",");
    Serial.print("Temperature-");Serial.println(t);
    String api ="http://topping-sewers.000webhostapp.com/insert.php?field1="+String(h)+"&field2="+String(t);
    HTTPClient client;
    client.begin(api);
    int code = client.GET();
    String response = client.getString();
    Serial.println(code);
    Serial.println(response);
    client.end();
    }  
  delay(15000);  //Atleast this much delay is needed due to internet connectivity and all
}
