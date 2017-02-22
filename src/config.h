/*
 * config.h
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// PWM ////////////////////////////////////
#define PWM_PortMoteurDroite1 0
#define PWM_PortMoteurDroite2 1
#define PWM_PortMoteurDroite3 2
#define PWM_PortMoteurGauche1 3
#define PWM_PortMoteurGauche2 4
#define PWM_PortMoteurGauche3 5

// Joystick ///////////////////////////////

#define JOYSTICK_PortJoystickPilote 0

// DIO ////////////////////////////////////

#define DIO_driveRa 0
#define DIO_driveRb 1
#define DIO_driveLa 2
#define DIO_driveLb 3
//#define DIO_shooterxa 4
//#define DIO_shooterxb 5
//#define DIO_limitswitch_shooter 7
//#define DIO_shooteralign_a 8
//#define DIO_shooteralign_b 9

// CAN //////////////////////////

#define CAN_shooterfeed 3
#define CAN_shooter1 5
#define CAN_shooter2 9
#define CAN_ramasseur 7

// SOL ///////////////////////////////

#define SOL_shifter 7
#define SOL_pistongrimpeur 6
#define SOL_secoue 0
#define SOL_blocker 5
#define SOL_capot1 2
#define SOL_capot2 3

#endif /* SRC_CONFIG_H_ */
