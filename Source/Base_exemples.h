#ifndef BASEEXEMPLE_H
#define BASEEXEMPLE_H

#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class BaseExemples
{
	// Surcharge de l'opérateur <<
	friend ostream& operator<<(ostream &out, const BaseExemples &b);

private:
	vector<string> allPictoName;
	map<string,vector<string>> base_exemples_path;
	// Recupere les fichiers contenus dans un dossier specifique
	vector<string> base_exemples_files(char* chemin);
	// Parcourt les dossiers sous la base_exemples
	map<string,vector<string>> base_exemples_repertoires();
	
public:
	// Constructeur
	BaseExemples();
	// Getter sur l'attribut base_exemples_path
	map<string,vector<string>> getBaseExemplesPath();
	// Rend tous les chemins d'accès à un pictogramme donné
	vector<string> getAllPictoPath(string picto);
	// Rend tous les noms des pictogrammes
	vector<string> getAllPictoName();
};

#endif

