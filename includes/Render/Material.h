#ifndef MATERIAL
#define MATERIAL

#include <GL/glut.h>

#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "RenderObj.h"

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

class Material:public RenderObj {

  protected:
    char * nom;
    double Ns;
    double Ni;
    double d;
    double Tr;
    GLfloat Ka[4];
    GLfloat Kd[4];
    GLfloat Ks[4];
    GLfloat Ke[4];
    int illum;
    char * map_Kd;
    GLfloat no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat test[4] = {0.0f, 1.0f, 0.0f, 1.0f}; //couleur verte de test

  public:
    Material();
    char* getNom();

    void setNom(char* pNom);
    void setAmbiant(double r, double v, double b);
    void setDiffus(double r, double v, double b);
    void setSpeculaire(double r, double v, double b);
    void setEmmission(double r, double v, double b);
    void setReflectivite(double r);
    void setTransparence(double t);
    void setNonTransparence(double nt);
    void setModeleIllumination(int num_model);
    void setTexture(string cheminTexture);

    void printInfos();

    void init();
    void dessiner(void);
};

#endif
