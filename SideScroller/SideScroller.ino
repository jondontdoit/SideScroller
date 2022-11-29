//We always have to include the library
#include "LedControl.h"

/*
 Pin 12 is connected to the DataIn [BLUE]
 Pin 11 is connected to the CLK   [GREEN]
 Pin 10 is connected to LOAD     [YELLOW]
 2x LED grids (8x8)
*/
const int numSeg = 2;
LedControl matrix = LedControl(12,11,10,4);

boolean firstRun = true;
byte pixelmap[16] = {};
int startPos = 0;

void setup() {

  //Configure debug pin
  pinMode(LED_BUILTIN, OUTPUT);  
  
  //Initialize Strobe Helmet
  for(int i=0; i<numSeg; i++) {
    matrix.shutdown(i,false);
    matrix.setIntensity(i,15);
    matrix.clearDisplay(i);
  }

  allOn();
  delay(1000);

  randomSeed(A0);

  firstRun = true;
}

void loop() {
/*
  // LIGHT TEST Alternating on and off
  allOn();
  delay(2000);
  allOff();
  delay(1000);
*/
  
//  allOff();

  int a=0;
  int c=0;

  // Random Continuous Line
  int p = random(8);

  if (firstRun) {
    for (int i=0; i<16; i++) {
      if (p == 0) {
        p = p+random(2);
      } else if (p == 7) {
        p = p-random(2);
      } else {
        p = p+random(3)-1;
      }
      if (p < 0) p = 0;
      if (p > 7) p = 7;
      pixelmap[i] = p;
    } 
    startPos = 15;
    firstRun = false;
  }
  
  int s = startPos;
  if (s == 0) s = 15;
    else s -= 1;
  p = pixelmap[s];
  
  if (p == 0) {
    p = p+random(2);
  } else if (p == 7) {
    p = p-random(2);
  } else {
    p = p+random(3)-1;
  }
  if (p < 0) p = 0;
  if (p > 7) p = 7;
  pixelmap[startPos] = p;

  s = startPos + 1;
  if (s > 15) s = 0;
  for (int i=0; i<16; i++) {
    a=i/8; c=7-(i%8);
    for (int y=0; y<8; y++) {
      if (y == pixelmap[s]) {
        matrix.setLed(a, y, c, HIGH);
      } else {
        matrix.setLed(a, y, c, LOW);
      }
    }
//    matrix.setLed(a, pixelmap[s], c, HIGH);
    s++;
    if (s > 15) s = 0;
  }
//  delay(50);

  startPos++;
  if (startPos > 15) startPos = 0;
  
/*
  // Random Line
  int p = random(8);
  
  for (int i=0; i<16; i++) {
    a=i/8; c=7-(i%8);
    if (p == 0) {
      p = p+random(2);
    } else if (p == 7) {
      p = p-random(2);
    } else {
      p = p+random(3)-1;
    }
    if (p < 0) p = 0;
    if (p > 7) p = 7;
    matrix.setLed(a, p, c, HIGH);
    delay(50);
  } 
*/
/*
  // Random noise
  for (int l=0; l<5; l++) {
    for (int i=0; i<16; i++) {
      a=i/8; c=7-(i%8);
      matrix.setLed(a, random(8), c, HIGH);
      delay(200);
    }
    delay(1000);  
  }
*/
}

/***************************************
 * Static Displays
 ***************************************/

void allOn() {
  // turn on all LEDs
  for (int a=0; a<numSeg; a++) {
    for (int i=0; i<8; i++) {
      matrix.setRow(a,i,B11111111);
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);
}

void allOff() {
  // turn off all LEDs
  for (int a=0; a<numSeg; a++) {
    matrix.clearDisplay(a);
  }
  digitalWrite(LED_BUILTIN, LOW);
}
