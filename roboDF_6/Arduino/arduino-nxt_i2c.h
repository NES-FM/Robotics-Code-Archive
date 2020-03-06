
//***********************Config***********************//

	// First, define the Arduino Address
	// Address is 0x0A on the Arduino:  					(Binary)  1010
	#ifndef ARDUINO_ADDRESS
		#define ARDUINO_ADDRESS	0x0A
	#endif

  uint8_t SensorVersion[9]  = "V0.1    ";
  uint8_t SensorName[9]     = "Arduino ";
  uint8_t SensorType[9]     = "Nano Mux";

	// Enums to define Arduino features

	#define ARDUINO_DEF_OUTPUT       0x41
	#define ARDUINO_DEF_INPUT        0x42
	#define ARDUINO_DEF_INPUT_PULLUP 0x43

	#define ARDUINO_READ_INPUT       0x50
	#define ARDUINO_ANALOG_INPUT     0x60
	#define ARDUINO_SET_OUTPUT       0x70
	#define ARDUINO_PWM_OUTPUT       0x71

  #define ARDUINO_GREEN_LEFT       0x30
  #define ARDUINO_GREEN_RIGHT      0x31

  #define ARDUINO_HIGH             1
  #define ARDUINO_LOW              0
  
  #define ARDUINO_BLACK            0
  #define ARDUINO_GREEN            1
  #define ARDUINO_WHITE            2

//******************************************************//


byte x = 0;
byte sendbuffer[] = {0};
char c[] = {};
byte b[] = {};
char s[] = {};


void receiveEvent(int howMany) {
/*    if (Wire.available() >0 ) {
       x = Wire.read(); // receive register address (1 byte)
   }*/
     int i = 0;

 while(1 < Wire.available()) // loop through all but the last
 {
   c[i] = Wire.read();     // Receive the incoming byte
   i++;
 }
 int x = Wire.read();        // Read the incoming byte
 toPrint = String(x) + ";data:";
 char* tmp = "";
 for(int ii = 0; ii < howMany; ii++)
 {
   //tmp = "";
   //sprintf(tmp, "%#x - %2d;", c[ii], c[ii]);
   toPrint +=  "|" + String(c[ii], DEC);
   //toPrint += String(tmp) + " - " + String(c[ii],DEC);
   //toPrint +=";";
 }
}

void requestEvent() {
  byte c_0 = c[0];
  // Serial.println(c[0],HEX);
  if (c_0 <= 0x07){
    Wire.write(SensorVersion[c_0]);
  }
  if (0x08 <= c_0 && c_0 <= 0x0F){
    Wire.write(SensorName[c_0]);
  }
  if (0x10 <= c_0 && c_0 <= 0x17){
    Wire.write(SensorType[c_0]);
  }
  if (ARDUINO_READ_INPUT <= c_0 && c_0 <= ARDUINO_READ_INPUT + 0x0F){ 
    Wire.write(inputVals[c_0-ARDUINO_READ_INPUT]);
  }
  if (ARDUINO_ANALOG_INPUT <= c_0 && c_0 <= ARDUINO_ANALOG_INPUT + 0x0F){ 
    Wire.write(analogVals[c_0-ARDUINO_ANALOG_INPUT]);
  }
    int intFromMessage = c[1];
    int secondArg = c[2];
    switch(c[0]){
      case ARDUINO_DEF_OUTPUT:
        Wire.write(0x44);
        pinModes[intFromMessage] = OUTPUT;
        break;
        
      case ARDUINO_DEF_INPUT:
        Wire.write(0x44);
        pinModes[intFromMessage] = INPUT;
        break;
        
      case ARDUINO_DEF_INPUT_PULLUP:
        Wire.write(0x44);
        pinModes[intFromMessage] = INPUT_PULLUP;
        break;
        
/*      case ARDUINO_READ_INPUT:
        Wire.write(inputVals[secondArg]);
        break;
        
      case ARDUINO_ANALOG_INPUT:
        Wire.write(analogVals[secondArg]);
        break; */
        
      case ARDUINO_SET_OUTPUT:
        Wire.write(0x44);
        outputVals[intFromMessage] = secondArg;
        outputChange = true;
        break;
        
      case ARDUINO_PWM_OUTPUT:
        Wire.write(0x44);
        pwmVals[intFromMessage] = secondArg;
        pwmChange = true;
        break;

      case ARDUINO_GREEN_LEFT:
        Wire.write(lState);
        break;
      case ARDUINO_GREEN_RIGHT:
        Wire.write(rState);
        break;
    }
    //Wire.write(0x58);

//  Wire.endTransmission();
  

  //Serial.println(x);
}

void I2C_init(int baud)
{
  Wire.begin(ARDUINO_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(baud);
}
