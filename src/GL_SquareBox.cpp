#include "GL_Board.h"

void glboard::GL_SquareBox::display () {
  std::map<std::pair<unsigned int, unsigned int>, board::Point3D> points = getPoints();

  glBegin(GL_TRIANGLES);

  //Soit 4 points ABCD
  //Dessiner ABC
  GL_Point3D(points[{0, 0}]).display();
  GL_Point3D(points[{0, 1}]).display();
  GL_Point3D(points[{1, 1}]).display();

  //Dessiner ACD
  GL_Point3D(points[{0, 0}]).display();
  GL_Point3D(points[{1, 1}]).display();
  GL_Point3D(points[{1, 0}]).display();

  glEnd();
}
