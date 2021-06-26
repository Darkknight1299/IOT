//Self Adjusting OLED Clock 
//by Shubham Santosh


#include<ESP8266WiFi.h>
#include<NTPClient.h>
#include<WiFiUdp.h>
#include<SPI.h>
#include<Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>
#include<Wire.h>

#define utcoffset 19800   // adds 19800 seconds = 5hr and 30 mins

Adafruit_SSD1306 display(128,64,&Wire,-1);
WiFiUDP ntp;
NTPClient timeclient(ntp,"asia.pool.ntp.org",utcoffset);

const char *ssid= "Rana Villa";               // enter SSID of your WiFi router
const char *password= "Sp@9991109566";        // enter password of the router


String Week[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  /*if(!(display.begin(SSD1306_SWITCHCAPVCC,0x3C)))
  {
    Serial.println("Connection Error");
    while (true)
    {continue;}
  }
  */
  delay(1000);

  // animation
display.clearDisplay();
display.setTextColor(WHITE);
display.setCursor(0,0);
display.setTextSize(2);
display.println("OLED");
display.setCursor(0,32);
display.println("CLOCK");
display.display();
display.startscrollright(0x00,0x05);
delay(1500);
display.invertDisplay(1);
display.stopscroll();
delay(1000);

    // displays ssid of the router to be connected
display.invertDisplay(0);
display.clearDisplay();
display.setCursor(0,0);
display.setTextColor(WHITE);
display.setTextSize(2);
display.println("CONNECTING");
display.setCursor(52,16);
display.println("TO");
display.setTextSize(1);
display.println(ssid);
display.display();
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.print(".");
  delay(500);
}
display.setCursor(0,48);
display.setTextSize(2);
display.setTextColor(BLACK,WHITE);
display.print("Connected");
display.display();
delay(500);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
}


const int xcenter=90;  //x and y center points for clock
const int ycenter=32;   
const int radius=30;    // radius of clock


void loop() {
  timeclient.update();       
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(BLACK,WHITE);
  display.println("INDIA");     
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println();
  display.println(Week[timeclient.getDay()]);
  display.println();
  display.println(timeclient.getFormattedTime());
  display.println();
  
  // to obtain and display date
  
  int epochtime=timeclient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochtime); 
  display.print(ptm->tm_mday);
  display.print(":");
  display.print( ptm->tm_mon+1);
  display.print(":");
  display.println(ptm->tm_year+1900);
  
  // to display clock
  
  display.drawCircle(xcenter,ycenter,radius,WHITE);
  displaytime(timeclient.getHours(),timeclient.getMinutes(),timeclient.getSeconds());
  display.display();
  display.clearDisplay();
  delay(1000);
}

void displaytime(int hours,int mins,int secs)
{
  int Sangle=secs*6;                        // second angle 
  int Mangle=mins*6;                         //minute angle
  int Hangle;                            // hour angle
  if(hours>=0 and hours<=12)
  Hangle=30*hours+map(mins,0,60,0,30);      // map for minor adjustments in hour hand
  else if(hours>12)              // hour format is 24hrs
  Hangle=(hours-12)*30+map(mins,0,60,0,30);  
  
    //for displaying seconds
  int shiftSecX=0.8*radius*sin(Sangle*0.0174533);      //shifted x coordinate of second,0.8 is the 
  int shiftSecY=0.8*radius*cos(Sangle*0.0174533);      //shifted y coordinate of second

 // if(Sangle>=0 and Sangle<=90)
 display.drawLine(xcenter,ycenter,xcenter+shiftSecX,ycenter-shiftSecY,WHITE);    //1st quadrant
/* else if(Sangle>90 and Sangle<=180)
 display.drawLine(xcenter,ycenter,xcenter+shiftSecX,ycenter-shiftSecY,WHITE);    //4th quadrant
 else if(Sangle>180 and Sangle<=270)
 display.drawLine(xcenter,ycenter,xcenter+shiftSecX,ycenter-shiftSecY,WHITE);    // 3rd quadrant
  else if(Sangle>270 and Sangle<=354)
display.drawLine(xcenter,ycenter,xcenter+shiftSecX,ycenter-shiftSecY,WHITE);    // 2nd quadrant
*/
//for displaying minutes
  int shiftMinX=radius*sin(Mangle*0.0174533);      //shifted x coordinate of minutes
  int shiftMinY=radius*cos(Mangle*0.0174533);      //shifted y coordinate of minutes

  display.drawLine(xcenter,ycenter,xcenter+shiftMinX,ycenter-shiftMinY,WHITE);

//for displaying hours
  int shiftHourX=0.6*radius*sin(Hangle*0.0174533);      //shifted x coordinate of hours
  int shiftHourY=0.6*radius*cos(Hangle*0.0174533);      //shifted y coordinate of hours

  display.drawLine(xcenter,ycenter,xcenter+shiftHourX,ycenter-shiftHourY,WHITE);

/*
// for testing purpose
  Serial.print(Sangle);
  Serial.print("\t");
  Serial.print(sin(Sangle*0.0174533));
  Serial.print("\t");
  Serial.print(cos(Sangle*0.0174533));
  Serial.print("\t");
  Serial.println(timeclient.getSeconds());
*/
}
