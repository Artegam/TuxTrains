#ifndef MATERIAL
#define MATERIAL

#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <string>
/*
	- newmtl name
	- Ns double : Reflectivité (shininess)
	- Ka double double double : Lumiere ambiante
	- Kd double double double : Lumière diffuse
	- Ks double double double : Lumière Speculaire
	- Ni double
	- d double : Non-Transparence
  - Tr double : Transparence
	- illum int : Illumination model
	- map_Kd (char*) chemin complet.jpg

*/
using namespace std;

class Material {

  protected:
    char * nom;
    double Ns;
    double Ni;
    double d;
    double Tr;
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
    void setReflectivite(double r);
    void setTransparence(double t);
    void setNonTransparence(double nt);
    void setModeleIllumination(int num_model);
    void setTexture(string cheminTexture);

};

#endif
