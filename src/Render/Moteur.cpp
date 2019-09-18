#include "Moteur.h"


void Moteur::ajouter(Objet3D obj) {
  //Not implemented yet !!!
}

void Moteur::ajouter(vector<Objet3D> lst) {
  //Not implemented yet !!!
}

void Moteur::tic() {
  //Not implemented yet !!!
  for(it = listeObjets.begin(); it != listeObjets.end(); it++) {
    it->desssiner(); //ou animer();
  }
}

