#include "GL_Board.h"

void glboard::GL_Point2D::display () {
  std::vector<double> vec = this->getCoordinates();
  glVertex2f(vec[0], vec[1]);
}
