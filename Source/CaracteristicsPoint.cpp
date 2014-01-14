#include <iostream>
#include "CaracteristicsPoint.h"
#include <fstream>
using namespace std;

CaracteristicsPoint::CaracteristicsPoint(){}

void CaracteristicsPoint::writeInAFile(string header,string pathFile){
	// On complète le chemin d'accès au fichier
	string newPathFile = pathFile +"X.txt";
	pointX.writeInAFile(header,newPathFile);
	newPathFile = pathFile+"Y.txt";
	pointY.writeInAFile(header,newPathFile);
}

void CaracteristicsPoint::writeIn7File(string header,string pathFile){
	// On complète le chemin d'accès au fichier
	string newPathFile = pathFile +"X";
	pointX.writeIn7File(header,newPathFile);
	newPathFile = pathFile+"Y";
	pointY.writeIn7File(header,newPathFile);
}