#include <FastLED.h>
#include "fibonacci.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_EDGE     84
#define NUM_CENTER  256
#define NUM_LEDS    (NUM_EDGE + NUM_CENTER + 1)
#define PI 3.14159

CRGB leds[NUM_LEDS];
void set_absolute(uint16_t i, const struct CRGB& color){
  if(i < NUM_LEDS){
    leds[i] = color;
  }
}
void set_edge(uint16_t i, const struct CRGB& color){
  uint16_t led = 1 + NUM_CENTER + i;
  set_absolute(led, color);
}
void set_fibonacci(uint16_t i, const struct CRGB& color){
  if(i < 256){
    set_absolute(1 + fibindex[i], color);
  }
}


#define BRIGHTNESS         8
#define FRAMES_PER_SECOND  10

void set_pixel(int i, CRGB color){
  set_absolute(i + 1, color);
}

CHSV hsv;
void setup() {
  hsv.hue = 0;
  hsv.val = 255;
  hsv.sat = 240;
  Serial.begin(115200);
  Serial.println("powered by WyoLum.com");
  delay(2000); // limit reset frequency to 1 Hz!
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void jazz();

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {one};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  //gPatterns[gCurrentPatternNumber]();
  rainbow_hours();
  // send the 'leds' array out to the actual LED strip
  //fill_solid(leds, NUM_LEDS, CRGB::Black);

  //FastLED.show();  
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  //EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void off(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
}
//                       12   1   2   3   4   5   6   7   8   9  10  11
uint8_t hour_leds[12] = {95, 97, 99,137,174,176,177,218,253, 18, 21, 58};
//uint8_t hour_leds[12] = { };

uint8_t fib_lookup(uint8_t i){
  uint8_t out = 0;
  for(out=0; out<256; out++){
    if(fibindex[out] == i){
      return out;
    }
  }
}

void setFib(int16_t i, const struct CRGB& color){
  set_pixel(fibindex[i], color);
}

void draw_hand(int16_t start, uint8_t step, const struct CRGB&  color){
  for(int j=start; j >= 0; j -= step){
    setFib(j, color);
  }
}

void rainbow_hand(int16_t start, uint8_t step, int8_t deltahue){
  for(int j=start; j > 0; j -= step){
    setFib(j, hsv);
    hsv.hue += deltahue;
  }
  hsv.hue = (hsv.hue - start/step * deltahue) % 256;
}

void draw_hour_edge(unsigned long long t, const struct CRGB& color){
  float minutes = t / 60.;
  int hh = (t / 3600) % 12;
  int led;
  float theta = (2 * PI * minutes) / (720);
    
  // edge lighting
  for(int i = 0; i < 7; i++){
    led = hh * 7 + 17 + i;
    led %= NUM_EDGE;
    set_pixel(NUM_CENTER + led, color);
  }
}

//uint8_t fib[6] = {5, 8, 13, 21, 34, 55};
uint8_t fib[6] = {5, 13, 34, 55, 21, 8};

void hours(){
  for(uint8_t f = 1; f < 2; f++){
    for(int i=0; i < 1; i++){
      off();
      draw_hour_edge(i * 3600, CRGB::Blue);
      
      // find hour in fibindex and count back from there
      //uint8_t hand_start = fib_lookup(hour_leds[i]);
      //draw_hand(hand_start, fib[f], CRGB::Blue);
      //FastLED.show();
      //FastLED.delay(100);
    }
  }
}

void rainbow_hours(){
  off();
  draw_hour_edge(3 * 3600, CRGB::Blue);
  int8_t deltahue = 10;
  int i = (millis() / 1000) % 12;
  uint8_t f = (millis() / 13000) % 6;
  Serial.println(f);
  off();
  //draw_hour_edge(i * 3600, hsv);
      
  // find hour in fibindex and count back from there
  uint8_t hand_start = fib_lookup(hour_leds[i]);
  rainbow_hand(hand_start, fib[f], deltahue);
  for(i=0; i < NUM_EDGE; i++){
    set_edge(i, CRGB::Green);
  }
  FastLED.show();
  FastLED.show();
  //FastLED.delay(0);
}


void jazz(){
  uint8_t deltahue = 10;
  uint8_t fibidx = (millis() / 5000) % 6;
  uint8_t step = fib[fibidx];
  off();
  rainbow_hand(255, step, deltahue);
}  
// 34
void one(){
  for(uint16_t i = 0; i < 64; i++){
    //set_fibonacci(i, CRGB::Black);
  }
  for(uint16_t i = 4; i < 4 + 16; i++){
    set_fibonacci(i, CRGB::Blue);
  }
  

  for(uint16_t i = 256-35; i < 256; i++){
    set_fibonacci(i, CRGB::Green);
  }
}
