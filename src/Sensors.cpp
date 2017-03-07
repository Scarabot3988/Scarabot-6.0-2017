/*
 * Sensors.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: XPS15
 */

#include <Sensors.h>
#include <Encoder.h>

Sensors::Sensors()
{
	encoderdriveR=new Encoder(DIO_driveRa,DIO_driveRb);
	encoderdriveL=new Encoder(DIO_driveLa,DIO_driveLb);
	gyro=new ADXRS450_Gyro();
}

Sensors::~Sensors()
{
	// TODO Auto-generated destructor stub
}
