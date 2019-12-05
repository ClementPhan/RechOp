#pragma once

#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "data/data_types.h"

using namespace std;

vector<vector <int> > adj(vector<vector<int> > fournisseur, vector<vector<int> > A);

void generation(vector<groupe>& groupes, vector<vector<int> >& fournisseur);

bool nettoyage(vector<int> a);

int cogroupe(groupe a, vector<vector<int> > A);

void optimisation(vector<groupe>& groupes, vector<vector<int> > A);

void chemins_dans_un_groupe(vector<tournee>& tournees, groupe groupe_fixe, vector<int> usine, vector<int> depot, vector<vector<int>> fournisseur, vector<vector<int>> A, int semaines);