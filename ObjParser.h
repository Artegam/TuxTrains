
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Objet3D.h"
#include <boost/regex.hpp>
#include <fstream>
#include <iostream>

class ObjParser {

private:
	vector<Objet3D> objets;
	Objet3D * vObj;

  char** getMatchedChar(cmatch m);
  double* getMatchedDouble(cmatch sm);

public:

	//ObjParser();
	//~ObjParser();
	vector<Objet3D> readFile (const char * filename);

};
