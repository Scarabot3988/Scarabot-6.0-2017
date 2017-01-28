/*
 * ModeAutonome.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_MODEAUTONOME_H_
#define SRC_MODEAUTONOME_H_
#include "config.h"
#include "SystemesDeControle.h"

class ModeAutonome {
public:
	ModeAutonome(SystemesDeControle * _systemesdecontrole);
	virtual ~ModeAutonome();

	void Update();

private:
	SystemesDeControle * systemesdecontrole;
};

#endif /* SRC_MODEAUTONOME_H_ */
