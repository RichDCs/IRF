#include "percent_of_white.h"	
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
#include "cv.h"
using namespace cv;

bool check_percent_of_white(Mat src){
	bool vide = false;
	Vec3b intensity;
	int compteur = 0;
	float blue,green,red;
	for(int j=0;j<src.rows;j++){
		for(int i=0; i<src.cols; i++){
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
			if(red>=200 && green>=200 && blue>=200){
				compteur++;
			}
		}
	}
	int numberOfPixel = src.cols*src.rows;
	double result = 100.0*compteur/numberOfPixel;
	if(result >= 99.9){
		vide = true;
	}
	return vide;
}