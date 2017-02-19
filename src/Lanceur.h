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
#include <CANTalon.h>
class Lanceur
{
	public:
		Lanceur();
		virtual ~Lanceur();
		void Update();
		void setposition(float angle);
		void donnersensor(Sensors* _sensor);
		void homein();
		void mouve_align(bool button_left, bool button_right);

		CANTalon *motoralignement;
		Talon *shoot;
		Sensors *sensors;
		bool limitswitch_trouve;
		int valeurdepart;
		float anglecible;
		float anglepresent;
		float angledepart;
		float v;
		//Solenoid *piston;

};

#endif /* SRC_LANCEUR_H_ */
