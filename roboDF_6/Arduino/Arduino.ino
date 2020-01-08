#include <Wire.h>

/*
 * Adapted from Gatsu's post on Arduino's forums:
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1262353163
 */

int outputVals[14] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int oldOutputVals[14] = {};

int pwmVals[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int oldPwmVals[14] = {};

int inputVals[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int analogVals[8] = {0,0,0,0,0,0,0,0};

int pinModes[14] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP};
int oldPinModes[14] = {};

String toPrint = "";
String oldPrint = "";
 
#include "arduino-nxt_spi.h"

void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  I2C_init(9600);
  Serial.begin(9600);
}

void loop() {
 // This could be any code used to read a sensor.
 // In this simple example, we just count up once a second
 if(pinModes != oldPinModes)
 {
  for(int x = 1; x < 14; x++)
  {
    pinMode(x,pinModes[x]);
    oldPinModes[x] = pinModes[x];
//    Serial.print(String(x) + ": " + String(pinModes[x]) + "|");
  }
//  Serial.println("\n " + String(INPUT) + "=INPUT|" + String(OUTPUT) + "=OUTPUT|" + String(INPUT_PULLUP) + "=INPUT_PULLUP");
 }
 
 if(outputVals != oldOutputVals)
 {
  for(int x = 1; x < 14; x++)
  {
    digitalWrite(x,outputVals[x]);
    oldOutputVals[x] = outputVals[x];
  }
 }
 
 if(pwmVals != oldPwmVals)
 {
  for(int x = 1; x < 14; x++)
  {
    analogWrite(x,pwmVals[x]);
    oldPwmVals[x] = pwmVals[x];
  }
 }

 for(int x = 1; x < 14; x++)
 {
  inputVals[x] = digitalRead(x);
 }

 for(int y = 0; y < 8; y++)
 {
  analogVals[y] = map(analogRead(y),0,1023,0,255);
 }

 if(toPrint != oldPrint)
 {
  oldPrint = toPrint;
  Serial.println(toPrint + "\t taster: " + String(inputVals[3],DEC) + "-" + String(digitalRead(3)));
 }
}
