

#include "Objet3D.h"
#include <stdio.h>
#include <math.h>

//test pour les fichiers tildeÃ©s
void afficherVertex(Vertex& v);

Objet3D::Objet3D() {
  setNom("unamed");
}

Objet3D::Objet3D(const char* pNom) {
  setNom(pNom);
}

string Objet3D::getNom() {
	return nom;
}

void Objet3D::setNom(const char* pNom) {
	nom = pNom;
}

Element3D Objet3D::getElement3D(char* nom){
  return elements[nom];
}

void Objet3D::setElements(map<string,Element3D> pElements) {
  this->elements = pElements;
}


void Objet3D::init() {
  printf("Objet %s \n", nom.c_str());

  map <string,Element3D>::iterator it;

  for(it = this->elements.begin(); it != this->elements.end(); it++) {
    it->second.init(); //ou animer();
  }


}

void Objet3D::dessiner() {
  map <string,Element3D>::iterator it;

  for(it = elements.begin(); it != elements.end(); it++) {
    it->second.dessiner(); //ou animer();
  }

}

Vertex Objet3D::calculerBarycentre() {

  Vertex barycentre;
  /*
  unsigned int nbPts = vertices.size();

  double sommeX = 0.0;
  double sommeY = 0.0;
  double sommeZ = 0.0;

  map<int, Vertex>::iterator it;


  for(it = vertices.begin(); it != vertices.end(); it++) {
    sommeX += it->second.getX();
    sommeY += it->second.getY();
    sommeZ += it->second.getZ();
  }

  barycentre.setX(sommeX/nbPts);
  barycentre.setY(sommeY/nbPts);
  barycentre.setZ(sommeZ/nbPts);
*/
  // TODO: A implementer
  printf("To be implemented...\n");
  return barycentre;
}

