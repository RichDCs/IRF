#ifndef FOLDERS_H
#define FOLDERS_H

#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;

#include <string>
#include <Windows.h>

void create_folder(string path);
void output_pictogrammes(std::map<std::string, std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>> map, string path);

#endif