// UcvImageMatch.h
#ifndef UCV_IMAGE_MATCH_H
#define UCV_IMAGE_MATCH_H

#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/opencv.hpp>
#include "UcvImageFeature.h"

using namespace cv;

class UcvImageMatch
{
public:
	UcvImageFeature uif_src ;
	UcvImageFeature uif_match ;
	vector<vector<DMatch>> matches1 ;
	vector<vector<DMatch>> matches2 ;

public:
	virtual void init(const UcvImageFeature uifSrc, const UcvImageFeature uifMatch){}
	virtual void knnMatch( ){}
	virtual void radiusMatch( ){}
	virtual vector<vector<DMatch>> getMatches1(){return matches1;}
	virtual vector<vector<DMatch>> getMatches2(){return matches2;}
	virtual Mat getKnnMatchImage1(){return Mat();}
	virtual Mat getKnnMatchImage2(){return Mat();}
	virtual Mat getRadiusMatchImage1(){return Mat();}
	virtual Mat getRadiusMatchImage2(){return Mat();}
};

#endif