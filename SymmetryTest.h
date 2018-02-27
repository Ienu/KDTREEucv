//3,∂‘≥∆–‘…∏—°
#ifndef SYMMETRY_TEST_H
#define SYMMETRY_TEST_H

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


using namespace std;
using namespace cv;
class SymmetryTest:
{
public:
// Insert symmetrical matches in symMatches vector
	  void symmetryTest(const std::vector<std::vector<cv::DMatch>>& matches1,
		                const std::vector<std::vector<cv::DMatch>>& matches2,
					    std::vector<cv::DMatch>& symMatches) {
			
		// for all matches image 1 -> image 2
		for (std::vector<std::vector<cv::DMatch>>::const_iterator matchIterator1= matches1.begin();
			 matchIterator1!= matches1.end(); ++matchIterator1) {

			if (matchIterator1->size() < 2) // ignore deleted matches 
				continue;

			// for all matches image 2 -> image 1
			for (std::vector<std::vector<cv::DMatch>>::const_iterator matchIterator2= matches2.begin();
				matchIterator2!= matches2.end(); ++matchIterator2) {

				if (matchIterator2->size() < 2) // ignore deleted matches 
					continue;

				// Match symmetry test
				if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx  && 
					(*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx) {

						// add symmetrical match
						symMatches.push_back(cv::DMatch((*matchIterator1)[0].queryIdx,
									  				    (*matchIterator1)[0].trainIdx,
													    (*matchIterator1)[0].distance));
						break; // next match in image 1 -> image 2
				}
			}
		}
	  }
};
#endif;