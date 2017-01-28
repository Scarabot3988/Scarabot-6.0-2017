/*
 * bras.h
 *
 *  Created on: 28 janv. 2017
 *      Author: Marc
 */

#ifndef SRC_BRAS_H_
#define SRC_BRAS_H_
#include "config.h"
#include "WPIlib.h"
class bras {
public:
	bras();
	virtual ~bras();
	void Set(float _z);
	void Update();

private:
	Talon *moteurbras;

	float z;


};

#endif /* SRC_BRAS_H_ */
