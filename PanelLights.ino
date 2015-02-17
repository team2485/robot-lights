#include "FastLED.h"
#define NUM_LEDS 60

#define DATA_PIN 8
#define CLOCK_PIN 7

#define PIN1 9
#define PIN2 10
#define PIN3 11
#define PIN4 12

CRGB leds[NUM_LEDS];

/* Runs different animations for the lights panels
case 0: black
case 1: green block
case 2: yellow block
case 3: yellow seizure lights
case 4: white seizure lights
case 5: red single flash
case 6: happy rainbow
case 7: yellow chaser
case 8: yellow blink
case 9: red block
case 10: blue block
case 11: rainbow chaser
*/

void setup() {
   delay(200);
   FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

   pinMode(PIN1, INPUT);
   pinMode(PIN2, INPUT);
   pinMode(PIN3, INPUT);
   pinMode(PIN4, INPUT);

   Serial.begin(9600);
   Serial.println("Hey there Ian");
}
int showToRun = 10;
int i;
void loop() {
  if(i > 159)
    i = 0;

  //showToRun = digitalRead(PIN1) | digitalRead(PIN2) << 1 | digitalRead(PIN3) << 2 | digitalRead(PIN4) << 3;

  switch(showToRun){
    // black
    case 0:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Black;
      FastLED.show();
      break;
    }
    //green block
    case 1:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Green;
      FastLED.show();
      break;
    }
    //yellow block
    case 2:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB(255, 100, 0);
      FastLED.show();
      break;
    }
    //yellow seizure lights
    case 3:{
      if(i%2 == 0){
        for(int numLights = 0; numLights < NUM_LEDS; numLights++){
          if(numLights%2 == 0)
            leds[numLights] = CRGB(255, 100, 0);
          if(numLights%2 == 1)
            leds[numLights] = CRGB::Black;
        }
      }
      if(i%2 == 1){
        for(int numLights = 0; numLights < NUM_LEDS; numLights++){
          if(numLights%2 == 1)
            leds[numLights] = CRGB(255, 100, 0);
          if(numLights%2 == 0)
            leds[numLights] = CRGB::Black;
        }
      }
      delay(100);
      FastLED.show();
      break;
    }
    //white seizure lights
    case 4:{
      if(i%2 == 0){
        for(int numLights = 0; numLights < NUM_LEDS; numLights++){
          if(numLights%2 == 0)
            leds[numLights] = CRGB::White;
          if(numLights%2 == 1)
            leds[numLights] = CRGB::Black;
        }
      }
      if(i%2 == 1){
        for(int numLights = 0; numLights < NUM_LEDS; numLights++){
          if(numLights%2 == 1)
            leds[numLights] = CRGB::White;
          if(numLights%2 == 0)
            leds[numLights] = CRGB::Black;
        }
      }
      delay(100);
      FastLED.show();
      break;
    }
    //red single flash
    case 5:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Red;
      FastLED.show();
      delay(500);
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Black;
      FastLED.show();
      delay(2000);
      break;
    }
    //happy rainbow
    case 6:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB(random(100), random(100), random(100));
      FastLED.show();
      break;
    }
    //yellow chaser
    case 7:{
      leds[i] = CRGB(255, 100, 0);
      leds[i+80] = CRGB(255, 100, 0);
      if(i > 10){
        leds[i-10] = CRGB::Black;
        leds[i+70] = CRGB::Black;
      }
      FastLED.show();
      delay(10);
      break;
    }
    //yellow blink
    case 8:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB(255, 100, 0);
      FastLED.show();
      delay(500);
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Black;
      FastLED.show();
      delay(500);
      break;
    }
    //red block
    case 9:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Red;
      FastLED.show();
      break;
    }
    //blue block
    case 10:{
      for(int numLights = 0; numLights < NUM_LEDS; numLights++)
        leds[numLights] = CRGB::Blue;
      FastLED.show();
      break;
    }
    //rainbow chaser
    case 11:{
      leds[i] = CRGB::Red;
      leds[i-1] = CRGB::Red;
      leds[i-2] = CRGB::Orange;
      leds[i-3] = CRGB::Orange;
      leds[i-4] = CRGB::Yellow;
      leds[i-5] = CRGB::Yellow;
      leds[i-6] = CRGB::Green;
      leds[i-7] = CRGB::Green;
      leds[i-8] = CRGB::Blue;
      leds[i-9] = CRGB::Blue;
      leds[i-10] = CRGB::Purple;
      leds[i-11] = CRGB::Purple;
      leds[i-12] = CRGB::Black;
      FastLED.show();
      delay(10);
      break;
    }
  }

  i++;
  Serial.println(showToRun);
}
