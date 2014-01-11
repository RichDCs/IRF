#ifndef CARACTERISTICS_H
#define CARACTERISTICS_H

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "cv.h"
using namespace cv;
using namespace std;

class Caracteristics
{
	// Surcharge de l'op�rateur <<
	friend ostream& operator<<(ostream &out, const Caracteristics &c);

protected:
	// Nom de la caract�ristique
	string name;
	// Cette map associe � chaque picto, la valeur de la caract�ristique correspondante
	map<string,vector<double>> caractValues;	

public:
	// Constructeur
	Caracteristics();
	// Getter de la map
	map<string,vector<double>> getCaractValues();
	// Getter des valeurs de la caract�ristique pour un pictogramme donn�
	vector<double> getCaractValuesPicto(string pictoName);
	// Getter du nom de la caract�ristique
	string getName();
	// Setter du nom de la caract�ristique
	void setName(string nameCaracteristics);
	// Setter de la map
	void setCaractValues(map<string,vector<string>> pathFiles);
	// Ecrit le r�sultat de la caract�ristique dans un fichier
	void writeInAFile(string header, string pathFile);
};

#endif

