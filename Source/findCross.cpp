/*
*	TODO :
*
*
*/

#include "cv.h"
#include "highgui.h"
using namespace cv;

#include <iostream>
using namespace std;

#include <math.h>
#define M_PI 3.14159265358979323846264338327

#include "warping.h"

#define ANGLE_REFERENCE (double)54.88302

/* headers*/
void MatchingMethod( cv::Mat& full_image, cv::Mat& template_image, cv::Point& origin_template );
void rotateE(cv::Mat& src, double angle, cv::Mat& dst);

int main (void) {
	Mat full_image_usable;
    Mat template_usable;
	int reduction_factor = 4;	//depends on your screen size (>Reduction is better for debuging on computer)

	Mat full_image = imread( "img/00000.png", 1 );
	Mat full_image_resized;
	Size size_full_image( full_image.cols/reduction_factor, full_image.rows/reduction_factor);
	resize(full_image, full_image_resized, size_full_image );

	/* configure a mask for the top_image and the bottom_image, split in middle */
	Rect roi_middle_up = Rect( 0, 0, full_image_resized.size().width, full_image_resized.size().height/2 );
	Rect roi_middle_down = Rect( 0, full_image_resized.size().height/2, full_image_resized.size().width, full_image_resized.size().height/2 );

	/* apply a mask, to split image into 2 parts*/
	full_image_usable = full_image_resized;
	Mat full_image_usable_up = full_image_resized(roi_middle_up);
	Mat full_image_usable_down = full_image_resized(roi_middle_down);

	/*********** If you want to add rotation on the source image *******************/
	double angle = 0 ;
	rotateE(full_image_usable, angle, full_image_usable);
	rotateE(full_image_usable_up, angle, full_image_usable_up);
	rotateE(full_image_usable_down, angle, full_image_usable_down);
	/*******************************************************************************/

	/*Load the template (the cross) and apply a reduction */
	Mat template_cross = imread( "img/template.png", 1 );
	Size size_template( template_cross.cols/reduction_factor, template_cross.rows/reduction_factor );
	resize( template_cross, template_usable/*********/, size_template );	

	Point origine_cross_up;
	Point origine_cross_down;

	MatchingMethod( full_image_usable_up, template_usable, origine_cross_up );
	printf("Coordonnees 1ere croix :\n x : %d\n y : %d\n", origine_cross_up.x, origine_cross_up.y);

	MatchingMethod( full_image_usable_down, template_usable, origine_cross_down );
	printf("\n\nCoordonnees 2eme croix :\n x : %d\n y : %d\n", origine_cross_down.x, origine_cross_down.y);
	origine_cross_down.y += full_image_usable.size().height/2 ;
	printf("\n\nCoordonnees 2eme croix (img complete) :\n x : %d\n y : %d\n\n", origine_cross_down.x, origine_cross_down.y);


/*
*		 origine_cross_up
*		/|
*  hyp / |
* ------------
*	 /	 | op
*	/____|
*	^   adj
*	origine_cross_down
*/

	double op = origine_cross_down.y - origine_cross_up.y ;
	double adj = origine_cross_up.x - origine_cross_down.x ;
	double hyp = sqrt( pow(op,2) + pow(adj,2) );

	/* Compute the angle */
	double result_tan, result_cos, result_sin ;
	result_tan = atan( (double)(op) / (adj) ) ;// tan(angle) = op / adj
	printf("resultat angle (tan) : %f degres\n", result_tan * 180 / M_PI );

	result_cos = acos( (double)(adj) / (hyp) ) ;
	printf("resultat angle (cos) : %f degres\n", result_cos * 180 / M_PI );

	result_sin = asin( (double)(op) / (hyp) ) ;
	printf("resultat angle (sin) : %f degres\n", result_sin * 180 / M_PI );

	double mean_angle = (result_tan + result_cos + result_sin)/3 ;
	printf("\nangle moyen : %f degres\n", mean_angle * 180 / M_PI );
	double correction_angle = ANGLE_REFERENCE - (mean_angle * 180 / M_PI) ;
	printf("inclinaison image : %f degres\n",  correction_angle);

	rotateE(full_image_usable, correction_angle, full_image_usable);
	imshow( "image droite", full_image_usable );

	//termine le programme lorsqu'une touche est frappee
	waitKey(0);
}