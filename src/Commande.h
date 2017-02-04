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
	Commande(std::string nom, float param1, float param2=0)
{
	if (nom=="delai")
	{
		deltatemps=param1;
	}







nomdelacommande = nom;
tempsfin=0;
demarre=false;
termine=false;
}

virtual ~Commande();

	std::string nomdelacommande;



	bool fini;

	int deltatemps;
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

	void start(int t);

	bool isfinished(int t);
};



#endif /* SRC_COMMANDE_H_ */
