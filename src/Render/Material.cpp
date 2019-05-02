#include "Material.h"
#include <stdio.h>


Material::Material() {
  copy(begin(Ka), end(Ka), begin(no_mat));
  copy(begin(Kd), end(Kd), begin(no_mat));
  copy(begin(Ks), end(Ks), begin(no_mat));
  copy(begin(Ke), end(Ke), begin(no_mat));
}

char* Material::getNom() {
	return nom;
}

void Material::setNom(char* pNom) {
	nom = pNom;
}

void Material::setAmbiant(double r, double v, double b){
  Ka[0] = r;
  Ka[1] = v;
  Ka[2] = b;
  Ka[3] = 1.0; //Alpha
}

void Material::setDiffus(double r, double v, double b){
  Kd[0] = r;
  Kd[1] = v;
  Kd[2] = b;
  Kd[3] = 1.0; //Alpha
}

void Material::setSpeculaire(double r, double v, double b){
  Ks[0] = r;
  Ks[1] = v;
  Ks[2] = b;
  Ks[3] = 1.0; //Alpha
}

void Material::setEmmission(double r, double v, double b){
  Ke[0] = r;
  Ke[1] = v;
  Ke[2] = b;
  Ke[3] = 1.0; //Alpha
}


void Material::setReflectivite(double r){
  Ns = r;
}

void Material::setTransparence(double t){
  Tr = t;
}

void Material::setNonTransparence(double nt){
  d = nt;
}

void Material::setModeleIllumination(int num_model){
  illum = num_model;
}

void Material::setTexture(string cheminTexture){
  map_Kd = new char[cheminTexture.size()+1];
  strcpy(map_Kd,cheminTexture.c_str());
}

void Material::init() {
};

void Material::dessiner(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, Ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Ks);
  glMaterialf(GL_FRONT, GL_SHININESS, Ns);
  glMaterialfv(GL_FRONT, GL_EMISSION, Ke);
}
