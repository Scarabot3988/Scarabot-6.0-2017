/*
 * Lanceur.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_LANCEUR_H_
#define SRC_LANCEUR_H_
#include <WPILib.h>
class Lanceur {
public:
	Lanceur();
	virtual ~Lanceur();

	void Update();

	frc::Victor *motorx;
	frc::Victor *motory;
	frc::Victor *motorshoot;

};

#endif /* SRC_LANCEUR_H_ */
