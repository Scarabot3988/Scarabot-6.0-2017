/*
 * MultiSpeedController.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: XPS15
 */

// trouvé ici https://www.reddit.com/r/FRC/comments/2qr29j/6_cim_tank_drive_wpilib/

#include <iostream>
#include "MultiSpeedController.h"

MultiSpeedController::MultiSpeedController()
	{
        Set(0.0);
        turbo=false;
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

		if(turbo==true)
			{
				for (unsigned int i = 0; i < auxSpeedControllers.size(); i++)
					{
						auxSpeedControllers[i]->Set(speed);
					}
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

		for (unsigned int i = 0; i < auxSpeedControllers.size(); i++)
		    {
				auxSpeedControllers[i]->Disable();
		    }
		ResetTurbo();
	}

void MultiSpeedController::DonnerMoteur(SpeedController *moteur)
	{
		speedControllers.push_back(moteur);
	}

void MultiSpeedController::DonnerAuxMoteur(SpeedController *moteur)
	{
		auxSpeedControllers.push_back(moteur);
	}

void MultiSpeedController::SetInverted(bool isInverted)
	{
		for (unsigned int i = 0; i < speedControllers.size(); i++)
			{
				speedControllers[i]->SetInverted(isInverted);
			}

		for (unsigned int i = 0; i < auxSpeedControllers.size(); i++)
			{
				auxSpeedControllers[i]->SetInverted(isInverted);
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

    	ResetTurbo();
	}

void MultiSpeedController::ResetAux()
	{
    	for (unsigned int i = 0; i < auxSpeedControllers.size(); i++)
    		{
    			auxSpeedControllers[i]->Disable();
    		}
	}
