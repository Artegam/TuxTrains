#ifndef MATERIAL
#define MATERIAL

#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
/*
	- newmtl name
	- Ns double
	- Ka double double double
	- Kd double double double
	- Ks double double double
	- Ni double
	- d double
	- illum int
	- map_Kd (char*) chemin complet.jpg

*/


class Material {

  protected:
    char * nom;
    double Ns;
    double Ni;
    double d;
    double Ka[3];
    double Kd[3];
    double Ks[3];
    int illum;
    char * map_Kd;


  public:
    Material();
    char* getNom();

    void setNom(char* pNom);
    void setAmbiant(double r, double v, double b);
    void setDiffus(double r, double v, double b);
    void setSpeculaire(double r, double v, double b);

};

#endif
