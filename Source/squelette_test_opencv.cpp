//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-iNFO
// Projet, séance 1
// thème : premier pas en OpenCV
// contenu : charge, affiche, réduction, calcul et affichage d'histogramme
// auteur : Luce Morin
// date : 4/10/2010
//////////////////////////////////////////////////////////////////////////

#include "histogram.h"

#include "cv.h"
#include "highgui.h"
using namespace cv;

#include <iostream>
using namespace std;


int main (void) {

	//charge et affiche l'image 
	string imName = "00000.png";
	//string imName = "arc.jpg";
	Mat im = imread(imName);
	Mat imout;
	if(im.data == NULL){
		cerr << "Image not found: "<< imName << endl;
		exit(0);
	}
	imshow("exemple1", im);

	//applique une reduction de taille d'un facteur 5
	//ici modifier pour ne reduire qu'a l'affichage 
	//comme demande dans l'enonce
	int reduction = 5;
	Size tailleReduite(im.cols/reduction, im.rows/reduction);
	Mat imreduite = Mat(tailleReduite,CV_8UC3); //cree une image à 3 canaux de profondeur 8 bits chacuns
	resize(im,imreduite,tailleReduite);
	imshow("image reduite", imreduite);
	
	vector<Mat> rgb;
	split(im,rgb);
	imshow("r", rgb[0]);
	imshow("g", rgb[1]);
	imshow("b", rgb[2]);

	cvtColor(im, imout, CV_BGR2HSV);
	imshow("out", imout);
	vector<Mat> hsv;
	split(imout, hsv);
	imshow("h", hsv[0]);
	imshow("s", hsv[1]);
	imshow("v", hsv[2]);

	Mat imout2;
	cvtColor(imreduite, imout2, CV_BGR2GRAY);
	threshold(imout2, imout2, 245, 255, 0);
	imshow("out2", imout2);

	IplImage *img = cvLoadImage("00000.png",1);
	IplImage *img_dest;

	CvRect ROI = cvRect(0, 0, 2000, 2000);
	img_dest = cvCreateImage(cvSize(ROI.width, ROI.height), IPL_DEPTH_8U, 3);
	cvSetImageROI(img, ROI);
	cvShowImage("ROI", img_dest);

	computeHistogram("histogramme", im);

	//termine le programme lorsqu'une touche est frappee
	waitKey(0);
}
