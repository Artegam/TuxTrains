#ifndef OBJET3D
#define OBJET3D

#include <vector>
#include <algorithm>    // std::for_each
#include <stdio.h>
#include <cstring>
#include <string>

#include "Vertex.h"
#include "VertexNormal.h"
#include "Face.h"
#include "Material.h"

using namespace std;

class Objet3D {

	protected:
		char* nom;
    Material mat;
		vector<Vertex> vertices;
		vector<VertexNormal> verticesNormal;
		vector<Face> faces;
    GLuint listeAffichage;

	public:
		void setNom(const char* pNom);
		void setMateriau(Material pMateriau);

		char* getNom();
    string getNomMateriau();
    Material getMateriau(void);

		void ajouterVertex(double pX, double pY, double pZ, double pW);
		void ajouterVertexNormal(double pX, double pY, double pZ, double pW);
		void ajouterFace(const int nbParametres, char** parametres);
    void ajouterFace(Face f);

    void init();
		void dessiner();
};

#endif
