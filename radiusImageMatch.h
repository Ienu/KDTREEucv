//1，radius匹配
#ifndef RADIUS_IMAGE_MATCH_H
#define RADIUS_IMAGE_MATCH_H

#include <vector>
#include<opencv2/legacy/legacy.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "UcvImageMatch.h"
#include "UcvImageFeature.h"
#include "SurfFeature.h"

using namespace cv;
using namespace std;

class RadiusImageMatch: public UcvImageMatch
{
	public:
		void init( UcvImageFeature &uifSrc,  UcvImageFeature &uifMatch)
	    {
			uifSrc.getImage().copyTo(uif_src.image);
			uif_src.descriptors = uifSrc.getDescriptors();
			uif_src.keyPoints = uifSrc.getKeyPoint();

			uifMatch.getImage().copyTo(uif_match.image);
			uif_match.descriptors = uifMatch.getDescriptors();
			uif_match.keyPoints = uifMatch.getKeyPoint();
		
	    }

		void radiusMatch()
		{
			cv::BFMatcher matcher(NORM_L2,true);//针对surf,sift特征，float型数据,试验orb也行
	        //cv::BFMatcher matcher(NORM_HAMMING,true);//针对orb和brief特征，uchar型数据

			matcher.radiusMatch(uif_src.descriptors,uif_match.descriptors, matches1, 150);//0.2是半径，距离小于该长度则认为是匹配点
			matcher.radiusMatch(uif_match.descriptors,uif_src.descriptors, matches2, 150);
		}

		vector<vector<DMatch>> getMatches1(){return matches1;}
		vector<vector<DMatch>> getMatches2(){return matches2;}

		Mat getRadiusMatchImage1()
		{
			Mat imageMatches1;
	        drawMatches(uif_src.image,uif_src.keyPoints,  // 1st image and its keypoints
			uif_match.image,uif_match.keyPoints,  // 2nd image and its keypoints
			matches1,			// the matches
			imageMatches1,		// the image produced
			Scalar(255,255,255)); // color of the lines
		   // namedWindow("Matches1");
		    //imshow("Matches1",imageMatches1);
			//waitKey(0);
			return (imageMatches1);
		}
        Mat getRadiusMatchImage2()
		{
			cv::Mat imageMatches2;
	        cv::drawMatches(uif_match.image,uif_match.keyPoints,  // 1st image and its keypoints
			uif_src.image,uif_src.keyPoints,  // 2nd image and its keypoints
			matches2,			// the matches
			imageMatches2,		// the image produced
			Scalar(255,255,255)); // color of the lines
		   // namedWindow("Matches2");
		   // imshow("Matches2",imageMatches2);
			//waitKey(0);
			return (imageMatches2);
		 }
		

};

#endif;