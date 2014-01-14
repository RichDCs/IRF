#ifndef CARACTPOINT_H
#define CARACTPOINT_H

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include "cv.h"
using namespace cv;
#include "caracteristics.h"

class CaracteristicsPoint{
public:
	// Constructeur
	CaracteristicsPoint();
	void writeInAFile(string header,string pathFile);
	void writeIn7File(string header,string pathFile);
protected :
	string name;
	Caracteristics pointX;
	Caracteristics pointY;
};

#endif