
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Objet3D.h"
#include <fstream>
#include <iostream>

class ObjParser {

protected:
	vector<Objet3D> objets;
	Objet3D * vObj;
  vector<string> fichierRAM;

public:

	vector<Objet3D> readFile (const char * filename);
  void parserFichier(void);
  vector<string> getTokens(vector<string>::iterator it);

};
