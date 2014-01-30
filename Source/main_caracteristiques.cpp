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
#include <string>
using namespace std;
#include <Windows.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "Base_exemples.h"
#include "Moment.h"
#include "percent_of_white.h"
#include "center.h"
#include "cut_down.h"
#include "diagonale.h"
#include "angle.h"

int main(void){  
	// Recupere la liste des chemins d'acces a tous les fichiers de la base d'exemple
	BaseExemples base_exemple = BaseExemples();
	//cout << base_exemple;
	system("mkdir resultat");

	//cut_down_all(base_exemple.getBaseExemplesPath());

	/*Center center = Center("center");
	center.setCaractValues(base_exemple.getBaseExemplesPath());
	center.writeInAFile("center","resultat/center");
	center.setZonesValues(base_exemple.getBaseExemplesPath());
	center.writeIn7File("center","resultat/center");

	PercentOfWhite percent = PercentOfWhite("percentOfWhite");
	percent.setCaractValues(base_exemple.getBaseExemplesPath());
	percent.writeInAFile("percent","resultat/percent_of_white.txt");
	percent.setZonesValues(base_exemple.getBaseExemplesPath());*/
	// le chemin d'accès au fichier sera complété dans la fonction donc ne pas mettre ".txt"
	/*percent.writeIn7File("percent","resultat/percent_of_white");

	Diagonale diagonale = Diagonale("diagonale");
	diagonale.setCaractValues(base_exemple.getBaseExemplesPath());
	diagonale.writeInAFile("diagonale","resultat/diagonale.txt");

	Angle angle = Angle("angle");
	angle.setCaractValues(base_exemple.getBaseExemplesPath());
	angle.writeInAFile("angle","resultat/angle.txt");*/
	Moment moment = Moment("moment","m01");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m01","resultat/m01.txt");
	
	moment = Moment("moment","m02");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m02","resultat/m02.txt");

	moment = Moment("moment","m03");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m03","resultat/m03.txt");

	moment = Moment("moment","m10");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m10","resultat/m10.txt");

	moment = Moment("moment","m11");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m11","resultat/m11.txt");

	moment = Moment("moment","m12");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m12","resultat/m12.txt");

	moment = Moment("moment","m20");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m20","resultat/m20.txt");

	moment = Moment("moment","m21");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m21","resultat/m21.txt");

	moment = Moment("moment","m30");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("m30","resultat/m30.txt");	

	moment = Moment("moment","mu02");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mu02","resultat/mu02.txt");

	moment = Moment("moment","mu03");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mu03","resultat/mu03.txt");

	moment = Moment("moment","mu11");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mu11","resultat/mu11.txt");

	moment = Moment("moment","mu12");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mu12","resultat/mu12.txt");

	moment = Moment("moment","mu20");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mu20","resultat/mu20.txt");

	moment = Moment("moment","mu30");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mu30","resultat/mu30.txt");
	
	/*
	Hauteur hauteur = Hauteur("hauteur");
	hauteur.setCaractValues(base_exemple.getBaseExemplesPath());
	hauteur.writeInAFile("hauteur","resultat/hauteur.txt");
	*/
	// Moyenne des moments m00
	//Moment moment = Moment("moment","moy");
	//moment.setCaractValues(base_exemple.getBaseExemplesPath());
	//cout << moment;

	//moment.writeInAFile("moyenne","resultat/moyenne.txt");
	// Moment m00
	//moment = Moment("moment","m00");
	//moment.setCaractValues(base_exemple.getBaseExemplesPath());
	//moment.writeInAFile("m00","resultat/m00.txt");
	// Moment mcX
	/*Moment moment = Moment("moment","mcX");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mcX","resultat/mcX.txt");*/
	// Moment mcY
	/*moment = Moment("moment","mcY");
	moment.setCaractValues(base_exemple.getBaseExemplesPath());
	moment.writeInAFile("mcX","resultat/mcY.txt");*/
	// Nombre de contours
	//moment = Moment("moment","nbContours");
	//moment.setCaractValues(base_exemple.getBaseExemplesPath());
	//moment.writeInAFile("nbContours","resultat/nbContours.txt");
	// Arc length
	//moment = Moment("moment","arclength");
	//moment.setCaractValues(base_exemple.getBaseExemplesPath());
	//moment.writeInAFile("arclength","resultat/arclength.txt");
	// Contours area
	//moment = Moment("moment","contourArea");
	//moment.setCaractValues(base_exemple.getBaseExemplesPath());
	//moment.writeInAFile("contourArea","resultat/contourArea.txt");
	system("pause");
	waitKey(0);
	return 0;
}
	