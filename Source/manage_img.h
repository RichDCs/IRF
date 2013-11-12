#ifndef MAN_H
#define MAN_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include <cv.h>
using namespace cv;

#include "warping.h"

#define MATCH_IMG 0
#define MATCH_TXT 1


struct database_picto{
	string path;
	string description;
	/*other caract ?*/
};

void extractImage(Mat& src, Mat& dst, int x1, int y1, int x2, int y2);
void saveImage(Mat& src, string name);
int match_img(Mat& img_extract, int type_base);

#endif