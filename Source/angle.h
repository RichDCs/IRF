#ifndef ANGLE_H
#define ANGLE_H

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include "cv.h"
#include "Caracteristics.h"
using namespace cv;

// Moment hérite de Caracteristics
class Angle:public Caracteristics{
public:
	// Constructeur
	Angle(string nameCaract);
	virtual void setCaractValues(map<string,vector<string>> pathFiles);
	//virtual void setZonesValues(map<string,vector<string>> pathFiles);
private:
	// Normalise l'image en la rognant
	Mat normalize_img(Mat src);
	// Calcul le pourcentage de blanc
	double calcul_angle(Mat src);
};

#endif