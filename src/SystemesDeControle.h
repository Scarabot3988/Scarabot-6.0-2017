/*
 * SystemesDeControle.h
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#ifndef SRC_SYSTEMESDECONTROLE_H_
#define SRC_SYSTEMESDECONTROLE_H_

#include "BaseMobile.h"
#include "Lanceur.h"
#include "RamasseurDeBalles.h"


class SystemesDeControle {
public:
	SystemesDeControle();
	BaseMobile basemobile;
	Lanceur lanceur;
	RamasseurDeBalles ramasseurballes;
	Ramasseur ramasseur;



	void initSystemes();
	void Update();

	Sensors *sensors;

};

#endif /* SRC_SYSTEMESDECONTROLE_H_ */
