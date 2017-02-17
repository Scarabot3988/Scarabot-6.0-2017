/*
 * BaseMobile.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#include <BaseMobile.h>

BaseMobile::BaseMobile()
{
	x=0;
	y=0;

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

	drive = new RobotDrive(moteurgauche, moteurdroit);
}

BaseMobile::~BaseMobile()
{
	// TODO Auto-generated destructor stub
}

void BaseMobile::Drive(float _x, float _y)
{
	/*float vitesseR;
	float vitesseL;

	vitesseR=(_x+_y)/2;
	vitesseL=(_x-_y)/2;
 std::cout<<_y<<std::endl;
	moteurgauche->Set(vitesseL);
	moteurdroit->Set(vitesseR);
return;
	int t=0;
	if (t<150)
		{
			vitesseR=1.0/(1+std::exp(-5.0*(-1+t/100.0)));
			vitesseL=1.0/(1+std::exp(-5.0*(-1+t/100.0)));
			moteurgauche->Set(vitesseL);
			moteurdroit->Set(vitesseR);
		}
	else
		{
			vitesseR=(x+y)/2;
			vitesseL=(x-y)/2;
		}
	t=t+1;*/
	x=_x;
	y=_y;
}


void BaseMobile::SetAngleCible(double _AngleCible)
{
	AngleCible = _AngleCible;
}

double BaseMobile::GetAngleDelta()
{
	static int n=0;
	n++;
	if(!(n%20))
	   std::cout << "gyro: " << sensors->gyro->GetAngle() << " cible="<< AngleCible << std::endl;
	return AngleCible - sensors->gyro->GetAngle();
}

void BaseMobile::SetAngleDelta(double delta)
{
	AngleCible = sensors->gyro->GetAngle() + delta;
}

void BaseMobile::CorrectionGyro()
{
	double delta=GetAngleDelta();
	double absdelta=abs(delta);
	if (absdelta>3)
		{
			if (absdelta<45)
				{
					x=0.2;
				}
			else
				{
					x=0.3;
				}
		}

	if(delta>0)
		{
			x=-x;

			if (absdelta<45)
				{
					x=0.2;
				}
			else
				{
					x=0.45;
				}
		}

	if(y!=0)
		{
			x=x*y/abs(y);
		}
}

void BaseMobile::Update()
{
	/*if (abs(x)<=0.1)
	{x=0;}

	if(x!=0)
	{t=20;}

	else
	{
		if (t != 0)
		{t = t - 1;}

		else
		{CorrectionGyro();}
	}*/

		drive->ArcadeDrive(y, x);
		//x = y = 0;
}

void BaseMobile::donnersensor(Sensors * _sensor)
{
	sensors = _sensor;
}

double BaseMobile::GetDistance()
{
	std::cout<<"encoder1 d="<<sensors->encoderdrive1->Get()<<std::endl;
	std::cout<<"encoder2 d="<<sensors->encoderdrive2->Get()<<std::endl;

	return (sensors->encoderdrive1->Get() + sensors->encoderdrive2->Get()) / 400.0;
}

void BaseMobile::ResetDistance()
{
	std::cout<<"resetdistance"<<std::endl;
	sensors->encoderdrive1->Reset();
	sensors->encoderdrive2->Reset();
}
