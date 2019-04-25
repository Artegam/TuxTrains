
#include <stdio.h>
#include <cstring>
#include <vector>
#include "Material.h"
#include <fstream>
#include <iostream>

/*
	- newmtl name
	- Ns double
	- Ka double double double
	- Kd double double double
	- Ks double double double
	- Ni double
	- d double
	- illum int
	- map_Kd (char*) chemin complet.jpg

*/

using namespace std;

class MatParser {

protected:
	Material * vMat;
	vector<Material> materials;
  vector<string> fichierRAM;
  map<string, Material> materiaux;

public:
  void parserFichier(void);
  vector<string> getTokens(vector<string>::iterator it);
  vector<Material> readFile (const char * filename);
};
