/*
 * Commande.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#include <Commande.h>




Commande::~Commande() {
	// TODO Auto-generated destructor stub
}

void Commande::start(int t)
{
	if (nomdelacommande=="delai")
	{
		tempsdebut=t;
	}
}
bool Commande::isfinished(int t)
{
	if (nomdelacommande=="delai" && t>tempsdebut+deltatemps)
		{
			return true;
		}

	return false;
}
