#include "Moteur.h"
#include "Loader.h"
#include <math.h>


Moteur::Moteur(){
  Loader *l = new Loader(defaultPath, false);
  objets = l->getObjets(); //Charge tous les objets dans la scene en 3D
}

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
  map <string,Objet3D>::iterator it;

  for(it = objets.begin(); it != objets.end(); it++) {
    it->second.dessiner(); //ou animer();
  }

}

void Moteur::init() {
  map <string,Objet3D>::iterator it;

  for(it = objets.begin(); it != objets.end(); it++) {
    it->second.init(); //ou animer();
  }

}

Objet3D Moteur::getObjet3D(string nom) {
  return objets[nom];
}

