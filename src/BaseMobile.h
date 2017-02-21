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
#include "sensors.h"
#include "MultiSpeedController.h"
#include "math.h"

class BaseMobile
{
	public:
		BaseMobile();

		virtual ~BaseMobile();
		void donnersensor(Sensors*_sensor);
		void Update();
		void Drive(float _x, float _y);
		void ResetDistance();
		void SetAngleDelta(double);
		void SetAngleCible(double);
		void SetTurbo()
			{
				turbo=true;
			}
		void ResetTurbo()
			{
				turbo=false;
			}
		double GetDistance();
		double GetAngleDelta();

	private:
		void CorrectionGyro();

		double anglecible;
		bool turbo;

		MultiSpeedController *moteurgauche;
		MultiSpeedController *moteurdroit;
		Talon *moteur1gauche;
		Talon *moteur2gauche;
		Talon *moteur3gauche;
		Talon *moteur1droite;
		Talon *moteur2droite;
		Talon *moteur3droite;
		Sensors *sensors;
		RobotDrive *drive;

		int t = 0;
		float vitesserobot;
		double x;
		double y;
};

#endif /* SRC_BASEMOBILE_H_ */
