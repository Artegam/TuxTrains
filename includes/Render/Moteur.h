#ifndef MOTEUR_H
#define MOTEUR_H

#include <vector>
#include <list>
#include "Objet3D.h"

class Moteur {

	protected:
    map<string,Objet3D> objets;
    const char * defaultPath = "/home/tonio/TuxTrains/obj";
    float angle = 0.0;

	public:
    Moteur();
    Moteur(const char* objPath);

    //void ajouter(Objet3D obj);
    //void ajouter(vector<Objet3D> lst);
		void tic();
		void init();
    Objet3D getObjet3D(string nom);
};

#endif
