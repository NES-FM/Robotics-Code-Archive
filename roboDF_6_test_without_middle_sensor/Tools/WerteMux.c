#pragma config(Sensor, S2, mux, sensorI2CCustom)
#pragma config(Motor, motorA, l, tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor, motorC, r, tmotorNXT, PIDControl, reversed, encoder)
#include "../dInclude.h"
task main()
{

	StartTask(Ard);
	StartTask(Sensor);
	while(true)
	{
		nxtDisplayCenteredTextLine(0, "G, W, B");
		nxtDisplayCenteredTextLine(1, "%d, %d, %d", ARDUINO_GREEN, ARDUINO_WHITE, ARDUINO_BLACK);
		nxtDisplayCenteredTextLine(2, "Color L:");
		nxtDisplayCenteredTextLine(3, "%d", Green[left]);
		nxtDisplayCenteredTextLine(4, "Color R:");
		nxtDisplayCenteredTextLine(5, "%d", Green[right]);
		nxtDisplayCenteredTextLine(6, "Light Mid");
		nxtDisplayCenteredTextLine(7, "%d", Light[mid]);
		delay(100);
	}
}
