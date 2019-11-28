#include "parseur.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


vector<int> split(const string& s, char delimiter){
   vector<int> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream,token,delimiter)){
       if (((int(token[0])>=48)&&(int(token[0]))<=57))  ////// Si c'est pas un chiffre : On ballec
       {
       int a = atof(token.c_str());    //
       tokens.push_back(a);
       }     //  C'est ici qu'il faut checker.
   }
   return(tokens);
}


vector<vector<int> > lecture(string adresse, vector<int>& instances,vector<int>& usine,vector<int>& depot,vector<vector<int> >& fournisseur){       // lire le fichier et stocker les variables dans les vecteurs.
    ifstream myflux(adresse.c_str());
    if (myflux){
        string ligne;
        getline(myflux,ligne);
        cout<<"première ligne : "<<ligne<<endl;
        instances=split(ligne,' ');   //////////   Definition des instances  //////////
        vector<vector<int> > A;
        int j=0,i=0;
        while (getline(myflux,ligne)&&ligne[0]=='f'){
            fournisseur.resize(j+1);
            fournisseur[j]=split(ligne,' ');
        }
        A.resize(1);
        A[0]=split(ligne,' ');
        i++;
        while (getline(myflux,ligne)){
              A.resize(i+1);                             // lecture de toute les lignes
              A[i]=split(ligne,' ');     // A[i] doit être la ligne d'instance
              i++;
        }
        cout<<(A.size())<<endl;
        return(A);
    }
    else {
        cout<<"impossible de lire le fichier"<<endl;
        vector<vector<int> > A;
        return(A);
    }
}


void ecriture(vector<vector<int> > A){
    string const nomFichier("C:/Users/hugues/Desktop/solution.txt");
    ofstream monFlux(nomFichier.c_str());
    for (int i=0;i<A.size();i++){
        for (int j=0;j<A[i].size();j++){
            monFlux<<A[i][j]<<" ";
        }
        monFlux<<endl;
    }

}
