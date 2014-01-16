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
	// Surcharge de l'opérateur <<
	//friend ostream& operator<<(ostream &out, const Caracteristics &c);

protected:
	// Nom de la caractéristique
	string name;
	// Cette map associe à chaque picto, la valeur de la caractéristique correspondante
	map<string,vector<double>> caractValues;	
	//CaractValues caractValues;
	// Cette map associe à chaque zone d'un picto, la valeur de la caractéristique correspondante
	map<int,map<string,vector<double>>> zonesValues;
public:
	// Constructeur
	Caracteristics();
	// Getter de la map
	map<string,vector<double>> getCaractValues();
	// Getter des valeurs de la caractéristique pour un pictogramme donné
	vector<double> getCaractValuesPicto(string pictoName);
	map<int,map<string,vector<double>>> getZonesCaractValues();
	void insertCaractValues(string pictoName,vector<double> vec);
	void insertZonesCaractValues(int zone, map<string,vector<double>> caract);
	void clearCaractValues();
	// Getter du nom de la caractéristique
	string getName();
	// Setter du nom de la caractéristique
	void setName(string nameCaracteristics);
	// Setter de la map
	void setCaractValues(map<string,vector<string>> pathFiles);
	// Setter de la map zonesValues
	void setZonesValues(map<string,vector<string>> pathFiles);
	// Ecrit le résultat de la caractéristique dans un fichier
	void writeInAFile(string header, string pathFile);
	// Affichage de la map de la caractéristique
	string showCaractValues(map<string,vector<double>> caract);
	// Ecrit le résultat de la caractéristique dans sept fichiers différents correspondants aux sept zones possibles
	void writeIn7File(string header,string pathFile);
};

#endif

