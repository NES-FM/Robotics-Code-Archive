#pragma config(Sensor, S1,     LSA,            sensorI2CCustomFastSkipStates9V)
#pragma config(Sensor, S2,     HTCSM,          sensorI2CCustom)
#pragma config(Sensor, S4,     mux,            sensorI2CCustom)
#pragma config(Motor,  motorB,          r,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          l,             tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/***********************************************************************
*
*  Name:				roboDF_3.c
*
*  Funktion:    Mit einem Sensorarray der Linie folgen
*
*  Version:			3.0
*  Datum:
*  Author:			Florian Magg
*
*  Aenderungen:
************************************************************************/
//0--1--2--3--4--5--6--7
												//move(int motorl,int motorr,int step,int time)
#include "dInclude.h"
#include "config_3.h"
#include "roboDF_3.h"

task getValues();

task main()
{
	//ausweichen();
	StartTask(getValues);
	delay(500);
	while(true)
	{
		//log_WDS("-");
		if(bValues[LA]&&(bValues[ML] && bValues[MR]))
		{
			log_WDS("ld90i");
			move(15,15,0,500);
			//while((value[0]<swLSA)||(value[3]<swLSA||value[4]<swLSA)){
			//	geradeausfahren();
			//}
			linksDrehenS();
			log_WDS("ld90o");
			delay(10);
		}
		else if(bValues[LA])//&&(value[3]>swLSA && value[4]>swLSA))
		{
			linksDrehenS();
			log_WDS("lds");
			delay(10);
		}
		//else if(bValues[RM]&&(!bValues[ML] && !bValues[MR])
		//{
		//	linksDrehenM();
		//	log_WDS("ldm");
		//	delay(10);
		//}



		if(bValues[ML] && bValues[MR])//Mittlere Sensoren
		{
				geradeausfahren();
				log_WDS("g");
			delay(10);
		}

		if(bValues[RA]&&(bValues[ML] && bValues[MR]))
		{
			log_WDS("rd90i");
			move(15,15,0,700);
			while(bValues[RA]||(bValues[ML] || bValues[MR])){
				geradeausfahren();
			}
			rechtsDrehenS();
			log_WDS("rd90o");
			delay(10);
		}
		else if(bValues[RA])//&&(value[3]>swLSA && value[4]>swLSA))
		{
			rechtsDrehenS();
			log_WDS("rds");
			delay(10);
		}
		//else if(bValues[RM]&&(!bValues[ML] && !bValues[MR])
		//{
		//	rechtsDrehenM();
		//	log_WDS("rdm");
		//	delay(10);
		//}


		if(vMux[TouchL]>Tpress||vMux[TouchR]>Tpress)
		{
			ausweichen();
			log_WDS("ausw");
		}
	}
}

task getValues()
{
	while(true)
	{
		MSLSAreadSensors(LSA, &value[0]);
		bValues[LA] = value[LA]<swLSA;       //bValues: true = schwarz
		bValues[LM] = value[LM]<swLSA;
		bValues[LI] = value[LI]<swLSA;
		bValues[ML] = value[ML]<swLSA;
		bValues[MR] = value[MR]<swLSA;
		bValues[RI] = value[RI]<swLSA;
		bValues[RM] = value[RM]<swLSA;
		bValues[RA] = value[RA]<swLSA;
		HTCSreadRGB(HTCSM, redM, greenM, blueM);
		vMux[0] = LSvalRaw(port1);
		vMux[1] = LSvalRaw(port2);
		vMux[2] = LSvalRaw(port3);
		vMux[3] = LSvalRaw(port4);
		delay(10);
	}
}
