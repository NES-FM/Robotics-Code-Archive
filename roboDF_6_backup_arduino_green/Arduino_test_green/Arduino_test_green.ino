#include <Wire.h>
#include <SoftwareSerial.h>

#define sio      6           // ColorPAL connected to pin 6
#define unused   255         // Non-existant pin # for SoftwareSerial
#define sioBaud  4800

// Received RGB values from ColorPAL
int red;
int grn;
int blu;

// Set up two software serials on the same pin.
SoftwareSerial serin(sio, unused);
SoftwareSerial serout(unused, sio);

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

  delay(2000);

  //ColorPal
  reset();                    // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(sio, OUTPUT);
  serout.print("=(00 $ s W)!"); // Loop print values, see ColorPAL documentation
  serout.end();               // Discontinue serial port for transmitting

  pinMode(sio, INPUT);
  serin.begin(sioBaud);       // Set up serial port for receiving
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

 readData(); // read ColorPAL

 if(toPrint != oldPrint)
 {
  oldPrint = toPrint;
  Serial.println(toPrint + "\t Green: " + String(grn,DEC));
 }
}

void reset() {
  delay(200);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  pinMode(sio, INPUT);
  while (digitalRead(sio) != HIGH);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  delay(80);
  pinMode(sio, INPUT);
  delay(200);
}

void readData() {
  char buffer[32];
  buffer[0] = "";
  // Wait for a $ character, then read three 3 digit hex numbers
  while(buffer[0] != "$")
  {
    buffer[0] = serin.read();
    if (buffer[0] == '$') {
      for(int i = 0; i < 3; i++) {
        while (serin.available() == 0);     // Wait for next input character
        buffer[i] = serin.read();
        if (buffer[i] == '$')               // Return early if $ character encountered
          return;
      }
      sscanf (buffer, "%3x", &grn);  // Pull the R, G, and B values from the data string
    }
  }
}
