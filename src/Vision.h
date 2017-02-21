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

class Vision
{
	public:
		Vision();

		virtual ~Vision();
		void test();
		float calculdistance(int pix);

		std::shared_ptr<NetworkTable> Net;
};

#endif /* SRC_VISION_H_ */
