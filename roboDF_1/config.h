#define minSchwarzGL 0  //Min und max fuer schwarz links:
#define maxSchwarzGL 45

#define minSchwarzGR 0//Min und max fuer schwarz rechts:
#define maxSchwarzGR 45

#define maxSchwarz 42  //40 //mittlerer sensor kalibrierung
#define minWeis 52  //45

#define drehGeschwNeg -25 //dreh geschwindigkeiten
#define drehGeschwPos 20

#define drehGeschwNeg2 -20 //dreh geschwindigkeiten fuer auf der Stelle
#define drehGeschwPos2 20

#define raumGeschw 40  //standartgeschwindigkeit fuer Raum

int raumZurueckFuerBall[] = {0, 1010, 1200, 1200};

int tWert = 40;//Kalibrierungswet fuer die Taster (<=)

int iFahrGeschw = 25;    //allgemeine fahr-sgeschwindigkeit

int auswLZurueck = 1000;  //zeit. fuer ausweichen nach Links
int auswLDrehen = 1650;
int auswLFahren = 700;

int auswRZurueck = 1000;  //zeit. fuer ausweichen nach Rechts
int auswRDrehen = 1300;
int auswRFahren = 700;

int schnellerM = 27;  //variablen fuer das ausweichen
int langsammerM = 8;
