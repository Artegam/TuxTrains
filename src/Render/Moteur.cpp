#include "Moteur.h"
#include "Loader.h"
#include <math.h>

Moteur::Moteur(const char* objPath){
  Loader *l = new Loader(objPath, false);
  objets = l->getObjets(); //Charge tous les objets dans la scene en 3D
}
/*
void Moteur::ajouter(vector<Objet3D> lst) {
  //Not implemented yet !!!
}
*/
void Moteur::tic() {
  vector<Objet3D>::iterator it;
  glTranslatef(-0.01, 0.0, 0.0);
  for(it = objets.begin(); it != objets.end(); it++) {
      it->dessiner(); //ou animer();
  }
}

void Moteur::init() {
  vector<Objet3D>::iterator it;

  for(it = objets.begin(); it != objets.end(); it++) {
    it->init(); //ou animer();
  }
}

