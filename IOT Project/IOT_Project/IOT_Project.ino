#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Adafruit_SSD1306.h>

#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

 
#define REPORTING_PERIOD_MS 1000
#define AIO_SERVER        "io.adafruit.com"
#define AIO_SERVERPORT  1883                 
#define AIO_USERNAME "Lakshay1299"
#define AIO_KEY                "aio_EhLa80s0V8lXiD8DyWooTHEVFYUc"


Adafruit_SSD1306 display(128,64,&Wire,-1);
 
char auth[] = " -pHjorGy-10Hlj8LyYZ-PyYCPwpZ_m7A";             // You should get Auth Token in the Blynk App.
char ssid[] = "Rana Villa";                                     // Your WiFi credentials.
char pass[] = "Sp@9991109566";
 
// Connections : SCL PIN - D1 , SDA PIN - D2 , INT PIN - D0
PulseOximeter pox;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        
Adafruit_MQTT_Publish bpm = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/bpm");
Adafruit_MQTT_Publish spo2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/SpO2");

 
float BPM, SpO2;
uint32_t tsLastReport = 0;
 
const unsigned char bitmap [] PROGMEM=
{
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
 
void onBeatDetected()
{
    Serial.println("Beat Detected!");
    display.drawBitmap( 60, 20, bitmap, 28, 28, 1);
    display.display();
}

void connect() {
  Serial.print("Connecting to MQTT... ");
  uint8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }
    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(1000);
  }
  Serial.println("MQTT Connected!");
}
 
void setup()
{
    Serial.begin(115200);
    display.begin(SSD1306_SWITCHCAPVCC,0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 0);
 
    display.println("Initializing pulse oximeter..");
    display.display();
    
    pinMode(16, OUTPUT);
    Serial.print(F("Connecting to "));
                Serial.println(ssid);
                WiFi.begin(ssid, pass);
                while (WiFi.status() != WL_CONNECTED) {
                  delay(500);
                  Serial.print(F("."));
                }
                 Serial.println();
                 Serial.println(F("WiFi connected"));
                 Serial.println(F("IP address: "));
                 Serial.println(WiFi.localIP());

    Blynk.begin(auth, ssid, pass);
    // connect to adafruit io
                 connect();
  
    Serial.print("Initializing Pulse Oximeter..");
 
    if (!pox.begin())
    {
         Serial.println("FAILED");
         display.clearDisplay();
         display.setTextSize(1);
         display.setTextColor(1);
         display.setCursor(0, 0);
         display.println("FAILED");
         display.display();
         for(;;);
    }
    else
    {
         display.clearDisplay();
         display.setTextSize(1);
         display.setTextColor(1);
         display.setCursor(0, 0);
         display.println("SUCCESS");
         display.display();
         Serial.println("SUCCESS");
         pox.setOnBeatDetectedCallback(onBeatDetected);
    }
 
    // The default current for the IR LED is 50mA and it could be changed by uncommenting the following line.
     //pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
}
 
void loop()
{
    pox.update();
    Blynk.run();
 
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate:");
        Serial.print(BPM);
        Serial.print(" bpm / SpO2:");
        Serial.print(SpO2);
        Serial.println(" %");
 
        Blynk.virtualWrite(V7, BPM);
        Blynk.virtualWrite(V8, SpO2);
        
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0,16);
        display.println(pox.getHeartRate());
 
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0, 0);
        display.println("Heart BPM");
 
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0, 30);
        display.println("Spo2");
 
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0,45);
        display.println(pox.getSpO2());
        display.display();
        
    }
    if (! bpm.publish(BPM)) {                     //Publish to Adafruit
          Serial.println(F("Failed"));
        } 
        if (! spo2.publish(SpO2)) {                     //Publish to Adafruit
          Serial.println(F("Failed"));
        }
        else {
          Serial.println(F("Sent!"));
        }
        tsLastReport = millis();
        
}
