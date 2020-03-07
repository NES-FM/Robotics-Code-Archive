const tMUXSensor port1 = msensor_S2_1;
const tMUXSensor port2 = msensor_S2_2;
const tMUXSensor port3 = msensor_S2_3;
const tMUXSensor port4 = msensor_S2_4;

int Light[] = {0, 0, 0};
int Green[] = {ARDUINO_WHITE, 0, ARDUINO_WHITE};
int GreenG[] = {0, 0, 0};
int vArDVal[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int vArAVal[] = {0,0,0,0,0,0,0,0};
int Accel = 0;

bool arduinoBeep = false;
bool arduinoBeepTurnoff = false;

int __tmpR, __tmpG, __tmpB;

task Sensor()
{
  while(true)
  {
    Light[mid] = LSvalRaw(port2);

	if (HTCSreadColor(port4) == 4)
	{
		Green[left] = ARDUINO_GREEN;
		arduinoBeep = true;
	}
	else
	{
		__tmpR = 0;
		__tmpG = 0;
		__tmpB = 0;
		HTCSreadRGB(port4, __tmpR, __tmpG, __tmpB);
		if (__tmpG < 50)
			Green[left] = ARDUINO_BLACK;
		else
			Green[left] = ARDUINO_WHITE;
	}

	Light[mid] = LSvalRaw(port2);

	if (HTCSreadColor(port1) == 4)
	{
		Green[right] = ARDUINO_GREEN;
		arduinoBeep = true;
	}
	else
	{
		__tmpR = 0;
		__tmpG = 0;
		__tmpB = 0;
		HTCSreadRGB(port1, __tmpR, __tmpG, __tmpB);
		if (__tmpG < 50)
			Green[right] = ARDUINO_BLACK;
		else
			Green[right] = ARDUINO_WHITE;
	}
	int _x_axis, _y_axis, _z_axis ;
	HTACreadAllAxes(port3, _x_axis, _y_axis, _z_axis);
	Accel = _x_axis;
  }
}
task Ard()
{
	byte returned = 0x00;
	bool ledState = false;
	arduino_command(ARDUINO_DEF_INPUT_PULLUP,3,0,returned);
	wait1Msec(arduino_delay);
	arduino_command(ARDUINO_DEF_OUTPUT,5,0,returned);
	wait1Msec(arduino_delay);
	arduino_command(ARDUINO_SET_OUTPUT,5,0,returned);
	wait1Msec(arduino_delay);
	while(true)
	{
		arduino_command(ARDUINO_READ_INPUT,3,0,returned);vArDVal[3]=returned;
		wait1Msec(arduino_delay);
		if (arduinoBeepTurnoff)
		{
			arduinoBeepTurnoff = false;
			//arduinoBeep = false;
			arduino_command(ARDUINO_SET_OUTPUT, 5, 0, returned);
			wait1Msec(arduino_delay);
		}

		if (arduinoBeep)
		{
			arduinoBeep = false;
			arduinoBeepTurnoff = true;
			arduino_command(ARDUINO_SET_OUTPUT, 5, 1, returned);
			wait1Msec(arduino_delay);
		}
		wait1Msec(arduino_delay);
	}
}
