
#include "MatParser.h"



//ASCH - 17/10/2014 - Parametres



//ASCH - 17/10/2014 - Methodes
map<string, Material> MatParser::readFile (const char * filename) {
  string sligne;

  ifstream fichier;
  fichier.open(filename, ios::in);
  printf ("Debut de lecture du fichier de materiaux %s...\n", filename);

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

      //Le cas newmtl xxxx
      regex newmtl_regex("^newmtl \\(.*\\)", regex_constants::basic);
      smatch m;


      if(regex_search(*it, m, newmtl_regex)) {
        Material mat;
        nom = new char[m[1].str().size() + 1];
        strcpy(nom, m[1].str().c_str());
        mat.setNom(nom);
        vMat = &mat; // On garde le pointeur de materiau courant
        materiaux[nom] = mat;
        vMat = &mat;
        continue;
      }

      //Le cas Ka xxxx xxxxx xxxx
      regex ka_regex("^Ka \\([0-9\\.]*\\) \\([0-9\\.]*\\) \\([0-9\\.]*\\)", regex_constants::basic);

      if(regex_search(*it, m, ka_regex)) {
        if(m.size() == 4) {
        double d[m.size()-1];
        for(unsigned int i = 0; i < m.size()-1; i++) {
          d[i] = stod(m[i+1].str().c_str());
        }

        materiaux[nom].setAmbiant(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur ambiante ####\n");
        }

        continue;
      }

      //Le cas Kd xxxx xxxxx xxxx
      regex kd_regex("^Kd \\([0-9\\.]*\\) \\([0-9\\.]*\\) \\([0-9\\.]*\\)", regex_constants::basic);

      if(regex_search(*it, m, kd_regex)) {
        if(m.size() == 4) {
        double d[m.size()-1];
        for(unsigned int i = 0; i < m.size()-1; i++) {
          d[i] = stod(m[i+1].str().c_str());
        }

        materiaux[nom].setDiffus(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur diffuse ####\n");
        }

        continue;
      }


      //Le cas Ks xxxx xxxxx xxxx
      regex ks_regex("^Ks \\([0-9\\.]*\\) \\([0-9\\.]*\\) \\([0-9\\.]*\\)", regex_constants::basic);

      if(regex_search(*it, m, ks_regex)) {
        if(m.size() == 4) {
        double d[m.size()-1];
        for(unsigned int i = 0; i < m.size()-1; i++) {
          d[i] = stod(m[i+1].str().c_str());
        }

        materiaux[nom].setSpeculaire(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur speculaire ####\n");
        }

        continue;
      }


      //Le cas Ke xxxx xxxxx xxxx
      regex ke_regex("^Ke \\([0-9\\.]*\\) \\([0-9\\.]*\\) \\([0-9\\.]*\\)", regex_constants::basic);

      if(regex_search(*it, m, ke_regex)) {
        if(m.size() == 4) {
        double d[m.size()-1];
        for(unsigned int i = 0; i < m.size()-1; i++) {
          d[i] = stod(m[i+1].str().c_str());
        }

        materiaux[nom].setEmmission(d[0], d[1], d[2]);
        }else{
          printf("#### Erreur couleur emmission ####\n");
        }

        continue;
      }

      //Le cas Ns xxxx
      regex ns_regex("^Ns \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, ns_regex)) {
        if(m.size() == 2) {
          double d;
          d = stod(m[1].str().c_str());
          materiaux[nom].setReflectivite(d);
        }else{
          printf("#### Erreur Reflectivite ####\n");
        }

        continue;
      }

      //Le cas Tr xxxx
      regex tr_regex("^Tr \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, tr_regex)) {
        if(m.size() == 2) {
          double d;
          d = stod(m[1].str().c_str());
          materiaux[nom].setTransparence(d);
        }else{
          printf("#### Erreur Transparence ####\n");
        }

        continue;
      }

      //Le cas d xxxx
      regex d_regex("^d \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, d_regex)) {
        if(m.size() == 2) {
          double d;
          d = stod(m[1].str().c_str());
          materiaux[nom].setNonTransparence(d);
        }else{
          printf("#### Erreur Non-Transparence ####\n");
        }

        continue;
      }

      //Le cas illum xxxx
      regex illum_regex("^illum \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, illum_regex)) {
        if(m.size() == 2) {
          int i = atoi(m[1].str().c_str());
          materiaux[nom].setModeleIllumination(i);
        }else{
          printf("#### Erreur Modele illumination ####\n");
        }

        continue;
      }

      //Le cas map_Kd xxxx Chemin texture
      regex mapkd_regex("^map_Kd \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, mapkd_regex)) {
        if(m.size() == 2) {
          printf("%s\n", m[1].str().c_str());
          materiaux[nom].setTexture(m[1].str());
        }else{
          printf("#### Erreur chemin texture ####\n");
        }

        continue;
      }


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




