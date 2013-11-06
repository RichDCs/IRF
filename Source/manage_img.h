#ifndef MAN_H
#define MAN_H

#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;

void extractImage(Mat& src, Mat& dst, int x1, int y1, int x2, int y2);
void saveImage(Mat& src, string name);


#endif