/*
 * BaseMobile.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_BASEMOBILE_H_
#define SRC_BASEMOBILE_H_
#include <WPIlib.h>

#define PORTMOTORDROITE1 0
#define PORTMOTORDROITE2 1
#define PORTMOTORGAUCHE1 2
#define PORTMOTORGAUCHE2 3

class BaseMobile
{
	public:
	BaseMobile();
	virtual ~BaseMobile();

	void miseajour(Joystick *joy);

	Talon *moteur1gauche;
	Talon *moteur2gauche;
	Talon *moteur1droite;
	Talon *moteur2droite;
};

#endif /* SRC_BASEMOBILE_H_ */
