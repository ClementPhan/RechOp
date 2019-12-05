#pragma once

#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "data/data_types.h"

using namespace std;

vector<vector <int> > adj(vector<fournisseur> fournisseurs, vector<vector<int> > A);

void generation(vector<groupe>& groupes, vector<fournisseur >& fournisseur);

bool nettoyage(fournisseur a);

int cogroupe(groupe a, vector<vector<int> > A);

void optimisation(vector<groupe>& groupes, vector<vector<int> > A);

void chemins_dans_un_groupe(vector<tournee>& tournees, groupe groupe_fixe, vector<int> usine, vector<int> depot, vector<fournisseur> fournisseurs, vector<vector<int>> A, int semaines);