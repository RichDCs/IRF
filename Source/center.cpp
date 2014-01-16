#include "center.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "cv.h"
using namespace cv;
#include "cut_down.h"
#include "splitImage.h"
	
Center::Center(string nameCaract){
	name = nameCaract;
	CaracteristicsPoint();
}

void Center::setCaractValues(map<string,vector<string>> pathFiles){
	cout << "gravity center" << endl;
	for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
		string pictoName = it->first;
		vector<string> pathsForAPicto = it->second;
		vector<double> tempX;
		vector<double> tempY;
		for(int i=0;i<pathsForAPicto.size();i++){	
			/// Load source image
			Mat src = imread(pathsForAPicto[i], 1 );
			src = normalize_img(src);
			Point point = calcul_center(src);
			tempX.push_back(point.x);
			tempY.push_back(point.y);
		}
		pointX.insertCaractValues(pictoName,tempX);
		pointY.insertCaractValues(pictoName,tempY);
	}
}
	
void Center::setZonesValues(map<string,vector<string>> pathFiles){
	cout << "gravity center" << endl;
	// On effectue les calculs sur une zone à la fois
	for(int zone=1;zone<=7;zone++){
		// On efface les données qui étaient dans la map des caractéristiques avant d'y écrire
		pointX.clearCaractValues();
		pointY.clearCaractValues();

		for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
			string pictoName = it->first;
			vector<string> pathsForAPicto = it->second;
			vector<double> tempX;
			vector<double> tempY;
			for(int i=0;i<pathsForAPicto.size();i++){	
				/// Load source image
				Mat src = imread(pathsForAPicto[i], 1 );
				src = cut_down(src);
				// On splitte l'image en plusieurs images
				Mat image_zone = splitImageIn7(src,zone);
				Point point = calcul_center(image_zone);
				tempX.push_back(point.x);
				tempY.push_back(point.y);
			}
			pointX.insertCaractValues(pictoName,tempX);
			pointY.insertCaractValues(pictoName,tempY);
			tempX.clear();
			tempY.clear();
		}
		pointX.insertZonesCaractValues(zone,pointX.getCaractValues());
		pointY.insertZonesCaractValues(zone,pointY.getCaractValues());
	}
}

Mat Center::normalize_img(Mat src){
	return cut_down(src);
}

Point Center::calcul_center(Mat src){
	Vec3b intensity;
	int sumX = 0;
	int sumY = 0;
	int nbPixel = 0;
	float blue,green,red;
	for(int j=0;j<src.rows;j++){
		for(int i=0; i<src.cols; i++){
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
			// c'est le centre de gravité des pixels non blancs
			// attention parce que si on se base sur les pixels blancs c'est peut être mieux 
			// car dans le cas d'une image vide, le centre de gravité sera au milieu de l'image
			// ici il sera en haut à gauche
			if(red>=200 || green>=200 || blue>=200){
				sumX += i;
				sumY += j;
				nbPixel++;
			}
		}
	}
	double centre_gravity_x = 0;
	double centre_gravity_y = 0;
	if (nbPixel != 0) {
		centre_gravity_x = (sumX*100)/(nbPixel*src.cols);
		centre_gravity_y = (sumY*100)/(nbPixel*src.rows);
	}
	return Point(centre_gravity_x,centre_gravity_y);
}