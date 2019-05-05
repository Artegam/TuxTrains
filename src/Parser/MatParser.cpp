
#include "MatParser.h"



//ASCH - 17/10/2014 - Parametres



//ASCH - 17/10/2014 - Methodes
map<string, Material> MatParser::readFile (const char * filename) {
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

  return materiaux;
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

  char* nom;

  for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {
    vector<string> tokens = getTokens(it);
    //Conditions pour traitements
    if(tokens.size() > 0) {

      // newmtl
      if(tokens[0].compare("newmtl") == 0) {
        Material mat;
        nom = new char[tokens[1].size() + 1];
        strcpy(nom, tokens[1].c_str());
        mat.setNom(nom);
        vMat = &mat; // On garde le pointeur de materiau courant
        printf("NOUVEAU MATERIAU : %s\n", nom);
        materiaux[nom] = mat;
        vMat = &mat;
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

        materiaux[nom].setAmbiant(d[0], d[1], d[2]);
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

        materiaux[nom].setDiffus(d[0], d[1], d[2]);
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

        materiaux[nom].setSpeculaire(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur speculaire ####\n");
        }

        continue;
      }

      // Emmission
      if(tokens[0].compare("Ke") == 0) {

        if(tokens.size() == 4) {
        double d[tokens.size()-1];
        for(unsigned int i = 0; i < tokens.size()-1; i++) {
          d[i] = stod(tokens[i+1]);
        }

        materiaux[nom].setEmmission(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur emmission ####\n");
        }

        continue;
      }

      // Reflectivite
      if(tokens[0].compare("Ns") == 0) {

        printf("!!!! %s\n", tokens[1].c_str());

        if(tokens.size() == 2) {
          double d;
          d = stod(tokens[1]);
printf("!!!! %f\n", d);
          materiaux[nom].setReflectivite(d);
        }else{
          printf("#### Erreur Reflectivite ####\n");
        }

        continue;
      }

      // Transparence
      if(tokens[0].compare("Tr") == 0) {

        if(tokens.size() == 2) {
          double d;
          d = stod(tokens[1]);

          materiaux[nom].setTransparence(d);
        }else{
          printf("#### Erreur Transparence ####\n");
        }

        continue;
      }

      // Non-Transparence
      if(tokens[0].compare("d") == 0) {

        if(tokens.size() == 2) {
          double d;
          d = stod(tokens[1]);

          materiaux[nom].setNonTransparence(d);
        }else{
          printf("#### Erreur Non-Transparence ####\n");
        }

        continue;
      }

      // Num illumination
      if(tokens[0].compare("illum") == 0) {

        if(tokens.size() == 2) {
          int i;
          i = atoi(tokens[1].c_str());

          materiaux[nom].setModeleIllumination(i);
        }else{
          printf("#### Erreur Modele illumination ####\n");
        }

        continue;
      }

      // Chemin texture
      if(tokens[0].compare("map_Kd") == 0) {

        if(tokens.size() == 2) {
          printf("%s\n", tokens[1].c_str());
          materiaux[nom].setTexture(tokens[1]);
        }else{
          printf("#### Erreur chemin texture ####\n");
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




