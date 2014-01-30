#ifndef MOMENT_H
#define MOMENT_H

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include "cv.h"
#include "Caracteristics.h"
using namespace cv;

// Moment hérite de Caracteristics
class Moment:public Caracteristics{
public:
	// Constructeur
	Moment(string nameCaract, string option);
	virtual void setCaractValues(map<string,vector<string>> pathFiles);
private:
	// Fonctions relatives au moment
	void prepare_img_moment(/*string pathFile*/);
	friend void thresh_callback(int,void*);
};

#endif
