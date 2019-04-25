
#include "MatParser.h"



//ASCH - 17/10/2014 - Parametres



//ASCH - 17/10/2014 - Methodes
vector<Material> MatParser::readFile (const char * filename) {
  string sligne;

  ifstream fichier;
  fichier.open(filename, ios::in);
  printf ("Debut de lecture du fichier de materiaux\n");

  while(!fichier.eof()) {
   getline(fichier, sligne);
   fichierRAM.insert(fichierRAM.end(), sligne);
  }

  fichier.close();
  printf ("Fin de lecture du fichier de materiaux\n");

  parserFichier();

  return materials;
}


void MatParser::parserFichier() {
  vector<string>::iterator it;
  printf ("Debut parcours fichier RAM\n");

// exemple
//  std::map<char,int> first;
//
//  first['a']=10;
//  first['b']=30;
//  first['c']=50;
//  first['d']=70;


  for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {
    vector<string> tokens = getTokens(it);
    //Conditions pour traitements
    if(tokens.size() > 0) {

      // newmtl
      if(tokens[0].compare("newmtl") == 0) {
        Material mat;
        char* nom = new char[tokens[1].size() + 1];
        strcpy(nom, tokens[1].c_str());
        mat.setNom(nom);
        vMat = &mat; // On garde le pointeur de materiau courant
        //objets.insert(objets.begin(), *vObj);
        materiaux[nom] = mat;
        printf("Materiau : %s\n", nom);
        continue;
      }

      // Ambiant
      if(tokens[0].compare("Ka") == 0) {

        if(tokens.size() == 4) {
        double d[tokens.size()-1];
        for(unsigned int i = 0; i < tokens.size()-1; i++) {
          d[i] = stod(tokens[i+1]);
        }

        vMat->setAmbiant(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur ambiante ####\n");
        }

        continue;
      }

      // Diffus
      if(tokens[0].compare("Kd") == 0) {

        if(tokens.size() == 4) {
        double d[tokens.size()-1];
        for(unsigned int i = 0; i < tokens.size()-1; i++) {
          d[i] = stod(tokens[i+1]);
        }

        vMat->setDiffus(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur diffuse ####\n");
        }

        continue;
      }

      // Speculaire
      if(tokens[0].compare("Ks") == 0) {

        if(tokens.size() == 4) {
        double d[tokens.size()-1];
        for(unsigned int i = 0; i < tokens.size()-1; i++) {
          d[i] = stod(tokens[i+1]);
        }

        vMat->setSpeculaire(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur speculaire ####\n");
        }

        continue;
      }

    }
    tokens.clear();
  }

  printf ("FIN parcours fichier RAM\n");
  printf("Fin du traitement\n");

}



vector<string> MatParser::getTokens(vector<string>::iterator it) {
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




