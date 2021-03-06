

#include "Objet3D.h"
#include <stdio.h>


void afficherVertex(Vertex& v);

char* Objet3D::getNom() {
	return nom;
}

void Objet3D::setNom(char* pNom) {
	nom = pNom;
}

void Objet3D::ajouterVertex(double pX, double pY, double pZ, double pW){
	Vertex * v = new Vertex();

	v->setX(pX);
	v->setY(pY);
	v->setZ(pZ);
	if (pW > 0) v->setW(pW);

	vertices.insert(vertices.end(), *v);
}

void Objet3D::ajouterVertexNormal(double pX, double pY, double pZ, double pW){
	VertexNormal * vn = new VertexNormal();

	vn->setX(pX);
	vn->setY(pY);
	vn->setZ(pZ);
	if (pW > 0) vn->setW(pW);
	//printf("Vn %lf %lf %lf \n", pX, pY, pZ);
	verticesNormal.insert(verticesNormal.end(), *vn);
}

void Objet3D::ajouterFace(const int nbParametres, char** parametres){

	int numVertex[4];
	int numVertexTexture[4];
	int numVertexNormal[4];
	int nbVertexInfo;
	int numCas;
  const int MAX = nbParametres;

	if (MAX > 0) {

		Face f;

		for(int cpt = 0; cpt < MAX; cpt++) {
			numCas = 0;

      string delimiter = "/";
      string token;
      size_t pos = 0;
      vector<string> tokens;
      string param = parametres[cpt];
      vector<string>::iterator it;

      while((pos = param.find(delimiter)) != string::npos) {
        token = param.substr(0, pos);
        tokens.push_back(token);
        param.erase(0, pos + delimiter.length());
      }
      //Ajouter le dernier element
      token = param.substr(0, param.size());
      tokens.push_back(token);

      switch(tokens.size()){
        case 1:   // cas v
          f.ajouterNumVertex(atoi(tokens[0].c_str()));
          break;

        case 2:// cas v/vt
          if(tokens[1].compare("") != 0) { // vt present
            f.ajouterNumVertex(atoi(tokens[0].c_str()));
            f.ajouterNumVertexTexture(atoi(tokens[1].c_str()));
          }

          // cas v//vn
          if(tokens[1].compare("") == 0) { // vt absent
            f.ajouterNumVertex(atoi(tokens[0].c_str()));
            f.ajouterNumVertexNormal(atoi(tokens[2].c_str()));
          }
          break;

        case 3:// cas v/vt/vn
          f.ajouterNumVertex(atoi(tokens[0].c_str()));
          f.ajouterNumVertexTexture(atoi(tokens[1].c_str()));
          f.ajouterNumVertexNormal(atoi(tokens[2].c_str()));
          break;

      }


		}
		faces.insert(faces.end(), f);
	}
}


void afficherVertex(Vertex& v) {
	v.dessiner();
}

void Objet3D::init() {

  // Instanciation de la liste
  listeAffichage = glGenLists(1);

  printf("Initialisation de l'objet %s\n", nom);
  // CrÃation et dÃ©finition de la liste d'affichage
  glNewList(listeAffichage, GL_COMPILE);

  //Calcul de l'objet (points, faces, etc...
 	vector<Face>::iterator it;

	//if (faces.size() > 0) printf("%s nb de faces : %d\n", nom, faces.size());
	for(it = faces.begin(); it != faces.end(); it++) {
		it->dessiner(vertices, verticesNormal);
	}

  glEndList();

}

void Objet3D::dessiner() {

  glCallList(listeAffichage);

}
