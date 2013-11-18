#include "warping.h"

#include <iostream>
using namespace std;
/**
 * @function find_crosses
 * @brief
 * @arg
 *		
 */
bool find_crosses( cv::Mat& full_image, cv::Mat& cross_image, cv::Point& cross_up, cv::Point& cross_down ){

	double result_warping_up, result_warping_down ;

	/* configure a mask for the top_image and the bottom_image, split in middle */
	Rect roi_middle_up = Rect( 0, 0, full_image.size().width, full_image.size().height/2 );
	Rect roi_middle_down = Rect( 0, full_image.size().height/2, full_image.size().width, full_image.size().height/2 );

	/* apply a mask, to split image into 2 parts*/
	Mat full_image_usable_up = full_image(roi_middle_up);
	Mat full_image_usable_down = full_image(roi_middle_down);

	result_warping_up = MatchingMethod( full_image_usable_up, cross_image, cross_up );
	printf("Coordonnees 1ere croix :\n x : %d\n y : %d\nmatch : %lf\n", cross_up.x, cross_up.y,result_warping_up);
	
	result_warping_down = MatchingMethod( full_image_usable_down, cross_image, cross_down );
//	printf("\nCoordonnees 2eme croix :\n x : %d\n y : %d\nmatch : %lf\n", cross_down.x, cross_down.y,result_warping);
	cross_down.y += full_image.size().height/2 ;
	printf("\nCoordonnees 2eme croix (img complete) :\n x : %d\n y : %d\nmatch : %lf\n", cross_down.x, cross_down.y,result_warping_down);

	bool result = true;
	if(result_warping_down < 0.5){
		cout << "\nmatch de la croix du bas insuffisante\n" << endl;
		result = false;
	}
	if(result_warping_up < 0.5){
		cout << "\nmatch de la croix du haut insuffisante\n" << endl;
		result = false;
	}
	return result;
}

