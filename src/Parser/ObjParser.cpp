
#include "ObjParser.h"


//ASCH - 17/10/2014 - ParamÃ¨tres

ObjParser::ObjParser() {
}


//ASCH - 17/10/2014 - MÃ©thodes
vector<Objet3D> ObjParser::readFile (const char * filename, const char * chemin) {

  string sligne;
  cheminFichiersObj = chemin;

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
  map<string, Material> materials;
  vector<string>::iterator it;
  //printf ("Debut parcours fichier RAM\n");

  int index_vertex = 0;
  int index_vertex_normal = 0;

  for(it = fichierRAM.begin(); it != fichierRAM.end(); it++) {

      //Le cas o xxxx
      regex o_regex("o \\(.*\\)", regex_constants::basic);
      smatch m;


      if(regex_search(*it, m, o_regex)) {
        vObj = new Objet3D();
        char* nom = new char[m[1].str().size() + 1];
        strcpy(nom, m[1].str().c_str());

        vObj->setNom(nom);
        objets.insert(objets.begin(), *vObj);
        continue;
      }

      //Le cas mtllib xxxx
      regex mtllib_regex("mtllib \\(.*\\)", regex_constants::basic);

      if(regex_search(*it, m, mtllib_regex)) {
        printf("Nom de la librairie de materiaux a charger : %s/%s\n", cheminFichiersObj.c_str(), m[1].str().c_str());
        string nomComplet = cheminFichiersObj + '/' + m[1].str().c_str();
        materials = matParser.readFile(nomComplet.c_str());


        // Charger le fichier en parametre
        continue;
      }

      //Le cas usemtl xxxx
      regex usemtl_regex("usemtl \\(.*\\)", regex_constants::basic);
      if(regex_search(*it, m, usemtl_regex)) {
        for(size_t i = 0; i < m.size(); ++i) {
          //printf(" Materiau lu : %s\n", m[1].str().c_str());
          mat_courant = materials[m[1].str()];
          objets[0].setMateriau(mat_courant); //L'objet3D est insÃrÃ© en dÃ©but de liste a chaque fois ???
        }
        continue;
      }

      //Le cas de v xxxx xxxx xxxx
      regex v3_regex("v \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, v3_regex)) {
        index_vertex++;
        objets.front().ajouterVertex(index_vertex, stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()), 0.0);
        continue;
      }

      //Le cas de v xxxx xxxx xxxx xxxxx
      regex v4_regex("v \\(-*.*\\) \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, v4_regex)) {
        index_vertex++;
        objets.front().ajouterVertex(index_vertex, stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()),  stod(m[4].str().c_str()));
        continue;
      }


      //Le cas de vn xxxx xxxx xxxx
      regex vn3_regex("vn \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, vn3_regex)) {
        index_vertex_normal++;
        objets.front().ajouterVertexNormal(index_vertex_normal, stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()), 0.0);
        continue;
      }


      //Le cas de vn xxxx xxxx xxxx xxxxx
      regex vn4_regex("vn \\(-*.*\\) \\(-*.*\\) \\(-*.*\\) \\(-*.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, vn4_regex)) {
        index_vertex_normal++;
        objets.front().ajouterVertexNormal(index_vertex_normal, stod(m[1].str().c_str()), stod(m[2].str().c_str()), stod(m[3].str().c_str()), stod(m[4].str().c_str()));
        continue;
      }


      //Les faces
      //Le cas de f xxxx xxxx xxxx
      //exemple
      //f 4//9 2//9 20//9 18//9 16//9 14//9 12//9 10//9 8//9 6//9
      //f [0-9\/ ]*
      //regex f3_regex("f \\([0-9/]*\\) \\([0-9/]*\\) \\([0-9/]*\\)$", regex_constants::basic);
      regex f_regex("f \\([0-9\\/ ]*\\)", regex_constants::basic);

      if(regex_search(*it, m, f_regex)) {
        parserFace(m[1].str());
        continue;
      }
/*
      //Le cas de f xxxx xxxx xxxx xxxxx
      regex f4_regex("f \\(.*\\) \\(.*\\) \\(.*\\) \\(.*\\)$", regex_constants::basic);

      if(regex_search(*it, m, f4_regex)) {
        parserFace(m);
        continue;
      }
*/
  }

  //printf ("FIN parcours fichier RAM\n");
  //printf("Fin du traitement\n");
}


int ObjParser::parserFace(string m) {
  Face *f = new Face(mat_courant);

  regex v_vt_vn_regex("^\\([0-9]*\\)/\\([0-9]*\\)/\\([0-9]*\\)$", regex_constants::basic);
  smatch sm;


  vector<string> matches = split(m, " "); // divise les arguments trouves
  vector<string>::iterator it;

	for(it = matches.begin(); it != matches.end(); it++) {
    string str = *it;

    if(regex_search(str, sm, v_vt_vn_regex)) {

    if(sm[1].str() != "" && sm[2].str() == "" && sm[3].str() == "") {
      f->ajouterNumVertex(atoi(sm[1].str().c_str()));
    }

    if(sm[1].str() != "" && sm[2].str() != "" && sm[3].str() == "") {
      f->ajouterNumVertex(atoi(sm[1].str().c_str()));
      f->ajouterNumVertexTexture(atoi(sm[2].str().c_str()));
    }

    if(sm[1].str() != "" && sm[2].str() == "" && sm[3].str() != "") {
      f->ajouterNumVertex(atoi(sm[1].str().c_str()));
      f->ajouterNumVertexNormal(atoi(sm[3].str().c_str()));
    }

    if(sm[1].str() != "" && sm[2].str() != "" && sm[3].str() != "") {
      f->ajouterNumVertex(atoi(sm[1].str().c_str()));
      f->ajouterNumVertexTexture(atoi(sm[2].str().c_str()));
      f->ajouterNumVertexNormal(atoi(sm[3].str().c_str()));
    }
    }
  }

  objets.front().ajouterFace(*f);
  return 0;
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

vector<string> ObjParser::split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

