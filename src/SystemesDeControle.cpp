/*
 * SystemesDeControle.cpp
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#include <SystemesDeControle.h>

SystemesDeControle::SystemesDeControle(){
	sensors= new Sensors;
	basemobile.donnersensor(sensors);
}

void SystemesDeControle::initSystemes()
{

}

void SystemesDeControle::Update()
{

	basemobile.Update();
	grimpeur.Update();
	ramasseur.Update();
	ramasseurballes.Update();

}
