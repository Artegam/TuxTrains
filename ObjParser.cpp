
#include "ObjParser.h"


//ASCH - 17/10/2014 - Paramètres



//ASCH - 17/10/2014 - Méthodes
vector<Objet3D> ObjParser::readFile (const char * filename) {

  string sligne;

  vector<string> fichierRAM;

  ifstream fichier;
  fichier.open(filename, ios::in);
printf ("Début de lecture du fichier\n");

	while(!fichier.eof()) {
   getline(fichier, sligne);
   fichierRAM.insert(fichierRAM.end(), sligne);
  }

	fichier.close();
printf ("Fin de lecture du fichier\n");


  vector<string>::iterator it;
    cmatch m; // Tableau des chaines qui match
   regex reg_vertex = regex("v ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*|v ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*");


  for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {

    const char* ligne = it->c_str();
    //printf("Ligne : %s", ligne);

    // D�but de l'objet en 3D (avec le nom)
    if (regex_match(ligne, m, regex("o (.*)"))) {
//printf ("OBJET\n");
continue;
      vObj = new Objet3D();
      char * nom = getMatchedChar(m)[0];
      vObj->setNom(nom);
      objets.insert(objets.begin(), *vObj);
      printf("\t - %s\n", nom);
      continue;
    }

    if (regex_match(ligne, m, regex("usemtl (.*)"))) {
//printf ("USEMTL\n");
continue;

      printf("materiaux utilise: %s\n", getMatchedChar(m)[0]);
      continue;
    }

    //Vertex
    if (regex_match(ligne, m, reg_vertex)) {
//printf ("VERTEX\n");
continue;


      double* d = getMatchedDouble(m);

      //printf("vect %f %f %f\n", d[0], d[1], d[2]);
      if(sizeof(d) == 3) objets[objets.size()-1].ajouterVertex(d[0], d[1], d[2], 0.0);
      if(sizeof(d) == 4) objets[objets.size()-1].ajouterVertex(d[0], d[1], d[2], d[3]);
      continue;
    }

    //Vertex Normal
    if (regex_match(ligne, m, regex("vn ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*|vn ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*"))) {

//      printf ("VERTEX NORMAL\n");
continue;

      
      double* d = getMatchedDouble(m);
      //printf("vect normal %f %f %f\n", d[0], d[1], d[2]);
      if(sizeof(d) == 3) objets[objets.size()-1].ajouterVertexNormal(d[0], d[1], d[2], 0.0);
      if(sizeof(d) == 4) objets[objets.size()-1].ajouterVertexNormal(d[0], d[1], d[2], d[3]);
      continue;
    }

    if (regex_match(ligne, m, regex("f ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*)|f ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*)"))) {
//      printf ("FACE\n");
continue;

      char** res = getMatchedChar(m);
      objets[objets.size()-1].ajouterFace(sizeof(res), res);
      continue;
    }

    if (regex_match(ligne, m, regex("mtllib (.*)"))) {
//      printf ("MTLLIB\n");
continue;

      
      printf("Nom de la librairie de maetriaux : %s\n", getMatchedChar(m)[0]);
      continue;
    }


  }

  printf("Fin du traitement\n");
  //exit(0);
	return objets;
}

char** ObjParser::getMatchedChar(cmatch m) {
  char** ret = new char*[m.size()];
  int cpt = 0;

  for (cmatch::iterator it = m.begin()+1; it != m.end(); it++) {
    ret[cpt] = new char[it->str().length() + 1];
    strcpy(ret[cpt], it->str().c_str());
    //printf("pour le char** : %s\n", ret[cpt]);
    cpt++;
  }
  return ret;
}

double* ObjParser::getMatchedDouble(cmatch m) {
  double* ret = new double[m.size()];
  int cpt = 0;

  for (cmatch::iterator it = m.begin()+1; it != m.end(); it++) {
    if(it->str().size() > 0) { // Protege de la regex multiple avec le ou '|'
      const char* val = it->str().c_str();
      string str = it->str();
      ret[cpt] = atof((const char*)str.c_str()); // converti en double (atof)
      cpt++;
    }
  }

  return ret;
}

