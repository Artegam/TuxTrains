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
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslatef(-0.01, 0.0, 0.0);
  for(it = objets.begin(); it != objets.end(); it++) {
    //printf("%s\n", it->getNom().c_str());
//glPushMatrix();
/*
    if(it->getNom() == "Roue_AVG_Circle.002" ||
        it->getNom() == "Roue_AVD_Circle.004" ||
        it->getNom() == "Roue_ARD_Circle.005" ||
        it->getNom() == "Roue_ARG_Circle.006") {

glPushMatrix();
angle += 10.0;
      //glLoadIdentity();
    Vertex barycentre = it->calculerBarycentre();
    //printf("barycantre x:%f y:%f z:%f\n", barycentre.getX(), barycentre.getY(), barycentre.getZ());
    glTranslatef(-barycentre.getX(), -barycentre.getY(), -barycentre.getZ());
     //glRotatef(angle,0.0,0.0,1.0);
      it->dessiner(); //ou animer();
    glTranslatef(barycentre.getX(), barycentre.getY(), barycentre.getZ());
      //it->dessiner(); //ou animer();
glPopMatrix();
    }else{
      it->dessiner(); //ou animer();
    }
//glPopMatrix();
*/
  //glTranslatef(-0.01, 0.0, 0.0);
      it->dessiner(); //ou animer();
  }

  //glutPostRedisplay();
}

void Moteur::init() {
  //Not implemented yet !!!
  vector<Objet3D>::iterator it;

  for(it = objets.begin(); it != objets.end(); it++) {
    it->init(); //ou animer();
  }
}

