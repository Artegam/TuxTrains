
#include "ObjParser.h"

#include <regex>
#include <iostream>

//ASCH - 17/10/2014 - Paramètres



//ASCH - 17/10/2014 - Méthodes
vector<Objet3D> ObjParser::readFile (const char * filename) {

	FILE* fichier;
	char ligne[255];
	int selection = 0;


  // Ca fonctionne (version 7 installÃe a la maison)
if (regex_match("a", regex("[0-9]"))) {
    cout << "c'est un chiffre !!" << endl;
}else {
    cout << "c'est PAS un chiffre !!" << endl;
}

	fichier = fopen(filename, "r");

	while(!feof(fichier)) {
    fscanf(fichier, "%[^\n]\n", ligne);
		selection = 0;

    cout << ":" << ligne << endl;

		if(strcmp((const char*)ligne, (char*)"v") == 0) {
			selection = 1;
		}

		if(strcmp((const char*)ligne, (char*)"vn") == 0) {
			selection = 2;
		}

		if(strcmp((const char*)ligne, (char*)"o") == 0) {
			selection = 3;
		}

		if(strcmp((const char*)ligne, (char*)"f") == 0) {
			selection = 4;
		} 

		if(strcmp((const char*)ligne, (char*)"mtllib") == 0) {
			selection = 5;
		} 

		if(strcmp((const char*)ligne, (char*)"usemtl") == 0) {
			selection = 6;
		} 


		switch(selection) {

			//ASCH - 16/10/2014 - Le cas du vertex
			case 1:
				readVertex(fichier);
				break;

			case 2:
				readVertexNormal(fichier);
				break;

			case 3:
				readObject(fichier);
				break;

			case 4:
				readFace(fichier);
				break;

			case 5:
				readMaterialLib(fichier);
				break;

			case 6:
				readMateriaUsed(fichier);
				break;
		}
	}
	fclose(fichier);
	return objets;
}

void ObjParser::readVertex(FILE* fichier){

	double x;
	double y;
	double z;
	double w;

	fscanf(fichier, "%lf %lf %lf %lf", &x, &y, &z, &w);
	objets[objets.size()-1].ajouterVertex(x, y, z, w);
}

void ObjParser::readVertexNormal(FILE* fichier){

	double x;
	double y;
	double z;
	double w;

	fscanf(fichier, "%lf %lf %lf %lf", &x, &y, &z, &w);
	objets[objets.size()-1].ajouterVertexNormal(x, y, z, w);
}

void ObjParser::readObject(FILE* fichier){

	char nom[255];
	vObj = new Objet3D();
	vector<Objet3D>::iterator it;
	
	fscanf(fichier, "%s", nom);
	
	vObj->setNom(nom);
	objets.insert(objets.begin(), *vObj);
	printf("\t - %s\n", nom);
}

void ObjParser::readFace(FILE* fichier) {

	char parametres[4][50];
	int numVertex[4];
	int numVertexTexture[4];
	int numVertexNormal[4];
	int nbParametres;
	int nbVertexInfo;
	
	nbParametres = fscanf(fichier, "%s %s %s %s", parametres[0], parametres[1], parametres[2], parametres[3]);
	objets[objets.size()-1].ajouterFace(nbParametres, parametres);

}

void ObjParser::readMaterialLib(FILE* fichier) {

	char nomLib[255];

	fscanf(fichier, "%s", nomLib);
	printf("Nom de la librairie de maetriaux : %s\n", nomLib);

}

void ObjParser::readMateriaUsed(FILE* fichier) {

	char nomMat[255];

	fscanf(fichier, "%s", nomMat);
	printf("materiaux utilise: %s\n", nomMat);

}

