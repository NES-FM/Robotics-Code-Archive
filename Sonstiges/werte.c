#pragma config(Sensor, S1,     HTCSL,          sensorI2CCustomFastSkipStates9V)
#pragma config(Sensor, S2,     CenterL,        sensorLightActive)
#pragma config(Sensor, S3,     HTCSR,          sensorI2CCustomFastSkipStates9V)
#pragma config(Sensor, S4,     mux,            sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-touch.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/hitechnic-colour-v2.h"
#include "drivers/lego-light.h"
#include "drivers/mindsensors-lightsensorarray.h"
#include "drivers/hitechnic-accelerometer.h"

const tMUXSensor port1 = msensor_S4_1;
const tMUXSensor port2 = msensor_S4_2;
const tMUXSensor port3 = msensor_S4_3;
const tMUXSensor port4 = msensor_S4_4;

int redL, greenL, blueL, redR, greenR, blueR, durchschnittl, durchschnittr, colorR, colorL,x,y,z;
tByteArray value;
task main()
{
	while(true)
	{
 		HTCS2readRGB(HTCSL, redL, greenL, blueL);
 		colorL = HTCS2readColor(HTCSL);
 		HTCS2readRGB(HTCSR, redR, greenR, blueR);
 		colorR = HTCS2readColor(HTCSR);
 		durchschnittl = (greenL + blueL) / 2;
 		durchschnittr = (greenR + blueR) / 2;
 		HTACreadAllAxes(Port4,x,y,z);
		nxtDisplayCenteredTextLine(0, "L durch,c:%d,%d",durchschnittl,colorL);
		nxtDisplayCenteredTextLine(1, "center Light:%d",SensorValue[CenterL]);
		nxtDisplayCenteredTextLine(2, "R durch,c:%d,%d",durchschnittr,colorR);
		nxtDisplayCenteredTextLine(3, "----------------");
		nxtDisplayCenteredTextLine(4, "IrFront:%d",LSvalRaw(Port1));
		nxtDisplayCenteredTextLine(5, "IrSide:%d",LSvalRaw(Port2));
		nxtDisplayCenteredTextLine(6, "Touch:%d",LSvalRaw(Port3));
		nxtDisplayCenteredTextLine(7, "Accel:%d",x);
		//writeDebugStreamLine("L: %d, %d, %d",redL,greenL,blueL);
		//writeDebugStreamLine("R: %d, %d, %d",redR,greenR,blueR);
		//writeDebugStreamLine("c: %d", colorL);
	 // writeDebugStreamLine("C: %d", colorR);
		//writeDebugStreamLine("L: %d",SensorValue[S2] );
		//wait1Msec(1000);
	}
}
