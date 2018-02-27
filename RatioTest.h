//2,±»¬ …∏—°
#ifndef RATIO_TEST_H
#define RATIO_TEST_H

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

using namespace std;
using namespace cv;

class RatioTest:  public UcvImageMatch
{
public:
	float ratio; // max ratio between 1st and 2nd NN
	float setRatio(const float r)
	{
		ratio= r;
	}
	int ratioTest(const vector<vector<DMatch>>  matches)
	{

		int removed=0;

		// for all matches
		for (std::vector<std::vector<cv::DMatch>>::iterator matchIterator= matches.begin();
			matchIterator!= matches.end(); ++matchIterator) 
		{

			// if 2 NN has been identified
			if (matchIterator->size() > 1) 
			{

				// check distance ratio
				if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio) 
				{

					matchIterator->clear(); // remove match
					removed++;
				}

			} 
			else
			{ // does not have 2 neighbours

				matchIterator->clear(); // remove match
				removed++;
			}
		}
		return removed;
	}
};
#endif;