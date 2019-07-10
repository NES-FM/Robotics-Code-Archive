#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-touch.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/hitechnic-colour-v1.h"
#include "drivers/lego-light.h"
#include "config_2.h"

const tMUXSensor TouchL = msensor_S4_3;
const tMUXSensor gyro = msensor_S4_4;
const tMUXSensor LeftIR = msensor_S4_1;
const tMUXSensor TouchR = msensor_S4_2;

int irWerte[] = {   0, 70, 47, 70};

#define neunzigGrad 410 //steps fuer 90°

int kachelEcke = NULL; //1 = unten links, 2 = oben links, 3 = oben rechts, 4 = unten rechts
int keReihenfolge[] = {1,2,3,NULL};
bool ballDrinnen = false;

int vor = 0;
int zurueck = 1;

int durchschnittr;
int durchschnittl;

int richtung = vor;

bool bCAL = false;  //temp. fuer mittleren sensor

bool bAndersRum = true;

bool links = true;     //temp. variablen(NICHT VERAENDERN)
bool rechts = false;

void nachLinksDrehen();  //dreht nach links/rechts
void nachRechtsDrehen();

void nachLinksDrehen2();  //dreht nach links/rechts
void nachRechtsDrehen2();

void geradeausFahren(); //setzt motoren auf fahrtGeschw
void zurueckFahren();  //setzt motoren auf -fahrtGeschw

void piepL();    //piepst runter
void piepR();    //piepst hoch

void anhalten(int fur);  //stoppt die motoren fuer die angegebene Zeit(fur)

void delay(int zeit); //wartet in msec

bool istCenterAufLinie(); //gibt true zurueck wenn mittlerer Sensor auf linie

bool schwarzLinks(); //gibt true zurueck wenn links schwarz

bool gruenLinks(); //gibt true zurueck wenn links gruen

bool schwarzRechts(); //gibt true zurueck wenn rechts schwarz

bool gruenRechts(); //gibt true zurueck wenn rechts gruen

void ausweichen(bool l); //Weicht dem Gegenstandt nach rechts/links aus

void geradeausFahrenRaum();

void anhalten();

void anhalten()
{
	motor[motorB] = 0;
	motor[motorC] = 0;
}

void nachLinksDrehen()
{
	motor[motorC] = drehGeschwNeg;
	motor[motorB] = drehGeschwPos;

}
void nachRechtsDrehen()
{
	motor[motorC] = drehGeschwPos;
	motor[motorB] = drehGeschwNeg;
}

void nachLinksDrehen2()
{
	motor[motorC] = drehGeschwNeg2;
	motor[motorB] = drehGeschwPos2;

}
void nachRechtsDrehen2()
{
	motor[motorC] = drehGeschwPos2;
	motor[motorB] = drehGeschwNeg2;
}

void geradeausFahren()
{
	motor[motorB] = iFahrGeschw;
	motor[motorC] = iFahrGeschw;
}

void zurueckFahren()
{
	motor[motorB] = -20;
	motor[motorC] = -20;
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

bool gruenLinks()
{
	HTCSreadRGB(HTCSL, redL, greenL, blueL);

	if(HTCSreadColor(HTCSL) == 4)
	{
		return true;
	}
	return false;
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

bool gruenRechts()
{
	HTCSreadRGB(HTCSR, redR, greenR, blueR);

	if(HTCSreadColor(HTCSR) == 4)// && !schwarzRechts())
	{
		return true;
	}
	return false;
}

void delay(int zeit)
{
	wait1Msec(zeit);
}

void piepL()
{
	PlaySound(soundDownwardTones);
	wait1Msec(100);
}

void piepR()
{
	PlaySound(soundUpwardTones);
	wait1Msec(100);
}
void anhalten(int fur)
{
	int altMB = motor[motorB];
	int altMC = motor[motorC];

	motor[motorB] = 0;
	motor[motorC] = 0;

	wait1Msec(fur);

	motor[motorB] = altMB;
	motor[motorC] = altMC;
}
void ausweichen(bool l)
{
	if(l)
	{
		zurueckFahren();

		delay(auswLZurueck);

		nachLinksDrehen();

		delay(auswLDrehen);

		geradeausFahren();

		delay(auswLFahren);

		motor[motorB] = langsammerM;
		motor[motorC] = schnellerM;

	}

	else if(!l)
	{
		zurueckFahren();

		delay(auswRZurueck);

		nachRechtsDrehen();

		delay(auswRDrehen);

		geradeausFahren();

		delay(auswRFahren);

		motor[motorB] = langsammerM;
		motor[motorC] = schnellerM;
	}

	while(!istCenterAufLinie())
	{
	}
}

void geradeausFahrenRaum()
{
	motor[motorB] = raumGeschw;
	motor[motorC] = raumGeschw;
}

void zurueckFahrenRaum()
{
	motor[motorB] = -raumGeschw;
	motor[motorC] = -raumGeschw;
}

void move(int mtr, int geschw, int anzahl)
{
	nMotorEncoder[mtr] = 0;
	nMotorEncoderTarget[mtr] = anzahl;
	motor[mtr] = geschw;
}

void move2m(int mtr1, int steps1, int geschw1, int mtr2, int steps2, int geschw2)
{
	move(mtr1, geschw1, steps1);
  move(mtr2, geschw2, steps2);
	while((nMotorRunState[mtr1] != runStateIdle) || (nMotorRunState[mtr2] != runStateIdle)) {	}
}

void move1m(int mtr, int steps, int geschw)
{
	move(mtr,geschw,steps);
	while(nMotorRunState[mtr] != runStateIdle) { }
}
