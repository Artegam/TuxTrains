
#include "Face.h"

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


void Face::dessiner(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal){

	int nbPoints = vertexNums.size();

  //if(vertexNums.size() < 3 and vertexNums.size() > 4) printf("Nb Points : %d\n", vertexNums.size());

  //Materiau
  mat.printInfos();
  mat.dessiner();

	glBegin(GL_TRIANGLES);
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
