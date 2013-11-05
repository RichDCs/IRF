
#include "warping.h"

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
  char name_windows[20];

//  0: SQDIFF - 1: SQDIFF NORMED - 2: TM CCORR - 3: TM CCORR NORMED - 4: TM COEFF - 5: TM COEFF NORMED
  int match_method = 5; // > 5 est la plus performante > testée jusqu'à +/- 12°

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

  //TODO : tester pourquoi l'efficacité est meilleure avec '-1'
  origin_template.x = matchLoc.x /*- 1*/ + template_image.size().width/2 ;
  origin_template.y = matchLoc.y /*- 1*/ + template_image.size().height/2 ;
  circle(img_display, origin_template, 5, Scalar(0,0,255), 1, 8, 0);

  sprintf(name_windows, "Source Image - %d", i);
  imshow( name_windows, img_display );

  sprintf(name_windows, "Result Image - %d", i);
  imshow( name_windows, result );

  i++;
  return;
}

double compute_warping(cv::Mat& full_image, cv::Mat& image_reference){

	/*********** If you want to add rotation on the source image *******************
	double angle = 0.5 ;
	rotateE(full_image, angle, full_image);
	//rotateE(full_image_usable_up, angle, full_image_usable_up);
	//rotateE(full_image_usable_down, angle, full_image_usable_down);
	/*******************************************************************************/

	/* configure a mask for the top_image and the bottom_image, split in middle */
	Rect roi_middle_up = Rect( 0, 0, full_image.size().width, full_image.size().height/2 );
	Rect roi_middle_down = Rect( 0, full_image.size().height/2, full_image.size().width, full_image.size().height/2 );

	/* apply a mask, to split image into 2 parts*/
	Mat full_image_usable_up = full_image(roi_middle_up);
	Mat full_image_usable_down = full_image(roi_middle_down);

	Point origine_cross_up;
	Point origine_cross_down;

	MatchingMethod( full_image_usable_up, image_reference, origine_cross_up );
	printf("Coordonnees 1ere croix :\n x : %d\n y : %d\n", origine_cross_up.x, origine_cross_up.y);

	MatchingMethod( full_image_usable_down, image_reference, origine_cross_down );
	printf("\n\nCoordonnees 2eme croix :\n x : %d\n y : %d\n", origine_cross_down.x, origine_cross_down.y);
	origine_cross_down.y += full_image.size().height/2 ;
	printf("\n\nCoordonnees 2eme croix (img complete) :\n x : %d\n y : %d\n\n", origine_cross_down.x, origine_cross_down.y);
	imshow( "image base", full_image );

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

	return correction_angle ;
}