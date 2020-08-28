#include "FastLED.h"

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



#define DATA_PIN    A5
#define LED_TYPE    WS2812
#define pi         3.14159
//#define CLK_PIN   19
//#define LED_TYPE    APA102

#define COLOR_ORDER GRB
#define NUM_RING     84
#define NUM_CENTER  256
#define NUM_LEDS    (NUM_RING + NUM_CENTER)

CRGB leds[NUM_LEDS];

#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  120

void setup() {
  Serial.begin(115200);
  Serial.println("WyoLum.com!");
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).
    setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInMilliWatts(2000);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  //clock_test();
  simple_clock();

  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


void off(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
}

const uint8_t l_arms[21 * 12] = {
    20,57,62,93,105,129,147,165,190,201,232,
    58,61,94,104,130,146,166,189,202,231,238,
    60,95,103,131,145,167,188,203,230,239,2,
    59,96,102,132,144,168,187,204,229,240,3,
    97,101,133,143,169,186,205,228,241,4,37,
    98,100,134,142,170,185,206,227,242,5,36,
    99,135,141,171,184,207,226,243,6,35,42,
    136,140,172,183,208,225,244,7,34,43,76,
    137,139,173,182,209,224,245,8,33,44,75,
    138,174,181,210,223,246,9,32,45,74,81,
    175,180,211,222,247,10,31,46,73,82,116,

    176,179,212,221,248,11,30,47,72,83,115, 

    178,213,220,249,12,29,48,71,84,114,120,
    177,214,219,250,13,28,49,70,85,113,121,
    215,218,251,14,27,50,69,86,112,122,154,
    217,252,15,26,51,68,87,111,123,153,159,
    216,253,16,25,52,67,88,110,124,152,160,
    254,17,24,53,66,89,109,125,151,161,194,
    255,18,23,54,65,90,108,126,150,162,193,
    19,22,55,64,91,107,127,149,163,192,199,
    21,56,63,92,106,128,148,164,191,200,233,
};

const uint8_t r_lens[13] =   {
  20, 20, 19, 20, 20, 19, 20, 19, 20, 20, 19, 20, 20
};
const uint8_t r_starts[13] = {
  0, 20,  39,  59,  79,  99, 118, 138, 157, 177, 196, 216, 236
};

void draw_left_arm(uint8_t idx){
  uint8_t j;
  idx %= 21;
  for(j = 0; j < 11; j++){
    leds[l_arms[11 * idx + j]] += CRGB::Green / 8;
  }
}

void draw_right_arm(uint8_t idx){
  uint8_t j;
  idx %= 13;
  
  for(j = 0; j < r_lens[(idx+3)%13]; j++){
    leds[r_starts[(idx + 3) % 13] + j] += CRGB::Blue/8;
  }
}

void draw_hour_hand(unsigned long long t){
  float minutes = t / 60.;
  int hh = (t / 3600) % 12;
  int led;
  float theta = (2 * pi * minutes) / (720);
  
  uint8_t idx = 21 * theta / (2 * pi);
  draw_left_arm(idx + 2);
  
  // edge lighting
  for(int i = 0; i < 7; i++){
    led = hh * 7 + 17 + i;
    led %= NUM_RING;
    leds[NUM_CENTER + led] += CRGB::Green;
  }
}

void draw_minute_hand(unsigned long long t){
  int led, mm;
  float theta = 2 * pi * t / 3600;
  uint8_t idx = 13 * theta / (2 * pi);
  idx %= 13;
  
  draw_right_arm(idx);

  // edge lighting
  mm = (theta * NUM_RING) / (2 * pi);
  mm %= NUM_RING;
  for(int i = 0; i < 7; i++){
    led = mm + 17 + i;
    led %= NUM_RING;
    leds[NUM_CENTER + led] += CRGB::Blue;
  }
  
}

void draw_seconds(unsigned long long t, uint16_t ms){
  uint8_t idx;
  float theta = 2 * pi * (t + ms / 1000.) / 60.;
  
  idx = NUM_RING * theta / (2 * pi) + 20;
  idx %= NUM_RING;
  leds[NUM_CENTER + idx] += CRGB::White/8;
}


void simple_clock(){
  unsigned long long t;
  uint16_t ms;
  
  t = 100 * millis()  / 1000 + 12000;
  ms = millis() % 1000;
  off();
  draw_hour_hand(t);
  draw_minute_hand(t);
  //draw_seconds(t, ms);
}
void clock_test(){
  unsigned long long i, j, k, led, hh, mm, ss;
  uint32_t now = millis();
  CRGBPalette16 palette = PartyColors_p;
  while(1){
    for(i = 0; i < 13; i++){
      off();
      draw_right_arm(i);
      FastLED.show();
      Serial.println((int)i);
      delay(10000);
    }
  }
  while(1){
    for(i = 0; i < 3600 * 2; i+= 60){
      off();
      draw_minute_hand(i);
      FastLED.show();
      delay(100);
    }
    draw_minute_hand(0);
    delay(5000);
    for(i = 0; i < 60; i++){
      off();
      draw_seconds(i, i * 1000/60.);
      FastLED.show();
      delay(10);
    }
    delay(1000);
    for(i = 0; i < (unsigned long long)12 * 3600; i+= 60){
      off();
      draw_hour_hand(i);
      FastLED.show();
    }
    draw_hour_hand(0);
    delay(4000);
  }
}

