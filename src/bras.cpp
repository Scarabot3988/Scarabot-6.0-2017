/*
 * bras.cpp
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#include <bras.h>

bras::bras() {
	// TODO Auto-generated constructor stub
moteurbras=new Talon(PWM_portmoteurbras);
z=0;
}

bras::~bras() {
	// TODO Auto-generated destructor stub
}

void bras::Set(float _z)
{
	z=_z;
}

void bras::Update()
{
	moteurbras->SetSpeed(z);
}
