
#define PARSEUR_H
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


vector<int> split(const string& s, char delimiter);

vector<vector<int> > lecture(string adresse,vector<int>& instances);

void ecriture(vector<vector <int> > A);
