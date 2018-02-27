//SURF_FEATURE_DETECT_AND_DESCRIPTION_H
#ifndef SIFT_FEATURE_DETECT_AND_DESCRIPTION_H
#define SIFT_FEATURE_DETECT_AND_DESCRIPTION_H
#include "UcvImageFeature.h"
#include <cassert>


class SiftFeature : public UcvImageFeature
{
public: 
	void init(const Mat im)
	{
		assert( !im.empty() ); //check the program
		image = im;
	}

	void computeFeature()
	{
		Ptr<FeatureDetector> sift_detector = new SIFT();
		sift_detector->detect(image, keyPoints);

		Ptr<DescriptorExtractor> sift_descriptor = sift_detector;
		sift_descriptor->compute(image, keyPoints, descriptors);
		
		
	}// compute the feature

	void saveFeature(const char* filePath) //save the keyponits and description as xml files
	{
		int keySize = (int)keyPoints.size();

		FileStorage fs( filePath, FileStorage::WRITE);
		fs << "KeyPointsNum" << keySize;

		for(int i = 0; i < keySize; i++)
		{
			fs << "KeyPoint";
			fs << "{";
			fs << "Num" << (i + 1);
		    fs << "x" << keyPoints[i].pt.x; 
		    fs << "y" << keyPoints[i].pt.y;
			fs << "}";
		}
		fs << "Description" << descriptors;
		fs.release();
	}

	void readFeature(const char* filePath){}
	Mat getImage(){return image;}
	Mat getFeatureImage()
	{
		Mat result;
		cv::drawKeypoints(
			image,
			keyPoints,
			result,
			Scalar(255, 255, 255),
		    cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS
			);
	
		
		return result;
	}

	Mat getDescriptors(){return descriptors;}

	vector<KeyPoint> getKeyPoint(){return keyPoints;}

};
#endif