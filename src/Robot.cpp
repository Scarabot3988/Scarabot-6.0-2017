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
#include "vision.h"

bool button_pic;
class Robot: public frc::IterativeRobot
{
	private:
		SystemesDeControle *sdc;
		Joystick *joyPilote;
		ModeAutonome *modeautonome;
		frc::LiveWindow* lw = LiveWindow::GetInstance();
		frc::SendableChooser<std::string> chooser;
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
		Compressor *compressor;

		bool activation_grimpeur;
		bool transition_grimpeur;
		bool activation_blocker;

void RobotInit()
	{
		/*chooser.AddDefault("RB", "RB");
		chooser.AddDefault("RC", "RC");
		chooser.AddDefault("RF", "RF");*/
		chooser.AddDefault("Droite", "Droite");
		chooser.AddDefault("Centre", "Centre");
		chooser.AddDefault("Gauche", "Gauche");
		chooser.AddDefault("Testealigner", "Testealigner");
		chooser.AddDefault("Testeapprocher", "Testeapprocher");
		chooser.AddDefault("NONE", "NONE");



		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		activation_grimpeur= false;
		activation_blocker=false;
		transition_grimpeur=false;
		entraingrimper=false;
//		CameraServer::GetInstance()->StartAutomaticCapture();

		sdc=new SystemesDeControle;
		sdc->initSystemes();
		joyPilote=new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome=new ModeAutonome(sdc);
		shifter=new Solenoid(SOL_shifter);
		grimpeurpiston=new Solenoid(SOL_grimpeurpiston);
		secoue=new Solenoid(SOL_secoue);
		blocker=new Solenoid(SOL_blocker);
		ramasseur=new CANTalon(7);
		//intake=new CANTalon(15);
		compressor=new Compressor(0);
		compressor->Start();
		blocker->Set(true);
		Vision::Init();
		shifter->Set(true);

	}



void AutonomousInit() override
	{
		grimpeurpiston->Set(false);
		autoSelected=chooser.GetSelected();
		modeautonome->choose_scenario(autoSelected);
		t=0;
		sdc->basemobile.desactiverrampe();
		//shifter->Set(true);
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
		//sdc->basemobile.ResetTurbo();
		sdc->basemobile.activerrampe();
	}

void TeleopPeriodic()
	{


//std::cout<<"nombre de tours droite  "<< sdc->sensors->encoderdriveR->GetRaw()<<std::endl;
//std::cout<<"nombre de tours gauche  "<< sdc->sensors->encoderdriveL->GetRaw()<<std::endl;
			button_pic=joyPilote->GetRawButton(11);

// DRIVE //////////////////////////////////////////////////////////////////////////////////////
		if(entraingrimper==false)
			{
				sdc->basemobile.Drive(joyPilote->GetRawAxis(0), joyPilote->GetRawAxis(1));
			}

		sdc->Update();

// RAMASSEUR DE BALLES ////////////////////////////////////////////////////////////////////////

		bool button_ramasseur=joyPilote->GetRawButton(2);
		bool button_ramasseur_reverse=joyPilote->GetRawButton(1);

		if(button_ramasseur_reverse==true)
			{
				ramasseur->Set(1);
			//	std::cout << "Courant ramasseur : " << ramasseur->GetOutputCurrent() << std::endl;
			}
		else if (button_ramasseur==true)
			{
				ramasseur->Set(-0.4);
			}
		else
			{
				ramasseur->Set(0);
			}

// PISTONS GRIMPEUR //////////////////////////////////////////////////////////

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



// TURBO ///////////////////////////////////////////////////////////
/*
		bool turbo=joyPilote->GetRawButton(5);
		if(turbo==true)
			{
				sdc->basemobile.SetTurbo();
			}
		else
			{
				sdc->basemobile.ResetTurbo();
			}
*/
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

// SHIFTER //////////////////////////////////////////////////////////////

		bool button_shifter=joyPilote->GetRawButton(9);
		if(button_shifter==true)
			{
				shifter->Set(false);
			}
		else
			{
				shifter->Set(true);
			}

// BOUTTON GRIMPEUR /////////////////////////////////////////////////////
		bool button_grimpeur1=joyPilote->GetRawButton(10);
		if(button_grimpeur1==true)
			{
				if(entraingrimper==false)
					sdc->basemobile.ResetDistance();
				//std::cout << "Distance grimpage: " << sdc->basemobile.GetDistance()<<std::endl;
				grimpeurpiston->Set(true);
				blocker->Set(false);
				sdc->basemobile.Drive(0,1);
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
