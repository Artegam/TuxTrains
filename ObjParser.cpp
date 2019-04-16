
#include "ObjParser.h"

//ASCH - 17/10/2014 - ParamÃ¨tres



//ASCH - 17/10/2014 - MÃ©thodes
vector<Objet3D> ObjParser::readFile (const char * filename) {

  string sligne;

  vector<string> fichierRAM;

  ifstream fichier;
  fichier.open(filename, ios::in);
printf ("DÃ©but de lecture du fichier\n");

  while(!fichier.eof()) {
   getline(fichier, sligne);
   fichierRAM.insert(fichierRAM.end(), sligne);
  }

  fichier.close();
printf ("Fin de lecture du fichier\n");


  vector<string>::iterator it;
  boost::cmatch m; // Tableau des chaines qui match
  boost::regex reg_obj{"o (.*)"};
  boost::regex reg_usemtl{"usemtl (.*)"};
  boost::regex reg_vertex{"v ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*|v ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*"};
  boost::regex reg_vertNorm{"vn ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*|vn ([-]*\\d.\\d*) ([-]*\\d.\\d*) ([-]*\\d.\\d*).*"};
  boost::regex reg_face{"f ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*)|f ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*) ([0-9]*/[0-9]*/[0-9]*)"};
  boost::regex reg_mtllib{"mtllib (.*)"};

  for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {

    const char* ligne = it->c_str();
    //printf("Ligne : %s", ligne);

    // Début de l'objet en 3D (avec le nom)
    if (boost::regex_match(ligne, m, reg_obj)) {
//printf ("OBJET\n");
continue;
      vObj = new Objet3D();
      char * nom = getMatchedChar(m)[0];
      vObj->setNom(nom);
      objets.insert(objets.begin(), *vObj);
      printf("\t - %s\n", nom);
      continue;
    }

    if (boost::regex_match(ligne, m, reg_usemtl)) {
//printf ("USEMTL\n");
continue;

      printf("materiaux utilise: %s\n", getMatchedChar(m)[0]);
      continue;
    }

    //Vertex
    if (boost::regex_match(ligne, m, reg_vertex)) {
//printf ("VERTEX\n");
continue;


      double* d = getMatchedDouble(m);

      //printf("vect %f %f %f\n", d[0], d[1], d[2]);
      if(sizeof(d) == 3) objets[objets.size()-1].ajouterVertex(d[0], d[1], d[2], 0.0);
      if(sizeof(d) == 4) objets[objets.size()-1].ajouterVertex(d[0], d[1], d[2], d[3]);
      continue;
    }

    //Vertex Normal
    if (boost::regex_match(ligne, m, reg_vertNorm)) {

//      printf ("VERTEX NORMAL\n");
continue;
      
      double* d = getMatchedDouble(m);
      //printf("vect normal %f %f %f\n", d[0], d[1], d[2]);
      if(sizeof(d) == 3) objets[objets.size()-1].ajouterVertexNormal(d[0], d[1], d[2], 0.0);
      if(sizeof(d) == 4) objets[objets.size()-1].ajouterVertexNormal(d[0], d[1], d[2], d[3]);
      continue;
    }

    if (boost::regex_match(ligne, m, reg_face)) {
//      printf ("FACE\n");
continue;

      char** res = getMatchedChar(m);
      objets[objets.size()-1].ajouterFace(sizeof(res), res);
      continue;
    }

    if (boost::regex_match(ligne, m, reg_mtllib)) {
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

char** ObjParser::getMatchedChar(boost::cmatch m) {
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

double* ObjParser::getMatchedDouble(boost::cmatch m) {
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

