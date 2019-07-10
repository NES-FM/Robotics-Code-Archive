//***debug an/aus********
#define debug true
//***********************

#define minSchwarzGL 5  //Min und max fuer schwarz links:
#define maxSchwarzGL 80

#define minSchwarzGR 5//Min und max fuer schwarz rechts:
#define maxSchwarzGR 80

#define maxSchwarz 39//30  //40 //mittlerer sensor kalibrierung
#define minWeis 49//40  //45

#define Accel 3
#define IRSide 1
#define IRFront 0
#define Touch 2

#define accel_ramp_up 100
#define accel_ramp_down 20
#define accel_flat_min 40
#define accel_flat_max 80

int drehenMPos = 25;
int drehenSPos = 25;
int drehenMNeg = -15;
int drehenSNeg = -25;

int drehenMPosR = 20;
int drehenSPosR = 25;
int drehenMNegR = 10;
int drehenSNegR = 10;

int drehenMPosStandard = drehenMPos;
int drehenSPosStandard = drehenSPos;

int drehenMNegStandard = drehenMNeg;
int drehenSNegStandard = drehenSNeg;


#define normGeschw 25

#define Tpress 45 //schwellenwert fuer die touchs an mux

const tMUXSensor port1 = msensor_S4_1;
const tMUXSensor port2 = msensor_S4_2;
const tMUXSensor port3 = msensor_S4_3;
const tMUXSensor port4 = msensor_S4_4;

int NZgradSteps = 370; //steps fuer neunzig grad

int auswZurueck = -140;  //|steps fuer ausweichen|
int auswDrehen = -177;   //|steps fuer ausweichen|
int auswFahren = 300;		 //|steps fuer ausweichen|
int langsammerM = 10;
int schnellerM = 40;

int vonSensorBisMitte = 200;

//ra: raum--------
int raIRKL = 860; //raum Infrarot Kurz/Lang (schwellenwert)
//----------------

int redL, greenL, blueL, redR, greenR, blueR; //variablen in denen spaeter die Farbwerte reingeschrieben werden
int durchschnittl, durchschnittr;
int colorL, colorR;

bool raumEntry()
{
	if(SensorValue[S2] > 65)// || durchschnittr == 255))//&&((colorL == 17 || colorR == 17)||(colorL == 14 && colorR == 14)))//bedingung, um in void raum zu gehen
		return true;

	return false;
}
