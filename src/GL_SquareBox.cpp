#include "GL_Board.h"

glboard::GL_SquareBox::GL_SquareBox(std::map<std::pair<unsigned int, unsigned int>, board::Point3D> data) : board::SquareBox(data) {};
void glboard::GL_SquareBox::display () {
  std::map<std::pair<unsigned int, unsigned int>, board::Point3D> points = getPoints();

  glBegin(GL_TRIANGLES);

  //Soit 4 points ABCD
  //Dessiner ABC
  display(GL_Point3D(points[{0, 0}]));
  display(GL_Point3D(points[{0, 1}]));
  display(GL_Point3D(points[{1, 1}]));

  //Dessiner ACD
  display(GL_Point3D(points[{0, 0}]));
  display(GL_Point3D(points[{1, 1}]));
  display(GL_Point3D(points[{1, 0}]));

  glEnd();
}

void glboard::GL_SquareBox::display(GL_Point3D pt) {
  std::vector<double> vec = pt.getCoordinates();
  glVertex3f(vec[0], vec[1], vec[2]);
}
