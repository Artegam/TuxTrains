#include "Board.h"

board::SquareBox::SquareBox() {
  _points.insert(std::make_pair(std::make_pair(0, 0), Point3D(0.0, 0.0, 0.0)));
  _points.insert(std::make_pair(std::make_pair(0, 1), Point3D(0.0, 0.0, 1.0)));
  _points.insert(std::make_pair(std::make_pair(1, 1), Point3D(1.0, 0.0, 1.0)));
  _points.insert(std::make_pair(std::make_pair(1, 0), Point3D(1.0, 0.0, 0.0)));
}

board::SquareBox::SquareBox(std::map<std::pair<unsigned int, unsigned int>, board::Point3D> data) {
  _points.clear();
  _points.insert(data.begin(), data.end());
}

void board::SquareBox::move(std::pair<unsigned int, unsigned int> position) {
  for(std::map<std::pair<unsigned int, unsigned int>, board::Point3D>::iterator it = _points.begin(); it!=_points.end(); it++) {
    Point3D p = it->second;
    p.move(position.first, 0.0, position.second); 
  }
}
