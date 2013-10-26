//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-INFO 5-EII
// contenu : creer la base de donnée de la reconnaissance d'images
// auteur : Yannick Gaudin, Martin Seillan, Alexandra Charrier, Richard Lagrange
// date : 26/10/2013
//////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"
using namespace cv;
#include <iostream>
using namespace std;

#include "warping.h"

#define DEBUG_LEVEL  3		// 0:no dbg - 1:dbg mini - 2:dbg normal - 3:dbg max

int main(void){

	double angle_correction;
	Mat image_test = imread( "img/00000.png", 1 );
	Mat image_reference = imread( "img/template.png", 1 );

/**** calculer l'angle de rotation de l'image ****/
	angle_correction = compute_warping(image_test, image_reference);

/**** appliquer la rotation **/
	rotateE(image_test, angle_correction, image_test);

	#if DEBUG_LEVEL > 0
	imshow( "image droite", image_test );
	#endif

/**** générer l'image aux dimensions voulues ****/

/**** reconnaitre le symbole en tête de chaque ligne ****/

/**** isoler et enregistrer chaque rectangle de la ligne ****/



	waitKey(0);
	return 0;
}