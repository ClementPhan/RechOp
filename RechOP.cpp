﻿// RechOP.cpp : Defines the entry point for the application.
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

int score(vector<tournee> tournees, vector<int> fournisseurs_sous_traites, vector<vector<int>> fournisseurs, vector<vector<int>> A) {
	int cout = 0;
	for (int i = 0; i < fournisseurs_sous_traites.size(); i++) {
		cout += fournisseurs[fournisseurs_sous_traites[i]][1];
	}
	
	for(int i = 0; i < tournees.size(); i++) {
		for (int j = 0; j < tournees[i].nombre_de_fournisseurs; i++) {
			cout += A[tournees[i].fournisseurs[j]][tournees[i].fournisseurs[j+1]];
		}
	}
	
	return cout;
}


int main()
{
	// PARSAGE
	vector<int> instances, usine, depot;
	vector<vector<int>> fournisseur, A;
	string adresse = "C:/instance-propre.txt";

	A = lecture(adresse, instances, usine, depot, fournisseur);

	// TRAINTEMENT INITIAL
	vector<tournee> tournees;
	vector<tournee> groupe;
	vector<int> fournisseurs_sous_traites;

	// CALCUL 
	return 0;
}
