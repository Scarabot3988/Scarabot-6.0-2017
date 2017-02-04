 #include <iostream>
#include <memory>
#include <string>
#include "config.h"
#include "SystemesDeControle.h"
#include "modeautonome.h"
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Sensors.h"

class Robot: public frc::IterativeRobot {
public:
	void RobotInit()
	{
		systemesdecontrole.initSystemes();
		joyPilote = new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome = new ModeAutonome(&systemesdecontrole);
		systemesdecontrole.basemobile.donnersensor(sensor);
	}
	void AutonomousInit() override
	{
		t = 0;
	}
	void AutonomousPeriodic()
	{
		modeautonome->Execute(t);
		systemesdecontrole.Update();
		t=t+1;
	}
	void TeleopInit()
	{
	}
	void TeleopPeriodic()
	{
		systemesdecontrole.basemobile.Drive(joyPilote->GetRawAxis(0), joyPilote->GetRawAxis(1));
		systemesdecontrole.Update();
	}
	void TestPeriodic()
	{
	}
private:
	SystemesDeControle systemesdecontrole;
	Joystick * joyPilote;
	ModeAutonome * modeautonome;
	Sensors sensor;
	unsigned int t = 0;



};

START_ROBOT_CLASS(Robot)
