/*
 * Lanceur.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <Lanceur.h>
#include <WPILib.h>


Lanceur::Lanceur()
{
	limitswitch_trouve=false;
	alignement=new Talon(PWM_motoralignement);
	shoot=new Talon(PWM_motorshoot);
	//piston=new Solenoid();
}

Lanceur::~Lanceur()
{
	// TODO Auto-generated destructor stub
}

void Lanceur::donnersensor(Sensors * _sensor)
{
	sensors = _sensor;
}

void Lanceur::homein()
{
	float vitesse;
	if (limitswitch_trouve == false)
		{
			vitesse = -0.15;

			bool etat_limitswitch;
			etat_limitswitch = sensors->limitswitch_shooter->Get();

			if (etat_limitswitch == true)
				{
					vitesse = 0;
					limitswitch_trouve = true;
					sensors->encoder_shoot_align->Reset();
				}

			alignement->Set(vitesse);
		}
}
void Lanceur::mouve_align(bool button_left, bool button_right)
{
	float vitesse = 0;
	if (button_left == true && sensors->encoder_shoot_align->GetRaw() <= 1000)
		{
			vitesse = 0.5;
		}

	if (button_right == true && sensors->encoder_shoot_align->GetRaw() >= 0)
		{
			vitesse = -0.5;
		}

	if (limitswitch_trouve == true)
		{
			alignement->Set(vitesse);
		}
}
void Lanceur::setposition(float angle)
{
	float tourencoder;
	int valeurdepart = sensors->encoder_shoot_align->GetRaw();

	tourencoder = angle/0.18;
}

void Lanceur::Update()
{
}
