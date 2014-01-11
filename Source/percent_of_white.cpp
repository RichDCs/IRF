#include "percent_of_white.h"	
#include "cut_down.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;


PercentOfWhite::PercentOfWhite(string nameCaract){
	Caracteristics();
	name = nameCaract;
}

void PercentOfWhite::setCaractValues(map<string,vector<string>> pathFiles){
	cout << "percent of white" << endl;
	// Iterateur pour remplir la map des caracteristiques
	map<string,vector<double>>::iterator itValues = caractValues.begin();
	for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
		string pictoName = it->first;
		vector<string> pathsForAPicto = it->second;
		vector<double> temp;
		for(int i=0;i<pathsForAPicto.size();i++){	
			/// Load source image and convert it to gray
			Mat src = imread(pathsForAPicto[i], 1 );
			temp.push_back(normalize_img(src));
		}
		caractValues.insert(itValues,pair<string,vector<double>>(pictoName,temp));
	}
}

// Normalise l'image en la rognant
double PercentOfWhite::normalize_img(Mat src){
	// On normalise d'abord l'image
	src = cut_down(src);
	// puis appelle de la fonction qui calcule le pourcentage de pixel blanc
	return calcul_percent_of_white(src);
}

// Calcul le pourcentage de blanc
double PercentOfWhite::calcul_percent_of_white(Mat src){
	Vec3b intensity;
	int compteur = 0;
	float blue,green,red;
	for(int j=0;j<src.rows;j++){
		for(int i=0; i<src.cols; i++){
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
			if(red>=240 && green>=240 && blue>=240){
				compteur++;
			}
		}
	}
	int numberOfPixel = src.cols*src.rows;
	double result = (compteur*100/numberOfPixel);
	return result;
}