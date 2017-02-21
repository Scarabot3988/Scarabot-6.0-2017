/*
 * Vision.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: XPS15
 */

#include <Vision.h>
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

#define X1    113.0
#define X2    335.0
#define D1    60.0
#define D2    120.0

Vision::Vision()
{
	Net= NetworkTable::GetTable("Data");
}

Vision::~Vision()
{
	// TODO Auto-generated destructor stub
}

void Vision::test()
{
	try
		{
			float valeur = Net.get()->GetNumber("x",0);
			//std::cout<<"Number :"<<valeur<<std::endl;
		}
	catch(...)
		{
				std::cout<<"Pas de valeur"<<std::endl;
		}
}

float Vision::calculdistance(int pix)
{
	float a;
	float b;
	float d;

	a=(D2-D1)/(X2-X1);	//la pente
	b=D1-(X1*a);		//l"ordonnée à l'origine
	d=pix*a+b;			//le y

	return d;
}
