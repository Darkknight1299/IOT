#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Rana Villa"
#define WLAN_PASS       "Sp@9991109566"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Lakshay1299"
#define AIO_KEY         "aio_EhLa80s0V8lXiD8DyWooTHEVFYUc"

/************ Global State (you don't need to change this!) ******************/

WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish hum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humid");
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
int h,t;

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
  pinMode(D2,OUTPUT);
}

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      char* data = (char *)onoffbutton.lastread;
      if(strcmp(data,"ON")==0{ // Compare Strings
        Serial.println("LED ON");
        digitalWrite(D2,HIGH);
        }
      if(strcmp(data,"OFF")==0{ // Compare Strings
        Serial.println("LED OFF");
        digitalWrite(D2,LOW);
        }
    }
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending data "));
  Serial.print("...");
  h++;
  t++;
  hum.publish(h);
  temp.publish(t);
  delay(1000);  //Give 15000 for dht sensor....rightnow giving values of humid and temp manually. Also giving less delay will ban the acc...so use appropriate delay always.If acc ban it will be unban after few minutes.
}
  
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
