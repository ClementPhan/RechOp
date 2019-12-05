#pragma once

struct tournee {
	int groupe;
	int semaine;
	int nombre_de_fournisseurs;
	int fournisseurs[6];
	int quantite[6];
};

struct groupe {
	int indice_du_groupe;
	int nombre_de_fournisseurs;
	int fournisseurs[4];
};
