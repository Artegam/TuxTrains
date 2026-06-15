
#include "ObjParser.h"
#include "Board.h"
#include <iobyte.h>

//ASCH - 17/10/2014 - Parametres


//ASCH - 17/10/2014 - Methodes
vector<board::SquareBox> ObjParser::readFile (const char * filename) {
  iobyte::Device * d = new iobyte::Device(filename);
  unsigned int filesize = d->size();
  unsigned int blocksize = d->blockSize();
  unsigned int blocksnumber = filesize / blocksize;
  vector<string> data;
  printf ("Debut de lecture du fichier\n");
  for(unsigned int block = 0; block <= blocksnumber; block++)
    data.push_back(d->binaryRead(block));
  printf ("Fin de lecture du fichier\n");

  printf ("Analyse des blocks...\t");
  string line;
  string key;
  unsigned int cpt = 0;
  vector<board::Point3D> vertices;
  vector<double> vertex;
  vector<board::Point3D> normals;
  vector<double> normal;
  vector<board::SquareBox> faces; //[ASC] les faces de l'objet
  std::map<std::pair<unsigned int, unsigned int>, board::Point3D> face_points;
  unsigned int face_points_cpt = 0;
  unsigned int block = 0;
  for(vector<string>::iterator it = data.begin(); it != data.end(); it++) {
    //[ASC] ici la taille d'un block est importante
    string str_block = *it;
    unsigned int limit_end = blocksize;
    if(limit_end > filesize-(block*blocksize)) limit_end = filesize-(block*blocksize);
    for(unsigned int i = 0; i<=limit_end; i++) {
      if(str_block[i] == ' ' || str_block[i] == '\n') {
        if(key == "v") { //[ASC] vertex
          vertex.push_back(std::stod(line));
          if(str_block[i] == '\n') {
/*
            //[ASC] y et z sont inversés dans notre représentation opengl
            double tmp = vertex[2];
            vertex[2] = vertex[1];
            vertex[1] = tmp;
*/
            vertices.push_back(board::Point3D(vertex));
            vertex.clear();
          }
          line.clear();
        } else if(key == "vn") { //[ASC] normal
          normal.push_back(std::stod(line));
          if(str_block[i] == '\n') {
            normals.push_back(board::Point3D(normal));
            normal.clear();
          }
          line.clear();
        } else if(key == "f") { //[ASC] face
          //[ASC] traiter le format f v1/vt1/vn1 (v: vertex, vt: vertex texture, vn: vertex normal)
          //[ASC] Attention seul vertex est traite pour l instant
          vector<std::string> elts = split(line, "/");
          unsigned int v_index = 0;
          unsigned int vt_index = 0;
          unsigned int vn_index = 0;

          if(elts[0].size()>0) v_index = std::stoi(elts[0]);
          if(elts[1].size()>0) vt_index = std::stoi(elts[1]);
          if(elts[2].size()>0) vn_index = std::stoi(elts[2]);

          unsigned int idx = face_points_cpt;
          unsigned int y = idx % 2;
          unsigned int x = (idx>>1)%2;

          vertices[v_index-1].setNormal(normals[vn_index-1].getCoordinates()); //[ASC] erreur induite ici car il peut y avoir plusieurs vecteurs normal en un point
          face_points.insert(std::make_pair(std::make_pair(x, y), vertices[v_index-1]));
          face_points_cpt++;
          if(str_block[i] == '\n') {
            faces.push_back(board::SquareBox(face_points));
            face_points.clear();
            face_points_cpt = 0;
          }
          line.clear();
        }
        if(key.size() == 0) {
          key = line;
          line.clear();
        }
      }
      if(str_block[i] != 0x00 && str_block[i] != ' ' && str_block[i] != '\n') line.push_back(str_block[i]);
      if(str_block[i] == '\n') {
        cpt++;
        key.clear();
        line.clear();
      }
    }
    block++;
  }
  printf ("[Termine]\n");
//  string sligne;
/*
  vector<string> fichierRAM;
  fichierRAM.insert(fichierRAM.end(), data.begin(), data.end());
*/
/*
  ifstream fichier;
  fichier.open(filename, ios::in);
  printf ("Debut de lecture du fichier\n");

  while(!fichier.eof()) {
   getline(fichier, sligne);
   fichierRAM.insert(fichierRAM.end(), sligne);
  }

  fichier.close();
  printf ("Fin de lecture du fichier\n");
*/

/*
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
        char* nom = new char[tokens[1].size() + 1];
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
        printf("Nom de la librairie de maetriaux : %s\n", tokens[1].c_str());
        continue;
      }

    }
    tokens.clear();
  }

  printf ("FIN parcours fichier RAM\n");
*/
  printf("Fin du traitement\n");
  //return objets;
  return faces;
}

vector<std::string> ObjParser::split(std::string str, std::string delimiter) {
  vector<std::string> pieces;
  unsigned int start_position = 0;
  unsigned int delim_position = 0;
  while(delim_position < str.size()) {
    delim_position = str.find(delimiter, start_position);
    pieces.push_back(str.substr(start_position, delim_position - start_position));
    start_position = delim_position + delimiter.size();
  }
  return pieces;
}
