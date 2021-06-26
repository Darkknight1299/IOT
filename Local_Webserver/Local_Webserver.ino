#include<ESP8266WiFi.h>
char* ssid="Rana Villa";
char* pass="Sp@9991109566";
WiFiServer server(80); //Default statement,80-default port name
void setup() {
  // put your setup code here, to run once:
  //Nord MCU and laptop should be connected to the same network
  Serial.begin(9600);
  Serial.print("Connection to ");
  Serial.println(ssid);
  WiFi.begin(ssid,pass); //connect to Wifi
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
    Serial.println("WiFi Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP()); //This is the IP address that will be used for interaction,server formation and webpage
    server.begin();
    pinMode(D2,OUTPUT);   
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client=server.available(); //This will be true as soon as client will send some request
  if(!client){
    return; //Will go back to first line in loop()
    }
  Serial.println("New Request Received"); //It will send multiple request when there is no response    
  String request = client.readStringUntil('\r'); //It will read url untill on or off(all data after ip address) -- 192.168.0.1/on,192.168.0.1/off
  Serial.println(request);
  client.flush(); //To get new request everytime and not cache
  //We will get output after reading input in ip address as-  GET /on HTTP 1.1  --so on is on 4 index(include / as well)
  if(request.indexOf("/on")!=-1){//on is present in the ip address
    digitalWrite(D2,HIGH);
    Serial.println("LED ON");  
    }
   if(request.indexOf("/off")!=-1){//off is present in the ip address
    digitalWrite(D2,LOW);
    Serial.println("LED OFF");  
    }

    //Now if we go to the ip address then the below html code will run and give us a webpage for the same led interaction
    client.println("<html><title>LED CONTROL</title><center>"); 
    client.println("<h1>LED CONTROL WITH LOCAL WEB SERVER</h1>");
    client.println("<a href='/on'><button>LED ON</button></a>"); //Put on in single quotes as we are using double quotes first already 
    client.println("<a href='/off'><button>LED OFF</button></a>");
    client.println("</center></html>"); 
  }
