int Timer = 0;

void delay(int msecs)
{
  wait1Msec(msecs);
}

task Timer()
{
  while(true)
  {
    Timer++;
    delay(1);
  }
}
