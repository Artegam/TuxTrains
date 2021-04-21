#ifndef MOTEUR_H
#define MOTEUR_H

#include <vector>
#include <list>
#include "Objet3D.h"

class Moteur {

	protected:
    vector<Objet3D> objets;
    list<vector<Objet3D>> files;
    const char * defaultPath = "/home/tonio/TuxTrains/obj";
    float angle = 0.0;

	public:
    Moteur(const char* objPath);

    //void ajouter(Objet3D obj);
    //void ajouter(vector<Objet3D> lst);
		void tic();
		void init();
};

#endif
