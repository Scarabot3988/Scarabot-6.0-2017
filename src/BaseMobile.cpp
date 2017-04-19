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

void BaseMobile::Update()
{
/*	if(turbo==false)
		{
			moteurgauche->ResetTurbo();
			moteurdroit->ResetTurbo();
		}
	else
		{
			moteurgauche->SetTurbo();
			moteurdroit->SetTurbo();
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
	static int n=0;
	if(!(n%20))
		{
			std::cout<<"distance parcourue G ="<<sensors->encoderdriveL->Get()/155.0<<std::endl;
			std::cout<<"distance parcourue D ="<<sensors->encoderdriveR->Get()/155.0<<std::endl;
		}

	n++;
	return (sensors->encoderdriveR->Get() - sensors->encoderdriveL->Get()) / 310.0;
}

void BaseMobile::ResetDistance()
{
	std::cout<<"reset distance"<<std::endl;
	sensors->encoderdriveR->Reset();
	sensors->encoderdriveL->Reset();
}
#if 0
void MyRobotDrive::ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs)
{
	static bool reported = false;
	if (!reported)
	{
		nUsageReporting::report(nUsageReporting::kResourceType_RobotDrive, GetNumMotors(), nUsageReporting::kRobotDrive_ArcadeStandard);
		reported = true;
	}

	// local variables to hold the computed PWM values for the motors
	float leftMotorOutput;
	float rightMotorOutput;

	moveValue = Limit(moveValue);
	rotateValue = Limit(rotateValue);

	if (squaredInputs)
	{
		// square the inputs (while preserving the sign) to increase fine control while permitting full power
		if (moveValue >= 0.0)
		{
			moveValue = (moveValue * moveValue);
		}
		else
		{
			moveValue = -(moveValue * moveValue);
		}
		if (rotateValue >= 0.0)
		{
			rotateValue = (rotateValue * rotateValue);
		}
		else
		{
			rotateValue = -(rotateValue * rotateValue);
		}
	}

	if (moveValue > 0.0)
	{
		if (rotateValue > 0.0)
		{
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = std::max(moveValue, rotateValue);
		}
		else
		{
			leftMotorOutput = std::max(moveValue, -rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		}
	}
	else
	{
		if (rotateValue > 0.0)
		{
			leftMotorOutput = - std::max(-moveValue, rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		}
		else
		{
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = - std::max(-moveValue, -rotateValue);
		}
	}
	SetLeftRightMotorOutputs(leftMotorOutput, rightMotorOutput);
}
#endif
