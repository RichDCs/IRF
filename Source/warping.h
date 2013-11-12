#ifndef WARPING_H
#define WARPING_H
#define _CRT_SECURE_NO_WARNINGS

	#include "cv.h"
	#include "highgui.h"
	using namespace cv;

	#include <math.h>
	#define M_PI 3.14159265358979323846264338327

	#define ANGLE_REFERENCE (double)54.88302

	void rotateE(cv::Mat& src, double angle, cv::Mat& dst);
	double MatchingMethod( cv::Mat& full_image, cv::Mat& template_image, cv::Point& origin_template );
	double compute_warping(cv::Mat& image_test, cv::Mat& image_reference);
	void find_crosses( cv::Mat& full_image, cv::Mat& cross_image, cv::Point& cross_up, cv::Point& cross_down );

#endif