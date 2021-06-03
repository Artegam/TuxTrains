
#include "VertexNormal.h"


VertexNormal::VertexNormal() {
  x = 0.0;
  y = 0.0;
  z = 0.0;
  w = 1.0;
}

void VertexNormal::setX(double pX) {
	x = pX;
}

void VertexNormal::setY(double pY) {
	y = pY;
}

void VertexNormal::setZ(double pZ) {
	z = pZ;
}

void VertexNormal::setW(double pW) {
	w = pW;
}

double VertexNormal::getX() {
	return x;
}

double VertexNormal::getY() {
	return y;
}

double VertexNormal::getZ(){
	return z;
}

double VertexNormal::getW(){
	return w;
}

void VertexNormal::dessiner() {
  //printf("dessiner - vn %lf %lf %lf\n", x, y, z);
	glNormal3d(x, y, z);
}
