
#include "MatParser.h"



//ASCH - 17/10/2014 - Paramètres



//ASCH - 17/10/2014 - Méthodes
vector<Material> MatParser::readFile (const char * filename) {

	FILE* fichier;
	char ligne[255];
	int selection = 0;
	
	fichier = fopen(filename, "r");
	
	while(!feof(fichier)) {	
		fscanf(fichier, "%s", ligne);
		selection = 0;


		if(strcmp((const char*)ligne, (char*)"v") == 0) {
			selection = 1;
		}


		switch(selection) {

			//ASCH - 16/10/2014 - Le cas du vertex
			case 1:
				//readVertex(fichier);
				break;

		}
	}
	fclose(fichier);
	return objets;
}

