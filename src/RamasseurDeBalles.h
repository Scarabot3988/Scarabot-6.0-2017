/*
 * RamasseurDeBalles.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_RAMASSEURDEBALLES_H_
#define SRC_RAMASSEURDEBALLES_H_
#include "config.h"
#include<CANTalon.h>
#include<WPILib.h>
class RamasseurDeBalles {
public:
	RamasseurDeBalles();
	virtual ~RamasseurDeBalles();

	// fontions ///////

	    void mouvealign(bool button_down, bool button_up);
		void Update();
};

//variables
	Talon *motorramasseurdeballes;
	/////Solenoid *piston;




#endif /* SRC_RAMASSEURDEBALLES_H_ */
