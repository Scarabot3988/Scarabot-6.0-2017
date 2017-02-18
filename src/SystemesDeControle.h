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
#include "Vision.h"

class SystemesDeControle
{
	public:
		SystemesDeControle();
		BaseMobile basemobile;
		Lanceur lanceur;
		Sensors *sensors;
		Vision moduleVision;


		void initSystemes();
		void Update();
};

#endif /* SRC_SYSTEMESDECONTROLE_H_ */
