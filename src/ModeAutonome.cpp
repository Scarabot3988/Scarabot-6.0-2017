/*
 * ModeAutonome.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <ModeAutonome.h>

ModeAutonome::ModeAutonome(SystemesDeControle * _systemesdecontrole)
{
 listecommande.push_back(Commande(_systemesdecontrole,"delai", 50));
 listecommande.push_back(Commande(_systemesdecontrole,"avancer",300));
 listecommande.push_back(Commande(_systemesdecontrole,"lancer",400));
 listecommande.push_back(Commande(_systemesdecontrole,"placer la gear",500));
 commandeencours=0;
 systemesdecontrole=_systemesdecontrole;

}

ModeAutonome::~ModeAutonome() {
}

void ModeAutonome::Execute(int t)
{
	int i=commandeencours;

	std::cout << "commande en exécution: " << listecommande[i].nomdelacommande <<std::endl;

	if(listecommande[0].demarre==false)
	{
		std::cout<<"on démarre"<<std::endl;
		listecommande[0].demarre=true;
		listecommande[0].start(t);
	}

	if (listecommande[i].demarre==true && listecommande[i].termine==false && listecommande[i].isfinished(t)==true)
	{
		std::cout<<"commande finie"<<std::endl;
		listecommande[i].termine=true;
	}

	if (listecommande[i].termine==true && listecommande[i+1].demarre==false)
	{
		std::cout<<"entre deux commandes"<<std::endl;
		i=i+1;
		listecommande[i].demarre=true;
		listecommande[i].start(t);
	}
	commandeencours=i;
}
