//4,随机抽样验证
#ifndef RANSIC_TEST_H
#define RANSIC_TEST_H

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/legacy/legacy.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "UcvImageMatch.h"
#include "UcvImageFeature.h"
#include "SurfFeature.h"
#include "KnnImageMatch.h"
#include "RatioTest.h"
#include "symmetryTest.h"

using namespace std;
using namespace cv;

class RansicTest:
{
protected:
	std::vector<cv::DMatch>& outMatches ;
	bool refineF; // if true will refine the F matrix
	double distance; // min distance to epipolar
	double confidence; // confidence level (probability)

public:
	// Identify good matches using RANSAC
	// Return fundemental matrix
	cv::Mat ransacTest(const std::vector<cv::DMatch>& matches,
		const std::vector<cv::KeyPoint>& keypoints1, 
		const std::vector<cv::KeyPoint>& keypoints2,
		std::vector<cv::DMatch>& outMatches) 
	{

		// Compute F matrix using RANSAC
		std::vector<uchar> inliers(uif_src.keyPointsPose.size(),0);
		cv::Mat fundemental= cv::findFundamentalMat(
			cv::Mat(uif_src.keyPointsPose),cv::Mat(uif_match.keyPointsPose), // matching points
			inliers,      // match status (inlier ou outlier)  
			CV_FM_RANSAC, // RANSAC method
			distance,     // distance to epipolar line
			confidence);  // confidence probability

		// extract the surviving (inliers) matches
		std::vector<uchar>::const_iterator itIn= inliers.begin();
		std::vector<cv::DMatch>::const_iterator itM= matches.begin();
		// for all matches
		for ( ;itIn!= inliers.end(); ++itIn, ++itM) 
		{
			if (*itIn)
			{ 
				// it is a valid match
				outMatches.push_back(*itM);
			}
		}
	}
		Mat reComputeF()
		{
			if (refineF) 
			{
				// The F matrix will be recomputed with all accepted matches

				// Convert keypoints into Point2f for final F computation	
				points1.clear();
				points2.clear();

				for (std::vector<cv::DMatch>::const_iterator it= outMatches.begin();
					it!= outMatches.end(); ++it)
				{
					// Get the position of left keypoints
					float x= keypoints1[it->queryIdx].pt.x;
					float y= keypoints1[it->queryIdx].pt.y;
					points1.push_back(cv::Point2f(x,y));
					// Get the position of right keypoints
					x= keypoints2[it->trainIdx].pt.x;
					y= keypoints2[it->trainIdx].pt.y;
					points2.push_back(cv::Point2f(x,y));
				}

				// Compute 8-point F from all accepted matches
				fundemental= cv::findFundamentalMat(
					cv::Mat(points1),cv::Mat(points2), // matching points
					CV_FM_8POINT); // 8-point method
			}
			return fundemental;
	};
#endif;