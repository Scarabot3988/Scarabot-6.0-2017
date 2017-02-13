/*
 * RamasseurDeBalles.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <RamasseurDeBalles.h>
#include <config.h>
RamasseurDeBalles::RamasseurDeBalles() {
	// TODO Auto-generated constructor stub

	////Fonction/////////

}

RamasseurDeBalles::~RamasseurDeBalles() {
	// TODO Auto-generated destructor stub
}

void RamasseurDeBalles::Update() {
}

void  RamasseurDeBallesmouvealign(bool button_down, bool button_up) {
	float vitesse = 0;
	if (button_up == true)
	{
		vitesse = 0.5;
	}
	if (button_down == true)
	{
		vitesse = -0.5;
	}
	//motorramasseurdeballes->Set(vitesse);


