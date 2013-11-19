#define _CRT_SECURE_NO_WARNINGS
#include "caneva.h"
#include "warping.h"

can_pt caneva_pts ; //structure contenant tous les points du caneva d'une image complète

void create_caneva(cv::Mat& full_image, cv::Point& cross_up, cv::Point& cross_down){

	full_image.size().width ;
	full_image.size().height ;
	unsigned int lx = cross_up.x - cross_down.x; // Largeur entre les deux croix
	unsigned int ly = cross_down.y - cross_up.y;// Hauteur entre les deux croix
/******* lignes (en rouge, car parcours selon X) *********/

	caneva_pts.x[FIRST_VERTICAL_COL] =  (unsigned int) (cross_down.x-lx*0.08) ; //= le haut de l'image (!=0 pour voir un bord)

	caneva_pts.x[1] = (unsigned int)( cross_down.x-lx*0.03 ); //encadre le symbole propre
	caneva_pts.x[2] = (unsigned int)( cross_down.x+lx*0.1 );

	caneva_pts.x[3] = (unsigned int)( cross_down.x+lx*0.183 );	//encadre la 1ere colone d'image
	caneva_pts.x[4] = (unsigned int)( cross_down.x+lx*0.31 );

	caneva_pts.x[5] = (unsigned int)( cross_down.x+lx*0.363 );	//encadre la 2eme colone d'image
	caneva_pts.x[6] = (unsigned int)( cross_down.x+lx*0.49 );

	caneva_pts.x[7] = (unsigned int)( cross_down.x+lx*0.541 );	//encadre la 3eme colone d'image
	caneva_pts.x[8] = (unsigned int)( cross_down.x+lx*0.668 );

	caneva_pts.x[9] = (unsigned int)( cross_down.x+lx*0.72 );	//encadre la 4eme colone d'image
	caneva_pts.x[10] = (unsigned int)( cross_down.x+lx*0.848 )	;

	caneva_pts.x[11] = (unsigned int)( cross_down.x+lx*0.90 );	//encadre la 5eme colone d'image
	caneva_pts.x[12] = (unsigned int)( cross_down.x+lx*1.027 );

	caneva_pts.x[LAST_VERTICAL_COL] =  (unsigned int)( cross_down.x+lx*1.05 );//==la fin de l'image, dernière bordure d'arret

/******* colones (en bleu, car parcours selon Y)*********/

	caneva_pts.y[FIRST_VERTICAL_LINE] = cross_up.y ;		//colone de bord de l'image (!=0 pour voir un bord)

	caneva_pts.y[1] = (unsigned int)( cross_up.y + ly*0.092 );		//encadre la 1eme ligne d'imagette dessinée main
	caneva_pts.y[2] = (unsigned int)( cross_up.y + ly*0.182 );

	caneva_pts.y[3] = (unsigned int)( cross_up.y + ly*0.217 );	//encadre la 2eme ligne d'imagette dessinée main
	caneva_pts.y[4] = (unsigned int)( cross_up.y + ly*0.307 );

	caneva_pts.y[5] = (unsigned int)( cross_up.y + ly*0.343 );	//encadre la 3eme ligne d'imagette dessinée main
	caneva_pts.y[6] = (unsigned int)( cross_up.y + ly*0.433 );

	caneva_pts.y[7] = (unsigned int)( cross_up.y + ly*0.470 );	//encadre la 4eme ligne d'imagette dessinée main
	caneva_pts.y[8] = (unsigned int)( cross_up.y + ly*0.559 );

	caneva_pts.y[9] = (unsigned int)( cross_up.y + ly*0.595 );	//encadre la 5eme ligne d'imagette dessinée main
	caneva_pts.y[10] = (unsigned int)( cross_up.y + ly*0.684 );

	caneva_pts.y[11] = (unsigned int)( cross_up.y + ly*0.721 );	//encadre la 6eme ligne d'imagette dessinée main
	caneva_pts.y[12] = (unsigned int)( cross_up.y + ly*0.81 );

	caneva_pts.y[13] = (unsigned int)( cross_up.y + ly*0.847 );	//encadre la 7eme ligne d'imagette dessinée main
	caneva_pts.y[14] = (unsigned int)( cross_up.y + ly*0.935 );

	caneva_pts.y[LAST_VERTICAL_LINE] = cross_down.y ;
}

void show_caneva(cv::Mat& full_image){

/* lignes verticales (== y est fixe) */
	for(int i = 0 ; i <= LAST_VERTICAL_COL ; i++ )
		line(full_image,
			Point(caneva_pts.x[i],caneva_pts.y[0]),
			Point(caneva_pts.x[i],caneva_pts.y[LAST_VERTICAL_LINE]),
			Scalar(0,0,255), /*thickness=*/1, /*lineType=*/8, /*shift=*/0);

/* lignes horizontales (== x est fixe) */
	for(int i = 0 ; i <= LAST_VERTICAL_LINE ; i++ )
		line(full_image,
			Point(caneva_pts.x[0],caneva_pts.y[i]),
			Point(caneva_pts.x[LAST_VERTICAL_COL],caneva_pts.y[i]),
			Scalar(255,100,0), /*thickness=*/1, /*lineType=*/8, /*shift=*/0);
}
