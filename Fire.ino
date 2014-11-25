#include <Adafruit_NeoPixel.h>

#define PIN 2
Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for (int iii=0;iii<8;iii=iii+4) {
  if (random(100) < 98 )         strip.setPixelColor(iii, strip.Color(random(120)+135, 0, 0));
  else      {
    int c=random(50);
   // strip.setPixelColor(iii, strip.Color(c+135, c+135,0));
    strip.setPixelColor(iii, strip.Color(255, 120,0));
  }
  }
  strip.show();
  delay(random(100));
}

