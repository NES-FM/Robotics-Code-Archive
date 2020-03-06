#pragma config(Sensor, S1, ll, sensorAnalogActive)
#pragma config(Sensor, S2, mux, sensorI2CCustom)
#pragma config(Sensor, S3, rr, sensorAnalogActive)
#pragma config(Sensor, S4, ARDUINO, sensorI2CCustom)
#pragma config(Motor, motorA, l, tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor, motorC, r, tmotorNXT, PIDControl, reversed, encoder)
#include "../dInclude.h"

int lW, mW, rW, lB, mB, rB;

task main()
{
	StartTask(Ard);
	StartTask(Sensor);
	while(true)
	{
		eraseDisplay();
		nxtDisplayCenteredTextLine(4, "All White");
		while (nNxtButtonPressed == -1) { }
		delay(500);
		lW = SensorValue[ll];
		mW = Light[mid];
		rW = SensorValue[rr];
		delay(500);
		nxtDisplayCenteredTextLine(4, "All Black");
		while (nNxtButtonPressed == -1) { }
		delay(500);
		lB = SensorValue[ll];
		mB = Light[mid];
		rB = SensorValue[rr];
		delay(500);
		nxtDisplayCenteredTextLine(1, "OK:  W  |  B ");
		nxtDisplayCenteredTextLine(2, "le: %3d | %3d", lW, lB);
		nxtDisplayCenteredTextLine(3, "mi: %3d | %3d", mW, mB);
		nxtDisplayCenteredTextLine(4, "ri: %3d | %3d", rW, rB);
		nxtDisplayCenteredTextLine(5, "left cal: %3d", ((lW + lB) / 2));
		nxtDisplayCenteredTextLine(6, "mid cal:  %3d", ((mW + mB) / 2));
		nxtDisplayCenteredTextLine(7, "rightcal: %3d", ((rW + rB) / 2));
		delay(2000);
		nxtDisplayCenteredTextLine(0, "Retry?");
		while (nNxtButtonPressed == -1) { }
		delay(500);
	}
}
