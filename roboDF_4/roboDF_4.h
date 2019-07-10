tByteArray value;
int vMux[5];

bool istCenterAufLinie(); //gibt true zurueck wenn mittlerer Sensor auf linie
bool schwarzLinks(); //gibt true zurueck wenn links schwarz
bool schwarzRechts(); //gibt true zurueck wenn rechts schwarz
void readColor(); //liest die color-werbIncludeMotorEncoderInUploadMessabIncludeMotorEncoderInUploadMessabIncludeMotorEncoderInUploadMessabIncludeMotorEncoderInUploadMessabIncludeMotorEncoderInUploadMessabIncludeMotorEncoderInUploadMessage
void linksDrehenM();
void linksDrehenS();

void rechtsDrehenM();
void rechtsDrehenS();

void geradeausfahren();

void delay(int msec);

void log_WDS(char* WasIchMach);

string lastState;

bool bCAL = false;

void NZGrad(bool l);

bool links = true;
bool rechts = false;
bool auf = true;
bool zu = false;

bool raumActive = true;
string lastAccel = "forward";

int _x_axis = 0;
int _y_axis = 0;
int _z_axis = 0;

//ra: raum--------
int raEcken[4];				   //alle Ecken in der richtigen Reihenfolge
int kachelEcke = 99;     //aktuelle Ecke (99 ist ein wert, zum differenzieren)
int raBisMitte = 500;    //steps bis zur mitte von der erkennung einer Kachel
int raAusrichten = 2500; //zeit, um sich auszurichten
int raBisNachEcke = 800; //zeit, von wand bis ir nach ecke
int raBallIr = 0;				 //schwellenwert fuer das Ball-suchen
int raBallIrDrinnen = 400;//schwellenwert, ob ball im greifer
int raGreifer = 500;     //zeit, um den greifer auf/zu zu machen
void raBallSuchen();		 //funktion, zum ball suchen
void greifer(bool a);    //funktion, um den Greifer zu Offnen/schliessen
bool raBall = false;     //variable, ob ein Ball drinnen ist
bool raGreiferZustand = false;
bool raRichtung = false;
//----------------

void linksDrehenM()
{
	motor[motorB] = drehenMPos;
	motor[motorC] = drehenMNeg;
}
void linksDrehenS()
{
	motor[motorB] = drehenSPos;
	motor[motorC] = drehenSNeg;
}
void rechtsDrehenM()
{
	motor[motorB] = drehenMNeg;
	motor[motorC] = drehenMPos;
}
void rechtsDrehenS()
{
	motor[motorB] = drehenSNeg;
	motor[motorC] = drehenSPos;
}
void geradeausfahren()
{
	motor[motorB] = (normGeschw + 1);
	motor[motorC] =  normGeschw;
}

void delay(int msec)
{
	wait1Msec(msec);
}

void ausweichen()
{
	move(-normGeschw,-normGeschw,auswZurueck);

	move(normGeschw,-normGeschw,auswDrehen);

	move(normGeschw,normGeschw,auswFahren);

	move(langsammerM,schnellerM);

	while(!istCenterAufLinie()){}
	//soll sich gerade hinstellen
	move(normGeschw,normGeschw,vonSensorBisMitte);

	move(normGeschw,-normGeschw);

	while(istCenterAufLinie()){}
}

void log_WDS(char* WasIchMach)
{
	for(int i=0;i<8;i++)
	{
		if(i==4)
		{
			writeDebugStream(": ");
		}
		writeDebugStream("%02d ",value[i]);
	}
	writeDebugStreamLine(WasIchMach);
}

bool schwarzRechts()
{
	HTCSreadRGB(HTCSR, redR, greenR, blueR);
	durchschnittr = (greenR + blueR) / 2;

	if(durchschnittr >= minSchwarzGR && durchschnittr <= maxSchwarzGR)
	{
		return true;
	}
	return false;
}

bool schwarzLinks()
{
	HTCSreadRGB(HTCSL, redL, greenL, blueL);
	durchschnittl = (greenL + blueL) / 2;

	if(durchschnittl >= minSchwarzGL && durchschnittl <= maxSchwarzGL)
	{
		return true;
	}
	return false;
}

bool istCenterAufLinie()
{
	if(bCAL == false && SensorValue[centerL] < maxSchwarz)
	{
		bCAL = true;
	}
	else if(bCAL == true && SensorValue[centerL] > minWeis)
	{
		bCAL = false;
	}
	return bCAL;
}

void NZGrad(bool l)  //true = links || links = true\\
{
	if(l)
		move(-(normGeschw + 2),normGeschw,NZgradSteps);
	else
		move(normGeschw - 2,-normGeschw,NZgradSteps);
}
void anhalten()
{
	motor[motorA]=0;
	motor[motorB]=0;
	motor[motorC]=0;
}
void anhaltenFuer(int time, int danachR = -1, int danachL = -1)
{
	int altGeschwR = motor[motorB];
	int altGeschwL = motor[motorC];

	motor[motorB]=0;
	motor[motorC]=0;

	delay(time);

	if(danachR != -1 && danachL != -1)
	{
		motor[motorB]=danachR;
		motor[motorC]=danachL;
	}
	else
	{
		motor[motorB]=altGeschwR;
		motor[motorC]=altGeschwL;
	}
}

void greifer(bool a) //auf = true || true = auf\\
{
	if(a) //auf
	{
		if(raGreiferZustand==zu)
		{
			raGreiferZustand=auf;
			motor[motorA] = -25;
			delay(raGreifer);
		}
	}
	else //zu
	{
		if(raGreiferZustand==auf)
		{
			raGreiferZustand=zu;
			motor[motorA] = 25;
			delay(raGreifer);
		}
	}
	motor[motorA] = 0;
}

void readColor()
{
	colorL = HTCSreadColor(HTCSL);
	colorR = HTCSreadColor(HTCSR);
}

void raBallSuchen()
{
	move(normGeschw,normGeschw,raBisNachEcke,0,false);
	raBallIr = (vMux[IRSide] - 100);
	while(!raBall)
	{
		if(vMux[IRSide]<raBallIr)
		{
			NZGrad(rechts);
			greifer(auf);
			nMotorEncoder[motorB] = 0;
			geradeausfahren();
			while(vMux[IRFront]>raBallIrDrinnen){}
			anhalten();
			greifer(zu);
			move(-normGeschw,-normGeschw,nMotorEncoder[motorB]);
			if(raRichtung) //zum startpunkt hin
			{
				NZGrad(links);
			}
			else	//vom startpunkt weg
			{
				NZGrad(rechts);
			}
			geradeausfahren();
			while(vMux[Touch]<Tpress) {}//&&vMux[TouchR]<Tpress
			move(-normGeschw,-normGeschw,raBisNachEcke);
			raBall = true;
		}
		if(vMux[IRFront]<raBallIrDrinnen)
		{
			greifer(zu);
			if(!raRichtung) //vom startpunkt weg
			{
				NZGrad(links);
				NZGrad(links);
			}
			geradeausfahren();
			while(vMux[Touch]<Tpress) {}//&&vMux[TouchR]<Tpress
			move(-normGeschw,-normGeschw,raBisNachEcke);
			raBall = true;
		}
		if(vMux[Touch]>Tpress)//||vMux[TouchR]>Tpress
		{
			raRichtung = !raRichtung;
			move(-normGeschw,-normGeschw,0,500);
			NZGrad(rechts);
			NZGrad(rechts);
			move(-normGeschw,-normGeschw,0,raAusrichten);
			move(normGeschw,normGeschw,0,100);
			raBallIr = (vMux[IRSide] - 100);
			geradeausfahren();
		}
	}
}
