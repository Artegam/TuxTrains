#ifndef MOTEUR_H
#define MOTEUR_H

#include <vector>
#include "Objet3D.h"

class Moteur {

	protected:
    vector<Objet3D> objets;
    const char * defaultPath = "/home/tonio/TuxTrains/obj";

	public:
    Moteur(const char* objPath);

    //void ajouter(Objet3D obj);
    //void ajouter(vector<Objet3D> lst);
		void tic();
};

#endif
