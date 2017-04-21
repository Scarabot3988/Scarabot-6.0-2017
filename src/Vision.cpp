/*
 * Vision.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: XPS15
 */
#include <unistd.h>
#include <Vision.h>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include "wpilib.h"
#define MINRECTSIZE  500
#define MAXRECTSIZE  2000

static void VisionThread();
bool Vision::m_bStart=false;
bool Vision::m_bDone=false;
int Vision::m_nCentreX=-1;
int Vision::m_nCentreY=-1;
int Vision::m_nHauteur=-1;
int Vision::m_nLargeur=-1;


void Vision::Init()
{
	std::thread visionThread(VisionThread);
	visionThread.detach();

}

float Vision::GetDistance()
{
	float distance=0;
	float surface;
	surface=m_nHauteur*m_nLargeur;
	std::cout<<"surface= "<<surface<<std::endl;
	if(surface>1)
	{
		distance=sqrt(32250/surface)*13;
	}
	std::cout<<"distance= "<<distance<<std::endl;
	return distance;
}

float Vision::GetAngle()
{
	float angle=0;
	float distance=GetDistance();

	angle=atan2(45,distance);
	angle=angle*360/(2*3.1415962);
	std::cout<<"angle= "<<angle<<std::endl;
	return angle;
}

static void VisionThread()
{
	cs::UsbCamera camera =CameraServer::GetInstance()->StartAutomaticCapture();

	camera.SetResolution(320, 240);
	camera.SetBrightness(20);
	camera.SetExposureManual(20);
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	//cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Vision", 640, 360);



	int n=0;
	char str[80];
	cv::Mat source;
	cv::Mat output;
	while(true)
	{

		cvSink.GrabFrame(source);

		if(Vision::m_bStart)
		{
			std::cout << "Doing vision" << std::endl;

			Vision::m_nCentreX= -1;
			Vision::m_nCentreY= -1;
			Vision::m_nHauteur= -1;
			Vision::m_nLargeur= -1;

			// Si image pas vide
			if(source.empty()==false){
				cv::Mat image=source.clone();
				sprintf(str,"/home/lvuser/gear%d.png",n++);

				//        		cv::MSER ms(5, 5000, 50000);
				std::vector<std::vector<cv::Point>> regions;
				std::vector<cv::Rect> bboxes;
				//      		        ms(image, regions, cv::Mat());

				cv::Ptr< cv::MSER> mser = cv::MSER::create(5,MINRECTSIZE, MAXRECTSIZE);
				mser->detectRegions(image, regions, bboxes);

				// Affichage des regions trouvees dans l'image
				for(unsigned int k=0; k<bboxes.size(); k++)
					cv::rectangle(image,bboxes[k],cv::Scalar(0,255,255),2);

				// notre cible est la plus grosse region
				cv::Rect oBestRegion(0,0,0,0);
				for (unsigned int i = 0; i < bboxes.size(); i++)
				{
					double w = bboxes[i].width;
					double h = bboxes[i].height;
					int cx=bboxes[i].x+bboxes[i].width/2;
					int cy=bboxes[i].y+bboxes[i].height/2;
					// si le rapport largeur/hauteur est bon et que la boite est assez blanche
					if (w/h >0.2 && w/h < 0.60  && image.at<cv::Vec3b>(cy,cx).val[1]>100)
					{
						// Si la region trouvee est plus grande que oBestRegion,
						// oBestRegion est maintgenant egal a cette region
						if(bboxes[i].height*bboxes[i].width > oBestRegion.height*oBestRegion.width){
							oBestRegion=bboxes[i];
						}
					}

				}


				if(oBestRegion.width>0){
					Vision::m_nCentreX= oBestRegion.x+oBestRegion.width/2;
					Vision::m_nCentreY= oBestRegion.y+oBestRegion.height/2;
					Vision::m_nHauteur= oBestRegion.height;
					Vision::m_nLargeur= oBestRegion.width;
					cv::rectangle(image,oBestRegion,cv::Scalar(0,255,0));
					std::cout << "target found at "<< Vision::m_nCentreX << " " << Vision::m_nCentreY << std::endl;

				} else std::cout << "Target not found" << std::endl;

				cv::imwrite(str,image);
			}
			Vision::m_bStart=false;
			Vision::m_bDone=true;
		}

		sleep(10);

		//outputStreamStd.PutFrame(output);
	}


}


