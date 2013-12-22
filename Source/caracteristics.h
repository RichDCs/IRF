#ifndef CARACTERISTICS_H
#define CARACTERISTICS_H

#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Caracteristics
{
	// Surcharge de l'opérateur <<
	friend ostream& operator<<(ostream &out, const Caracteristics &c);

protected:
	// Nom de la caractéristique
	string name;
	// Cette map associe à chaque picto, la valeur de la caractéristique correspondante
	map<string,vector<double>> caractValues;	

public:
	// Constructeur
	Caracteristics();
	// Getter de la map
	map<string,vector<double>> getCaractValues();
	// Getter des valeurs de la caractéristique pour un pictogramme donné
	vector<double> getCaractValuesPicto(string pictoName);
	// Getter du nom de la caractéristique
	string getName();
	// Setter du nom de la caractéristique
	void setName(string nameCaracteristics);
	// Setter de la map
	void setCaractValues(map<string,vector<string>> pathFiles);
	// Ecrit le résultat de la caractéristique dans un fichier
	void writeInAFile(string header, string pathFile);
};

#endif

