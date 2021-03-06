/*
 * MultiSpeedController.h
 *
 *  Created on: Feb 11, 2017
 *      Author: XPS15
 */

// trouv� ici https://www.reddit.com/r/FRC/comments/2qr29j/6_cim_tank_drive_wpilib/

#ifndef MULTISPEEDCONTROLLER_H_
#define MULTISPEEDCONTROLLER_H_

#include <SpeedController.h>
#include <vector>

class MultiSpeedController: public frc::SpeedController
{
	private:
		std::vector <SpeedController*> speedControllers;
		std::vector <SpeedController*> auxSpeedControllers;

		double speed;
		bool turbo;

	public:
		MultiSpeedController ();
		virtual double Get() const;
		virtual void Set(double speed);
		virtual void PIDWrite(double output);
		virtual void Disable();
		virtual void SetInverted(bool);
		virtual bool GetInverted() const;
		virtual void StopMotor();
		void ResetAux();
		void ResetTurbo()
			{
				turbo=false;
				ResetAux();
			}
		void SetTurbo()
			{
				turbo=true;
			}
		void DonnerMoteur(SpeedController* moteur);
		void DonnerAuxMoteur(SpeedController* moteur);
};

#endif /* MULTISPEEDCONTROLLER_H_ */
