
#include "manage_img.h"

void extractImage(Mat& src, Mat& dst, int x1, int y1, int x2, int y2)
{
	Mat image;
	Rect region_of_interest = Rect(x1, y1, x2-x1, y2-y1);
	dst = src(region_of_interest);
}

void saveImage(Mat& src, string name){
	;
}
