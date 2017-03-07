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
	std::cout << "dans ctr() sensors" << std::endl;

	encoderdriveR=new Encoder(DIO_driveRa,DIO_driveRb);
	encoderdriveL=new Encoder(DIO_driveLa,DIO_driveLb);
	gyro=new ADXRS450_Gyro();
	//limitswitch_shooter=new DigitalInput(DIO_limitswitch_shooter);
	//encoder_shoot_align=new Encoder(DIO_shooteralign_a,DIO_shooteralign_b);

	//encoder_shoot_align->Reset();
}

Sensors::~Sensors()
{
	// TODO Auto-generated destructor stub
}
