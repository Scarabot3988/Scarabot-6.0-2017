/*
 * Vision.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: XPS15
 */

#include <Vision.h>
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

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

/*float Vision::calculdistance(int pix)
{
}*/
