/*
 * Commande.h
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#ifndef SRC_COMMANDE_H_
#define SRC_COMMANDE_H_
#include"string"
#include "SystemesDeControle.h"

class Commande
{
	public:
		Commande(SystemesDeControle* p, std::string nom, float param1, float param2 = 0)
			{
				sdc = p;
				if (nom == "delai")
					{
						deltatemps = param1;
					}

				if (nom == "tourner")
					{
						deltaangle = param1;
					}

				if (nom == "avancer")
					{
						targetdistance = param1;
						targetspeed = param2;
					}

				if (nom == "reculer")
					{
						targetdistance = -param1;
						targetspeed = param2;
					}

				if (nom == "lancer")
					{
					}

				nomdelacommande = nom;
				tempsfin = 0;
				demarre = false;
				termine = false;
			}

		virtual ~Commande();
		void avancer();
		void tourner();
		void start(int t);
		bool isfinished(int t);
		bool avancefinie();

		std::string nomdelacommande;
		SystemesDeControle *sdc;

		int deltatemps;
		int tempsdebut;
		int tempsfin;
		float deltaangle;
		float targetdistance;
		float targetspeed;
		bool demarre;
		bool termine;
};

#endif /* SRC_COMMANDE_H_ */
