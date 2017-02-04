/*
 * Commande.h
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#ifndef SRC_COMMANDE_H_
#define SRC_COMMANDE_H_
# include"string"


class Commande {
public:
	Commande(std::string nom, int maxt)
{
nomdelacommande = nom;
tempsfin=maxt;
demarre=false;
termine=false;

	}

virtual ~Commande();

	std::string nomdelacommande;



	bool fini;

	int tempsdebut;
	int tempsfin;

	float angledebut;

	float angletarget;

	int encoderdebut;

	int encoderfin;

	int commandeafaire;

	bool demarre;

	bool termine;

	bool avancefinie();

	void avancer();

	void tourner();

	void start();

	bool isfinished(int t);
};



#endif /* SRC_COMMANDE_H_ */
