#include "cv.h"
#include "highgui.h"
using namespace cv;
#include <iostream>
#include <string>
using namespace std;
#include "center_gravity.h"

int main(void) {
	CenterGravity c1 = CenterGravity();

	c1.calculate_CenterGravity("C:/Users/Bamako/Documents/GitHub/IRF/Mini_base_test/s01_0001.png");
}