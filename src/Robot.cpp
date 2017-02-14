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

class Robot: public frc::IterativeRobot
{
	public:
		FILE *out = 0;
		Solenoid *capot;
		CANTalon *ramasseur;

void RobotInit()
	{
		sdc = new SystemesDeControle;
		sdc->initSystemes();
		joyPilote = new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome = new ModeAutonome(sdc);
		modeautonome->choose_scenario(0);
		capot=new Solenoid(3);
		ramasseur=new CANTalon(6);

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

		std::cout << "GYRO: " << sdc->sensors->gyro->GetAngle() << '\n';
		std::cout << "ENCODEUR: " << sdc->sensors->encoderdrive1->GetRaw() << '\n';


		sdc->basemobile.Drive(joyPilote->GetRawAxis(MAPPING_drivex), joyPilote->GetRawAxis(MAPPING_drivey));

/////////////////////////////////////////// CAPOT
		bool button_capot=joyPilote->GetRawButton(4);
		if(button_capot==true) capot->Set(true);
		else capot->Set(false);


///////////////////////////////////RAMASSEUR DE BALLES

		bool button_invert=joyPilote->GetRawButton(5);

		bool button_ramasseur=joyPilote->GetRawButton(6);

		if(button_ramasseur==true && button_invert==false) ramasseur->Set(1);
		else ramasseur->Set(0);
		if (button_invert==true && button_ramasseur==true) ramasseur->Set(-1);
		else ramasseur->Set(0);

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
