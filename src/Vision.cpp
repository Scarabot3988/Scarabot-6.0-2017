/*
 * Vision.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: XPS15
 */

#include <Vision.h>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include "wpilib.h"
#define MINRECTSIZE  5000
#define MAXRECTSIZE  20000

static void VisionThread();
bool Vision::m_bStart=false;
bool Vision::m_bDone=false;
int Vision::m_nCentreX=-1;
int Vision::m_nCentreY=-1;
int Vision::m_nHauteur=-1;
int Vision::m_nlargeur=-1;


void Vision::Init()
{
	std::thread visionThread(VisionThread);
			visionThread.detach();

}


float Vision::GetDistance(){
//dist = A - B*sqrt(surface);
	float d;



	return d;
}

float Vision::GetAngle(){
float angle;


return angle;
}


static void VisionThread()
    {
        cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
        camera.SetResolution(640, 480);
        camera.SetBrightness(20);
        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Vision", 640, 480);
        cv::Mat source;
        cv::Mat output;
        while(true) {
        	cvSink.GrabFrame(source);

        	if(Vision::m_bStart){
        		std::cout << "Doing vision" << std::endl;
        		Vision::m_nCentreX= -1;
  				Vision::m_nCentreY= -1;
  				Vision::m_nHauteur= -1;
  				Vision::m_nlargeur= -1;
        		cv::Mat image=source.clone();
//        		cv::MSER ms(5, 5000, 50000);
        		        std::vector<std::vector<cv::Point>> regions;
        		        std::vector<cv::Rect> bboxes;
  //      		        ms(image, regions, cv::Mat());

        		        cv::Ptr< cv::MSER> mser = cv::MSER::create(5,MINRECTSIZE, MAXRECTSIZE);
        		         mser->detectRegions(image, regions, bboxes);

        		         /* opencv 2.4
        		        //std::vector<cv::RotatedRect> filtered_regions;
        		        for (int i = 0; i < regions.size(); i++)
        		        {
    		                cv::RotatedRect rectcandidate = cv::minAreaRect(regions[i]);
    		                double w = rectcandidate.boundingRect().width;
    		                double h = rectcandidate.boundingRect().height;

        		            if (w/h >0.2 && w/h < 0.6)
        		            {
        		            	filtered_regions.push_back(rectcandidate);
        		            }

        		        }*/
        		         std::vector<cv::Rect> filtered_regions;
        		         for (unsigned int i = 0; i < bboxes.size(); i++)
        		         {
							double w = bboxes[i].width;
							double h = bboxes[i].height;

							if (w/h >0.2 && w/h < 0.6)
							{
								filtered_regions.push_back(bboxes[i]);
							}

						}


        		        if(filtered_regions.size()>1){
        		        	bool stop=false;
        		        	for(unsigned int i=0; !stop && i<filtered_regions.size(); i++)
        		        		for(unsigned int j=0; !stop && j<filtered_regions.size(); j++){
        		        			float wi=filtered_regions[i].width;
        		        			float wj=filtered_regions[j].width;
        		        			float hi=filtered_regions[i].height;
        		        			float hj=filtered_regions[j].height;
        		        			if(i!=j && fabs(filtered_regions[i].y - filtered_regions[j].y) < 25 &&
        		        					fabs(wi-wj)/(1+wi) < 0.2 &&
											fabs(hi-hj)/(1+hi) < 0.2){
        		        				cv::Rect r1=filtered_regions[i];
        		        				cv::Rect r2=filtered_regions[j];

        		        				int x1=std::min(r1.x,r2.x);
        		        				int y1=std::min(r1.y,r2.y);
        		        				int x2=std::max(r1.x+r1.width, r2.x+r2.width);
        		        				int y2=std::max(r1.y+r1.height, r2.y+r2.height);
        		        				Vision::m_nCentreX= x1/2+x2/2;
        		        				Vision::m_nCentreY= y1/2+y2/2;
        		        				Vision::m_nHauteur= y2-y1;
        		        				Vision::m_nlargeur= x2-x1;
        		        				cv::rectangle(output,cv::Rect(x1,y1,x2-x1,y2-y1),cv::Scalar(0,255,255));
        		        				stop=true;
        		        			}
        		        	}
        		        } else std::cout << "Targets not found (" << filtered_regions.size() << " regions)" << std::endl;

             	Vision::m_bStart=false;
        		Vision::m_bDone=true;
        	}


        	outputStreamStd.PutFrame(output);


    } // while
}


