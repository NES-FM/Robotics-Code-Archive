#pragma config(Motor,  motorA,          l,             tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          r,             tmotorNXT, PIDControl, reversed, encoder)

task main()
{
		motor[l] = 30;
		motor[r] = 30;
		wait1Msec(1500);
		motor[l] = -30;
		motor[r] = 30;
		wait1Msec(1300);
		motor[l] = 30;
		motor[r] = 30;
		wait1Msec(2000);
}
