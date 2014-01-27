#ifndef CUTDOWN_H
#define CUTDOWN_H

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include "cv.h"
using namespace cv;

using namespace cv;

void cut_down_all(map<string,vector<string>> pathFiles);
Mat cut_down(Mat src);

// c'est pour débugger et vérifier que ça rogne correctement les images
//void cut_down_all(map<string,vector<string>> pathFiles);

#endif