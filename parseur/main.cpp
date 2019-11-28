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
    string const adresse="C:/Users/hugues/Desktop/KIRO/inst.in";
    vector<int> instances;
    vector<vector<int> > A=lecture(adresse, instances);

    /*  CODER  */

    ecriture(A);
    return 0;
}
