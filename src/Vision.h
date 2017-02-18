/*
 * Vision.h
 *
 *  Created on: Feb 18, 2017
 *      Author: XPS15
 */

#include <WPILib.h>

#ifndef SRC_VISION_H_
#define SRC_VISION_H_

#include <memory>

class Vision {
public:

	std::shared_ptr<NetworkTable> Net;

	Vision();
	virtual ~Vision();

	void test();

	float calculdistance(int pix);
};

#endif /* SRC_VISION_H_ */
