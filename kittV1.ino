#include <Adafruit_NeoPixel.h>

#define NEOPIXELPIN 11
#define TEAMCOLORPIN 2
#define VACUUMPIN 3
#define VELOCITYPIN 5
#define CATAPULTPIN 7
#define NOPIXELS 26

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NOPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int pixelDirection = 1;
long previousMillis = 0;
long currentPixel = 0;

const uint32_t dimRed = strip.Color(32, 0, 0);
const uint32_t midRed = strip.Color(63, 0, 0);
const uint32_t brightRed = strip.Color(255, 0, 0);
const uint32_t dimBlue = strip.Color(0, 0, 32);
const uint32_t midBlue = strip.Color(0, 0, 63);
const uint32_t brightBlue = strip.Color(0, 0, 255);
const uint32_t brightGreen = strip.Color(0, 255, 0);
const uint32_t brightYellow = strip.Color(255, 255, 0);
const uint32_t black = strip.Color(0,0,0);
const long kittPixel = NOPIXELS - 3;
const long vacuumPixel = kittPixel + 1;
const long catapultPixel = kittPixel + 2;
const long directionChangePixel = kittPixel - 2;

long interval = 25;

int teamColor = 0;


void setup() {
  pinMode(TEAMCOLORPIN,INPUT);
  pinMode(VACUUMPIN,INPUT);
  pinMode(VELOCITYPIN,INPUT);
  pinMode(CATAPULTPIN,INPUT);
  strip.begin();
  strip.show(); 
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (digitalRead(VELOCITYPIN) == HIGH) {
    interval = 15;
  } else {
    interval = 30;
  }
  
  if (digitalRead(VACUUMPIN) == HIGH) {
    strip.setPixelColor(vacuumPixel, brightYellow);
  } else {
    strip.setPixelColor(vacuumPixel, black);
  }

  
  if (digitalRead(CATAPULTPIN) == HIGH) {
    strip.setPixelColor(catapultPixel, brightGreen);
  } 
  else {
    strip.setPixelColor(catapultPixel, black);
  } 
  
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    
    uint32_t dimColor = dimRed;
    uint32_t midColor = midRed;
    uint32_t brightColor = brightRed;
    
    for(uint16_t i=0; i < kittPixel; i++) {
      strip.setPixelColor(i, dimRed);
    }
    
    if (digitalRead(TEAMCOLORPIN) == HIGH) {
      dimColor = dimBlue;
      midColor = midBlue;
      brightColor = brightBlue;
      for(uint16_t i=0; i < kittPixel; i++) {
        strip.setPixelColor(i, dimBlue);
      }
    }
    
    currentPixel += pixelDirection;
    
    if (currentPixel > directionChangePixel) {
      pixelDirection = -1;
      currentPixel = directionChangePixel;
    }
    
    if (currentPixel < 0) {
      pixelDirection = 1;
      currentPixel = 0;
    }

    strip.setPixelColor(currentPixel - 1, midColor);
    strip.setPixelColor(currentPixel, brightColor);
    strip.setPixelColor(currentPixel + 1, midColor);
    
  }
  
  strip.show();
}


