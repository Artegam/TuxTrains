#ifndef FACE_H
#define FACE_H

#include <vector>
//#include <algorithm>

#include "Vertex.h"
#include "VertexNormal.h"

using namespace std;

class Face {

	private:
		vector<long> vertexNums;
		vector<long> vertexTextNums;
		vector<long> vertexNormalNums;
		//vector<Vertex> vertices;


	public:
		void ajouterNumVertex(long numVertex);
		void ajouterNumVertexTexture(long numVertexTexture);
		void ajouterNumVertexNormal(long numVertexNormal);

		void dessiner(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal);

};


#endif
