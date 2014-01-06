#include "Base_exemples.h"
#include <string>
#include <iostream>
#include <vector>
#include "dirent.h"
#include <sstream>
using namespace std;

BaseExemples::BaseExemples() {
	base_exemples_path = base_exemples_repertoires();
}

vector<string> BaseExemples::base_exemples_files(char* chemin){
	vector<string> files;
	DIR* base_files = NULL;
	struct dirent* one_file = NULL;
	char* nom_picto = NULL;

	// Ouverture du repertoire
	base_files = opendir(chemin);
	if(base_files==NULL){
		printf("Erreur lors de l'ouverture du répertoire du pictogramme\n");
		exit(1);
	}else{
		one_file = readdir(base_files);
		while(one_file!=NULL){
			string name = one_file->d_name;
			string extension = name.substr(name.length()-1,name.length()-1);
			if(extension!="" && extension!="."){
				extension = name.substr(name.length()-4,name.length()-1);
				if(extension==".png"){
					// Ajout dans le vecteur
					string chemin_fichier = chemin;
					chemin_fichier +="/"+name;
					files.push_back(chemin_fichier);
				}
			}
			one_file = readdir(base_files);
		}
		// Fermeture du repertoire
		closedir(base_files);
	}
	return files;
}

map<string,vector<string>> BaseExemples::base_exemples_repertoires(){
	map<string,vector<string>> resultat;
	map<string,vector<string>>::iterator it = resultat.begin();
	DIR* base_exemples = NULL;
	char* base = "base_exemples";
	struct dirent* sous_repertoire = NULL;

	base_exemples = opendir(base);
	if(base_exemples == NULL){
		printf("Erreur lors de l'ouverture du répertoire de la base\n");
		exit(1);
	}else{
		sous_repertoire = readdir(base_exemples);
		while(sous_repertoire!=NULL){
			string name = sous_repertoire->d_name;
			string end_of_name = name.substr(name.length()-1,name.length()-1);
			// Ne prend pas en compte ni le dossier courant ni le dossier parent
			if(end_of_name!="." && end_of_name!=""){
				vector<string> temp;
				char chemin[100] = "";
				strcat(chemin,base);
				strcat(chemin,"/");
				strcat(chemin,sous_repertoire->d_name);
				temp = base_exemples_files(chemin);
				allPictoName.push_back(name);
				resultat.insert(it,pair<string,vector<string>>(name,temp));
			}
			sous_repertoire = readdir(base_exemples);
		}		
	closedir(base_exemples);
	}
	return resultat;
}

map<string,vector<string>> BaseExemples::getBaseExemplesPath(){
	return base_exemples_path;
}

ostream& operator<<(ostream &out, const BaseExemples &b){
	for(int i=0;i<b.allPictoName.size();i++){
		string namePicto = b.allPictoName[i];
		vector<string> allPath = b.base_exemples_path.find(namePicto)->second;
		out << namePicto << " => " << endl;
		for(int j=0;j<allPath.size();j++){
			out << allPath[j] << endl;
		}
		out << endl;
	}
    return out;
} 

vector<string> BaseExemples::getAllPictoName(){
	return allPictoName;
}

vector<string> BaseExemples::getAllPictoPath(string picto){
	return base_exemples_path.find(picto)->second;
}