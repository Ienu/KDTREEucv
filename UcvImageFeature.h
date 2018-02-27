// UcvImageFeature
#ifndef UCV_IMAGE_FEATURE_H
#define UCV_IMAGE_FEATURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

class UcvImageFeature
{
public:
	Mat image;
	vector<KeyPoint> keyPoints;
	Mat descriptors;

public:
	virtual void init(const Mat im){}
	virtual void computeFeature(){}
	//virtual void saveFeature(const char* filePath){}
	//virtual void readFeature(const char* filePath){}

    virtual Mat getImage()const{return image;}
    virtual Mat getFeatureImage(){return image;}
    virtual Mat getDescriptors()const{return descriptors;}
    virtual vector<KeyPoint> getKeyPoint()const{return keyPoints;}
};

#endif