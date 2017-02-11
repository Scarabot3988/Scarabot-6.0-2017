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
	limitswitch_trouve= false;
	motoralignement = new Talon(PWM_motoralignement);

}

// fontions ////////////
Lanceur::~Lanceur() {
	// TODO Auto-generated destructor stub
}
void Lanceur::donnersensor(Sensors * _sensor)
{

	sensors = _sensor;

}

void Lanceur::homein()
{
	float vitesse;
	if (limitswitch_trouve == false) {
		vitesse = -0.15;

		bool etat_limitswitch;
		etat_limitswitch = sensors->limitswitch_shooter->Get();

		if (etat_limitswitch == true) {

			vitesse = 0;
			limitswitch_trouve = true;
			sensors->encoder_shoot_align->Reset();

		}

		motoralignement->Set(vitesse);

	}
}
void Lanceur::mouvealign(bool button_left, bool button_right)
{
	float vitesse = 0;
	if (button_left == true && sensors->encoder_shoot_align->GetRaw() <= 1000) {
		vitesse = 0.5;
	}
	if (button_right == true && sensors->encoder_shoot_align->GetRaw() >= 0) {
		vitesse = -0.5;
	}

	if (limitswitch_trouve == true) {
		motoralignement->Set(vitesse);
	}

}
void Lanceur::Update() {


}
