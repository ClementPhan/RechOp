#include "traitement.h"

vector<vector <int> > adj(vector<fournisseur> fournisseurs, vector<vector<int> > A) {
	vector<vector<int> > adj;
	int n = fournisseurs.size() + 2;
	adj.resize(n);
	for (int i = 0; i < n; i++) {
		adj[i].resize(n);
	}
	for (int j = 0; j < A.size(); j++) {
		adj[A[j][0]][A[j][1]] = A[j][2];
	}
	return(adj);
}

void generation(vector<groupe>& groupes, vector<fournisseur>& fournisseurs) {
	int taille = 0;
	for (int i = 0; i < fournisseurs.size();) {
		groupe a;
		a.nombre_de_fournisseurs = rand() % 4 + 1;
		for (int j = 0; j < a.nombre_de_fournisseurs; j++) {
			while ((nettoyage(fournisseurs[i])) && (i < fournisseurs.size() - 1)) i++;
			if (i < fournisseurs.size() - 1) { a.fournisseurs[j] = fournisseurs[i].indice; i++; }
			else { i++; break; }
		}
		a.indice_du_groupe = taille;
		taille++;
		groupes.resize(taille);
		groupes[taille - 1] = a;
	}
}

bool nettoyage(fournisseur a) {
	bool ok = true;
	for (int j = 0; j < a.quantites.size(); j++) {
		if (a.quantites[j] != 0) {
			return(false);
		}
	}
	return(true);
}

int cogroupe(groupe a, vector<vector<int> > A) {
	int co = 0;
	for (int i = 0; i < a.nombre_de_fournisseurs - 1; i++) {
		for (int j = 1; j < a.nombre_de_fournisseurs; j++) {
			co = co + A[a.fournisseurs[i]][a.fournisseurs[j]] + A[a.fournisseurs[j]][a.fournisseurs[i]];
		}
	}
	return(co);
}

void optimisation(vector<groupe>& groupes, vector<vector<int> > A) {
	for (int i = 0; i < 10000; i++) { 
		int p = rand() % groupes.size();
		int l = rand() % groupes.size();
		int a = rand() % groupes[p].nombre_de_fournisseurs;
		int b = rand() % groupes[l].nombre_de_fournisseurs;
		int cou1 = cogroupe(groupes[p], A) + cogroupe(groupes[l], A);
		swap(groupes[p].fournisseurs[a], groupes[l].fournisseurs[b]);
		int cou2 = cogroupe(groupes[p], A) + cogroupe(groupes[l], A);
		if (cou1 > cou2) {
			swap(groupes[p].fournisseurs[a], groupes[l].fournisseurs[b]);
		}
		if (i % 1000 == 0) {
			cout << i << endl;
		}
	}
}


void chemins_dans_un_groupe(vector<tournee>& tournees, groupe groupe_fixe, vector<int> usine, vector<int> depot, vector<fournisseur> fournisseurs, vector<vector<int>> A, int semaines) {
	// trajet A/R minimum
	int capacite = 13; // On suppose une quantité de 13

	int place_libre;
	int i = 0;
	int j = 0;
	tournee temp_tournee;

	vector<vector<int>> paires(groupe_fixe.nombre_de_fournisseurs, vector<int>(3)); // On cree 4 vecteurs de 3 de long

	for (int s = 0; s < semaines; s++) { // Pour chaque semaine
		i = 0;
		j = 0;
		for (int l = 0; l < groupe_fixe.nombre_de_fournisseurs; l++) {
			paires[l][0] = l; // position dans groupe_fixe.fournisseurs
			paires[l][1] = A[depot[0]][groupe_fixe.fournisseurs[l]] + A[groupe_fixe.fournisseurs[l]][usine[0]]; // cout d'un aller retour
			paires[l][2] = fournisseurs[groupe_fixe.fournisseurs[l]].quantites[s]; // quantité a recuperer
		}

		std::sort(paires.begin(), paires.end(), [](vector<int> a, vector<int> b) {
			return (a[1] < b[1]);
			});

		temp_tournee.semaine = s;
		temp_tournee.groupe = groupe_fixe.indice_du_groupe;
		temp_tournee.quantite;

		while (i < groupe_fixe.nombre_de_fournisseurs) { //  tant que tous les fournisseurs n'ont pas été vidés
			if (paires[i][2] == 0) { // si le fournisseur actuel n'a pas besoin d'etre visité, on passe au suivant
				i++;
			}
			else { // Il faut passer par le fourniseur
				place_libre = capacite;
				j = 0;
				while ((place_libre != 0) && (i < groupe_fixe.nombre_de_fournisseurs)) { // On lance un camion, il tourne tant qu'il n'est pas rempli
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
				temp_tournee.nombre_de_fournisseurs = j;
				if (j != 0) {
					tournees.push_back(temp_tournee);
				}
			}
		}
	}
}