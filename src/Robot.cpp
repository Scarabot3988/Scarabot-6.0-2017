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

	public:
		FILE *out = 0;
		CANTalon *ramasseur;
		Solenoid *shifter;
		Solenoid *grimpeurpiston;
		Solenoid *blocker;
		Solenoid *secoue;


		DoubleSolenoid *capot;
		bool activation_grimpeur;
		bool transition_grimpeur;
		bool activation_blocker;
		CANTalon *shooter1;
		CANTalon *shooter2;
		CANTalon *feeder;

void RobotInit()
	{

	std::cout<<"message "<<std::endl;

	chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		activation_grimpeur= false;
		activation_blocker=false;
		transition_grimpeur=false;

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
		shooter1=new CANTalon(5);
		shooter2=new CANTalon(9);
		ramasseur=new CANTalon(7);

		CameraServer::GetInstance()->StartAutomaticCapture();
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

// SHOOTER //////////////////////////////////////////////////////////////////

		//sdc->lanceur.homein();

// CORRECTION ///////////////////////////////////////////////////////////////




// DRIVE //////////////////////////////////////////////////////////////////////////////////////

		sdc->basemobile.Drive(joyPilote->GetRawAxis(0), joyPilote->GetRawAxis(1));
		sdc->Update();

// CAPOT //////////////////////////////////////////////////////////////////////////////////////

		bool button_capot=joyPilote->GetRawButton(4);
		if(button_capot==true) capot->Set(DoubleSolenoid::Value::kReverse);
		else capot->Set(DoubleSolenoid::Value::kForward);

// RAMASSEUR DE BALLES ////////////////////////////////////////////////////////////////////////

		//std::cout << "Courant ramasseur: " << ramasseur->GetOutputCurrent()<< std::endl;
		bool button_ramasseur=joyPilote->GetRawButton(5);

		if(button_ramasseur==true )
			{
				ramasseur->Set(1);
				std::cout<<"on ramasse"<<std::endl;
			}
		else
			{
				ramasseur->Set(0);
			}

// PISTONS GRIMPEUR //////////////////////////////////////////////////////////

		bool button_pistongrimpeur=joyPilote->GetRawButton(12);

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
		std::cout << activation_grimpeur<<std::endl;

// BLOCKER /////////////////////////////////////////////////////////

		bool button_blocker=joyPilote->GetRawButton(9);
		if(button_blocker==true)
			{
				blocker->Set(false);
			}
		else
			{
				blocker->Set(true);
			}

// TURBO ///////////////////////////////////////////////////////////

		bool turbo=joyPilote->GetRawButton(8);
		if(turbo==true)
			{
				sdc->basemobile.SetTurbo();
			}
		else
			{
				sdc->basemobile.ResetTurbo();
			}

// GEAR ///////////////////////////////////////////////////////////

		bool button_secoue= joyPilote->GetRawButton(19);
		bool button_gear =joyPilote->GetRawButton(13);
		if(button_gear==true)
			{
				sdc->gear->Set(DoubleSolenoid::Value::kForward);
			}
		else
			{
				sdc->gear->Set(DoubleSolenoid::Value::kReverse);
			}

		if(button_secoue==true)		secoue->Set(true);
		else secoue->Set(false);


		//////SHOOTER///////////////////////////////////////////////////

				bool button_feeder=joyPilote->GetRawButton(6);
				bool button_vitesseDown=joyPilote->GetRawButton(15);
				bool button_vitesseUP=joyPilote->GetRawButton(16);

				if(button_feeder==true)
				{
				std::cout<<"message"<<std::endl;
					feeder->Set(0.4);
				}
				else feeder->Set(0);


				if(button_vitesseUP==true) v=v+0.05;



				if(button_vitesseDown==true) v=v-0.05;




				shooter1->Set(v);
				shooter2->Set(v);

///////SHIFTER//////////////////////////////////////////////////////////////
				bool button_shifter=joyPilote->GetRawButton(20);
				if(button_shifter==true) shifter->Set(true);
				else shifter->Set(false);




	} // FIN DE TELEOP /////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestPeriodic()
	{
	}

void DisabledPeriodic()
	{
		if (out)
		fclose(out);
	}
};

START_ROBOT_CLASS(Robot)
