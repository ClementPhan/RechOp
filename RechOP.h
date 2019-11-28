// RechOP.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "parseur/parseur.h"
//#include "output.h"

// TODO: Reference additional headers your program requires here.


struct tournee {
	int groupe;
	int semaine;
	int nombre_de_fournisseurs;
	int fournisseurs[6];
};

struct groupe {
	int nombre_de_fournisseurs;
	int fournisseurs[4];
};