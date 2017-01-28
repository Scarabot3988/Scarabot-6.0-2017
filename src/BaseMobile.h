/*
 * BaseMobile.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_BASEMOBILE_H_
#define SRC_BASEMOBILE_H_
#include <WPIlib.h>
#include "config.h"

class BaseMobile
{
	public:
	BaseMobile();
	virtual ~BaseMobile();

	void Update();
	void Drive(float _x, float _y);

	private:
	Talon *moteur1gauche;
	Talon *moteur2gauche;
	Talon *moteur1droite;
	Talon *moteur2droite;


	float x;
	float y;
};

#endif /* SRC_BASEMOBILE_H_ */
