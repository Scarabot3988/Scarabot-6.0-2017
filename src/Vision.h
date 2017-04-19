/*
 * Vision.h
 *
 *  Created on: Feb 18, 2017
 *      Author: XPS15
 */
#include <iostream>
#include <WPILib.h>

#ifndef SRC_VISION_H_
#define SRC_VISION_H_

#include <memory>

class Vision
{
	public:
		static void Init();
		static void Start(){
			if(m_bStart==false){
				m_bDone=false;
				m_bStart=true;
			}
			else std::cout << "Vision deja commence"<<std::endl;
		}
		static bool IsDone(){ return m_bDone;}
		static float GetDistance();
		static float GetAngle();
		static bool m_bStart;
		static bool m_bDone;
		static int m_nCentreX,m_nCentreY, m_nHauteur, m_nLargeur;
};

#endif /* SRC_VISION_H_ */
