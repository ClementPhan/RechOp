#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "../data_types.h"

using namespace std;


vector<int> split(const string& s, char delimiter);

vector<vector<int> > lecture(string adresse, vector<int>& instances, vector<int> &usine, vector<int> &depot, vector<fournisseur> &fournisseurs);

void ecriture(vector<vector <int> > A);
