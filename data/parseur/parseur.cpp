#include "parseur.h"


vector<int> split(const string& s, char delimiter){
   vector<int> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream,token,delimiter)){
       if ((((int(token[0])>=48)&&(int(token[0]))<=57)) || (int(token[0]==45)))  ////// Si c'est pas un chiffre : On ballec
       {
       int a = atof(token.c_str());    //
       tokens.push_back(a);
       }     //  C'est ici qu'il faut checker.
   }
   return(tokens);
}


vector<vector<int> > lecture(string adresse, vector<int>& instances,vector<int>& usine,vector<int>& depot,vector<fournisseur>& fournisseurs){       // lire le fichier et stocker les variables dans les vecteurs.
    ifstream myflux(adresse.c_str());
	vector<vector<int> > A;

    if (myflux){
        string ligne;
        getline(myflux,ligne);
        cout<<"première ligne : "<<ligne<<endl;
        instances=split(ligne,' ');   //////////   Definition des instances  //////////
        getline(myflux,ligne);
        depot = split(ligne,' ');
        getline(myflux,ligne);
        usine = split(ligne,' ');

		fournisseur temp_fournisseur;
		vector<int> temp_vect;

        int j=0,i=0;
        while ((getline(myflux,ligne))&&(ligne[0]=='f')){
			// Les deux premiers éléments sont l'indice et le prix, les deux derniers sont les coordonnées GPS
			temp_vect = split(ligne, ' ');
			temp_fournisseur.indice = temp_vect[0];
			temp_fournisseur.prix_sous_traitance = temp_vect[1];
			temp_fournisseur.quantites = vector<int>(temp_vect.begin()+2,temp_vect.begin()+2+instances[2]);
			fournisseurs.push_back(temp_fournisseur);
            j++;
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
    }
    else {
        cout<<"impossible de lire le fichier"<<endl;
    }
	return(A);
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
