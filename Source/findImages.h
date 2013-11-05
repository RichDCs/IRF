#ifndef FINDIMAGES_H

	#include "cv.h"
	#include "highgui.h"
	#include <string>

	using namespace cv;

	/* Prend en paramètre la position de l'image d'origine et trouve dans quelle ligne elle se situe */
	int findLine(double positionY);
	/* Pour une ligne donnée, extraie les images associées et les ajoute dans un fichier (image+ appel de createDescription) */
	void extractImagesPerLine(int line, string name);
	/* Créer le fichier description de l'image */
	void createDescription(int line,int column, string name);
	/* Extraction d'une partie de l'image */
	void extractImage(Mat& src, double posX, double posY, int width, int height, string name);

#endif