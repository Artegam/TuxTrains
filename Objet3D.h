#ifndef OBJET3D
#define OBJET3D

#include <vector>
#include <algorithm>    // std::for_each
#include <stdio.h>
#include <string>

#include "Vertex.h"
#include "VertexNormal.h"
#include "Face.h"

using namespace std;

class Objet3D {

	private:
		char* nom;
		vector<Vertex> vertices;
		vector<VertexNormal> verticesNormal;
		vector<Face> faces;
    GLuint listeAffichage;

	public:
		char* getNom();
		void setNom(char* pNom);

		void ajouterVertex(double pX, double pY, double pZ, double pW);
		void ajouterVertexNormal(double pX, double pY, double pZ, double pW);
		void ajouterFace(const int nbParametres, char** parametres);

    void init();
		void dessiner();
};

#endif
