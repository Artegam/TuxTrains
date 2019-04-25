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
  printf("setAmbiant not implemented yet !!\n");
}

void Material::setDiffus(double r, double v, double b){
  printf("setDiffus not implemented yet !!\n");
}

void Material::setSpeculaire(double r, double v, double b){
  printf("setSpeculaire not implemented yet !!\n");
}


