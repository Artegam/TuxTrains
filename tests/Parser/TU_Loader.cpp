#include "TU_Loader.h"
#include "Loader.h"
#include "Material.h"
#include <map>

int TU_Loader::execute() {

	vector<Objet3D> objets;
	vector<Objet3D>::iterator it;

  Loader *l = new Loader("/home/tonio/TuxTrains/obj", "/home/tonio/TuxTrains/mtl", false);
  objets = l->getObjets(); //Charge tous les objets dans la scene en 3D

  //Initialisation des objets (chargement dans la carte graphique pour le rendu
  printf("Parcours des  objets lus...\n");
	for(it = objets.begin(); it != objets.end(); it++) {
		printf(" -> %s\n", it->getNom());
	}

  return 0;
}