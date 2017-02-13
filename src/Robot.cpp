#include <iostream>
#include <stdio.h>
#include <memory>
#include <string>
#include "config.h"
#include "SystemesDeControle.h"
#include "modeautonome.h"
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "CANTalon.h"
#include "Sensors.h"
#include "RamasseurDeBalles.h"

class Robot: public frc::IterativeRobot
{
	public:
		FILE *out = 0;
		void RobotInit()
			{
				sdc = new SystemesDeControle;
				sdc->initSystemes();
				joyPilote = new Joystick(JOYSTICK_PortJoystickPilote);
				//modeautonome = new ModeAutonome(sdc);
				talon = new CANTalon(0);
			}

void AutonomousInit() override
	{
		t = 0;
	}

void AutonomousPeriodic()
	{
		modeautonome->Execute(t);
		sdc->Update();
		t = t + 1;
	}

void TeleopInit()
	{
	//out=fopen("/home/lvuser/talon.txt","w");
	//	printf("GetClosedLoopError\tEncPosition\tGetOutputCurrent\tPosition\tVitesse\n");
	//if(out)
	//	fprintf(out,"GetClosedLoopError\tEncPosition\tGetOutputCurrent\tPosition\tVitesse\n");

	//talon->Set(0.5);
	//	talon->ConfigLimitMode(frc::CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
	//	talon->SetFeedbackDevice(CANTalon::QuadEncoder);

	}

void TeleopPeriodic()
	{
		sdc->lanceur.homein();
		//tests alignement

		bool button_1=joyPilote->GetRawButton(10);
		bool button_2=joyPilote->GetRawButton(11);
		sdc->lanceur.mouvealign(button_1,button_2);

		if (button_1==false)
			{
				sdc->basemobile.SetAngleDelta(0);
			}

		//Ramasseur/////////////////////////


		//talon->Set(0.5);
		//printf("%d\t%d\t%f\t%f\t%f\n", talon->GetClosedLoopError(), talon->GetEncPosition(), talon->GetOutputCurrent(), talon->GetPosition(),talon->GetSpeed() );
		//if(out)
		//	{
		//		fprintf(out,"%d\t%d\t%f\t%f\t%f\n", talon->GetClosedLoopError(), talon->GetEncPosition(), talon->GetOutputCurrent(), talon->GetPosition(),talon->GetSpeed() );
		//		fflush(out);
		//	}
		std::cout << "GYRO: " << sdc->sensors->gyro->GetAngle() << '\n';
		std::cout << "ENCODEUR: " << sdc->sensors->drive1->GetDistance() << '\n';

		sdc->basemobile.Drive(joyPilote->GetRawAxis(MAPPING_drivex),
		joyPilote->GetRawAxis(MAPPING_drivey));

		sdc->Update();
	}

void TestPeriodic()
	{
	}

void DisabledPeriodic()
	{
		if (out)
		fclose(out);
	}

	private:
		SystemesDeControle *sdc;
		Joystick *joyPilote;
		ModeAutonome *modeautonome;

		CANTalon *talon;

		unsigned int t = 0;
		int vieux = 0;bool bon = true;
};

START_ROBOT_CLASS(Robot)
