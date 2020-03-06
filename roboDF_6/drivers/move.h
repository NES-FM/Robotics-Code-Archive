void move(int motorl,int motorr, int step=0, int time=0)//c, b
{
	if(step != 0)
	{
		if(abs(motorl) > abs(motorr))
		{
			nMotorEncoder[motorA] = 0;
			while(abs(nMotorEncoder[motorA]) <= abs(step))
			{
				motor[motorC] = motorr;
				motor[motorA] = motorl;
			}
		}
		else
		{
			nMotorEncoder[motorC] = 0;
			while(abs(nMotorEncoder[motorC]) <= abs(step))
			{
				motor[motorC] = motorr;
				motor[motorA] = motorl;
			}
		}
		motor[motorC] = 0;
		motor[motorA] = 0;
	}
	else if(time != 0)
	{
		motor[motorC] = motorr;
		motor[motorA] = motorl;
		wait1Msec(time);
		motor[motorA] = 0;
		motor[motorC] = 0;
	}
	else
	{
		motor[motorC] = motorr;
		motor[motorA] = motorl;
	}
}
