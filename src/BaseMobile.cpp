/*
 * BaseMobile.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <BaseMobile.h>

BaseMobile::BaseMobile() : x(0), y(0)
{

	moteur1droite = new Talon(PWM_PortMoteurDroite1);
	moteur2droite = new Talon(PWM_PortMoteurDroite2);
	moteur1gauche = new Talon(PWM_PortMoteurGauche1);
	moteur2gauche = new Talon(PWM_PortMoteurGauche2);

}

BaseMobile::~BaseMobile()
{
}

void BaseMobile::Drive(float _x, float _y)
{
	x = _x;
	y = _y;
}

void BaseMobile::Update()
{
	float vitesseg = (x-y)/2; // TOURNER À GAUCHE
	float vitessed = (x+y)/2; // TOURNER À DROITE

	moteur1gauche->SetSpeed(vitesseg);
	moteur2gauche->SetSpeed(vitesseg);
	moteur1droite->SetSpeed(vitessed);
	moteur2droite->SetSpeed(vitessed);
}

void BaseMobile::donnersensor(Sensors& _sensor)
{
	sensor=_sensor;
}
