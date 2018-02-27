/***************************************
Name: ORBFeature.h
Corpyright(c): ISI Lab
Author: XU Chengguang
E-mail: 1303918938@qq.com
Date: 4/20/2016
Abstract: Define a class of the ORB
          feature. Using to get the 
		  ORB keypoints and description
		  from a input image.
***************************************/
#ifndef ORIENTED_FAST_AND_ROTATED_BRIEF_FEATURE_H
#define ORIENTED_FAST_AND_ROTATED_BRIEF_FEATURE_H
#include "UcvImageFeature.h"
#include <cassert>

class ORBFeature : public UcvImageFeature
{
protected:
	int FeatureNum; //number of the keypoints
public: 
	ORBFeature(int nfeature = 200) : FeatureNum(nfeature){};
    void init(const Mat im) //initailize
	{
		assert( !im.empty() );
		image = im;
	}
	void computeFeature() //compute the ORB feature
	{
		Ptr<FeatureDetector> orb_detector = new ORB(FeatureNum, 1.2, 8);
		orb_detector->detect(image, keyPoints); //detect the ORB keypoints

		Ptr<DescriptorExtractor> orb_descriptor = orb_detector;
		orb_descriptor->compute(image, keyPoints, descriptors); //compute the description
	}
    Mat getImage(){return image;} //return the input image
    Mat getFeatureImage()
	{
		Mat result;
		result = image.clone();
		cv::drawKeypoints(
			image,
			keyPoints,
			result,
		    Scalar(0, 255, 0),
			DrawMatchesFlags::DRAW_RICH_KEYPOINTS
			);
		return result;
	} //return the feature image
    Mat getDescriptors(){return descriptors;} //return the descriptors
    vector<KeyPoint> getKeyPoint(){return keyPoints;} //return the keypoints
};

#endif
