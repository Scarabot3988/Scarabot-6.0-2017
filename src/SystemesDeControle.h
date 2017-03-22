/*
 * SystemesDeControle.h
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#ifndef SRC_SYSTEMESDECONTROLE_H_
#define SRC_SYSTEMESDECONTROLE_H_

#include "BaseMobile.h"
#include "Vision.h"
#include "CANTalon.h"


class SystemesDeControle
{
	public:
		SystemesDeControle();
		void initSystemes();
		void Update();

		BaseMobile basemobile;
		Sensors *sensors;
		Vision modulevision;
		DoubleSolenoid *gear;
};

#endif /* SRC_SYSTEMESDECONTROLE_H_ */
