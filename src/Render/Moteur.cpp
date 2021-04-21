#include "Moteur.h"
#include "Loader.h"
#include <math.h>

Moteur::Moteur(const char* objPath){
  Loader *l = new Loader(objPath, false);
  objets = l->getObjets(); //Charge tous les objets dans la scene en 3D
  files = l->getFiles();
}
/*
void Moteur::ajouter(vector<Objet3D> lst) {
  //Not implemented yet !!!
}
*/
void Moteur::tic() {
  vector<Objet3D>::iterator it;
  list<vector<Objet3D>>::iterator itf;

  for(itf = files.begin(); itf != files.end(); itf++) {
    for(it = itf->begin(); it != itf->end(); it++) {
      it->dessiner(); //ou animer();
    }
  }

}

void Moteur::init() {
  vector<Objet3D>::iterator it;
  list<vector<Objet3D>>::iterator itf;

  for(itf = files.begin(); itf != files.end(); itf++) {
    for(it = itf->begin(); it != itf->end(); it++) {
      it->init(); //ou animer();
    }
  }

}

