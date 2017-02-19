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
	encoderdrive1=new Encoder(DIO_drive1a,DIO_drive1b);
	encoderdrive2=new Encoder(DIO_drive2a,DIO_drive2b);

	gyro=new ADXRS450_Gyro();
	//LMS1=new DigitalInput(DIO_LMS1);
	//LMS2=new DigitalInput(DIO_LMS2);
	limitswitch_shooter=new DigitalInput(DIO_limitswitch_shooter);
	encoder_shoot_align=new Encoder(DIO_shooteralign_a,DIO_shooteralign_b);
	encoder_shoot_align->Reset();
}

Sensors::~Sensors()
{
	// TODO Auto-generated destructor stub

}
