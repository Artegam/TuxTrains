
#include "Face.h"


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
/*
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 3; i++){
		if(vertexNormalNums.size() > 0) {
			int normalIndex = (int)vertexNormalNums[i];
			if(pVerticesNormal.size() > 0) pVerticesNormal[normalIndex-1].dessiner();
		}

		int index = (int)vertexNums[i];		
		pVertices[index-1].dessiner();
	}
	glEnd();


	if (vertexNums.size() > 3) {
		//glBegin(GL_LINE_LOOP);
		glBegin(GL_TRIANGLES);
		for(int i = 2; i != 1; i = (i + 1)%vertexNums.size()){
			if(vertexNormalNums.size() > 0) {
				int normalIndex = (int)vertexNormalNums[i];
				if(pVerticesNormal.size() > 0) pVerticesNormal[normalIndex-1].dessiner();
			}

			int index = (int)vertexNums[i];
			pVertices[index-1].dessiner();
		}
		glEnd();
	}
*/

	int nbPoints = vertexNums.size();
	//if(vertexNums.size() < 3 and vertexNums.size() > 4) printf("Nb Points : %d\n", vertexNums.size());
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
