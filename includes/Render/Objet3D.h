#ifndef OBJET3D
#define OBJET3D

#include <vector>
#include <map>
#include <algorithm>    // std::for_each
#include <stdio.h>
#include <cstring>
#include <string>

#include "Element3D.h"

using namespace std;

class Objet3D {

	protected:
		string nom;
		map<string, Element3D> elements;
    GLuint listeAffichage; // A Reflechir...
/*
    float angle = 0.0;
    double facteurX = 0.0;
    double step = 0.05;
*/
	public:
    Objet3D();
    Objet3D(const char* pNom);

		void setNom(const char* pNom);
		string getNom();

    void setElements(map<string,Element3D> pElements);
    Element3D getElement3D(char* nom);

    Vertex calculerBarycentre();

    void init();
		void dessiner();
};

#endif
