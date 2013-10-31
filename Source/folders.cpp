//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-INFO 5-EII
// contenu : creer la base de données de la reconnaissance d'images
// auteur : Yannick Gaudin, Martin Seillan, Alexandra Charrier, Richard Lagrange
// date : 26/10/2013
//////////////////////////////////////////////////////////////////////////

#include "folders.h"

LPWSTR ConvertToLPWSTR(const std::string& s) {
  LPWSTR ws = new wchar_t[s.size()+1]; // +1 for zero at the end
  copy( s.begin(), s.end(), ws );
  ws[s.size()] = 0; // zero at the end
  return ws;
}

/// <summary>
/// Creates a folder at the specified path.
/// </summary>
/// <param name="path">The path.</param>
void create_folder(string path) {
	cout << "Chosen path: " + path + "\n";

	LPWSTR complete_path = ConvertToLPWSTR(path);

	if (CreateDirectory(complete_path, NULL) ||
    ERROR_ALREADY_EXISTS == GetLastError()) {
		// Directory created or already existing
		cout << "Directory " + path + " created." + "\n";
	} else {
		 // Failed to create directory.
		cout << "Unable to create " + path + "\n";
		throw exception();
	}
}

void initialize_folders(string path) {
	create_folder(path + "/input_pictogrammes");
	create_folder(path + "/output_pictogrammes");
}

/// <summary>
/// Outputs the pictogram images from the specified map into individual folders.
/// </summary>
/// <param name="map">The map.</param>
/// <param name="path">The path.</param>
void output_pictogrammes(vectorMap map, string path) {	
	vectorMap::iterator it;
	string output_folder = path + "/output_pictogrammes";
	
	for (it = map.begin(); it != map.end(); ++it) {
		string pict_folder = output_folder + "/" + it->first;
		cout << "Creating " + pict_folder + "\n";
		create_folder(pict_folder);

		// iterer sur les points pour extraire les imagettes et les mettre dans le dossier crée.
		std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>>::iterator it_vect;
		for (it_vect = it->second.begin(); it_vect != it->second.end(); ++it_vect) {
			// appliquer la fonction pour créer une imagette (grace à la paire de points) à l'endroit pict_folder
			cout << it_vect->first.get() << ";";
			cout << it_vect->second.get() << "\n";
		}
	}
	cout << "output_pictogrammes";
}

vectorMap input_pictogrammes(vectorMap map, string path) {
	string input_folder = path + "/input_pictogrammes/*";
	
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(ConvertToLPWSTR(input_folder), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		cout << "FindFirstFile failed " << GetLastError() << "\n";
		throw exception();
	} else {
		while (FindNextFile(hFind, &FindFileData) != 0) {
			string filename = "";
			cout << "File found: ";
			for (int i = 0; i < wcslen(FindFileData.cFileName); ++i) {
				cout << char(FindFileData.cFileName[i]);
				filename += char(FindFileData.cFileName[i]);
			}
			if (FindFileData.dwFileAttributes == 32) {
				cout << " FILE!";
				std::vector<std::pair<reference_wrapper<Point2f>, reference_wrapper<Point2f>>> vect;
				map.insert(make_pair(filename, vect));
			}
			cout << "\n";
		}
		FindClose(hFind);
	}
	return map;
}