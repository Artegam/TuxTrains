
#include "Loader.h"
#include "ObjParser.h"
#include "MatParser.h"
//Pour le parcours des dossiers
#include <dirent.h>
#include <string.h>

#ifndef WIN32
  #include <sys/types.h>
#endif

// documentation ici : https://pubs.opengroup.org/onlinepubs/007908799/xsh/dirent.h.html

Loader::Loader(vector<string> listeObj, vector<string> listeMtl){
  //TODO: Not implemented yet !!
}

Loader::Loader(const char* cheminObj, const char* cheminMtl, bool recursif){
  //TODO: Not implemented yet !!

  vector<string> fichiersMtl;

  fichiersMtl =  getFilenamesFromDir(cheminMtl);
  //getFilenamesFromDir(cheminObj);

	ObjParser * parser;
  MatParser matParser;
  map<string, Material> materials;
	vector<Objet3D> objets;

  //Exemple
  //fichierRAM.insert(fichierRAM.end(), sligne);
  //objets.insert(objets.end(), sligne);
  //
  vector<string>::iterator it;

  for(it = fichiersMtl.begin(); it != fichiersMtl.end(); it++) {
    materials = matParser.readFile(it->c_str());
    printf(" * %s\n", it->c_str());
  }

  parser = new ObjParser(materials);
  objets = parser->readFile("/home/tonio/TuxTrains/obj/jaguard.obj");

}

vector<string> Loader::getFilenamesFromDir(const char* directory) {
  vector<string> res;
  DIR* rep = NULL;
  struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

  rep = opendir(directory); // Ouverture d'un dossier (mauvais chemin par exemple)
  if(rep == NULL) exit(1);                  // Si le dossier n'a pas pu être ouvert

  printf("Repertoire scanne : %s\n", directory);

  fichierLu = readdir(rep);                                                                // On lit le premier répertoire du dossier.
  while(fichierLu != NULL) {
    //printf("Le fichier lu s'appelle '%s' ( %c )\n", fichierLu->d_name, fichierLu->d_type);
    if(fichierLu->d_type != DT_DIR) {                                                      // Protection : on ne prends pas les repertoires
      string nomFchier = fichierLu->d_name;
      string separator = "/";
      string cheminComplet = directory + separator + nomFchier;

      res.insert(res.end(), cheminComplet);                                               // On ajoute le nom de fichier trouve a la liste de resultat
    }
    fichierLu = readdir(rep);                                                              // On lit le premier répertoire du dossier.
  }

  //puts("Le dossier a ete ouvert avec succes");

  if(closedir(rep) == -1) exit(-1);/* S'il y a eu un souci avec la fermeture */

  //puts("Le dossier a ete ferme avec succes");

  //return 0;
  return res;
}


