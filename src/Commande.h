/*
 * Commande.h
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#ifndef SRC_COMMANDE_H_
#define SRC_COMMANDE_H_
# include"string"
#include "SystemesDeControle.h"

class Commande {
public:
	Commande(SystemesDeControle* p, std::string nom, float param1,
			float param2 = 0) {

		sdc = p;
		if (nom == "delai") {
			deltatemps = param1;
		}

		if (nom == "tourner") {
			deltaangle = param1;
		}
		if (nom == "avancer") {
			targetdistance = param1;
			targetspeed = param2;
		}

		nomdelacommande = nom;
		tempsfin = 0;
		demarre = false;
		termine = false;

		pistongear = new Solenoid(0);
	}

	virtual ~Commande();

// Place pour variables

	std::string nomdelacommande;

	SystemesDeControle *sdc;

	bool fini;

	int deltatemps;
	int tempsdebut;
	int tempsfin;

	float angledebut;
	float angletarget;
	float deltaangle;
	float targetdistance;
	float targetspeed;
	int distancefin;

	int commandeafaire;

	int i;

	bool demarre;

	bool termine;

	bool avancefinie();

	void avancer();

	void tourner();

	void start(int t);

	bool isfinished(int t);

	Solenoid *pistongear;
};

#endif /* SRC_COMMANDE_H_ */
