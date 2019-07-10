void move(int motorl,int motorr,int step,int time)
{
	if(step != 0)
	{
		if(abs(motorl) > abs(motorr))
		{
			nMotorEncoder[motorB] = 0;
			while(abs(nMotorEncoder[motorB]) <= step)
			{
				motor[motorA] = motorr;
				motor[motorB] = motorl;
			}
		}
		else
		{
			nMotorEncoder[motorA] = 0;
			while(abs(nMotorEncoder[motorA]) <= step)
			{
				motor[motorA] = motorr;
				motor[motorB] = motorl;
			}
		}
		motor[motorA] = 0;
		motor[motorB] = 0;
	}
	else if(time != 0)
	{
		motor[motorA] = motorr;
		motor[motorB] = motorl;
		wait1Msec(time);
		motor[motorA] = 0;
		motor[motorB] = 0;
	}
	else
	{
		motor[motorA] = motorr;
		motor[motorB] = motorl;
	}
}
