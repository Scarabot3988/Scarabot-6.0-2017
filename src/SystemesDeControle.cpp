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
	basemobile.donnersensor(sensors);
}

void SystemesDeControle::initSystemes()
{
}

void SystemesDeControle::Update()
{
	basemobile.Update();
}
