// RechOP.cpp : Defines the entry point for the application.
//
#include "main.h"





int score(vector<tournee> tournees, vector<int> fournisseurs_sous_traites, vector<vector<int> > fournisseurs, vector<vector<int> > A) {
	int cout = 0;
	for (int i = 0; i < fournisseurs_sous_traites.size(); i++) {
		cout += fournisseurs[fournisseurs_sous_traites[i]][0];
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
    srand(time(NULL));
	// PARSAGE
	vector<int> instances, usine, depot;
    vector<vector<int> > A;
	vector<fournisseur> fournisseurs;
    const string adresse = desktop_path() + "\\rechop\\Instance-plus-propre.csv";

	A = lecture(adresse, instances, usine, depot, fournisseurs);

	// TRAINTEMENT INITIAL
	vector<tournee> tournees;
    vector<groupe> groupes;
	vector<int> fournisseurs_sous_traites;


	// CALCUL 
    cout<<A.size()<<endl;
    for (int i=0;i<fournisseurs.size();i++){
        fournisseurs_sous_traites.resize(i+1,i);
    }
    vector<vector<int> > ad=adj(fournisseurs,A);

    generation(groupes,fournisseurs);
    cout<<"ok"<<endl;
    cout<<groupes.size()<<endl;
    optimisation(groupes,ad);
	for (auto& i : groupes) {
		chemins_dans_un_groupe(tournees, i, usine, depot, fournisseurs, ad, instances[2]);
	}
    return output(tournees,groupes,fournisseurs_sous_traites);
}
