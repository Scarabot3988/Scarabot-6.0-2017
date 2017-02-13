/*
 * Commande.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#include <Commande.h>

Commande::~Commande()
	{
		pistongear=new Solenoid(0);
	}

void Commande::start(int t) {
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
			sdc->basemobile.Drive(0, 1);
		}
	if (nomdelacommande == "placergear")
		{
			pistongear->Set(true);
		}
	if (nomdelacommande == "lancer")
		{

		}
	if (nomdelacommande == "aligner")
		{

		}

}
bool Commande::isfinished(int t)
{
	if (nomdelacommande == "delai" && t > tempsdebut + deltatemps)
		{
			return true;
		}
	if (nomdelacommande == "tourner" && fabs(sdc->basemobile.GetAngleDelta()) <= 2)
		{
			return true;
		}
	if (nomdelacommande == "avancer" && sdc->basemobile.GetDistance() >= distancefin)
		{
			return true;
		}
	if (nomdelacommande == "placergear" && pistongear==true)
		{
			pistongear->Set(false);
			return true;
		}
	if ()
		{

		}

	return false;
}
