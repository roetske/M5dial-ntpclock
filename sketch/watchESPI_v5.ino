/*
chip M5Dial
set flashsize to 8mb !!! arduino ide 2.3.2 set partition scheme to custom
add corresponding partitions.csv to folder 
webpage to build partition 
https://thelastoutpostworkshop.github.io/microcontroller_devkit/esp32partitionbuilder/
nvs 12kb
phy 4kb
factory 6.8mb
coredump 625kb
fat (for fonts) 1mb
comment 
based on this sketch
https://github.com/nyasu3w/M5DialWatch/tree/devel credits especially for the graphics to this man
timezones
https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
timezone brussels CET-1CEST,M3.5.0,M10.5.0/3

//See: https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
  // CST6CDT, M3.2.0/2:00:00, M11.1.0/2:00:00
  // CST6CDT is the name of the time zone
  // CST is the abbreviation used when DST is off
  // 6 hours is the time difference from GMT
  // CDT is the abbreviation used when DST is on
  // ,M3 is the third month
  // .2 is the second occurrence of the day in the month
  // .0 is Sunday
  // /2:00:00 is the time
  // ,M11 is the eleventh month
  // .1 is the first occurrence of the day in the month
  // .0 is Sunday
  // 2:00:00 is the time
added partiontable with coredump partition
Had big trouble with time rebooting +2 each time could not figure out
culprit was 
setenv("TZ",TZ_INFO,1);
tzset();
M5Dial.Rtc.setDateTime(timeinfox);
removed all of this and used esp32time that works fine in previous projects
this works 
to do should add wifi connection point to set via phone wifi credentials
*/

#include "M5Dial.h"
#include "WiFi.h"
#include <ESP32Time.h>

#include <TFT_eSPI.h>
String version ="version3";
//files for fonts
#include "Noto.h"
#include "smallFont.h"
#include "middleFont.h"
#include "bigFont.h"
#include "secFont.h"
//time
const char* ssid="your ssid"; 
const char* password="your password wifi";
const char* NTP_SERVER =  "0.europe.pool.ntp.org";        //set your timeserver
const char* NTP_SERVER2 = "1.europe.pool.ntp.org";
const char* NTP_SERVER3 = "2.be.pool.ntp.org"; 
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00"; //stimezone brussels

tm timeinfo;
int updateinterval = 40; //update to ntp in min interval
int lastupdate = 0;
//local timer
ESP32Time rtc;
//screen
M5Canvas img(&M5Dial.Display);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
#define color1 TFT_WHITE
#define color2  0x8410
#define color3 0x5ACB
#define color4 0x15B3
#define color5 0x00A3

volatile int counter = 0;
float VALUE;
float lastValue=0;

unsigned short grays[12];

double rad=0.01745;
float x[360];
float y[360];
float px[360];
float py[360];
float lx[360];
float ly[360];

int r=116;
int sx=120;
int sy=120;

int start[12];
int startP[60];

int angle=0;
bool onOff=0;

String h="23";
String m="24";
String s="48";
String d1="0";
String d2="1";

String m1="2";
String m2="3";

int lastAngle=0;
float circle=100;
bool dir=0;
int rAngle=359;
int inc=0;

//*******
//setup
//*******
void setup() 
{
  Serial.begin(115200);
  Serial.print("version=");
  Serial.println(version);
  
  //m5dial
  init_M5dial();
  
  //cheat check it works
  //cheat check update works
  rtc.setTime(0,10, 0, 1, 1, 1970);
  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
  //wifi
  Serial.println("Init Wifi");
  init_Wifi();
  Serial.println("Get ntp clock");
  getNTPtime_check();
  stop_Wifi();
}

//*******
//mainloop
//*******
void loop() {
  M5Dial.update();
  //normal clock
  showlocaltime(); 
  M5Dial.Display.pushImage(0,0,240,240,(uint16_t*)sprite.getPointer());
  //handle update when button pressed
  if(M5.BtnA.wasPressed())
    {
        Serial.println("Update pressed");
        getNTPtime();
    }
  //autoupdate via ntp every x minutes
  checkNTPupdate();
  //loop protection small delay
  delay(20);
}
