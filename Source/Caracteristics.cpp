#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Caracteristics.h"
using namespace std;


// Surcharge de l'opérateur <<
ostream& operator<<(ostream &out, const Caracteristics &c){
	//out << c.name << endl;
	map<string,vector<double>> caractValues = c.caractValues;
	for(map<string,vector<double>>::iterator it=caractValues.begin(); it!=caractValues.end(); ++it){
		out << it->first << " = [ ";
		vector<double> values = it->second;
		for(int i=0;i<values.size();i++){
			out << values[i] << " ";
			if(i!=values.size()-1)
				out << "; ";
		}
		out << "]" << endl;
	}
	return out;
}

Caracteristics::Caracteristics(){}

// Getter de la map
map<string,vector<double>> Caracteristics::getCaractValues(){
	return caractValues;
}

// Getter des valeurs de la caractéristique pour un pictogramme donné
vector<double> Caracteristics::getCaractValuesPicto(string pictoName){
	return caractValues.find(pictoName)->second;
}

// Getter du nom de la caractéristique
string Caracteristics::getName(){
	return name;
}

// Setter du nom de la caractéristique
void Caracteristics::setName(string nameCaracteristics){
	name=nameCaracteristics;
}

void Caracteristics::setCaractValues(map<string,vector<string>> pathFiles){
	cout << "caracteristics" << endl;
}

void Caracteristics::writeInAFile(string header,string pathFile){
	ofstream myfile;
	myfile.open (pathFile);
	myfile << header << endl;
	myfile << (*this);
	myfile.close();
}