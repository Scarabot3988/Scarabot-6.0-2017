/*
 * Commande.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#include <Commande.h>
#include <Math.h>

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
			sdc->gear->Set(DoubleSolenoid::Value::kForward);
			tempsdebut=t;
		}
	if (nomdelacommande == "aligner" ||
		nomdelacommande == "approcher"	)
		{
			Vision::Start();
			visionfollowup=false;
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

	if (nomdelacommande == "aligner")
	{
		if(Vision::IsDone()){
			if(visionfollowup==false){
				sdc->basemobile.SetAngleDelta(Vision::GetAngle());
				visionfollowup=true;
			}
			else if(fabs(sdc->basemobile.GetAngleDelta()) <= 2)
			{
				sdc->basemobile.Drive(0, 0);
				return true;
			}
		}
	}

	if (nomdelacommande == "approcher")
	{
		if(Vision::IsDone()){
			if(visionfollowup==false){
				sdc->basemobile.ResetDistance();
				visionfollowup=true;
			}
			else if(sdc->basemobile.GetDistance() >= Vision::GetDistance())
			{
				sdc->basemobile.Drive(0, 0);
				return true;
			}
		}
	}


	return false;
}
