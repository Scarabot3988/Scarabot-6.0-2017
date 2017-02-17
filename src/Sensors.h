/*
 * Sensors.h
 *
 *  Created on: Feb 4, 2017
 *      Author: XPS15
 */

#ifndef SRC_SENSORS_H_
#define SRC_SENSORS_H_

#include<Encoder.h>
#include<WPILib.h>
#include "config.h"

class Sensors
{
	public:
		Sensors();
		virtual ~Sensors();

		Encoder *encoderdrive1;
		Encoder *encoderdrive2;

		ADXRS450_Gyro *gyro;

		//DigitalInput *LMS1;
		//DigitalInput *LMS2;

		DigitalInput *limitswitch_shooter;

		Encoder *encoder_shoot_align;
};

#endif /* SRC_SENSORS_H_ */
