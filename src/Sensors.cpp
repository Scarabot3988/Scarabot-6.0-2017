/*
 * Sensors.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: XPS15
 */

#include <Sensors.h>

Sensors::Sensors()
{
	drive1=new Encoder(DIO_drive1a,DIO_drive1b);
	drive2=new Encoder(DIO_drive2a,DIO_drive2b);
	shooterx=new Encoder(DIO_shooterxa,DIO_shooterxb);
	shootery=new Encoder(DIO_shooterya,DIO_shooteryb);
	shoot=new Encoder(DIO_shoota,DIO_shootb);
	gyro=new ADXRS450_Gyro();
	LMS1=new DigitalInput(DIO_LMS1);
	LMS2=new DigitalInput(DIO_LMS2);


}

Sensors::~Sensors() {
	// TODO Auto-generated destructor stub
}

