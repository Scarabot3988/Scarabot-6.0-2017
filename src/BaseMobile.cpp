/*
 * BaseMobile.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <BaseMobile.h>

BaseMobile::BaseMobile() : x(0), y(0)
{

	moteurdroit = new MultiSpeedController();

	moteur1droite = new Talon(PWM_PortMoteurDroite1);
	moteur2droite = new Talon(PWM_PortMoteurDroite2);
	moteur3droite = new Talon(PWM_PortMoteurDroite3);

	moteurdroit->DonnerMoteur(moteur1droite);
	moteurdroit->DonnerMoteur(moteur2droite);
	moteurdroit->DonnerMoteur(moteur3droite);




	moteurgauche = new MultiSpeedController();

	moteur1gauche = new Talon(PWM_PortMoteurGauche1);
	moteur2gauche = new Talon(PWM_PortMoteurGauche2);
	moteur3gauche = new Talon(PWM_PortMoteurGauche3);

	moteurgauche->DonnerMoteur(moteur1gauche);
	moteurgauche->DonnerMoteur(moteur2gauche);
	moteurgauche->DonnerMoteur(moteur3gauche);

drive= new RobotDrive(moteurgauche, moteurdroit);

}

BaseMobile::~BaseMobile()
{
}

void BaseMobile::Drive(float _x, float _y)
{
	x = _x;
	y = _y;


}

void BaseMobile::SetAngleCible(double _AngleCible)
{
	AngleCible= _AngleCible;
}
double BaseMobile::GetAngleDelta()
{
	return AngleCible-sensors->gyro->GetAngle();
}

void BaseMobile::SetAngleDelta(double delta)
{
	AngleCible=sensors->gyro->GetAngle() + delta;
}

void BaseMobile::CorrectionGyro()
{

	double delta=GetAngleDelta();
	double absdelta=abs(delta);
	if (absdelta>3)
	{
		if (absdelta<30) x=0.2;
		else x=0.6;



	}
	else x=0;

	if(delta<0) x=-x;


}

void BaseMobile::Update()
{
	if (abs(x)<=0.05 )x=0;

	if(x!=0) t=15;

	else
	{
		if(t!=0) t=t-1;

		else
		{
			CorrectionGyro();
		}
	}


	drive->ArcadeDrive(y,x);
x=y=0;




}


void BaseMobile::donnersensor(Sensors * _sensor)
{
	sensors = _sensor;

}


double BaseMobile::GetDistance()
{
	 return (sensors->drive1->GetDistance() + sensors->drive2->GetDistance())/2;

}

void BaseMobile::ResetDistance()
{
	sensors->drive1->Reset();
	sensors->drive2->Reset();

}

