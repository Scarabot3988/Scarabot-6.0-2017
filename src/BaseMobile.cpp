/*
 * BaseMobile.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <BaseMobile.h>

BaseMobile::BaseMobile()
{
	// TODO Auto-generated constructor stub

	moteur1droite=new Talon(PORTMOTORDROITE1);
	moteur2droite=new Talon(PORTMOTORDROITE2);
	moteur1gauche=new Talon(PORTMOTORGAUCHE1);
	moteur2gauche=new Talon(PORTMOTORGAUCHE2);
}

BaseMobile::~BaseMobile()
{
	// TODO Auto-generated destructor stub
}

void BaseMobile::miseajour(Joystick *joy)
{
	float x = joy->GetRawAxis(0);
	float y =  joy->GetRawAxis(1);
	float vitesseg = (x-y)/2; // TOURNER À GAUCHE
	float vitessed = (x+y)/2; // TOURNER À DROITE

	moteur1gauche->SetSpeed(vitesseg);
	moteur2gauche->SetSpeed(vitesseg);
	moteur1droite->SetSpeed(vitessed);
	moteur2droite->SetSpeed(vitessed);
}
