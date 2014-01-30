#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Caracteristics.h"
#include "cv.h"
using namespace cv;
using namespace std;


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

map<int,map<string,vector<double>>> Caracteristics::getZonesCaractValues(){
	return zonesValues;
}

// Setter du nom de la caractéristique
void Caracteristics::setName(string nameCaracteristics){
	name=nameCaracteristics;
}

void Caracteristics::setCaractValues(map<string,vector<string>> pathFiles){
	cout << "caracteristics caractValues" << endl;
}

void Caracteristics::setZonesValues(map<string,vector<string>> pathFiles){
	cout << "caracteristics zonesValues" << endl;
}

void Caracteristics::writeInAFile(string header,string pathFile){
	ofstream myfile;
	myfile.open (pathFile);
	myfile << header << endl;
	myfile << (this->showCaractValues(this->caractValues));
	myfile.close();
}

string Caracteristics::showCaractValues(map<string,vector<double>> caract){
	string result;
	for(map<string,vector<double>>::iterator it=caract.begin(); it!=caract.end(); ++it){
		result+= it->first+" = [ ";
		vector<double> values = it->second;
		for(int i=0;i<values.size();i++){
			
			// Conversion de la valeur en string
			ostringstream oss;
			oss	<< values[i];
			string value = oss.str();

			result += value;
			result+=" ";
			if(i!=values.size()-1)
				result+="; ";
		}
		result+="]\n";
	}
	return result;
}

void Caracteristics::writeIn7File(string header,string pathFile){
	for(int i=1;i<=7;i++){
		map<string,vector<double>> caract = zonesValues[i];
		ofstream myfile;
		
		// Conversion de la valeur en string
		ostringstream oss;
		oss	<< i;
		string zone = oss.str();

		string newPathFile = pathFile+"_zone"+zone+".txt";

		myfile.open (newPathFile);
		myfile << header << endl;
		myfile << (this->showCaractValues(caract));
		myfile.close();
	}
}

void Caracteristics::insertCaractValues(string pictoName,vector<double> vec){
	map<string,vector<double>>::iterator it = caractValues.begin(); 
	caractValues.insert(it,pair<string,vector<double>>(pictoName,vec));
}

void Caracteristics::insertZonesCaractValues(int zone, map<string,vector<double>> caract){
	map<int,map<string,vector<double>>>::iterator it = zonesValues.begin();
	zonesValues.insert(it,pair<int,map<string,vector<double>>>(zone,caract));
}

void Caracteristics::clearCaractValues(){
	caractValues.clear();
}