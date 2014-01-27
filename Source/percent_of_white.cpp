#include "percent_of_white.h"	
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;
#include "splitImage.h"


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
			/// Load source image
			Mat src = imread(pathsForAPicto[i], 1 );
			//src = normalize_img(src);
			temp.push_back(calcul_percent_of_white(src));
		}
		caractValues.insert(itValues,pair<string,vector<double>>(pictoName,temp));
	}
}

void PercentOfWhite::setZonesValues(map<string,vector<string>> pathFiles){
	cout << "percent of white" << endl;
	// Iterateur pour remplir la map des zones
	map<int,map<string,vector<double>>>::iterator itZones = zonesValues.begin();
		
	// On effectue les calculs sur une zone à la fois
	for(int zone=1;zone<=7;zone++){
		// Iterateur pour remplir la map des caracteristiques
		caractValues.clear();
		map<string,vector<double>>::iterator itValues = caractValues.begin();
		for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
			string pictoName = it->first;
			vector<string> pathsForAPicto = it->second;
			vector<double> temp;
			for(int i=0;i<pathsForAPicto.size();i++){	
				/// Load source image
				Mat src = imread(pathsForAPicto[i], 1 );
				//src = cut_down(src);
				// On splitte l'image en plusieurs images
				Mat image_zone = splitImageIn7(src,zone);
				temp.push_back(calcul_percent_of_white(image_zone));
			}
			caractValues.insert(itValues,pair<string,vector<double>>(pictoName,temp));
			temp.clear();
		}
		zonesValues.insert(itZones,pair<int,map<string,vector<double>>>(zone,caractValues));	
	}
}

// Normalise l'image en la rognant
Mat PercentOfWhite::normalize_img(Mat src){
	// On normalise d'abord l'image
	return src;
	//return cut_down(src);
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
			if(red>=200 && green>=200 && blue>=200){
				compteur++;
			}
		}
	}
	int numberOfPixel = src.cols*src.rows;
	double result = 100.0*compteur/numberOfPixel;
	return result;
}