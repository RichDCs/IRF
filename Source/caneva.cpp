#include "caneva.h"
#include "warping.h"

can_pt caneva_pts ; //structure contenant tous les points du caneva d'une image complète

void create_caneva(cv::Mat& full_image, cv::Point& cross_up, cv::Point& cross_down){

	full_image.size().width ;
	full_image.size().height ;

/******* lignes (en rouge, car parcours selon X) *********/

	caneva_pts.x[FIRST_VERTICAL_COL] = 30 ; //= le haut de l'image (!=0 pour voir un bord)

	caneva_pts.x[1] = cross_down.x-20 ; //encadre le symbole propre
	caneva_pts.x[2] = cross_down.x+40 ;

	caneva_pts.x[3] = cross_down.x + 90 ;	//encadre la 1ere colone d'image
	caneva_pts.x[4] = cross_down.x + 130;

	caneva_pts.x[5] = cross_down.x + 180;	//encadre la 2eme colone d'image
	caneva_pts.x[6] = cross_down.x + 210;

	caneva_pts.x[7] = cross_down.x + 260;	//encadre la 3eme colone d'image
	caneva_pts.x[8] = cross_down.x + 300;

	caneva_pts.x[9] = cross_down.x + 340;	//encadre la 4eme colone d'image
	caneva_pts.x[10] = cross_down.x + 370;

	caneva_pts.x[11] = cross_down.x + 420;	//encadre la 5eme colone d'image
	caneva_pts.x[12] = cross_down.x + 460;

	caneva_pts.x[LAST_VERTICAL_COL] = cross_up.x + 40 ;//==la fin de l'image, dernière bordure d'arret

/******* colones (en bleu, car parcours selon Y)*********/

	caneva_pts.y[FIRST_VERTICAL_LINE] = cross_up.y ;		//colone de bord de l'image (!=0 pour voir un bord)

	caneva_pts.y[1] = cross_up.y + 70;		//encadre la 1eme ligne d'imagette dessinée main
	caneva_pts.y[2] = cross_up.y + 112 ;

	caneva_pts.y[3] = cross_up.y + 150 ;	//encadre la 2eme ligne d'imagette dessinée main
	caneva_pts.y[4] = cross_up.y + 190 ;

	caneva_pts.y[5] = cross_up.y + 238 ;	//encadre la 3eme ligne d'imagette dessinée main
	caneva_pts.y[6] = cross_up.y + 273 ;

	caneva_pts.y[7] = cross_up.y + 320 ;	//encadre la 4eme ligne d'imagette dessinée main
	caneva_pts.y[8] = cross_up.y + 360 ;

	caneva_pts.y[9] = cross_up.y + 400 ;	//encadre la 5eme ligne d'imagette dessinée main
	caneva_pts.y[10] = cross_up.y + 440 ;

	caneva_pts.y[11] = cross_up.y + 480 ;	//encadre la 6eme ligne d'imagette dessinée main
	caneva_pts.y[12] = cross_up.y + 520 ;

	caneva_pts.y[13] = cross_up.y + 568 ;	//encadre la 7eme ligne d'imagette dessinée main
	caneva_pts.y[14] = cross_up.y + 603 ;

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
