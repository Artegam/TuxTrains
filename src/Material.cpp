#include "Material.h"
#include <stdio.h>


Material::Material() {
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
}

void Material::setDiffus(double r, double v, double b){
  Kd[0] = r;
  Kd[1] = v;
  Kd[2] = b;
}

void Material::setSpeculaire(double r, double v, double b){
  Ks[0] = r;
  Ks[1] = v;
  Ks[2] = b;
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


