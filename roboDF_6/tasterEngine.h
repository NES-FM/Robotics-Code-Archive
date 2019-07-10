int getTasterPressed()
{
	int tValue = vMuxRaw[Touch];
	if(tValue < 610 && tValue > 500)
		return 40;
	if(tValue < 760 && tValue > 610)
		return 30;
	if(tValue < 815 && tValue > 760)
		return 34;
	if(tValue < 850 && tValue > 815)
		return 20;
	if(tValue < 880 && tValue > 850)
		return 24;
	if(tValue < 910 && tValue > 880)
		return 23;
	if(tValue < 933 && tValue > 910)
		return 10;
	if(tValue < 942 && tValue > 933)
		return 14;
	if(tValue < 950 && tValue > 942)
		return 13;
	if(tValue > 950)
		return 12;

	return 0;
}
