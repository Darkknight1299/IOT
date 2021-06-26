#include<ESP8266WiFi.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); //esp8266 will be in stationary mode
  WiFi.disconnect(); //Disconnects any already connected networks , optional as above statement does the same work as well
  Serial.println("Setup Done");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Scanning Networks....");
  int n=WiFi.scanNetworks(); //return the number of available networks.
  if(n==0){
    Serial.println("No Wifi Network Available"); 
   }
   else{
    Serial.print(n);
    Serial.println(" Networks Found");
    for(int i=0;i<n;i++){
      Serial.print(i+1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print("(");
      Serial.print(WiFi.RSSI(i));
      Serial.println(")");
      } 
   } 
   Serial.println(" ");
   delay(5000);
}
