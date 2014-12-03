#include <Servo.h>

/*
wires: 
 white-pin5
 grey - GND
 pink - VCC
 blue - pin2
 */

#include "pitches.h"
#include "SongsInfo.h"
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



int numOfSongs = 4;
int songsN[] = {
  SONG1_NOTES,SONG2_NOTES,SONG3_NOTES,SONG4_NOTES};
int songsD[] = {
  SONG1_DUR, SONG2_DUR,SONG3_DUR,SONG4_DUR};
int songsS[]={
  SONG1_SIZE,SONG2_SIZE,SONG3_SIZE,SONG4_SIZE,1};


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver  
  attachInterrupt(0, button1, FALLING);
}

void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
    case 635951127:
      playSong(1);
      break; 
    case 1975606519:
      playSong(2);
      break; 
    case 2154077425:
      playSong(3);
      break; 
    case 1824319917:
      playSong(4);
      break;       
    case 3742150327:
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
      for (int iii=0;iii<9;iii++)         candlesFlag[iii]=1;
      break;     
    case 1834108717:         
      for (int iii=0;iii<9;iii++)         candlesFlag[iii]=0;
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
  else
  {
    for (int iii=0;iii<9;iii++)         candlesFlag[iii]=0;
    candlesFlag[4]=1;
    numOfCandles=0;
  }

}

void button2()
{
  for (int iii=0;iii<9;iii++)         candlesFlag[iii]=0;
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

void playSong(int num)
{
  int runIdx=1;
  int startI = 0;
  int endI = startI + songsS[0];
  while (runIdx<num && runIdx<=numOfSongs+1 ) {
    runIdx++;
    startI=endI;
    endI =  startI+songsS[runIdx-1];
  }
  int LEDidx=0;
  for (int iii=0;iii<9;iii++)      strip.setPixelColor(iii, strip.Color(0, 0, 0));
  strip.show();
  for (int thisNote = startI; thisNote < endI; thisNote++) {
    switch (songsN[thisNote]) {
    case NOTE_C4:
      LEDidx=0;
      break;
    case NOTE_D4:
    case NOTE_D5:
      LEDidx=1;
      break;     
    case NOTE_E4:
      LEDidx=2;
      break;       
    case NOTE_F4:
      LEDidx=3;
      break;   
    case NOTE_FS4:
      LEDidx=4;
      break;   
    case NOTE_G4:
      LEDidx=5;
      break;   
    case NOTE_A3:      
    case NOTE_A4:
      LEDidx=6;
      break;   
    case NOTE_B3:      
    case NOTE_B4:
      LEDidx=7;
      break;  
    case NOTE_C5:
      LEDidx=8;
      break;           
    }
    strip.setPixelColor(LEDidx, Wheel(((LEDidx * 256 / strip.numPixels()) + 0) & 255));
    strip.show();
    int noteDuration = 1000/songsD[thisNote];
    tone(MELODYPIN, songsN[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(MELODYPIN);
    strip.setPixelColor(LEDidx, strip.Color(0, 0, 0));
    strip.show();
  }
}




