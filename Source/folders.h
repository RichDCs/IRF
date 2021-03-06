#ifndef FOLDERS_H
#define FOLDERS_H
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include "cv.h"
using namespace cv;

#include <string>
#include <Windows.h>
#include <tchar.h> 
#include <stdio.h>

typedef std::map<std::string, std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>> vectorMap;

void create_folder(string path);
void initialize_folders(string path);
void output_pictogrammes(std::map<std::string, std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>> map, string path);
std::map<std::string, std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>> input_pictogrammes(std::map<std::string, std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>> map, string path);

#endif