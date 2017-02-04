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

void Commande::start()
{

}
bool Commande::isfinished(int t)
{
	if (t==tempsfin)
		{
		return true;
		}

	return false;
}
