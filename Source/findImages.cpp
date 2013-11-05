
#include "findImages.h"

#define MARGE 82;
#define HEIGHT 60;
#define WIDTH 700;

int findLine(double positionY)
{
	// à calculer de façon relative
	int firstPosition = 195;
	int line = (positionY-195)/82+1;
	return line;
	// resize à 4 : 195 277 359 442 525 608 691
}

void extractImage(Mat& src, double posX, double posY, int width, int height, string name)
{
	Mat image;
	Rect region_of_interest = Rect(posX, posY, width, height);
	image = src(region_of_interest);
	imshow(name,image);
}

void extractImagesPerLine(int line, string name)
{
	// à calculer de façon relative
	int firstPosition = 195;
	int column;
	for(column=1;column<=5;column++)
	{
		// extract each image in a file and call createDescription

	}
	return;
}

void createDescription(int line,int column, string name)
{
	return;
}

