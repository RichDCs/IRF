#ifndef CENTER_H
#define CENTER_H

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include "cv.h"
#include "CaracteristicsPoint.h"
using namespace cv;

// Moment h�rite de Caracteristics
class Center:public CaracteristicsPoint{
public:
	// Constructeur
	Center(string nameCaract);
	virtual void setCaractValues(map<string,vector<string>> pathFiles);
	virtual void setZonesValues(map<string,vector<string>> pathFiles);
private:
	// Normalise l'image en la rognant
	Mat normalize_img(Mat src);
	// Calcul du centre de gravit� de l'image
	Point calcul_center(Mat src);
};

#endif