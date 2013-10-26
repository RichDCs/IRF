/*
*	TODO :
*		- faire le traitement simultan� top/bottom
*		- s�parer les focntions en fichiers propres
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

char name_windows[20];

int match_method = 5; // > 5 est la plus performante > test�e jusqu'� +/- 12�
int max_Trackbar = 5;

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
	double angle = 5 ;
	rotateE(full_image_usable, angle, full_image_usable);
	rotateE(full_image_usable_up, angle, full_image_usable_up);
	rotateE(full_image_usable_down, angle, full_image_usable_down);
	/*******************************************************************************/

	/*Load the template (the cross) and apply a reduction */
	Mat template_cross = imread( "img/template.png", 1 );
	Size size_template( template_cross.cols/reduction_factor, template_cross.rows/reduction_factor );
	resize( template_cross, template_usable/*********/, size_template );	


	/// Create Trackbar
//	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
	Point origine_template;

	MatchingMethod( full_image_usable_up, template_usable, origine_template );
	printf("Coordonnees 1ere croix :\n x : %d\n y : %d\n", origine_template.x, origine_template.y);

	MatchingMethod( full_image_usable_down, template_usable, origine_template );
	printf("\n\nCoordonnees 2eme croix :\n x : %d\n y : %d\n", origine_template.x, origine_template.y);

	//termine le programme lorsqu'une touche est frappee
	waitKey(0);
}


/**
 * Rotate an image
 */
void rotateE(cv::Mat& src, double angle, cv::Mat& dst)
{
    int len = std::max(src.cols, src.rows);
    cv::Point2f pt(len/2., len/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
    cv::warpAffine(src, dst, r, cv::Size(len, len));
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 * @arg
 *		full_image : image for source
 *		template_image : image that you want to find in source
 *		origin_template : Point of the matching template found in the image source
 */
void MatchingMethod( cv::Mat& full_image, cv::Mat& template_image, cv::Point& origin_template )
{
  static unsigned int i ;
  Mat result;//step by step
  /// Source image to display
  Mat img_display;
  full_image.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  full_image.cols - template_image.cols + 1;
  int result_rows = full_image.rows - template_image.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( full_image, template_image, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + template_image.cols , matchLoc.y + template_image.rows ), Scalar(255,0,255), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + template_image.cols , matchLoc.y + template_image.rows ), Scalar(255,0,255), 2, 8, 0 );

  //TODO : tester pourquoi l'efficacit� est meilleure avec '-1'
  origin_template.x = matchLoc.x - 1 + template_image.size().width/2 ;
  origin_template.y = matchLoc.y - 1 + template_image.size().height/2 ;
  circle(img_display, origin_template, 5, Scalar(0,0,255), 1, 8, 0);

  sprintf(name_windows, "Source Image - %d", i);
  imshow( name_windows, img_display );

  sprintf(name_windows, "Result Image - %d", i);
  imshow( name_windows, result );

  i++;
  return;
}