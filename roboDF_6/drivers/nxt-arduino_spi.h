
//***********************Config***********************//

	// First, define the Arduino Address
	// Address is 0x0A on the Arduino:  					(Binary)  1010
	// Bit shifted out with one 0, that becomes: 	(Binary) 10100
	// Which is 0x14
	#ifndef ARDUINO_ADDRESS
		#define ARDUINO_ADDRESS	0x14
	#endif
	#ifndef ARDUINO_PORT
		#define ARDUINO_PORT S4
	#endif

	// Enums to define Arduino features

	#define ARDUINO_DEF_OUTPUT       0x41
	#define ARDUINO_DEF_INPUT        0x42
	#define ARDUINO_DEF_INPUT_PULLUP 0x43

	#define ARDUINO_READ_INPUT       0x50
	#define ARDUINO_ANALOG_INPUT     0x60
	#define ARDUINO_SET_OUTPUT       0x70
	#define ARDUINO_PWM_OUTPUT       0x71

	#define ARDUINO_HIGH             1
	#define ARDUINO_LOW              0

//******************************************************//

// #include "common.h" //Only Include if not already

tByteArray I2Cmessage;
tByteArray I2Creply;

void debug(byte ans)
{
	writeDebugStreamLine("0x%02X | %02d | %c", ans, ans, ans);
}

void arduino_command(ubyte Enum, int pin = 0, int value = 0, byte &ret){
	if(Enum == ARDUINO_READ_INPUT || Enum == ARDUINO_ANALOG_INPUT)
	{
		Enum = Enum + pin;
	}
	ret = 0x00;
  memset(I2Creply, 0, sizeof(I2Creply));
  memset(I2Cmessage, 0, sizeof(I2Creply));

  int message_size = 2+3;

  I2Cmessage[0] = message_size;    // Messsage Size
  I2Cmessage[1] = ARDUINO_ADDRESS;
  I2Cmessage[2] = Enum; // Register

  I2Cmessage[3] = pin;
  I2Cmessage[4] = value;

  sendI2CMsg(ARDUINO_PORT, &I2Cmessage[0], 1);

  wait1Msec(20);

  readI2CReply(ARDUINO_PORT, &I2Creply[0], 1);

  int length = (sizeof(I2Creply)/2);

//  for(int i = 0; i < length; i++)
//  {
//  	ret = ret + I2Creply[i];
//  }
  //int i = 0;
  //while(true)
  //{
  //	ret = ret + I2Creply[i];
  //	i++;
  //	if(I2Creply[i]==0) break;
  //}
  ret = I2Creply[0];
  debug(ret);
}

/*
void i2c_read_write_register(ubyte register_2_write, int message_size, int return_size, ubyte byte1, ubyte byte2, ubyte byte3, ubyte byte4, string &ret){
	ret = "";
  memset(I2Creply, 0, sizeof(I2Creply));
  memset(I2Cmessage, 0, sizeof(I2Creply));

  message_size = message_size+3;

  I2Cmessage[0] = message_size;    // Messsage Size
  I2Cmessage[1] = ARDUINO_ADDRESS;
  I2Cmessage[2] = register_2_write; // Register

  I2Cmessage[3] = byte1;
  I2Cmessage[4] = byte2;
  I2Cmessage[5] = byte3;
  I2Cmessage[6] = byte4;

  sendI2CMsg(ARDUINO_PORT, &I2Cmessage[0], return_size);

  wait1Msec(20);

  readI2CReply(ARDUINO_PORT, &I2Creply[0], return_size);

  int length = (sizeof(I2Creply)/2);

//  for(int i = 0; i < length; i++)
//  {
//  	ret = ret + I2Creply[i];
//  }
  int i = 0;
  while(true)
  {
  	ret = ret + I2Creply[i];
  	i++;
  	if(I2Creply[i]==0) break;
  }
}

void i2c_read_write_register_cust_addr(ubyte register_2_write, int message_size, int return_size, ubyte byte1, ubyte byte2, ubyte byte3, ubyte byte4, string &ret, ubyte addr){
	ret = "";
  memset(I2Creply, 0, sizeof(I2Creply));
  memset(I2Cmessage, 0, sizeof(I2Creply));

  message_size = message_size+3;

  I2Cmessage[0] = message_size;    // Messsage Size
  I2Cmessage[1] = addr;
  I2Cmessage[2] = register_2_write; // Register

  I2Cmessage[3] = byte1;
  I2Cmessage[4] = byte2;
  I2Cmessage[5] = byte3;
  I2Cmessage[6] = byte4;

  sendI2CMsg(ARDUINO_PORT, &I2Cmessage[0], return_size);

  wait1Msec(20);

  readI2CReply(ARDUINO_PORT, &I2Creply[0], return_size);

  int length = (sizeof(I2Creply)/2);

  for(int i = 0; i < length; i++)
  {
  	ret = ret + I2Creply[i];
  }
}
*/
