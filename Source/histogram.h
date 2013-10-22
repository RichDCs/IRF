#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <iostream>
using namespace std;

#include <cv.h>
#include <highgui.h>
using namespace cv;

/*
* Compute and show histogram of a gray OR color BGR image
*/
void computeHistogram(string histTitle, Mat img);


#endif /* HISTOGRAM_H_ */