
#include <iostream>
#include "ORBFeature.h"
#include "SurfFeature.h"
#include "SIFTFeature.h"
#include "KnnImageMatch.h"
#include "UcvImageMatch.h"
#include "UcvImageFeature.h"
#include "RadiusImageMatch.h"

using namespace std;
using namespace cv;

void main()
{
//	SiftFeature obj1,obj2;
//	SurfFeature obj1, obj2;
	ORBFeature obj1 ,obj2;
	RadiusImageMatch match;
//	KnnImageMatch match;
	vector<vector<DMatch>> matches1,matches2;
	Mat img1,img2, match_1_2, match_2_1;
	/*
	img1=imread("box.png");
	img2=imread("box_in_scene.png");
	*/
	img1=imread("parliament1.bmp");
	img2=imread("parliament2.bmp");

	obj1.init(img1);
	obj2.init(img2);
	obj1.computeFeature();
	obj2.computeFeature();

	match.init(obj1,obj2);
	match.radiusMatch( );//k=1;
	matches1 = match.getMatches1();
	//cout<< matches1 <<endl;
    match_1_2 = match.getRadiusMatchImage1();
	namedWindow("Matches1");
	imshow("Matches1",match_1_2);
	waitKey();
/*
	match.init(obj1,obj2);
	match.knnMatch();
	match_2_1 = match.getKnnMatchImage1();
	namedWindow("Matches2");
	imshow("Matches2",match_2_1);
	waitKey();
	*/
}