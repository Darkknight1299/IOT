#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266_SSL.h>
char auth[]="je8sVjknO1dY7g94BFeIAI3EUiuW_BRO";
char ssid[]="Rana Villa";
char pass[]="Sp@9991109566";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass); //This line will connect to wifi and blynk server and will retrive all information from there itself 
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  }
