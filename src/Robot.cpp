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

class Robot: public frc::IterativeRobot {
public:
	FILE *out = 0;
	void RobotInit()
	{
		systemesdecontrole.initSystemes();
		joyPilote = new Joystick(JOYSTICK_PortJoystickPilote);
		modeautonome = new ModeAutonome(&systemesdecontrole);
		talon = new CANTalon(0);

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
		out=fopen("/home/lvuser/talon.txt","w");
		printf("GetClosedLoopError\tEncPosition\tGetOutputCurrent\tPosition\tVitesse\n");
		if(out)
			fprintf(out,"GetClosedLoopError\tEncPosition\tGetOutputCurrent\tPosition\tVitesse\n");
		//talon->Set(0.5);
		talon->ConfigLimitMode(frc::CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
		talon->SetFeedbackDevice(CANTalon::QuadEncoder);
	}
	void TeleopPeriodic()
	{
		talon->Set(0.5);
		printf("%d\t%d\t%f\t%f\t%f\n", talon->GetClosedLoopError(), talon->GetEncPosition(), talon->GetOutputCurrent(), talon->GetPosition(),talon->GetSpeed() );
		if(out){
				fprintf(out,"%d\t%d\t%f\t%f\t%f\n", talon->GetClosedLoopError(), talon->GetEncPosition(), talon->GetOutputCurrent(), talon->GetPosition(),talon->GetSpeed() );
				fflush(out);
		}
static int n=0;
if(!(n%20))
	printf("GetClosedLoopError\tEncPosition\tGetOutputCurrent\tPosition\tVitesse\n");
n++;
	}

	void TestPeriodic()
	{

	}

	void DisabledPeriodic(){
		if(out) fclose(out);
	}

private:
	SystemesDeControle systemesdecontrole;
	Joystick * joyPilote;
	ModeAutonome * modeautonome;
	CANTalon * talon;


	unsigned int t = 0;
	int vieux = 0;
	bool bon = true;



};

START_ROBOT_CLASS(Robot)
