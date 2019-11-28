// RechOP.cpp : Defines the entry point for the application.
//

#include "RechOP.h"

int output(vector<tournee> tournees, vector<groupe> groupes, vector<int> fournisseurs_sous_traites) {

	string const nomFichier("C:/Users/hugues/Desktop/KIRO/solution.txt");
	ofstream monFlux(nomFichier.c_str());

	// Sous-traitants
	monFlux << "x" << fournisseurs_sous_traites.size() << " f";
	for (int i = 0; i < fournisseurs_sous_traites.size(); i++) {
		monFlux << " " << fournisseurs_sous_traites[i];
	}
	monFlux << std::endl;

	// Nombre de Tournées
	monFlux << "y " << tournees.size() << std::endl;
	
	// Groupes
	monFlux << "z " << groupes.size() << std::endl;

	for (int i = 0; i < groupes.size(); i++) {
		monFlux << "C " << i << " n " << groupes[i].nombre_de_fournisseurs << " f";
		for (int j = 0; j < groupes[i].nombre_de_fournisseurs; j++) {
			monFlux << " " << groupes[i].fournisseurs;
		}
		monFlux << std::endl;
	}

	// Tournées
	for (int i = 0; i < tournees.size(); i++) {
		monFlux << "P " << i << " g " << tournees[i].groupe << " s " << tournees[i].semaine << " n " << tournees[i].semaine << " n " << tournees[i].nombre_de_fournisseurs;
		for (int j = 0; j < tournees[i].nombre_de_fournisseurs; j++) {
			monFlux << " " << tournees[i].fournisseurs;
		}
		monFlux << std::endl;
	}

	return 0;
}

vector<vector <int> > adj(vector<vector<int> > fournisseur,vector<vector<int> > A){
    vector<vector<int> > adj;
    int n=fournisseur.size()+2;
    adj.resize(n);
    for (int i=0;i<n;i++){
        adj[i].resize(n);
    }
    for (int j=0;j<A.size();j++){
        adj[A[j][0]][A[j][1]]=A[j][2];
    }
    return(adj);
}



int main()
{
	// PARSAGE

	// TRAINTEMENT INITIAL
	vector<tournee> tournees;
	vector<tournee> groupe;
	vector<int> fournisseurs_sous_traites;


	// CALCUL 

    for (int i=0;i<fournisseur.)

	return 0;
}
