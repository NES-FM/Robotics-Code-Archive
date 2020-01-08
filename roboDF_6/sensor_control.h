const tMUXSensor port1 = msensor_S4_1;
const tMUXSensor port2 = msensor_S4_2;
const tMUXSensor port3 = msensor_S4_3;
const tMUXSensor port4 = msensor_S4_4;

int vMuxRaw[] = {0, 0, 0, 0, 0};
int vMuxNorm[] = {0, 0, 0, 0, 0};
int Light[] = {0, 0, 0};
int vArDVal[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int vArAVal[] = {0,0,0,0,0,0,0,0};

bool leftBlack, midBlack, rightBlack, leftWhite, midWhite, rightWhite = false;

task Sensor()
{
  while(true)
  {
    Light[left] = SensorValue(ll);
    Light[mid] = SensorValue(mm);
    Light[right] = SensorValue(rr);
    vMuxRaw[0] = LSvalRaw(port1);
    vMuxRaw[1] = LSvalRaw(port2);
    vMuxRaw[2] = LSvalRaw(port3);
    vMuxRaw[3] = LSvalRaw(port4);
    vMuxNorm[0] = LSvalNorm(port1);
    vMuxNorm[1] = LSvalNorm(port2);
    vMuxNorm[2] = LSvalNorm(port3);
    vMuxNorm[3] = LSvalNorm(port4);
    leftBlack = (Light[left] < CalLeft);
    midBlack = (Light[mid] < CalMid);
    rightBlack = (Light[right] < CalRight);
    leftWhite = (Light[left] > CalLeft);
    midWhite = (Light[mid] > CalMid);
    rightWhite = (Light[right] > CalRight);
  }
}
task Ard()
{
	byte returned = 0x00;
	bool ledState = false;
	arduino_command(ARDUINO_DEF_INPUT_PULLUP,3,1,returned);
	wait1Msec(arduino_delay);
	//arduino_command(ARDUINO_DEF_OUTPUT,13,1,returned);
	//wait1Msec(arduino_delay);
	while(true)
	{
		arduino_command(ARDUINO_READ_INPUT,3,1,returned);vArDVal[3]=returned;
		wait1Msec(arduino_delay);
		//if(ledState == false)
		//{
		//	arduino_command(ARDUINO_SET_OUTPUT,13,1,returned);
		//	ledState = true;
		//}
		//else
		//{
		//	arduino_command(ARDUINO_SET_OUTPUT,13,1,returned);
		//	ledState = true;
		//}
		//wait1Msec(arduino_delay);
	}
}
