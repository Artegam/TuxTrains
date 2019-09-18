#include "Moteur.h"


void Moteur::ajouter(Objet3D obj) {
  //Not implemented yet !!!
}

void Moteur::ajouter(vector<Objet3D> lst) {
  //Not implemented yet !!!
}

void Moteur::tic() {
  //Not implemented yet !!!
  vector<Objet3D>::iterator it;

  for(it = listeObjets.begin(); it != listeObjets.end(); it++) {
    it->dessiner(); //ou animer();
  }
}

