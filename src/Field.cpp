#include "Board.h"

board::Field::Field(unsigned int width, unsigned int height) {
  _width = width;
  _height = height;
  for(unsigned int z = 0; z <= _height; z++)
    for(unsigned int x = 0; x <= _width; x++)
      _points.insert(std::make_pair(std::make_pair(x, z), Point3D(x, 0.0, z)));
}

board::SquareBox board::Field::getSquareBox(std::pair<unsigned int, unsigned int> position) {
  return board::SquareBox();
}

board::Point3D board::Field::getCenter() {
  if(_points.size() == 1)
    return Point3D(0.0, 0.0, 0.0);

  unsigned int x = _width / 2;
  unsigned int z = _height / 2;
  return _points[{x, z}];
}

void board::Field::processElevation(std::map<std::pair<unsigned int, unsigned int>, double> elevation) {
  for(unsigned int z = 0; z <= _height; z++)
    for(unsigned int x = 0; x <= _width; x++)
      _points[{x, z}].elevate(elevation[{x, z}]);
}

