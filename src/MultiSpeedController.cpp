/*
 * MultiSpeedController.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: XPS15
 */

// trouvé ici https://www.reddit.com/r/FRC/comments/2qr29j/6_cim_tank_drive_wpilib/

#include "MultiSpeedController.h"

MultiSpeedController::MultiSpeedController()
	{
        Set(0.0);
    }

double MultiSpeedController::Get() const
	{
		return speed;
	}

void MultiSpeedController::Set(double speed)
	{
		this->speed = speed;

		for (unsigned int i = 0; i < speedControllers.size(); i++)
		{
			speedControllers[i]->Set(speed);
		}
	}
void MultiSpeedController::PIDWrite(double output)
	{
		this->Set(output);
	}

void MultiSpeedController::Disable()
	{
		for (unsigned int i = 0; i < speedControllers.size(); i++)
    		{
				speedControllers[i]->Disable();
    		}
	}

void MultiSpeedController::DonnerMoteur(SpeedController * moteur)
	{
		speedControllers.push_back(moteur);
	}

void MultiSpeedController::SetInverted(bool isInverted)
	{
		for (unsigned int i = 0; i < speedControllers.size(); i++)
		{
			speedControllers[i]->SetInverted(isInverted);
		}
	}

bool MultiSpeedController::GetInverted() const
	{
		if(speedControllers.size() > 0)
			{
				return speedControllers[0]->GetInverted();
			}
		else
			{
				return false;
			}
	}

void MultiSpeedController::StopMotor()
	{
    	for (unsigned int i = 0; i < speedControllers.size(); i++)
    	{
    		speedControllers[i]->StopMotor();
    	}
	}
