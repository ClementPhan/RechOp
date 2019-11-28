#include <iostream>
#include "parseur.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
using namespace std;

/////////////////////////////  SI les instances sont à virgule utiliser atof  //////////////
/// \brief main
/// \return



int main()
{
    string const adresse="C:/Users/hugues/Desktop/RechOp/Instance-propre.in";
    vector<int> instances;
    vector<int> usine;
    vector<int> depot;
    vector<vector<int> > fournisseur;
    vector<vector<int> > A=lecture(adresse,instances,usine,depot,fournisseur);
    cout<<instances[0]<<endl;
    /*  CODER  */
    for (int i=0;i<A.size();i++){
        cout<<A[i][0]<<" "<<A[i].size()<<endl;
    }

    ecriture(A);
    return 0;
}
