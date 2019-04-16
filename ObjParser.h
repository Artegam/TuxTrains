
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Objet3D.h"
#include <fstream>
#include <iostream>

class ObjParser {

private:
	vector<Objet3D> objets;
	Objet3D * vObj;

public:

	//ObjParser();
	//~ObjParser();
	vector<Objet3D> readFile (const char * filename);

};
