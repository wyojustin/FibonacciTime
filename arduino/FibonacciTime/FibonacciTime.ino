#include <Time.h>
#include <Wire.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <EEPROM.h>
#include <EEPROMAnything.h>

#include "credentials.h"
#include "FastLED.h"
#include "get_time.h"
#include "config.h"
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


#define DATA_PIN    4 //32 //21
#define LED_TYPE    WS2812
#define pi         3.14159
//#define CLK_PIN   19
//#define LED_TYPE    APA102

#define COLOR_ORDER     GRB
#define NUM_EDGE         84
#define NUM_CENTER      256
#define NUM_LEDS       (NUM_EDGE + NUM_CENTER)
#define FADE_INDEX_LEN 193

CRGBPalette16 palette = OceanColors_p;

uint8_t fade[FADE_INDEX_LEN] = {0, // remain off indef, setting index to one starts automated increments
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

CRGB leds[NUM_LEDS];
CHSV hsv_leds[NUM_CENTER];
uint8_t fade_index[NUM_CENTER];
void increment_fade(){
  //Serial.println(fade_index[0]);
  for(int i = 0; i < NUM_CENTER; i++){
    if(0 < fade_index[i]){
      float x = pixel_x[i] - cx;
      float y = pixel_y[i] - cy;
      float theta = atan2(y, x);
      if(theta < 0){
	theta += 2 * PI;
      }
      
      fade_index[i] += 1;
      fade_index[i] %= FADE_INDEX_LEN;
      hsv_leds[i].hue = (uint8_t)(theta * 256 / (2 * PI)) + millis()/100 % 256;
      hsv_leds[i].value = fade[fade_index[i]]/4;
      leds[i] = ColorFromPalette(palette, hsv_leds[i].hue, fade[fade_index[i]]/4);
    }
  }
}

void set_absolute(uint16_t i, const struct CRGB& color){
  if(i < NUM_LEDS){
    leds[i] = color;
  }
}
void set_edge(uint16_t i, const struct CRGB& color){
  uint16_t led = NUM_CENTER + i;
  set_absolute(led, color);
}
void set_fibonacci(uint16_t i, const struct CRGB& color){
  if(i < 256){
    set_absolute(fibindex[i], color);
  }
}
void add_absolute(uint16_t i, const struct CRGB& color){
  if(i < NUM_LEDS){
    leds[i] += color;
  }
}
void add_edge(uint16_t i, const struct CRGB& color){
  uint16_t led = NUM_CENTER + i;
  add_absolute(led, color);
}
void add_fibonacci(uint16_t i, const struct CRGB& color){
  if(i < 256){
    add_absolute(fibindex[i], color);
  }
}

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

WiFiManager wifiManager;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "us.pool.ntp.org", 0, 60000); //Default

NTPClock ntp_clock;
DS3231Clock ds3231_clock;
DoomsdayClock doomsday_clock;
struct config_t{
  int timezone;
  uint8_t brightness;
  uint8_t display_idx;
  bool factory_reset;
  bool use_wifi;
  bool use_ip_timezone;
  byte mqtt_ip[4];
  bool flip_display;
  uint32_t last_tz_lookup; // look up tz info every Sunday at 3:00 AM
  uint8_t solid_color_rgb[3];
  bool use_ntp_time;
  bool wifi_reset;
  uint8_t faceplate_idx;
} config;


bool setup_complete = false;

void print_config(){
  Serial.println("config:");
  Serial.print("    timezone:"); Serial.println(config.timezone);
  Serial.print("    brightness:"); Serial.println(config.brightness);
  Serial.print("    display_idx:"); Serial.println(config.display_idx);
  Serial.print("    factory_reset:"); Serial.println(config.factory_reset);
  Serial.print("    use_wifi:"); Serial.println(config.use_wifi);
  Serial.print("    use_ip_timezone:"); Serial.println(config.use_ip_timezone);
  Serial.print("    mqtt_ip:");
  for(int ii = 0; ii < 4; ii++){
    if (ii > 0){
      Serial.print(".");
    }
    Serial.print(config.mqtt_ip[ii]);
  }
  Serial.println();
  Serial.print("    flip_display:"); Serial.println(config.flip_display);
  Serial.print("    last_tz_lookup:"); Serial.println(config.last_tz_lookup);
  Serial.print("    solid_color_rgb:");
  for(int ii = 0; ii < 3; ii++){
    if (ii > 0){
      Serial.print(".");
    }
    Serial.print(config.solid_color_rgb[ii]);
  }
  Serial.println();
  Serial.print("    use_ntp_time:"); Serial.println(config.use_ntp_time);
  Serial.print("    wifi_reset:"); Serial.println(config.wifi_reset);
  Serial.print("    faceplate_idx:"); Serial.println(config.faceplate_idx);
}

void wifi_setup(){
  if(config.wifi_reset){
    config.wifi_reset = false;
    saveSettings();
    wifiManager.startConfigPortal("Fibonacci");
  }
  else{
    wifiManager.autoConnect("Fibonacci");
  }
  /*
  Serial.println(ssid);
  Serial.println(pass);
  while(WiFi.begin(ssid, pass)!= WL_CONNECTED){
    Serial.println("Try...");
    delay(1000);
  }
  */
  Serial.println("Yay connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

uint32_t last_second = 0;
uint32_t first_change_ms = 0;
uint32_t last_change_ms = 0;
uint32_t number_of_seconds = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("WyoLum.com!");
  delay(6000);
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).
    setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInMilliWatts(2000);
  wifi_setup();

  ntp_clock.setup(&timeClient);
  ntp_clock.setOffset(config.timezone);
  ds3231_clock.set(ntp_clock.now());
  doomsday_clock.setup(&ntp_clock, &ds3231_clock);
  
  set_timezone_from_ip();
  last_second = ds3231_clock.now();
  while(last_second == ds3231_clock.now()){
  }
  number_of_seconds = 0;
  first_change_ms = millis();
  last_second = Now();
  last_change_ms = millis();
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
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;
  }
  EVERY_N_MILLISECONDS(1) {
    increment_fade();
  }
  EVERY_N_MILLISECONDS(100 ) {
    fadeToBlackBy(leds + NUM_CENTER, NUM_EDGE, 5);
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


void off(uint16_t start, uint16_t length){
  for(int i = start; i < start + length; i++){
    leds[i] = CRGB::Black;
  }
}
void off(){
  off(0, NUM_LEDS);
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
  int led;
  float theta = (2 * pi * minutes) / (720);
  
  uint8_t idx = 21 * theta / (2 * pi);
  draw_left_arm(idx + 2);
}

void draw_hour_edge(unsigned long long t){
  float minutes = t / 60.;
  int hh = (t / 3600) % 12;
  int led;
  float hh_float = (t / 3600.);
  hh_float -= (int)(hh_float / 3600) * 3600;
    
  // edge lighting
  for(int i = 0; i < 7; i++){
    led = hh * 7 + 17 + i;
    led %= NUM_EDGE;
    set_edge(led, CRGB::Cyan);
  }
  led = (int)(hh_float * 7 + 17) % NUM_EDGE;
  set_edge(led, CRGB::White);
}

void draw_minute_hand(unsigned long long t){
  float theta = 2 * pi * t / 3600;
  uint8_t idx = 13 * theta / (2 * pi);
  idx %= 13;
  
  draw_right_arm(idx);
}

void draw_minute_edge(unsigned long long t){
  int led, mm;
  float theta = (2 * pi * (t % 86400)) / 3600;

  // edge lighting
  mm = (theta * NUM_EDGE) / (2 * pi);
  mm %= NUM_EDGE;
  for(int i = 2; i < 5; i++){
    led = mm + 17 + i;
    led %= NUM_EDGE;
    set_edge(led, CRGB(0, 255, 32));
  }
  
}

void draw_seconds_edge(unsigned long long t, uint16_t ms){
  uint8_t idx;
  float theta = 2 * pi * ((t % 60) + ms / 1000.) / 60.;
  idx = NUM_EDGE * theta / (2 * pi) + 23;
  idx %= NUM_EDGE;
  add_edge(idx, CRGB::Blue);
}

uint32_t Now(){
  uint32_t out;

  if(config.use_wifi){
    if(config.use_ntp_time){
      if(setup_complete){
	out = doomsday_clock.now();
      }
      else{
	out = 0;
      }
      if(weekday(out) == 1){ // refresh utc offset sunday between 3:02 and 3:59 AM
	if(hour(out) == 3){
	  if(minute(out) > 1){ 
	    if(doomsday_clock.gmt() - config.last_tz_lookup > 86400 -2 * 60){// at most one update per day
	      Serial.print(" Check DST!! ");
	      Serial.print(hour(out));Serial.print(":");
	      Serial.print(minute(out));Serial.print("\n");
	      set_timezone_from_ip();
	    }
	  }
	}
      }
    }
    else{
      out = ds3231_clock.now();
    }
  }
  else{
    out = ds3231_clock.now();
  }
  if(out != last_second){
    last_second = out;
    //Serial.print("millis() - last_change_ms");Serial.println(millis() - last_change_ms);
    last_change_ms = millis();
  }
  return out;
}

void seconds(uint32_t t, uint16_t ms){//21
  t %= 86400;
  t = t * 1000 + ms;
  
  uint32_t row = t /2857.1428571428573 + 15;
  /*
  for(int i = 0; i < 12; i++){
    //set_fibonacci((i * 13 + t) % NUM_CENTER, ColorFromPalette(palette, gHue+(i*2), gHue+(i*1)));
    set_fibonacci((i * 21 + (-8*t)%21) % NUM_CENTER, CHSV(i * 8 + gHue, 255, 255));
    
  }
  */
  uint32_t col = ((int)(t * 12 / 2857.1428571428573)) % 12;
  uint16_t idx = (col * 21 + (-8*row)%21) % NUM_CENTER;

  //set_fibonacci((col * 21 + (-8*row)%21) % NUM_CENTER, CHSV(row * 13 + gHue + col * 10, 255, 255));
  fade_index[fibindex[idx]] = 1;// kick off fade run
  hsv_leds[idx] = CHSV(gHue + col*4, 32, 1);
  set_fibonacci(idx, hsv_leds[idx]);
}
void seconds8(uint32_t t, uint16_t ms){//8
  t %= 86400;
  t = t * 1000 + ms;
  
  float t_step = 60000 / 32.;
  uint32_t row = t/t_step;
  uint32_t col = ((int)(t * 32 / t_step)) % 32;

  set_fibonacci((col * 8 + (5*row)%8) % NUM_CENTER, ColorFromPalette(palette, gHue+(col*2), 64));
  
}

void simple_clock(){
  unsigned long long t;
  uint16_t ms;
  
  t = Now();
  ms = millis() - last_change_ms;
  //off(1 + NUM_CENTER, NUM_RING);
  draw_hour_edge(t);
  draw_minute_edge(t);
  //draw_seconds_edge(t, ms);
  seconds(t, ms);
  delay(100);
}

// return json value for name identified (or "not found")
String jsonLookup(String s, String name){
  String out;
  int start, stop;
  
  name = String("\"") + name + String("\""); // add bounding quotes

  start = s.indexOf(name);
  if(start < 0){
    out = String("not found");
  }
  else{
    start +=  name.length() + 2;
    stop = s.indexOf('"', start);
    out = s.substring(start, stop);
  }
  return out;
}

void set_timezone_offset(int32_t offset){
  config.timezone = offset % 86400;
  saveSettings();
  if(config.use_wifi){
    ntp_clock.setOffset(config.timezone);
  }
}

void set_timezone_from_ip(){

  HTTPClient http;
  String payload;
  
  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
  // http.begin("http://example.com/index.html"); //HTTP

  //http.begin("https://timezoneapi.io/api/ip");// no longer works!
  String url = String("https://www.wyolum.com/utc_offset/utc_offset.py") +
    String("?refresh=") + String(millis()) +
    String("&localip=") +
    String(WiFi.localIP()[0]) + String('.') + 
    String(WiFi.localIP()[1]) + String('.') + 
    String(WiFi.localIP()[2]) + String('.') + 
    String(WiFi.localIP()[3]) + String('&') +
    String("macaddress=") + WiFi.macAddress() + String('&') + 
    String("dev_type=FibonacciTime");
  Serial.println(url);
  http.begin(url);
  
  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  
  // httpCode will be negative on error
  //httpCode = -1; // force error
  if(httpCode < 0){
    http.end();
    url = String("https://ipapi.co/json/?key=");
    Serial.print("Using backup url:");
    Serial.println(url + "<SECRET KEY>");
    http.begin(url + ipapikey);
  
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    httpCode = http.GET();
  }
  payload = http.getString();
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    
    // file found at server
    //String findme = String("offset_seconds");
    if(httpCode == HTTP_CODE_OK) {
      Serial.print("payload:");
      Serial.println(payload);
      payload.replace(" ", "");
      String offset_str = jsonLookup(payload, String("utc_offset"));
      int hours = offset_str.substring(0, 3).toInt();
      int minutes = offset_str.substring(3, 5).toInt();
      if(hours < 0){
	minutes *= -1;
      }
      int offset = hours * 3600 + minutes * 60;

      String utc_str =jsonLookup(payload, String("utc"));
      Serial.print("  UTC:"); Serial.println(utc_str);
      if(!utc_str.equals("not found")){
	uint32_t local = utc_str.toInt() + offset;
	Serial.print("Local:");Serial.println(local);
	ds3231_clock.set(local);
      }
      Serial.println((int)doomsday_clock.master);
      if(doomsday_clock.master->initialized){
	Serial.println("NTP is clock alive!");
      }
      else{
Serial.println("No NTP, fall back to DS3231");
      }
      Serial.println();
      if(config.use_ip_timezone){
	Serial.print("timezone_offset String:");
	Serial.println(offset_str);
	Serial.print("timezone_offset:");
	Serial.println(offset);
	set_timezone_offset(offset);
	config.last_tz_lookup = doomsday_clock.gmt();
	saveSettings();
      }
      else{
	Serial.println("Using previously selected timezone");
      }
    }
    else{
      Serial.println("No timezone found");
      Serial.println("Payload:");
      Serial.println(payload);
    }
  }
}

void clock_test(){
  unsigned long long i, j, k, led, hh, mm, ss;
  uint32_t now = millis();
  while(1){
    for(i = 0; i < 13; i++){
      off();
      draw_right_arm(i);
      FastLED.show();
      delay(100);
    }
    for(i = 0; i < 3600 * 2; i+= 60){
      off();
      draw_minute_edge(i);
      FastLED.show();
      delay(100);
    }
    draw_minute_edge(0);
    delay(5000);
    for(i = 0; i < 60; i++){
      off();
      draw_seconds_edge(i, i * 1000/60.);
      FastLED.show();
      delay(10);
    }
    delay(1000);
    for(i = 0; i < (unsigned long long)12 * 3600; i+= 60){
      off();
      draw_hour_edge(i);
      FastLED.show();
    }
    draw_hour_edge(0);
    delay(4000);
  }
}


void loadSettings(){
  EEPROM_readAnything(0, config);
}

void saveSettings(){
  EEPROM_writeAnything(0, config);
  EEPROM.commit();
}
