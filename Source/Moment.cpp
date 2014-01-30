#include "Moment.h"
#include "Caracteristics.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;

#include <math.h>


Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
vector<double> moment;
string optionCaract;

// Constructeur
Moment::Moment(string nameCaract, string option){
	Caracteristics();
	optionCaract = option;
	name = nameCaract;	
}

void thresh_callback(int,void*){
	moment.clear();
	Mat canny_output = src_gray;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
//	Canny( src_gray, canny_output, thresh, thresh*2, 3 );
	//imshow("canny",canny_output);
	/// Find contours
	findContours( src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/*for(int i=0;i<contours.size();i++){
		 cout << endl;
		 cout << "vector number " << i  << endl;
		 for(int j=0;j<contours[i].size();j++){
		  cout << contours[i][j].x << ";" << contours[i][j].y << endl;
		 }
	 }*/

	 /// Get the moments
	
	 vector<Moments> mu(contours.size() );
	 if(contours.size()>=1){
		mu[0] = moments( contours[0], false );
		double normalize = mu[0].m00;
		//cout << "caract " << i << "\n\n";
		//if(optionCaract=="m00")
			//moment.push_back(mu[i].m00*100/normalize);
		if(optionCaract=="m01")
			moment.push_back(mu[0].m01/normalize);
		else if(optionCaract=="m02")
			moment.push_back(mu[0].m02/normalize);
		else if(optionCaract=="m03")
			moment.push_back(mu[0].m03/normalize);
		else if(optionCaract=="m10")
			moment.push_back(mu[0].m10/normalize);
		else if(optionCaract=="m11")
			moment.push_back(mu[0].m11/normalize);
		else if(optionCaract=="m12")
			moment.push_back(mu[0].m12/normalize);
		else if(optionCaract=="m20")
			moment.push_back(mu[0].m20/normalize);
		else if(optionCaract=="m21")
			moment.push_back(mu[0].m21/normalize);
		else if(optionCaract=="m30")
			moment.push_back(mu[0].m30/normalize);
		else if(optionCaract=="mu02")
			moment.push_back(mu[0].mu02/normalize);
		else if(optionCaract=="mu03")
			moment.push_back(mu[0].mu03/normalize);
		else if(optionCaract=="mu11")
			moment.push_back(mu[0].mu11/normalize);
		else if(optionCaract=="mu12")
			moment.push_back(mu[0].mu12/normalize);
		else if(optionCaract=="mu20")
			moment.push_back(mu[0].mu21/normalize);
		else if(optionCaract=="mu30")
			moment.push_back(mu[0].mu30/normalize);
	 }else{
		 cout << "Pas de contours" << contours.size()<< endl;
		 moment.push_back(0.0);
	 }
	/* for( int i = 0; i < contours.size(); i++ ) {
		mu[i] = moments( contours[i], false );
		double normalize = mu[i].m00;
		//cout << "caract " << i << "\n\n";
		//if(optionCaract=="m00")
			//moment.push_back(mu[i].m00*100/normalize);
		if(optionCaract=="m01")
			moment.push_back(mu[i].m01/normalize);
		else if(optionCaract=="m02")
			moment.push_back(mu[i].m02/normalize);
		else if(optionCaract=="m03")
			moment.push_back(mu[i].m03/normalize);
		else if(optionCaract=="m10")
			moment.push_back(mu[i].m10/normalize);
		else if(optionCaract=="m11")
			moment.push_back(mu[i].m11/normalize);
		else if(optionCaract=="m12")
			moment.push_back(mu[i].m12/normalize);
		else if(optionCaract=="m20")
			moment.push_back(mu[i].m20/normalize);
		else if(optionCaract=="m21")
			moment.push_back(mu[i].m21/normalize);
		else if(optionCaract=="m30")
			moment.push_back(mu[i].m30/normalize);
		else if(optionCaract=="mu02")
			moment.push_back(mu[i].mu02/normalize);
		else if(optionCaract=="mu03")
			moment.push_back(mu[i].mu03/normalize);
		else if(optionCaract=="mu11")
			moment.push_back(mu[i].mu11/normalize);
		else if(optionCaract=="mu12")
			moment.push_back(mu[i].mu12/normalize);
		else if(optionCaract=="mu20")
			moment.push_back(mu[i].mu21/normalize);
		else if(optionCaract=="mu30")
			moment.push_back(mu[i].mu30/normalize);
	 }
	 */
	 	  ///  Get the mass centers:
	 vector<Point2f> mc( contours.size() );
	 for( int i = 0; i < contours.size(); i++ ){
		 mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); 
		 if(optionCaract == "mc"){
			 double lel = 0;
			 if (mc[i].y != mc[i].y) {
				 cout << mc[i].y << "\n";
				 cout << "HERE LEL" << "\n";
			 }
			 moment.push_back(mc[i].x);
			 moment.push_back(mc[i].y);
		 }
	 }
	 	  /// Draw contours
	 Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	 for( int i = 0; i< contours.size(); i++ ){
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		//circle( drawing, mc[i], 4, color, -1, 8, 0 );
		 char c[3];
		//sprintf(c,"%d",i);
		//imshow( c, drawing );
	 }
	 	  /// Show in a window
	 //namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	 //imwrite("contours.png",drawing);
	 /// Calculate the area with the moments 00 and compare with the result of the OpenCV function
	 //printf("\t Info: Area and Contour Length \n");
	 double moy=0;
	 for(int i = 0; i< contours.size(); i++ ){
		 moy+=mu[i].m00;
		 //if(optionCaract == "m00")
			//moment.push_back(mu[i].m00);
		 if(optionCaract == "contourArea")
			 moment.push_back(contourArea(contours[i]));
		 if(optionCaract == "arclength")
			 moment.push_back(arcLength(contours[i],true));
	   //printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
	  // Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	   //drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
	   //circle( drawing, mc[i], 4, color, -1, 8, 0 );
	 }
	 moy/=contours.size();
	 if(optionCaract == "moy")
		 moment.push_back(moy);
	 if(optionCaract == "nbContours")
		 moment.push_back(contours.size());
}

// Fonctions relatives au moment
void Moment::prepare_img_moment(/*string pathFile*/){
	/// Load source image and convert it to gray
	//src = imread(pathFile, 1 );
	/// Convert image to gray and blur it
	cvtColor( src, src_gray, CV_BGR2GRAY );
	 // imshow("cvtcolor",src_gray);
	blur( src_gray, src_gray, Size(3,3) );

	/// Create Window
	//char* source_window = "Source";
	//namedWindow( source_window, CV_WINDOW_AUTOSIZE );
	//imshow( source_window, src );

	createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
	thresh_callback( 0, 0 );
}

// Initialise la map des valeurs de la carct�ristique
void Moment::setCaractValues(map<string,vector<string>> pathFiles){
	cout << "moment" << endl;
	// Iterateur pour remplir la map des caracteristique
	map<string,vector<double>>::iterator itValues = caractValues.begin();
	for(map<string,vector<string>>::iterator it=pathFiles.begin(); it!=pathFiles.end(); ++it){
		string pictoName = it->first;
		vector<string> pathsForAPicto = it->second;
		vector<double> temp;
		for(int i=0;i<pathsForAPicto.size();i++){		
			src = imread(pathsForAPicto[i]);
			prepare_img_moment();
			temp.insert( temp.end(), moment.begin(), moment.end() );
		}
		caractValues.insert(itValues,pair<string,vector<double>>(pictoName,temp));
	}
}
