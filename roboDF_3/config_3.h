#define TouchR 1
#define IRFront 2
#define IRSide 3
#define TouchL 4

#define drehenLPos 25
#define drehenMPos 25
#define drehenSPos 25

#define drehenLNeg 10
#define drehenMNeg -15
#define drehenSNeg -25

#define normGeschw 25

#define Tpress 45 //schwellenwert fuer die touchs an mux

unsigned int swLSA = 6;

const tMUXSensor port1 = msensor_S4_1;
const tMUXSensor port2 = msensor_S4_2;
const tMUXSensor port3 = msensor_S4_3;
const tMUXSensor port4 = msensor_S4_4;


int auswZurueck = -140;  //|steps fuer ausweichen|
int auswDrehen = -177;   //|zeit fuer ausweichen |
int auswFahren = 300;		 //|steps fuer ausweichen|
