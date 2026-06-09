#include "Board.h"

board::Point3D::Point3D () : board::Point2D() {_z = 0.0;}
board::Point3D::Point3D (double x, double y, double z) : Point2D(x, y) {
  _z = z;
}
board::Point3D::Point3D(std::vector<double> coordinates) : board::Point2D(coordinates[0], coordinates[1]) { _z = coordinates[2];}

void board::Point3D::move (double x, double y, double z) {
  Point2D::move(x, y);
  _z += z;
}

std::vector<double> board::Point3D::getCoordinates() {
  std::vector<double> vec = Point2D::getCoordinates();
  vec.push_back(_z);
  return vec;
}

void board::Point3D::setCoordinates(std::vector<double> coordinates) {board::Point2D::setCoordinates(coordinates); _z = coordinates[2];}
void board::Point3D::elevate (double elevation) {
  std::vector<double> vec = Point2D::getCoordinates();
  Point2D::move(vec[0], elevation);
}
