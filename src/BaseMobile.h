/*
 * BaseMobile.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_BASEMOBILE_H_
#define SRC_BASEMOBILE_H_

#include <WPIlib.h>
#include "config.h"
#include "sensors.h"
#include "MultiSpeedController.h"
#include "math.h"

class MyRobotDrive: public RobotDrive {
public:
	MyRobotDrive(uint32_t leftMotorChannel, uint32_t rightMotorChannel);
		MyRobotDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
					uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel) : RobotDrive(frontLeftMotorChannel,rearLeftMotorChannel,
							frontRightMotorChannel, rearRightMotorChannel){}
		MyRobotDrive(SpeedController *leftMotor, SpeedController *rightMotor): RobotDrive(leftMotor, rightMotor){}
		MyRobotDrive(SpeedController &leftMotor, SpeedController &rightMotor): RobotDrive(leftMotor, rightMotor){}
		MyRobotDrive(SpeedController *frontLeftMotor, SpeedController *rearLeftMotor,
					SpeedController *frontRightMotor, SpeedController *rearRightMotor) : RobotDrive(frontLeftMotor,rearLeftMotor,
		frontRightMotor, rearRightMotor) {}
		MyRobotDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
					SpeedController &frontRightMotor, SpeedController &rearRightMotor):
						RobotDrive(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor){}
		void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs);
};

class BaseMobile
{
	public:
		BaseMobile();
		virtual ~BaseMobile();
		void donnersensor(Sensors*_sensor);
		void Update();
		void Drive(float _x, float _y);
		void ResetDistance();
		void SetAngleDelta(double);
		void SetAngleCible(double);
		void SetTurbo()
			{
				turbo=true;
			}
		void ResetTurbo()
			{
				turbo=false;
			}
		double GetDistance();
		double GetAngleDelta();
		void activerrampe()
		{
			presencerampe=true;
		}
		void desactiverrampe()
		{
			presencerampe=false;
		}

	private:
		void CorrectionGyro();

		double anglecible;
		bool turbo;
		int t = 0;
		float vitesserobot;
		double x;
		double y;
		double ancienx;
		double ancieny;
		bool presencerampe;

		MultiSpeedController *moteurgauche;
		MultiSpeedController *moteurdroit;
		Talon *moteur1gauche;
		Talon *moteur2gauche;
		Talon *moteur3gauche;
		Talon *moteur1droite;
		Talon *moteur2droite;
		Talon *moteur3droite;
		Sensors *sensors;
		RobotDrive *drive;
};

#endif /* SRC_BASEMOBILE_H_ */
