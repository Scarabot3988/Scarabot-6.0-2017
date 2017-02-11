/*
 * ModeAutonome.h
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#ifndef SRC_MODEAUTONOME_H_
#define SRC_MODEAUTONOME_H_
#include "config.h"
#include "SystemesDeControle.h"
#include "Commande.h"
#include "Sensors.h"

class ModeAutonome {
public:
	ModeAutonome(SystemesDeControle * _systemesdecontrole);
	virtual ~ModeAutonome();

	void Execute(int t);
	void choose_scenario(int n);


private:
	SystemesDeControle * systemesdecontrole;
	std::vector<Commande> listecommande;

	int commandeencours;
};

#endif /* SRC_MODEAUTONOME_H_ */
