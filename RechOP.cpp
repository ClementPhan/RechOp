// RechOP.cpp : Defines the entry point for the application.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RechOP.h"
#include <algorithm>

int output(vector<tournee> tournees, vector<groupe> groupes, vector<int> fournisseurs_sous_traites) {

	string const nomFichier("C:/Users/hugues/Desktop/KIRO/solution.txt");
	ofstream monFlux(nomFichier.c_str());

	// Sous-traitants
    monFlux << "x " << fournisseurs_sous_traites.size() << " f";
	monFlux << "x " << fournisseurs_sous_traites.size() << " f";
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

bool netoyage(vector<int> a){
        bool ok=true;
        for (int j=2;j<10;j++){
            if (a[j]!=0){
                return(false);}
        }
        return(true);
}

void generation(vector<groupe>& groupes,vector<vector<int> >& fournisseur){
    int taille=0;
    for (int i=0;i<fournisseur.size();){
        groupe a;
        a.nombre_de_fournisseurs=rand()%4+1;
        for (int j=0;j<a.nombre_de_fournisseurs;j++){
            while ((netoyage(fournisseur[i]))&&(i<fournisseur.size()-1)) i++;
            if (i<fournisseur.size()-1) {a.fournisseurs[j]=fournisseur[i][0];i++;}
            else {i++;break;}
        }
        taille++;
        groupes.resize(taille);
        groupes[taille-1]=a;
    }   
}
int cogroupe(groupe a,vector<vector<int> > A){
    int co=0;
    for (int i=0;i<a.nombre_de_fournisseurs-1;i++){
        for (int j=1;j<a.nombre_de_fournisseurs;j++){
            co=co+A[a.fournisseurs[i]][a.fournisseurs[j]]+A[a.fournisseurs[j]][a.fournisseurs[i]];
        }
    }
    return(co);
}

void optimisation(vector<groupe>& groupes, vector<vector<int> > A){
    for (int i=0;i<10000;i++){
        int p=rand()%groupes.size();
        int l=rand()%groupes.size();
        int a=rand()%groupes[p].nombre_de_fournisseurs;
        int b=rand()%groupes[l].nombre_de_fournisseurs;
        int cou1=cogroupe(groupes[p],A)+cogroupe(groupes[l],A);
        swap(groupes[p].fournisseurs[a],groupes[p].fournisseurs[a]);
        int cou2=cogroupe(groupes[p],A)+cogroupe(groupes[l],A);
        if (cou1>cou2){
            swap(groupes[p].fournisseurs[a],groupes[p].fournisseurs[a]);
        }
        cout<< cou1<<" "<<cou2<<endl;
    }
}


void chemins_dans_un_groupe(vector<tournee> &tournees, groupe groupe_fixe, vector<int> usine, vector<int> depot, vector<vector<int>> fournisseur, vector<vector<int>> A, int semaines) {
	// trajet A/R minimum
	int capacite = 13; // On suppose une quantité de 13

	int place_libre;
	int i = 0;
	int j = 0;
	tournee temp_tournee;

	vector<vector<int>> paires(4, vector<int>(3)); // On cree 4 vecteurs de 3 de long

	for (int s = 0; s < semaines; s++) {
		

		for (int i = 0; i < groupe_fixe.nombre_de_fournisseurs; i++) {
			paires[i][0] = i; // position dans groupe_fixe.fournisseurs
			paires[i][1] = A[depot[0]][groupe_fixe.fournisseurs[i]] + A[groupe_fixe.fournisseurs[i]][usine[0]]; // cout d'un aller retour
			paires[i][2] = fournisseur[groupe_fixe.fournisseurs[i]][2 + s]; // quantité a recuperer
		}

		std::sort(paires.begin(), paires.end(), [](vector<int> a, vector<int> b) {
			return (a[1] < b[1]);
			});

		temp_tournee.semaine = s;
		temp_tournee.nombre_de_fournisseurs = groupe_fixe.nombre_de_fournisseurs + 2;
		temp_tournee.groupe = groupe_fixe.indice_du_groupe;

		while (i < groupe_fixe.nombre_de_fournisseurs) { //  tant que tous les fournisseurs n'ont pas été vidés
			if (paires[i][2] == 0) { // si le fournisseur actuel n'a pas besoin d'etre visité, on passe au suivant
				i++;
			}
			else { // Il faut passer par le fourniseur
				place_libre = capacite;
				while ((place_libre != 0) && (i < groupe_fixe.nombre_de_fournisseurs)) { // On lance un camion, il tourne tant qu'il n'est pas rempli
					j = 0;
					if (paires[i][2] >= place_libre) { // Si un camion serait totalement rempli
						temp_tournee.fournisseurs[j] = groupe_fixe.fournisseurs[paires[i][0]];
						temp_tournee.quantite[j] = place_libre;
						paires[i][2] -= place_libre;
						place_libre = 0;
					}
					else { // Si il reste de la place dans un camion, on le remplit et on passe au fournisseur suivant (i++)
						temp_tournee.fournisseurs[j] = groupe_fixe.fournisseurs[paires[i][0]];
						temp_tournee.quantite[j] = min(paires[i][2], place_libre); // On remplit le camion au maximum
						place_libre = max(place_libre - paires[i][2], 0);
						paires[i][2] = 0;
						i++; //On passe au fournisseur suivant
						j++;
					}
				}
				tournees.push_back(temp_tournee);
			}
		}
	}
}

int main()
{
    srand(time(NULL));
	// PARSAGE
	vector<int> instances, usine, depot;
    vector<vector<int> > fournisseur, A;
    string adresse = "C:/Users/hugues/Desktop/RechOp/Instance-plus-propre.csv";

	A = lecture(adresse, instances, usine, depot, fournisseur);

	// TRAINTEMENT INITIAL
	vector<tournee> tournees;
    vector<groupe> groupes;
	vector<int> fournisseurs_sous_traites;


	// CALCUL 
    cout<<A.size()<<endl;
    for (int i=0;i<fournisseur.size();i++){
        fournisseurs_sous_traites.resize(i+1,i);
    }
    vector<vector<int> > ad=adj(fournisseur,A);

    generation(groupes,fournisseur);
    cout<<"ok"<<endl;
    cout<<groupes.size()<<endl;
    optimisation(groupes,ad);
    return output(tournees,groupes,fournisseurs_sous_traites);
}
