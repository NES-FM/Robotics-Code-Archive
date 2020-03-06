#include <Wire.h>

/*
 * Adapted from Gatsu's post on Arduino's forums:
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1262353163
 */

int outputVals[14] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int oldOutputVals[14] = {LOW};
bool outputChange = true;

int pwmVals[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int oldPwmVals[14] = {0};
bool pwmChange = true;

int inputVals[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int analogVals[8] = {0,0,0,0,0,0,0,0};

int pinModes[14] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP};
int oldPinModes[14] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP};

String toPrint = "";
String oldPrint = "";

//Green Sensors
byte lState = "W";
int lRaw = 0;
const int lPin = 7;
byte rState = "W";
int rRaw = 0;
const int rPin = 6;
int frequency = 0;
#define lWhite 600
#define lGreen 2706
#define lBlack 5900
#define rWhite 1775
#define rGreen 7807
#define rBlack 17200
int m = 0;
 
#include "arduino-nxt_i2c.h"

void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  pinMode(lPin,INPUT);
  pinMode(rPin,INPUT);

  pinModes[rPin] = INPUT;
  pinModes[lPin] = INPUT;
  
  I2C_init(9600);
  Serial.begin(9600);
}

void loop() {
 // This could be any code used to read a sensor.
 // In this simple example, we just count up once a second
 if(array_cmp(pinModes, oldPinModes, 14, 14) == false)
 {
  for(int x = 0; x < 14; x++)
  {
    pinMode(x,pinModes[x]);
    oldPinModes[x] = pinModes[x];
    //Serial.print(String(x) + ": " + String(pinModes[x]) + "/" + String(oldPinModes[x]) + "|");
  }
  //Serial.println("\n " + String(INPUT) + "=INPUT|" + String(OUTPUT) + "=OUTPUT|" + String(INPUT_PULLUP) + "=INPUT_PULLUP");
  toPrint += ";After PinModes;";
 }

 
 
 if(outputChange)
 {
  toPrint += ";After Output;";
  for(int x = 1; x < 14; x++)
  {
    if(pinModes[x] == OUTPUT) {
      digitalWrite(x,outputVals[x]);
      oldOutputVals[x] = outputVals[x];
    }
  }
  outputChange = false;
 }

 
 
 if(pwmChange)
 {
  toPrint += ";After PWM;";
  for(int x = 1; x < 14; x++)
  {
    if(pinModes[x] == OUTPUT) {
      analogWrite(x,pwmVals[x]);
      oldPwmVals[x] = pwmVals[x];
    }
  }
  pwmChange = false;
 }

 
 
 for(int x = 1; x < 14; x++)
 {
  inputVals[x] = digitalRead(x);
 }

 for(int y = 0; y < 8; y++)
 {
  analogVals[y] = map(analogRead(y),0,1023,0,255);
 }

 getGreen();

 if(toPrint != oldPrint)
 {
  oldPrint = toPrint;
  Serial.println(toPrint + "\t L: " + String(lRaw) + "| R: " + String(rRaw) + "\t L: " + String(lState) + "| R: " + String(rState));
 }
}


void getGreen()
{
  frequency = pulseIn(lPin, HIGH);
  // Printing the value on the serial monitor
  int lWG, lGB = 0;
  lWG = ((lWhite + lGreen) / 2);
  lGB = ((lGreen + lBlack) / 2);
  if(frequency < ((lWG + lWhite) / 2))
    lState = ARDUINO_WHITE;
  else if(frequency > ((lWG + lGreen) / 2) && frequency < ((lGB + lGreen) / 2))
    lState = ARDUINO_GREEN;
  else if(frequency > ((lGB + lBlack) / 2))
    lState = ARDUINO_BLACK;
  else
    lState = ARDUINO_WHITE;
  
  lRaw = frequency;
  
  frequency = pulseIn(rPin, LOW);
  // Printing the value on the serial monitor
  if(frequency < ((rWhite + rGreen) / 2))
    rState = ARDUINO_WHITE;
  else if(frequency > ((rWhite + rGreen) / 2) && frequency < ((rGreen + rBlack) / 2))
    rState = ARDUINO_GREEN;
  else if(frequency > ((rGreen + rBlack) / 2))
    rState = ARDUINO_BLACK; 
  rRaw = frequency;
}

boolean array_cmp(int *a, int *b, int len_a, int len_b){
     int n;

     // if their lengths are different, return false
     if (len_a != len_b) return false;

     // test each element to be the same. if not, return false
     for (n=0;n<len_a;n++) {
       if (a[n]!=b[n]) {
         return false;
       }
     }

     //ok, if we have not returned yet, they are equal :)
     return true;
}


