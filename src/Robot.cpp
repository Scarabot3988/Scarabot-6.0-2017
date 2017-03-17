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
		int vieux = 0;
		bool bon = true;
		float v=0;
		unsigned int t_avantgrimpeur=0;
		bool entraingrimper;

	public:
		FILE *out = 0;
		CANTalon *ramasseur;
		Solenoid *shifter;
		Solenoid *grimpeurpiston;
		Solenoid *blocker;
		Solenoid *secoue;
		CANTalon *intake;
		DoubleSolenoid *capot;
		CANTalon *shooter1;
		CANTalon *shooter2;
		CANTalon *feeder;
		Compressor *compressor;

		bool activation_grimpeur;
		bool transition_grimpeur;
		bool activation_blocker;

void RobotInit()
	{
		chooser.AddDefault("RB", "RB");
		chooser.AddObject("RBS", "RBS");
		chooser.AddDefault("RC", "RC");
		chooser.AddObject("RCS", "RCS");
		chooser.AddDefault("RF", "RF");
		chooser.AddObject("RFS", "RFS");
		chooser.AddDefault("BB", "BB");
		chooser.AddObject("BBS", "BBS");
		chooser.AddDefault("BC", "BC");
		chooser.AddObject("BCS", "BCS");
		chooser.AddDefault("BF", "BF");
		chooser.AddDefault("NONE", "NONE");



		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		activation_grimpeur= false;
		activation_blocker=false;
		transition_grimpeur=false;
		entraingrimper=false;
		CameraServer::GetInstance()->StartAutomaticCapture();

		sdc=new SystemesDeControle;
		sdc->initSystemes();
		joyPilote=new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome=new ModeAutonome(sdc);
		shifter=new Solenoid(SOL_shifter);
		grimpeurpiston=new Solenoid(SOL_grimpeurpiston);
		secoue=new Solenoid(SOL_secoue);
		blocker=new Solenoid(SOL_blocker);
		capot=new DoubleSolenoid(SOL_capot1,SOL_capot2);
		feeder=new CANTalon(3);
		//shooter1=new CANTalon(5);
		//shooter2=new CANTalon(9);
		ramasseur=new CANTalon(7);
		//intake=new CANTalon(15);
		compressor=new Compressor(0);
		compressor->Start();
		blocker->Set(true);

	}

void AutonomousInit() override
	{
		grimpeurpiston->Set(false);
		autoSelected=chooser.GetSelected();
		modeautonome->choose_scenario(autoSelected);
		t=0;
	}

void AutonomousPeriodic()
	{
		modeautonome->Execute(t);
		sdc->Update();
		//sdc->modulevision.test();
		t=t+1;
	}

void TeleopInit()
	{
		sdc->basemobile.ResetTurbo();
	}

void TeleopPeriodic()
	{

// CORRECTION /////////////////////////////////////////////////////////////////////////////////

// DRIVE //////////////////////////////////////////////////////////////////////////////////////
		if(entraingrimper==false)
			{
				sdc->basemobile.Drive(joyPilote->GetRawAxis(0), joyPilote->GetRawAxis(1));
			}

		sdc->Update();

// CAPOT //////////////////////////////////////////////////////////////////////////////////////

		bool button_capot=joyPilote->GetRawButton(1);
		if(button_capot==true)
			{
				capot->Set(DoubleSolenoid::Value::kReverse);
			}
		else
			{
				capot->Set(DoubleSolenoid::Value::kForward);
			}


// RAMASSEUR DE BALLES ////////////////////////////////////////////////////////////////////////

		bool button_ramasseur=joyPilote->GetRawButton(2);

		if(button_ramasseur==true)
			{
				ramasseur->Set(1);
				std::cout<<"on ramasse"<<std::endl;
			}
		else
			{
				ramasseur->Set(0);
			}

// PISTONS GRIMPEUR //////////////////////////////////////////////////////////
#if 0
		bool button_pistongrimpeur=joyPilote->GetRawButton(3);

		if (button_pistongrimpeur==true)
			{
				if(transition_grimpeur==false)
					{
						activation_grimpeur = !activation_grimpeur;
						transition_grimpeur=true;
					}
			}
		else
			{
				transition_grimpeur=false;
			}

		grimpeurpiston->Set(activation_grimpeur);


// BLOCKER /////////////////////////////////////////////////////////

		bool button_blocker=joyPilote->GetRawButton(4);
		if(button_blocker==true)
			{
				blocker->Set(false);
			}
		else
			{
				blocker->Set(true);
			}

#endif

// TURBO ///////////////////////////////////////////////////////////

		bool turbo=joyPilote->GetRawButton(5);
		if(turbo==true)
			{
				sdc->basemobile.SetTurbo();
			}
		else
			{
				sdc->basemobile.ResetTurbo();
			}

// GEAR ///////////////////////////////////////////////////////////

		bool button_secoue= joyPilote->GetRawButton(6);
		bool button_gear =joyPilote->GetRawButton(7);
		if(button_gear==true)
			{
				sdc->gear->Set(DoubleSolenoid::Value::kForward);
			}
		else
			{
				sdc->gear->Set(DoubleSolenoid::Value::kReverse);
			}

		if(button_secoue==true)
			{
				secoue->Set(true);
			}
		else
			{
				secoue->Set(false);
			}

// SHOOTER ///////////////////////////////////////////////////

		/*bool button_vitesseUP=joyPilote->GetRawButton(8);

		if (button_vitesseUP==true)
			{
				v=0.75;
			}
		else
			{
				v=0;
			}

		sdc->shooter1->Set(v);
		sdc->shooter2->Set(v);
		sdc->intake->Set(v);
		*/

// SHIFTER //////////////////////////////////////////////////////////////

		bool button_shifter=joyPilote->GetRawButton(9);
		if(button_shifter==true)
			{
				shifter->Set(true);
			}
		else
			{
				shifter->Set(false);
			}

// BOUTTON GRIMPEUR /////////////////////////////////////////////////////

		bool button_grimpeur=joyPilote->GetRawButton(10);
		if(button_grimpeur==true)
			{
				grimpeurpiston->Set(true);
				blocker->Set(false);
				sdc->basemobile.SetTurbo();
				sdc->basemobile.Drive(0,0.5);
				entraingrimper=true;
			}
		else if(entraingrimper==true)
			{
				sdc->basemobile.Drive(0,0);
				blocker->Set(false);
			}
		t=t+1;

	} // FIN DE TELEOP /////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestPeriodic()
	{
	}

void DisabledPeriodic()
	{
		if (out)
			{
				fclose(out);
			}
	}
};

START_ROBOT_CLASS(Robot)
