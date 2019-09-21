#ifndef FACE_H
#define FACE_H

#include <vector>
//#include <algorithm>

#include "Vertex.h"
#include "VertexNormal.h"
#include "Material.h"

using namespace std;

class Face {

	protected:
    Material mat;
		vector<long> vertexNums;
		vector<long> vertexTextNums;
		vector<long> vertexNormalNums;
		//vector<Vertex> vertices;


	public:
    Face();
    Face(Material m);

		void ajouterNumVertex(long numVertex);
		void ajouterNumVertexTexture(long numVertexTexture);
		void ajouterNumVertexNormal(long numVertexNormal);

		void dessiner(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal);
    void dump(void);

};


#endif
