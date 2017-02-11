/*
 * Commande.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#include <Commande.h>

Commande::~Commande() {

}

void Commande::start(int t) {
	if (nomdelacommande == "delai") {
		tempsdebut = t;
	}
	if (nomdelacommande == "tourner") {
		// Le robot va tourner sur lui-m�me.
		//Le sens des angles seront dans le sens du cercle trigonom�trique(SENS ANTI-HORAIRE POUR MISKA).
		//Alors, si vous voulez tourner � gauche, il faut avoir un angle positif.
		sdc->basemobile.SetAngleDelta(deltaangle);
	}
	if (nomdelacommande == "avancer") {
		sdc->basemobile.ResetDistance();
		sdc->basemobile.Drive(0, 1);

	}
	if (nomdelacommande == "placergear") {

	}

}
bool Commande::isfinished(int t) {
	if (nomdelacommande == "delai" && t > tempsdebut + deltatemps) {
		return true;
	}
	if (nomdelacommande == "tourner"
			&& fabs(sdc->basemobile.GetAngleDelta()) <= 2) {
		return true;
	}
	if (nomdelacommande == "avancer"
			&& sdc->basemobile.GetDistance() >= distancefin) {
		return true;
	}
	return false;

}
