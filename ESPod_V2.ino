#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <BleKeyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";


WebServer server(80);

Adafruit_SSD1306 display(128,64,&Wire,-1);

BleKeyboard bleKeyboard("ESPod32");

#define LEFT_RED 19
#define LEFT_GREEN 18
#define BLACK 5
#define RIGHT_GREEN 17
#define RIGHT_RED 16

String song="Waiting...";
String artist="ESPod32";

int progress=0;
int duration=100;

unsigned long lastOLED=0;




void setup(){

Serial.begin(115200);


pinMode(LEFT_RED,INPUT_PULLUP);
pinMode(LEFT_GREEN,INPUT_PULLUP);
pinMode(BLACK,INPUT_PULLUP);
pinMode(RIGHT_GREEN,INPUT_PULLUP);
pinMode(RIGHT_RED,INPUT_PULLUP);



Wire.begin(21,22);

display.begin(
SSD1306_SWITCHCAPVCC,
0x3C
);


showText(
"ESPod32",
"Booting"
);

bleKeyboard.begin();

WiFi.begin(ssid,password);


showText(
"WiFi",
"Connecting"
);


while(WiFi.status()!=WL_CONNECTED)
{
 delay(300);
}


Serial.println(WiFi.localIP());


showText(
"IP:",
WiFi.localIP().toString()
);

server.on(
"/update",
HTTP_POST,
receiveData
);


server.begin();


delay(2000);

}

void loop(){

server.handleClient();


buttons();


if(millis()-lastOLED>1000)
{

 drawPlayer();

 lastOLED=millis();

}

}

void receiveData(){


StaticJsonDocument<300> doc;


deserializeJson(
doc,
server.arg("plain")
);


song =
doc["song"].as<String>();

artist =
doc["artist"].as<String>();

progress =
doc["progress"];

duration =
doc["duration"];


server.send(
200,
"text/plain",
"OK"
);

}

void buttons(){


if(!bleKeyboard.isConnected())
return;



if(digitalRead(BLACK)==LOW)
{

bleKeyboard.write(
KEY_MEDIA_PLAY_PAUSE
);

delay(300);

}


if(digitalRead(LEFT_RED)==LOW)
{

bleKeyboard.write(
KEY_MEDIA_PREVIOUS_TRACK
);

delay(300);

}


if(digitalRead(RIGHT_RED)==LOW)
{

bleKeyboard.write(
KEY_MEDIA_NEXT_TRACK
);

delay(300);

}



if(digitalRead(LEFT_GREEN)==LOW)
{

bleKeyboard.write(
KEY_MEDIA_VOLUME_DOWN
);

delay(150);

}



if(digitalRead(RIGHT_GREEN)==LOW)
{

bleKeyboard.write(
KEY_MEDIA_VOLUME_UP
);

delay(150);

}


}

void drawPlayer()
{

display.clearDisplay();

display.setTextColor(WHITE);

display.setTextSize(1);

display.setCursor(0,0);

String title = song;

if(title.length() > 18)
{
 title = title.substring(0,18);
 title += "...";
}

display.println(title);

display.setCursor(10,14);

String art = artist;

if(art.length() > 18)
{
 art = art.substring(0,18);
 art += "...";
}

display.println(art);


display.setCursor(0,32);

display.print("> ");

display.print(progress/60);
display.print(":");

if(progress%60 < 10)
display.print("0");

display.print(progress%60);

display.setCursor(96,32);

display.print(duration/60);
display.print(":");

if(duration%60 < 10)
display.print("0");

display.print(duration%60);

int bar = map(
progress,
0,
duration,
0,
90
);


display.drawRoundRect(
18,
45,
90,
7,
3,
WHITE
);


display.fillRoundRect(
18,
45,
bar,
7,
3,
WHITE
);


display.setCursor(40,56);

display.print("ESPod32");


display.display();

}

void showText(
String a,
String b
)
{

display.clearDisplay();

display.setTextColor(WHITE);


display.setTextSize(2);

display.setCursor(0,5);

display.println(a);


display.setTextSize(1);

display.setCursor(0,40);

display.println(b);


display.display();

}

void printTime(int sec)
{
  int m = sec / 60;
  int s = sec % 60;

  display.print(m);
  display.print(":");

  if (s < 10)
  {
    display.print("0");
  }

  display.print(s);
}