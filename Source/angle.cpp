#include "angle.h"	
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;
#include "splitImage.h"
#include <math.h>


Angle::Angle(string nameCaract){
	Caracteristics();
	name = nameCaract;
}

void Angle::setCaractValues(map<string,vector<string>> pathFiles){
	cout << "diagonale" << endl;
	// Iterateur pour remplir la map des caracteristiques
	map<string,vector<double>>::iterator itValues = caractValues.begin();
	for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
		string pictoName = it->first;
		vector<string> pathsForAPicto = it->second;
		vector<double> temp;
		for(int i=0;i<pathsForAPicto.size();i++){	
			/// Load source image
			Mat src = imread(pathsForAPicto[i], 1 );
			//src = normalize_img(src);
			temp.push_back(calcul_angle(src));
		}
		caractValues.insert(itValues,pair<string,vector<double>>(pictoName,temp));
	}
}

// Normalise l'image en la rognant
Mat Angle::normalize_img(Mat src){
	// On normalise d'abord l'image
	return src;
	//return cut_down(src);
}

// Calcul le pourcentage de blanc
double Angle::calcul_angle(Mat src){
	int hauteur = src.rows;
	int longueur = src.cols;
	double result = sqrt((pow(hauteur,2.0)+pow(longueur,2.0)));
	// normalisation du resultat (avec la hauteur de l'image)
	result = 100*result/hauteur;
	return result;
}