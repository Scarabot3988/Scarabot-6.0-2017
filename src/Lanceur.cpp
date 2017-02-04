/*
 * Lanceur.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <Lanceur.h>
#include <WPILib.h>


Lanceur::Lanceur()
{
	motorx= new Victor(0);

}

Lanceur::~Lanceur() {
	// TODO Auto-generated destructor stub
}

void Lanceur::Update() {
}
