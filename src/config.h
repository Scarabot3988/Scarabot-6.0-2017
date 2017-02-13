/*
 * config.h
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// PWM ////////////////////////////
#define PWM_PortMoteurDroite1 0
#define PWM_PortMoteurDroite2 1
#define PWM_PortMoteurDroite3 2
#define PWM_PortMoteurGauche1 3
#define PWM_PortMoteurGauche2 4
#define PWM_PortMoteurGauche3 5
#define PWM_motoralignement   6
#define PWM_motorramaseur     7

// Joystick ///////////////////////////////
#define JOYSTICK_PortJoystickPilote 0

//mapping de manette

#define MAPPING_drivex 0
#define MAPPING_drivey 1
// DIO
#define DIO_drive1a 0
#define DIO_drive1b 1

#define DIO_drive2a 2
#define DIO_drive2b 3

#define DIO_shooterxa 4
#define DIO_shooterxb 5

#define DIO_shooteralign_a 8
#define DIO_shooteralign_b 9

#define DIO_limitswitch_shooter 7
#define DIO_shootb 9

#define DIO_LMS1 10
#define DIO_LMS2 11

#endif /* SRC_CONFIG_H_ */

