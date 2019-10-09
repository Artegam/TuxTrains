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
  //Not implemented yet !!!
  vector<Objet3D>::iterator it;
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslatef(-0.01, 0.0, 0.0);
  for(it = objets.begin(); it != objets.end(); it++) {
    //printf("%s\n", it->getNom().c_str());
//glPushMatrix();
//    if(it->getNom() != "Chaudiere_Circle.001") {
      it->dessiner(); //ou animer();
//    }
//glPopMatrix();

  }

  glutPostRedisplay();
}

void Moteur::init() {
  //Not implemented yet !!!
  vector<Objet3D>::iterator it;

  for(it = objets.begin(); it != objets.end(); it++) {
    it->init(); //ou animer();
  }
}

