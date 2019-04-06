
#include <stdio.h>
#include <cstring>
#include <vector>
#include "Objet3D.h"


class ObjParser {

private:
	vector<Objet3D> objets;
	Objet3D * vObj;

public:
	
	//ObjParser();
	//~ObjParser();
	vector<Objet3D> readFile (const char * filename);
	void readVertex(FILE* fichier);
	void readVertexNormal(FILE* fichier);
	void readObject(FILE* fichier);
	void readFace(FILE* fichier);
	void readMaterialLib(FILE* fichier);
	void readMateriaUsed(FILE* fichier);

};
