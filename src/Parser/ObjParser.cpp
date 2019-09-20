
#include "ObjParser.h"

#include <regex>

//ASCH - 17/10/2014 - ParamÃ¨tres

ObjParser::ObjParser(map<string, Material> mats) {
  materiaux = mats;
}


//ASCH - 17/10/2014 - MÃ©thodes
vector<Objet3D> ObjParser::readFile (const char * filename) {

  string sligne;


  ifstream fichier;
  fichier.open(filename, ios::in);
  printf("Taille de fichierRAM : %d\n", fichierRAM.size());
  printf ("Debut de lecture du fichier %s...\n", filename);

  while(!fichier.eof()) {
   getline(fichier, sligne);
   fichierRAM.insert(fichierRAM.end(), sligne);
  }

  fichier.close();
  printf ("Fin de lecture du fichier\n");

  parserFichier();

  return objets;
}


void ObjParser::parserFichier() {
  vector<string>::iterator it;
  //printf ("Debut parcours fichier RAM\n");

  for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {

      //Le cas o xxxx
      regex o_regex("o \\(.*\\)", regex_constants::basic);
      smatch m;


      if(regex_search(*it, m, o_regex)) {
        //printf("\t - %s\n", m[1].str().c_str());
        vObj = new Objet3D();
        vObj->setNom(m[1].str().c_str());
        objets.insert(objets.begin(), *vObj);
        continue;
      }

      //Le cas mtllib xxxx
      regex mtllib_regex("mtllib \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, mtllib_regex)) {
        printf("Nom de la librairie de materiaux : %s\n", m[1].str().c_str());
        continue;
      }

      //Le cas usemtl xxxx
      regex usemtl_regex("usemtl \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, usemtl_regex)) {
        for(size_t i = 0; i < m.size(); ++i) {
          //printf(" Materiau lu : %s\n", m[1].str().c_str());
          objets[0].setMateriau(materiaux[m[1].str().c_str()]); //L'objet3D est insÃrÃ© en dÃ©but de liste a chaque fois ???
        }
        continue;
      }

      //Le cas de v xxxx xxxx xxxx
      regex v3_regex("v \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, v3_regex)) {
        objets[objets.size()-1].ajouterVertex(stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()), 0.0);
        continue;
      }

      //Le cas de v xxxx xxxx xxxx xxxxx
      //regex v4_regex("v \\(-*\d*.\d*\\) \\(-*\\d*.\\d*\\) \\(-*\\d*.\\d*\\) \\(-*\\d*.\\d*\\)$", regex_constants::basic);
      regex v4_regex("v \\(-*.*\\) \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, v4_regex)) {
        objets[objets.size()-1].ajouterVertex(stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()),  stod(m[4].str().c_str()));
        continue;
      }


      //Le cas de vn xxxx xxxx xxxx
      regex vn3_regex("vn \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$" regex_constants::basic);

      if(regex_search(*it, m, vn3_regex)) {
        objets[objets.size()-1].ajouterVertexNormal(stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()), 0.0);
        continue;
      }


      //Le cas de vn xxxx xxxx xxxx xxxxx
      regex vn4_regex("vn \\(-*.*\\) \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, vn4_regex)) {
        objets[objets.size()-1].ajouterVertexNormal(stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()), stod(m[4].str().c_str()));
        continue;
      }

      //Les faces
      //Le cas de f xxxx xxxx xxxx
      regex f3_regex("f \\(.*\\) \\(.*\\) \\(.*\\)$" regex_constants::basic);

      if(regex_search(*it, m, f3_regex)) {
        printf("une face du type f 3\n");
        continue;
      }

      //Le cas de f xxxx xxxx xxxx xxxxx
      regex f4_regex("f \\(.*\\) \\(.*\\) \\(.*\\) \\(.*\\)$" regex_constants::basic);

      if(regex_search(*it, m, f4_regex)) {
        printf("une face du type f 4\n");
        continue;
      }

/*
    vector<string> tokens = getTokens(it);
    //Conditions pour traitements
    if(tokens.size() > 0) {
      // Objets
      if(tokens[0].compare("o") == 0) {
        vObj = new Objet3D();
        char* nom = new char[tokens[1].size() + 1];
        strcpy(nom, tokens[1].c_str());
        vObj->setNom(nom);
        objets.insert(objets.begin(), *vObj);
        printf("\t - %s\n", nom);
        continue;
      }

      //USEMTL
      if(tokens[0].compare("usemtl") == 0) {
        //printf("SET MATERIAU %s\n", tokens[1].c_str());

        //materiaux[tokens[1]].printInfos();
        objets[0].setMateriau(materiaux[tokens[1]]); //L'objet3D est insÃrÃ© en dÃ©but de liste a chaque fois ???
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

        char** res = new char*[tokens.size()-1]; // A vérifier sinon utiliser +1 a cause du caractère de fin de chaine '\0'

        for(unsigned int i = 0; i < tokens.size()-1; i++) {
          res[i] = new char[tokens[i+1].size()+1];
          strcpy(res[i], tokens[i+1].c_str());
        }

        objets.back().ajouterFace(tokens.size()-1, res);
        continue;
      }


      //MTLLIB
      if(tokens[0].compare("mtllib") == 0) {
        printf("Nom de la librairie de materiaux : %s\n", tokens[1].c_str());
        continue;
      }

    }
    tokens.clear();
    */
  }

  //printf ("FIN parcours fichier RAM\n");
  //printf("Fin du traitement\n");

}



vector<string> ObjParser::getTokens(vector<string>::iterator it) {

  string delimiter = " ";
  string token;
  size_t pos = 0;

  vector<string> tokens;
  while((pos = it->find(delimiter)) != string::npos) {
    token = it->substr(0, pos);
    tokens.push_back(token);
    it->erase(0, pos + delimiter.length());
  }
  //Ajouter le dernier element
  token = it->substr(0, it->size());
  tokens.push_back(token);

  return tokens;
}
