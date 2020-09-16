#include <math.h>
#include <FastLED.h>
#include "fibonacci.h"
#include "layout.h"
#include "Moon_64.h"
#include "vec2.h"

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
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_CENTER  256
#define NUM_EDGE    84
#define NUM_LEDS    (1 + NUM_CENTER + NUM_EDGE)
#define DEG         (PI / 180)
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          8
#define FRAMES_PER_SECOND  120
CHSV g_hsv;

CRGB get_color565(uint16_t color){
  uint8_t r, g, b;

  r = (color & 0b1111100000000000) >> (11);
  g = (color & 0b0000011111100000) >> (5);
  b = (color & 0b0000000000011111) >> (0);
  return CRGB(r, g, b);
}
void setup() {
  g_hsv.hue = 0;
  //g_hsv.val = 255;
  g_hsv.val = 255;
  g_hsv.sat = 140;

  Serial.begin(115200);
  delay(6000); //  seconds delay for recovery
  Serial.println("Powered by WyoLum.com");
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
SimplePatternList gPatterns = {rain, xy, ball};//, palette, xy};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint16_t g_fib_steps[14] = {21, 157, 4, 5, 7, 8, 10, 12, 13, 14, 16, 18, 19, 20};
int8_t g_fib_step_idx = 0;
int16_t g_fib_step = 4;
int16_t g_fib_offset = 0;
uint8_t g_n_fib_step = 14;

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
    set_absolute(fibindex[i], color);
  }
}

uint8_t fib_lookup(uint8_t i){
  uint8_t out = 0;
  for(out=0; out<256; out++){
    if(fibindex[out] == i){
      return out;
    }
  }
}

void draw_hand(int16_t start, uint8_t step, const struct CRGB&  color){
  for(int j=start; j >= 0; j -= step){
    set_fibonacci(j, color);
  }
}

void rainbow_hand(int16_t start, uint8_t step, int8_t deltahue){
  uint8_t hue_start = g_hsv.hue;
  for(int j=start; j > 0; j -= step){
    set_fibonacci(j, g_hsv);
    g_hsv.hue += deltahue;
  }
  //g_hsv.hue = (g_hsv.hue - start/step * deltahue) % 256;
  g_hsv.hue = hue_start;
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
    set_edge(led, color);
  }
}

uint8_t fade_index = 0;
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND);
  delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS(20){
    fadeToBlackBy( leds, NUM_LEDS, 1);
  }
  EVERY_N_MILLISECONDS(50) {
    gHue++;
    g_hsv.hue--;
    fade_index++;
    fade_index %= 192;
  } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS(20){
    nextPattern(); // change patterns periodically
  } 
  EVERY_N_SECONDS(10){
    g_fib_offset--;
  }
  EVERY_N_SECONDS(10){
    //g_fib_step_idx = (g_fib_step_idx + 1) % g_n_fib_step;
    //g_fib_step = g_fib_steps[g_fib_step_idx];
    //g_fib_step++;
    //Serial.println(g_fib_step);
  }
  int cur = 0;
  char c;
  char response[10];
  if(Serial.available()){
    while(Serial.available()){
      g_fib_step++;
      c = Serial.read();
      response[cur++] = c;
      Serial.print(c);
    }
    Serial.println();
    response[cur] = 0;
    fadeToBlackBy(leds, NUM_LEDS, 200);
    Serial.println(g_fib_step);
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

const uint8_t hour_leds[12] = {95, 97, 99,137,174,176,177,218,253, 18, 21, 58};
const uint8_t minute_leds[60] = {
232,211,245,224,203,237,216,250,229,208,208,221,221,255,234,213,247,226,205,239,218,252,197,231,210,244,223,202,236,215,249,228,207,207,220,220,199,233,212,246,225,204,238,217,251,196,209,209,243,222,201,235,214,248,227,206,240,219,219,198,
};
const uint8_t fib[6] = {5, 13, 34, 55, 21, 8};
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds, NUM_LEDS, 1);
  int pos = beatsin16( 13, 0, NUM_CENTER-1 );
  set_fibonacci((pos * g_fib_step) % 256, CHSV( gHue, 255, 192));
  uint8_t i = (millis() / 60000) % 12;
  uint8_t j = (millis() * 84 / 60000) % 84;
  uint8_t k = (millis() * 60 / 60000) % 60;

  uint8_t f = 2;
  uint8_t deltahue = 10;
  uint8_t hour_hand_start = fib_lookup(hour_leds[i]);
  uint8_t minute_hand_start = minute_leds[k];
  set_edge(j, g_hsv);
  draw_hour_edge(3600 * i, g_hsv);
  //rainbow_hand(hour_hand_start, fib[3], deltahue);
  //rainbow_hand(minute_hand_start, fib[2], deltahue);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 1;
  CRGBPalette16 palette = PartyColors_p;
  palette  = ForestColors_p;
  palette = CloudColors_p;
  palette = LavaColors_p;
  palette = OceanColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  //uint8_t beat = ((millis() % 60000) / 60000.) * 256;
  fadeToBlackBy( leds, NUM_LEDS, 1);
  for( int i = 0; i < NUM_CENTER; i++) { //9948
    //set_fibonacci((i * g_fib_step + g_fib_offset) % NUM_CENTER, ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10)));
    set_fibonacci((i * g_fib_step + g_fib_offset) % NUM_CENTER, ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*1)));
  }

  uint8_t i = (millis() / 60000) % 12;
  uint8_t j = (millis() * 84 / 60000) % 84;
  uint8_t k = (millis() * 60 / 60000) % 60;

  uint8_t f = 2;
  uint8_t deltahue = 10;
  uint8_t hour_hand_start = fib_lookup(hour_leds[i]);
  uint8_t minute_hand_start = minute_leds[k];
  set_edge(j, g_hsv);
  draw_hour_edge(3600 * i, g_hsv);
}

int xy_idx;
void xy(){
 // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 1;
  CRGBPalette16 palette;

  palette = OceanColors_p;
  palette = PartyColors_p;
  
  uint8_t t = millis()/100;
  float x, y;
  float theta = 2 * PI * millis() / 30000.;
  xy_idx++;
  xy_idx %= NUM_CENTER;
  x = (pixel_x[xy_idx] - cx) * cos(theta) - (pixel_y[xy_idx] - cy) * sin(theta);
  y = (pixel_x[xy_idx] - cy) * sin(theta) + (pixel_y[xy_idx] - cy) * cos(theta);
  set_absolute(xy_idx, CRGB(y + t,x + t,t + x-y));
}
float normal(float mean, float sigma, float x){
  //you will want to choose mean, sigma and scale the output value appropriately
  return exp(-0.5 * pow((x - mean) / sigma, 2.));
}

float normalized(float mean, float sigma, float x){
  return normal(mean, sigma, x) / normal(mean, sigma, 0);
}
float fmod(float num, float den){
  //always return positive number
  float out;
  if(num < 0){
    out = fmod(-num, (den - num));
  }
  else{
    out = num - ((int)(num / den)) * den;
  }
  return out;
}
void rtheta(){
 // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 1;
  CRGBPalette16 palette;

  palette = OceanColors_p;
  palette = PartyColors_p;
  
  float t = fmod(millis(), 60000.) * 2 * PI/60000. -  PI;
  float r, theta;
  float x, y;
  float h, s, v;
  for( int i = 0; i < NUM_CENTER; i++) {
    x = (pixel_x[i] - cx);
    y = (pixel_y[i] - cy);
    r = sqrt(x * x + y * y);
    theta = atan2(y, x);
    //v = normalized(0, .6 * DEG * cos(r * PI/256), theta * DEG) * 255;
    //v = normal(-t, 15 * DEG * cos(r * PI/270), theta) * 255;
    //v = normal(fmod(t - theta, 2 * PI), 90 * DEG, 0) * 255;
    v = fmod(theta + PI + 130 * DEG + t, 2 * PI) * 128 / PI;

    //Serial.print(s);
    leds[i+1] = CHSV(r - millis()/50, 255, v);
  }
}
void seconds21(){
  CRGBPalette16 palette = PartyColors_p;

  uint32_t row = millis()/2857.1428571428573 + 12;
  /*
  for(int i = 0; i < 12; i++){
    //set_fibonacci((i * 13 + t) % NUM_CENTER, ColorFromPalette(palette, gHue+(i*2), gHue+(i*1)));
    set_fibonacci((i * 21 + (-8*t)%21) % NUM_CENTER, CHSV(i * 8 + gHue, 255, 255));
    
  }
  */
  fadeToBlackBy( leds, NUM_LEDS, 1);
  uint32_t col = ((int)(millis() * 12 / 2857.1428571428573)) % 12;
  //set_fibonacci((col * 21 + (-8*row)%21) % NUM_CENTER, CHSV(row * 13 + gHue + col * 10, 255, 255));
  set_fibonacci((col * 21 + (-8*row)%21) % NUM_CENTER, ColorFromPalette(palette, gHue+(col*2), 255));
  
}

uint8_t fade[192] = {
  1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,
  3,   3,   3,   3,   4,   4,   5,   5,   6,   6,   7,   7,   8,
  9,  10,  11,  12,  13,  14,  15,  17,  18,  20,  22,  24,  26,
  29,  31,  34,  37,  41,  45,  49,  53,  58,  63,  69,  75,  82,
  90,  98, 107, 116, 127, 139, 151, 165, 180, 196, 214, 233, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 233, 214,
  196, 180, 165, 151, 139, 127, 116, 107,  98,  90,  82,  75,  69,
  63,  58,  53,  49,  45,  41,  37,  34,  31,  29,  26,  24,  22,
  20,  18,  17,  15,  14,  13,  12,  11,  10,   9,   8,   7,   7,
  6,   6,   5,   5,   4,   4,   3,   3,   3,   3,   2,   2,   2,
  2,   1,   1,   1,   1,   1,   1,   1,   1,   1};

void fade_in_out(){
  leds[1] = CHSV(255, 128, fade[fade_index]);
}

void seconds(){
  CRGBPalette16 palette = OceanColors_p;
  
  int t_step = millis() / 100;

  set_fibonacci((t_step * 21 + t_step % 21) % NUM_CENTER, ColorFromPalette(palette, gHue+(t_step/8), 255));
  
}

CRGBPalette16 myPalette(
			CRGB::Yellow,           // 0
			CRGB::Yellow + CRGB::Green,           // 1
			CRGB::Yellow,          // 2
			CRGB::Yellow,          // 3
			CRGB::Orange,           // 4
			CRGB::Yellow,          // 5
			CRGB::Yellow,          // 6 
			CRGB::Orange,          // 7 
			CRGB::Red,             // 8 
			CRGB::Green,           // 9 
			CRGB::Yellow + CRGB::Green,             //10 
			CRGB::Yellow,          //11 
			CRGB::Green,           //12 
			CRGB::Green,           //13 
			CRGB::Yellow,          //14
			CRGB::Green            //15
			);

void palette(){
  CRGBPalette16 palette = HeatColors_p;
  palette = myPalette;
  int i = (millis()/20) % NUM_LEDS;
  if(i < NUM_CENTER){
    set_fibonacci(i, ColorFromPalette(palette, i - gHue, 255));
  }
  else{
    set_edge(i - NUM_CENTER, ColorFromPalette(palette, i + 256 - gHue, 255));
  }
}

const int MAX_DROP = 50;
int drop_x[MAX_DROP];
int drop_y[MAX_DROP];
uint8_t drop_hue[MAX_DROP];

int n_drop = 0;
int dy = -5;
int dx = -2;
void rain(){
  CRGBPalette16 palette = OceanColors_p;
  
  int r2 = 200;
  float pct = 10;
  fadeToBlackBy( leds, NUM_LEDS, 2);
  if(random(100)  < pct && n_drop < MAX_DROP - 1){
    // make a new drop
    drop_x[n_drop] = random(256) + 50;
    drop_y[n_drop] = 256;
    drop_hue[n_drop] = random(256);
    n_drop++;
  }
  // fall drops
  int miny = 500;
  for(int i = 0; i < n_drop; i++){
    drop_y[i] += dy;
    drop_x[i] += dx;
    if(drop_y[i] < miny){
      miny = drop_y[i];
    }
  }

  // remove falled drops
  int n_removed = 0;
  for(int i = 0; i < n_drop; i++){
    if(drop_y[i] < -10){
      n_removed++;
    }
    else if(n_removed > 0){
      drop_x[i - n_removed] = drop_x[i];
      drop_y[i - n_removed] = drop_y[i];
      drop_hue[i - n_removed] = drop_hue[i];
    }
  }  
  n_drop -= n_removed;
  
  // light up drops
  for(int i = 0; i < n_drop; i++){
    for(int j = 0; j < 256; j++){
      int delta_x = pixel_x[j] - drop_x[i];
      int delta_y = pixel_y[j] - drop_y[i];
      int d2 = delta_x * delta_x + delta_y * delta_y;
      if(d2 < r2){
	
	//CHSV color = CHSV(drop_hue[i], 128, 256 * (r2 - d2)/ r2);
	CRGB color = ColorFromPalette(palette,  gHue + drop_hue[i], 255);
	if(leds[j] < color){
	  leds[j] = color;
	}
      }
    }
  }
}
const float G = .05;

float ball_pos[2] = {1, 80}; // relative to {cx, cy}
float ball_vel[2] = {.0, 0};
float ball_acc[2] = {0, -G};

uint8_t ball_hue;

const float diameter = 168;
const float radius = diameter / 2;
const float radius_sq = radius * radius;
float ball_energy(){
  
  // ensure conservation of energy
  float energy = .5 * dot2(ball_vel, ball_vel) + G * ball_pos[1];
  return energy;
}

void ball(){
  int r2 = 2500;// radius squared
  r2 = 2500 + 2499 * cos(2 * PI * millis()/10000);
  

  // fall ball
  float p2[2];// see page 120 in purple notebook 2020
  float p2_prime[2];// see page 120 in purple notebook 2020
  float pc[2];      // see page 120 in purple notebook 2020
  float tmp2[2];
  float ihat[2];
  float jhat[2];
  float ball_x, ball_y;
  float energy0, energy1;
  float speed;
  CRGBPalette16 palette = OceanColors_p;
  //palette = myPalette;

  // ensure conservation of energy
  energy0 = ball_energy();
    
  add2(ball_vel, ball_acc, ball_vel);// see page 120 in purple notebook 2020
  add2(ball_pos, ball_vel, p2_prime);// see page 120 in purple notebook 2020

  //scale2(ball_acc, .5, tmp2);
  //add2(p2_prime, tmp2, p2_prime);// see page 120 in purple notebook 2020

  //bounce ball
  if(norm2(p2_prime) > radius){
    gHue += 32;
    
    float A, B, C, t; // see page 120 in purple notebook 2020
    A = pow(norm2(ball_vel),2);
    B = 2 * dot2(ball_pos, ball_vel);
    C = pow(norm2(ball_pos), 2) - radius_sq;
    t = (-B + sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
    
    scale2(ball_vel, t, tmp2);
    add2(ball_pos, tmp2, pc);
    
    negate2(pc, ihat);
    normalize2(ihat);
    if(abs(norm2(ihat) - 1) > .0001){
      while(1){
	delay(1000);
      }
    }
    perp2(ihat, jhat);
    if(abs(dot2(ihat, jhat)) > .001){
      Serial.println("not orthog");
      print2(ihat, "ihat");
      print2(jhat, "jhat");
    }
    A = -dot2(ball_vel, ihat);
    B = dot2(ball_vel, jhat);
    scale2(ihat, A, tmp2);
    add2(pc, tmp2, p2);

    scale2(jhat, B, tmp2);
    add2(p2, tmp2, p2);
    
    copy2(p2, ball_pos);

    // vel = speed (ball_pos - pc) / ||.||
    speed = sqrt(2 * (energy0 - G * ball_pos[1]));
    
    sub2(ball_pos, pc, tmp2);
    normalize2(tmp2);
    scale2(tmp2, speed, ball_vel);

  }
  else{
    copy2(p2_prime, ball_pos);
  }

  // conservation of energy
  speed = norm2(ball_vel);
  if(speed > 1e-4){ // don't divide by zero!!
    speed = sqrt(2 * (energy0 - G * ball_pos[1]));
    normalize2(ball_vel);                          
    scale2(ball_vel, speed, ball_vel);
  }
  else{ // compensate with height
    float height;
    ball_pos[1] = (energy0 - .5 * pow(speed, 2)) / G;
  }
  
		 

  //energy1 = ball_energy();

  ball_x = ball_pos[0];
  ball_y = ball_pos[1];
  // light up ball
  for(int j = 0; j < NUM_LEDS; j++){
    int delta_x = layout_x[j] - ball_x;
    int delta_y = layout_y[j] - ball_y;
    int d2 = delta_x * delta_x + delta_y * delta_y;
    if(d2 < r2){
      // CRGB color = ColorFromPalette(palette, gHue, 256 * (r2 - d2)/ r2);
      // CHSV color = CHSV(gHue, 128, , 256 * (r2 - d2)/ r2);
      float max_speed = sqrt(2 * energy0);
      CRGB color = ColorFromPalette(palette,  gHue + 256 - 64 * speed / max_speed, 256 * (r2 - d2)/ r2);
      //if(leds[j] < color){
      leds[j] = color;
      //}
    }
  }
}
