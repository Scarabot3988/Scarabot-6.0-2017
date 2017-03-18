/*
 * config.h
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// PWM ////////////////////////////////////
#define PWM_PortMoteurDroite1 2
#define PWM_PortMoteurDroite2 1
#define PWM_PortMoteurDroite3 0
#define PWM_PortMoteurGauche1 5
#define PWM_PortMoteurGauche2 4
#define PWM_PortMoteurGauche3 3

// Joystick ///////////////////////////////

#define JOYSTICK_PortJoystickPilote 0

// DIO ////////////////////////////////////

#define DIO_driveRa 0
#define DIO_driveRb 1
#define DIO_driveLa 2
#define DIO_driveLb 3

// CAN //////////////////////////

#define CAN_intake 3
#define CAN_shooter1 5
#define CAN_ramasseur 7

// SOL ///////////////////////////////

#define SOL_secoue 0
#define SOL_capot1 2
#define SOL_capot2 3
#define SOL_blocker 5
#define SOL_grimpeurpiston 6
#define SOL_shifter 7

#endif /* SRC_CONFIG_H_ */
