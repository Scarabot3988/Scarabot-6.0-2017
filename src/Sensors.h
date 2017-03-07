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

		Encoder *encoderdriveR;
		Encoder *encoderdriveL;
		ADXRS450_Gyro *gyro;
};

#endif /* SRC_SENSORS_H_ */
