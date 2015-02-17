#include "FastLED.h"
 
#define NUM_LEDS 160
#define NUM_PORT 18
#define NUM_FRONT 16
#define NUM_STBD 15
#define NUM_BACK 17
 
// Arduino pins
#define CLOCK_PIN 7
#define DATA_PIN 8
#define PIN1 3  // white
#define PIN2 4  // red
#define PIN3 5  // black
#define PIN4 10 // black
#define PIN5 11 // red
 
// Sequence numbers
#define S_BLACK 0
#define S_RED 1
#define S_SEIZURE_LIGHTS 2
#define S_RAINBOW_CYCLE 3

CRGB leds[NUM_LEDS];
 
int i = 0, showToRun = S_BLACK, lastShow = showToRun;
 
void setBlock(CRGB color, int start, int length);
void setAlternating(CRGB one, CRGB two, int start, int length);
void setChaserBlock(CRGB background, CRGB foreground, int start, int length, int chaserLength);
 
void setup() {
   delay(200);
   FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
 
   pinMode(PIN1, INPUT);
   pinMode(PIN2, INPUT);
   pinMode(PIN3, INPUT);
   pinMode(PIN4, INPUT);
 
   Serial.begin(9600);
   Serial.println("Valkyrie LED Code.\n");
   Serial.println("INITIATING SEQUENCE.\n");  
}

void loop() {
  showToRun = digitalRead(PIN1) | digitalRead(PIN2) << 1 | digitalRead(PIN3) << 2 | digitalRead(PIN4) << 3 | digitalRead(PIN5) << 4;
     showToRun = S_SEIZURE_LIGHTS;
 
  if (showToRun != lastShow) {
    i = 0;
    Serial.print("RUNNING.\n");
    Serial.println(showToRun);
  }
  Serial.println(showToRun);
 
  switch (showToRun) {
    case S_BLACK:{
      setBlock(CRGB::Black, 0, NUM_LEDS);
      break;
    }
 
    case S_RED:{
      setBlock(CRGB::Red, 0, NUM_LEDS);
      break;
    }
    case S_SEIZURE_LIGHTS:{
      if(i%2 == 0){
        for(int numLights = 0; numLights < NUM_LEDS; numLights++){
          if(numLights%2 == 0)
            leds[numLights] = CRGB(255,100,0);
          if(numLights%2 == 1)
            leds[numLights] = CRGB::Black;
         }
       }
     }
      if(i%2 == 1){
        for(int numLights = 0; numLights < NUM_LEDS; numLights++){
          if(numLights%2 == 1)
            leds[numLights] = CRGB(255,100,0);
          if(numLights%2 == 0)
            leds[numLights] = CRGB::Black;
        }
      }
    case S_RAINBOW_CYCLE: {
      // see http://krazydad.com/tutorials/makecolors.php
      int red   = sin(0.025 * i    ) * 127 + 128;
      int green = sin(0.025 * i + 2) * 127 + 128;
      int blue  = sin(0.025 * i + 4) * 127 + 128;
      setBlock(CRGB(red, green, blue), 0, NUM_LEDS);
      break;
     }  
   }  
      FastLED.show();
      delay(10);
    
  lastShow = showToRun;
  i++;
}
void setBlock(CRGB color, int start, int length) {
  if (start < 0) start = 0;
  if (start + length >= NUM_LEDS) length = NUM_LEDS - start;
 
  for (int light = start; light < start + length; light++)
    leds[light] = color;
}
 
void setAlternating(CRGB one, CRGB two, int start, int length) {
  if (start < 0) start = 0;
  if (start + length >= NUM_LEDS) length = NUM_LEDS - start;
 
  for (int light = start; light < start + length; light++)
    leds[light] = (light % 2 == 0) ? one : two;
}
 
void setChaserBlock(CRGB background, CRGB foreground, int start, int length, int chaserLength, int it) {
  setBlock(background, start, length);
  setBlock(foreground, start + it - chaserLength, chaserLength);
}

