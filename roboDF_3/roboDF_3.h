tByteArray value;
bool bValues[8];
int vMux[5];

//Position Sensoren LSA
#define LA 0  //Links aussen
#define LM 1  //Links mitte
#define LI 2  //Links innen
#define ML 3  //Mitte links
#define MR 4  //Mitte rechts
#define RI 5  //Rechts innen
#define RM 6  //Rechts mitte
#define RA 7  //Rechts aussen

void linksDrehenL();
void linksDrehenM();
void linksDrehenS();

void rechtsDrehenL();
void rechtsDrehenM();
void rechtsDrehenS();

void geradeausfahren();

void delay(int msec);

void log_WDS(char* WasIchMach);

int redM, greenM, blueM;

string lastState;


void linksDrehenL()
{
	motor[motorB] = drehenLPos;
	motor[motorC] = drehenLNeg;
}
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
void rechtsDrehenL()
{
	motor[motorB] = drehenLNeg;
	motor[motorC] = drehenLPos;
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
	motor[motorB] = normGeschw;
	motor[motorC] = normGeschw;
}

void delay(int msec)
{
	wait1Msec(msec);
}

void ausweichen()
{
	move(-normGeschw,-normGeschw,auswZurueck);

	move(-normGeschw,normGeschw,auswDrehen);

	move(normGeschw,normGeschw,auswFahren);

	//motor[motorB] = langsammerM;
	//motor[motorC] = schnellerM;

	wait1Msec(100000);
	while(value[3]>swLSA || value[4]>swLSA){}
			//soll sich gerade hinstellen
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
