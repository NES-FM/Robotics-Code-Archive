#pragma config(Sensor, S1,     ll,             sensorLightActive)
#pragma config(Sensor, S2,     mm,             sensorLightActive)
#pragma config(Sensor, S3,     rr,             sensorLightActive)
#pragma config(Sensor, S4,     mux,            sensorI2CCustom)
#pragma config(Motor,  motorB,          r,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          l,             tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "dInclude.h"

task main()
{
	StartTask(Sensor);
	delay(500); //let sensor init
	while(true)
	{
		if(leftBlack && rightWhite)
		{
			SlowLeft();
		}
		if(leftWhite && midBlack && rightWhite)
		{
			Drive();
		}
		if(leftWhite && rightBlack)
		{
			SlowRight();
		}
	}
}