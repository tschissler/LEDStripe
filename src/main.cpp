#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"


#define Datapin 13
#define Ledcount 30
#define Delay 250
#define DHTPIN 12 
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel (Ledcount, Datapin, NEO_GRB+NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE);

uint32_t color_temp=Pixel.Color(50,0,50);

void setup() {
  Pixel.begin();
  dht.begin();
  Serial.begin(9600);
  Serial.println("LEDStripe");
}

void temperature()
{
  float t = dht.readTemperature();
  Serial.println(t);
  for (int i=0; i<29; i++)
  {
    if(i<=(int)t)
    {
      Pixel.setPixelColor(i, color_temp);
    }
    else 
    {
      Pixel.setPixelColor(i,Pixel.Color(0,0,0));
    }
  }
  
  Pixel.show();
  delay(1000);
}

void glitter () 
{
  for(int i=0;i<30;i++)
  {
    int baseColorRed = rand() % 255;
    int baseColorGreen = rand() % 255;
    int baseColorBlue = rand() % 255;
    uint32_t color=Pixel.Color(baseColorRed,baseColorGreen,baseColorBlue);
    Pixel.setPixelColor(i,color);
  }
  Pixel.show();
  delay(Delay);
}

void bounce()
{
  int baseColorRed = rand() % 11;
  int baseColorGreen = rand() % 11;
  int baseColorBlue = rand() % 11;

  uint32_t color_low=Pixel.Color(baseColorRed,baseColorGreen,baseColorBlue);
  uint32_t color_med=Pixel.Color(baseColorRed*10,baseColorGreen*10,baseColorBlue*10);
  uint32_t color_high=Pixel.Color(baseColorRed*20,baseColorGreen*20,baseColorBlue*20);
  
  for(int i=0;i<26;i++)
  {
    Pixel.setPixelColor(i,color_low);
    Pixel.setPixelColor(i+1,color_med);
    Pixel.setPixelColor(i+2,color_high);
    Pixel.setPixelColor(i+3,color_med);
    Pixel.setPixelColor(i+4,color_low);
    Pixel.show();
    delay (Delay);
    Pixel.setPixelColor(i,Pixel.Color(0,0,0));
  }
 for(int i=25;i>0;i--)
  {
    Pixel.setPixelColor(i,color_low);
    Pixel.setPixelColor(i+1,color_med);
    Pixel.setPixelColor(i+2,color_high);
    Pixel.setPixelColor(i+3,color_med);
    Pixel.setPixelColor(i+4,color_low);
    Pixel.show();
    delay (Delay);
    Pixel.setPixelColor(i+4,Pixel.Color(0,0,0));
  }
}

void loop() {
  temperature();
}