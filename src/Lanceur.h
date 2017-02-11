/*
 * Lanceur.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_LANCEUR_H_
#define SRC_LANCEUR_H_
#include <WPILib.h>
#include "sensors.h"
class Lanceur {
public:

	// fontions
	Lanceur();
	virtual ~Lanceur();



	void donnersensor(Sensors* _sensor);
	void Update();
	void homein();
	void mouvealign(bool button_left, bool button_right);

	//variables
	Talon * motoralignement;
	Victor *motorshoot;
	Sensors *sensors;
	bool limitswitch_trouve;
	////Solenoid piston_////

};




#endif /* SRC_LANCEUR_H_ */
