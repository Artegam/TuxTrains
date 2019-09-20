
#include "Loader.h"
#include "Material.h"
#include <map>

int main(int argc, char** argv) {

	vector<Objet3D> objets;

  Loader *l = new Loader("/home/tonio/TuxTrains/obj", "/home/tonio/TuxTrains/mtl", false);
  objets = l->getObjets(); //Charge tous les objets dans la scene en 3D

  //Initialisation des objets (chargement dans la carte graphique pour le rendu
  printf("Parcours des  objets lus...\n";
	for(it = objets.begin(); it != objets.end(); it++) {
		printf(" -> %s\n", it->getName());
	}

  return 0;
}
