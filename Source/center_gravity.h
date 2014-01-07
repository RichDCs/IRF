#ifndef CENTERGRAVITY_H
#define CENTERGRAVITY_H

#include <cv.h>
#include <highgui.h>
using namespace cv;
#include <iostream>
#include <string>
using namespace std;
#include <Windows.h>

class CenterGravity {
private:
	int threshold;
public:
	CenterGravity(void);
	virtual ~CenterGravity(void);
	Mat remove_edges(Mat image_path, int threshold);
	Mat read_image_grayscale(string image_path);
	void calculate_CenterGravity(string path);
};

#endif

