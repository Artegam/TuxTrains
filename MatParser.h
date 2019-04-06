
#include <stdio.h>
#include <cstring>
#include <vector>
#include "Material.h"

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

class MatParser {

private:
	vector<Material> materials;
	Material * vMat;

public:
	
	vector<Material> readFile (const char * filename);
	/*
	void readVertex(FILE* fichier);
	void readVertexNormal(FILE* fichier);
	void readObject(FILE* fichier);
	void readFace(FILE* fichier);
	void readMaterialLib(FILE* fichier);
	void readMateriaUsed(FILE* fichier);
	*/
};
