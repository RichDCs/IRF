#ifndef WARPING_H

	#include "cv.h"
	#include "highgui.h"
	using namespace cv;

	void rotateE(cv::Mat& src, double angle, cv::Mat& dst);
	void MatchingMethod( cv::Mat& full_image, cv::Mat& template_image, cv::Point& origin_template );

#endif