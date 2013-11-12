#ifndef CAN_H
#define CAN_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;

#define FIRST_VERTICAL_COL 0
#define FIRST_VERTICAL_LINE 0

#define LAST_VERTICAL_COL 13	//==parcours de l'image selon le x
#define LAST_VERTICAL_LINE 15	//==parcours de l'image selon le y

typedef struct can_pt can_pt ;
struct can_pt{
	unsigned int x[LAST_VERTICAL_COL +1];
	unsigned int y[LAST_VERTICAL_LINE +1];
};

void create_caneva(cv::Mat& full_image, cv::Point& cross_up, cv::Point& cross_down);
void show_caneva(cv::Mat& full_image);


#endif