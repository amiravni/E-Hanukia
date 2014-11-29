/*
wires: 
white-pin5
grey - GND
pink - VCC
blue - pin2
*/

#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

#define RECV_PIN 5
#define PIN 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, PIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(RECV_PIN);
decode_results results;
int candlesFlag[9]={
  0,0,0,0,1,0,0,0,0};
//    1,1,1,1,1,1,1,1,1};
int numOfCandles=0;
int pattern=0;
int j = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver  
  attachInterrupt(0, button1, FALLING);
  attachInterrupt(1, button2, RISING);
}

void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
    case 1834108717:
      pattern++;
      break;      
    case 1416517997:
      candlesFlag[0]=1;
      break;
    case 3402334771:
      candlesFlag[1]=1;
      break;
    case 2756177041:         
      candlesFlag[2]=1;
      break;  
    case 1126035863:         
      candlesFlag[3]=1;
      break;     
    case 3083090929:         
      candlesFlag[5]=1;
      break;      
    case 3953766327:         
      candlesFlag[6]=1;
      break;       
    case 1909591125:         
      candlesFlag[7]=1;
      break;   
    case 814668755:         
      candlesFlag[8]=1;
      break;           
    case 2741535633:         
      for (int iii;iii<9;iii++)         candlesFlag[iii]=1;
      break;     
    case 635951127:         
      for (int iii;iii<9;iii++)         candlesFlag[iii]=0;
      candlesFlag[4]=1;
      break;                
    }
    if (results.value != 0x4AB0F7B6 && results.value != 0x4AB0F7B5 && results.value != 0x4AB0F7B7 && results.value != 0xFFFFFFFF) {
      Serial.println(results.value, DEC);
    }
    irrecv.resume(); // Receive the next value
  }
  for (int iii=0;iii<9;iii=iii+1) {
    if (!candlesFlag[iii])
    {
      strip.setPixelColor(iii, strip.Color(0, 0, 0));
    }
    else if (candlesFlag[iii]==1)
    { 
      if( pattern%2==0)
      {
          if (random(100) < 99 )         strip.setPixelColor(iii, strip.Color(random(120)+135, 0, 0));
          else      {
            int c=random(50);
            // strip.setPixelColor(iii, strip.Color(c+135, c+135,0));
            strip.setPixelColor(iii, strip.Color(255, 120,0));
          }
      }
      else
      {
        strip.setPixelColor(iii, Wheel(((iii * 256 / strip.numPixels()) + j) & 255));
        j++;
        //delay(10);
      }
    }
  }
  strip.show();
  delay(100);
}

void button1()
{
  if (numOfCandles<8)
  {
    if (numOfCandles<4)
    {
      candlesFlag[numOfCandles]=1;
    }
    else
    {
      candlesFlag[numOfCandles+1]=1;
    }
    numOfCandles++;
  }
}

void button2()
{
  for (int iii;iii<9;iii++)         candlesFlag[iii]=0;
  candlesFlag[4]=1;
  pattern++;
  numOfCandles=0;
}

uint32_t Wheel(int WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else if (WheelPos < 255) {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else
  {
    WheelPos -= 255;  
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


