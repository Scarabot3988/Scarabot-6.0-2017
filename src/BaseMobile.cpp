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
	anglecible=0;
	vitesserobot=0;

	moteurdroit = new MultiSpeedController();
	moteur1droite = new Talon(PWM_PortMoteurDroite1);
	moteur2droite = new Talon(PWM_PortMoteurDroite2);
	moteur3droite = new Talon(PWM_PortMoteurDroite3);
	moteurgauche = new MultiSpeedController();
	moteur1gauche = new Talon(PWM_PortMoteurGauche1);
	moteur2gauche = new Talon(PWM_PortMoteurGauche2);
	moteur3gauche = new Talon(PWM_PortMoteurGauche3);
	drive = new RobotDrive(moteurgauche, moteurdroit);

	moteurdroit->DonnerAuxMoteur(moteur1droite);
	moteurdroit->DonnerMoteur(moteur2droite);
	moteurdroit->DonnerMoteur(moteur3droite);

	moteurgauche->DonnerAuxMoteur(moteur1gauche);
	moteurgauche->DonnerMoteur(moteur2gauche);
	moteurgauche->DonnerMoteur(moteur3gauche);

	turbo=false;
}

BaseMobile::~BaseMobile()
{
	// TODO Auto-generated destructor stub
}

void BaseMobile::Drive(float _x, float _y)
{
	if (presencerampe==true)
	{
	float accy;
	accy=_y-y;
	if (accy>0.1)
		{
			accy = 0.1;
		}

	if (accy<-0.1)
		{
			accy = -0.1;
		}

	y = y+accy;

	float accx;
	accx=_x-x;
	if(accx<-0.1)
		{
			accx=-0.1;
		}

	if(accx>0.1)
		{
			accx=0.1;
		}

	x=x+accx;
	}

	else
	{
		x=_x;
		y=_y;

	}

}

void BaseMobile::SetAngleCible(double _anglecible)
{
	anglecible = _anglecible;
}

double BaseMobile::GetAngleDelta()
{
	static int n=0;
	n++;
	if(!(n%1))
		{
			std::cout << "gyro: " << sensors->gyro->GetAngle() << " cible="<< anglecible << std::endl;
			return anglecible - sensors->gyro->GetAngle();
		}
}

void BaseMobile::SetAngleDelta(double delta)
{
	anglecible = sensors->gyro->GetAngle() + delta;
	if(delta<0)
		{
			x=.75;
		}
	else
		{
			x=-.75;
		}
	y=0;
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
		{
			x=0;
		}

	if(x!=0)
		{
			t=20;
		}

	else
		{
			if (t != 0)
				{
					t = t - 1;
				}

			else
				{
					CorrectionGyro();

				}
		}*/


	if(turbo==false)
		{
			moteurgauche->ResetTurbo();
			moteurdroit->ResetTurbo();
		}
	else
		{
			moteurgauche->SetTurbo();
			moteurdroit->SetTurbo();
		}

	drive->ArcadeDrive(y, x);

	//x = y = 0;
}

void BaseMobile::donnersensor(Sensors * _sensor)
{
	sensors = _sensor;
}

double BaseMobile::GetDistance()
{
	static int n=0;
	if(!(n%20)){
		std::cout<<"distance parcourue G ="<<sensors->encoderdriveL->Get()/155.0<<std::endl;
		std::cout<<"distance parcourue D ="<<sensors->encoderdriveR->Get()/155.0<<std::endl;
	}
	n++;
	return (-sensors->encoderdriveR->Get() + sensors->encoderdriveL->Get()) / 310.0;
}

void BaseMobile::ResetDistance()
{
	std::cout<<"reset distance"<<std::endl;
	sensors->encoderdriveR->Reset();
	sensors->encoderdriveL->Reset();
}
