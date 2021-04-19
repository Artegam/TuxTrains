
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

Loader::Loader(const char* cheminObj, bool recursif) {
  //Charger les fichier obj, ne charger que les fichiers MTL necessaires aux fixhiers obj

  //vector<string> fichiersMtl;
  vector<string> fichiersObj;

  //fichiersMtl = getFilenamesFromDir(cheminMtl);
  fichiersObj = getFilenamesFromDir(cheminObj);

	ObjParser * parser;
  MatParser matParser;
  map<string, Material> materials;

  //Lecture des fichiers mtl
  vector<string>::iterator it;
/*  
  vector<string> fichiersMtl;

  fichiersMtl = getFilenamesFromDir(cheminMtl);
  for(it = fichiersMtl.begin(); it != fichiersMtl.end(); it++) {
    materials = matParser.readFile(it->c_str());
    printf(" * %s\n", it->c_str());
  }
  parser = new ObjParser(materials);
   */
  //Lecture des fichiers obj
  parser = new ObjParser();

  for(it = fichiersObj.begin(); it != fichiersObj.end(); it++) {
    regex self_regex(".*\\.obj$", regex_constants::basic);
    if(regex_search(it->c_str(), self_regex)) {
      objets = parser->readFile(it->c_str(), cheminObj);
      printf(" # %s\n", it->c_str());
    }
  }

}

vector<string> Loader::getFilenamesFromDir(const char* directory) {
  vector<string> res;
  DIR* rep = NULL;
  struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

  rep = opendir(directory); // Ouverture d'un dossier (mauvais chemin par exemple)
  if(rep == NULL) exit(1);  // Si le dossier n'a pas pu être ouvert

  printf("Repertoire scanne : %s\n", directory);

  fichierLu = readdir(rep);                                     // On lit le premier répertoire du dossier.
  while(fichierLu != NULL) {
    if(fichierLu->d_type != DT_DIR) {                           // Protection : on ne prends pas les repertoires
      string nomFchier = fichierLu->d_name;
      string separator = "/";
      string cheminComplet = directory + separator + nomFchier;

      res.insert(res.end(), cheminComplet);                     // On ajoute le nom de fichier trouve a la liste de resultat
    }
    fichierLu = readdir(rep);                                   // On lit le premier répertoire du dossier.
  }

  if(closedir(rep) == -1) exit(-1);/* S'il y a eu un souci avec la fermeture */

  return res;
}


vector<Objet3D> Loader::getObjets()
{
 return objets;
}

