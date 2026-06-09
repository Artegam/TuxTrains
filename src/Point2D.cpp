#include "Board.h"

board::Point2D::Point2D () {_x = 0.0; _y = 0.0;}
board::Point2D::Point2D (double x, double y) {
  _x = x;
  _y = y;
}

void board::Point2D::move (double x, double y) {
  _x += x;
  _y += y;
}

void board::Point2D::setCoordinates(std::vector<double> coordinates) { _x = coordinates[0]; _y = coordinates[1];}
std::vector<double> board::Point2D::getCoordinates() {
  return {_x, _y};
}
