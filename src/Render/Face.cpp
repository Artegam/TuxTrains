
#include "Face.h"

Face::Face(){
  Material *m = new Material();
  mat = *m;
}

Face::Face(Material m){
  mat = m;
}

void Face::ajouterNumVertex(long numVertex) {
	vertexNums.insert(vertexNums.end(), numVertex);
}

void Face::ajouterNumVertexTexture(long numVertexTexture) {
	vertexTextNums.insert(vertexTextNums.end(), numVertexTexture);
}


void Face::ajouterNumVertexNormal(long numVertexNormal) {
	vertexNormalNums.insert(vertexNormalNums.end(), numVertexNormal);
}

void Face::dump() {
  printf("####### dump face #########\n");
  printf(" vertex\n");
  for(unsigned int i = 0; i < vertexNums.size(); i++) {
    printf("%ld ", vertexNums[i]);
  }
  printf("\n vertex normal\n");
  for(unsigned int i = 0; i < vertexNormalNums.size(); i++) {
    printf("%ld ", vertexNormalNums[i]);
  }
  printf("\n vertex texture\n");
  for(unsigned int i = 0; i < vertexTextNums.size(); i++) {
    printf("%ld ", vertexTextNums[i]);
  }
  printf("\n");
}

void Face::dessiner(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal){

	int nbPoints = vertexNums.size();

  //if(vertexNums.size() < 3 and vertexNums.size() > 4) printf("Nb Points : %d\n", vertexNums.size());

  //Materiau
  //mat.printInfos();
  mat.dessiner();

//  glBegin(GL_QUADS);
//  glutSolidCube(1.0);
//  glEnd();

	glBegin(GL_TRIANGLES);
  //glNormal3d(0, 0, 1);
	for(int cpt = 1; cpt < nbPoints-1; cpt++){
		int index;
		int normalIndex;

		// origine
		if(vertexNormalNums.size() > 0) {
			normalIndex = (int)vertexNormalNums[0];
			if(pVerticesNormal.size() > 0) pVerticesNormal[normalIndex-1].dessiner();
		}
		index = (int)vertexNums[0];
		pVertices[index-1].dessiner();

		//Cpt
		if(vertexNormalNums.size() > 0) {
			normalIndex = (int)vertexNormalNums[cpt];
			if(pVerticesNormal.size() > 0) pVerticesNormal[normalIndex-1].dessiner();
		}
		index = (int)vertexNums[cpt];
		pVertices[index-1].dessiner();

		//Cpt +1
		if(vertexNormalNums.size() > 0) {
			normalIndex = (int)vertexNormalNums[cpt+1];
			if(pVerticesNormal.size() > 0) pVerticesNormal[normalIndex-1].dessiner();
		}
		index = (int)vertexNums[cpt+1];
		pVertices[index-1].dessiner();

	}
	glEnd();

}
