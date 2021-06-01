

#include "Objet3D.h"
#include <stdio.h>
#include <math.h>

//test pour les fichiers tildeÃ©s
void afficherVertex(Vertex& v);

string Objet3D::getNom() {
	return nom;
}

void Objet3D::setNom(const char* pNom) {
	nom = pNom;
}

string Objet3D::getNomMateriau(){
  return mat.getNom();
}

void Objet3D::setMateriau(Material pNomMateriau) {
  mat = pNomMateriau;
}

Material Objet3D::getMateriau() {
  return mat;
}

void Objet3D::ajouterVertex(int index, double pX, double pY, double pZ, double pW){
	Vertex * v = new Vertex();

	v->setX(pX);
	v->setY(pY);
	v->setZ(pZ);
	if (pW > 0) v->setW(pW);

	vertices[index] = *v;
}

void Objet3D::ajouterVertexNormal(int index, double pX, double pY, double pZ, double pW){
	VertexNormal * vn = new VertexNormal();

	vn->setX(pX);
	vn->setY(pY);
	vn->setZ(pZ);
	if (pW > 0) vn->setW(pW);
	verticesNormal[index] = *vn;
}

void Objet3D::ajouterFace(const int nbParametres, char** parametres){

  const int MAX = nbParametres;
	if (MAX > 0) {
		Face * f = new Face(mat);

		for(int cpt = 0; cpt < MAX; cpt++) {
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
          f->ajouterNumVertex(atoi(tokens[0].c_str()));
          break;

        case 2:// cas v/vt
          if(tokens[1].compare("") != 0) { // vt present
            f->ajouterNumVertex(atoi(tokens[0].c_str()));
            f->ajouterNumVertexTexture(atoi(tokens[1].c_str()));
          }

          // cas v//vn
          if(tokens[1].compare("") == 0) { // vt absent
            f->ajouterNumVertex(atoi(tokens[0].c_str()));
            f->ajouterNumVertexNormal(atoi(tokens[2].c_str()));
          }
          break;

        case 3:// cas v/vt/vn
          f->ajouterNumVertex(atoi(tokens[0].c_str()));
          f->ajouterNumVertexTexture(atoi(tokens[1].c_str()));
          f->ajouterNumVertexNormal(atoi(tokens[2].c_str()));
          break;
      }
		}
		faces.insert(faces.end(), *f);
	}
}


void Objet3D::ajouterFace(Face f) {
  faces.insert(faces.end(), f);
}

void afficherVertex(Vertex& v) {
	v.dessiner();
}

void Objet3D::init() {

  // Instanciation de la liste
  //listeAffichage = glGenLists(100);

  printf("Initialisation de l'objet %s '%s'\n", nom.c_str(), mat.getNom().c_str());
  printf("v: %ld, vn: %ld, f: %ld\n", vertices.size(), verticesNormal.size(), faces.size());

  // CrÃation et dÃ©finition de la liste d'affichage
  //glNewList(listeAffichage, GL_COMPILE);
/*
  //Calcul de l'objet (points, faces, etc...
 	vector<Face>::iterator it;

	//if (faces.size() > 0) printf("%s nb de faces : %d\n", nom, faces.size());
	for(it = faces.begin(); it != faces.end(); it++) {
		it->dessiner(vertices, verticesNormal);
	}
*/
  //glEndList();

}

void Objet3D::dessiner() {

  //Calcul de l'objet (points, faces, etc...
 	vector<Face>::iterator it;

  if(nom == "Roue_AVG_Circle.002" ||
      nom == "Roue_AVD_Circle.004" ||
      nom == "Roue_ARD_Circle.005" ||
      nom == "Roue_ARG_Circle.006") {

    angle += 10.0;
    Vertex barycentre = calculerBarycentre();

    // ************* Se positionner sur le barycentre **********
    //OpenGL n'a pas le meme repere que blender.... GGrrrrr...
    //Cubes position barycentre
    //On peux dessiner un cube sur la position du barycentre
    glPushMatrix();
    glTranslatef(barycentre.getX(), barycentre.getY(), barycentre.getZ());
    glRotatef(angle,0.0,0.0,1.0);
    //glutSolidCube(0.25);
    glPopMatrix();



    // ************ Matrice pour les roues *************
    glPushMatrix();


    // **********  Animation de rotation des roues **********
    // Les operations matricielles sont inversees
    //OpenGL n'a pas le meme repere que blender.... GGrrrrr...
    glTranslatef(barycentre.getX(), barycentre.getY(), barycentre.getZ());
    glRotatef(angle,0.0,0.0,1.0);
    glTranslatef(-barycentre.getX(), -barycentre.getY(), -barycentre.getZ());


    // ********** Dessiner les roues *********
    glBegin(GL_TRIANGLES);
    for(it = faces.begin(); it != faces.end(); it++) {
      it->dessiner(vertices, verticesNormal);
    }
    glEnd();
    glPopMatrix();

  }else if(nom == "Bras_puissance_G_Cube.001" ||
           nom == "Bras_puissance_D_Cube.006" ||
           nom == "Bras_entrainement_G_Cube.002" ||
           nom == "Bras_entrainement_D_Cube.005") {


    Vertex barycentre = calculerBarycentre();

    facteurX += step;
    if(facteurX <= -1.0 || facteurX >= 1.0) {step = -step;}

    // ************* Se positionner sur le barycentre **********
    //OpenGL n'a pas le meme repere que blender.... GGrrrrr...
    //Cubes position barycentre
    //On peux dessiner un cube sur la position du barycentre
    glPushMatrix();
    glTranslatef(barycentre.getX() + facteurX, barycentre.getY(), barycentre.getZ());
    glTranslatef(-barycentre.getX(), -barycentre.getY(), -barycentre.getZ());
    //glutSolidCube(0.25);
    glPopMatrix();



    // ************ Matrice pour les roues *************
    glPushMatrix();


    // **********  Animation de rotation des roues **********
    // Les operations matricielles sont inversees
    //OpenGL n'a pas le meme repere que blender.... GGrrrrr...


    if(nom == "Bras_entrainement_G_Cube.002" ||
       nom == "Bras_entrainement_D_Cube.005") {
      //Je le remets a sa place sur l'objet
      glTranslatef(barycentre.getX() + facteurX, barycentre.getY(), barycentre.getZ());
      // Je fais la transformation
      angle += 10.0;
      glRotatef(angle,0.0,0.0,1.0);
      glutSolidCube(0.25);
      glTranslatef(1.0, 0, 0);
      // Je l'amene en 0
      glTranslatef(-barycentre.getX(), -barycentre.getY(), -barycentre.getZ());
    } else {
      //Je le remets a sa place sur l'objet
      glTranslatef(barycentre.getX() + facteurX, barycentre.getY(), barycentre.getZ());
      // Je fais la transformation
      // Je l'amene en 0
      glTranslatef(-barycentre.getX(), -barycentre.getY(), -barycentre.getZ());
    }

    // ********** Dessiner les roues *********
    glBegin(GL_TRIANGLES);
    for(it = faces.begin(); it != faces.end(); it++) {
      it->dessiner(vertices, verticesNormal);
    }
    glEnd();
    glPopMatrix();


  }else{
    //dessiner
    glBegin(GL_TRIANGLES);
    for(it = faces.begin(); it != faces.end(); it++) {
      //it->dump(vertices);
      it->dessiner(vertices, verticesNormal);
    }
    glEnd();
  }


/*
	//if (faces.size() > 0) printf("%s nb de faces : %d\n", nom, faces.size());
	for(it = faces.begin(); it != faces.end(); it++) {
    //it->dump();
		it->dessiner(vertices, verticesNormal);
	}
*/
  //glEnd();
    //glCallList(listeAffichage);
}

Vertex Objet3D::calculerBarycentre() {

  Vertex barycentre;
  unsigned int nbPts = vertices.size();

  double sommeX = 0.0;
  double sommeY = 0.0;
  double sommeZ = 0.0;

  map<int, Vertex>::iterator it;


  for(it = vertices.begin(); it != vertices.end(); it++) {
    sommeX += it->second.getX();
    sommeY += it->second.getY();
    sommeZ += it->second.getZ();
  }

  barycentre.setX(sommeX/nbPts);
  barycentre.setY(sommeY/nbPts);
  barycentre.setZ(sommeZ/nbPts);

  return barycentre;
}

