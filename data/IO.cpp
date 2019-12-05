#include "IO.h"

int output(vector<tournee> tournees, vector<groupe> groupes, vector<int> fournisseurs_sous_traites) {

	string const nomFichier(desktop_path()+"\\rechop\\solution.txt");
	ofstream monFlux(nomFichier.c_str());

	// Sous-traitants
	monFlux << "x " << fournisseurs_sous_traites.size() << " f";
	for (int i = 0; i < fournisseurs_sous_traites.size(); i++) {
		monFlux << " " << fournisseurs_sous_traites[i];
	}
	monFlux << endl;


	monFlux << std::endl;

	// Nombre de Tournées
	monFlux << "y " << tournees.size() << std::endl;

	// Groupes
	monFlux << "z " << groupes.size() << std::endl;


	for (int i = 0; i < groupes.size(); i++) {
		monFlux << "C " << i << " n " << groupes[i].nombre_de_fournisseurs << " f";
		for (int j = 0; j < groupes[i].nombre_de_fournisseurs; j++) {
			monFlux << " " << groupes[i].fournisseurs[j];
		}
		monFlux << std::endl;
	}

	// Tournées
	for (int i = 0; i < tournees.size(); i++) {
		monFlux << "P " << i << " g " << tournees[i].groupe << " s " << tournees[i].semaine << " n " << tournees[i].nombre_de_fournisseurs;
		for (int j = 0; j < tournees[i].nombre_de_fournisseurs; j++) {
			monFlux << " f " << tournees[i].fournisseurs[j] << " " << tournees[i].quantite[j];
		}
		monFlux << std::endl;
	}

	return 0;
}

string desktop_path() {
	TCHAR myPath[MAX_PATH];	

	SHGetSpecialFolderPath(0, myPath, CSIDL_DESKTOPDIRECTORY, FALSE);

	return string(myPath);
}