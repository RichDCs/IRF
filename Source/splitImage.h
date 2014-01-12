#ifndef SPLITIMAGE_H
#define SPLITIMAGE_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "cv.h"
using namespace cv;

/* Split une image en 7 zones (2x3x2) */
Mat splitImageIn7(Mat src, int choix);

#endif