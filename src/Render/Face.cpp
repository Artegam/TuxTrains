
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

void Face::dessiner(map<int, Vertex> pVertices, map<int, VertexNormal> pVerticesNormal){

  //Materiau
  //mat.printInfos();
  mat.dessiner();


	//glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
  //glNormal3d(0, 0, 1);

  // Si la taille de la liste est < 3 il faut sortir une ereur

  // Si la taille de la liste est >= 3 C'est bon
  //
  // Il faut parcourir la liste suivant le critÃ¨re :
  // Taille de la liste - 3
  //
  // exemple taille de la liste = 7
  // 7 - 3 = 4 => 4 iterations (de 0 a 3)
  //
  // pour offset, offset + 1, offset + 2
  // calculer les deux index
  // dessiner les deux vertex
  //
  //

  int index = 0;
  int index_normal = 0;

  if(vertexNums.size() >= 3) {

    for(unsigned int i = 0; i <= vertexNums.size() - 3; i++) {

      // Vertex 1
      index = vertexNums[i];
      index_normal = vertexNormalNums[i];

      pVerticesNormal[index_normal].dessiner();
      pVertices[index].dessiner();

      // Vertex 2
      index = vertexNums[i+1];
      index_normal = vertexNormalNums[i+1];

      pVerticesNormal[index_normal].dessiner();
      pVertices[index].dessiner();

      // Vertex 3
      index = vertexNums[i+2];
      index_normal = vertexNormalNums[i+2];

      pVerticesNormal[index_normal].dessiner();
      pVertices[index].dessiner();

    }

  }
  unsigned int i = vertexNums.size() - 3;

  // Vertex 2
  index = vertexNums[i+1];
  index_normal = vertexNormalNums[i+1];

  pVerticesNormal[index_normal].dessiner();
  pVertices[index].dessiner();

  // Vertex 3
  index = vertexNums[i+2];
  index_normal = vertexNormalNums[i+2];

  pVerticesNormal[index_normal].dessiner();
  pVertices[index].dessiner();

  //Vertex 0
  index = vertexNums[0];
  index_normal = vertexNormalNums[0];

  pVerticesNormal[index_normal].dessiner();
  pVertices[index].dessiner();


  //glEnd();

}

