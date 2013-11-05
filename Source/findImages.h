#ifndef FINDIMAGES_H

	#include "cv.h"
	#include "highgui.h"
	#include <string>

	using namespace cv;

	/* Prend en param�tre la position de l'image d'origine et trouve dans quelle ligne elle se situe */
	int findLine(double positionY);
	/* Pour une ligne donn�e, extraie les images associ�es et les ajoute dans un fichier (image+ appel de createDescription) */
	void extractImagesPerLine(int line, string name);
	/* Cr�er le fichier description de l'image */
	void createDescription(int line,int column, string name);
	/* Extraction d'une partie de l'image */
	void extractImage(Mat& src, double posX, double posY, int width, int height, string name);

#endif