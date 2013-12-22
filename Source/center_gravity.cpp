#include "center_gravity.h"


CenterGravity::CenterGravity(void)
{
	threshold = 0;
}


CenterGravity::~CenterGravity(void)
{
}

void CenterGravity::calculate_CenterGravity(string path)
{
	/// Read image in gray
	Mat src;
	src = read_image_grayscale(path);

	/// Detect edges
	Mat edges;
	edges = remove_edges(src, 100);

	/// Coordonates of the result
	int centre_gravity_x;
	int centre_gravity_y;

	/// Sum of the coordonates
	int sumX = 0;
	int sumY = 0;

	/// Number of black points
	int count = 0;

	/// Convert image to gray
	//cvtColor( src, src_gray, CV_BGR2GRAY );

	for (int i = 0; i < edges.rows; i++)
	{
		for (int j = 0; j < edges.cols; j++)
		{
			if (edges.at<Vec3b>(i, j).val[0] > threshold)
		   {
			   sumX += i;
			   sumY += j;
			   count++;
		   }
		}
	}

	if (count != 0) 
	{
		centre_gravity_x = (int) sumX/count;
		centre_gravity_y = (int) sumY/count; 
	}

	cout << "Point de gravité : (" << centre_gravity_x << "; " << centre_gravity_y << ")";
}

Mat CenterGravity::remove_edges(Mat src, int threshold)
{
	Mat canny_output;

	/// Detect edges using canny
	Canny(src, canny_output, threshold, threshold*2, 3);

	/// Do more stuff here

	return canny_output;
}

Mat CenterGravity::read_image_grayscale(string image_path)
{
	/// Return image matrix
    return imread(image_path, CV_LOAD_IMAGE_GRAYSCALE);
}