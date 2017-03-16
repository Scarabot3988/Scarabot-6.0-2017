/*
 * SystemesDeControle.cpp
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#include <SystemesDeControle.h>
#include "CANTalon.h"

SystemesDeControle::SystemesDeControle()
{
	sensors = new Sensors;
	gear=new DoubleSolenoid(1,4);
	//shooter1=new CANTalon(13);
	//shooter2=new CANTalon(14);
	//intake=new CANTalon(15);
	basemobile.donnersensor(sensors);
}

void SystemesDeControle::initSystemes()
{
}

void SystemesDeControle::Update()
{
	basemobile.Update();
}
