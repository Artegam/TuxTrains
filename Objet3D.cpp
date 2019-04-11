

#include "Objet3D.h"
#include <stdio.h>


void afficherVertex(Vertex& v);

char* Objet3D::getNom() {
	return nom;
}

void Objet3D::setNom(char* pNom) {
	nom = pNom;
}

void Objet3D::ajouterVertex(double pX, double pY, double pZ, double pW){
	Vertex * v = new Vertex();

	v->setX(pX);
	v->setY(pY);
	v->setZ(pZ);
	if (pW > 0) v->setW(pW);

	vertices.insert(vertices.end(), *v);
}

void Objet3D::ajouterVertexNormal(double pX, double pY, double pZ, double pW){
	VertexNormal * vn = new VertexNormal();

	vn->setX(pX);
	vn->setY(pY);
	vn->setZ(pZ);
	if (pW > 0) vn->setW(pW);
	//printf("Vn %lf %lf %lf \n", pX, pY, pZ);
	verticesNormal.insert(verticesNormal.end(), *vn);
}

void Objet3D::ajouterFace(int nbParametres, char** parametres){

	int numVertex[4];
	int numVertexTexture[4];
	int numVertexNormal[4];
	int nbVertexInfo;
	int numCas;


	if (nbParametres > 0) {

		Face f;

		for(int cpt = 0; cpt < nbParametres;cpt++) {
			numCas = 0;
			nbVertexInfo = sscanf(parametres[cpt], "%d//%d", &numVertex[cpt], &numVertexNormal[cpt]);
			switch(nbVertexInfo){
				case 1:
					nbVertexInfo = sscanf(parametres[cpt], "%d/%d/%d", &numVertex[cpt], &numVertexTexture[cpt], &numVertexNormal[cpt]);
					numCas = nbVertexInfo;
					break;

				case 2:
					numCas = 4;
					break;
			}

			switch(numCas){
				case 1: // cas v
					f.ajouterNumVertex(numVertex[cpt]);
					break;

				case 2: // cas v/vt
					f.ajouterNumVertex(numVertex[cpt]);
					f.ajouterNumVertexTexture(numVertexTexture[cpt]);
					break;

				case 3: // cas v/vt/vn
					f.ajouterNumVertex(numVertex[cpt]);
					f.ajouterNumVertexTexture(numVertexTexture[cpt]);
					f.ajouterNumVertexNormal(numVertexNormal[cpt]);
					break;

				case 4: // cas v//vn
					f.ajouterNumVertex(numVertex[cpt]);
					f.ajouterNumVertexNormal(numVertexNormal[cpt]);
					break;
			}

		}
		faces.insert(faces.end(), f);
	}
}


void afficherVertex(Vertex& v) {
	v.dessiner();
}


void Objet3D::dessiner() {

	vector<Face>::iterator it;

	//if (faces.size() > 0) printf("%s nb de faces : %d\n", nom, faces.size());
	for(it = faces.begin(); it != faces.end(); it++) {
		it->dessiner(vertices, verticesNormal);
	}

}
