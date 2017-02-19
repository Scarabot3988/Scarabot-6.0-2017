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
		bool activation_grimpeur;
		bool transition_grimpeur;
		bool activation_blocker;

void RobotInit()
	{

	chooser.AddDefault(autoNameDefault, autoNameDefault);
			chooser.AddObject(autoNameCustom, autoNameCustom);
			frc::SmartDashboard::PutData("Auto Modes", &chooser);

	sdc=new SystemesDeControle;
		sdc->initSystemes();
		joyPilote=new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome=new ModeAutonome(sdc);

		ramasseur=new CANTalon(2);
		shifter=new Solenoid(7);
		grimpeurpiston=new Solenoid(6);
		blocker=new DoubleSolenoid(0,5);
		gear=new DoubleSolenoid(1,4);
		capot=new DoubleSolenoid(2,3);
		compressor=new Compressor;
		compressor->Start();
		activation_grimpeur= false;
		activation_blocker=false;
		transition_grimpeur=false;
		blocker->Set(DoubleSolenoid::Value::kReverse);


	}

void AutonomousInit() override
	{
	grimpeurpiston->Set(true);
	autoSelected=chooser.GetSelected();
	 modeautonome->choose_scenario(autoSelected);
	t=0;
	}

void AutonomousPeriodic()
	{
		modeautonome->Execute(t);
		sdc->Update();
		//sdc->moduleVision.test();
		//sdc->lanceur.homein();
		//sdc->lanceur.Update();
		t=t+1;
	}

void TeleopInit()
	{
	}

void TeleopPeriodic()
	{
		//sdc->lanceur.Update();

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
        std::cout << "Courant ramasseur: " << ramasseur->GetOutputCurrent()<< std::endl;
		bool button_ramasseur=joyPilote->GetRawButton(5);

		if(button_ramasseur==true )
			{ramasseur->Set(0.9);

			std::cout<<"on ramasse"<<std::endl;
			}

		else
			{ramasseur->Set(0);
			}



// PISTONS GRIMPEUR ////////////////////////////////////////////////////////////////////////////

		bool button_pistongrimpeur=joyPilote->GetRawButton(12);

		if (button_pistongrimpeur==true){
			if(transition_grimpeur==false){
			   activation_grimpeur = !activation_grimpeur;
			   transition_grimpeur=true;

		    }
		}
		else transition_grimpeur=false;

		grimpeurpiston->Set(activation_grimpeur);


				std::cout << activation_grimpeur<<std::endl;



//BLOCKER/////////////////////////////////////////////////////////
		bool button_blocker=joyPilote->GetRawButton(9);
		if(button_blocker==true)

			blocker->Set(DoubleSolenoid::Value::kForward);



////TURBO////////////////////////////////////////////////////

		bool turbo=joyPilote->GetRawButton(8);
		if(turbo==true)
			sdc->basemobile.SetTurbo();
			else sdc->basemobile.ResetTurbo();
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

		frc::LiveWindow* lw = LiveWindow::GetInstance();
		frc::SendableChooser<std::string> chooser;
		const std::string autoNameDefault = "RB";
		const std::string autoNameCustom = "RBS";
		std::string autoSelected;


		unsigned int t = 0;
		int vieux = 0;bool bon = true;
};

START_ROBOT_CLASS(Robot)
