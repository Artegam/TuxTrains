#include "GL_Board.h"

void glboard::GL_Point3D::display () {
  std::vector<double> vec = GL_Point3D::getCoordinates();
  glTranslatef(vec[0], vec[1], vec[2]);
  glutSolidCube(0.1);
  glTranslatef(-vec[0], -vec[1], -vec[2]);
}
