#define minSchwarzGL 5  //Min und max fuer schwarz links:
#define maxSchwarzGL 80

#define minSchwarzGR 5//Min und max fuer schwarz rechts:
#define maxSchwarzGR 80

#define maxSchwarz 30  //40 //mittlerer sensor kalibrierung
#define minWeis 40  //45

#define drehGeschwNeg -30 //dreh geschwindigkeiten
#define drehGeschwPos 25

#define drehGeschwNeg2 -30 //dreh geschwindigkeiten fuer auf der Stelle
#define drehGeschwPos2 30

#define raumGeschw 40  //standartgeschwindigkeit fuer Raum

int raumZurueckFuerBall[] = {0, 1010, 1200, 1200};

int tWert = 40;//Kalibrierungswet fuer die Taster (<=)

int iFahrGeschw = 25;    //allgemeine fahr-geschwindigkeit

int auswLZurueck = 1000;  //zeit. fuer ausweichen nach Links
int auswLDrehen = 1000;
int auswLFahren = 700;

int auswRZurueck = 1000;  //zeit. fuer ausweichen nach Rechts
int auswRDrehen = 1300;
int auswRFahren = 700;

int schnellerM = 28;  //variablen fuer das ausweichen
int langsammerM = 8;

int volMain = 4;
int volRaum = 4;

int redL, greenL, blueL, redR, greenR, blueR; //variablen in denen spaeter die Farbwerte reingeschrieben werden

bool raumStart()
{
	if(((redL == 255) && (redR == 255)) && ((greenL == 255) && (greenR == 255)) && ((blueL == 255) && (blueR == 255)))
	{
		return true;
	}
	return false;
}
