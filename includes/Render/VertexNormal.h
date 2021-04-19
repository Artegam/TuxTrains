#ifndef VERTEXNORMAL_H
#define VERTEXNORMAL_H

#include <stdio.h>
#include <GL/glut.h>

class VertexNormal {

	protected:
		double x;
		double y;
		double z;
		double w;

	public:

		VertexNormal();

		void setX(double pX);
		void setY(double pY);
		void setZ(double pZ);
		void setW(double pW);

		double getX();
		double getY();
		double getZ();
		double getW();

		void dessiner();
};

#endif
