/*
 * Commande.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: prg6robot
 */

#include <Commande.h>




Commande::~Commande()
{

}

void Commande::start(int t)
{
	if (nomdelacommande=="delai")
	{
		tempsdebut=t;
	}
	if (nomdelacommande=="tourner")
		{
			// Le robot va tourner sur lui-même.
		    //Le sens des angles seront dans le sens du cercle trigonométrique(SENS ANTI-HORAIRE POUR MISKA).
			//Alors, si vous voulez tourner à gauche, il faut avoir un angle positif.
		angledebut = sdc->sensors->gyro->GetAngle();
		angletarget = angledebut + deltaangle;
		if(angletarget>0)
		{
			sdc->basemobile.moteur1droite->SetSpeed(-0.5);
			sdc->basemobile.moteur2droite->SetSpeed(-0.5);
			sdc->basemobile.moteur1gauche->SetSpeed(0.5);
			sdc->basemobile.moteur2gauche->SetSpeed(0.5);
		}
		else
		{
			sdc->basemobile.moteur1droite->SetSpeed(0.5);
			sdc->basemobile.moteur2droite->SetSpeed(0.5);
			sdc->basemobile.moteur1gauche->SetSpeed(-0.5);
			sdc->basemobile.moteur2gauche->SetSpeed(-0.5);
		}



		}



}
bool Commande::isfinished(int t)
{
	if (nomdelacommande=="delai" && t>tempsdebut+deltatemps)
		{
			return true;
		}
	if (nomdelacommande=="tourner" && sdc->sensors->gyro->GetAngle()== angletarget)
			{

					sdc->basemobile.moteur1droite->SetSpeed(0);
					sdc->basemobile.moteur2droite->SetSpeed(0);
					sdc->basemobile.moteur1gauche->SetSpeed(0);
					sdc->basemobile.moteur2gauche->SetSpeed(0);

				return true;
			}
	return false;
}
