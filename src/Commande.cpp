/*
 * Commande.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#include <Commande.h>

Commande::~Commande()
{
}

int i=0;

void Commande::start(int t)
{
	if (nomdelacommande == "delai")
		{
			tempsdebut = t;
		}

	if (nomdelacommande == "tourner")
		{
			sdc->basemobile.SetAngleDelta(deltaangle);
		}

	if (nomdelacommande == "avancer")
		{
			sdc->basemobile.ResetDistance();
			sdc->basemobile.Drive(0, targetspeed);
		}

	if (nomdelacommande == "reculer")
		{
			sdc->basemobile.ResetDistance();
			sdc->basemobile.Drive(0, -targetspeed);
		}

	if (nomdelacommande == "placergear")
		{
			std::cout<<"on place la gear"<<std::endl;
			sdc->gear->Set(DoubleSolenoid::Value::kForward);
			tempsdebut=t;
		}

	if (nomdelacommande == "lancer")
		{
			std::cout<<"on shoot"<<std::endl;
			sdc->shooter1->Set(0.75);
			sdc->shooter2->Set(0.75);
			sdc->intake->Set(0.75);

		}
}

bool Commande::isfinished(int t)
{
	if (nomdelacommande == "delai" && t > tempsdebut + 50*deltatemps)
		{
			return true;
		}

	if (nomdelacommande == "tourner" && fabs(sdc->basemobile.GetAngleDelta()) <= 2)
		{
			std::cout << "atteint"<< std::endl;
			sdc->basemobile.Drive(0, 0);
			return true;
		}

	if (nomdelacommande == "avancer" && sdc->basemobile.GetDistance() >= targetdistance)
		{
		sdc->basemobile.Drive(0, 0);
			return true;
		}

	if (nomdelacommande == "reculer" && sdc->basemobile.GetDistance() <= targetdistance)
		{
			sdc->basemobile.Drive(0, 0);
			return true;
		}

	if (nomdelacommande == "placergear" && t > tempsdebut +50)
		{
			sdc->gear->Set(DoubleSolenoid::Value::kReverse);
			return true;
		}

	if (nomdelacommande == "lancer")
		{
			std::cout<<"fin shoot"<<std::endl;
			sdc->shooter1->Set(0);
			sdc->shooter2->Set(0);
			sdc->intake->Set(0);
			return true;
		}

	return false;
}
