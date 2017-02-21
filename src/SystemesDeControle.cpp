/*
 * SystemesDeControle.cpp
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#include <SystemesDeControle.h>

SystemesDeControle::SystemesDeControle()
{
	std::cout << "inside sdc" << std::endl;
	sensors = new Sensors;
	basemobile.donnersensor(sensors);
	lanceur.donnersensor(sensors);
	gear=new DoubleSolenoid(1,4);
}

void SystemesDeControle::initSystemes()
{
}

void SystemesDeControle::Update()
{
	basemobile.Update();
}
