void move(int motorl,int motorr,int step=0,int time=0,bool endeStoppen=true)//c, b
{
	if(step != 0)
	{
		if(abs(motorl) > abs(motorr))
		{
			nMotorEncoder[motorC] = 0;
			while(abs(nMotorEncoder[motorC]) <= abs(step))
			{
				motor[motorB] = motorr;
				motor[motorC] = motorl;
			}
		}
		else
		{
			nMotorEncoder[motorB] = 0;
			while(abs(nMotorEncoder[motorB]) <= abs(step))
			{
				motor[motorB] = motorr;
				motor[motorC] = motorl;
			}
		}
		if(endeStoppen)
		{
			motor[motorB] = 0;
			motor[motorC] = 0;
		}
	}
	else if(time != 0)
	{
		motor[motorB] = motorr;
		motor[motorC] = motorl;
		wait1Msec(time);
		if(endeStoppen)
		{
			motor[motorB] = 0;
			motor[motorC] = 0;
		}
	}
	else
	{
		motor[motorB] = motorr;
		motor[motorC] = motorl;
	}
}
