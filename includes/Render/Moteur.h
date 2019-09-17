#ifndef MOTEUR_H
#define MOTEUR_H

#include <vector>
#include "Objet3D.h"

class Moteur {

	protected:
    vector<Objets3D> listeObjets;

	public:
    void ajouter(Objet3D obj);
    void ajouter(vector<Objets3D> lst);
		void tic();
};

#endif
