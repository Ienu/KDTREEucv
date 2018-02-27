//1，knn匹配
#ifndef KNN_IMAGE_MATCH_H
#define KNN_IMAGE_MATCH_H

#include <vector>
#include<opencv2/legacy/legacy.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "UcvImageMatch.h"
#include "UcvImageFeature.h"
#include "SurfFeature.h"

using namespace cv;
using namespace std;

class KnnImageMatch: public UcvImageMatch
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

		void knnMatch( )
		{
			// Construction of the matcher 
		    cv::BFMatcher matcher(NORM_L2,true);//针对surf,sift特征，float型数据，试验orb也行
	        //cv::BFMatcher matcher(NORM_HAMMING,true);//针对orb和brief特征，uchar型数据
			//matcher.match(uif_src.descriptors,uif_match.descriptors, matches2);
			// from image 1 to image 2
			
		    //src查询，是被匹配的图，match是要匹配的图
			matcher.knnMatch( uif_src.descriptors, uif_match.descriptors, matches1, 1);

		   // from image 2 to image 1
		    matcher.knnMatch(uif_match.descriptors,uif_src.descriptors, 
			matches2, // vector of matches (up to 2 per entry) 
			1);		  // return 2 nearest neighbours
 
		}
	/*
		void match()
		{
			cv::BFMatcher matcher(NORM_L2,true);
		
			matcher.match(uif_src.descriptors,uif_match.descriptors, matches1);
		}
*/
		vector<vector<DMatch>> getMatches1(){return matches1;}
		vector<vector<DMatch>> getMatches2(){return matches2;}

		Mat getKnnMatchImage1()
		{
			Mat imageMatches1;
	        drawMatches(uif_src.image,uif_src.keyPoints,  // 1st image and its keypoints
			uif_match.image,uif_match.keyPoints,  // 2nd image and its keypoints
			matches1,			// the matches
			imageMatches1,		// the image produced
			Scalar(255,255,255)); // color of the lines
		//    namedWindow("Matches1");
		//    imshow("Matches1",imageMatches1);
		//	waitKey(0);
			return (imageMatches1);
		}
        Mat getKnnMatchImage2()
		{
			cv::Mat imageMatches2;
	        cv::drawMatches(uif_match.image,uif_match.keyPoints,  // 1st image and its keypoints
			uif_src.image,uif_src.keyPoints,  // 2nd image and its keypoints
			matches2,			// the matches
			imageMatches2,		// the image produced
			Scalar(255,255,255)); // color of the lines
		//    namedWindow("Matches2");
		 //   imshow("Matches2",imageMatches2);
		//	waitKey(0);
			return (imageMatches2);
		 }
		

};

#endif;