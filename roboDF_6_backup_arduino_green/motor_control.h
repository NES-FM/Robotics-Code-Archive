//----------Fast
void FastLeft()
{
  motor[l] = bf;
  motor[r] = ff;
}
void FastRight()
{
  motor[l] = ff;
  motor[r] = bf;
}

//---------- Mid
void MidLeft()
{
  motor[l] = bm;
  motor[r] = fm;
}
void MidRight()
{
  motor[l] = fm;
  motor[r] = bm;
}

//----------Slow
void SlowLeft()
{
  motor[l] = bs;
  motor[r] = fs;
}
void SlowRight()
{
  motor[l] = fs;
  motor[r] = bs;
}

//----------Forward
void Drive()
{
  motor[l] = drive;
  motor[r] = drive;
}
