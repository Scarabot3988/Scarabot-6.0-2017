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
	//limitswitch_trouve=false;
	shoot=new Talon(PWM_motorshoot);
	//sensors=new Sensors;
	//piston=new Solenoid();
	v=0;
	anglecible=0;
	angledepart=0;
	anglepresent=0;
	valeurdepart=0;
}

Lanceur::~Lanceur()
{
	// TODO Auto-generated destructor stub
}

void Lanceur::donnersensor(Sensors * _sensor)
{
	sensors = _sensor;
}

void Lanceur::homein()
{
	/*float vitesse;
	if (limitswitch_trouve == false)
		{
			vitesse = -0.2;

			bool etat_limitswitch;
			etat_limitswitch = sensors->limitswitch_shooter->Get();
			if (etat_limitswitch == true)
				{
					vitesse = 0;
					limitswitch_trouve = true;
					sensors->encoder_shoot_align->Reset();
					anglecible=0;
				}

			motoralignement->Set(vitesse);
		}*/
}

void Lanceur::mouve_align(bool button_left, bool button_right)
{/*
	float vitesse = 0;
	if (button_left == true && sensors->encoder_shoot_align->GetRaw() >= 0)
		{
			vitesse = -0.2;
		}

	if (button_right == true && sensors->encoder_shoot_align->GetRaw() <= 1000)
		{
			vitesse = 0.2;
		}

	if (limitswitch_trouve == true)
		{
			motoralignement->Set(vitesse);
		}*/
}

void Lanceur::setposition(float angle)
{
	float tourencoder;
	float valeurdepart = sensors->encoder_shoot_align->GetRaw();
	tourencoder = angle/0.18;
	angledepart=valeurdepart*0.18;
	anglecible=angle;

	if (anglecible<angledepart)
		{
			v=-0.2;
		}

	if (anglecible>angledepart)
		{
			v=0.2;
		}
}

void Lanceur::Update()
{
	anglepresent=sensors->encoder_shoot_align->GetRaw()*0.18;
	bool stop=false;
	if (angledepart<anglecible && anglepresent>anglecible)
		{
			v=0;
			stop=true;
		}

	if (angledepart>anglecible && anglepresent<anglecible)
		{
			v=0;
			stop=true;
		}

	if(stop==false && fabs(anglepresent-anglecible) < 10)
		{
		    int signv=1;
		    if(v<0) signv=-1;
			v=signv*(0.05+fabs(anglepresent-anglecible) /100.0);
		}

	//motoralignement->Set(v);
}
