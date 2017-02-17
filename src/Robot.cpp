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
		CANTalon *ramasseur;
		Solenoid *shifter;
		Solenoid *grimpeurpiston;
		DoubleSolenoid *blocker;
		DoubleSolenoid *gear;
		DoubleSolenoid *capot;
		Compressor *compressor;

void RobotInit()
	{
		sdc=new SystemesDeControle;
		sdc->initSystemes();
		joyPilote=new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome=new ModeAutonome(sdc);
		modeautonome->choose_scenario(1);
		ramasseur=new CANTalon(0);
		shifter=new Solenoid(7);
		grimpeurpiston=new Solenoid(6);
		blocker=new DoubleSolenoid(0,5);
		gear=new DoubleSolenoid(1,4);
		capot=new DoubleSolenoid(2,3);
		compressor=new Compressor;
		compressor->Start();
	}

void AutonomousInit() override
	{
		t=0;
	}

void AutonomousPeriodic()
	{
		modeautonome->Execute(t);
		sdc->Update();
		t=t+1;
	}

void TeleopInit()
	{
	}

void TeleopPeriodic()
	{

// SHOOTER //////////////////////////////////////////////////////////////////////////

		//sdc->lanceur.homein();

// CORRECTION //////////////////////////////////////////////////////////////////////

		bool button1=joyPilote->GetRawButton(10);
		bool button2=joyPilote->GetRawButton(11);
		//sdc->lanceur.mouve_align(button1,button2);

		if (button1==false)
			{
				sdc->basemobile.SetAngleDelta(0);
			}

		std::cout << "GYRO: " << sdc->sensors->gyro->GetAngle() << '\n';


// DRIVE //////////////////////////////////////////////////////////////////////////////

		sdc->basemobile.Drive(joyPilote->GetRawAxis(0), joyPilote->GetRawAxis(1));
		sdc->Update();

// CAPOT ///////////////////////////////////////////////////////////////////////////////

		bool button_capot=joyPilote->GetRawButton(4);
		if(button_capot==true) capot->Set(DoubleSolenoid::Value::kForward);
		else capot->Set(DoubleSolenoid::Value::kOff);

// RAMASSEUR DE BALLES //////////////////////////////////////////////////////////////////

		bool button_ramasseur=joyPilote->GetRawButton(5);
		bool button_invert=joyPilote->GetRawButton(6);

		if(button_ramasseur==true && button_invert==false)
			{ramasseur->Set(1);}
		else
			{ramasseur->Set(0);}

		//if (button_invert==true && button_ramasseur==true)
			//{ramasseur->Set(-1);}
		//else ramasseur->Set(0);



// PISTONS GRIMPEUR ////////////////////////////////////////////////////////////////////////////

		bool button_pistongrimpeur=joyPilote->GetRawButton(12);

		if (button_pistongrimpeur==true)
		{
			grimpeurpiston->Set(true);
		}
		else
		{
			grimpeurpiston->Set(false);
		}

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
