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
#include "folders.h"
#include "caneva.h"
#include "manage_img.h"

#define DEBUG_LEVEL  3		// 0:no dbg - 1:dbg mini - 2:dbg normal - 3:dbg max

int reduction_factor ;
extern can_pt caneva_pts ;

int main(void){

	cout << "main\n";
/*	
	// paires de test
	Point2f p1 (0.33f, 0.1f);
	Point2f p2 (2.f, 2.f);
	Point2f p3 (3.f, 3.f);
	Point2f p4 (4.f, 4.f);
	pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>> paire_test1 = std::make_pair(p1, p2);
	pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>> paire_test2 = std::make_pair(p3, p4);
	
	// vector de test
	vector<pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>> vecteur = vector<pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>();
	vecteur.clear();
	vector<pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>::iterator it;
	it = vecteur.begin();
	it = vecteur.insert(it, paire_test1);
	it = vecteur.insert(++it, paire_test2);

	// map de test
	vectorMap pict = vectorMap();
	pict.insert(make_pair("banane", vecteur));

	string path = "C:/Users/Bamako/Downloads";
	try
	{
		initialize_folders(path);
		pict = input_pictogrammes(pict, path);
		output_pictogrammes(pict, path);
	}
	catch (exception& e)
	{
		std::cerr << "exception caught: " << e.what() << '\n';
	}
	*/

	Mat image_test = imread( "img/00000.png", 1 );
	Mat image_reference = imread( "img/template.png", 1 );
	

	cout << "\n\n" ;
/**** redimensionner images pour les tests ****/
	#if DEBUG_LEVEL > 0
	reduction_factor = 4;
	Size size_image_test( image_test.cols/reduction_factor, image_test.rows/reduction_factor);
	resize(image_test, image_test, size_image_test );
	Size size_image_reference( image_reference.cols/reduction_factor, image_reference.rows/reduction_factor );
	resize( image_reference, image_reference, size_image_reference );
	#endif

/**** calculer l'angle de rotation de l'image ****/
	double angle_correction = compute_warping(image_test, image_reference);

/**** appliquer la rotation **/
	rotateE(image_test, angle_correction, image_test);

	#if DEBUG_LEVEL > 1
	imshow( "image droite", image_test );
	#endif

/**** creer et dessiner le caneva ****/
	Point cross_up, cross_down;
	Mat image_caneva;
	find_crosses(image_test, image_reference, cross_up, cross_down);
	create_caneva(image_test, cross_up, cross_down);
	image_test.copyTo( image_caneva );
	show_caneva( image_caneva );
	circle(image_caneva, cross_up, 5, Scalar(100,0,255), 1, 8, 0);
	circle(image_caneva, cross_down, 5, Scalar(100,0,255), 1, 8, 0);
	imshow( "image avec caneva", image_caneva );

/**** reconnaitre le symbole en tête de chaque ligne ****/
	Mat img_extract ;
	int id_picto ;
	for(int i = 0 ; i < 7 ; i++){
		/*extraction de l'image de tête*/
		extractImage(image_test, img_extract, caneva_pts.x[1], caneva_pts.y[2*i+1], caneva_pts.x[2], caneva_pts.y[2*i+2]);
		imshow( "img_ext:" + ('0' + i) , img_extract );

		/********* ---> ICI : comparer cette image avec la base des pictogrammes (Martin) */
		id_picto = match_img(img_extract);

		/* extraction de la ligne + enregistrement sous le bon nom */
		for(int j=0; j<5 ; j++){
			extractImage(image_test, img_extract, caneva_pts.x[2*j+1], caneva_pts.y[2*i+1], caneva_pts.x[2*j+2], caneva_pts.y[2*i+2]);
			//imshow( "img_ext_line:" + ('0' + 10*i) + j, img_extract );

			//TODO : void saveImage(img_extract, "un joli petit nom bien formaté ici en fonction du type");
		}
	}

	waitKey(0);
	return 0;
}