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

class BaseMobile {
public:
	BaseMobile();
	virtual ~BaseMobile();
	void donnersensor(Sensors*_sensor);
	void Update();
	void Drive(float _x, float _y);
	double GetDistance();
	void ResetDistance();

	void SetAngleDelta(double);
	void SetAngleCible(double);
	double GetAngleDelta();

private:
	void CorrectionGyro();

	double AngleCible;

	MultiSpeedController *moteurgauche;

	Talon *moteur1gauche;
	Talon *moteur2gauche;
	Talon *moteur3gauche;

	MultiSpeedController *moteurdroit;

	Talon *moteur1droite;
	Talon *moteur2droite;
	Talon *moteur3droite;
	Sensors *sensors;

	RobotDrive *drive;

	int t = 0;

	double x;
	double y;
};

#endif /* SRC_BASEMOBILE_H_ */
