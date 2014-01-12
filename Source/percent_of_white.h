#ifndef PERCENTWHITE_H
#define PERCENTWHITE_H

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include "cv.h"
#include "Caracteristics.h"
using namespace cv;

// Moment hérite de Caracteristics
class PercentOfWhite:public Caracteristics{
public:
	// Constructeur
	PercentOfWhite(string nameCaract);
	virtual void setCaractValues(map<string,vector<string>> pathFiles);
	virtual void setZonesValues(map<string,vector<string>> pathFiles);
private:
	// Normalise l'image en la rognant
	Mat normalize_img(Mat src);
	// Calcul le pourcentage de blanc
	double calcul_percent_of_white(Mat src);
};

#endif