#pragma once
#include <vector>

struct tournee {
	int groupe;
	int semaine;
	int nombre_de_fournisseurs;
	int fournisseurs[4];
	int quantite[4];
};

struct groupe {
	int indice_du_groupe;
	int nombre_de_fournisseurs;
	int fournisseurs[4];
};

struct fournisseur {
	int indice;
	int prix_sous_traitance;
	std::vector<int> quantites;
};
