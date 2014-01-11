#include "cut_down.h"

#include <map>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "cv.h"
using namespace cv;

// POur vérifier que ça rogne correctement les images
void cut_down_all(map<string,vector<string>> pathFiles){
	// Iterateur pour remplir la map des caracteristique
	for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
		string pictoName = it->first;
		vector<string> pathsForAPicto = it->second;
		vector<double> temp;
		for(int i=0;i<pathsForAPicto.size();i++){	
			/// Load source image and convert it to gray
			Mat src = imread(pathsForAPicto[i], 1 );
			src = cut_down(src);
			imwrite("resultat/"+pathsForAPicto[i],src);
		}
	}
}

Mat cut_down(Mat src){
	// 200 semble le bon seuil
	Vec3b intensity;
	float blue,green,red;
	// Rogner en haut
	int haut = 0;
	bool trouve = false;
	for(int j=0;j<src.rows && !trouve;j++){
		for(int i=0; i<src.cols && !trouve; i++){
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
			if(red<200 || green<200 || blue<200){
			   trouve = true;
			}
		}
		if(!trouve){
			haut++;
		}
	}

	// Rogner en bas
	int bas = 0;
	trouve = false;
	for(int j=src.rows-1;j>=0 && !trouve;j--){
		for(int i=0; i<src.cols && !trouve; i++){
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
		   if(red<200 || green<200 || blue<200){
			   trouve = true;
		   }
		}
		if(!trouve){
			bas++;
		}
	}

	// Rogner à gauche
	int gauche = 0;
	trouve = false;
	for(int i=0; i<src.cols && !trouve; i++){
		for(int j=0;j<src.rows && !trouve;j++){
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
		   if(red<200 || green<200 || blue<200){
			   trouve = true;
		   }
		}
		if(!trouve){
			gauche++;
		}
	}

	// Rogner à droite
	int droite = 0;
	trouve = false;
	for(int i=src.cols-1; i>=0 && !trouve; i--){
		for(int j=0; j<src.rows && !trouve;j++){	
			intensity = src.at<Vec3b>(j, i);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
		   if(red<200 || green<200 || blue<200){
			   trouve = true;
		   }
		}
		if(!trouve){
			droite++;
		}
	}
	
	int newWidth = src.cols-droite-gauche;
	int newHeight = src.rows-bas-haut;
	Mat out;
	Rect region_of_interest = Rect(gauche,haut,newWidth,newHeight);
	out = src(region_of_interest);
	return out;
}
