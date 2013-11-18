//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-INFO 5-EII
// contenu : creer la base de donnée de la reconnaissance d'images
// auteur : Yannick Gaudin, Martin Seillan, Alexandra Charrier, Richard Lagrange
// date : 26/10/2013
//////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"
using namespace cv;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "warping.h"
//#include "folders.h"
#include "caneva.h"
#include "manage_img.h"
#include <Windows.h>

#define DEBUG_LEVEL  3		// 0:no dbg - 1:dbg mini - 2:dbg normal - 3:dbg max
#define NB_REPOSITORY 35 // 35
#define NB_FILE 22 // 22

int reduction_factor = 2;
extern can_pt caneva_pts ;
extern struct database_picto db_picto[];
extern struct database_picto db_text[];

int main(void){

	cout << "main\n";
/*** dossier necessaires ***/
	system("mkdir sortie");
	system("mkdir data");

/**** Template de la croix ****/
	Mat image_reference = imread( "img/template.png", 1 );
	
	#if DEBUG_LEVEL > 0
	Size size_image_reference( image_reference.cols/reduction_factor, image_reference.rows/reduction_factor );
	resize( image_reference, image_reference, size_image_reference );
	#endif

/**** boucle générale pour parcourir les dossiers ****/
	string path_root = "NicIcon/";
	int k;
	for(k=0;k<NB_REPOSITORY;k++){

/**** Détermination du numéro du scripteur ****/
		string path_directory = path_root;
		string numeroScripteur = "";
		// conversion d'un entier en string
		ostringstream ossK;
		ossK << k;
		string num_k = ossK.str();
		if(k<10)
			numeroScripteur = "00"+num_k;
		else
			numeroScripteur = "0"+num_k;

/**** Construction du chemin d'accès au dossier ****/
		string tmp_directory = "";
		tmp_directory = "w"+numeroScripteur;
		tmp_directory += "-scans/";
		path_directory += tmp_directory;

		int l;
		for(l=0;l<NB_FILE;l++){
/**** Détermination du numéro de la page ****/
			string path_file = path_directory;
			string numeroPage = "";
			ostringstream ossL;
			ossL << l;
			string num_l = ossL.str();
			if(l<10)
				numeroPage = "0"+num_l;
			else
				numeroPage = num_l;

/**** Détermination du numéro du formulaire ****/
			string numeroFormulaire = numeroScripteur+numeroPage;

/**** Construction du chemin d'accès au fichier et initialisation de image_in (image actuelle à traiter) ****/
			path_file += numeroFormulaire+".png"; 
			Mat image_in = imread(path_file,1);
			cout << path_file << endl;
/**** Redimensionnement des images pour les tests ****/
			#if DEBUG_LEVEL > 0
			Size size_image_test( image_in.cols/reduction_factor, image_in.rows/reduction_factor);
			resize(image_in, image_in, size_image_test );
			#endif
			
/**** Calcul de l'angle de rotation de l'image ***/
			cout << "Calcul de l'angle de rotation de l'image" << endl;
			double angle_correction = compute_warping(image_in,image_reference);

/**** Applique la rotation ****/
			rotateE(image_in,angle_correction,image_in);
			
			/*#if DEBUG_LEVEL > 1
			imshow("image droite", image_in);
			#endif*/

/**** Creer le canevas et dessiner le caneva ****/
			cout << "Dessiner le caneva" << endl;
			Point cross_up, cross_down;
			Mat image_caneva;
			find_crosses(image_in, image_reference, cross_up, cross_down);
			create_caneva(image_in, cross_up, cross_down);
			image_in.copyTo( image_caneva );
			show_caneva( image_caneva );
			circle(image_caneva, cross_up, 5, Scalar(100,0,255), 1, 8, 0);
			circle(image_caneva, cross_down, 5, Scalar(100,0,255), 1, 8, 0);
			//imshow( "image avec caneva", image_caneva );
			string path_caneva = "sortie/"+numeroFormulaire+"_caneva.png";
			imwrite(path_caneva,image_caneva);

/**** Reconnaissance du symbole en tête de chaque ligne ****/
			Mat img_extract ;
			int id_picto, id_text ;
			for(int i = 0 ; i < 7 ; i++){
				/*extraction de l'image de tête*/
				cout << "Reconnaissance de l'image de tete" << endl;
				extractImage(image_in, img_extract, caneva_pts.x[1], caneva_pts.y[2*i+1], caneva_pts.x[2], caneva_pts.y[2*i+2]);
				//imshow( "img_ext:" + ('0' + i) , img_extract );
				/* comparaison du pictogramme avec la base*/
				id_picto = match_img(img_extract, MATCH_IMG);
				/* comparaison du texte avec la base */
				id_text = match_img(img_extract, MATCH_TXT);
				//cout << "-\n-\n" ;

				// détermination de la ligne
				int ligne_int = i+1;
				ostringstream ossLigne;
				ossLigne << ligne_int;
				string ligne = ossLigne.str();

				string identifiantIcone = "";
				if(id_picto!=-1)
					identifiantIcone = db_picto[id_picto].description.c_str();
				else{
					cout << "\nProbleme lors du match d'un picto de "+path_file+" a la ligne "+ligne << endl;
					system("pause");
				}
					
				string taille = "";
				if(id_text!=-1)
						taille=db_text[id_text].description.c_str();
				else if(l>=2 && id_text==-1){
					cout << "\nProbleme lors du match d'un text de "+path_file+" a la ligne "+ligne << endl;
					system("pause");
				}

				/* extraction de la ligne + enregistrement sous le bon nom */
				for(int j=1; j<6 ; j++){
					cout << "Extraction imagette" << endl;
					extractImage(image_in, img_extract, caneva_pts.x[2*j+1], caneva_pts.y[2*i+1], caneva_pts.x[2*j+2], caneva_pts.y[2*i+2]);
					//imshow( "img_ext_line:" + ('0' + 10*i) + j, img_extract );   //si vous voulez voir les 5 images extraites de la ligne en cours

/**** Création de l'imagette ****/

					// détermination de la colonne
					int colonne_int = j;
					ostringstream ossColonne;
					ossColonne << colonne_int;
					string colonne = ossColonne.str();
				
					// chemin d'accès aux deux fichiers de sortie
					string path_out = "data/"+identifiantIcone+"_"+numeroScripteur+"_"+numeroPage+"_"+ligne+"_"+colonne;
					string path_out_png = path_out+".png";
					string path_out_txt = path_out+".txt";

					// création du fichier png
					cout << "Extraction dans un fichier png" << endl;
					imwrite(path_out_png,img_extract);

					// création du fichier txt
					cout << "Extraction dans un fichier de description" << endl;
					ofstream extract_image_file;
					extract_image_file.open(path_out_txt,ios::out);
					if(extract_image_file.bad())
						return 1;
					extract_image_file << "# Module IRF, 5INFO 5EII" << endl;
					extract_image_file << "# Yannick GAUDIN, Martin SEILLAN, Alexandra CHARRIER, Richard LAGRANGE" << endl;
					extract_image_file << "etiquette "+identifiantIcone << endl;
					extract_image_file << "formulaire "+numeroFormulaire << endl;
					extract_image_file << "scripteur "+numeroScripteur << endl;
					extract_image_file << "page "+numeroPage << endl;
					extract_image_file << "ligne "+ligne << endl;
					extract_image_file << "colonne "+colonne << endl;
					extract_image_file << "taille "+taille << endl;
					extract_image_file.close();
				
					cout << endl;
					cout << endl;
					//TODO : void saveImage(img_extract, "un joli petit nom bien formaté ici en fonction du type");
					/* utiliser :
						db_picto[id_picto].description.c_str()
							ET
						db_text[id_text].description.c_str()
							pour obtenir les textes correspondants au résultat
					*/
				}
			}
		}
	}

	cout << "\n\n-- fin du programme --\n\n" ;
	system("pause");
	waitKey(0);
	return 0;
}