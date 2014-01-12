#include "splitImage.h"
#include <iostream>
using namespace std;

Mat splitImageIn7(Mat src,int choix){
	Mat zone;
	double three_row = src.size().width/3;
	double two_row = src.size().width/2;
	double line = src.size().height/3;
	Rect region_of_interest;
	switch(choix){
		case 1:
			region_of_interest = Rect(0, 0, two_row, line);
			zone = src(region_of_interest);
			break;
		case 2:
			region_of_interest = Rect(two_row,0,two_row,line);
			zone = src(region_of_interest);
			break;
		case 3:
			region_of_interest = Rect(0,line,three_row,line);
			zone = src(region_of_interest);
			break;
		case 4:
			region_of_interest = Rect(three_row,line,three_row,line);
			zone = src(region_of_interest);
			break;
		case 5:
			region_of_interest = Rect(three_row*2,line,three_row,line);
			zone = src(region_of_interest);
			break;
		case 6:
			region_of_interest = Rect(0,line*2,two_row,line);
			zone = src(region_of_interest);
			break;
		case 7:
			region_of_interest = Rect(two_row,line*2,two_row,line);
			zone = src(region_of_interest);
			break;
		default:
			cout << "erreur de zones";
	}
	return zone;
}