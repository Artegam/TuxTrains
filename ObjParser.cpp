
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
printf ("Debut parcours fichier RAM\n");

string delimiter = " ";
string token;
size_t pos = 0;

for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {
  pos = 0;
  vector<string> tokens;
  while((pos = it->find(delimiter)) != string::npos) {
    token = it->substr(0, pos);
    tokens.push_back(token);
    it->erase(0, pos + delimiter.length());
  }
    //Ajouter le dernier element
    token = it->substr(0, it->size());
    tokens.push_back(token);

  //Conditions pour traitements
  if(tokens.size() > 0) {
    // Objets
    if(tokens[0].compare("o") == 0) {
      vObj = new Objet3D();
      char* nom = new char[tokens[1].size()];
      strcpy(nom, tokens[1].c_str());
      vObj->setNom(nom);
      objets.insert(objets.begin(), *vObj);
      printf("\t - %s\n", nom);
      continue;
    }

    //USEMTL
    if(tokens[0].compare("usemtl") == 0) {
      printf("materiaux utilise: %s\n", tokens[1].c_str());
      continue;
    }

    //Vertex
    if(tokens[0].compare("v") == 0) {
      double d[tokens.size()-1];
      for(unsigned int i = 0; i < tokens.size()-1; i++) {
        d[i] = stod(tokens[i+1]);
    }

      if(tokens.size()-1 == 3) objets[objets.size()-1].ajouterVertex(d[0], d[1], d[2], 0.0);
      if(tokens.size()-1 == 4) objets[objets.size()-1].ajouterVertex(d[0], d[1], d[2], d[3]);
      continue;
    }

    //Vertex Normal
    if(tokens[0].compare("vn") == 0) {

      double d[tokens.size()-1];
      for(unsigned int i = 0; i < tokens.size()-1; i++) {
        d[i] = stod(tokens[i+1]);
      }

      if(tokens.size() - 1 == 3) objets[objets.size()-1].ajouterVertexNormal(d[0], d[1], d[2], 0.0);
      if(tokens.size() - 1 == 4) objets[objets.size()-1].ajouterVertexNormal(d[0], d[1], d[2], d[3]);
      continue;
    }

  //Faces
    if(tokens[0].compare("f") == 0) {

      char** res = new char*[tokens.size()-1];

      for(unsigned int i = 0; i < tokens.size()-1; i++) {
        res[i] = new char[tokens[i+1].length()];
        strcpy(res[i], tokens[i+1].c_str());
      }
//      printf("taille size %d\n", tokens.size()-1);
//      printf("taille sizeof %d \n", sizeof(res));

      if(tokens.size()-1 == 3) {
      printf(":: %s %s %s \n", res[0], res[1], res[2]);
      }else{
      printf(":: %s %s %s %s \n", res[0], res[1], res[2], res[3]);
      }

      objets[objets.size()-1].ajouterFace(tokens.size()-1, res);
      continue;
      }


    //MTLLIB
    if(tokens[0].compare("mtllib") == 0) {
      printf("Nom de la librairie de maetriaux : %s\n", tokens[1].c_str());
      continue;
    }

  }
  tokens.clear();
}

printf ("FIN parcours fichier RAM\n");

  printf("Fin du traitement\n");
  //exit(0);
	return objets;
}

